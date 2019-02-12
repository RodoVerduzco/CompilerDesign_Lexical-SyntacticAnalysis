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

void freeItem (entry_p data) {
  free(data);
}

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

void printItem(gpointer key, gpointer value, gpointer data) {
	tableEntry * table_node = (tableEntry *) value;
	printf("%s\n",table_node->name);
}

void printTable() {
  printf("> > > SYMBOL TABLE < < < \n");
  printf("NAME\n");
  g_hash_table_foreach(symTable_p, (GHFunc)printItem, NULL);
}

entry_p addSymbol(char * identifier_name) {
  // lookup for the symbol on the symbol table
  entry_p lookup_symbol = g_hash_table_lookup(symTable_p, identifier_name);

  if (lookup_symbol != NULL) {
  	return lookup_symbol;
  }
  else {
    createSymbol(identifier_name);
  }

}
