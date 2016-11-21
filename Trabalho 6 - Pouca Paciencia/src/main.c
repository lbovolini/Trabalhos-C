//!TODO organizar

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdio_ext.h> // __fpurge();
#include "funcoes.h"

int main()
{
    tipo_descritor_pilha *pilha_naipe[4]; 
    tipo_descritor_pilha *pilha_fileira[7];

    tipo_descritor_lista *estoque = NULL;
    st_lista_circular *percorrer = NULL;
    st_elemento *carta = NULL;

    int i = 0, n = 0, j = 0, sair = 0;

    int origem_pi, destino_pi, acao, valido = 0;
    char origem_p, destino_p;
 
    //printf("intervalo da rand: [0,%d]\n", RAND_MAX);

    gera_numeros();

    //for(i = 0 ; i < 40 ; i++)
    //    printf("Num %d: %d %d%c\t",i+1, numeros[i], valor_carta(i), naipe_carta(i));


    // cria e inicializa 4 pilhas de naipe
    for(i = 0; i < 4; i++)
    {
        pilha_naipe[i] = cria_descritor_pilha();
    }

    // cria 7 pilhas de fileira
    for(i = 0; i < 7; i++)
    {
        pilha_fileira[i] = cria_descritor_pilha();
    }

    // cria lista de estoque
    //estoque = cria_lista();

    // inicializa 7 pilhas de fileira
    for(i = 0; i < 7; i++)
    {
        for(j = 0; j <= i; j++)
        {
            carta = cria_elemento(valor_carta(n), naipe_carta(n));
            insere_pilha(pilha_fileira[i], carta, i == j);
            n++;
        }
    }

    // inicializa descritor lista
    estoque = cria_descritor_lista();

    // inicializa lista de estoque com as cartas restantes
    for(n = 28; n < 40; n++)
    {
        carta = cria_elemento(valor_carta(n), naipe_carta(n));
        insere_lista(estoque, carta, 1);
    }
    percorrer = estoque->prim;

    system("clear");
    while(!sair)
    {
        printf("=L0=");
        printf("\t\t\t");
        for(i = 0; i < 4; i++)
        {
            printf("=A%d=\t", i);
        }

        printf("\n");
        imprime_elemento_lista(percorrer);

        printf("\t\t\t");
        for(i = 0; i < 4; i++)
        {
            imprime(pilha_naipe[i], i);
        }

        printf("\n\n");
        imprime_pilha_invertida(pilha_fileira, 7);
        printf("Selecione uma acao:\n1 - Consultar lista de estoque\n2 - Mover cartas\n3 - Sair\n");
        __fpurge(stdin); // for unix
        scanf("%d", &acao);
        if(acao == 1)
        {
            if(percorrer)
                percorrer = percorrer->prox;
        }
        else if(acao == 2)
        {
            
            printf("Origem: ");
            __fpurge(stdin); // for unix
            scanf("%c%d", &origem_p, &origem_pi);
            printf("Destino: ");
            __fpurge(stdin); // for unix
            scanf("%c%d", &destino_p, &destino_pi);

            origem_p = toupper(origem_p);
            destino_p = toupper(destino_p);

            // verifica se as entradas sao validas
            if(origem_p == 'P' && origem_pi >= 0 && origem_pi < 7)
            {
                valido = 1;
            }
            else if(origem_p == 'A' && origem_pi >= 0 && origem_pi < 4)
            {
                valido = 1;
            }
            else if(origem_p == 'L' && origem_pi == 0)
            {
                valido = 1;
            }
            else valido = 0;

            if(destino_p == 'P' && destino_pi >= 0 && destino_pi < 7)
            {
                valido++;
            }
            else if(destino_p == 'A' && destino_pi >= 0 && destino_pi < 4)
            {
                valido++;
            }
            else valido = 0;

            // entradas validas
            if(valido == 2)
            {
                // lista de estoque
                if(origem_p == 'L' && percorrer)
                {
                    // pilha de naipe
                    if(destino_p == 'A')
                    {
                        if(possivel_mover_naipe(
                            percorrer->carta, 
                            consulta_pilha(pilha_naipe[destino_pi])))
                        {
                            carta = get_elemento_lista(estoque, percorrer);
                            percorrer = estoque->prim;

                            insere_pilha(pilha_naipe[destino_pi], carta, 1);
                        }
                    }
                    // pilha de fileira
                    else if(destino_p == 'P')
                    {
                        if(possivel_mover_fileira(
                            percorrer->carta, 
                            consulta_pilha(pilha_fileira[destino_pi])))
                        {
                            carta = get_elemento_lista(estoque, percorrer);
                            percorrer = estoque->prim;

                            insere_pilha(pilha_fileira[destino_pi], carta, 1);
                        }
                    }
                }
                // pilha de naipe
                else if(origem_p == 'A')
                {
                    //pilha_naipe[origem_pi]
                    if(destino_p == 'P')
                    {
                        if(possivel_mover_fileira(consulta_pilha(pilha_naipe[origem_pi]), 
                            consulta_pilha(pilha_fileira[destino_pi])))
                        {
                            carta = get_elemento_pilha(pilha_naipe[origem_pi]);

                            insere_pilha(pilha_fileira[destino_pi], carta, 1);
                        }
                    }
                }
                // pilha de fileira
                else if(origem_p == 'P')
                {
                    // pilha de naipe
                    if(destino_p == 'A')
                    {
                        if(possivel_mover_naipe(consulta_pilha(pilha_fileira[origem_pi]), 
                            consulta_pilha(pilha_naipe[destino_pi])))
                        {
                            carta = get_elemento_pilha(pilha_fileira[origem_pi]);

                            insere_pilha(pilha_naipe[destino_pi], carta, 1);
                        }
                    }
                    // pilha de fileira
                    else if(destino_p == 'P')
                    {
                        if(possivel_mover_fileira(
                            consulta_pilha(pilha_fileira[origem_pi]), 
                            consulta_pilha(pilha_fileira[destino_pi])))
                        {
                            carta = get_elemento_pilha(pilha_fileira[origem_pi]);

                            insere_pilha(pilha_fileira[destino_pi], carta, 1);
                        }
                    }
                }
            }
        }
        else if(acao == 3)
            sair = 1;

        if(venceu(pilha_naipe, 4))
        {
            printf("Parabéns, voce venceu!\n");
            break;
        }
        system("clear");
    }
    return 0;
}