#ifndef FUNCOES
#define FUNCOES

#include <stdio.h>
#include <stdlib.h>


typedef struct st_celula
{
  struct st_celula *prox;

  int   lin, 
        col;

  float val;

} tipo_celula;


typedef struct tipo_matriz_esparsa
{
  int i, 
      j;

  tipo_celula *prim_celula, 
              *ult_celula;

} matriz_esparsa;



// aloca matriz_esparsa e retorna
matriz_esparsa *cria_matriz_esparsa(int i, int j);


// aloca elemento e retorna
tipo_celula *cria_celula(int linha, int coluna, float valor);


// insere um elemento na matriz
int insere(matriz_esparsa *mat, int linha, int coluna, float valor);


// altera o valor de um elemento na matriz
int altera_elemento(matriz_esparsa *mat, int linha, int coluna, float valor);

//
int imprime_matriz(matriz_esparsa *mat);


//
int ler_arquivo(matriz_esparsa **matriz1, matriz_esparsa **matriz2);


// le arquivo com as operacoes
void ler_operacoes();


// retorna valor do elemento, zero se nao encontrado
float valor_elemento(matriz_esparsa *mat, int linha, int coluna);


// retorna o resultado da multiplicacao de duas matrizes
matriz_esparsa *multiplica_matriz(matriz_esparsa *matriz1, matriz_esparsa *matriz2);


// retorna o resultado da soma de duas matrizes
matriz_esparsa *soma_matriz(matriz_esparsa *matriz1, matriz_esparsa *matriz2);


//
int escrever_matriz(FILE *arquivo, matriz_esparsa *matriz);


// escrever no arquivo
int escrever_arquivo(matriz_esparsa *matriz1, matriz_esparsa *matriz2, matriz_esparsa *multiplicacao, matriz_esparsa *soma);


// remove a quebra de linha do final da string
void remover_quebra_linha(char *string);


// remove "lixo" do inicio da string, retorn indice de inicio da string
int limpar_string(char *string);


#endif
