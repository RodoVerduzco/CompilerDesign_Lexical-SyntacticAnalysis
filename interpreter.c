#include "interpreter.h"
#include "table.h"

int i = 0;
char j;

int Interpreter(GList *quadList_p, GHashTable *symTable_p)
{
	while (i < g_list_length(quadList_p))
	{
		quad_p quadItem = g_list_nth_data(quadList_p, i);

		entry_p dest = NULL;
		entry_p arg1 = NULL;
		entry_p arg2 = NULL;

		switch (quadItem->op)
		{
			case DIVISION:
				//printf("Prueba /\n");
				arg1 = lookSymbol(quadItem->arg1);
				arg2 = lookSymbol(quadItem->arg2);
				dest = lookSymbol(quadItem->dest);
				//if(atoi(quadItem->arg2) == 0 || atof(quadItem->arg2) == 0.0 ){
				//printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n",i);
				//  exit(0);
				//}
				/*
									if(arg2->type == FLT){
										if(arg2->value.float_value == 0.0){
											printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n",i);
											exit(0);
										}
									}
									else if(arg2->type == INT){
										if(arg2->value.integer_value == 0){
											printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n",i);
											exit(0);
										}
									}
									*/

				if (arg1 == NULL && arg2 == NULL)
				{
					if (dest->type == INT)
					{
						if (atoi(quadItem->arg2) == 0)
						{
							printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n", i);
							exit(0);
						}
						else
						{
							dest->value.integer_value = atoi(quadItem->arg1) / atoi(quadItem->arg2);
						}
					}
					else if (dest->type == FLT)
					{
						if (atof(quadItem->arg2) == 0.0)
						{
							printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n", i);
							exit(0);
						}
						else
						{
							dest->value.float_value = atof(quadItem->arg1) / atof(quadItem->arg2);
						}
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else if (arg2 == NULL)
				{
					if (dest->type == INT)
					{
						if (atoi(quadItem->arg2) == 0)
						{
							printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n", i);
							exit(0);
						}
						else
						{
							dest->value.integer_value = arg1->value.integer_value / atoi(quadItem->arg2);
						}
					}
					else if (dest->type == FLT)
					{
						if (atof(quadItem->arg2) == 0.0)
						{
							printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n", i);
							exit(0);
						}
						else
						{
							dest->value.float_value = arg1->value.float_value / atof(quadItem->arg2);
						}
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else if (arg1 == NULL)
				{
					if (dest->type == INT)
					{
						if (arg2->value.integer_value == 0)
						{
							printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n", i);
							exit(0);
						}
						else
						{
							dest->value.integer_value = atoi(quadItem->arg1) / arg2->value.integer_value;
						}
					}
					else if (dest->type == FLT)
					{
						if (arg2->value.float_value == 0.0)
						{
							printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n", i);
							exit(0);
						}
						else
						{
							dest->value.float_value = atoi(quadItem->arg1) / arg2->value.float_value;
						}
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else
				{
					if (dest->type == INT)
					{
						if (arg2->value.integer_value == 0)
						{
							printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n", i);
							exit(0);
						}
						else
						{
							dest->value.integer_value = arg1->value.integer_value / arg2->value.integer_value;
						}
					}
					else if (dest->type == FLT)
					{
						if (arg2->value.float_value == 0.0)
						{
							printf("\n[ERROR]. DIVISION BY ZERO ON QUAD %d. \n\n", i);
							exit(0);
						}
						else
						{
							dest->value.float_value = arg1->value.float_value / arg2->value.float_value;
						}
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				i++;
				break;
			case MULTIPLICATION:
				//printf("Prueba *\n");
				dest = lookSymbol(quadItem->dest);
				arg1 = lookSymbol(quadItem->arg1);
				arg2 = lookSymbol(quadItem->arg2);
				if (arg1 == NULL && arg2 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = atoi(quadItem->arg1) * atoi(quadItem->arg2);
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = atof(quadItem->arg1) * atof(quadItem->arg2);
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else if (arg2 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = arg1->value.integer_value * atoi(quadItem->arg2);
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = arg1->value.float_value * atof(quadItem->arg2);
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else if (arg1 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = atoi(quadItem->arg1) * arg2->value.integer_value;
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = atoi(quadItem->arg1) * arg2->value.float_value;
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = arg1->value.integer_value * arg2->value.integer_value;
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = arg1->value.float_value * arg2->value.float_value;
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				i++;
				break;
			case ADDITION:
				//printf("Prueba +\n");
				// printf("des: %s arg1: %s arg2: %s", quadItem->dest, quadItem->arg1, quadItem->arg2);
				dest = lookSymbol(quadItem->dest);
				arg1 = lookSymbol(quadItem->arg1);
				arg2 = lookSymbol(quadItem->arg2);
				if (arg1 == NULL && arg2 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = atoi(quadItem->arg1) + atoi(quadItem->arg2);
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = atof(quadItem->arg1) + atof(quadItem->arg2);
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else if (arg2 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = arg1->value.integer_value + atoi(quadItem->arg2);
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = arg1->value.float_value + atof(quadItem->arg2);
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else if (arg1 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = atoi(quadItem->arg1) + arg2->value.integer_value;
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = atoi(quadItem->arg1) + arg2->value.float_value;
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = arg1->value.integer_value + arg2->value.integer_value;
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = arg1->value.float_value + arg2->value.float_value;
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				i++;
				break;
			case SUBSTRACTION:
				//printf("Prueba -\n");
				dest = lookSymbol(quadItem->dest);
				arg1 = lookSymbol(quadItem->arg1);
				arg2 = lookSymbol(quadItem->arg2);
				if (arg1 == NULL && arg2 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = atoi(quadItem->arg1) - atoi(quadItem->arg2);
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = atof(quadItem->arg1) - atof(quadItem->arg2);
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else if (arg2 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = arg1->value.integer_value - atoi(quadItem->arg2);
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = arg1->value.float_value - atof(quadItem->arg2);
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else if (arg1 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = atoi(quadItem->arg1) - arg2->value.integer_value;
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = atoi(quadItem->arg1) - arg2->value.float_value;
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = arg1->value.integer_value - arg2->value.integer_value;
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = arg1->value.float_value - arg2->value.float_value;
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				i++;
				break;
			case ASSIGNMENT:
				//printf("Prueba =\n");
				dest = lookSymbol(quadItem->dest);
				arg1 = lookSymbol(quadItem->arg1);

				if (arg1 == NULL)
				{
					if (dest->type == INT)
					{
						dest->value.integer_value = atoi(quadItem->arg1);
					}
					else if (dest->type == FLT)
					{
						dest->value.float_value = atof(quadItem->arg1);
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else
				{
					if (dest->type == INT)
					{
						if (arg1->type == INT)
						{
							dest->value.integer_value = arg1->value.integer_value;
						}
						else if (arg1->type == FLT)
						{
							dest->value.integer_value = arg1->value.float_value;
						}
						else
						{
							printf("Unexpected type error");
						}
					}
					else if (dest->type == FLT)
					{
						if (arg1->type == INT)
						{
							dest->value.float_value = arg1->value.integer_value;
						}
						else if (arg1->type == FLT)
						{
							dest->value.float_value = arg1->value.float_value;
						}
						else
						{
							printf("Unexpected type error");
						}
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				i++;
				break;
			case LT_GOTO:
				//printf("Prueba <\n");
				arg1 = lookSymbol(quadItem->arg1);
				arg2 = lookSymbol(quadItem->arg2);
				if (arg2 == NULL && arg1 == NULL)
				{
					if (atof(quadItem->arg1) < atof(quadItem->arg2))
					{
						i = GotoLine(quadItem->dest);
						//printf("Goto %d", i);
					}
					else
					{
						i++;
					}
				}
				else if (arg1 == NULL)
				{
					if (arg2->type == INT)
					{
						if (atoi(quadItem->arg1) < arg2->value.integer_value)
						{
							i = GotoLine(quadItem->dest);
						}
						else
						{
							i++;
						}
					}
					else if (arg2->type == FLT)
					{
						if (atof(quadItem->arg1) < arg2->value.float_value)
						{
							i = GotoLine(quadItem->dest);
						}
						else
						{
							i++;
						}
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else if (arg2 == NULL)
				{
					if (arg1->type == INT)
					{
						if (arg1->value.integer_value < atoi(quadItem->arg2))
						{
							i = GotoLine(quadItem->dest);
						}
						else
						{
							i++;
						}
					}
					else if (arg1->type == FLT)
					{
						//printf("%f < %f", arg1->value.float_value, atof(quadItem->arg2));
						if (arg1->value.float_value < atof(quadItem->arg2))
						{
							i = GotoLine(quadItem->dest);
						}
						else
						{
							i++;
						}
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else
				{
					if (arg1->type == INT)
					{
						if (arg2->type == INT)
						{
							if (arg1->value.integer_value < arg2->value.integer_value)
							{
								i = GotoLine(quadItem->dest);
								//printf("Goto %d", i);
							}
							else
							{
								i++;
								//printf("Goto %d", i);
							}
						}
						else
						{
							if (arg1->value.integer_value < arg2->value.float_value)
							{
								i = GotoLine(quadItem->dest);
							}
							else
							{
								i++;
							}
						}
					}
					else
					{
						if (arg2->type == INT)
						{
							if (arg1->value.float_value < arg2->value.integer_value)
							{
								i = GotoLine(quadItem->dest);
							}
							else
							{
								i++;
							}
						}
						else
						{
							if (arg1->value.float_value < arg2->value.float_value)
							{
								i = GotoLine(quadItem->dest);
							}
							else
							{
								i++;
							}
						}
					}
				}
				break;
			case EQ_GOTO:
				//printf("Prueba <\n");
				arg1 = lookSymbol(quadItem->arg1);
				arg2 = lookSymbol(quadItem->arg2);
				if (arg2 == NULL && arg1 == NULL)
				{
					if (atof(quadItem->arg1) == atof(quadItem->arg2))
					{
						i = GotoLine(quadItem->dest);
						//printf("Goto %d", i);
					}
					else
					{
						i++;
					}
				}
				else if (arg1 == NULL)
				{
					if (arg2->type == INT)
					{
						if (atoi(quadItem->arg1) == arg2->value.integer_value)
						{
							i = GotoLine(quadItem->dest);
						}
						else
						{
							i++;
						}
					}
					else if (arg2->type == FLT)
					{
						if (atof(quadItem->arg1) == arg2->value.float_value)
						{
							i = GotoLine(quadItem->dest);
						}
						else
						{
							i++;
						}
					}
					else
					{
						printf("Unexpected type error or values not numeric");
					}
				}
				else if (arg2 == NULL)
				{
					if (arg1->type == INT)
					{
						if (arg1->value.integer_value == atoi(quadItem->arg2))
						{
							i = GotoLine(quadItem->dest);
						}
						else
						{
							i++;
						}
					}
					else if (arg1->type == FLT)
					{
						if (arg1->value.integer_value == atof(quadItem->arg2))
						{
							i = GotoLine(quadItem->dest);
						}
						else
						{
							i++;
						}
					}
					else
					{
						printf("Unexpected type error");
					}
				}
				else
				{
					if (arg1->type == INT)
					{
						if (arg2->type == INT)
						{
							if (arg1->value.integer_value == arg2->value.integer_value)
							{
								i = GotoLine(quadItem->dest);
								// printf("Goto %d", i);
							}
							else
							{
								i++;
								// printf("Goto %d", i);
							}
						}
						else
						{
							if (arg1->value.integer_value == arg2->value.float_value)
							{
								i = GotoLine(quadItem->dest);
							}
							else
							{
								i++;
							}
						}
					}
					else
					{
						if (arg2->type == INT)
						{
							if (arg1->value.float_value == arg2->value.integer_value)
							{
								i = GotoLine(quadItem->dest);
							}
							else
							{
								i++;
							}
						}
						else
						{
							if (arg1->value.float_value == arg2->value.float_value)
							{
								i = GotoLine(quadItem->dest);
							}
							else
							{
								i++;
							}
						}
					}
				}
				i++;
				break;
			// case 'j':
			case GOTO:
				//printf("Prueba j\n");
				i = GotoLine(quadItem->dest);
				//printf("Goto %d", i);
				break;
			default:
				printf("Error it seems it was in i=%d Quad\n",i);
		}
	}
	return EXIT_SUCCESS;
}

int GotoLine(char *g)
{
	char chars[16];
	strcpy(chars, g);
	char *token;
	token = strtok(chars, "_");
	token = strtok(NULL, " ");
	printf("GO TO LINE: %d\n", atoi(token));
	return atoi(token);
}