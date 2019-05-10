#include "interpreter.h"
#include "table.h"

int i = 0; // Quad index;

void PrintQuadItemValue(entry_p aEntry)
{
    if (aEntry->type == INT)
        printf("\tACTION: %-10s %-4s VALUE: %-10d\n",
            "integer",
            aEntry->name,
            aEntry->value.integer_value);
    else
        printf("\tACTION: %-10s %-4s VALUE: %-10.2f\n",
            "float",
            aEntry->name,
            aEntry->value.float_value);
    return;
}

void errorAtInterpreter()
{
    printf("ERROR: At interpreter, unexpected or unknow type in QUAD = %d", i);
    return;
}

void errorDivisionByZero()
{
    printf("ERROR: Division by zero in QUAD = %d", i);
    exit(0);
    return;
}

int Interpreter(GList* quadList_p, GHashTable* symTable_p)
{
    printf("\n\nStart of Interpreter:\n");
    while (i < g_list_length(quadList_p)) {
        quad_p quadItem = g_list_nth_data(quadList_p, i);

        entry_p dest = NULL;
        entry_p arg1 = NULL;
        entry_p arg2 = NULL;

        dest = lookSymbol(quadItem->dest);
        arg1 = lookSymbol(quadItem->arg1);
        arg2 = lookSymbol(quadItem->arg2);

        switch (quadItem->op) {
        case ADDITION:
            if (arg1 == NULL && arg2 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = atoi(quadItem->arg1) + atoi(quadItem->arg2);
                } else if (dest->type == FLT) {
                    dest->value.float_value = atof(quadItem->arg1) + atof(quadItem->arg2);
                } else {
                    errorAtInterpreter();
                }
            } else if (arg2 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = arg1->value.integer_value + atoi(quadItem->arg2);
                } else if (dest->type == FLT) {
                    dest->value.float_value = arg1->value.float_value + atof(quadItem->arg2);
                } else {
                    errorAtInterpreter();
                }
            } else if (arg1 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = atoi(quadItem->arg1) + arg2->value.integer_value;
                } else if (dest->type == FLT) {
                    dest->value.float_value = atof(quadItem->arg1) + arg2->value.float_value;
                } else {
                    errorAtInterpreter();
                }
            } else {
                if (dest->type == INT) {
                    dest->value.integer_value = arg1->value.integer_value + arg2->value.integer_value;
                } else if (dest->type == FLT) {
                    dest->value.float_value = arg1->value.float_value + arg2->value.float_value;
                } else {
                    errorAtInterpreter();
                }
            }
            PrintQuadItemValue(dest);
            i++;
            break;
        case SUBSTRACTION:
            if (arg1 == NULL && arg2 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = atoi(quadItem->arg1) - atoi(quadItem->arg2);
                } else if (dest->type == FLT) {
                    dest->value.float_value = atof(quadItem->arg1) - atof(quadItem->arg2);
                } else {
                    errorAtInterpreter();
                }
            } else if (arg2 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = arg1->value.integer_value - atoi(quadItem->arg2);
                } else if (dest->type == FLT) {
                    dest->value.float_value = arg1->value.float_value - atof(quadItem->arg2);
                } else {
                    errorAtInterpreter();
                }
            } else if (arg1 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = atoi(quadItem->arg1) - arg2->value.integer_value;
                } else if (dest->type == FLT) {
                    dest->value.float_value = atof(quadItem->arg1) - arg2->value.float_value;
                } else {
                    errorAtInterpreter();
                }
            } else {
                if (dest->type == INT) {
                    dest->value.integer_value = arg1->value.integer_value - arg2->value.integer_value;
                } else if (dest->type == FLT) {
                    dest->value.float_value = arg1->value.float_value - arg2->value.float_value;
                } else {
                    errorAtInterpreter();
                }
            }
            PrintQuadItemValue(dest);
            i++;
            break;
        case DIVISION:
            if (arg1 == NULL && arg2 == NULL) {
                if (dest->type == INT) {
                    if (atoi(quadItem->arg2) == 0) {
                        errorDivisionByZero();
                    } else {
                        dest->value.integer_value = atoi(quadItem->arg1) / atoi(quadItem->arg2);
                    }
                } else if (dest->type == FLT) {
                    if (atof(quadItem->arg2) == 0.0) {
                        errorDivisionByZero();
                    } else {
                        dest->value.float_value = atof(quadItem->arg1) / atof(quadItem->arg2);
                    }
                } else {
                    errorAtInterpreter();
                }
            } else if (arg2 == NULL) {
                if (dest->type == INT) {
                    if (atoi(quadItem->arg2) == 0) {
                        errorDivisionByZero();
                    } else {
                        dest->value.integer_value = arg1->value.integer_value / atoi(quadItem->arg2);
                    }
                } else if (dest->type == FLT) {
                    if (atof(quadItem->arg2) == 0.0) {
                        errorDivisionByZero();
                    } else {
                        dest->value.float_value = arg1->value.float_value / atof(quadItem->arg2);
                    }
                } else {
                    errorAtInterpreter();
                }
            } else if (arg1 == NULL) {
                if (dest->type == INT) {
                    if (arg2->value.integer_value == 0) {
                        errorDivisionByZero();
                    } else {
                        dest->value.integer_value = atoi(quadItem->arg1) / arg2->value.integer_value;
                    }
                } else if (dest->type == FLT) {
                    if (arg2->value.float_value == 0.0) {
                        errorDivisionByZero();
                    } else {
                        dest->value.float_value = atof(quadItem->arg1) / arg2->value.float_value;
                    }
                } else {
                    errorAtInterpreter();
                }
            } else {
                if (dest->type == INT) {
                    if (arg2->value.integer_value == 0) {
                        errorDivisionByZero();
                    } else {
                        dest->value.integer_value = arg1->value.integer_value / arg2->value.integer_value;
                    }
                } else if (dest->type == FLT) {
                    if (arg2->value.float_value == 0.0) {
                        errorDivisionByZero();
                    } else {
                        dest->value.float_value = arg1->value.float_value / arg2->value.float_value;
                    }
                } else {
                    errorAtInterpreter();
                }
            }
            PrintQuadItemValue(dest);
            i++;
            break;
        case MULTIPLICATION:
            if (arg1 == NULL && arg2 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = atoi(quadItem->arg1) * atoi(quadItem->arg2);
                } else if (dest->type == FLT) {
                    dest->value.float_value = atof(quadItem->arg1) * atof(quadItem->arg2);
                } else {
                    errorAtInterpreter();
                }
            } else if (arg2 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = arg1->value.integer_value * atoi(quadItem->arg2);
                } else if (dest->type == FLT) {
                    dest->value.float_value = arg1->value.float_value * atof(quadItem->arg2);
                } else {
                    errorAtInterpreter();
                }
            } else if (arg1 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = atoi(quadItem->arg1) * arg2->value.integer_value;
                } else if (dest->type == FLT) {
                    dest->value.float_value = atof(quadItem->arg1) * arg2->value.float_value;
                } else {
                    errorAtInterpreter();
                }
            } else {
                if (dest->type == INT) {
                    dest->value.integer_value = arg1->value.integer_value * arg2->value.integer_value;
                } else if (dest->type == FLT) {
                    dest->value.float_value = arg1->value.float_value * arg2->value.float_value;
                } else {
                    errorAtInterpreter();
                }
            }
            PrintQuadItemValue(dest);
            i++;
            break;
        case ASSIGNMENT:
            if (arg1 == NULL) {
                if (dest->type == INT) {
                    dest->value.integer_value = atoi(quadItem->arg1);
                } else if (dest->type == FLT) {
                    dest->value.float_value = atof(quadItem->arg1);
                } else {
                    errorAtInterpreter();
                }
            } else {
                if (dest->type == INT) {
                    if (arg1->type == INT) {
                        dest->value.integer_value = arg1->value.integer_value;
                    } else if (arg1->type == FLT) {
                        dest->value.integer_value = arg1->value.float_value;
                    } else {
                        errorAtInterpreter();
                    }
                } else if (dest->type == FLT) {
                    if (arg1->type == INT) {
                        dest->value.float_value = arg1->value.integer_value;
                    } else if (arg1->type == FLT) {
                        dest->value.float_value = arg1->value.float_value;
                    } else {
                        errorAtInterpreter();
                    }
                } else {
                    errorAtInterpreter();
                }
            }
            PrintQuadItemValue(dest);
            i++;
            break;
        case LT_GOTO:
            if (arg2 == NULL && arg1 == NULL) {
                if (atof(quadItem->arg1) < atof(quadItem->arg2)) {
                    i = GOTO_QUAD(quadItem->dest);
                } else {
                    i++;
                }
            } else if (arg1 == NULL) {
                if (arg2->type == INT) {
                    if (atoi(quadItem->arg1) < arg2->value.integer_value) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else if (arg2->type == FLT) {
                    if (atof(quadItem->arg1) < arg2->value.float_value) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else {
                    errorAtInterpreter();
                }
            } else if (arg2 == NULL) {
                if (arg1->type == INT) {
                    if (arg1->value.integer_value < atoi(quadItem->arg2)) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else if (arg1->type == FLT) {
                    if (arg1->value.float_value < atof(quadItem->arg2)) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else {
                    errorAtInterpreter();
                }
            } else {
                if (arg1->type == INT) {
                    if (arg2->type == INT) {
                        if (arg1->value.integer_value < arg2->value.integer_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    } else {
                        if (arg1->value.integer_value < arg2->value.float_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    }
                } else {
                    if (arg2->type == INT) {
                        if (arg1->value.float_value < arg2->value.integer_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    } else {
                        if (arg1->value.float_value < arg2->value.float_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    }
                }
            }
            break;
        case GT_GOTO:
            if (arg2 == NULL && arg1 == NULL) {
                if (atof(quadItem->arg1) > atof(quadItem->arg2)) {
                    i = GOTO_QUAD(quadItem->dest);
                } else {
                    i++;
                }
            } else if (arg1 == NULL) {
                if (arg2->type == INT) {
                    if (atoi(quadItem->arg1) > arg2->value.integer_value) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else if (arg2->type == FLT) {
                    if (atof(quadItem->arg1) > arg2->value.float_value) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else {
                    errorAtInterpreter();
                }
            } else if (arg2 == NULL) {
                if (arg1->type == INT) {
                    if (arg1->value.integer_value > atoi(quadItem->arg2)) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else if (arg1->type == FLT) {
                    if (arg1->value.float_value > atof(quadItem->arg2)) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else {
                    errorAtInterpreter();
                }
            } else {
                if (arg1->type == INT) {
                    if (arg2->type == INT) {
                        if (arg1->value.integer_value > arg2->value.integer_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    } else {
                        if (arg1->value.integer_value > arg2->value.float_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    }
                } else {
                    if (arg2->type == INT) {
                        if (arg1->value.float_value > arg2->value.integer_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    } else {
                        if (arg1->value.float_value > arg2->value.float_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    }
                }
            }
            break;
        case EQ_GOTO:
            if (arg2 == NULL && arg1 == NULL) {
                if (atof(quadItem->arg1) == atof(quadItem->arg2)) {
                    i = GOTO_QUAD(quadItem->dest);
                } else {
                    i++;
                }
            } else if (arg1 == NULL) {
                if (arg2->type == INT) {
                    if (atoi(quadItem->arg1) == arg2->value.integer_value) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else if (arg2->type == FLT) {
                    if (atof(quadItem->arg1) == arg2->value.float_value) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else {
                    printf("ERROR: In equal operator");
                }
            } else if (arg2 == NULL) {
                if (arg1->type == INT) {
                    if (arg1->value.integer_value == atoi(quadItem->arg2)) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else if (arg1->type == FLT) {
                    if (arg1->value.integer_value == atof(quadItem->arg2)) {
                        i = GOTO_QUAD(quadItem->dest);
                    } else {
                        i++;
                    }
                } else {
                    errorAtInterpreter();
                }
            } else {
                if (arg1->type == INT) {
                    if (arg2->type == INT) {
                        if (arg1->value.integer_value == arg2->value.integer_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    } else {
                        if (arg1->value.integer_value == arg2->value.float_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    }
                } else {
                    if (arg2->type == INT) {
                        if (arg1->value.float_value == arg2->value.integer_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    } else {
                        if (arg1->value.float_value == arg2->value.float_value) {
                            i = GOTO_QUAD(quadItem->dest);
                        } else {
                            i++;
                        }
                    }
                }
            }
            i++;
            break;
        case READ_:
            printf("READ_OP:");
            i++;
            break;
        case WRITE_:
            printf("WRITE_OP:");
            if (dest->type == INT)
                printf("\tACTION: WRITE_ %-4s VALUE: %-10d\n",
                    dest->name,
                    dest->value.integer_value);
            else
                printf("\tACTION: WRITE_ %-4s VALUE: %-10.2f\n",
                    dest->name,
                    dest->value.float_value);
            i++;
            break;
        case GOTO:
            i = GOTO_QUAD(quadItem->dest);
            break;
        default:
            printf(
                "CRITICAL ERROR: It seems it occured in QUAD = %d\n Check if you are not creating a loop in the test file", i);
        }
    }
    printf("End of Interpreter\n\n");
    return EXIT_SUCCESS;
}

int GOTO_QUAD(char* nexQuad)
{
    char character[16];
    strcpy(character, nexQuad);
    char* tknNumber;
    tknNumber = strtok(character, "_");
    tknNumber = strtok(NULL, " ");
    printf("\tACTION: GOTO_QUAD: %d\n", atoi(tknNumber));
    return atoi(tknNumber);
}
