#include "aux.h"
#include "io.h"
#include <ctype.h>


// cria lista e retorna
st_lista_circular *cria_lista(void *dado)
{
    st_lista_circular *lista = NULL;

    lista = (st_lista_circular*)malloc(sizeof(st_lista_circular));
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
void insere_lista(tipo_descritor_lista *descritor, void *dado)
{
    if(!descritor) return;
    if(!dado) return;

    tipo_descritor_lista *percorrer = NULL;
    st_lista_circular *lista = NULL;

    percorrer = descritor;
    lista = cria_lista(dado);

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
void insere_antes_lista(tipo_descritor_lista *descritor, st_lista_circular *atual, void *dado)
{
    if(!descritor) return;
    if(!dado) return;
    //if(!atual) return;

    tipo_descritor_lista *percorrer = NULL;
    st_lista_circular *lista = NULL;

    percorrer = descritor;
    lista = cria_lista(dado);

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
}



// insere na lista
void insere_inicio_lista(tipo_descritor_lista *descritor, void *dado)
{
    if(!descritor) return;

    tipo_descritor_lista *percorrer = NULL;
    st_lista_circular *lista = NULL;

    percorrer = descritor;
    lista = cria_lista(dado);

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
        if (isalpha (*((char*)percorrer->dado)) || ispunct (*((char*)percorrer->dado)))
            printf("[char %c]\n", ((char*)percorrer->dado)[0]);
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
    st_lista_circular *remover = NULL;
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

	while(isalpha(linha[*i]) ||isdigit(linha[*i])) {(*i)++;}

	operando = (char *)malloc((*i - indice_inicio) * sizeof(char));

	while(indice_operando < ((*i) - indice_inicio)) {
		operando[indice_operando] = linha[indice_inicio + indice_operando];
		indice_operando++;
	}

	operando[indice_operando] = '\0';
	(*i)--;

    //printf("%s\n", operando);

	return operando;
}


// 1 Higher
int level (char *operador) {
    if (operador[0] == ')')
        return 1;
    if (operador[0] == '^')
        return 2;
    if (operador[0] == '/' || operador[0] == '*')
        return 3;
    if (operador[0] == '-' || operador[0] == '+')
        return 4;
    if (operador[0] == '(')
        return 5;
    return 0;
}



int operacao (char c)
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


float _add (float operando1, float operando2) {
    return operando1 + operando2;
}

float _sub (float operando1, float operando2) {
    return operando1 - operando2;
}

float multiplica (float operando1, float operando2) {
    return operando1 * operando2;
}

float divide (float operando1, float operando2) {

    if (operando2 == 0) {
        printf("Impossivel dividir por 0.\n");
        exit (EXIT_FAILURE);
    }

    return operando1 / operando2;
}

/*
float eleva (float operando1, float operando2) {
    return operando1  operando2;
}*/



// !TODO > sem tempo
void calcula(tipo_descritor_lista *expressao, tipo_descritor_lista *operacao, matriz_esparsa *matriz1)
{
    if(!expressao || !operacao) return;

    if(!expressao->prim || !operacao->prim) return;

    if(!matriz1) return;


    st_lista_circular *atual_operando = NULL;
    st_lista_circular *atual_operador = NULL;
    st_lista_circular *prim_operando = NULL;
    st_lista_circular *prim_operador = NULL;
    st_lista_circular *remover_operador = NULL;
    st_lista_circular *remover_operando = NULL;

    prim_operando = expressao->prim;
    prim_operador = operacao->prim;

    atual_operando = expressao->prim;
    atual_operador = operacao->prim;

    int bad_expression = 0;
    float *result = NULL;
    float operando1 = 0;
    float operando2 = 0;

    // variavel de destino
    atual_operando = get_elemento_lista (expressao, atual_operando);
    st_lista_circular *destino_resultado = atual_operando;

    while (atual_operador) {
        char *operador = (char *)atual_operador->dado;
        char *prox_operador = (char *)atual_operador->prox->dado;



        // se operando1 nao for numero
        if (!is_number (atual_operando->dado)) {
            operando1 = get_value (matriz1, atual_operando);          
        }
        else
            operando1 = *(float *)atual_operando->dado;


        // se operando2 nao for numero
        if (!is_number (atual_operando->prox->dado)) {
            operando2 = get_value (matriz1, atual_operando->prox); 
            //printf("operando2 %f\n", operando2);             
        }
        else
            operando2 = *(float *)atual_operando->prox->dado;




        // ha mais operadores
        //if (atual_operador != atual_operador->prox) {
            // prioridade do operador atual eh maior do que o proximo
            if (level (prox_operador) >= level (operador)) {


                // nao eh um numero
               // if (!atof(dado))

                // Remove operando1
                //remover_operando = atual_operando;
                //atual_operando = atual_operando->prox;
                atual_operando = get_elemento_lista (expressao, atual_operando);
                // Remove operando2
                //remover_operando = atual_operando;
                ///atual_operando = atual_operando->prox;
                atual_operando = get_elemento_lista (expressao, atual_operando);

                // aloca resultado
                result = (float*)malloc(sizeof(float));
                // calula
                switch (operador[0]) {
                    case '(' :
                        prim_operador = atual_operador;
                        break;

                    case '+' :  
                        *result = soma (operando1, operando2);

                        break;


                    //case '-' :
//
                    //case '*' :
//
                    //case '/' :

                    //case '^' :

                }

                // insere resultado na lista
                insere_antes_lista(expressao, atual_operando, result);
                // atualiza atual
                //atual_operando = atual_operando->ant;

                // remove operador
                //remover_operador = atual_operador;
                //atual_operador = atual_operador->prox;
                atual_operador = get_elemento_lista (operacao, atual_operador);     
            }
            else 
                atual_operador = atual_operador->prox;
        //}



        

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
float extrair_numero(char *string, int ind_inicio_num, char sinal)
{
    int   ind_fim_num = ind_inicio_num;
    float float_num;

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
    strncpy(string_num, &string[ind_inicio_num], (ind_fim_num - ind_inicio_num));

    // adiciona caractere de fim de string
    string_num[ind_fim_num - ind_inicio_num] = '\0';
    
    // convert string_num para float
    float_num = atof(string_num);

    if(sinal == '-')
    {
        float_num *= -1;
    }

    ind_inicio_num = ind_fim_num;
    // retorna numero
    return float_num;
}