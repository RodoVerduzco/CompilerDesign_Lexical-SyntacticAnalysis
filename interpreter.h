// #include "UserDefined.h"
// #include "types.h"

// #include "table.h"
#include <glib.h> // For all hashing functions
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Interpreter(GList* quadList_p, GHashTable* symTable_p);

int GOTO_QUAD(char* nexQuad);

// void PrintQuadItemValue(entry_p aEntry);