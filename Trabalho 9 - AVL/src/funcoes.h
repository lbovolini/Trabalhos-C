#ifndef FUNCOES
#define FUNCOES

#include <stdio.h>
#include <stdlib.h>


typedef struct arvore
{  
    int num,
        ht;

    struct arvore *esq,
                  *dir;
} Arvore;




Arvore *inserir(Arvore *arvore, int numero);


Arvore *remover(Arvore *arvore, int numero);


int altura(Arvore *arvore);


Arvore *rotacao_dir(Arvore *arvore);


Arvore *rotacao_esq(Arvore *arvore);


Arvore *RR(Arvore *arvore);


Arvore *LL(Arvore *arvore);


Arvore *LR(Arvore *arvore);


Arvore *RL(Arvore *arvore);


int BF(Arvore *arvore);


void preenchimento(char ch, int n);


void imprimir(Arvore *arvore, int level);


void ler_arquivo(Arvore **arvore);


#endif