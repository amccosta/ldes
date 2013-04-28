#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "pvm3.h"

#define ABORT(message, code) \
do {fprintf(stderr, "error: %s [%d]\n", message, code);\
if (pvm_mytid() >= 0) pvm_exit();\
exit(code);} while (0)

#define WARNING(message) \
do {if (verbose) fprintf(stderr, "warning: %s\n", message);} while (0)

#define SLAVE "rtslave"

#define RAYS_TASK 32

static char verbose = 1;

typedef struct _server_strcut {
  int task, free, first, size, work;
  float calc, tran;
} server_struct;

typedef struct _rt_struct {
  float point[3], dir[3], value[3];
} rt_struct;

static int
input_data(int n, float *data, rt_struct **prt_data)
{
  rt_struct *rt_data;
  float *pdata = data;
  int i;

  rt_data = (rt_struct *) malloc(n * sizeof(rt_struct));
  if (!rt_data) return 1;
  *prt_data = rt_data;
  for (i = 0; i < n; i++)
  {
    rt_data[i].point[0] = *pdata++;
    rt_data[i].point[1] = *pdata++;
    rt_data[i].point[2] = *pdata++;
    rt_data[i].dir[0] = *pdata++;
    rt_data[i].dir[1] = *pdata++;
    rt_data[i].dir[2] = *pdata++;
  }
  return 0;
}

static void
output_data(int rays, rt_struct *rt_data, float *data)
{
  float *pdata = data;
  int i;

  for (i = 0; i < rays; i++)
  {
    *pdata++ = rt_data[i].value[0];
    *pdata++ = rt_data[i].value[1];
    *pdata++ = rt_data[i].value[2];
  }
}

static int servers, *server_tid;
static server_struct *server_data;

static void
rtmain(char *name, int pref_rays_task, int rays, rt_struct *rt_data)
{
  int server;
  int rays_task;
  int ray_current, ray_block, ray_current_rec, ray_block_rec;
  int tasks, tasks_todo, task;
  int tid, i;
  char error_rec;

  if (pvm_mytid() < 0) ABORT("PVM not running", 1);

  for (server = 0; server < servers; server++)
  {
    server_data[server].free = server - 1;
    if (verbose)
    {
      server_data[server].work = 0;
      server_data[server].calc = 0;
      server_data[server].tran = 0;
    }
  }
  server--;

  rays_task = pref_rays_task;
  if (rays_task < 1) rays_task = 5;
  else if (rays_task > rays) rays_task = rays;
  tasks = (rays + rays_task - 1) / rays_task;
  if (verbose > 1) fprintf(stderr, "%d task(s)\n", tasks);
  task = tasks;
  tasks_todo = tasks;
  ray_current = 0;
  ray_block = rays_task;

  /* 1st group */
  while (server >= 0 && task)
  {
    server_data[server].task = --task;
    server_data[server].first = ray_current;
    server_data[server].size = ray_block;

    pvm_initsend(PvmDataRaw);
    pvm_pkint(&ray_current, 1, 1);
    pvm_pkint(&ray_block, 1, 1);
    pvm_pkstr(name);
    for (i = 0; i < ray_block; i++)
    {
      pvm_pkfloat(rt_data[ray_current + i].point, 3 , 1);
      pvm_pkfloat(rt_data[ray_current + i].dir, 3 , 1);
    }
    if (pvm_send(server_tid[server], 1))
    {
      WARNING("cannot send task");
      if (verbose > 1)
        fprintf(stderr, "task not sent %d to server %d <%x>\n",
                task, server, server_tid[server]);
      ABORT("server not available", 5);
    }
    if (verbose > 1)
      fprintf(stderr, "task sent %d to server %d <%x> ray %d [%d]\n",
              task, server, server_tid[server], ray_current, ray_block);

    server = server_data[server].free;
    ray_current += ray_block;
    if (ray_current + ray_block - 1 >= rays) ray_block = rays - ray_current;
  }

  /* 2nd group */
  while (tasks_todo && pvm_recv(-1, 2) >= 0)
  {
    pvm_bufinfo(pvm_getrbuf(), (int *) 0, (int *) 0, &tid);
    for (server = 0; server < servers; server++)
      if (server_tid[server] == tid) break;
    if (server >= servers)
    {
      WARNING("unknown server!");
      continue;
    }

    tasks_todo--;
    if (verbose) server_data[server].work++;
    if (verbose > 1)
      fprintf(stderr, "finished task %d from server %d <%x>\n",
              server_data[server].task, server, tid);

    pvm_initsend(PvmDataRaw);
    if (pvm_send(tid, 3))
    {
      WARNING("cannot send request");
      if (verbose > 1) fprintf(stderr, "server %d <%x>\n", server, tid);
      ABORT("server not available", 6);
    }

    pvm_recv(tid, 4);
    pvm_upkint(&ray_current_rec, 1, 1);
    pvm_upkint(&ray_block_rec, 1, 1);
    if (ray_current_rec != server_data[server].first ||
        ray_block_rec != server_data[server].size)
    {
      WARNING("wrong data!");
      if (verbose > 1)
        fprintf(stderr, "ray %d [%d] (%d [%d])\n",
                ray_current_rec, ray_block_rec,
                server_data[server].first,
                server_data[server].size);
      continue;
    }

    pvm_upkbyte(&error_rec, 1, 1);
    if (error_rec)
    {
      WARNING("no data!");
      if (verbose > 1)
        fprintf(stderr, "ray(s) %d to %d (error %d)\n", ray_current_rec,
                ray_current_rec + ray_block_rec - 1, (int) error_rec);
    } else
    {
      for (i = 0; i < ray_block_rec; i++)
        pvm_upkfloat(rt_data[ray_current_rec + i].value, 3, 1);
      if (verbose > 1)
        fprintf(stderr, "ray(s) %d to %d done\n", ray_current_rec,
                ray_current_rec + ray_block_rec - 1);
    }

    pvm_initsend(PvmDataRaw);
    if (pvm_send(tid, 5))
    {
      WARNING("cannot send ack");
      if (verbose > 1) fprintf(stderr, "server %d <%x>\n", server, tid);
      ABORT("server not available", 7);
    }

    server_data[server].free = server;

    if (task)
    {
      server_data[server].task = --task;
      server_data[server].first = ray_current;
      server_data[server].size = ray_block;

      pvm_initsend(PvmDataRaw);
      pvm_pkint(&ray_current, 1, 1);
      pvm_pkint(&ray_block, 1, 1);
      pvm_pkstr(name);
      for (i = 0; i < ray_block; i++)
      {
        pvm_pkfloat(rt_data[ray_current + i].point, 3 , 1);
        pvm_pkfloat(rt_data[ray_current + i].dir, 3 , 1);
      }
      if (pvm_send(tid, 1))
      {
        WARNING("cannot send task");
        if (verbose > 1)
          fprintf(stderr, "task not sent %d to server %d <%x>\n",
                  task, server, tid);
        ABORT("server not available", 8);
      }
      if (verbose > 1)
        fprintf(stderr, "task sent %d to server %d <%x> ray %d [%d]\n",
                task, server, tid, ray_current, ray_block);

      server = server_data[server].free;
      ray_current += ray_block;
      if (ray_current + ray_block - 1 >= rays) ray_block = rays - ray_current;
    }
  }

  if (tasks_todo)
  {
    WARNING("missing tasks!");
    if (verbose > 1) fprintf(stderr, "%d task(s) not done\n", tasks_todo);
    ABORT("server problems", 9);
  }
}

static void
rtstart()
{
  int server;

  if (pvm_mytid() < 0) ABORT("PVM not running", 1);

  pvm_setopt(PvmRoute, PvmRouteDirect);
  pvm_config(&servers, (int *) 0, (struct pvmhostinfo **) 0);
  server_tid = (int *) malloc(servers * sizeof(int));
  if (!server_tid) ABORT("out of memory", 2);
  server = 0;
  while (server < servers)
  {
    if (pvm_spawn(SLAVE, 0, PvmTaskDefault, 0, 1, &server_tid[server]) < 1)
    {
      WARNING("cannot start server");
      if (verbose > 1) fprintf(stderr, "server %d\n", server);
      servers--;
    } else
      server++;
  }
  if (servers <= 0) ABORT("cannot start any server", 3);
  server_data = (server_struct *) malloc(servers * sizeof(server_struct));
  if (!server_data) ABORT("out of memory", 4);
}

static void
rtfinish()
{
  int server;
  float timecalc, timetran;

  if (pvm_mytid() < 0) ABORT("PVM not running", 1);

  for (server = 0; server < servers; server++)
  {
    pvm_initsend(PvmDataRaw);
    if (pvm_send(server_tid[server], 101))
    {
      WARNING("cannot send ack");
      if (verbose > 1)
        fprintf(stderr, "server %d <%x>\n", server, server_tid[server]);
    } else
    pvm_recv(server_tid[server], 102);
    pvm_upkfloat(&timecalc, 1, 1);
    pvm_upkfloat(&timetran, 1, 1);
    if (verbose)
    {
      server_data[server].calc += timecalc;
      server_data[server].tran += timetran;
    }
  }
  if (verbose)
    for (server = 0; server < servers; server++)
    {
      fprintf(stderr, "server %d: %d %g %g\n", server,
              server_data[server].work,
              server_data[server].calc,
              server_data[server].tran);
    }
}

static int rays_task;

int
rtrace(char *name, int rays, float *data)
{
  rt_struct *rt_data;
  struct timeval stime, etime;
  float runtime;

  if (input_data(rays, data, &rt_data)) return 1;

  if (verbose) gettimeofday(&stime, (struct timezone *) 0);
  rtmain(name, rays_task, rays, rt_data);
  if (verbose)
  {
    gettimeofday(&etime, (struct timezone *) 0);
    runtime = etime.tv_sec - stime.tv_sec +
            (etime.tv_usec - stime.tv_usec) / 1000000.0;
    fprintf(stderr, "time: %g\n", runtime);
  }

  output_data(rays, rt_data, data);
  free(rt_data);

  return 0;
}

void
rtrace_start()
{
  FILE *fp;

  verbose = 1;
  rtstart();
  rays_task = RAYS_TASK;
  fp = fopen("task.opt", "r");
  if (!fp) return;
  if (fscanf(fp, "%d", &rays_task) != 1 || rays_task < 1)
    rays_task = RAYS_TASK;
  if (fp) fclose(fp);
}

void
rtrace_finish()
{
  rtfinish();
  free(server_tid);
  free(server_data);
  pvm_exit();
}
