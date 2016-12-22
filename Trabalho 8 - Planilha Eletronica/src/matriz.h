/**
* Funcoes da matriz
**/


#ifndef MATRIZ
#define MATRIZ


#include "structures.h"


// aloca matriz_esparsa e retorna
matriz_esparsa *cria_matriz_esparsa(int i, int j);


// aloca elemento e retorna
tipo_celula *cria_celula(int linha, int coluna, float valor);


// insere um elemento na matriz
int insere(matriz_esparsa *mat, int linha, int coluna, float valor);


// insere um elemento na matriz de forma ordenada
int insere_ordenado(matriz_esparsa *mat, int linha, int coluna, float valor);


// remove elemento 
int remove_elemento(matriz_esparsa *mat, int linha, int coluna);


// altera o valor de um elemento na matriz
int altera_elemento(matriz_esparsa *mat, int linha, int coluna, float valor);


// retorna valor do elemento, zero se nao encontrado
float valor_elemento(matriz_esparsa *mat, int linha, int coluna);


#endif