#include <stdlib.h>
#include <stdio.h>
#ifndef WIN32
#include <unistd.h>
#endif
#include <string.h>
#include <math.h>
#ifdef LOG
#include <sys/times.h>
#endif

#ifndef M_PI
#define M_PI 3.14159267
#endif
#ifndef R_OK
#define R_OK 0
#endif

#define TOL 0.000001

#include "mesh.h"
#include "data.h"

#ifdef WIN32
#define TEMP1 "\\tmp\\rt.in"
#define TEMP2 "\\tmp\\rt.ou"
#ifdef F_ASCII
#define ARG2 "rtrace -h -ov @%s.opt %s.oct <%s >%s"
#else
#define ARG2 "rtrace -h -fff -ov @%s.opt %s.oct <%s >%s"
#endif
#else
#define TEMP1 "/tmp/rt.in"
#define TEMP2 "/tmp/rt.ou"
#define PNAME "/tmp/rt.%s.pf"
#define ARG1 "rtrace -P %s <%s >%s"
#ifdef F_ASCII
#define ARG2 "rtrace -P %s -h -ov @%s.opt %s.oct <%s >%s"
#else
#define ARG2 "rtrace -P %s -h -fff -ov @%s.opt %s.oct <%s >%s"
#endif
#endif

/***** start of config *****/
#define DIST_THRES 0.04
#define POINT_MAX 512
#define NPOINT 64
#define NDIVS 16
#define DRATIO 15
#define MTHRES 0
#define UNUSED_MAX 400
/***** end of config *****/

#define OFFSET 0.001

#define STR_SIZE 256

typedef struct _data_struct {
  float v,x,y,z,d;
} data_struct;

static data_struct data1[MESH_SIZE+1],data2[MESH_SIZE+1];

#define CODE_UNKNOWN -888888
#define CODE_IGNORED -999999

#define EQ(A,B) fabs((A)-(B))<1e-6

typedef struct _dist_struct {
  char name[32];
  short int u;
  float x,y,z,vx,vy,vz,a,v;
  float l[MESH_SIZE];
  float dx[MESH_SIZE];
  float dy[MESH_SIZE];
  float dz[MESH_SIZE];
} dist_struct;

static dist_struct point[POINT_MAX];
static int point_ptr=-1;

static float dist_thres=DIST_THRES;
static char dist_thres_init=1;

static float
find_val(float P1,float P2,float P3,float P4,data_struct *P5,
         char *P6,float P7,float P8,float P9)
{
  float x=P1;
  float y=P2;
  float z=P3;
  float d=0;
  float l=sqrt(x*x+y*y+z*z);
  float sum_value=0,sum_weight=0;
  int i;

  if (l>TOL)
  {
    x=x/l;
    y=y/l;
    z=z/l;
  }

  if (P4>0) d=cos(P4/180*M_PI);

  for (i=0; i<MESH_SIZE; i++)
  {
    float dt=1;

    if (EQ(P5[i].v,CODE_UNKNOWN) || EQ(P5[i].v,CODE_IGNORED)) continue;
    if (P4>0 || P6[0]) dt=x*P5[i].x+y*P5[i].y+z*P5[i].z;
    if (P4<=0 || dt>d)
    {
      float v=P5[i].v;
      if (v<0) v=-v;
      if (P6[0])
      {
        float k[MAXDDIM];
        data_array *datap=getdata(P6);
        if (!datap) return 0;
        k[0]=acos(dt)*180/M_PI;
        if (datap->nd>1)
        {
          float x1=P7;
          float y1=P8;
          float z1=P9;
          float l1=sqrt(x1*x1+y1*y1+z1*z1);
          if (l1>TOL)
          {
            x1=x1/l1;
            y1=y1/l1;
            z1=z1/l1;
            dt=x1*P5[i].x+y1*P5[i].y+z1*P5[i].z;
            k[1]=acos(dt)*180/M_PI;
          } else
            k[1]=0;
        }
        dt=datavalue(datap,k);
      }
      if(dt>0)
      {
        sum_value+=v*dt;
        sum_weight+=dt;
      }
    }
  }

  if (sum_weight>0) return sum_value/sum_weight;
  return 0;
}

#define PRED(X) ((X)+POINT_MAX-1)%POINT_MAX
#define SUCC(X) ((X)+1)%POINT_MAX

static int
exist_point(char *P1,float P2,float P3,float P4,
            float P5,float P6,float P7,float P8)
{
  int i;

  for (i=PRED(point_ptr); i!=point_ptr; i=PRED(i))
    if (point[i].v>=0 && strcmp(P1,point[i].name)==0 &&
        EQ(P2,point[i].x) && EQ(P3,point[i].y) && EQ(P4,point[i].z) &&
        EQ(P5,point[i].vx) && EQ(P6,point[i].vy) && EQ(P7,point[i].vz) &&
        EQ(P8,point[i].a))
    {
      point[i].u=0;
      return i;
    }
  return -1;
}

static char vnn[NDIVS*2][NDIVS*4];

typedef struct _query_struct {
  int i;
  float l;
} query_struct;

static int
list_cmp(const void *P1,const void *P2)
{
  query_struct *a=(query_struct *)P1,*b=(query_struct *)P2;
  if (a->l>b->l) return 1;
  if (a->l<b->l) return -1;
  return 0;
}

static void
query_point(float P1,float P2,float P3,float P4,float P5,float P6,
            float P7,int *P8,int *P9)
{
  query_struct list[POINT_MAX];
  int list_index=0,list_end;
  float px=P1;
  float py=P2;
  float pz=P3;
  float pdx=P4;
  float pdy=P5;
  float pdz=P6;
  float cosa=cos(P7/180*M_PI);
  float nz=NDIVS-TOL;
  float na=2*nz/M_PI;
  int i,j;

  for (i=0; i<NDIVS*2; i++)
    for (j=0; j<NDIVS*4; j++)
      vnn[i][j]=0;

  for (i=PRED(point_ptr); i!=point_ptr; i=PRED(i))
  {
    float dx,dy,dz,x,y,z,l,k;
    int n1,n2;
    char u;

    if (point[i].u>UNUSED_MAX || point[i].v<0) continue;
    u=point[i].u;
    point[i].u=u+1;
    dx=point[i].vx;
    dy=point[i].vy;
    dz=point[i].vz;
    if (dx*pdx+dy*pdy+dz*pdz<cosa) continue;
    x=point[i].x-px;
    y=point[i].y-py;
    z=point[i].z-pz;
    l=sqrt(x*x+y*y+z*z);
    if (l<TOL) continue;
    x=x/l;
    y=y/l;
    z=z/l;
    n1=(int) (nz*(z+1));
    k=atan2(y,x);
    if (y<0) k=2*M_PI+k;
    n2=(int) (na*k);
    if (vnn[n1][n2]) continue;
    vnn[n1][n2]=1;
    if (l/dist_thres<=DRATIO)
    {
      list[list_index].i=i;
      list[list_index++].l=l;
      point[i].u=u;
    }
  }
  if (list_index==0)
  {
#ifdef LOG
    printf("query: 0 %g,%g,%g\n",px,py,pz);
#endif
    *P8=0;
    return;
  }
  if (list_index>1)
    qsort(list,list_index,sizeof(query_struct),list_cmp);
  if (list_index>NPOINT) list_end=NPOINT;
  else list_end=list_index;
  *P8=list_end;
  for (i=0; i<list_end; i++)
  {
    j=list[i].i;
    P9[i]=j;
    point[j].u=0;
  }
  for (i=list_end; i<list_index; i++)
  {
    j=list[i].i;
    point[j].u=point[j].u+1;
  }
#ifdef LOG
  printf("query: %d %g,%g,%g\n",list_end,px,py,pz);
  for (i=0; i<list_end; i++)
  {
    j=list[i].i;
    printf(" %d %g %g,%g,%g\n",j,list[i].l,
            point[j].x,point[j].y,point[j].z);
  }
#endif
}

static void
init_point()
{
  int i,j;

  for (i=0; i<POINT_MAX; i++)
  {
    point[i].v=-1;
    point[i].u=UNUSED_MAX;
    for (j=0; j<MESH_SIZE; j++)
      point[i].l[j]=-1;
  }
  point_ptr=0;
}

static void
init_dirs(float P1,float P2,float P3,float P4,data_struct *P5)
{
  float vx=-P1;
  float vy=-P2;
  float vz=-P3;
  float d=cos(P4/180*M_PI)-TOL;
  float l=sqrt(vx*vx+vy*vy+vz*vz);
  char ck=0;
  int i;

  if (l>TOL)
  {
    ck=1;
    vx=vx/l;
    vy=vy/l;
    vz=vz/l;
  }

  for (i=0; i<MESH_SIZE; i++)
  {
    float X=mesh_point[i].x;
    float Y=mesh_point[i].y;
    float Z=mesh_point[i].z;

    if (!ck || vx*X+vy*Y+vz*Z>d)
    {
      P5[i].v=CODE_UNKNOWN;
      P5[i].x=-X;
      P5[i].y=-Y;
      P5[i].z=-Z;
      P5[i].d=-1;
      continue;
    }
    P5[i].v=CODE_IGNORED;
    P5[i].x=-X;
    P5[i].y=-Y;
    P5[i].z=-Z;
    P5[i].d=-1;
  }
}

static void
test_dirs(float P1,float P2,float P3,float P4,float P5,float P6,float P7,
          float P8,int P9,data_struct *P10)
{
  float x=P1;
  float y=P2;
  float z=P3;
  float vx=P4;
  float vy=P5;
  float vz=P6;
  float d=cos(P7/180*M_PI)-TOL;
  float pdm=P8*P8;
  float dx=point[P9].x-x;
  float dy=point[P9].y-y;
  float dz=point[P9].z-z;
  float l=sqrt(vx*vx+vy*vy+vz*vz);
  char ck=0;
  int i;

  if (l>TOL)
  {
    ck=1;
    vx=vx/l;
    vy=vy/l;
    vz=vz/l;
  }

  for (i=0; i<MESH_SIZE; i++)
  {
    float pdx=point[P9].dx[i];
    float pdy=point[P9].dy[i];
    float pdz=point[P9].dz[i];
    if (!ck || vx*pdx+vy*pdy+vz*pdz>d)
    {
      float k=-(pdx*dx+pdy*dy+pdz*dz);
      float kx=k*pdx+dx;
      float ky=k*pdy+dy;
      float kz=k*pdz+dz;
      float kdm=kx*kx+ky*ky+kz*kz;
      if (kdm<pdm)
      {
        P10[i].v=point[P9].l[i];
        P10[i].x=pdx;
        P10[i].y=pdy;
        P10[i].z=pdz;
        P10[i].d=kdm;
      }
      else
      {
        P10[i].v=CODE_UNKNOWN;
        P10[i].x=pdx;
        P10[i].y=pdy;
        P10[i].z=pdz;
        P10[i].d=-1;
      }
      continue;
    }
    P10[i].v=CODE_IGNORED;
    P10[i].x=pdx;
    P10[i].y=pdy;
    P10[i].z=pdz;
    P10[i].d=-1;
  }
}

static void
join_dirs(data_struct *P1,data_struct *P2)
{
  int i;

  for (i=0; i<MESH_SIZE; i++)
  {
    if (P1[i].v>=0)
    {
      if (P2[i].v<0 || P1[i].d<P2[i].d)
      {
        P2[i].v=P1[i].v;
        P2[i].x=P1[i].x;
        P2[i].y=P1[i].y;
        P2[i].z=P1[i].z;
        P2[i].d=P1[i].d;
        continue;
      }
    }
  }
}

static int
count_dirs(float P1,data_struct *P2)
{
  int i,n=0;

  for (i=0; i<MESH_SIZE; i++)
    if (EQ(P1,P2[i].v)) n++;
  return n;
}

static int
get_dirs(float P1,data_struct *P2,data_struct *P3)
{
  int i,n=0;

  for (i=0; i<MESH_SIZE; i++)
  {
    if (EQ(P1,P2[i].v))
    {
      P3[n].v=P1;
      P3[n].x=P2[i].x;
      P3[n].y=P2[i].y;
      P3[n].z=P2[i].z;
      P3[n].d=P2[i].d;
      n++;
    }
  }
  P3[n].v=CODE_IGNORED;
  return n;
}

static int
find_dirs(float P1,float P2,float P3,data_struct *P4,char *P5)
{
  float x=P1;
  float y=P2;
  float z=P3;
  FILE *ou=fopen(P5,"w");
  int i,n=0;

  for (i=0; i<MESH_SIZE && ou; i++)
  {
    float dx,dy,dz;
    float data[6];

    if (EQ(P4[i].v,CODE_IGNORED)) break;
    dx=OFFSET*P4[i].x;
    dy=OFFSET*P4[i].y;
    dz=OFFSET*P4[i].z;
    data[0]=x-dx;
    data[1]=y-dy;
    data[2]=z-dz;
    data[3]=dx;
    data[4]=dy;
    data[5]=dz;
#ifdef F_ASCII
    fprintf(ou,"%10f %10f %10f %10f %10f %10f\n",
      data[0],data[1],data[2],data[3],data[4],data[5]);
#else
    fwrite(data,sizeof(float),6,ou);
#endif
    n++;
  }
  if (ou) fclose(ou);
  return n;
}

static void
copy_data(char *P1,float *P2,int P3)
{
  int i;
  FILE *in=fopen(P1,"r");

  for (i=0; i<P3 && in; i++)
  {
    float data[3];

#ifdef F_ASCII
    if (fscanf(in,"%f %f %f",&data[0],&data[1],&data[2])!=3) break;
#else
    if (fread(data,sizeof(float),3,in)!=3) break;
#endif
    P2[i]=0.265*data[0]+0.670*data[1]+0.065*data[2];
  }
  if (in) fclose(in);
}

static void
out_dirs(float *P1,data_struct *P2,data_struct *P3)
{
  int i,n=0;

  for (i=0; i<MESH_SIZE; i++)
  {
    if (EQ(P2[i].v,CODE_UNKNOWN))
    {
      P3[i].v=P1[n++];
      P3[i].x=P2[i].x;
      P3[i].y=P2[i].y;
      P3[i].z=P2[i].z;
      P3[i].d=P2[i].d;
      continue;
    }
    P3[i].v=P2[i].v;
    P3[i].x=P2[i].x;
    P3[i].y=P2[i].y;
    P3[i].z=P2[i].z;
    P3[i].d=P2[i].d;
  }
}

static void
cache_save(float *P1,data_struct *P2,char *P3,float P4,float P5,float P6,
           float P7,float P8,float P9,float P10,float P11)
{
  int i,n=0;

  for (i=0; i<MESH_SIZE; i++)
  {
    float v;

    if (EQ(P2[i].v,CODE_UNKNOWN))
    {
      point[point_ptr].l[i]=P1[n++];
      point[point_ptr].dx[i]=P2[i].x;
      point[point_ptr].dy[i]=P2[i].y;
      point[point_ptr].dz[i]=P2[i].z;
      continue;
    }
    v=P2[i].v;
    if (v>=0)
    {
      point[point_ptr].l[i]=-v;
      point[point_ptr].dx[i]=P2[i].x;
      point[point_ptr].dy[i]=P2[i].y;
      point[point_ptr].dz[i]=P2[i].z;
      continue;
    }
    point[point_ptr].l[i]=v;
    point[point_ptr].dx[i]=P2[i].x;
    point[point_ptr].dy[i]=P2[i].y;
    point[point_ptr].dz[i]=P2[i].z;
  }
  strcpy(point[point_ptr].name,P3);
  point[point_ptr].x=P4;
  point[point_ptr].y=P5;
  point[point_ptr].z=P6;
  point[point_ptr].vx=P7;
  point[point_ptr].vy=P8;
  point[point_ptr].vz=P9;
  point[point_ptr].a=P10;
  point[point_ptr].v=P11;
  point_ptr=SUCC(point_ptr);
}

static void
read_dist()
{
  FILE *in=fopen("dist.opt","r");
  dist_thres_init=0;
  if (!in) return;
  if (fscanf(in,"%f",&dist_thres)!=1 || dist_thres<0 || dist_thres>100)
  {
    if (in) fclose(in);
    dist_thres=DIST_THRES;
    return;
  }
  if (in) fclose(in);
}

static char pfil[STR_SIZE];

static void
gen_command(char *P1,char *P2)
{
#ifdef WIN32
  sprintf(P2,ARG2,P1,P1,TEMP1,TEMP2);
#else
  sprintf(pfil,PNAME,P1);
  if (access(pfil,R_OK)==0)
    sprintf(P2,ARG1,pfil,TEMP1,TEMP2);
  else
    sprintf(P2,ARG2,pfil,P1,P1,TEMP1,TEMP2);
#endif
}

float
radcalcdir(char *P1,float P2,float P3,float P4,
           float P5,float P6,float P7,float P8,
           char *P9,float P10,float P11,float P12)
{
  int list_point[NPOINT],npoint=0;
  char command[4*STR_SIZE];
  int i;
  float grey[MESH_SIZE];
  float val;
#ifdef LOG
  clock_t t0;
  float dt;
#endif

  if (dist_thres_init) read_dist();

#ifdef LOG
  t0=times(0);
#endif
  if (point_ptr >= 0)
  {
    int found=exist_point(P1,P2,P3,P4,P5,P6,P7,P8);
    if (found>=0)
    {
#ifdef LOG
      dt=times(0)-t0;
      if (dt==0) dt=1;
      dt=dt/CLOCKS_PER_SEC;
      printf("hit0: %s %g\n",P1,dt);
#endif
      return point[found].v;
    }
  }

  if (point_ptr<0)
    init_point();
  else
    query_point(P2,P3,P4,P5,P6,P7,P8,&npoint,list_point);

  init_dirs(P5,P6,P7,P8,data2);

  for (i=0; i<npoint; i++)
  {
    int m;

    test_dirs(P2,P3,P4,P5,P6,P7,P8,dist_thres,list_point[i],data1);
    join_dirs(data1,data2);
    m=count_dirs(CODE_UNKNOWN,data2);
    if (m<MTHRES) break;
  }

  if (get_dirs(CODE_UNKNOWN,data2,data1)==0)
  {
#ifdef LOG
    dt=times(0)-t0;
    if (dt==0) dt=1;
    dt=dt/CLOCKS_PER_SEC;
    printf("hit1: %s %g\n",P1,dt);
#endif
    return find_val(P5,P6,P7,P8,data2,P9,P10,P11,P12);
  }

  i=find_dirs(P2,P3,P4,data1,TEMP1);
#ifdef LOG
  dt=times(0)-t0;
  if (dt==0) dt=1;
  dt=dt/CLOCKS_PER_SEC;
  printf("setup: %s %g\n",P1,dt);
#endif
  gen_command(P1,command);
#ifdef LOG
  t0=times(0);
#endif
  system(command);
#ifdef LOG
  dt=times(0)-t0;
  if (dt==0) dt=1;
  dt=dt/CLOCKS_PER_SEC;
  printf("rtrace: %s %g %d\n",P1,dt,i);
#endif

#ifdef LOG
  t0=times(0);
#endif
  copy_data(TEMP2,grey,i);
  out_dirs(grey,data2,data1);
  val=find_val(P5,P6,P7,P8,data1,P9,P10,P11,P12);
  cache_save(grey,data2,P1,P2,P3,P4,P5,P6,P7,P8,val);
#ifdef LOG
  dt=times(0)-t0;
  if (dt==0) dt=1;
  dt=dt/CLOCKS_PER_SEC;
  printf("calc: %s %g\n",P1,dt);
#endif
  return val;
}

#ifdef TESTDIR
int
main(int argc,char *argv[])
{
  char P1[32];
  float P2,P3,P4,P5,P6,P7,P8;

  if (argc==8)
  {
    P2=atof(argv[2]);
    P3=atof(argv[3]);
    P4=atof(argv[4]);
    P5=atof(argv[5]);
    P6=atof(argv[6]);
    P7=atof(argv[7]);
    P8=atof(argv[8]);
    fprintf(stderr,"%s %g %g %g %g %g %g %g: %g\n",
      argv[1],P2,P3,P4,P5,P6,P7,P8,radcalcdir(argv[1],P2,P3,P4,P5,P6,P7,P8));
    return 0;
  }
  do {
    if (scanf("%s %f %f %f %f %f %f %f",P1,&P2,&P3,&P4,&P5,&P6,&P7,&P8)!=8)
      break;
    fprintf(stderr,"%s %g %g %g %g %g %g %g: %g\n",
      P1,P2,P3,P4,P5,P6,P7,P8,radcalcdir(P1,P2,P3,P4,P5,P6,P7,P8));
  } while (strcmp(P1,"-"));
  return 0;
}
#endif
