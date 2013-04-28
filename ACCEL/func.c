#ifndef M_PI
#define M_PI 3.14159267
#endif

double
radian(double a)
{
  return a / 180 * M_PI;
}

double
degree(double a)
{
  return a * 180 / M_PI;
}

double
urandom(double a, double b)
{
  if (a > b)
  {
    double t = a;
    a = b;
    b = t;
  }
#ifdef WIN32
  return a + (b - a) * rand() / (double) RAND_MAX;
#else
  return a + (b - a) * random() / (double) RAND_MAX;
#endif
}

double
dmax(double a, double b)
{
  return a >= b ? a : b;
}

double
dmin(double a, double b)
{
  return a <= b ? a : b;
}

double
length(vector *v)
{
  return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

double
getx(vector *v)
{
  return v->x;
}

double
gety(vector *v)
{
  return v->y;
}

double
getz(vector *v)
{
  return v->z;
}

double
distance(vector *v1, vector *v2)
{
  vector v;

  v.x = v1->x - v2->x;
  v.y = v1->y - v2->y;
  v.z = v1->z - v2->z;
  return length(&v);
}

double
dotp(vector *v1, vector *v2)
{
  return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

double
angle(vector *v1, vector *v2)
{
  double l1, l2, cosa;

  l1 = length(v1);
  l2 = length(v2);
  if (ZERO(l1) || ZERO(l2)) return 2 * M_PI;
  cosa = dotp(v1, v2) / l1 / l2;
  return acos(cosa);
}

double
normalize(vector *v1, vector *v2)
{
  double l = length(v1);
  if (ZERO(l))
  {
    v2->x = 0;
    v2->y = 0;
    v2->z = 0;
    return 0;
  } else
  {
    v2->x = v1->x / l;
    v2->y = v1->y / l;
    v2->z = v1->z / l;
    return 1 / l;
  }
}

double
dir(vector *v1, vector *v2)
{
  double w = 1 - v1->x * v1->x;
  if (w <= 0)
  {
    v2->x = 0;
    v2->y = 0;
    v2->z = v1->x > 0 ? 1 : -1;
    return 0;
  }
  w = sqrt(w);
  v2->x = w * cos(v1->y);
  v2->y = w * sin(v1->y);
  v2->z = v1->x;
  return 1;
}

double
dirxy(vector *v1, vector *v2)
{
  char n = v1->z < 0;

  v1->z = 1 - v1->x * v1->x - v1->y * v1->y;
  if (v1->z < 0)
  {
    v2->x = sqrt(0.5);
    v2->y = sqrt(0.5);
    v2->z = 0;
    return 0;
  }
  v2->x = v1->x;
  v2->y = v1->y;
  v2->z = sqrt(v1->z);
  if (n) v2->z = -v2->z;
  return 1;
}

double
crossp(vector *v1, vector *v2, vector *v3)
{
  v3->x = v1->y * v2->z - v1->z * v2->y;
  v3->y = v1->z * v2->x - v1->x * v2->z;
  v3->z = v1->x * v2->y - v1->y * v2->x;
  return length(v3);
}

void
addfuncv(int n, char *name, double (*func)())
{
  addfunc(n + 1, name, func);
}

void
define_functions()
{
  /* scalar -> scalar */
  addfunc(1, "abs", fabs);
  addfunc(1, "sqrt", sqrt);
  addfunc(1, "exp", exp);
  addfunc(1, "log", log);
  addfunc(1, "sin", sin);
  addfunc(1, "cos", cos);
  addfunc(1, "tan", tan);
  addfunc(1, "asin", asin);
  addfunc(1, "acos", acos);
  addfunc(1, "atan", atan);
  addfunc(2, "atan2", atan2);

  addfunc(1, "radian", radian);
  addfunc(1, "degree", degree);
  addfunc(2, "urandom", urandom);
  addfunc(2, "max", dmax);
  addfunc(2, "min", dmin);
  /* vector -> scalar */
  addfunc(1, "length", length);
  addfunc(1, "getx", getx);
  addfunc(1, "gety", gety);
  addfunc(1, "getz", getz);
  addfunc(2, "distance", distance);
  addfunc(2, "dotp", dotp);
  addfunc(2, "angle", angle);

  /* vector -> vector */
  addfuncv(1, "normalize", normalize);
  addfuncv(1, "dir", dir);
  addfuncv(1, "dirxy", dirxy);
  addfuncv(2, "crossp", crossp);
}
