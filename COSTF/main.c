#include <stdlib.h>
#include <stdio.h>
#include <math.h>

extern int evalcf(char *, double, int, double *, double *);

main(int argc, char *argv[])
{
  int n, code;
  double param[16], value;

  if (argc < 4) exit(99);
  for (n = 0; n < argc - 3; n++) param[n] = atof(argv[n + 3]);
  code = evalcf(argv[1], atof(argv[2]), n, param, &value);
  switch (code)
  {
    case 0:
      printf("2 %s: result -> %g\n", argv[1], value);
      exit(0);
    case 1:
      printf("bad number of parameters\n");
      exit(1);
    case 2:
      printf("%s: not found\n", argv[1]);
      exit(2);
    case 3:
      printf("%s: evaluation error\n", argv[1]);
      exit(3);
    default:
      exit(99);
  }
}
