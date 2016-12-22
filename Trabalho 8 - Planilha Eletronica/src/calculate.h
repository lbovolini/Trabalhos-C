#ifndef CALCULATE
#define CALCULATE

#include "structures.h"


/*
 * Sum two float numbers
 */
float _add (float operando1, float operando2) ;


/*
 * Subtract two float numbers
 */
float _sub (float operando1, float operando2) ;


/*
 * Multiply two float numbers
 */
float _mul (float operando1, float operando2) ;


/*
 * Divide two float numbers
 */
float _div (float operando1, float operando2) ;


/*
 * Power
 */
float _pow (float operando1, float operando2) ;


/*
 * Calculate given expression
 */
void calcula(tipo_descritor_lista *expressao, matriz_esparsa *matriz1);


#endif