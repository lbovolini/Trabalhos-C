#include <stdio.h>
#include "funcoes.h"

int main()
{
    FILE *saida = NULL;

    float x;
    float *polinomio1 = NULL;
    float *polinomio2 = NULL;
    float valor;

    saida = fopen("p-output.txt","w");

    if(!saida)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    ler_arquivo_polinomio(&polinomio1, &polinomio2, &x, &saida);
    //exibe_polinomio(&polinomio1, &saida);

    valor = calcula(&polinomio1, &x, 'P', &saida);
    valor = calcula(&polinomio2, &x, 'Q', &saida);

    soma(&polinomio1, &polinomio2, &x, &saida);
    subtrai(&polinomio1, &polinomio2, &x, &saida);

    derivada(&polinomio2, &x, 'Q', &saida);
    integral(&polinomio1, &x, 'P', &saida);

    printf("Fim\n");
    fprintf(saida, "Fim\n");

    fclose(saida);

    //exibe_polinomio(&polinomio1);
    //exibe_polinomio(&polinomio2);

    return 0;
}
