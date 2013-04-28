#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include "pvm3.h"

#define ABORT(message, code) \
do {fprintf(stderr, "error: %s [%d]\n", message, code);\
if (pvm_mytid() >= 0) pvm_exit();\
exit(code);} while (0)

#define WARNING(message) \
do {if (verbose) fprintf(stderr, "warning: %s\n", message);} while (0)

#define SLAVE "rtslave"

#define STR_SIZE 256

static char verbose = 1;
static char ifascii = 1;
static char ofascii = 1;

typedef struct _server_strcut {
  int task, free, first, size, work;
  float tran, calc;
} server_struct;

typedef struct _rt_struct {
  float point[3], dir[3], value[3];
} rt_struct;

static int
input_data(char *name, int rays, rt_struct **prt_data)
{
  rt_struct *rt_data;
  FILE *fp;
  int i;

  rt_data = (rt_struct *) malloc(rays * sizeof(rt_struct));
  if (!rt_data) return 0;
  fp = fopen(name, "r");
  if (!fp)
  {
    free(rt_data);
    return 0;
  }
  *prt_data = rt_data;
  for (i = 0; i < rays && fp; i++)
    if (ifascii)
    {
      if (fscanf(fp, "%f %f %f %f %f %f",
                 &(rt_data[i].point[0]), &(rt_data[i].point[1]),
                 &(rt_data[i].point[2]), &(rt_data[i].dir[0]),
                 &(rt_data[i].dir[1]), &(rt_data[i].dir[2])) != 6)
        break;
    } else
      if (fread(rt_data[i].point, sizeof(float), 3, fp) != 3 ||
          fread(rt_data[i].dir, sizeof(float), 3, fp) != 3)
        break;
  if (fp) fclose(fp);
  return i;
}

static int
output_data(char *name, int rays, rt_struct *rt_data)
{
  FILE *fp;
  int i;

  if (name[0] == '-') fp = stdout;
  else fp = fopen(name, "w");
  if (!fp) return 1;
  for (i = 0; i < rays; i++)
    if (ofascii)
      fprintf(fp, "%g %g %g\n",
              rt_data[i].value[0], rt_data[i].value[1], rt_data[i].value[2]);
    else
      fwrite(rt_data[i].value, sizeof(float), 3, fp);
  if (fp) fclose(fp);
  return 0;
}

static int servers, *server_tid;
static server_struct *server_data;

static float
rtmain(char *name, int pref_rays_task, int rays, rt_struct *rt_data)
{
  int server;
  int rays_task;
  int ray_current, ray_block, ray_current_rec, ray_block_rec;
  int tasks, tasks_todo, task;
  int tid, i;
  struct timeval start_time, end_time;
  struct timeval wstart_time, wend_time;
  float wait_time, prev_wait_time;
  char error_rec;

  if (pvm_mytid() < 0) ABORT("PVM not running", 101);

  for (server = 0; server < servers; server++)
  {
    server_data[server].free = server - 1;
    if (verbose)
    {
      server_data[server].work = 0;
      server_data[server].tran = 0;
      server_data[server].calc = 0;
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
    if (verbose) gettimeofday(&start_time, (struct timezone *) 0);
    if (pvm_send(server_tid[server], 1))
    {
      WARNING("cannot send task");
      if (verbose > 1)
        fprintf(stderr, "task not sent %d to server %d <%x>\n",
                task, server, server_tid[server]);
      ABORT("server not available", 105);
    }
    if (verbose)
    {
      gettimeofday(&end_time, (struct timezone *) 0);
      server_data[server].tran += end_time.tv_sec - start_time.tv_sec +
        (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    }
    if (verbose > 1)
      fprintf(stderr, "task %d sent to server %d <%x> ray %d [%d]\n",
              task, server, server_tid[server], ray_current, ray_block);

    server = server_data[server].free;
    ray_current += ray_block;
    if (ray_current + ray_block - 1 >= rays) ray_block = rays - ray_current;
  }
  if (verbose)
  {
    prev_wait_time = 0;
    wait_time = 0;
    gettimeofday(&wstart_time, (struct timezone *) 0);
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
    if (verbose)
    {
      gettimeofday(&wend_time, (struct timezone *) 0);
      wait_time += wend_time.tv_sec - wstart_time.tv_sec +
        (wend_time.tv_usec - wstart_time.tv_usec) / 1000000.0;
    }

    tasks_todo--;
    if (verbose) server_data[server].work++;
    if (verbose > 1)
    {
      fprintf(stderr, "waited %g for task %d from server %d <%x>\n",
              wait_time - prev_wait_time, server_data[server].task,
              server, tid);
      prev_wait_time = wait_time;
    }

    pvm_initsend(PvmDataRaw);
    if (pvm_send(tid, 3))
    {
      WARNING("cannot send request");
      if (verbose > 1) fprintf(stderr, "server %d <%x>\n", server, tid);
      ABORT("server not available", 106);
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
      gettimeofday(&wstart_time, (struct timezone *) 0);
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
      ABORT("server not available", 107);
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
      if (verbose) gettimeofday(&start_time, (struct timezone *) 0);
      if (pvm_send(tid, 1))
      {
        WARNING("cannot send task");
        if (verbose > 1)
          fprintf(stderr, "task not sent %d to server %d <%x>\n",
                  task, server, tid);
        ABORT("server not available", 108);
      }
      if (verbose)
      {
        gettimeofday(&end_time, (struct timezone *) 0);
        server_data[server].tran += end_time.tv_sec - start_time.tv_sec +
          (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
      }
      if (verbose > 1)
        fprintf(stderr, "task %d sent to server %d <%x> ray %d [%d]\n",
                task, server, tid, ray_current, ray_block);

      server = server_data[server].free;
      ray_current += ray_block;
      if (ray_current + ray_block - 1 >= rays) ray_block = rays - ray_current;
    }
    if (verbose) gettimeofday(&wstart_time, (struct timezone *) 0);
  }

  if (tasks_todo)
  {
    WARNING("missing tasks!");
    if (verbose > 1) fprintf(stderr, "%d task(s) not done\n", tasks_todo);
    ABORT("server problems", 109);
  }

  if (verbose)
  {
    gettimeofday(&wend_time, (struct timezone *) 0);
    wait_time += wend_time.tv_sec - wstart_time.tv_sec +
      (wend_time.tv_usec - wstart_time.tv_usec) / 1000000.0;
    return wait_time;
  }
  return 0;
}

static void
rtstart()
{
  int server;

  if (pvm_mytid() < 0) ABORT("PVM not running", 101);

  pvm_setopt(PvmRoute, PvmRouteDirect);
  pvm_config(&servers, (int *) 0, (struct pvmhostinfo **) 0);
  server_tid = (int *) malloc(servers * sizeof(int));
  if (!server_tid) ABORT("out of memory", 102);
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
  if (servers <= 0) ABORT("cannot start any server", 103);
  server_data = (server_struct *) malloc(servers * sizeof(server_struct));
  if (!server_data) ABORT("out of memory", 104);
}

static void
rtfinish()
{
  int server;
  float timecalc, timetran;

  if (pvm_mytid() < 0) ABORT("PVM not running", 101);

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

static int
options(int nargc, char *nargv[])
{
  char chr;

  while (nargc)
  {
    if (nargv[0][0] == '-' && nargv[0][1] == 'd'  && (chr = nargv[0][2]))
    {
      switch(chr)
      {
      case '0':
        verbose = 0;
        break;
      case '1':
        verbose = 1;
        break;
      case '2':
        verbose = 2;
        break;
      default:
        break;
      }
      nargc--;
      nargv++;
      continue;
    }
    if (nargv[0][0] == '-' && nargv[0][1] == 'i' && (chr = nargv[0][2]))
    {
      switch(chr)
      {
      case 'a':
        ifascii = 1;
        break;
      case 'f':
        ifascii = 0;
        break;
      default:
        break;
      }
      nargc--;
      nargv++;
      continue;
    }
    if (nargv[0][0] == '-' && nargv[0][1] == 'o' && (chr = nargv[0][2]))
    {
      switch(chr)
      {
      case 'a':
        ofascii = 1;
        break;
      case 'f':
        ofascii = 0;
        break;
      default:
        break;
      }
      nargc--;
      nargv++;
      continue;
    }
    break;
  }
  return nargc;
}

int main(int argc, char *argv[])
{
  int nargc;
  char **nargv;
  rt_struct *rt_data;
  char iname[STR_SIZE], oname[STR_SIZE], pname[STR_SIZE];
  int rays_task, rays;
  struct timeval start_time, end_time;
  float rtime, wtime;

  nargc = options(argc - 1, &argv[1]);

  if (nargc) /* command line */
  {
    nargv = &argv[argc - nargc];
    if (nargc != 5) ABORT("bad parameter(s)", 1);
    if (access(nargv[0], R_OK)) ABORT("cannot read ray file", 2);
    sprintf(oname, "%s.oct", nargv[1]);
    if (access(oname, R_OK)) ABORT("cannot read scene octree", 3);
    sprintf(oname, "%s.amb", nargv[1]);
    if (access(oname, R_OK)) ABORT("cannot read scene ambient cache", 4);
    sprintf(oname, "%s.opt", nargv[1]);
    if (access(oname, R_OK)) ABORT("cannot read scene options", 5);
    rays = atoi(nargv[2]);
    if (rays < 1) ABORT("invalid rays", 6);
    rays_task = atoi(nargv[3]);
    if (rays_task < 1 || rays_task > rays) ABORT("invalid rays/task", 7);

    rtstart();
    rays = input_data(nargv[0], rays, &rt_data);
    if (rays <= 0)
    {
      free(rt_data);
      ABORT("bad ray file (no rays)", 9);
    }
    if (verbose) gettimeofday(&start_time, (struct timezone *) 0);
    wtime = rtmain(nargv[1], rays_task, rays, rt_data);
    if (verbose)
    {
      gettimeofday(&end_time, (struct timezone *) 0);
      rtime = end_time.tv_sec - start_time.tv_sec +
              (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
      fprintf(stderr, "time: %g / waiting %g\n", rtime, wtime);
    }
    if (output_data(nargv[4], rays, rt_data))
      ABORT("cannot write rgb file", 8);
    free(rt_data);
    goto finish;
  }

  rtstart();

  while (1) /* input loop */
  {
    fprintf(stderr,
      "\n[ray file] [scene prefix] [rays] [rays/task] [rgb file]\n");
    fprintf(stderr, "quit with \"$ 0 0 0 0\"\n-> ");
    if (scanf("%s %s %d %d %s", iname, oname, &rays, &rays_task, pname) != 5)
      break;
    if (!strcmp(iname, "$") || rays < 1 || rays_task < 1) break;

    rays = input_data(iname, rays, &rt_data);
    if (rays <= 0)
    {
      free(rt_data);
      continue;
    }
    if (verbose) gettimeofday(&start_time, (struct timezone *) 0);
    wtime = rtmain(oname, rays_task, rays, rt_data);
    if (verbose)
    {
      gettimeofday(&end_time, (struct timezone *) 0);
      rtime = end_time.tv_sec - start_time.tv_sec +
              (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
      fprintf(stderr, "time: %g / waiting %g\n", rtime, wtime);
    }
    if (output_data(pname, rays, rt_data)) WARNING("cannot write rgb file");
    free(rt_data);
  }

finish:
  rtfinish();
  free(server_tid);
  free(server_data);
  pvm_exit();
  exit(0);
  return 0;
}
