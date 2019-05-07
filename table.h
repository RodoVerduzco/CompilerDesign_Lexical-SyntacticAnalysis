/**
 * Copyright (c) 2019 José Rodolfo Verduzco Torres
 *
 * @file    table.h
 *
 * @author  José Rodolfo Verduzco Torres
 *
 * @date    11 February 2019
 *
 * @brief   Declares all the user defined functions for handling the
 *          specific user-defined data structure that is pointed to
 *          by the doubly linked list node.
 */

#include <glib.h>							// For all hashing functions
#include <string.h>           // For strcmp, strlen, strcpy
#include <stdio.h>            // For printf
#include <stdlib.h>           // For malloc

/**
 * @GHashTable
 *
 * @brief The Hash Table structure to abstract the Symbol Table, this is automatically generated by Glib.h
 *
 */
GHashTable * symTable_p;

GList * quadList_p;

int lineC;

/**
 * @union num_val
 *
 * @brief Defines the 32-bit value of a symbol table element.
 *
 * The @c num_val union defines the possible values for the elements in the
 * symbol table.
 *
 */
union num_val {              /* Note that both values are 32-bits in length */
   int     integer_value;                   /**< Interpret it as an integer */
   float   float_value;                        /**< Interpret it as a float */
};

/**
 * @enum myTypes
 *
 * @brief Enum to describe the type of the variable stored into the symbol
 *        table
 */
enum myTypes{ INT, FLT };

/**
 * @struct symTable
 *
 * @brief This is the user-defined symbol table entry.
 *
 * @c name is a string holding the name of the variable. This may be
 *    different from the hash key (the key is the variable name plus the
 *    value of the current context).
 *
 * @c value is a union of all possible values (integer/float). Not space
 *    efficient if smaller types are allowed.
 *
 * @c type indicates if the variable is integer or float.
 *
 */
typedef struct symTable {
   char           * name;               /** < The name is just the string */
   union num_val    value;        /** < Value of the symbol table element */
   enum myTypes     type;                           /** < Identifier type */
   int              lineNo;
} tableEntry;

/**
 * @typedef entry_pGList * quadList = NULL;
 *
 * @brief declare a pointer to the @c symTable @c structure
 */
typedef struct symTable * entry_p;   /**< Declaration of ptr to an entry */

/****   FOR QUADS  *****/
typedef struct lineStruct {
  int quad;
  char * name;
  enum myTypes type;
  union num_val value;
  GList * true;
  GList * false;
  GList * next;
} line_st;

typedef struct lineStruct * line_p;

typedef struct quad_ {
  int op;
  char * arg1;
  char * arg2;
  char * dest;
  int addr;
} quad;

typedef struct quad_ * quad_p;

enum operation{
    ADDITION,
    SUBSTRACTION,
    MULTIPLICATION,
    DIVISION,
    LT_GOTO,
    GT_GOTO,
    EQ_GOTO,
    GOTO,
    ASSIGNMENT
};

int nextQuad;

/* * * * * * *  Function Declarations  * * * * * * * */

/**
 *
 * @brief Performs the actions to add an element to the symbol table
 *
 * @b addSymbol is used to select the correct parameters to add to the
 *    symbol hash table, by first looking up for the symbol to see if
 *    it exists alredy.
 *
 * @param  identifier_name is a string that indicates the name of the
 *         symbol.
 *
 * @return @c if the element was created, returns the created element,
 *         else it returns the existing element
 *
 * @code
 *  addSymbol(identifier_name);
 * @endcode
 *
 */
entry_p addSymbol(int type, char * identifier_name, int lineNumber);


/**
 *
 * @brief Looks for an identifier in the symbol table
 *
 * @b lookSymbol is used to search for a variable in the symbol table
 *    by searching for an specific identifier name into the hashtable
 *
 * @param  identifier_name is a string that indicates the name of the
 *         symbol.
 *
 * @code
 *  lookSymbol(identifier_name);
 * @endcode
 *
 */
entry_p lookSymbol(char * identifier_name);

/**
 *
 * @brief Prints the contents of the symbol table entry.
 *
 * @b printTable will print each field according to the user's formatting.
 *
 * @code
 *  printTable();
 * @endcode
 *
 */
void printTable();

/**
 *
 * @brief Prints a single eitem from the Table.
 *
 * @b printItem will print each field according to the user's formatting.
 *
 * @param  theEntry_p is a pointer to a user-defined structure element.
 *
 * @code
 *  printItem(theEntry_p);
 * @endcode
 *
 */
void printItem (gpointer key, gpointer value, gpointer data);

/**
 *
 * @brief De-allocates memory assigned to user-defined data structure.
 *
 * @b FreeItem will de-allocate the @c string inside the user-defined data
 * structure @c tableEntry.
 *
 * @param  theEntry_p is a pointer to the user-defined data structure.
 * @return @c EXIT_SUCCESS if the item was de-allocated with no
 *         problems, otherwise return @c EXIT_FAILURE.
 *
 * @code
 *  FreeItem(theEntry_p);
 * @endcode
 *
 * @warning This function must be passed as a parameter when calling
 *          DestroyTable() since it will call it to de-allocate the
 *          user-defined structure.
 */
int freeItem (entry_p data);

/**
 *
 * @brief Creates a new temporary constant
 *
 * @b The createTempConstant creates a new temporary constant and adds it
 *    to the symbol table for better handling the operations within the
 *    code
 *
 * @param  value is the numerical value to be assigned to the temp (either
 *         integer_value or float_value)
 *         type is the enum containing the type for the constant (either FLT
 *         or INT)
 *
 * TODO: Handle the usage of temps
 *
 * @code
 *  createTempConstant(12.12, FLT);
 * @endcode
 *
 */
entry_p createTempConstant(union num_val value, enum myTypes type);

/**
 *
 * @brief Updates a symbol's information
 *
 * @b The updateSymbol function looks for the symbol in the hashtable
 *    and then updates the information contained
 *
 * @param  identifier_name is a string that indicates the name of the
 *         symbol.
 *         type is the enum type of the symbol (either INT [0] of FLT [1])
 *         value is the contained value for that variable (has the fields
*          integer_value and float_value)
 *
 * @code
 *  updateSymbol(identifier_name, FLT, 12.12);
 * @endcode
 *
 */
entry_p updateSymbol(char * identifier_name, enum myTypes type, union num_val value);

quad_p newQuad(int op, char * arg1, char * arg2, char * dest);

GList * newList(int quadNo);

void PrintQuads();

void PrintItemQuads(quad_p quad);

void SupportPrintQuads(gpointer data);

char * opToString(int operation);

void backpatch(GList * list, int quad);

GList * mergeList(GList * list1, GList * list2);

line_p convertToLineStruct(entry_p node);

void execute_all_program (int length, quad_p quads[]);

void execute_quad (quad_p q);
