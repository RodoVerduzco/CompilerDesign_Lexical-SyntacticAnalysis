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

#include "table.h"

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
void freeItem (entry_p data) {
  free(data->name);
  free(data);
}

/**
 *
 * @brief Creates a new symbol and adds it to the hash table.
 *
 * @param  identifier_name is the name of the symbol to be added.
 *
 * @return @c Returns the node created, or exits the program if.
 *         the element couldnt be created
 *
 * @code
 *  createSymbol(identifier_name);
 * @endcode
 *
 */
entry_p createSymbol(char * identifier_name) {
  entry_p node_p;        // Node to be entered in the symbol table

  // Create new table node
  tableEntry * new_node = (tableEntry *) malloc(sizeof(tableEntry));

  new_node->name = g_strdup(identifier_name);
  /* Will add the value and type correcty in a more advanced implementation */
  //new_node->value = 0;
  if(g_hash_table_insert(symTable_p, new_node->name, new_node)) {
    return new_node;
  }
  else {
    printf("Error: While inserting the node");
    exit(EXIT_FAILURE);
  }
}

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
void printItem(gpointer key, gpointer value, gpointer data) {
	tableEntry * table_node = (tableEntry *) value;
	printf("%s\n",table_node->name);
}

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
void printTable() {
  printf("> > > SYMBOL TABLE < < < \n");
  printf("NAME\n");
  g_hash_table_foreach(symTable_p, (GHFunc)printItem, NULL);
}

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
 * @code
 *  addSymbol(identifier_name);
 * @endcode
 *
 */
entry_p addSymbol(char * identifier_name) {
  // lookup for the symbol on the symbol table
  entry_p lookup_symbol = g_hash_table_lookup(symTable_p, identifier_name);

  if (lookup_symbol != NULL) {
  	return lookup_symbol;
  }
  else {
    return createSymbol(identifier_name);
  }
}
