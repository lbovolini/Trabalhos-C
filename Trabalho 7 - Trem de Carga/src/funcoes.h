#ifndef FUNCOES
#define FUNCOES

#include <stdio.h>
#include <stdlib.h>


#define MAX 40

// Struct do Vagao
typedef struct vagao
{
	int carga;
	struct vagao *prox;
} Vagao;


// Struct do Trem
typedef struct trem
{
	int n_vagoes;
	Vagao *ult_vagao;
} Trem;


// Cria vagao
Vagao *criar_vagao(int carga);


// Cria trem
Trem *criar_trem();


/* Se tiver lugar vago insere carga no ultimo vagao, 
se não possuir, adiciona mais um vagão. */
int inserir_carga(Trem *trem, int carga);


/* Remove uma quantidade de carga a partir do ultimo vagão. 
Se a quantidade de carga removida esvazia o vagão, 
ele é removido do trem. Recursivamente */
int remover_carga(Trem *trem, int carga);


// Exibe vagoes e a quantidade de carga de cada um
int imprimir_trem(Trem *trem);


#endif