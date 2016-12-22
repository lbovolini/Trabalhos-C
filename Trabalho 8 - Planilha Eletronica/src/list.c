#include <stdio.h>
#include <stdlib.h>
#include "list.h"


/* 
 * Create list
 */
st_lista_circular *cria_lista (void *dado, int type)
{
    st_lista_circular *lista = NULL;

    lista = (st_lista_circular*) malloc (sizeof (st_lista_circular));
    lista->type = type;
 	lista->dado = dado;
    lista->ant = lista;
    lista->prox = lista;

    return lista;
}


/*
 * Create list descriptor
 */
tipo_descritor_lista *cria_descritor_lista (void)
{
    tipo_descritor_lista *descritor = NULL;

    if (!(descritor = (tipo_descritor_lista*) malloc (sizeof (tipo_descritor_lista))))
    {
        printf ("Falta de memoria!\n");
        exit (EXIT_FAILURE);
    }

    descritor->n = 0;
    descritor->prim = NULL;
    descritor->ult = NULL;

    return descritor;
}


/*
 * Insert data into list
 */
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


/*
 * Insert data before current list element
 */
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


/*
 * Insert data into first position of list
 */
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


/*
 * Print list
 */
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


/*
 * Remove element from list
 */
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


/*
 * Remove element from list and return data
 */
void *get_element (tipo_descritor_lista *descritor, st_lista_circular **atual)
{
    if(!descritor || !*atual) return NULL;

    void *dado = (*atual)->dado;

    if((*atual)->ant == *atual) {
        descritor->prim = NULL;
        descritor->ult = NULL;
        descritor->n--;
        *atual = NULL;

        return dado;
    }
    if(descritor->prim == *atual) {
        descritor->prim = (*atual)->prox;
    }
    else if(descritor->ult == *atual) {
        descritor->ult = (*atual)->ant;
    }

    (*atual)->prox->ant = (*atual)->ant;
    (*atual)->ant->prox = (*atual)->prox;
    descritor->n--;

    return dado;
}
