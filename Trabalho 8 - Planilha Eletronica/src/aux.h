#ifndef AUX
#define AUX

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>


typedef struct lista_circular 
{
    void *dado;
    struct lista_circular *ant, 
                          *prox;
} st_lista_circular ;


typedef struct
{
    int n; // numero de elementos da lista
    st_lista_circular *prim, 
                      *ult;
} tipo_descritor_lista;


#include "aux.h"
#include "io.h"


// cria lista e retorna
st_lista_circular *cria_lista(void *dado);


// cria descritor lista e retorna
tipo_descritor_lista *cria_descritor_lista(void);


// insere na lista
void insere_lista(tipo_descritor_lista *descritor, void *dado);


// insere na lista
void insere_inicio_lista(tipo_descritor_lista *descritor, void *dado);


// imprime lista
void imprime_lista(tipo_descritor_lista *descritor);


// remove elemento da lista e retorna
void *get_elemento_lista(tipo_descritor_lista *descritor, st_lista_circular *atual);


char *get_operando(char *linha, int *i);


int operacao(char c);



void calcula(tipo_descritor_lista *expressao, matriz_esparsa *matriz1);


// extrai numero de uma string
float extrair_numero(char *string, int ind_inicio_num, char sinal);


#endif