/**
* Funcoes da matriz
**/


#include "matriz.h"


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