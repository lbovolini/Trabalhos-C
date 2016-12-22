#ifndef AUX
#define AUX

#include "structures.h"


/*
 * Get operand
 */
char *get_operando (char *linha, int *i);


/*
 * Return operator priotity (1 Higher)
 */
int level (char operator);


/*
 * Chech if is operation
 */
int is_operation (char c);


/*
 * Check if is number
 */
int is_number (void *dado);


/* 
 * Get line corresponding from matrix
 */
int get_line (void *line);


/* 
 * Get column corresponding from matrix
 */
int get_col (void *col);

	
/*
 * Get value of the variable in matrix
 */
float get_value (matriz_esparsa *matriz1, st_lista_circular *operando);


/* Show default set of exception flags. */
void show_fe_exceptions (void);


/*
 * Get number from string
 */
float *extrair_numero (char *string, int *ind_inicio_num, char sinal);


#endif