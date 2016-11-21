#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int numeros[40];

typedef struct elemento
{
    int valor;
    char naipe;
} st_elemento;


typedef struct lista_circular 
{
    int visivel; // campo para definir se o elemento deve ficar visível ou não
    st_elemento *carta;
    struct lista_circular *ant, 
                          *prox;
} st_lista_circular ;


typedef struct pilha 
{
    st_elemento *carta;
    int visivel; // campo para definir se o elemento deve ficar visível ou não
    struct pilha *prox;
} st_pilha;


typedef struct
{
    int n; // numero de elementos da lista
    st_lista_circular *prim, 
                      *ult;
} tipo_descritor_lista;


typedef struct
{
    int n; // numero de elementos da pilha
    st_pilha *topo;
} tipo_descritor_pilha;


void gera_numeros ();


int valor_carta (int i);


char naipe_carta (int i);


// aloca elemento e retorna
st_elemento *cria_elemento(int valor, char naipe);


// aloca lista circular e retorna
st_lista_circular *cria_lista_circular(int visivel);


// cria descritor pilha e retorna
tipo_descritor_pilha *cria_descritor_pilha(void);


// cria pilha e retorna
st_pilha *cria_pilha(st_elemento *carta, int visivel);


// insere na pilha
void insere_pilha(tipo_descritor_pilha *descritor_pilha, st_elemento *elemento, int visivel);


// imprime pilha
void imprime(tipo_descritor_pilha *descritor, int n);


// insere no inicio
tipo_descritor_pilha *insere_inicio(tipo_descritor_pilha *descritor_pilha);


//imprime pilha invertida
void imprime_pilha_invertida(tipo_descritor_pilha *descritor_pilha[], int n);


// remove elemento da pilha
void remove_pilha(tipo_descritor_pilha *descritor_pilha);


// cria descritor lista e retorna
tipo_descritor_lista *cria_descritor_lista(void);


// insere na lista
void insere_lista(tipo_descritor_lista *descritor, st_elemento *carta, int visivel);


// cria lista e retorna
st_lista_circular *cria_lista(st_elemento *carta, int visivel);


// imprime lista
void imprime_lista(tipo_descritor_lista *descritor);


// imprime elemento da lista
void imprime_elemento_lista(st_lista_circular *atual);


// remove elemento da pilha e retorna
st_elemento *get_elemento_pilha(tipo_descritor_pilha *descritor_pilha);


// remove elemento da lista e retorna
st_elemento *get_elemento_lista(tipo_descritor_lista *descritor, st_lista_circular *atual);


// verifica se as cartas podem ser empilhadas na pilha de fileiras
int possivel_mover_fileira(st_elemento *elemento1, st_elemento *elemento2);


// retorna elemento do topo da pilha
st_elemento *consulta_pilha(tipo_descritor_pilha *descritor_pilha);


// verifica se as cartas podem ser empilhadas na pilha de naipe
int possivel_mover_naipe(st_elemento *elemento1, st_elemento *elemento2);


// verifica se o jogador venceu a partida
int venceu(tipo_descritor_pilha *descritor_pilha[], int n);