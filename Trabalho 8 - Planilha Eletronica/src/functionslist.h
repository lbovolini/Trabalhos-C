#ifndef FUNCTIONS_LIST
#define FUNCTIONS_LIST

#include "structures.h"


/*
 * Set operand to first left "("
 */
st_lista_circular *goto_parent (st_lista_circular *element);


/*
 * Set element pointer to next operator
 */
st_lista_circular *goto_next_operator (st_lista_circular *element);


/*
 * Go back n operands
 */
st_lista_circular *voltar_operando (st_lista_circular *operando, int n);


/* 
 * Return operator or null character if is not operator
 */
char get_operator (st_lista_circular *element);


/*
 * Return element data type
 */
int element_type (st_lista_circular *element);


/*
 * Return next operator
 */
char get_next_operator (st_lista_circular *element);


/* 
 * Checks if some operation can be performed
 */
int can_operate (st_lista_circular *element);


/*
 * Get operand value from matriz
 */
float get_operand_value (matriz_esparsa *matriz1, st_lista_circular *element);


/* 
 * Negate operand if preceded by minus sign and remove predecesor sign
 */
void negate_operand (tipo_descritor_lista **expressao, st_lista_circular **element);


#endif