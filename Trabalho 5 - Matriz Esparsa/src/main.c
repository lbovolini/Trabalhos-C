#include "matriz.h"


int main()
{
    matriz_esparsa *matriz1 = NULL,
                   *matriz2 = NULL;

    ler_arquivo(&matriz1, &matriz2);
    ler_operacoes(matriz1);

    printf("Matriz 1\n");
    imprime_matriz(matriz1);

    escrever_arquivo(matriz1, NULL, NULL, NULL);
    
    return 0;
}
