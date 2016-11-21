#include "funcoes.h"


int main()
{
    Arvore *arvore = NULL;

    int numero, 
        operacao;

    ler_arquivo(&arvore);
    printf("Arquivo lido!\n");

    do
    {

        printf("\n1 - Inserir \n2 - Remover \n3 - Mostrar \n0 - Sair\n");
        scanf("%d", &operacao);

        switch(operacao)
        {
            case 1:
                printf("\nInforme o numero: ");
                scanf("%d", &numero);

                if(numero < -1000 || numero > 1000) {
                    printf("Numero deve ser maior que -1000 e menor que 1000.\n");
                    break;
                }

                arvore = inserir(arvore, numero);
                break;

            case 2:
                printf("\nInforme o numero: ");
                scanf("%d", &numero);

                arvore = remover(arvore, numero);
                break;

            case 3:
                imprimir(arvore, 0);
                break;
        }
    }while(operacao != 0);

    return 0;
}