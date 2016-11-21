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


// insere um elemento na matriz de forma ordenada
int insere_ordenado(matriz_esparsa *mat, int linha, int coluna, float valor)
{
    tipo_celula *celula = NULL,
                *percorre = NULL,
                *anterior = NULL;
    
    celula = cria_celula(linha, coluna, valor);

    percorre = mat->prim_celula;

    // matriz vazia
    if(mat->prim_celula == NULL && mat->ult_celula == NULL)
    {
        mat->prim_celula = celula;
        mat->ult_celula  = celula;
        return 0;
    }

    // insere no inicio
    if((percorre->lin > linha) || ((percorre->lin == linha) && (percorre->col > coluna)))
    {
        celula->prox = percorre;   
        mat->prim_celula = celula;
        return 0;
    }

    while(percorre != NULL)
    {
        if((percorre->lin < linha) || ((percorre->lin == linha) && (percorre->col < coluna)))
        {
            anterior = percorre;
            percorre = percorre->prox;
        }
        else break;
    }

    // insere no fim
    if(percorre == NULL)
    {
        mat->ult_celula = celula;
    }

    // insere no meio/fim
    anterior->prox = celula;
    celula->prox = percorre;
    
    return 0;
}


// remove elemento 
int remove_elemento(matriz_esparsa *mat, int linha, int coluna)
{
    tipo_celula *percorre = NULL,
                *anterior = NULL;

    // matriz vazia
    if(!mat || !mat->prim_celula) return 1;

    percorre = mat->prim_celula;

    // remove no inicio
    if((percorre->lin == linha) && (percorre->col == coluna))
    {
        if(mat->prim_celula == mat->ult_celula)
        {
            mat->ult_celula = NULL;
        }
        mat->prim_celula = percorre->prox;
        
        // remove
        free(percorre);
        return 0;
    }

    while(percorre != NULL)
    {
        if(!((percorre->lin == linha) && (percorre->col == coluna)))
        {
            anterior = percorre;
            percorre = percorre->prox;
        }
        else break;
    }

    // nao encontrado
    if(percorre == NULL) return 1;

    if(percorre == mat->ult_celula)
    {
        mat->ult_celula = anterior;
    }    
    // remove no meio/fim
    anterior->prox = percorre->prox;
    // remove
    free(percorre);
    
    return 0;
}


// altera o valor de um elemento na matriz
int altera_elemento(matriz_esparsa *mat, int linha, int coluna, float valor)
{
    tipo_celula *percorre = NULL;
    
    percorre = mat->prim_celula;

    // matriz vazia
    if(!mat) return 1;

    while(percorre != NULL)
    {
        if((percorre->lin == linha) && (percorre->col == coluna))
        {
            //!TODO refatorar
            remove_elemento(mat, linha, coluna);
            insere_ordenado(mat, linha, coluna, valor);
            return 0;
        }
        percorre = percorre->prox;
    }

    // nao encontrado
    return 1;
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
void ler_operacoes(matriz_esparsa *matriz1)
{
    FILE *arquivo = NULL;

    int  linha0,
         linha1,
         linha2;
         
    float resultado = 0;

    char coluna0,
         coluna1,
         coluna2,
         operador;

    arquivo = fopen("operacao.txt", "r");

    if(!arquivo)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

    //!TODO refatorar
    while(!feof(arquivo))
    {
        fscanf(arquivo, "%c%d=%c%d%c%c%d\n", &coluna0, &linha0, &coluna1, &linha1, &operador, &coluna2, &linha2);
        //printf("%d%c=%d%c%c%d%c\n", linha0, coluna0, linha1, coluna1, operador, linha2, coluna2);

        switch(operador)
        {
            case '+': 
                resultado = valor_elemento(matriz1, linha1, ((int)coluna1) - 64) + valor_elemento(matriz1, linha2, ((int)coluna2) - 64);
                break;
                
            case '-':
                resultado = valor_elemento(matriz1, linha1, ((int)coluna1) - 64) - valor_elemento(matriz1, linha2, ((int)coluna2) - 64);
                break;
                
            case '*':
                resultado = valor_elemento(matriz1, linha1, ((int)coluna1) - 64) * valor_elemento(matriz1, linha2, ((int)coluna2) - 64);
                break;
                
            case '/':
                if(valor_elemento(matriz1, linha2, ((int)coluna2) - 64) == 0)
                {
                    printf("Impossivel dividir por 0.\n");
                    exit(0);
                }
                resultado = valor_elemento(matriz1, linha1, ((int)coluna1) - 64) / valor_elemento(matriz1, linha2, ((int)coluna2) - 64);
                break;
        }
    
        if(resultado == 0)
        {
            remove_elemento(matriz1, linha0, ((int)coluna0) - 64);
        }
        else
        {
            // se elemento nao existe
            if(altera_elemento(matriz1, linha0, ((int)coluna0) - 64, resultado))
            {
                insere_ordenado(matriz1, linha0, ((int)coluna0) - 64, resultado);
            }

        }
        
    }
    fclose(arquivo);

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


/*
// insere um elemento na matriz de forma ordenada pelo valor
int insere_ordenado(matriz_esparsa *mat, int linha, int coluna, float valor)
{
    tipo_celula *celula = NULL,
                *percorre = NULL,
                *anterior = NULL;
    
    celula = cria_celula(linha, coluna, valor);

    percorre = mat->prim_celula;

    // matriz vazia
    if(mat->prim_celula == NULL && mat->ult_celula == NULL)
    {
        mat->prim_celula = celula;
        mat->ult_celula  = celula;
        return 0;
    }

    // insere no inicio
    if(percorre->val > valor)
    {
        celula->prox = percorre;   
        mat->prim_celula = celula;
        return 0;
    }

    while(percorre != NULL)
    {
        if(percorre->val < valor)
        {
            anterior = percorre;
            percorre = percorre->prox;
        }
        else break;
    }

    // insere no fim
    if(percorre == NULL)
    {
        mat->ult_celula = celula;
    }

    // insere no meio/fim
    anterior->prox = celula;
    celula->prox = percorre;
    
    return 0;
}*/


/*
int imprime_matriz(matriz_esparsa *mat)
{
    int i = 1,
        j = 1;

    if(!mat) return 0;
        
    tipo_celula *percorrer = mat->prim_celula;

    while(percorrer)
    {
        printf("[%d, %d] = %.2f\t", percorrer->lin, percorrer->col, percorrer->val);
int a = 1;
        percorrer = percorrer->prox;
    }

    //
    return 0;
}*/
