%{
#include "defs.h"
#include "y.tab.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EXIT_LEXER(message) \
do { fprintf(stderr, "%s in lexer\n", message); exit(99); } while (0)

#undef YY_INPUT
#define YY_INPUT(buffer, result, size) (result = list_input(buffer, size))

static int list_input(char *, int);
static char first_lex = 1;

extern int yylinecount, yyinlinecount;
extern char end_reached;

#define STR_SIZE 4
typedef struct _lex_item {
  char str1[STR_SIZE];
  char *str2;
  short int len;
  struct _lex_item *next;
} lex_item;

static lex_item *head_lex_list = 0, *curr_lex_list = 0;
static void add_lex_item (char *);
%}

%option noyywrap
%option never-interactive
%%

<<EOF>> {
    if (first_lex)
    {
      add_lex_item("$");
      first_lex = 0;
    }
    curr_lex_list = head_lex_list;
    end_reached = 1;
    return 0;
}
"$" {
    if (first_lex)
    {
      add_lex_item("$");
      first_lex = 0;
    }
    curr_lex_list = head_lex_list;
    end_reached = 1;
    return 0;
}

[ \t]+    ;

\n {
    yylinecount++;
    yyinlinecount = 1;
}
\; {
    yyinlinecount++;
}

\#|\% {
    int c;
    while ((c = input()) != '\n' && c != EOF);
    yylinecount++;
}

([0-9]+|([0-9]*\.[0-9]+)([eE][-+]?[0-9]+)?) {
    yylval.double_type = atof(yytext);
    if (first_lex) add_lex_item(yytext);
    return NUMBER;
}

importance  { if (first_lex) add_lex_item(yytext); return IMPORTANCE; }
IMPORTANCE  { if (first_lex) add_lex_item(yytext); return IMPORTANCE; }
PRINTVAR  { if (first_lex) add_lex_item(yytext); return PRINTVAR; }
RETURN    { if (first_lex) add_lex_item(yytext); return RETURN; }
PRINT   { if (first_lex) add_lex_item(yytext); return PRINT; }
AND   { if (first_lex) add_lex_item(yytext); return AND; }
NOT   { if (first_lex) add_lex_item(yytext); return NOT; }
IF    { if (first_lex) add_lex_item(yytext); return IF; }
OR    { if (first_lex) add_lex_item(yytext); return OR; }
">="    { if (first_lex) add_lex_item(yytext); return GE; }
"<="    { if (first_lex) add_lex_item(yytext); return LE; }
"=="    { if (first_lex) add_lex_item(yytext); return EQ; }
"<"   { if (first_lex) add_lex_item(yytext); return LT; }
">"   { if (first_lex) add_lex_item(yytext); return GT; }
"="   { if (first_lex) add_lex_item(yytext); return ASSIGN; }
","   { if (first_lex) add_lex_item(yytext); return COMMA; }
"("   { if (first_lex) add_lex_item(yytext); return LPAREN; }
")"   { if (first_lex) add_lex_item(yytext); return RPAREN; }
"["   { if (first_lex) add_lex_item(yytext); return LAPAREN; }
"]"   { if (first_lex) add_lex_item(yytext); return RAPAREN; }
"+"   { if (first_lex) add_lex_item(yytext); return PLUS; }
"-"   { if (first_lex) add_lex_item(yytext); return MINUS; }
"*"   { if (first_lex) add_lex_item(yytext); return MULTIPLY; }
"/"   { if (first_lex) add_lex_item(yytext); return DIVIDE; }
"{"   { if (first_lex) add_lex_item(yytext); return START; }
"}"   { if (first_lex) add_lex_item(yytext); return END; }

[A-Za-z][A-Za-z0-9_]* {
    symbol *sp = symblook(yytext);
    yylval.symbp_type = sp;
    if (first_lex) add_lex_item(yytext);
    return NAME;
}

\"[A-Za-z0-9_\-\.]+\" {
    int l = yyleng - 2;
    strncpy(yylval.string_type, &yytext[1], l);
    yylval.string_type[l] = 0;
    if (first_lex) add_lex_item(yytext);
    return FNAME;
}
\'[^']*\' {
    int l = yyleng - 2;
    strncpy(yylval.string_type, &yytext[1], l);
    yylval.string_type[l] = 0;
    if (first_lex) add_lex_item(yytext);
    return TEXT;
}


.   { if (first_lex) add_lex_item(yytext); return yytext[0]; }
%%

static int
list_input(char *buffer, int size)
{
  int c, n = 0, len;

  if (first_lex)
  {
    while ((c = getc(yyin)) != EOF && n < size) buffer[n++] = c;
    return n;
  }

  if (!curr_lex_list) return 0;
  len = curr_lex_list->len;
  if (len >= size) EXIT_LEXER("buffer too small");
  if (len > STR_SIZE)
    memcpy(&buffer[n], curr_lex_list->str2, len);
  else
    memcpy(&buffer[n], curr_lex_list->str1, len);
  n += len;
  buffer[n++] = ' ';
  curr_lex_list = curr_lex_list->next;

  while (curr_lex_list)
  {
    len = curr_lex_list->len;
    if (n + len >= size) break;
    if (len > STR_SIZE)
      memcpy(&buffer[n], curr_lex_list->str2, len);
    else
      memcpy(&buffer[n], curr_lex_list->str1, len);
    n += len;
    buffer[n++] = ' ';
    curr_lex_list = curr_lex_list->next;
  }
  return n;
}

static void
add_lex_item(char *s)
{
  int len = strlen(s);
  lex_item *new_item = (lex_item *) malloc(sizeof(lex_item));
  if (!new_item) EXIT_LEXER("out of memory");
  if (len <= STR_SIZE)
    memcpy(new_item->str1, s, len);
  else
  {
    new_item->str2 = (char *) malloc(sizeof(char) * (len + 1));
    if (!new_item->str2) EXIT_LEXER("out of memory");
    memcpy(new_item->str2, s, len);
  }
  new_item->len = len;
  new_item->next = 0;
  if (!head_lex_list) head_lex_list = new_item;
  if (curr_lex_list) curr_lex_list->next = new_item;
  curr_lex_list = new_item;
}
