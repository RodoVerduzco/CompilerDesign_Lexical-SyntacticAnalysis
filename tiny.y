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
void yyerror (char *string);
void typeError(int line, entry_p data);
extern int line;
extern int yylex();
extern int yyparse();
extern FILE *yyin;
int errors = 0;

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
%token INT_NUM
%token FLOAT_NUM

 /* Identifier */
%token <stringVal>ID


%type <intVal> type
%type <symTab> variable factor term simple_exp exp stmt_seq block stmt
%type <intVal> FLOAT_NUM
%type <intVal> INT_NUM
%%

 /*  *  *  *  Grammar definition  *  *  *  */
program: var_dec stmt_seq {
                            printf("\nFound %d errors in the Program\n\n", errors);
                          };

var_dec: { /* epsilon */}
      |var_dec single_dec
      ;

single_dec: type ID SEMI {
                            if(addSymbol($1, $2)) {
                              printf("Warning [%d]: Variable '%s' alredy defined\n" ,line, $2);
                            }
                         };

type: INTEGER { $$ = INT;}
      | FLOAT { $$ = FLT;}
      ;

stmt_seq: { /* epsilon */ }
      |stmt_seq stmt
      ;

stmt: IF exp THEN stmt
      | IF exp THEN stmt ELSE stmt
      | WHILE exp DO stmt
      | variable ASSIGN exp SEMI
        {
          /* printf("\nLinea %d -> %s con tipo %d \n",line, $1->name, $1->type);
          printf("   >Type: %s   %d", $3->name, $3->type);
          printf("\n\n"); */

          //printf("$1 name %s type %d value %d    $3 name %s type %d value %d\n\n", $1->name, $1->type, $1->value, $3->name, $3->type, $3->value);
           if(($1->type == FLT) && ($3->type == FLT)) {
             union num_val value;
             value.float_value = 0;
             $$ = createTempConstant(value, FLT);
            //$$->value.float_value = $3->value.float_value;
            //$1->value.float_value = $3->value.float_value;
            // Do sth
          }
          else if(($1->type == INT)&& ($3->type == INT)) {
            union num_val value;
            value.float_value = 0;
            $$ = createTempConstant(value, INT);
            //$$->value.integer_value = $3->value.integer_value;
            //$1->value.integer_value = $3->value.integer_value;
            //$1->value.integer_value = $3;
            // ASSIGN to
          }
          else {
            typeError(line, $1);
          }

        };
      | READ LPAREN variable RPAREN SEMI
      | WRITE LPAREN exp RPAREN SEMI
      | block

block : LBRACE stmt_seq RBRACE;

exp: simple_exp LT simple_exp
      | simple_exp EQ simple_exp
      | simple_exp                { $$ = $1; }
      ;

simple_exp: simple_exp PLUS term  {
                                    if(($1->type==INT) && ($3->type==INT)) {
                                      union num_val value;
                                      value.float_value = 0;
                                      $$ = createTempConstant(value, INT);
                                      //$$->value.integer_value = $1->value.integer_value + $3->value.integer_value;
                                    }
                                    else if(($1->type==FLT) && ($3->type==FLT)) {
                                      union num_val value;
                                      value.float_value = 0;
                                      $$ = createTempConstant(value, FLT);
                                      //$$->value.float_value = $1->value.float_value + $3->value.float_value;
                                    }
                                    // Coersion
                                    else {
                                      if($$->type == FLT) {
                                        if(($1->type==FLT) && ($3->type==INT)) {
                                          union num_val value;
                                          value.float_value = 0;
                                          $$ = createTempConstant(value, FLT);
                                          //$$->value.float_value = $1->value.float_value + $3->value.integer_value;
                                        }
                                        if(($1->type==INT) && ($3->type==FLT)) {
                                          union num_val value;
                                          value.float_value = 0;
                                          $$ = createTempConstant(value, FLT);
                                          //$$->value.float_value = $1->value.integer_value + $3->value.float_value;
                                        }
                                      }
                                      else {
                                        typeError(line, $$);
                                      }
                                    }
                                  }
      | simple_exp MINUS term     {
                                    if(($1->type==INT) && ($3->type==INT)) {
                                      union num_val value;
                                      value.float_value = 0;
                                      $$ = createTempConstant(value, INT);
                                      //$$->value.integer_value = $1->value.integer_value - $3->value.integer_value;
                                    }
                                    else if(($1->type==FLT) && ($3->type==FLT)) {
                                      union num_val value;
                                      value.float_value = 0;
                                      $$ = createTempConstant(value, FLT);
                                      //$$->value.float_value = $1->value.float_value - $3->value.float_value;
                                    }
                                    // Coersion
                                    else {
                                      printf("MIN - Coersion [%d] for %s and %s\n", line, $1->name, $3->name);
                                      if($$->type == FLT) {
                                        if(($1->type==FLT) && ($3->type==INT)){
                                          union num_val value;
                                          value.float_value = 0;
                                          $$ = createTempConstant(value, FLT);
                                          //$$->value.float_value = $1->value.float_value - $3->value.integer_value;
                                        }
                                        if(($1->type==INT) && ($3->type==FLT)){
                                          union num_val value;
                                          value.float_value = 0;
                                          $$ = createTempConstant(value, FLT);
                                        //  $$->value.float_value = $1->value.integer_value - $3->value.float_value;
                                        }
                                      }
                                      else {
                                        typeError(line, $$);
                                      }
                                    }
                                  }
      | term                      { $$ = $1; }
      ;

term: term TIMES factor    {
                              if(($1->type==INT) && ($3->type==INT)) {
                                union num_val value;
                                value.float_value = 0;
                                $$ = createTempConstant(value, INT);
                                //$$->value.integer_value = $1->value.integer_value * $3->value.integer_value;
                              }
                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                union num_val value;
                                value.float_value = 0;
                                $$ = createTempConstant(value, FLT);
                                //$$->value.float_value = $1->value.float_value * $3->value.float_value;
                              }
                              // Coersion
                              else {
                                printf("MULT - Coersion [%d] for %s and %s\n", line, $1->name, $3->name);

                                if(($1->type==FLT) && ($3->type==INT)){
                                  union num_val value;
                                  value.float_value = 0;
                                  $$ = createTempConstant(value, FLT);
                                  //$$->value.float_value = $1->value.float_value * $3->value.integer_value;
                                }
                                if(($1->type==INT) && ($3->type==FLT)){
                                  union num_val value;
                                  value.float_value = 0;
                                  $$ = createTempConstant(value, FLT);
                                  //$$->value.float_value = $1->value.integer_value * $3->value.float_value;
                                }
                              }
                           }
      | term DIV factor    {
                              if(($1->type==INT) && ($3->type==INT)) {
                                //$$->type = INT;
                                union num_val value;
                                value.float_value = 0;
                                $$ = createTempConstant(value, INT);
/*
                                if($3->value.integer_value == 0) {
                                  printf("ERROR [%d] Division by Zero\n", line);
                                  errors ++;
                                  //exit(EXIT_FAILURE);
                                }
                                else {
                                  //$$->value.integer_value = $1->value.integer_value / $3->value.integer_value;
                                } */
                              }
                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                union num_val value;
                                value.float_value = 0;
                                $$ = createTempConstant(value, FLT);
                                //$$->type = FLT;

                                /* if($3->value.float_value == 0.0) {
                                  printf("ERROR [%d] Division by Zero\n", line);
                                  errors ++;
                                  //exit(EXIT_FAILURE);
                                }
                                else {
                                  $$->value.float_value = $1->value.float_value / $3->value.float_value;
                                } */
                              }
                              //else if( (($1->type==FLT) && ($3->type==INT)) || (($1->type==INT) && ($3->type==FLT)) ) {
                              // Coersion
                              else {
                                printf("DIV - Coersion [%d] for %s and %s\n", line, $1->name, $3->name);

                                /* if($3->value.float_value == 0.0) {
                                  printf("ERROR [%d] Division by Zero\n", line);
                                  errors ++;
                                  //exit(EXIT_FAILURE);
                                } */

                                if(($1->type==FLT) && ($3->type==INT)){
                                  union num_val value;
                                  value.float_value = 0;
                                  $$ = createTempConstant(value, FLT);
                                  //$$->value.float_value = $1->value.float_value / $3->value.integer_value;
                                }
                                if(($1->type==INT) && ($3->type==FLT)){
                                  union num_val value;
                                  value.float_value = 0;
                                  $$ = createTempConstant(value, FLT);
                                  //$$->value.float_value = $1->value.integer_value / $3->value.float_value;
                                }
                              }
                            }

      | factor             { $$ = $1; }
      ;

factor: LPAREN exp RPAREN  { $$ = $2; }
      | INT_NUM            {
                              tableEntry * new_node = (tableEntry *) malloc(sizeof(tableEntry));

                              //new_node->name = g_strdup(identifier_name);
                              /* new_node->type = INT;
                              new_node->value.integer_value = $1;
                              $$ = new_node; */
                              union num_val value;
                              value.integer_value = $1;
                              $$ = createTempConstant(value, INT);
                           }
      | FLOAT_NUM          {
                              tableEntry * new_node = (tableEntry *) malloc(sizeof(tableEntry));

                              //new_node->name = g_strdup(identifier_name);
                              /* new_node->type = FLT;
                              new_node->value.float_value = $1;
                              $$ = new_node; */
                              union num_val value;
                              value.float_value = $1;
                              $$ = createTempConstant(value, FLT);
                           }
      | variable           { $$ = $1; }
      ;

variable: ID {
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
};

%%

/* Function prototype for yylex() */
int yylex();

#include "lex.yy.c"

/* Bison does NOT implement yyerror, so define it here */
void yyerror (char *string) {
  printf ("ERROR: %s in line %d\n", string, line);
  exit(EXIT_FAILURE);
}

void typeError(int line, entry_p data){
  printf("ERROR [%d]: inconsistent type for %s \n", line, data->name);
  errors ++;
  //exit(EXIT_FAILURE);
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
