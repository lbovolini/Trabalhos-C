/**
* Funcoes de entrada e saida
**/

#ifndef IO
#define IO

#define STRING 1
#define FLOAT 2

#include "matriz.h"
#include "funcoes.h"
#include "aux.h"


//
int imprime_matriz(matriz_esparsa *mat);


//
int ler_arquivo(matriz_esparsa **matriz1, matriz_esparsa **matriz2);


// le arquivo com as operacoes
void ler_operacoes(tipo_descritor_lista *expressao, tipo_descritor_lista *operacao);


//
int escrever_matriz(FILE *arquivo, matriz_esparsa *matriz);


// escrever no arquivo
int escrever_arquivo(matriz_esparsa *matriz1, matriz_esparsa *matriz2, matriz_esparsa *multiplicacao, matriz_esparsa *soma);


#endif