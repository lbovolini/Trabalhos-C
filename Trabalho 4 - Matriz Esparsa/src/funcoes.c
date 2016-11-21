#include "matriz.h"
#include <string.h>
#include <ctype.h>


// aloca matriz_esparsa e retorna
matriz_esparsa *cria_matriz_esparsa(int i, int j)
{
    matriz_esparsa *matriz = NULL;

    if((matriz = (matriz_esparsa *)malloc(sizeof(matriz_esparsa))) == NULL)
    {
        printf("Falta de memoria!\n");
        return NULL;
    }
    
    matriz->i = i;
    matriz->j = j;
    matriz->prim_celula = NULL;
    matriz->ult_celula = NULL;
    
    return matriz;
}


// aloca elemento e retorna
tipo_celula *cria_celula(int linha, int coluna, float valor)
{
    tipo_celula *celula = NULL;
    
    if((celula = (tipo_celula *)malloc(sizeof(tipo_celula))) == NULL)
    {
        printf("Falta de memoria!\n");
        return NULL;
    }
    
    celula->lin = linha;
    celula->col = coluna;
    celula->val = valor;
    celula->prox = NULL;
    
    return celula;
}


// insere um elemento na matriz
int insere(matriz_esparsa *mat, int linha, int coluna, float valor)
{
    tipo_celula *celula = NULL;
    
    celula = cria_celula(linha, coluna, valor);

    // matriz vazia
    if(mat->prim_celula == NULL && mat->ult_celula == NULL)
    {
        mat->prim_celula = celula;
        mat->ult_celula  = celula;
        return 0;
    }
    
    // insere no fim
    mat->ult_celula->prox = celula;
    mat->ult_celula = celula;
    
    return 0;
}


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
                //TODO ponteiro permanece apontando para ultima posicao
                //if(percorrer->prox != NULL)
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
                insere(*matriz1, lin, col, valor);
            }
            else if(cont == 2)
            {
                insere(*matriz2, lin, col, valor);
            }
            
        }
        
    }
    
    fclose(arquivo);
    return 0;
}


// retorna valor do elemento, zero se nao encontrado
float valor_elemento(matriz_esparsa *mat, int linha, int coluna)
{
    if(!mat) return 0;
    
    tipo_celula *percorrer = mat->prim_celula;

    while(percorrer)
    {       
        if((percorrer->lin == linha) && (percorrer->col == coluna))
        {
            //printf("%f\n", percorrer->val);
            return percorrer->val;
        }
        percorrer = percorrer->prox;
    }
    
    //
    return 0;
}


// retorna o resultado da multiplicacao de duas matrizes
matriz_esparsa *multiplica_matriz(matriz_esparsa *matriz1, matriz_esparsa *matriz2)
{
    int i = 1,
        j = 1,
        n = 1;

    float valor1,
          valor2,
          soma = 0;

    if(!matriz1 || !matriz2) return NULL;

    /* verifica se o numero de colunas da matriz1 corresponde 
    ao numero de linhas da matriz2 */ 
    if(matriz1->j != matriz2->i)
    {
        //printf("Nao e possivel realizar esta multiplicacao.\n");
        return NULL;
    }
    
    matriz_esparsa *resultado = NULL;
    resultado = cria_matriz_esparsa(matriz1->i, matriz2->j);

    for(i = 1; i <= matriz1->i; i++)
    {
        //for(j = 1, m = 1; (j <= matriz1->j) && (m <= matriz2->i); j++, m++)
        for(j = 1; j <= matriz1->j; j++)
        {
            for(n = 1; n <= matriz2->j; n++)
            {
                valor1 = valor_elemento(matriz1, i, n);
                valor2 = valor_elemento(matriz2, n, j);
            
                soma += (valor1 * valor2);
                //printf("V1 = %.2f V2 = %.2f\n", valor1, valor2);
            }
            
            if(soma != 0)
            {
                insere(resultado, i, j, soma);
            }
            soma = 0;
        }

    }

    //
    return resultado;
}


// retorna o resultado da soma de duas matrizes
matriz_esparsa *soma_matriz(matriz_esparsa *matriz1, matriz_esparsa *matriz2)
{
    int i = 1,
        j = 1;

    float valor1,
          valor2, 
          soma = 0;
               
    if(!matriz1 || !matriz2) return NULL;

    /* verifica se o numero de linhas e colunas da matriz1 correspondem 
    ao numero de linhas e colunas da matriz2 */ 
    if((matriz1->i != matriz2->i) || (matriz1->j != matriz2->j))
    {
        //printf("Nao e possivel realizar esta soma.\n");
        return NULL;
    }
    
    matriz_esparsa *resultado = NULL;
    resultado = cria_matriz_esparsa(matriz1->i, matriz1->j);
    
    for(i = 1; i <= matriz1->i; i++)
    {
        for(j = 1; j <= matriz1->j; j++)
        {
            valor1 = valor_elemento(matriz1, i, j);
            valor2 = valor_elemento(matriz2, i, j);
        
            soma = (valor1 + valor2);
            
            if(soma != 0)
            {
                insere(resultado, i, j, soma);
            }
        }
    }
    
    //
    return resultado;
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
    
    arquivo = fopen("output.txt", "w");
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


// remove a quebra de linha do final da string
void remover_quebra_linha(char *string)
{
    if ((strlen(string) > 0) && (string[strlen(string) - 1] == '\n'))
    {
        string[strlen(string) - 1] = '\0';
    }
}


// remove "lixo" do inicio da string
int limpar_string(char *string)
{
    int i = 0;
 
    while(i < strlen(string))
    {
        if(isalpha(string[i]))
            return i;
        i++;
    }
    return 0;
}
