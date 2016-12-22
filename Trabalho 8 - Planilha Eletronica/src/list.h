#ifndef LIST
#define LIST

#include "structures.h"

/* 
 * Create list
 */
st_lista_circular *cria_lista (void *dado, int type);


/*
 * Create list descriptor
 */
tipo_descritor_lista *cria_descritor_lista (void);


/*
 * Insert data into list
 */
st_lista_circular *insere_lista (tipo_descritor_lista *descritor, void *dado, int type);


/*
 * Insert data before current list element
 */
st_lista_circular *insere_antes_lista(tipo_descritor_lista *descritor, st_lista_circular *atual, void *dado, int type);


/*
 * Insert data into first position of list
 */
void insere_inicio_lista(tipo_descritor_lista *descritor, void *dado, int type);


/*
 * Print list
 */
void imprime_lista(tipo_descritor_lista *descritor);


/*
 * Remove element from list
 */
st_lista_circular *get_elemento_lista (tipo_descritor_lista *descritor, st_lista_circular *atual);


/*
 * Remove element from list and return it
 */
void *get_element (tipo_descritor_lista *descritor, st_lista_circular **atual);


#endif