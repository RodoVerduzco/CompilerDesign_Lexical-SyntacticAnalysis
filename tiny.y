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
#define  YYERROR_VERBOSE

  /* Function definitions */
extern int line;
extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror(char const * string);
void typeError(int line, line_p data);

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
  line_p lineStruct_p;
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

%nonassoc IF_CONFLICT
%nonassoc ELSE

 /* Numbers */
%token <intVal> INT_NUM
%token <floatVal> FLOAT_NUM

 /* Identifier */
%token <stringVal>ID


%type <intVal> type;
%type <lineStruct_p> variable factor term simple_exp exp stmt_seq block stmt N M;


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

stmt_seq: %empty                            {
                                              $$ = (line_p) malloc(sizeof(line_st));
                                              $$->next = NULL;
                                            }
          |stmt_seq M stmt                  {
                                              $$ = (line_p) malloc(sizeof(line_st));
                                              $$->next = NULL;

                                              $$->next = mergeList($1->next, $3->next);
                                            }
          ;

 stmt: IF exp THEN M stmt %prec IF_CONFLICT N {
                                              /*
                                               * Code
                                               *    backpatch(E.t, M.quad)
                                               *    S.next = merge(E.f, S.next))
                                               *
                                               */
                                               $$ = (line_p) malloc(sizeof(line_st));
                                               backpatch($2->true, $4->quad);
                                               $$->next = mergeList($2->false, $5->next);
                                            }
      | IF exp THEN M stmt N ELSE M stmt    {
                                              /*
                                              * Code
                                              *    backpatch(E.t, M.quad)
                                              *    backpatch(E.f, M2.quad)
                                              *    S->next = merge(S1->next, merge(N.next, S2.next))
                                              */
                                              $$ = (line_p) malloc(sizeof(line_st));

                                              backpatch($2->true, $4->quad);
                                              backpatch($2->false, $8->quad);

                                              $$->next = mergeList($5->next, mergeList($6->next, $9->next));

                                              backpatch($$->next, nextQuad);
                                            }
      | WHILE M exp DO M stmt               {
                                              /*
                                               * Code
                                               *  backpatch(E.t, M2.quad)
                                               *  S.next = e.f;
                                               *  gen(goto m1.quad)
                                               *
                                               */
                                              $$ = (line_p) malloc(sizeof(line_st));
                                              backpatch($3->true, $5->quad);
                                              backpatch($3->false, nextQuad+1);

                                              $$->next = $3->false;

                                              char * dest = malloc(sizeof(char *));
                                              sprintf(dest, "goto_%d", $2->quad);

                                              newQuad(GOTO, "NULL", "NULL", dest);
                                            }
      | variable ASSIGN simple_exp SEMI     {
                                              if(($1->type == FLT) && ($3->type == FLT)) {
                                                union num_val value;
                                                value.float_value = $3->value.float_value;

                                                newQuad(ASSIGNMENT, $3->name, NULL, $1->name);
                                              }
                                              else if(($1->type == INT)&& ($3->type == INT)) {
                                                union num_val value;
                                                value.integer_value = $3->value.integer_value;

                                                newQuad(ASSIGNMENT, $3->name, NULL, $1->name);
                                              }
                                              else {

                                                if(($1->type == INT) && ($3->type == FLT)) {
                                                  yyerror("Loss of Precision. Casting Float to Integer.");
                                                  $$->value.integer_value = (int) $3->value.float_value;
                                                  newQuad(ASSIGNMENT, $3->name, NULL, $1->name);
                                                  //IntegerToReal(theTable_p, $1->place);
                                                }
                                                else if(($1->type == FLT) && ($3->type == INT)){
                                                  yyerror("Warning, implicit casting between int and float");

                                                  $1->value.float_value    = (float) $3->value.integer_value;
                                                  newQuad(ASSIGNMENT, $3->name, NULL, $1->name);

                                                }
                                                else {
                                                  typeError(line, $1);
                                                }
                                              }
                                            };
      | READ LPAREN variable RPAREN SEMI    {  }
      | WRITE LPAREN exp RPAREN SEMI        {  }
      | block                               {
                                              $$ = (line_p) malloc(sizeof(line_st));
                                              $$->next = NULL;
                                              $$->next = $1->next;
                                            }
      ;

block : LBRACE stmt_seq RBRACE              {
                                              $$ = (line_p) malloc(sizeof(line_st));
                                              $$->next = NULL;
                                              $$->next = $2->next;
                                            };

exp: simple_exp LT simple_exp               {
                                              /*
                                               * Code:
                                               *     E.t = newList(nextQuad)
                                               *     E.f = newList(nextQuad +1)
                                               *     gen(if id1.place < id2.place goto_)
                                               *     get(goto_)
                                               */
                                              $$ = (line_p) malloc(sizeof(line_st));
                                              $$->name = "goto_";

                                              $$->true  = newList(nextQuad);
                                              newQuad(LT_GOTO, $1->name, $3->name, "goto_");

                                              $$->false = newList(nextQuad);
                                              newQuad(GOTO, "NULL", "NULL", "goto_");
                                            }
      | simple_exp EQ simple_exp            {
                                              /*
                                               * Code:
                                               *     E.t = newList(nextQuad)
                                               *     E.f = newList(nextQuad +1)
                                               *     gen(if id1.place < id2.place goto_)
                                               *     get(goto_)
                                               */
                                              $$ = (line_p) malloc(sizeof(line_st));
                                              $$->name = "goto_";

                                              $$->true  = newList(nextQuad);
                                              newQuad(EQ_GOTO, $1->name, $3->name, "goto_");

                                              $$->false = newList(nextQuad);
                                              newQuad(GOTO, "NULL", "NULL", "goto_");

                                            }
      | simple_exp GT simple_exp            {
                                                                                            /*
                                               * Code:
                                               *     E.t = newList(nextQuad)
                                               *     E.f = newList(nextQuad +1)
                                               *     gen(if id1.place < id2.place goto_)
                                               *     get(goto_)
                                               */
                                               $$ = (line_p) malloc(sizeof(line_st));
                                               $$->name = "goto_";

                                               $$->true  = newList(nextQuad);
                                               newQuad(GT_GOTO, $1->name, $3->name, "goto_");

                                               $$->false = newList(nextQuad);
                                               newQuad(GOTO, "NULL", "NULL", "goto_");
                                            }
      | simple_exp                          { $$ = $1; }
      ;

simple_exp: simple_exp PLUS term            {
                                              entry_p temp = NULL;

                                              // Type Checking
                                              if(($1->type==INT) && ($3->type==INT)) {
                                                union num_val value;
                                                value.float_value = 0;

                                                // Create Temp
                                                temp = createTempConstant(value, INT);
                                              }
                                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                                union num_val value;
                                                value.float_value = 0;

                                                // Create Temp
                                                temp = createTempConstant(value, FLT);
                                              }
                                              // Coersion
                                              else {
                                                if($$->type == FLT) {
                                                  if(($1->type==FLT) && ($3->type==INT)) {
                                                    union num_val value;
                                                    value.float_value = 0;

                                                    // Create Temp
                                                    temp = createTempConstant(value, FLT);
                                                  }
                                                  if(($1->type==INT) && ($3->type==FLT)) {
                                                    union num_val value;
                                                    value.float_value = 0;

                                                    // Create Temp
                                                    temp = createTempConstant(value, FLT);
                                                  }
                                                }
                                                else {
                                                  typeError(line, convertToLineStruct(temp));
                                                }
                                              }

                                              $$ = convertToLineStruct(temp);
                                              newQuad(ADDITION, $1->name, $3->name, temp->name);
                                            }
      | simple_exp MINUS term               {
                                              entry_p temp = malloc(sizeof(tableEntry));

                                              if(($1->type==INT) && ($3->type==INT)) {
                                                union num_val value;
                                                value.integer_value = 0;
                                                temp = createTempConstant(value, INT);

                                                newQuad(SUBSTRACTION, $1->name, $3->name, temp->name);
                                              }
                                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                                union num_val value;
                                                value.float_value = 0;
                                                temp = createTempConstant(value, FLT);

                                                newQuad(SUBSTRACTION, $1->name, $3->name, temp->name);
                                              }
                                              // Coersion
                                              else {
                                                printf("MIN - Coersion [%d] for %s and %s\n", line, $1->name, $3->name);
                                                if($$->type == FLT) {
                                                  if(($1->type==FLT) && ($3->type==INT)){
                                                    union num_val value;
                                                    value.float_value = 0;
                                                    temp = createTempConstant(value, FLT);

                                                    newQuad(SUBSTRACTION, $1->name, $3->name, temp->name);
                                                  }
                                                  if(($1->type==INT) && ($3->type==FLT)){
                                                    union num_val value;
                                                    value.float_value = 0;
                                                    temp = createTempConstant(value, FLT);

                                                    newQuad(SUBSTRACTION, $1->name, $3->name, temp->name);
                                                  }
                                                }
                                                else {
                                                  typeError(line, convertToLineStruct(temp));
                                                }
                                              }

                                                $$ = convertToLineStruct(temp);
                                            }
      | term                                { $$ = $1; }
      ;

term: term TIMES factor                     {
                                              entry_p temp = malloc(sizeof(tableEntry));

                                              if(($1->type==INT) && ($3->type==INT)) {
                                                union num_val value;
                                                value.integer_value = 0;
                                                temp = createTempConstant(value, INT);

                                                newQuad(MULTIPLICATION, $1->name, $3->name, temp->name);
                                              }
                                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                                union num_val value;
                                                value.float_value = 0;
                                                temp = createTempConstant(value, FLT);

                                                newQuad(MULTIPLICATION, $1->name, $3->name, temp->name);
                                              }
                                              // Coersion
                                              else {
                                                printf("MULT - Coersion [%d] for %s and %s\n", line, $1->name, $3->name);

                                                if(($1->type==FLT) && ($3->type==INT)){
                                                  union num_val value;
                                                  value.float_value = 0;
                                                  temp = createTempConstant(value, FLT);

                                                  newQuad(MULTIPLICATION, $1->name, $3->name, temp->name);
                                                }
                                                if(($1->type==INT) && ($3->type==FLT)){
                                                  union num_val value;
                                                  value.float_value = 0;
                                                  temp = createTempConstant(value, FLT);

                                                  newQuad(MULTIPLICATION, $1->name, $3->name, temp->name);
                                                }
                                              }

                                              $$ = convertToLineStruct(temp);
                                           }
      | term DIV factor                    {
                                              entry_p temp = malloc(sizeof(tableEntry));

                                              if(($1->type==INT) && ($3->type==INT)) {
                                                union num_val value;
                                                value.float_value = 0;
                                                temp = createTempConstant(value, INT);

                                                newQuad(DIVISION, $1->name, $3->name, temp->name);
                                              }
                                              else if(($1->type==FLT) && ($3->type==FLT)) {
                                                union num_val value;
                                                value.float_value = 0;
                                                temp = createTempConstant(value, FLT);

                                                newQuad(DIVISION, $1->name, $3->name, temp->name);
                                              }
                                              // Coersion
                                              else {
                                                printf("DIV - Coersion [%d] for %s and %s\n", line, $1->name, $3->name);

                                                if(($1->type==FLT) && ($3->type==INT)){
                                                  union num_val value;
                                                  value.float_value = 0;
                                                  temp = createTempConstant(value, FLT);

                                                  newQuad(DIVISION, $1->name, $3->name, temp->name);
                                                }
                                                if(($1->type==INT) && ($3->type==FLT)){
                                                  union num_val value;
                                                  value.float_value = 0;
                                                  temp = createTempConstant(value, FLT);

                                                  newQuad(DIVISION, $1->name, $3->name, temp->name);
                                                }
                                              }

                                              $$ = convertToLineStruct(temp);
                                            }

      | factor                              { $$ = $1; }
      ;

factor: LPAREN exp RPAREN                   { $$ = $2; }
      | INT_NUM                             {
                                              entry_p node = malloc(sizeof(tableEntry));

                                              node->name = malloc(sizeof(char *));
                                              node->type = INT;
                                              node->value.integer_value = $1;
                                              sprintf(node->name, "%d", $1);

                                              $$ = convertToLineStruct(node);
                                            }
      | FLOAT_NUM                           {
                                              entry_p node = malloc(sizeof(tableEntry));

                                              node->name = malloc(sizeof(char *));
                                              node->type = FLT;
                                              node->value.float_value = $1;
                                              sprintf(node->name, "%f", $1);

                                              $$ = convertToLineStruct(node);
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
                                                      $$ = convertToLineStruct(node);
                                                }
                                            }
        ;
  /* Backpatching grammar */
  M: %empty                                 {
                                                // Add the quad address
                                                // Code:
                                                //    M.quad = nextQuad
                                                $$ = (line_p) malloc(sizeof(line));
                                                $$->quad = nextQuad;
                                            }
         ;

  N: %empty                                 {
                                                // Code:
                                                //    N.next_list = newList(nextQuad)
                                                //    gen('goto _')
                                                $$ = (line_p) malloc(sizeof(line_st));
                                                $$->next  = newList(nextQuad);
                                                newQuad(GOTO, NULL, NULL, "goto_");

                                            };

%%

/* Function prototype for yylex() */
int yylex();

#include "lex.yy.c"

/* Bison does NOT implement yyerror, so define it here */
void yyerror (char const * string) {
  char * stderr;
  printf ("ERROR: %s in line %d\n", string, line);
  //exit(EXIT_FAILURE);
}

void typeError(int line, line_p data){
  printf("ERROR [%d]: inconsistent type for %s \n", line, data->name);
  errors ++;
  exit(EXIT_FAILURE);
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


  PrintQuads();

  // Destroy the hash table
  g_hash_table_destroy(symTable_p);
  return(EXIT_SUCCESS);
}
