/**
 *  @file tiny.y
 *  @author  José Rodolfo Verduzco Torres || A01366134 ||
 *  @date 02 October 2018
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
extern int line;

 /* Removes the warning of yylex() not defined when using C99 */
#if YYBISON
    union YYSTYPE;
    int yylex();     // Should be int yylex(union YYSTYPE *, void *);
#endif

%}

%union {
  int  intVal;
  float floatVal;
  char * stringVal;
  entry_p symp;
}

  /*  *  *  Token Definition  *  *  */

/* NOT YET
  %token <intVal> INT_NUMBER      // FLOAT_NUMBER is used for float numbers
  %token <floatVal> FLOAT_NUMBER  // INT_NUMBER is used for decimal numbers
  %token <stringVal> NAME         // NAME is used for identifier tokens
  %token <symp> SYMP              // SYMP is used for symbol table entry
*/

 /* Reserved Words*/
%token INTEGER
%token FLOAT
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
%token ID

%%

 /*  *  *  *  Grammar definition  *  *  *  */
program: var_dec stmt_seq {
                            printf("No errors in the Program\n");
                          };

var_dec: var_dec single_dec
      |
      ;

single_dec: type ID SEMI;

type: INTEGER
      | FLOAT
      ;

stmt_seq: stmt_seq stmt
      |
      ;

stmt: IF exp THEN stmt
      | IF exp THEN stmt ELSE stmt
      | WHILE exp DO stmt
      | variable ASSIGN exp SEMI
      | READ LPAREN variable RPAREN SEMI
      | WRITE LPAREN exp RPAREN SEMI
      | block
      ;

block : LBRACE stmt_seq RBRACE;

exp: simple_exp LT simple_exp
      | simple_exp EQ simple_exp
      | simple_exp
      ;

simple_exp: simple_exp PLUS term
      | simple_exp MINUS term
      | term
      ;

term: term TIMES factor
      | term DIV factor
      | factor
      ;

factor: LPAREN exp RPAREN
      | INT_NUM
      | FLOAT_NUM
      | variable
      ;

variable: ID ;

%%

/* Function prototype for yylex() */
int yylex();

#include "lex.yy.c"

/* Bison does NOT implement yyerror, so define it here */
void yyerror (char *string) {
  printf ("ERROR: %s in line %d\n", string, line);
}

/* Bison does NOT define the main entry point so define it here */
int main (void) {
  // Create the hashtable
  symTable_p  = g_hash_table_new_full(g_str_hash, g_str_equal,
                                      NULL,
                                      (GDestroyNotify)freeItem);

  // Perform the parsing
  yyparse();

  printTable();
  // Destroy the hash table
  g_hash_table_destroy(symTable_p);
}
