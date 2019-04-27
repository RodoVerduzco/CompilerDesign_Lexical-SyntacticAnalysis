/**
 *  @file tiny.y
 *  @author  José Rodolfo Verduzco Torres || A01366134 ||
 *  @date 11 February 2019
 *
 *  @brief This program performs the grammar from a tiny c language
 *
 *  The program goes through every token received from tiny.l, and
 *  performs the  lexical analysis, if correct prints a message
 *  telling that everything is fine, else returns an error.
 *
 */

%{

#include "table.h"            // Helper file
  /* Function definitions */
extern int line;
extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(char *string);
void typeError(int line, entry_p data);
int quadLineIncrement();

int errors = 0;
int quadLine = 0;


 /* Removes the warning of yylex() not defined when using C99 */
#if YYBISON
    union YYSTYPE;
    int yylex();     // Should be int yylex(union YYSTYPE *, void *);
#endif

%}

%union {
  int     intVal;
  float   floatVal;
  char *  stringVal;
  line_p linePoint;
  entry_p symTab;
}

  /*  *  *  Token Definition  *  *  */

 /* Reserved Words*/
%token <intVal> INTEGER
%token <floatVal> FLOAT
%token IF
%token THEN
%token ELSE
%token WHILE
%token DO
%token READ
%token WRITE

 /* Punctuation Tokens */
%token SEMI
%token COMMA
%token LPAREN
%token RPAREN
%token LBRACE
%token RBRACE

 /* Relational Tokens */
%token LT
%token GT
%token EQ

 /* Operations*/
%token PLUS
%token MINUS
%token TIMES
%token DIV
%token ASSIGN

 /* Numbers */
%token <intVal> INT_NUM
%token <floatVal> FLOAT_NUM

 /* Identifier */
%token <stringVal>ID

%nonassoc THEN
%nonassoc ELSE

%type <intVal> type;
%type <linePoint>M N
%type <symTab> variable factor term simple_exp exp stmt_seq block stmt;
%%

 /*  *  *  *  Grammar definition  *  *  *  */
program: var_dec stmt_seq M                 {
                                              printf("\nFound %d errors in the Program\n\n", errors);
                                            };

var_dec: %empty                             {  /* epsilon */  }
         | var_dec single_dec               {  }
         ;

single_dec: type ID SEMI                    {
                                              if(addSymbol($1, $2, line)) {
                                                printf("Warning [%d]: Variable '%s' alredy defined\n" ,line, $2);
                                              }
                                            }
      ;

type:   INTEGER                             { $$ = INT; }
      | FLOAT                               { $$ = FLT; }
      ;

stmt_seq: %empty                            { /* epsilon */ }
          |stmt_seq M stmt                  {  }
          ;

stmt:   IF exp %prec THEN M stmt M          {  }
      | IF exp THEN M stmt N ELSE M stmt    {  }
      | WHILE M exp DO M stmt               {  }
      | variable ASSIGN exp SEMI            {  }
                                            {
                                               if(($1->type == FLT) && ($3->type == FLT)) {
                                                 union num_val value;
                                                 value.float_value = 0;
                                                 $$ = createTempConstant(value, FLT);
                                                // Do sth
                                              }
                                              else if(($1->type == INT)&& ($3->type == INT)) {
                                                union num_val value;
                                                value.float_value = 0;
                                                $$ = createTempConstant(value, INT);
                                                // ASSIGN to
                                              }
                                              else {
                                                typeError(line, $1);
                                              }

                                            };
      | READ LPAREN variable RPAREN SEMI    {  }
      | WRITE LPAREN exp RPAREN SEMI        {  }
      | block                               {  }
      ;

block : LBRACE stmt_seq RBRACE              {  }
      ;

exp: simple_exp LT simple_exp               {  }
      | simple_exp EQ simple_exp            {  }
      | simple_exp                          {  }
      ;

simple_exp: simple_exp PLUS term            {
                                              //$$ = line_p = malloc(sizeof(line_));

                                              // Type Checking
                                              if(($1->type==INT) && ($3->type==INT)) {
                                                union num_val value;
                                                value.float_value = 0;

                                                // Set quad Type
                                                $$->type = INT;

                                                // Create Temp
                                                createTempConstant(value, INT);
                                              }
                                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                                union num_val value;
                                                value.float_value = 0;

                                                // Set quad Type
                                                $$->type = FLT;

                                                // Create Temp
                                                createTempConstant(value, FLT);
                                              }
                                              // Coersion
                                              else {
                                                if($$->type == FLT) {
                                                  if(($1->type==FLT) && ($3->type==INT)) {
                                                    union num_val value;
                                                    value.float_value = 0;

                                                    // Set quad Type
                                                    $$->type = FLT;

                                                    // Create Temp
                                                    createTempConstant(value, FLT);
                                                  }
                                                  if(($1->type==INT) && ($3->type==FLT)) {
                                                    union num_val value;
                                                    value.float_value = 0;

                                                    // Set quad Type
                                                    $$->type = FLT;

                                                    // Create Temp
                                                    createTempConstant(value, FLT);
                                                  }
                                                }
                                                else {
                                                  typeError(line, $$);
                                                }
                                              }

                                              newQuad('+', $1->name, $3->name, $$->name);
                                              quadLineIncrement();
                                            }
      | simple_exp MINUS term               {
                                              if(($1->type==INT) && ($3->type==INT)) {
                                                union num_val value;
                                                value.integer_value = 0;
                                                $$ = createTempConstant(value, INT);
                                              }
                                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                                union num_val value;
                                                value.float_value = 0;
                                                $$ = createTempConstant(value, FLT);
                                              }
                                              // Coersion
                                              else {
                                                printf("MIN - Coersion [%d] for %s and %s\n", line, $1->name, $3->name);
                                                if($$->type == FLT) {
                                                  if(($1->type==FLT) && ($3->type==INT)){
                                                    union num_val value;
                                                    value.float_value = 0;
                                                    $$ = createTempConstant(value, FLT);
                                                  }
                                                  if(($1->type==INT) && ($3->type==FLT)){
                                                    union num_val value;
                                                    value.float_value = 0;
                                                    $$ = createTempConstant(value, FLT);
                                                  }
                                                }
                                                else {
                                                  typeError(line, $$);
                                                }
                                              }
                                            }
      | term                                { $$ = $1; }
      ;

term: term TIMES factor                     {
                                              if(($1->type==INT) && ($3->type==INT)) {
                                                union num_val value;
                                                value.integer_value = 0;
                                                $$ = createTempConstant(value, INT);
                                              }
                                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                                union num_val value;
                                                value.float_value = 0;
                                                $$ = createTempConstant(value, FLT);
                                              }
                                              // Coersion
                                              else {
                                                printf("MULT - Coersion [%d] for %s and %s\n", line, $1->name, $3->name);

                                                if(($1->type==FLT) && ($3->type==INT)){
                                                  union num_val value;
                                                  value.float_value = 0;
                                                  $$ = createTempConstant(value, FLT);
                                                }
                                                if(($1->type==INT) && ($3->type==FLT)){
                                                  union num_val value;
                                                  value.float_value = 0;
                                                  $$ = createTempConstant(value, FLT);
                                                }
                                              }
                                           }
      | term DIV factor                    {
                                              if(($1->type==INT) && ($3->type==INT)) {
                                                union num_val value;
                                                value.float_value = 0;
                                                $$ = createTempConstant(value, INT);
                                              }
                                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                                union num_val value;
                                                value.float_value = 0;
                                                $$ = createTempConstant(value, FLT);
                                              }
                                              // Coersion
                                              else {
                                                printf("DIV - Coersion [%d] for %s and %s\n", line, $1->name, $3->name);

                                                if(($1->type==FLT) && ($3->type==INT)){
                                                  union num_val value;
                                                  value.float_value = 0;
                                                  $$ = createTempConstant(value, FLT);
                                                }
                                                if(($1->type==INT) && ($3->type==FLT)){
                                                  union num_val value;
                                                  value.float_value = 0;
                                                  $$ = createTempConstant(value, FLT);
                                                }
                                              }
                                            }

      | factor                              {  }
      ;

factor: LPAREN exp RPAREN                   {  }
      | INT_NUM                             {
                                              union num_val value;
                                              value.integer_value = $1;
                                              $$ = createTempConstant(value, INT);
                                            }
      | FLOAT_NUM                           {
                                              union num_val value;
                                              value.float_value = $1;
                                              $$ = createTempConstant(value, FLT);
                                            }
      | variable                            { $$ = $1; }
      ;

variable: ID                                {
                                                /* Check if the variable is in the symbol table */
                                                entry_p node = lookSymbol($1);
                                                if(node == NULL){
                                                      printf("ERROR [%d]: Variable '%s' is undeclared\n" ,line, $1);
                                                      $$ = NULL;
                                                      exit(EXIT_FAILURE);
                                                }
                                                else {
                                                      $$ = node;
                                                }
                                            }
        ;
  /* Backpatching grammar */
  M: %empty                                 {
                                                // M.quad = nextQuad
                                                $$ = (line_p) malloc(sizeof(line_st));
                                                $$->quad = quadLine;
                                            }
         ;

  N: %empty                                 {
                                                // N.next_list = newList(nextQuad)
                                                // gen('goto _')
                                                $$ = (line_p) malloc(sizeof(line_st));
                                                //$$->nextList = NewList(quadLine);
                                                newQuad('j', "", "", "goto_");
                                                quadLineIncrement();
                                            };

%%

/* Function prototype for yylex() */
int yylex();

#include "lex.yy.c"

/* Bison does NOT implement yyerror, so define it here */
void yyerror (char *string) {
  char * stderr;
  printf ("ERROR: %s in line %d\n", string, line);
  //exit(EXIT_FAILURE);
}

void typeError(int line, entry_p data){
  printf("ERROR [%d]: inconsistent type for %s \n", line, data->name);
  errors ++;
  exit(EXIT_FAILURE);
}

int quadLineIncrement() {
  int prevQuad = quadLine;
  quadLine ++;
  return prevQuad;
}

/* Bison does NOT define the main entry point so define it here */
int main (void) {
  // Create the hash table
  symTable_p  = g_hash_table_new_full(g_str_hash, g_str_equal,
                                      NULL,
                                      (GDestroyNotify)freeItem);

  // Perform the parsing
  yyparse();

  // Print the table
  printTable();

  // Destroy the hash table
  g_hash_table_destroy(symTable_p);
  return(EXIT_SUCCESS);
}
