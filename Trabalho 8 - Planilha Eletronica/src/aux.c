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
void insere_lista(tipo_descritor_lista *descritor, void *dado, int type)
{
    if(!descritor) return;
    if(!dado) return;

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

    // insere no fim
    percorrer->n++;
    percorrer->ult->prox = lista;
    lista->ant = percorrer->ult;
    lista->prox = percorrer->prim;
    percorrer->prim->ant = lista;
    percorrer->ult = lista;
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

	do
	{
        //if (isalpha (*((char*)percorrer->dado)) || ispunct (*((char*)percorrer->dado)))
        //if (isdigit(*((float*)percorrer->dado)))
        if (percorrer->type == STRING)
            printf("[char %s]\n", (char*)percorrer->dado);
        else
            printf("[float %f]\n", *((float*)percorrer->dado));
		
		percorrer = percorrer->prox;
	} while(percorrer != descritor->prim);
}


// remove elemento da lista e retorna
st_lista_circular *get_elemento_lista(tipo_descritor_lista *descritor, st_lista_circular *atual)
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
int level (char *operador) {

    //if (operador[0] == '(')
        //return 1;
    if (operador[0] == '^')
        return 2;
    if (operador[0] == '/' || operador[0] == '*')
        return 3;
    if (operador[0] == '-' || operador[0] == '+')
        return 4;
    if (operador[0] == ')' || operador[0] == '(')
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


// seta operador para posicao inicial e retorna numero de vezes que voltou
st_lista_circular *goto_parent (st_lista_circular *operador, int *n) {

    if (!operador) return 0;

    if (!operador->dado) return 0;

    st_lista_circular *op = operador;

    while (((char *)op->dado)[0] != '(') {
        (*n)++;
        op = op->ant;
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

// verifica se alguma operacao pode ser realizada

int is_operate (st_lista_circular **operador) {

    if (!operador) return 0;

    st_lista_circular **current = operador;

    char *current_operador = (char *)(*current)->dado;
    char *next_operador = (char *)(*current)->prox->dado;

    if ((current_operador[0] != '(')  && (next_operador[0] == '(')) return 0; 
    if ((current_operador[0] == ')')  || (next_operador[0] == ')')) return 1; // || (next_operador[0] != '(')
    if ((*current == (*current)->prox) || (level (current_operador) <= level (next_operador))) return 1;


    return 0;
}


// !TODO > sem tempo
void calcula(tipo_descritor_lista *expressao, tipo_descritor_lista *operacao, matriz_esparsa *matriz1)
{
    if(!expressao || !operacao) return;

    if(!expressao->prim || !operacao->prim) return;

    if(!matriz1) return;


    st_lista_circular *atual_operando = NULL;
    st_lista_circular *atual_operador = NULL;

    atual_operando = expressao->prim;
    atual_operador = operacao->prim;

    //int bad_expression = 0;
    float *result = NULL;
    float operando1 = 0;
    float operando2 = 0;

    // flag se ha calculo foi executado
    int calc = 0, single;

    int posicao_operando1 = 0;

    // variavel de destino
    atual_operando = get_elemento_lista (expressao, atual_operando);
    st_lista_circular *destino_resultado = atual_operando;

    while (atual_operador) {
        // set calc flag
        calc = 1; single = 0;

        char *operador = (char *)atual_operador->dado;
        char *prox_operador = (char *)atual_operador->prox->dado;

    printf ("---------\n");
    imprime_lista (operacao);
    printf ("+++++++++\n");
    imprime_lista (expressao);

        if (atual_operando) {
            // se operando1 nao for numero
            if (atual_operando->type == STRING) {
                operando1 = get_value (matriz1, atual_operando);          
            }
            else
                operando1 = *(float *)atual_operando->dado;

            // se operando2 nao for numero
            if (atual_operando->prox->type == STRING) {
                operando2 = get_value (matriz1, atual_operando->prox); 
                //printf("operando2 %f\n", operando2);             
            }
            else{
                operando2 = *(float *)atual_operando->prox->dado;
                //printf("op2 %f\n", operando2);
            }
        }

        if (is_operate (&atual_operador)) {
            // operacao
            if (is_operation (operador[0])) {

                if (((operador[0] == '(') && (prox_operador[0] == ')'))) {
                    calc = 0;
                }
                else {
                  //printf("[CCC %s]\n", (char*)atual_operador->dado);
                
                    //printf("OOOOOO\n");
                       // printf("[FFFF %f]\n", *((float*)atual_operando->dado));
                    // Remove operando1
                    atual_operando = get_elemento_lista (expressao, atual_operando);
                    // Remove operando2
                    atual_operando = get_elemento_lista (expressao, atual_operando);

                    // se ha somente um elemento na lista ele eh o primeiro
                    if (expressao->prim == expressao->ult) {
                        single = 1;
                    }

                    // aloca resultado
                    result = (float*)malloc(sizeof(float));
                }
            }

            // calula
            switch (operador[0]) {
                case '(' :
                    if (prox_operador[0] == ')') {
                        // remove operador "("
                        atual_operador = get_elemento_lista (operacao, atual_operador);     
                        // remove operador ")"
                        atual_operador = get_elemento_lista (operacao, atual_operador); 
                    }
                    else {
                        atual_operador = atual_operador->prox;
                    }
                    // set calc flag to false
                    calc = 0;
                    break;

                case '+' :  
                    *result = _add (operando1, operando2);
                    break;

                case '-' :
                    *result = _sub (operando1, operando2);
                    break;

                case '*' :
                    *result = _mul (operando1, operando2);
                    
                    break;
                
                case '/' :
                    *result = _div (operando1, operando2);
                    break;

                case '^' :
                    *result = _pow (operando1, operando2);
                    break;
                case ')' :
                    posicao_operando1 = -1;
                    //printf("[AAAAAAAA %f]\n", *((float*)atual_operando->dado));
                    //printf("[BBBBBBBB %s]\n", (char*)atual_operador->dado);
                    atual_operador = goto_parent (atual_operador, &posicao_operando1);
                    atual_operando =  voltar_operando (atual_operando, posicao_operando1);
                    //printf("vv %d\n", posicao_operando1);
                    //printf("[BBBBBBBB %s]\n", (char*)atual_operador->dado);

                    //printf("[AAAAAAAA %f]\n", *((float*)atual_operando->dado));
                    // set calc flag to false
                    calc = 0;
                    break;

                }
                // se calculo foi executado
                if (calc) {
                    
                    //printf("##########\n");
                    // se ha somente um elemento na lista ele eh o primeiro
                    if (single) {
                        insere_lista(expressao, result, FLOAT);
                    }
                    else {
                        // insere resultado na lista
                        atual_operando = insere_antes_lista (expressao, atual_operando, result, FLOAT);
                    }
                    //printf("##########\n");
                    // remove operador
                    atual_operador = get_elemento_lista (operacao, atual_operador);  
                    //printf("##########\n");
                }
            }
            else {
                //
                if (operador[0] != '('){
                    if (atual_operando)
                        atual_operando = atual_operando->prox;
                }
                if (atual_operador)
                    atual_operador = atual_operador->prox;
            }
    }


    printf ("---------\n");
    imprime_lista (operacao);
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