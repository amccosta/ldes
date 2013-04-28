#include <stdio.h>
#include <stdlib.h>

void
makesph(int a,int b,float x,float y,float z,float r)
{
  FILE *fou;
  char name[64];

  sprintf(name,"s_%d_%d.rad",a,b);
  fou=fopen(name,"w");
  if (!fou) return;
  fprintf(fou,"void plastic m_%d_%d\n",a,b);
  fprintf(fou,"0\n0\n5 0.5 0.5 0.5 0.07 0\n\n");
  fprintf(fou,"m_%d_%d sphere s_%d_%d\n",a,b,a,b);
  fprintf(fou,"0\n0\n4 %g %g %g %g\n",x,y,z,r);
  fclose(fou);
  printf("%s\n",name);
}

main(int argc,char **argv)
{
  float sx,bx,sy,by,z,r;
  int nx,ny,i,j;
  float dx,dy;

  if (argc<=8) exit(1);
  sx=atof(argv[1]);
  bx=atof(argv[2]);
  sy=atof(argv[3]);
  by=atof(argv[4]);
  z=atof(argv[5]);
  nx=atoi(argv[6]);
  ny=atoi(argv[7]);
  r=atof(argv[8]);

  dx=(bx-sx)/(nx-1);
  dy=(by-sy)/(ny-1);
  for (i=1; i<=nx; i++)
    for (j=1; j<=ny; j++)
    {
      float x,y;
      x=sx+i*dx;
      y=sy+j*dy;
      makesph(i,j,x,y,z,r);
    }
}
