#include "aux.h"
#include "io.h"


// cria lista e retorna
st_lista_circular *cria_lista(void *dado, int type)
{
    st_lista_circular *lista = NULL;

    lista = (st_lista_circular*)malloc(sizeof(st_lista_circular));
    lista->type = type;
 	lista->dado = dado;
    lista->ant = lista;
    lista->prox = lista;

    return lista;
}


// cria descritor lista e retorna
tipo_descritor_lista *cria_descritor_lista(void)
{
    tipo_descritor_lista *descritor = NULL;

    if(!(descritor = (tipo_descritor_lista*)malloc(sizeof(tipo_descritor_lista))))
    {
        printf("Falta de memoria!\n");
        exit(1);
    }

    descritor->n = 0;
    descritor->prim = NULL;
    descritor->ult = NULL;

    return descritor;
}

// insere na lista
st_lista_circular *insere_lista (tipo_descritor_lista *descritor, void *dado, int type)
{
    if (!descritor || !dado) {
        printf ("Erro insere_lista()\n");
        exit (EXIT_FAILURE);
    }

    tipo_descritor_lista *percorrer = NULL;
    st_lista_circular *lista = NULL;

    percorrer = descritor;
    lista = cria_lista (dado, type);

    // lista vazia
    if(!percorrer->prim && !percorrer->ult)
    {
        percorrer->prim = lista;
        percorrer->ult = lista;
        lista->ant = lista;
        lista->prox = lista;
        percorrer->n++;
        return lista;
    }

    // insere no fim
    percorrer->n++;
    percorrer->ult->prox = lista;
    lista->ant = percorrer->ult;
    lista->prox = percorrer->prim;
    percorrer->prim->ant = lista;
    percorrer->ult = lista;

    return lista;
}


// insere na lista
st_lista_circular *insere_antes_lista(tipo_descritor_lista *descritor, st_lista_circular *atual, void *dado, int type)
{
    if(!descritor) return NULL;
    if(!dado) return NULL;
    //if(!atual) return;

    tipo_descritor_lista *percorrer = NULL;
    st_lista_circular *lista = NULL;

    percorrer = descritor;
    lista = cria_lista(dado, type);

    //printf("%s\n", (char*)lista->dado);
    // lista vazia
    if(!percorrer->prim && !percorrer->ult)
    {
        percorrer->prim = lista;
        percorrer->ult = lista;
        lista->ant = lista;
        lista->prox = lista;
        percorrer->n++;
        return lista;
    }

    // primeira
    if(atual == percorrer->prim) 
    {
        descritor->prim = lista;
    }


    // insere antes
    percorrer->n++;
    lista->ant = atual->ant;
    atual->ant->prox = lista;
    lista->prox = atual;
    atual->ant = lista;

    return lista;
}



// insere na lista
void insere_inicio_lista(tipo_descritor_lista *descritor, void *dado, int type)
{
    if(!descritor) return;

    tipo_descritor_lista *percorrer = NULL;
    st_lista_circular *lista = NULL;

    percorrer = descritor;
    lista = cria_lista(dado, type);

    //printf("%s\n", (char*)lista->dado);
    // lista vazia
    if(!percorrer->prim && !percorrer->ult)
    {
        percorrer->prim = lista;
        percorrer->ult = lista;
        lista->ant = lista;
        lista->prox = lista;
        percorrer->n++;
        return;
    }

    // insere no inicio
    percorrer->n++;

    percorrer->ult->prox = lista;
    lista->ant = percorrer->ult;
    lista->prox = percorrer->prim;
    percorrer->prim->ant = lista;
    percorrer->prim = lista;
}


// imprime lista
void imprime_lista(tipo_descritor_lista *descritor)
{
	st_lista_circular *percorrer = NULL;


	if(!descritor || !descritor->prim) return;

	percorrer = descritor->prim;

	do {
        if (percorrer->type == OPERAND) {
            printf ("[OPERAND %f]\n", *((float*)percorrer->dado));
        }
        else if (percorrer->type == OPERATOR) {
            printf("[OPERATOR %c]\n", *((char*)percorrer->dado));
        }
        else if (percorrer->type == VARIABLE) {
            printf ("[VARIABLE %s]\n", (char*)percorrer->dado);
        }
        else {
            printf ("Erro print_list()\n");
            exit (EXIT_FAILURE);
        }
		percorrer = percorrer->prox;
	} while (percorrer != descritor->prim);
}


// remove elemento da lista e retorna
st_lista_circular *get_elemento_lista (tipo_descritor_lista *descritor, st_lista_circular *atual)
{
	if(!descritor || ! atual) return NULL;

	void *dado = NULL;
    st_lista_circular *aux = NULL;

	if(atual->ant == atual)
	{
		descritor->prim = NULL;
		descritor->ult = NULL;
		descritor->n--;
		dado = atual->dado;
		atual->dado = NULL;
        //atual = NULL;
		//free(atual);

		return aux;
	}
	if(descritor->prim == atual)
	{
		descritor->prim = atual->prox;
	}
	else if(descritor->ult == atual)
	{
		descritor->ult = atual->ant;
	}

    aux = atual->prox;
	atual->prox->ant = atual->ant;
	atual->ant->prox = atual->prox;

	dado = atual->dado;
	atual->dado = NULL;
	descritor->n--;
	//free(atual);

	return aux;
}


// remove elemento da lista e retorna
void *get_elemento(tipo_descritor_lista *descritor, st_lista_circular **atual)
{
    if(!descritor || !*atual) return NULL;

    void *dado = NULL;
    st_lista_circular *p = (*atual)->ant;


    if((*atual)->ant == *atual)
    {
        descritor->prim = NULL;
        descritor->ult = NULL;
        descritor->n--;
        dado = (*atual)->dado;
        (*atual)->dado = NULL;
        *atual = p;
        //free(atual);

        return dado;
    }
    if(descritor->prim == *atual)
    {
        descritor->prim = (*atual)->prox;
    }
    else if(descritor->ult == *atual)
    {
        descritor->ult = (*atual)->ant;
    }

    (*atual)->prox->ant = (*atual)->ant;
    (*atual)->ant->prox = (*atual)->prox;

    dado = (*atual)->dado;
    (*atual)->dado = NULL;
    descritor->n--;
    *atual = p;
    //free(atual);

    return dado;
}




char *get_operando(char *linha, int *i)
{
	int indice_operando = 0,
		indice_inicio = *i;

	char *operando = NULL;

	while(isalpha(linha[*i]) || isdigit(linha[*i])) {(*i)++;}

	operando = (char *)malloc((*i - indice_inicio) * sizeof(char));


	while(indice_operando < ((*i) - indice_inicio)) {
		operando[indice_operando] = linha[indice_inicio + indice_operando];
		indice_operando++;
	}

	operando[indice_operando] = '\0';
	(*i)--;

	return operando;
}


// 1 Higher
int level (char operator) {

    //if (operador[0] == '(')
        //return 1;
    if (operator == '^')
        return 2;
    if (operator == '/' || operator == '*')
        return 3;
    if (operator == '-' || operator == '+')
        return 4;
    if (operator == ')' || operator == '(')
        return 5;
    return 0;
}



int is_operation (char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    return 0;
}

int is_number (void *dado) {
    char *string = (char *)dado;

    if (isdigit(string[0]))
        return 1;
    return 0;
}

int get_line (void *line) {
    return (int)(*((char*)line + 0)) - 64;
}

int get_col (void *col) {
    return (int)(*((char*)col + 1)) - 48;
}

float get_value (matriz_esparsa *matriz1, st_lista_circular *operando) {

    float value = 0;

    if (!matriz1 || !operando) {
        printf ("Erro get_value()\n");
        exit (EXIT_FAILURE);
    }

    value = valor_elemento(matriz1, get_col(operando->dado), get_line(operando->dado));
    //printf("%f\n", value);

    return value;
}

/* Show default set of exception flags. */
void show_fe_exceptions(void)
{
    //printf("current exceptions raised: ");
    if(fetestexcept(FE_DIVBYZERO))     printf(" FE_DIVBYZERO");
    //if(fetestexcept(FE_INEXACT))       printf(" FE_INEXACT");
    if(fetestexcept(FE_INVALID))       printf(" FE_INVALID");
    if(fetestexcept(FE_OVERFLOW))      printf(" FE_OVERFLOW");
    if(fetestexcept(FE_UNDERFLOW))     printf(" FE_UNDERFLOW");
    if(fetestexcept(FE_INEXACT))       return; //printf(" FE_INEXACT");
    if(fetestexcept(FE_ALL_EXCEPT)==0) return;
    //printf("\n");
    exit (EXIT_FAILURE);
}


float _add (float operando1, float operando2) {
    return operando1 + operando2;
}

float _sub (float operando1, float operando2) {
    return operando1 - operando2;
}

float _mul (float operando1, float operando2) {
    return operando1 * operando2;
}

float _div (float operando1, float operando2) {

    if (operando2 == 0) {
        printf("Impossivel dividir por 0.\n");
        exit (EXIT_FAILURE);
    }

    return operando1 / operando2;
}

float _pow (float operando1, float operando2) {

    float result = pow(operando1, operando2);

    // error handling
    show_fe_exceptions();
    return result;
}

// return operator or null character if is not operator
char get_operator (st_lista_circular *element) {

    if (!element) {
        printf ("Erro get_operator()\n");
        exit (EXIT_FAILURE);
    }

    if (element->type != OPERATOR) {
        //printf ("get_operator() type error\n");
        return '\0';
    }

    return *(char *)element->dado;
}


// seta operador para posicao inicial e retorna numero de vezes que voltou
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


// volta n operandos
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

// return element data type
int element_type (st_lista_circular *element) {

    if (!element) {
        printf ("Erro element_type()\n");
        exit (EXIT_FAILURE);
    }
    return element->type;
}

// return next operator
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

// verifica se alguma operacao pode ser realizada

int can_operate (st_lista_circular *element) {

    if (!element) return 0;

    st_lista_circular *current_element = element;

    char current_operator = *(char *)current_element->dado;
    char next_operator = get_next_operator (current_element);
    printf("op %c\n", current_operator);
    printf("opn %c\n", next_operator);

    if ((current_operator != '(')  && (next_operator == '(')) return 0; 
    if ((current_operator == ')')  || (next_operator == ')')) return 1; // || (next_operador[0] != '(')
    if ((current_element == current_element->prox) || (level (current_operator) <= level (next_operator))) return 1;

    return 0;
}



// TODO
// pega o valor do operando 
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
    // se operando2 nao for numero
    if (element->prox->type == STRING) {
        operando2 = get_value (matriz1, element->prox); 
        //printf("operando2 %f\n", operando2);             
    }
    else{
        operando2 = *(float *)element->prox->dado;
        //printf("op2 %f\n", operando2);
    }*/



// !TODO > sem tempo
void calcula(tipo_descritor_lista *expressao, matriz_esparsa *matriz1)
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
    element = get_elemento_lista (expressao, element);
    st_lista_circular *destino_resultado = element;


    while (expressao->n > 1) {
        // set calc flag
        calc = 1; single = 0;

    printf("++++++++++++++\n");
    imprime_lista (expressao);
    if (element->type == OPERAND) {
        printf ("[## OPERAND %f]\n", *((float*)element->dado));
    }
    else if (element->type == OPERATOR) {
        printf("[## OPERATOR %c]\n", *((char*)element->dado));
    }
    else if (element->type == VARIABLE) {
        printf ("[## VARIABLE %s]\n", (char*)element->dado);
    }

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
                        result = (float*)malloc(sizeof(float));
                    }
                }

                // calula
                switch (operator) {
                    case '(' :
                        if (get_next_operator (element) == ')') {
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
                        // go to ')'
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

    printf ("+++++++++\n");
    imprime_lista (expressao);



    //printf("Matriz 1\n");
    //imprime_matriz(matriz1);

    //escrever_arquivo(matriz1, NULL, NULL, NULL);
    
}

// extrai numero de uma string
float *extrair_numero(char *string, int *ind_inicio_num, char sinal)
{
    int   ind_fim_num = *ind_inicio_num;
    float *float_num = (float *) malloc (sizeof (float));

    char  string_num[100];

    // parte inteira do numero
    while(isdigit(string[ind_fim_num]))
    {
        ind_fim_num++;
    }

    // parte fracionaria do numero
    if(string[ind_fim_num] == '.' || string[ind_fim_num] == ',')
    {
        ind_fim_num++;
        while(isdigit(string[ind_fim_num]))
        {
            ind_fim_num++;
        }
    }
    //ind_fim_num--;

    // extrai numero para string_num
    strncpy(string_num, &string[*ind_inicio_num], (ind_fim_num - *ind_inicio_num));

    // adiciona caractere de fim de string
    string_num[ind_fim_num - *ind_inicio_num] = '\0';
    
    // convert string_num para float
    *float_num = atof(string_num);

    if(sinal == '-')
    {
        *float_num *= -1;
    }

    *ind_inicio_num = ind_fim_num - 1;
    // retorna numero
    return float_num;
}