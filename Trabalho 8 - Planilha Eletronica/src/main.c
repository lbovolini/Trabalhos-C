#include "list.h"
#include "io.h"
#include "calculate.h"


int main()
{
    matriz_esparsa *matriz1 = NULL,
                   *matriz2 = NULL;

    tipo_descritor_lista *expressao = cria_descritor_lista();

    ler_operacoes(expressao);

    ler_arquivo(&matriz1, &matriz2);
    //ler_operacoes(matriz1);

    //printf("Matriz 1\n");
    //imprime_matriz(matriz1);

    //escrever_arquivo(matriz1, NULL, NULL, NULL);


    // /imprime_lista(expressao);
    //printf("\n");
    calcula(expressao, matriz1);
    //printf("--------------\n");
    //imprime_lista(lista);

    printf("Matriz 1\n");
    imprime_matriz(matriz1);

    escrever_arquivo(matriz1, NULL, NULL, NULL);

    return 0;
}