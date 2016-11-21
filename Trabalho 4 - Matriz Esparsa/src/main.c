#include "matriz.h"


int main()
{
    matriz_esparsa *matriz1 = NULL,
                   *matriz2 = NULL,
                   *multiplicacao = NULL,
                   *soma = NULL;

    ler_arquivo(&matriz1, &matriz2);

    printf("Matriz 1\n");
    imprime_matriz(matriz1);
    printf("\nMatiz 2 \n");
    imprime_matriz(matriz2);

    soma = soma_matriz(matriz1, matriz2);
    printf("\nSoma\n");
    imprime_matriz(soma);

    multiplicacao = multiplica_matriz(matriz1, matriz2);
    printf("\nMultiplicacao\n");
    imprime_matriz(multiplicacao);

    escrever_arquivo(matriz1, matriz2, multiplicacao, soma);
    
    return 0;
}
