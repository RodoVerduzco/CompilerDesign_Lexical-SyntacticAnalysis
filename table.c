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

  printf("\n\tTest searching for an existing item for %s\n", identifier_name);

  //printTable();
  // lookup for the symbol on the symbol table
  entry_p lookup_symbol = g_hash_table_lookup(symTable_p, identifier_name);

  if (lookup_symbol != NULL) {
    printf("Found %s", identifier_name);
  	return lookup_symbol;
  }
  else {
    createSymbol(identifier_name);
  }

}
