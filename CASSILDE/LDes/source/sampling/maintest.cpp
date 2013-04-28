#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>

#include "ldradparser.h"
#include "qhsarea.h"

#define MAXOBJ 3500

void main()
{
  FILE *fp;
  char str[]="mat", str2[]="sphere", strm[]="void", strp[]="plastic", nam[256];
  int i, n = 100;

  fprintf(stderr, "Quantos objectos a criar?\n");
  scanf("%d", &n);
  srand((unsigned)time(NULL));

  for (i = 0; i < n; i++)
  { 
    sprintf(nam, "obj/sp%d.rad", i);
    fp = fopen(nam, "wt");
    if(fp == NULL)
    {
      fprintf(stderr, "Objecto %s nao foi criado\n", nam);
      exit(1);
    }

    fprintf(fp, "%s %s %d\n", strm, strp, i);
    fprintf(fp, "0\n");
    fprintf(fp, "0\n");
    fprintf(fp, "5 ");
    fprintf(fp, "1 1 1 %g %g", (.965*(rand()/(float)RAND_MAX))+.035,
            (.1*(rand()/(float)RAND_MAX)));

    fprintf(fp, "\n\n%d %s %d\n", i, str2, i);
    fprintf(fp, "0\n");
    fprintf(fp, "0\n");
    fprintf(fp, "4");
    fprintf(fp, " %g %g %g ", (2*(rand()/(float)RAND_MAX))-1,
            (2*(rand()/(float)RAND_MAX))-1, (2*(rand()/(float)RAND_MAX))-1);
    //fprintf(fp, " %g\n\n", (1.0f/(2.0f*(n+1.0f))));
    fprintf(fp, " %g\n\n", 0.05);

    fclose(fp);
  }

  ldMatList matlist;
  ldObjList objlist;

  for(i = 0; i < n; i++)
  {
    sprintf(nam, "obj/sp%d.rad", i);
    ParseRADFile(nam, &matlist, &objlist);
  }

  ldObjList niceObjList(false);
  ldObject *obj = objlist.GetFirstNode();

  while(obj != NULL)
  {
    if(obj->IsNice()) niceObjList.AddNode(obj);
    obj = objlist.GetNextNode();
  }

  float *dirs = new float[MAXOBJ * 3];
  n = FindNewDirs(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, MAXOBJ, &objlist, dirs);

  fprintf(stderr, "Dirs: %d\n", n);

  if (n >= 8)
  {
    fp = fopen("out.txt", "wt");
    fprintf(fp, "3\n%d\n", n);
    for(i = 0; i < n; i++)
      fprintf(fp, "%g %g %g\n", dirs[i*3], dirs[i*3+1], dirs[i*3+2]);
    fclose(fp);

    float *weights = new float[MAXOBJ];

    fprintf(stderr, "Code: %d\n", GetPointAreas(n, dirs, weights));

    fp = fopen("outw.txt", "wt");
    fprintf(fp, "%d\n", n);
    for(i = 0; i < n; i++)
      fprintf(fp, "%g\n", weights[i]);
    fclose(fp);

    delete[] weights;
  }

  delete[] dirs;
}
