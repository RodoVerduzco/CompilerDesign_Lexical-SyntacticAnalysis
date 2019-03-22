 /**
  *  @file tiny.l
  *  @author  José Rodolfo Verduzco Torres || A01366134 ||
  *  @date 11 February 2019
  *
  *  @brief This program performs a lexical analysis on a c program
  *
  *  The program goes through a program written in the C programming
  *  language, and performs a lexical analysis within a subset of the
  *  sets of 'C' language, and prints a message for each token of the
  *  analyzed code showing if a reserved word, punctuation token,
  *  relational token, arithmetic operation, comment, identifier,
  *  number or unknown token was found.
  *
  */
%{
  int line = 1;
%}

 /* Define the regular expresions to be used */
 /* Reserved Words */
 /*reserved_words int|float|if|then|else|while|read|write*/
int_rw int
float_rw float
if_rw if
then_rw then
else_rw else
while_rw while
do_rw do
read_rw read
write_rw write

 /* Punctuation Tokens */
 /* punctuation_token [,]|[;]|[(]|[)]|[{]|[}] */
semi_pnct [;]
comma_pnct [,]
left_paren [(]
right_paren [)]
left_brace [{]
right_brace [}]

 /* Relational Tokens */
 /* relational_token [<]|[=]|[>]|[<=]|[>=]|[!=] */
less_than [<]
greater_than [>]
equal [=]

 /* Arithmetic Operations */
 /* arithmetic_operation [+]|[-]|[*]|[/]*/
 /* assignment_operation \:\= */
assignment \:\=
plus [+]
minus [-]
times [*]
division [/]

 /* Identifier */
identifier [A-Za-z_][A-Za-z0-9_]*

 /* Decimal Number */
decimal_number -?([1-9]([0-9])*|0)

 /* Real Number */
real_number 0(c|C)[0-7]+|0(x|X)[0-9A-Fa-f]+|[+-]?[0-9]*\.[0-9]+([eE][-+]?[0-9]+)?

 /* Ignored */
single_coment \/\/.*
multi_comment \/\*([^*]|\*+[^\/])*\*+\/
unknown [.]

/* This is the rule definition */
%%
{single_coment} {  }
{multi_comment} {
                  /* count the newlines in the comment */
                  for(int i=0; i<=strlen(yytext); i++)
                    if(yytext[i] =='\n')
                      line++;
                }

[ \t]                               /* ignore white space */

{int_rw}    {
              yylval.stringVal = strdup(yytext);
              return INTEGER;
            }

{float_rw}  {
              yylval.stringVal = strdup(yytext);
              return FLOAT;
            }

{if_rw}     {
              return IF;
            }

{then_rw}   {
              return THEN;
            }

{else_rw}   {
              return ELSE;
            }

{while_rw}  {
              return WHILE;
            }

{do_rw}     {
              return DO;
            }

{read_rw}   {
              return READ;
            }

{write_rw}  {
              return WRITE;
            }

{semi_pnct} {
              return SEMI;
            }

{comma_pnct} {
                return COMMA;
             }

{left_paren}  {
                return LPAREN;
              }

{right_paren} {
                return RPAREN;
              }

{left_brace}  {
                return LBRACE;
              }

{right_brace} {
                return RBRACE;
              }

{less_than} {
              return LT;
            }

{equal} {
          return EQ;
        }

{greater_than} {
                  return GT;
               }

{plus}       {
                return PLUS;
             }

{minus}      {
                return MINUS;
             }

{times}      {
                return TIMES;
             }

{division}   {
                return DIV;
             }

{assignment} {
                return ASSIGN;
             }

{identifier} {
                yylval.stringVal = strdup(yytext);
                return ID;
             }

{decimal_number} {
                    /* NOT YET */
                    yylval.intVal = atof(yytext);
                    return INT_NUM;
                 }

{real_number}    {
                    /* NOT YET */
                    yylval.floatVal = atof(yytext);
                    return FLOAT_NUM;
                 }

\n      { line++; }
.       { return yytext[0]; }
%%
