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
 * @param  lineNumber refers to the line where the symbol was defined.
 *
 * @return @c Returns the node created, or exits the program if.
 *         the element couldnt be created
 *
 * @code
 *  createSymbol(identifier_name);
 * @endcode
 *
 */
entry_p createSymbol(int type, char * identifier_name, unsigned int lineNumber) {
  entry_p node_p;        // Node to be entered in the symbol table

  // Create new table node
  tableEntry * new_node = (tableEntry *) malloc(sizeof(tableEntry));

  new_node->name = g_strdup(identifier_name);
  new_node->type = type;
  new_node->lineNo = lineNumber;

  /* Initialize every variable as 0*/
	if(type == INT)
		new_node->value.integer_value = 0;
	else {
    new_node->value.float_value = 0.0;
  }


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
entry_p addSymbol(int type, char * identifier_name, int lineNumber) {
  // lookup for the symbol on the symbol table
  entry_p lookup_symbol = g_hash_table_lookup(symTable_p, identifier_name);
  if (lookup_symbol == NULL) {
    createSymbol(type, identifier_name, lineNumber);
  }

  return lookup_symbol;

}

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
entry_p lookSymbol(char * identifier_name) {
  entry_p lookup_symbol = g_hash_table_lookup(symTable_p, identifier_name);

  if(lookup_symbol != NULL){
    return lookup_symbol;
  }
  else {
    return NULL;
  }
}

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
 *         integer_value and float_value)
 *
 * @code
 *  updateSymbol(identifier_name, FLT, 12.12);
 * @endcode
 *
 */
entry_p updateSymbol(char * identifier_name, enum myTypes type, union num_val value) {
	entry_p node = g_hash_table_lookup(symTable_p, identifier_name);
	if(node != NULL) {
		node->type = type;
		node->value = value;
	}
  return node;
}

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
entry_p createTempConstant(union num_val value, enum myTypes type) {
  char * temp = malloc(sizeof(char *));

  int i=0;
  // Assign the correct temp name
  do {
    snprintf(temp, sizeof(char *), "t%d", i);
    i++;
  } while (lookSymbol(temp) != NULL);

  createSymbol(type, temp, 0);
  return updateSymbol(temp, type, value);
}

quad_p newQuad(int op, char* arg1, char* arg2, char * dest) {
  // Create quad
  quad_p quadItem = (quad_p) malloc(sizeof(quad));
  // Set Quad Values
  quadItem->op   = op;
  quadItem->arg1 = arg1?arg1:"NULL";
  quadItem->arg2 = arg2?arg2:"NULL";
  quadItem->dest = dest?dest:"NULL";
  quadItem->addr = nextQuad;

  nextQuad ++;

  //g_array_append_val(quadArray_p, quadItem);
  printf("INSERTED    %d     %s    %s    %s      - IN  %d\n", quadItem->op, quadItem->arg1, quadItem->arg2, quadItem->dest,  quadArray_p->len);
  // g_array_insert_vals (quadArray_p,
  //                    quadArray_p->len,
  //                    quadItem,
  //                     1);
  g_array_append_vals(quadArray_p, quadItem, 1);



  // for (int i=0; i<quadArray_p->len; i++) {
  //   quad_p item = g_array_index(quadArray_p, quad_p, i);
  //   printf("item[%d] = %d\n",i, item->addr);
  // }


  return quadItem;
}

GList * newList(GList * list, quad_p quadItem){
  list = g_list_append(list, quadItem);

  return list;
}


int PrintQuads()
{
  /********
   *
   *
   * !!!!!!!!!!1CHECK SEGMENTATION FAULT ON SECOND ITERATION !!!!!!!!!!!
   *
   *
   *
   *
   * *******/


  printf("\n\nAdd  -  Operator  -  Source1  -  Source2  -  Destination\n");
  quad_p item_ = g_array_index(quadArray_p, quad_p, 0);
  printf("%s", item_->arg1);

  for (int i=0; i<quadArray_p->len; i++) {
    quad_p item = g_array_index(quadArray_p, quad_p, i);
    printf("%d", item->addr);
    // printf("%2d %11s %11d %10s %12s\n", item->addr,
    //                                     item->dest?item->dest:" ",
    //                                     item->op, item->arg1?item->arg1:" ",
    //                                     item->arg2?item->arg2:" ");
  }
}
/*
Support function needed by GLib
 */
void SupportPrintQuads(gpointer data, gpointer user_data)
{
  //PrintItemQuads(data);
}

/*
 Actual printing
 */

int PrintItemQuads(quad_p quad){
printf(" %2d   %7s   %5c   %6.5s     %4.5s     |\n",lineC++, quad->dest, quad->op, quad->arg1, quad->arg2);
  return 1;
}
