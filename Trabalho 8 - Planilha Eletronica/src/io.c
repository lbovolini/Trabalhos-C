/**
* Funcoes de entrada e saida
**/


#include "io.h"


//
int imprime_matriz(matriz_esparsa *mat)
{
    int i = 1,
        j = 1;

    if(!mat) return 0;
        
    tipo_celula *percorrer = mat->prim_celula;

    for(i = 1; i <= mat->i; i++)
    {
        for(j = 1; j <= mat->j; j++)
        {
            if(!percorrer)
            {
                printf("0\t");
            }
            else if((percorrer->lin == i) && (percorrer->col == j))
            {
                printf("%.2f\t", percorrer->val);
                percorrer = percorrer->prox;
            }
            else
            {
                printf("0\t");
            }
        }
        printf("\n");
    }

    //
    return 0;
}




//
int ler_arquivo(matriz_esparsa **matriz1, matriz_esparsa **matriz2)
{
    int cont = 0,
        aux = 0,
        i,
        j,
        lin,
        col;
        
    float valor;
    
    FILE *arquivo = NULL;
    char linha[100];

    arquivo = fopen("matrizes.txt", "r");

    if(!arquivo)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }


    while(!feof(arquivo))
    {    
        if(!fgets(linha, sizeof(linha), arquivo)) return 0;
        //remover_quebra_linha(linha);

        aux = limpar_string(linha);
        //printf("%c\n", linha[aux]);

        if(isalpha(linha[aux]))
        {
            sscanf(linha, "%*s %d %d", &i, &j);

            if((i < 1) || (j < 1))
            {
                printf("Arquivo invalido!\n");
                exit(1);
            }
            
            if(linha[aux] == 'F')
            {
                break;
            }
            else if(linha[aux] == 'M')
            {
                cont++;
                if(cont == 1)
                {
                    *matriz1 = cria_matriz_esparsa(i, j);
                }
                else if(cont == 2)
                {
                    *matriz2 = cria_matriz_esparsa(i, j);
                }
            }

        }
        else
        {
            sscanf(linha, "%d %d %f", &lin, &col, &valor);
            //printf("%d x %d = %f\n", lin, col, valor);

            if((lin < 1) || (col < 1) || (lin > i) || (col > j))
            {
                printf("Arquivo invalido!\n");
                exit(1);
            }

            if(cont == 1)
            {
                insere_ordenado(*matriz1, lin, col, valor);
            }
            else if(cont == 2)
            {
                insere_ordenado(*matriz2, lin, col, valor);
            }
            
        }
        
    }

    fclose(arquivo);
    return 0;
}


// le arquivo com as operacoes
void ler_operacoes(tipo_descritor_lista *expressao)
{
    FILE *arquivo = NULL;

    arquivo = fopen("operacao.txt", "r");

    int i = 0, op = 0;

    char *caracter = NULL;

    char linha[100];

    tipo_descritor_lista *operacao = cria_descritor_lista();

    if(!arquivo)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    while(fscanf(arquivo, "%s", linha) == 1)
    {

        i = 0;
        insere_lista(expressao, get_operando(linha, &i));
        i++;
        //printf("%s\n", (char*)expressao->prim->dado);

        while(linha[i] != '\n' && linha[i])
        {
            // abre parenteses (
            if( linha[i] == '+' || linha[i] == '-' || linha[i] == '*' || linha[i] == '/' || linha[i] == '^') {
                caracter = (char *)malloc(1);
                *caracter = linha[i];
                insere_lista(operacao, &*caracter);
            }
            // letra ou numero
            else if(isalpha(linha[i]) || isdigit(linha[i])) {
                insere_lista(expressao, get_operando(linha, &i));
                op++;
            }
            // fecha parenteses (
            else if(linha[i] == ')') {

                    //while(operacao->prim && *((char*)operacao->prim->dado) != '(') {

                        insere_lista(expressao, get_elemento_lista(operacao, operacao->ult));
                    //}
                    //get_elemento_lista(operacao, operacao->ult);
                    op = 0;
                
            }
            i++;
        }
        insere_lista(expressao, get_elemento_lista(operacao, operacao->ult));
    }
    fclose(arquivo);
}


//
int escrever_matriz(FILE *arquivo, matriz_esparsa *matriz)
{
    //
    if(!matriz) return 1;
    
    tipo_celula *percorrer = NULL;
 
    fprintf(arquivo, "Matriz %d %d\n", matriz->i, matriz->j);
    
    percorrer = matriz->prim_celula;
    while(percorrer)
    {
        fprintf(arquivo, "%d %d %.1f\n", percorrer->lin, percorrer->col, percorrer->val);
        percorrer = percorrer->prox;
    }
    
    //
    return 0;
}


// escrever no arquivo
int escrever_arquivo(matriz_esparsa *matriz1, matriz_esparsa *matriz2, matriz_esparsa *multiplicacao, matriz_esparsa *soma)
{
    FILE *arquivo = NULL;
    
    arquivo = fopen("resultado.txt", "w");
    if(!arquivo)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    escrever_matriz(arquivo, matriz1);
    escrever_matriz(arquivo, matriz2);
    escrever_matriz(arquivo, soma);
    escrever_matriz(arquivo, multiplicacao);

    fprintf(arquivo, "Fim");
    fclose(arquivo);

    return 0;
}

