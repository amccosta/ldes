typedef union {
  double double_type;
  vector vector_type;
  symbol *symbp_type;
  string string_type;
} YYSTYPE;
#define LPAREN  257
#define RPAREN  258
#define COMMA 259
#define ASSIGN  260
#define LAPAREN 261
#define RAPAREN 262
#define IMPORTANCE  263
#define IF  264
#define RETURN  265
#define AND 266
#define OR  267
#define NOT 268
#define LT  269
#define GT  270
#define LE  271
#define GE  272
#define EQ  273
#define START 274
#define END 275
#define PRINT 276
#define PRINTVAR  277
#define NAME  278
#define NUMBER  279
#define FNAME 280
#define TEXT  281
#define MINUS 282
#define PLUS  283
#define MULTIPLY  284
#define DIVIDE  285
#define UMINUS  286

extern YYSTYPE yylval;
