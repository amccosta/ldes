#define TOL 1.0e-15

#define SCALAR_TYPE 1
#define VECTOR_TYPE 2
#define FUNCTION_TYPE 3

#define SYMB_MAX 1024

typedef struct _symbol {
  char *name;
  double (*funcptr)();
  char args, type;
  double value1, value2, value3;
} symbol;
symbol symbol_table[SYMB_MAX];

extern symbol *symblook();

typedef struct _vector {
  double x, y, z;
} vector;

typedef char string[80];
