#include <stdio.h>
#include <stdlib.h>
#include "functionslist.h"
#include "structures.h"
#include "aux.h"
#include "list.h"


/*
 * Set operand to first left "("
 */
st_lista_circular *goto_parent (st_lista_circular *element) {

    if (!element) {
        printf ("Erro goto_parent()\n");
        exit (EXIT_FAILURE);
    }

    if (!element->dado) {
        printf ("Erro goto_parent()\n");
        exit (EXIT_FAILURE);
    }

    st_lista_circular *op = element;

    char operator = get_operator (op);
    while (operator != '(') {
        op = op->ant;
        operator = get_operator (op);
    }

    return op;
}


/*
 * Set element pointer to next operator
 */
st_lista_circular *goto_next_operator (st_lista_circular *element) {

    if (!element) {
        printf ("Erro goto_next_operator()\n");
        exit (EXIT_FAILURE);
    }

    if (!element->dado) {
        printf ("Erro goto_next_operator()\n");
        exit (EXIT_FAILURE);
    }

    st_lista_circular *op = element->prox;

    while ((op->type != OPERATOR) && (element != op)) {
        op = op->prox;
    }

    return op;
}


/*
 * Go back n operands
 */
st_lista_circular *voltar_operando (st_lista_circular *operando, int n) {

    if (!operando) return NULL;

    if (n <= 0) return operando;

    st_lista_circular *op = operando;

    while (n > 0) {
        op = op->ant;
        n--;
    }

    return op;
}


/* 
 * Return operator or null character if is not operator
 */
char get_operator (st_lista_circular *element) {

    if (!element) {
        printf ("Erro get_operator()\n");
        exit (EXIT_FAILURE);
    }

    if (element->type != OPERATOR) {
        return '\0';
    }

    return *(char *)element->dado;
}


/*
 * Return element data type
 */
int element_type (st_lista_circular *element) {

    if (!element) {
        printf ("Erro element_type()\n");
        exit (EXIT_FAILURE);
    }
    return element->type;
}


/*
 * Return next operator
 */
char get_next_operator (st_lista_circular *element) {

    if (!element) {
        printf ("Erro get_operator()\n");
        exit (EXIT_FAILURE);
    }

    if (element->type != OPERATOR) {
        printf ("Erro get_operator()\n");
        exit (EXIT_FAILURE);
    }

    st_lista_circular *current_element = NULL;
    current_element = element->prox;

    while (current_element->type != OPERATOR) {
        current_element = current_element->prox;
    }

    return *(char *)current_element->dado;
}

/* 
 * Checks if some operation can be performed
 */
int can_operate (st_lista_circular *element) {

    if (!element) return 0;

    st_lista_circular *current_element = element;

    char current_operator = *(char *)current_element->dado;
    char next_operator = get_next_operator (current_element);

    if ((current_operator != '(')  && (next_operator == '(')) return 0; 
    if ((current_operator == ')')  || (next_operator == ')')) return 1; // || (next_operador[0] != '(')
    if ((current_element == current_element->prox) || (level (current_operator) <= level (next_operator))) return 1;

    return 0;
}


/*
 * Get operand value from matriz
 */
float get_operand_value (matriz_esparsa *matriz1, st_lista_circular *element) {

    if (!element) {
        printf ("Erro get_values()\n");
        exit (EXIT_FAILURE);
    }

    // se operando nao for numero
    if (element->type == VARIABLE) {
        return get_value (matriz1, element);          
    }
    return *(float *)element->dado;
}


/* 
 * Negate operand if preceded by minus sign and remove predecesor sign
 */
void negate_operand (tipo_descritor_lista **expressao, st_lista_circular **element) 
{
    if (!(*element)) {
        printf ("Erro negative_operand()\n");
        exit (EXIT_FAILURE);
    }

    char op = get_operator ((*element)->ant);
    if ((op != '+') && (op != '-')) {
        printf ("Error op\n");
        exit (EXIT_FAILURE);
    }

    if (op == '+') {
        // remove operator "+"
        *element = get_elemento_lista (*expressao, (*element)->ant);
    }
    else if (op == '-') {
        // negate operand
        *((float*)(*element)->prox->dado) = *((float*)(*element)->prox->dado) * (-1);
        // remove operator "-"
        *element = get_elemento_lista (*expressao, (*element)->ant);
    }
}
