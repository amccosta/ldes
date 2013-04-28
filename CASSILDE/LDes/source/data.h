/*
 *  data.h - header file for routines which interpolate data.
 */

#define MAXDDIM 2   /* maximum data dimensions */
#define NAMESIZE 80   /* maximum file name size */

typedef struct datarray {
  char name[NAMESIZE];    /* name of our data */
  short nd;     /* number of dimensions */
  struct {
    float org, siz;   /* coordinate domain */
    int ne;     /* number of elements */
    float *p;     /* point locations */
  } dim[MAXDDIM];   /* dimension specifications */
  float *d;     /* float data */
  struct datarray *next;  /* next array in list */
} data_array;     /* a data array */

data_array *getdata(char *);
float datavalue(data_array *, float *);
#if 0
extern void freedata();
#endif
