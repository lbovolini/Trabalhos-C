#include "io.h"


int main()
{
    matriz_esparsa *matriz1 = NULL,
                   *matriz2 = NULL;

    tipo_descritor_lista *expressao = cria_descritor_lista();
    tipo_descritor_lista *operacao = cria_descritor_lista();

    ler_operacoes(expressao, operacao);

    ler_arquivo(&matriz1, &matriz2);
    //ler_operacoes(matriz1);

    //printf("Matriz 1\n");
    //imprime_matriz(matriz1);

    //escrever_arquivo(matriz1, NULL, NULL, NULL);


    //imprime_lista(lista);
    //printf("\n");
    //calcula(lista, matriz1);
    //printf("--------------\n");
    //imprime_lista(lista);

    return 0;
}