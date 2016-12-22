#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fenv.h>
#include <float.h>
#include "aux.h"
#include "matriz.h"


/*
 * Get operand
 */
char *get_operando (char *linha, int *i)
{
	int indice_operando = 0,
		indice_inicio = *i;

	char *operando = NULL;

	while (isalpha (linha[*i]) || isdigit (linha[*i])) {(*i)++;}

	operando = (char *) malloc ((*i - indice_inicio) * sizeof (char));


	while (indice_operando < ((*i) - indice_inicio)) {
		operando[indice_operando] = linha[indice_inicio + indice_operando];
		indice_operando++;
	}

	operando[indice_operando] = '\0';
	(*i)--;

	return operando;
}


/*
 * Return operator priotity (1 Higher)
 */
int level (char operator) 
{
    if (operator == '^')
        return 1;
    if (operator == '/' || operator == '*')
        return 2;
    if (operator == '-' || operator == '+')
        return 3;
    if (operator == ')' || operator == '(')
        return 4;
    return 0;
}


/*
 * Chech if is operation
 */
int is_operation (char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    return 0;
}


/*
 * Check if is number
 */
int is_number (void *dado) {
    char *string = (char *)dado;

    if (isdigit(string[0]))
        return 1;
    return 0;
}


/* 
 * Get line corresponding from matrix
 */
int get_line (void *line) {
    return (int)(*((char*)line + 1)) - 48;
}


/* 
 * Get column corresponding from matrix
 */
int get_col (void *col) {
    return (int)(*((char*)col + 0)) - 64;
}


/*
 * Get value of the variable in matrix
 */
float get_value (matriz_esparsa *matriz1, st_lista_circular *operando) {

    float value = 0;

    if (!matriz1 || !operando) {
        printf ("Erro get_value()\n");
        exit (EXIT_FAILURE);
    }

    value = valor_elemento (matriz1, get_line (operando->dado), get_col (operando->dado));
    //printf("%f\n", value);

    return value;
}


/* Show default set of exception flags. */
void show_fe_exceptions (void)
{
    //printf ("current exceptions raised: ");
    if (fetestexcept (FE_DIVBYZERO))     printf (" FE_DIVBYZERO");
    //if (fetestexcept(FE_INEXACT))       printf (" FE_INEXACT");
    if (fetestexcept (FE_INVALID))       printf (" FE_INVALID");
    if (fetestexcept (FE_OVERFLOW))      printf (" FE_OVERFLOW");
    if (fetestexcept (FE_UNDERFLOW))     printf (" FE_UNDERFLOW");
    if (fetestexcept (FE_INEXACT))       return; //printf (" FE_INEXACT");
    if (fetestexcept (FE_ALL_EXCEPT)==0) return;
    //printf ("\n");
    exit (EXIT_FAILURE);
}


/*
    // se operando2 nao for numero
    if (element->prox->type == STRING) {
        operando2 = get_value (matriz1, element->prox); 
        //printf("operando2 %f\n", operando2);             
    }
    else{
        operando2 = *(float *)element->prox->dado;
        //printf("op2 %f\n", operando2);
    }*/


/*
 * Get number from string
 */
float *extrair_numero (char *string, int *ind_inicio_num, char sinal)
{
    int   ind_fim_num = *ind_inicio_num;
    float *float_num = (float *) malloc (sizeof (float));

    char  string_num[100];

    // parte inteira do numero
    while (isdigit (string[ind_fim_num]))
    {
        ind_fim_num++;
    }

    // parte fracionaria do numero
    if (string[ind_fim_num] == '.' || string[ind_fim_num] == ',')
    {
        ind_fim_num++;
        while (isdigit (string[ind_fim_num]))
        {
            ind_fim_num++;
        }
    }
    //ind_fim_num--;

    // extrai numero para string_num
    strncpy (string_num, &string[*ind_inicio_num], (ind_fim_num - *ind_inicio_num));

    // adiciona caractere de fim de string
    string_num[ind_fim_num - *ind_inicio_num] = '\0';
    
    // convert string_num para float
    *float_num = atof (string_num);

    if (sinal == '-')
    {
        *float_num *= -1;
    }

    *ind_inicio_num = ind_fim_num - 1;
    // retorna numero
    return float_num;
}