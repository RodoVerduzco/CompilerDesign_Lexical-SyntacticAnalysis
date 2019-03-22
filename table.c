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
int freeItem (entry_p data) {
  free(data->name);
  free(data);
  return(EXIT_SUCCESS);
}

/**
 *
 * @brief Creates a new symbol and adds it to the hash table.
 *
 * @param  identifier_name is the name of the symbol to be added.
 * @param  type refers to the enum type of the symbol.
 *
 * @return @c Returns the node created, or exits the program if.
 *         the element couldnt be created
 *
 * @code
 *  createSymbol(identifier_name);
 * @endcode
 *
 */
entry_p createSymbol(int type, char * identifier_name) {
  entry_p node_p;        // Node to be entered in the symbol table

  // Create new table node
  tableEntry * new_node = (tableEntry *) malloc(sizeof(tableEntry));

  new_node->name = g_strdup(identifier_name);
  new_node->type = type;

  /* Initialize every variable as 0*/
	if(type == INT)
		new_node->value.integer_value = 0;
	else
		new_node->value.float_value = 0.0;


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

  char type[15] ;

  if(table_node->type == INT) {
    sprintf(type, "integer");
    printf("%s \t %s \t \n",table_node->name, type);
  }
  else {
    sprintf(type, "float");
    printf("%s \t %s \t \n",table_node->name, type);
  }

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
  printf("NAME \t TYPE \t\n");
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
 * @param  type refers to the enum type of the symbol.
 *
 * @code
 *  addSymbol(identifier_name);
 * @endcode
 *
 */
entry_p addSymbol(int type, char * identifier_name) {
  // lookup for the symbol on the symbol table
  entry_p lookup_symbol = g_hash_table_lookup(symTable_p, identifier_name);

  if (lookup_symbol == NULL) {
    createSymbol(type, identifier_name);
  }

  return lookup_symbol;

}


entry_p lookSymbol(char * identifier_name) {
  entry_p lookup_symbol = g_hash_table_lookup(symTable_p, identifier_name);

  if(lookup_symbol != NULL){
    return lookup_symbol;
  }
  else {
    return NULL;
  }
}

void updateSymbol(char * identifier_name, enum myTypes type, union num_val value) {
	entry_p node = g_hash_table_lookup(symTable_p, identifier_name);
	if(node != NULL) {
		node->type = type;
		node->value = value;
	}
}

entry_p createTempConstant(union num_val value, enum myTypes type) {
  char * temp = malloc(sizeof(char *));
  char * c = malloc(sizeof(char *));

  int i=0;
  // Assign the correct temp name
  do {
    sprintf(temp, "t");
    snprintf(c, sizeof(char *), "%d", i);
    strcat(temp, c);
    i++;
  } while (lookSymbol(temp) != NULL);

  createSymbol(type, temp);
  updateSymbol(temp, type, value);

}
