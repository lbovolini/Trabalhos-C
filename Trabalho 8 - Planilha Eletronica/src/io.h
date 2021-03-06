/**
* Funcoes de entrada e saida
**/

#ifndef IO
#define IO

#include <stdio.h>
#include "structures.h"

//
int imprime_matriz(matriz_esparsa *mat);


//
int ler_arquivo(matriz_esparsa **matriz1, matriz_esparsa **matriz2);


// le arquivo com as operacoes
void ler_operacoes(tipo_descritor_lista *expressao);


//
int escrever_matriz(FILE *arquivo, matriz_esparsa *matriz);


// escrever no arquivo
int escrever_arquivo(matriz_esparsa *matriz1, matriz_esparsa *matriz2, matriz_esparsa *multiplicacao, matriz_esparsa *soma);


#endif