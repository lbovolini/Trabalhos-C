#include "aux.h"
#include "io.h"


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
        printf("[%s]\n", (char*)percorrer->dado);
		printf("[%f]\n", *((float*)percorrer->dado));
		percorrer = percorrer->prox;
	} while(percorrer != descritor->prim);
}


// remove elemento da lista e retorna
void *get_elemento_lista(tipo_descritor_lista *descritor, st_lista_circular *atual)
{
	if(!descritor || ! atual) return NULL;

	void *dado = NULL;
    st_lista_circular *remover = NULL;

	if(atual->ant == atual)
	{
		descritor->prim = NULL;
		descritor->ult = NULL;
		descritor->n--;
		dado = atual->dado;
		atual->dado = NULL;
		//free(atual);

		return dado;
	}
	if(descritor->prim == atual)
	{
		descritor->prim = atual->prox;
	}
	else if(descritor->ult == atual)
	{
		descritor->ult = atual->ant;
	}

	atual->prox->ant = atual->ant;
	atual->ant->prox = atual->prox;

	dado = atual->dado;
	atual->dado = NULL;
	descritor->n--;
	//free(atual);

	return dado;
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

	return operando;
}





int operacao(char c)
{
    if(c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
        return 1;
    return 0;
}

// !TODO > sem tempo
void calcula(tipo_descritor_lista *expressao, matriz_esparsa *matriz1)
{
    if(!expressao) return;

    if(!expressao->prim) return;

    if(!matriz1) return;

    float operador1, operador2;

    float *res = NULL;

tipo_descritor_lista *o = cria_descritor_lista();
    st_lista_circular *percorrer = expressao->prim;
    st_lista_circular *inicio = expressao->prim;
    st_lista_circular *atual = NULL;


    while(expressao->n > 2)
    {
        //printf("%c\n", *((char*)percorrer->dado)+0 );
        atual = percorrer->prox;

        if(operacao(*((char*)percorrer->dado) + 0)) 
        {
                 //               printf("(((( %c ))))\n", *((char*)percorrer->dado) + 0);

            char *operador = (char*)get_elemento(expressao, &percorrer);
                //    printf("(((( %c ))))\n", *((char*)percorrer->dado) + 0);

            //printf("%s\n", operador);

            void *op2 = get_elemento(expressao, &percorrer);

           // printf("OP2 = %s\n", op2);

            void *op1 = get_elemento(expressao, &percorrer);

             //       printf("(((( %c ))))\n", *((char*)percorrer->dado) + 0);

            //printf("OP1 = %s\n", op1);

                  //  printf("(((( %c ))))\n", *((char*)percorrer->dado) + 0);

            //percorrer = percorrer->prox;

                 //   printf("(((( %c ))))\n", *((char*)percorrer->dado) + 0);

            //printf("O))))) - %c\n", *((char*)op1));

            if(!isalpha(*((char*)op1))) {
                //operador2 = extrair_numero(op2, 0, '+');
                operador2 = *((float*)op2);
            }
            else {
                operador2 = valor_elemento(matriz1, (int)(*((char*)op2 + 1)) - 48, (int)(*((char*)op2 + 0)) - 64);
            }

            if(!isalpha(*((char*)op1))) {
                //operador1 = extrair_numero(op1, 0, '+');
                operador1 = *((float*)op1);
            }
            else {
                operador1 = valor_elemento(matriz1, (int)(*((char*)op1 +1)) - 48, (int)(*((char*)op1 + 0)) - 64);
            }
           // printf("OP1 - %f\n", operador1);
           // printf("OP2 - %f\n", operador2);

            res = (float*)malloc(sizeof(float));
                 //   printf("(((( %c ))))\n", *((char*)percorrer->dado) + 0);


            switch(operador[0]) 
            {
                case '+':
                    *res = operador1 + operador2;
                  //  printf("%f\n", *res);
                    insere_antes_lista(expressao, atual, res);
                    break;

                case '-':
                    *res = operador1 - operador2;
                    //printf("%f\n", *res);
                    insere_antes_lista(expressao, atual, res);
                    break;

                case '*':
                    *res = operador1 * operador2;
                    //printf("%f\n", *res);
                    insere_antes_lista(expressao, atual, res);
                    break;

                case '/':
                    if(operador2 == 0) {
                        printf("Impossivel dividir por 0.\n");
                        exit(0);
                    }
                    *res = operador1 / operador2;
                    //printf("%f\n", *res);
                    insere_antes_lista(expressao, atual, res);
                    break;

                case '^':
                    *res = pow(operador1, operador2);
                    //printf("%f\n", *res);
                    insere_antes_lista(expressao, atual, res);
                    break;
            }
            percorrer = atual->ant;
        }
        percorrer = percorrer->prox;
    } 

    percorrer = expressao->prim;
    void *result = get_elemento(expressao, &percorrer);
    char *dest = (char*)get_elemento(expressao, &percorrer);
    float resultado;

    if(!isalpha(*((char*)result)))
    {
        resultado = *((float*)result);
    }
    else {
        resultado = valor_elemento(matriz1, (int)(*((char*)result +1)) - 48, (int)(*((char*)result + 0)) - 64);
    }

    //printf("%f\n", resultado);

    if(resultado == 0)
    {
        remove_elemento(matriz1, dest[1]- 48, ((int)dest[0]) - 64);
    }
    else
    {
        // se elemento nao existe
        if(altera_elemento(matriz1, dest[1]- 48, ((int)dest[0]) - 64, resultado))
        {
            insere_ordenado(matriz1, dest[1]- 48, ((int)dest[0]) - 64, resultado);
        }

    }

    printf("Matriz 1\n");
    imprime_matriz(matriz1);

    escrever_arquivo(matriz1, NULL, NULL, NULL);
    
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