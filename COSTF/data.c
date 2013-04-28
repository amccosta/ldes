/*
 *  data.c - routines dealing with interpolated data.
 */

#include <stdio.h>
#include <string.h>
#include "data.h"

#ifndef TABSIZ
#define TABSIZ 97 /* table size (prime) */
#endif

#define hash(s) (shash(s)%TABSIZ)

static data_array *dtab[TABSIZ];

/* hash a nul-terminated string */
static unsigned long
shash(char *s)
{
  static unsigned char shuffle[256] = {
    0, 157, 58, 215, 116, 17, 174, 75, 232, 133, 34,
    191, 92, 249, 150, 51, 208, 109, 10, 167, 68, 225,
    126, 27, 184, 85, 242, 143, 44, 201, 102, 3, 160,
    61, 218, 119, 20, 177, 78, 235, 136, 37, 194, 95,
    252, 153, 54, 211, 112, 13, 170, 71, 228, 129, 30,
    187, 88, 245, 146, 47, 204, 105, 6, 163, 64, 221,
    122, 23, 180, 81, 238, 139, 40, 197, 98, 255, 156,
    57, 214, 115, 16, 173, 74, 231, 132, 33, 190, 91,
    248, 149, 50, 207, 108, 9, 166, 67, 224, 125, 26,
    183, 84, 241, 142, 43, 200, 101, 2, 159, 60, 217,
    118, 19, 176, 77, 234, 135, 36, 193, 94, 251, 152,
    53, 210, 111, 12, 169, 70, 227, 128, 29, 186, 87,
    244, 145, 46, 203, 104, 5, 162, 63, 220, 121, 22,
    179, 80, 237, 138, 39, 196, 97, 254, 155, 56, 213,
    114, 15, 172, 73, 230, 131, 32, 189, 90, 247, 148,
    49, 206, 107, 8, 165, 66, 223, 124, 25, 182, 83,
    240, 141, 42, 199, 100, 1, 158, 59, 216, 117, 18,
    175, 76, 233, 134, 35, 192, 93, 250, 151, 52, 209,
    110, 11, 168, 69, 226, 127, 28, 185, 86, 243, 144,
    45, 202, 103, 4, 161, 62, 219, 120, 21, 178, 79,
    236, 137, 38, 195, 96, 253, 154, 55, 212, 113, 14,
    171, 72, 229, 130, 31, 188, 89, 246, 147, 48, 205,
    106, 7, 164, 65, 222, 123, 24, 181, 82, 239, 140,
    41, 198, 99
  };
  int i = 0;
  unsigned long h = 0;
  unsigned char *t = (unsigned char *)s;

  while (*t) h ^= (unsigned long)shuffle[*t++] << ((i+=11) & 0xf);
  return h;
}

/* get data array name */
data_array *
getdata(char *dname)
{
  FILE *fp;
  int asize;
  int i, j;
  data_array *dp;
  float dmax;

  /* look for array in list */
  for (dp = dtab[hash(dname)]; dp != NULL; dp = dp->next)
    if (!strcmp(dname, dp->name)) return(dp); /* found! */
  /*
   *  The file has the following format:
   *
   *    N
   *    beg0  end0  n0
   *    beg1  end1  n1
   *    . . .
   *    begN  endN  nN
   *    data, later dimensions changing faster
   *    . . .
   *
   *  For irregularly spaced points, the following can be
   *  substituted for begi endi ni:
   *
   *    0 0 ni p0i p1i .. pni
   */

  if ((fp = fopen(dname, "r")) == NULL) goto error;
  /* get dimensions */
  if (fscanf(fp, "%d", &asize) < 1) goto error;
  if (asize <= 0 | asize > MAXDDIM) goto error;
  if ((dp = (data_array *)malloc(sizeof(data_array))) == NULL) goto error;
  strncpy(dp->name, dname, NAMESIZE);
  dp->nd = asize;
  asize = 1;
  for (i = 0; i < dp->nd; i++) {
    if (fscanf(fp, "%f", &dp->dim[i].org) < 1) goto error;
    if (fscanf(fp, "%f", &dp->dim[i].siz) < 1) goto error;
    if (fscanf(fp, "%d", &dp->dim[i].ne) < 1) goto error;
    if (dp->dim[i].ne < 2) goto error;
    asize *= dp->dim[i].ne;
    if ((dp->dim[i].siz -= dp->dim[i].org) == 0) {
      dp->dim[i].p = (float *)malloc(dp->dim[i].ne*sizeof(float));
      if (dp->dim[i].p == NULL) goto error;
      for (j = 0; j < dp->dim[i].ne; j++)
        if (fscanf(fp, "%f", &dp->dim[i].p[j]) < 1) goto error;
      for (j = 1; j < dp->dim[i].ne-1; j++)
        if ((dp->dim[i].p[j-1] < dp->dim[i].p[j]) !=
          (dp->dim[i].p[j] < dp->dim[i].p[j+1]))
          goto error;
      dp->dim[i].org = dp->dim[i].p[0];
      dp->dim[i].siz = dp->dim[i].p[dp->dim[i].ne-1] - dp->dim[i].p[0];
    } else
    dp->dim[i].p = NULL;
  }
  if ((dp->d = (float *)malloc(asize*sizeof(float))) == NULL) goto error;
  for (i = 0; i < asize; i++)
    if (fscanf(fp, "%f", &dp->d[i]) < 1) goto error;
  fclose(fp);
  /* normalize data to [0-1] */
  dmax = dp->d[0];
  for (i = 1; i < asize; i++) if (dp->d[i] > dmax) dmax = dp->d[i];
  if (dmax < 0.000001) goto error;
  for (i = 0; i < asize; i++) dp->d[i] /= dmax;
  i = hash(dname);
  dp->next = dtab[i];
  return (dtab[i] = dp);

error:
  return 0;
}

/* interpolate data value at a point */
float
datavalue(data_array *dp, float *pt)
{
  data_array sd;
  int asize;
  int lower, upper;
  int i;
  double x, y0, y1;

  /* set up dimensions for recursion */
  if (dp->nd > 1) {
    strcpy(sd.name, dp->name);
    sd.nd = dp->nd - 1;
    asize = 1;
    for (i = 0; i < sd.nd; i++) {
      sd.dim[i].org = dp->dim[i+1].org;
      sd.dim[i].siz = dp->dim[i+1].siz;
      sd.dim[i].p = dp->dim[i+1].p;
      asize *= sd.dim[i].ne = dp->dim[i+1].ne;
    }
  }

  /* get independent variable */
  if (dp->dim[0].p == NULL) { /* evenly spaced points */
    x = (pt[0] - dp->dim[0].org)/dp->dim[0].siz;
    x *= (double)(dp->dim[0].ne - 1);
    i = x;
    if (i < 0) i = 0;
    else
      if (i > dp->dim[0].ne - 2) i = dp->dim[0].ne - 2;
  } else {  /* unevenly spaced points */
    if (dp->dim[0].siz > 0.0) {
      lower = 0;
      upper = dp->dim[0].ne;
    } else {
      lower = dp->dim[0].ne;
      upper = 0;
    }
    do {
      i = (lower + upper) >> 1;
      if (pt[0] >= dp->dim[0].p[i]) lower = i;
      else upper = i;
    } while (i != (lower + upper) >> 1);
    if (i > dp->dim[0].ne - 2) i = dp->dim[0].ne - 2;
    x = i + (pt[0] - dp->dim[0].p[i]) / (dp->dim[0].p[i+1] - dp->dim[0].p[i]);
  }

  /* get dependent variable */
  if (dp->nd > 1) {
    sd.d = dp->d + i*asize;
    y0 = datavalue(&sd, pt+1);
    sd.d = dp->d + (i+1)*asize;
    y1 = datavalue(&sd, pt+1);
  } else {
    y0 = dp->d[i];
    y1 = dp->d[i+1];
  }

  /* extrapolate as far as one division then taper off harmonically to zero */
  if (x > i+2) return (float)(2*y1-y0)/(x-(i-1));
  if (x < i-1) return (float)((2*y0-y1)/(i-x));
  return (float)(y0*((i+1)-x) + y1*(x-i));
}

#if 0
/* free memory associated with dname */
void
freedata(char *dname)
{
  data_array head;
  int hval, nents;
  data_array *dp, *dpl;
  int i;

  if (dname == NULL) {  /* free all if NULL */
    hval = 0;
    nents = TABSIZ;
  } else {
    hval = hash(dname);
    nents = 1;
  }
  while (nents--) {
    head.next = dtab[hval];
    dpl = &head;
    while ((dp = dpl->next) != NULL)
      if (dname == NULL || !strcmp(dname, dp->name)) {
        dpl->next = dp->next;
        free((char *)dp->d);
        for (i = 0; i < dp->nd; i++)
          if (dp->dim[i].p != NULL) free((char *)dp->dim[i].p);
        free((char *)dp);
      } else
        dpl = dp;
    dtab[hval++] = head.next;
  }
}
#endif
