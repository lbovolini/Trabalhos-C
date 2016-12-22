#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "calculate.h"
#include "aux.h"
#include "list.h"
#include "functionslist.h"
#include "matriz.h"


/*
 * Sum two float numbers
 */
float _add (float operando1, float operando2) {
    return operando1 + operando2;
}


/*
 * Subtract two float numbers
 */
float _sub (float operando1, float operando2) {
    return operando1 - operando2;
}


/*
 * Multiply two float numbers
 */
float _mul (float operando1, float operando2) {
    return operando1 * operando2;
}


/*
 * Divide two float numbers
 */
float _div (float operando1, float operando2) {

    if (operando2 == 0) {
        printf("Impossivel dividir por 0.\n");
        exit (EXIT_FAILURE);
    }

    return operando1 / operando2;
}


/*
 * Power
 */
float _pow (float operando1, float operando2) {

    float result = pow(operando1, operando2);

    // error handling
    show_fe_exceptions();
    return result;
}


/*
 * Calculate given expression
 */
void calcula (tipo_descritor_lista *expressao, matriz_esparsa *matriz1)
{
    if(!expressao) return;

    if(!expressao->prim) return;

    if(!matriz1) return;


    st_lista_circular *element = expressao->prim;

    element = expressao->prim;

    //int bad_expression = 0;
    float *result = NULL;
    float first_operand = 0;
    float second_operand = 0;

    // flag se ha calculo foi executado
    int calc = 0, single;

    int posicao_operando1 = 0;

    // variavel de destino
    void *var_resul = get_element (expressao, &element);


    while (expressao->n > 1) {
        // set calc flag
        calc = 1; single = 0;

        // operador
        if (element_type (element) == OPERATOR) {

            char operator = get_operator (element);
            if (can_operate (element)) {
                // operacao
                if (is_operation (operator)) {

                    if (((operator == '(') && (operator == ')'))) {
                        calc = 0;
                    }
                    else {
                        first_operand = get_operand_value (matriz1, element->ant);
                        second_operand = get_operand_value (matriz1, element->prox);

                        if (element == expressao->prim) {
                            printf ("Erro calcula() no first operand\n");
                            exit (EXIT_FAILURE);
                        }
                        // remove first operand from list
                        element = get_elemento_lista (expressao, element->ant);
                        // remove opera from list
                        element = get_elemento_lista (expressao, element);
                        // remove second operand from list
                        element = get_elemento_lista (expressao, element);

                        // se ha somente um elemento na lista ele eh o primeiro
                        if (expressao->prim == expressao->ult) {
                            single = 1;
                        }

                        // aloca resultado
                        result = (float*) malloc (sizeof (float));
                    }
                }

                // calula
                switch (operator) {
                    case '(' :
                        if (get_next_operator (element) == ')') {
                            if (element != expressao->prim) {
                                if ((element->ant->type == OPERATOR) && (element->ant == expressao->prim)) {
                                    negate_operand (&expressao, &element); 

                                }
                                else if ((element->ant->type == OPERATOR) && (element->ant != expressao->prim) && (element->ant->ant->type == OPERATOR)) {
                                    negate_operand (&expressao, &element);
                                }
                            }


                            // remove operator "("
                            element = get_elemento_lista (expressao, element);     
                            // remove operator ")"
                            element = get_elemento_lista (expressao, element->prox);
                            // volta para operando
                            element = element->ant;
                        }
                        else {
                            element = element->prox;
                        }
                        // set calc flag to false
                        calc = 0;
                        break;

                    case '+' :  
                        *result = _add (first_operand, second_operand);
                        break;

                    case '-' :
                        *result = _sub (first_operand, second_operand);
                        break;

                    case '*' :
                        *result = _mul (first_operand, second_operand);
                        
                        break;
                    
                    case '/' :
                        *result = _div (first_operand, second_operand);
                        break;

                    case '^' :
                        *result = _pow (first_operand, second_operand);
                        break;
                    case ')' :
                        // go to '('
                        element = goto_parent (element);
                        calc = 0;
                        break;

                }
                // se calculo foi executado
                if (calc) {
                    // se ha somente um elemento na lista ou nenhum ele eh o primeiro
                    if (single) {
                        element = insere_lista(expressao, result, OPERAND);
                    }
                    // are more then one element in list
                    else {
                        // insere resultado na lista
                        element = insere_antes_lista (expressao, element, result, OPERAND);
                    }
                    element = goto_next_operator (element);  
                }
            }
            else {
                element = goto_next_operator (element); 
            }
        }
        else
            element = element->prox;
    } 

/*
    if (element->type != OPERAND) {
        printf ("Erro calculate()\n");
        exit (EXIT_FAILURE);
    }
    *result = *((float*)element->dado);

    if (result == 0) {
        remove_elemento (matriz1, get_line (var_resul), get_col (var_resul));

    } else {
        // se elemento nao existe
        if (altera_elemento (matriz1, get_line (var_resul), get_col (var_resul), *result)) {
            insere_ordenado (matriz1, get_line (var_resul), get_col (var_resul), *result);
        }

    }*/
}