#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "pvm3.h"
#include <sys/time.h>

#define TEMP1 "/tmp/rtp.in"
#define TEMP2 "/tmp/rtp.ou"
#define PNAME "/tmp/rtp.%s.pf"

#ifndef F_ASCII
#define LAUNCH_ARG \
"rtrace -P %s -h -fff -ov @%s.opt %s.oct <%s >%s"       
#else
#define LAUNCH_ARG \
"rtrace -P %s -h -ov @%s.opt %s.oct <%s >%s"       
#endif

#define RUN_ARG \
"rtrace -P %s <%s >%s"

#define FNULL "/dev/null"

#define STR_SIZE 256
#define PFIL_SIZE 256
#define COMM_SIZE 1024

static char pfilename[PFIL_SIZE];

static void
launch_rtrace(char *name)
{
  char command[COMM_SIZE], *basename;

  basename = strrchr(name, '/');
  if (basename) sprintf(pfilename, PNAME, &basename[1]);
  else sprintf(pfilename, PNAME, name);
  if (access(pfilename, R_OK) != 0)
  {
    sprintf(command, LAUNCH_ARG, pfilename, name, name, FNULL, FNULL);
    system(command);
  }
}

static int
run_rtrace(char *iname, char *oname)
{
  char command[COMM_SIZE];

  if (access(pfilename, R_OK) == 0)
  {
    sprintf(command, RUN_ARG, pfilename, iname, oname);
    system(command);
    return 0;
  }
  return 1;
}

static float timecalc = 0, timetran = 0;
static struct timeval start_time, end_time;

static void
run_task(int ray, int rays, int master_tid)
{
  char error = 0;
  float data[6], *value;
  FILE *fp;
  int i;

  value = (float *) malloc(rays * 3 * sizeof(float));
  if (!value) error = 1;

  if (!error)
  {
#ifndef F_ASCII
    fp = fopen(TEMP1, "wb");
#else
    fp = fopen(TEMP1, "w");
#endif
    if (!fp) error = 2;
  }

  for (i = 0; i < rays && !error; i++)
  {
    pvm_upkfloat(data, 6, 1);
#ifndef F_ASCII
    fwrite(data, sizeof(float), 6, fp);
#else
    fprintf(fp, "%10f %10f %10f %10f %10f %10f\n",
            data[0], data[1], data[2], data[3], data[4], data[5]);
#endif
  }

  if (!error)
  {
    if (fp) fclose(fp);
    gettimeofday(&start_time, (struct timezone *) 0);
    if (run_rtrace(TEMP1, TEMP2)) error = 3;
    gettimeofday(&end_time, (struct timezone *) 0);
    timecalc += end_time.tv_sec - start_time.tv_sec +
      (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
  }

  if (!error)
  {
#ifndef F_ASCII
    fp = fopen(TEMP2, "rb");
#else
    fp = fopen(TEMP2, "r");
#endif
    if (!fp) error = 4;
    for (i = 0; i < rays && !error; i++)
    {
      int j = i * 3;
#ifndef F_ASCII
      if (fread(&value[j], sizeof(float), 3, fp) != 3)
#else
      if (fscanf(fp, "%f %f %f", &value[j], &value[j + 1], &value[j + 2]) != 3)
#endif
        error = 4;
    }
    if (fp) fclose(fp);
  }

  pvm_initsend(PvmDataRaw);
  pvm_send(master_tid, 2);
  pvm_recv(master_tid, 3);

  pvm_initsend(PvmDataRaw);
  pvm_pkint(&ray, 1, 1);
  pvm_pkint(&rays, 1, 1);
  pvm_pkbyte(&error, 1, 1);
  if (!error) pvm_pkfloat(value, rays * 3, 1);
  if (value) free(value);
}

int
main(int argc, char *argv[])
{
  int tid, master_tid, tag;
  int first, size;
  char name[STR_SIZE];

  tid = pvm_mytid();
  if (tid < 0) exit(2);
  master_tid = pvm_parent();
  if (master_tid < 0)
  {
    pvm_exit();
    exit(3);
  }

  /* wait */
  while (pvm_recv(master_tid, -1) > 0)
  {
    pvm_bufinfo(pvm_getrbuf(), (int *) 0, &tag, (int *) 0);
    if (tag != 1) break;

    pvm_upkint(&first, 1, 1);
    pvm_upkint(&size, 1, 1);
    pvm_upkstr(name);

    launch_rtrace(name);
    run_task(first, size, master_tid);

    gettimeofday(&start_time, (struct timezone *) 0);
    pvm_send(master_tid, 4);
    gettimeofday(&end_time, (struct timezone *) 0);
    timetran += end_time.tv_sec - start_time.tv_sec +
      (end_time.tv_usec - start_time.tv_usec) / 1000000.0;
    pvm_recv(master_tid, 5);
  }

  if (tag == 101)
  {
    pvm_initsend(PvmDataRaw);
    pvm_pkfloat(&timecalc, 1, 1);
    pvm_pkfloat(&timetran, 1, 1);
    pvm_send(master_tid, 102);
  }

  pvm_exit();
  exit(0);
  return 0;
}
