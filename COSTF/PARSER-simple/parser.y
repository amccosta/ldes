%{
#include "defs.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ZERO(x) (fabs(x) < TOL)
#define LEVEL_MAX 16

char true[LEVEL_MAX];
char level;
double result;
int yylinecount, yyinlinecount;
char end_reached;
char parse_error;

extern char *yytext;
extern void yyerror(char *);
extern void yyerror2(char *, char *);
extern float radcalcdir(char *, float, float, float,
                        float, float, float, float,
                        char *, float, float, float);

#define if_PROCEED(level) \
if (parse_error) YYABORT; if (level >= 0 && true[level])
%}

%union {
  double double_type;
  vector vector_type;
  symbol *symbp_type;
  string string_type;
}

%token LPAREN RPAREN COMMA ASSIGN LAPAREN RAPAREN IMPORTANCE
%token IF RETURN AND OR NOT LT GT LE GE EQ START END PRINT PRINTVAR
%token <symbp_type> NAME
%token <double_type> NUMBER
%token <string_type> FNAME
%token <string_type> TEXT

%left LT GT LE GE EQ
%left AND OR
%left MINUS PLUS
%left MULTIPLY DIVIDE
%left NOT
%nonassoc UMINUS

%type <double_type> expression
%type <vector_type> vector_expression
%%

program:
  return_statement
  | statement_list return_statement
  ;

statement_list:
  statement
  | statement_list statement
  ;

statement:
  return_statement
  | NAME ASSIGN expression
  {
    if_PROCEED(level)
    {
      $1->value1 = $3;
      $1->type = SCALAR_TYPE;
    }
  }
  | NAME ASSIGN LAPAREN vector_expression RAPAREN
  {
    if_PROCEED(level)
    {
      $1->value1 = $4.x;
      $1->value2 = $4.y;
      $1->value3 = $4.z;
      $1->type = VECTOR_TYPE;
    }
  }
  | IF LPAREN expression RPAREN
  {
    if (++level == LEVEL_MAX) yyerror("too many levels");
    true[level] = true[level - 1] & !ZERO($3);
  }
  statement
  {
    level--;
  }
  | IF LPAREN expression RPAREN
  {
    if (++level == LEVEL_MAX) yyerror("too many levels");
    true[level] = true[level - 1] & !ZERO($3);
  }
  START statement_list END
  {
    level--;
  }
  | PRINT LPAREN TEXT RPAREN
  {
    if_PROCEED(level)
    {
      if ($3 && $3[0]) fprintf(stderr, "%s", $3);
      else fprintf(stderr, "\n");
    }
  }
  | PRINTVAR LPAREN expression RPAREN
  {
    if_PROCEED(level) fprintf(stderr, "%g ", $3);
  }
  | PRINTVAR LAPAREN vector_expression RAPAREN
  {
    if_PROCEED(level) fprintf(stderr, "%g %g %g ", $3.x, $3.y, $3.z);
  }
  ;

return_statement:
  RETURN expression
  {
    if_PROCEED(level)
    {
      result = $2;
      level = -1;
    }
  }
  ;

expression:
  NUMBER
  | NAME
  {
    if_PROCEED(level)
    {
      if ($1->type == SCALAR_TYPE)
        $$ = $1->value1;
      else
        yyerror2("non-scalar variable", $1->name);
    }
  }
  | expression LT expression
  {
    if_PROCEED(level) $$ = $1 < $3;
  }
  | expression GT expression
  {
    if_PROCEED(level) $$ = $1 > $3;
  }
  | expression LE expression
  {
    if_PROCEED(level) $$ = $1 <= $3;
  }
  | expression GE expression
  {
    if_PROCEED(level) $$ = $1 >= $3;
  }
  | expression EQ expression
  {
    if_PROCEED(level) $$ = ZERO($1 - $3) ? 1 : 0;
  }
  | expression AND expression
  {
    if_PROCEED(level) $$ = $1 && $3;
  }
  | expression OR expression
  {
    if_PROCEED(level) $$ = $1 || $3;
  }
  | NOT expression %prec UMINUS
  {
    if_PROCEED(level) $$ = !$2;
  }
  | expression PLUS expression
  {
    if_PROCEED(level) $$ = $1 + $3;
  }
  | expression MINUS expression
  {
    if_PROCEED(level) $$ = $1 - $3;
  }
  | expression MULTIPLY expression
  {
    if_PROCEED(level) $$ = $1 * $3;
  }
  | expression DIVIDE expression
  {
    if_PROCEED(level)
    {
      if (ZERO($3)) yyerror("divide by zero");
      else $$ = $1 / $3;
    }
  }
  | MINUS expression %prec UMINUS
  {
    if_PROCEED(level) $$ = -$2;
  }
  | LPAREN expression RPAREN
  {
    if_PROCEED(level) $$ = $2;
  }
  | NAME LPAREN expression RPAREN
  {
    if_PROCEED(level)
    {
      if ($1->type == FUNCTION_TYPE && $1->funcptr)
        if ($1->args == 1)
          $$ = ($1->funcptr)($3);
        else
          yyerror2("bad args in scalar function", $1->name);
      else
        yyerror2("non-scalar function", $1->name);
    }
  }
  | NAME LPAREN expression COMMA expression RPAREN
  {
    if_PROCEED(level)
    {
      if ($1->type == FUNCTION_TYPE && $1->funcptr)
        if ($1->args == 2)
          $$ = ($1->funcptr)($3, $5);
        else
          yyerror2("bad args in scalar function", $1->name);
      else
        yyerror2("non-scalar function", $1->name);
    }
  }
  | NAME LPAREN expression COMMA expression COMMA expression RPAREN
  {
    if_PROCEED(level)
    {
      if ($1->type == FUNCTION_TYPE && $1->funcptr)
        if ($1->args == 3)
          $$ = ($1->funcptr)($3, $5, $7);
        else
          yyerror2("bad args in scalar function", $1->name);
      else
        yyerror2("non-scalar function", $1->name);
    }
  }
  | NAME LAPAREN vector_expression RAPAREN
  {
    if_PROCEED(level)
    {
      if ($1->type == FUNCTION_TYPE && $1->funcptr)
        if ($1->args == 1)
          $$ = ($1->funcptr)(&$3);
        else
          yyerror2("bad args in vector function", $1->name);
      else
        yyerror2("non-vector function", $1->name);
    }
  }
  | NAME LAPAREN vector_expression COMMA vector_expression RAPAREN
  {
    if_PROCEED(level)
    {
      if ($1->type == FUNCTION_TYPE && $1->funcptr)
        if ($1->args == 2)
          $$ = ($1->funcptr)(&$3, &$5);
        else
          yyerror2("bad args in vector function", $1->name);
      else
        yyerror2("non-vector function", $1->name);
    }
  }
  | IMPORTANCE LPAREN FNAME COMMA expression
    COMMA expression COMMA expression COMMA expression
    COMMA expression COMMA expression COMMA expression RPAREN
  {
    if_PROCEED(level)
    {
      $$ = radcalcdir($3, $5, $7, $9, $11, $13, $15, $17, "", 0.0, 0.0, 0.0);
      if ($$ < 0)
      {
        $$ = 0;
        yyerror2("importance error related to", $3);
      }
    }
  }
  | IMPORTANCE LPAREN FNAME COMMA expression
    COMMA expression COMMA expression COMMA expression
    COMMA expression COMMA expression COMMA expression COMMA FNAME RPAREN
  {
    if_PROCEED(level)
    {
      $$ = radcalcdir($3, $5, $7, $9, $11, $13, $15, $17, $19, 0.0, 0.0, 0.0);
      if ($$ < 0)
      {
        $$ = 0;
        yyerror2("importance error related to", $3);
      }
    }
  }
  | IMPORTANCE LPAREN FNAME COMMA expression
    COMMA expression COMMA expression COMMA expression
    COMMA expression COMMA expression COMMA expression COMMA FNAME
    COMMA expression COMMA expression COMMA expression RPAREN
  {
    if_PROCEED(level)
    {
      $$ = radcalcdir($3, $5, $7, $9, $11, $13, $15, $17, $19, $21, $23, $25);
      if ($$ < 0)
      {
        $$ = 0;
        yyerror2("importance error related to", $3);
      }
    }
  }
  ;

vector_expression:
  NAME
  {
    if_PROCEED(level)
    {
      if ($1->type == VECTOR_TYPE)
      {
        $$.x = $1->value1;
        $$.y = $1->value2;
        $$.z = $1->value3;
      } else
        yyerror2("non-vector variable", $1->name);
    }
  }
  | LPAREN expression COMMA expression COMMA expression RPAREN
  {
    if_PROCEED(level)
    {
      $$.x = $2;
      $$.y = $4;
      $$.z = $6;
    }
  }
  | vector_expression PLUS vector_expression
  {
    if_PROCEED(level)
    {
      $$.x = $1.x + $3.x;
      $$.y = $1.y + $3.y;
      $$.z = $1.z + $3.z;
    }
  }
  | vector_expression MINUS vector_expression
  {
    if_PROCEED(level)
    {
      $$.x = $1.x - $3.x;
      $$.y = $1.y - $3.y;
      $$.z = $1.z - $3.z;
    }
  }
  | vector_expression MULTIPLY expression
  {
    if_PROCEED(level)
    {
      $$.x = $3 * $1.x;
      $$.y = $3 * $1.y;
      $$.z = $3 * $1.z;
    }
  }
  | NAME LAPAREN vector_expression RAPAREN
  {
    if_PROCEED(level)
    {
      if ($1->type == FUNCTION_TYPE && $1->funcptr)
        if ($1->args == 2)
        {
          vector temp;

          ($1->funcptr)(&$3, &temp);
          $$.x = temp.x;
          $$.y = temp.y;
          $$.z = temp.z;
        } else
          yyerror2("bad args in vector function", $1->name);
      else
        yyerror2("non-vector function", $1->name);
    }
  }
  | NAME LAPAREN vector_expression COMMA vector_expression RAPAREN
  {
    if_PROCEED(level)
    {
      if ($1->type == FUNCTION_TYPE && $1->funcptr)
        if ($1->args == 3)
        {
          vector temp;

          ($1->funcptr)(&$3, &$5, &temp);
          $$.x = temp.x;
          $$.y = temp.y;
          $$.z = temp.z;
        } else
          yyerror2("bad args in vector function", $1->name);
      else
        yyerror2("non-vector function", $1->name);
    }
  }
  ;
%%

symbol *
symblook(char *name)
{
  symbol *sp;

  for (sp = symbol_table; sp < &symbol_table[SYMB_MAX]; sp++)
  {
    if (sp->name && !strcmp(sp->name, name)) return sp;
    if (!sp->name)
    {
      sp->name = strdup(name);
      if (!sp->name) yyerror("out of memory");
      return sp;
    }
  }
  yyerror("too many symbols");
}

void
yyerror2(char *message, char *data)
{
  char *p, *whole_message, *unknown = "(unknown?)";

  if (data) p = data;
  else p = unknown;
  whole_message = malloc(strlen(message) + strlen(p) + 4);
  if (!whole_message) yyerror("out of memory");
  sprintf(whole_message, "%s \"%s\"", message, p);
  yyerror(whole_message);
}

void
yyerror(char *message)
{
  if (yytext[0])
  {
    if (yyinlinecount > 1)
      fprintf(stderr, "error in line %d (instruction %d) reading \"%s\"",
        yylinecount, yyinlinecount, yytext);
    else
      fprintf(stderr, "error in line %d reading \"%s\"",
        yylinecount, yytext);
  } else
  {
    if (yyinlinecount > 1)
      fprintf(stderr, "error in line %d (instruction %d)",
        yylinecount, yyinlinecount);
    else
      fprintf(stderr, "error in line %d",
        yylinecount);
  }
  if (end_reached)
    fprintf(stderr, " [%s - missing return statement]\n", message);
  else
    fprintf(stderr, " [%s]\n", message);
  parse_error = 1;
}

void
addfunc(int n, char *name, double (*func)())
{
  symbol *sp = symblook(name);
  sp->type = FUNCTION_TYPE;
  sp->args = n;
  sp->funcptr = func;
}

#include "func.c"

void
addsymb(char *name, double value)
{
  symbol *sp = symblook(name);
  sp->type = SCALAR_TYPE;
  sp->value1 = value;
}

#include "symb.c"

extern FILE *yyin;

static char *last_name = 0;
static int last_n = 0;

int
evalcf(char *name, double cost, int n, double *param, double *value)
{
  int i;
  char var[5];

  if (n < 0)
  {
    n = -n;
    last_name = 0;
    last_n = 0;
  }

  if (n < 1 || n > 100) return 1;
  if (last_n && last_n != n) return 1;
  if (last_name && strcmp(last_name, name)) return 1;

  yyin = fopen(name, "r");
  if (!yyin) return 2;

  sprintf(var, "x0");
  addsymb(var, cost);
  for (i = 0; i < n; i++)
  {
    sprintf(var, "x%d", i + 1);
    addsymb(var, param[i]);
  }

#ifdef WIN32
  srand(time(0));
#else
  srandom(time(0));
#endif
  true[level] = 1;

  if (!last_name)
  {
    define_symbols();
    define_functions();
  }

  level = 0;
  result = 0;
  end_reached = 0;
  parse_error = 0;
  yylinecount = 1;
  yyinlinecount = 1;

  if (yyparse())
  {
    if (yyin) fclose(yyin);
    return 3;
  }
  if (yyin) fclose(yyin);
  *value = result;
  last_n = n;
  last_name = name;
  return 0;
}
