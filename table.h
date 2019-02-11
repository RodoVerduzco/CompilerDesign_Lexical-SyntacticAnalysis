#include <string.h>           // For strcmp, strlen, strcpy
#include <stdio.h>            // For printf
#include <glib.h>             // For all hashing functions
#include <stdlib.h>           // For malloc

/*
* Create the hash table, use the variable name (a string) as
* the hash key. Note that we use the g_hash_table_new_full to
* handle the deallocation of memory for the data structure
* through a user defined function (FreeItem)
*/
GHashTable * symTable_p;

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
 * @struct symTable
 *
 * @brief This is the user-defined symbol table entry.
 *
 * @c name_p is a string holding the name of the variable. This may be
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
   char           * name;                /**< The name is just the string */
   union num_val    value;         /**< Value of the symbol table element */
   //enum myTypes     type;                          /**< Identifier type */
} tableEntry;

/**
 * @typedef entry_p
 *
 * @brief declare a pointer to the @c tableEntry @c structure
 */
typedef struct symTable * entry_p;   /**< Declaration of ptr to an entry */

/**
 * @GHashTable
 *
 * @brief The Hash Table structure to abstract the Symbol Table, this is automatically generated by Glib.h
 *
 */
//GHashTable *table = NULL;


/* * * * * * *  Function Declarations  * * * * * * * */

entry_p addSymbol(char * identifier_name);

entry_p searchSymbol(char * string);

/**
 *
 * @brief Prints the contents of the symbol table entry.
 *
 * @b printItem will print each field according to the user's formatting.
 *
 * @param  theEntry_p is a pointer to a user-defined structure element.
 *
 * @return @c EXIT_SUCCESS the item was printed with no
 *         problems, otherwise return @c EXIT_FAILURE
 *
 * @code
 *  printItem(theEntry_p);
 * @endcode
 *
 */
void printTable();
void printItem (gpointer key, gpointer value, gpointer data);

void freeItem (entry_p data);
