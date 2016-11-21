#include "funcoes.h"


// Insere na arvore
Arvore *inserir(Arvore *arvore, int numero)
{
    if(!arvore)
    {
        arvore = (Arvore*)malloc(sizeof(Arvore));
        arvore->num = numero;
        arvore->esq = NULL;
        arvore->dir = NULL;
    }
    else if(numero > arvore->num)
    {
        arvore->dir = inserir(arvore->dir, numero);

        if(BF(arvore) == -2)
        {
            if(numero>arvore->dir->num)
                arvore = RR(arvore);

            else
                arvore = RL(arvore);
        }
    }
    else if(numero < arvore->num)
    {
        arvore->esq = inserir(arvore->esq, numero);

        if(BF(arvore) == 2)
        {
            if(numero < arvore->esq->num)
                arvore = LL(arvore);

            else
                arvore = LR(arvore);
        }
    }

    arvore->ht = altura(arvore);

    return(arvore);
}


// Remove da arvore
Arvore *remover(Arvore *arvore, int numero)
{       
    Arvore *p = NULL;

    if(!arvore) return NULL;

    else if(numero > arvore->num)
    {
        arvore->dir = remover(arvore->dir, numero);

        if(BF(arvore) == 2)
        {
            if(BF(arvore->esq) >= 0)
                arvore = LL(arvore);

            else
                arvore = LR(arvore);
        }
    }
    else if(numero < arvore->num)
    {
        arvore->esq = remover(arvore->esq, numero);

        if(BF(arvore) == -2)
        {
            if(BF(arvore->dir) <= 0)
                arvore = RR(arvore);

            else
                arvore = RL(arvore);
        }
    }
    else
    {
        if(arvore->dir)
        {
            p = arvore->dir;
            while(p->esq)
                p = p->esq;

            arvore->num = p->num;
            arvore->dir = remover(arvore->dir, p->num);

            if(BF(arvore) == 2)
            {
                if(BF(arvore->esq) >= 0)
                    arvore = LL(arvore);

                else
                    arvore = LR(arvore);
            }
        } 
        else return(arvore->esq);
    }

    arvore->ht = altura(arvore);

    return(arvore);
}


// retorna a maior altura
int altura(Arvore *arvore)
{
    int lh,rh;

    if(!arvore) return 0;

    if(!arvore->esq)
        lh = 0;
    else
        lh = 1 + arvore->esq->ht;

    if(!arvore->dir)
        rh = 0;
    else
        rh = 1 + arvore->dir->ht;

    if(lh > rh)
        return(lh);

    return(rh);
}


// Rotaciona para direita
Arvore *rotacao_dir(Arvore *arvore)
{
    Arvore *p = NULL;

    p = arvore->esq;
    arvore->esq = p->dir;
    p->dir = arvore;
    arvore->ht = altura(arvore);
    p->ht = altura(p);

    return p;
}


// Rotaciona para direita
Arvore *rotacao_esq(Arvore *arvore)
{
    Arvore *p = NULL;

    p = arvore->dir;
    arvore->dir = p->esq;
    p->esq = arvore;
    arvore->ht = altura(arvore);
    p->ht = altura(p);

    return p;
}


Arvore *RR(Arvore *arvore)
{
    arvore = rotacao_esq(arvore);
    return arvore;
}


Arvore *LL(Arvore *arvore)
{
    arvore = rotacao_dir(arvore);
    return arvore;
}


Arvore *LR(Arvore *arvore)
{
    arvore->esq = rotacao_esq(arvore->esq);
    arvore = rotacao_dir(arvore);

    return arvore;
}


Arvore *RL(Arvore *arvore)
{
    arvore->dir = rotacao_dir(arvore->dir);
    arvore = rotacao_esq(arvore);

    return arvore;
}


int BF(Arvore *arvore)
{
    int lh,rh;

    if(!arvore) return 0;

    if(!arvore->esq)
        lh = 0;
    else
        lh = 1 + arvore->esq->ht;

    if(!arvore->dir)
        rh = 0;
    else
        rh = 1 + arvore->dir->ht;

    return (lh - rh);
}


void preenchimento(char ch, int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        putchar(ch);
    }
}


void imprimir(Arvore *arvore, int level)
{
    if(!arvore) 
    {
        preenchimento( '\t', level);
        puts("~");
    }
    else 
    {
        imprimir(arvore->dir, level + 1);
        preenchimento('\t', level);
        printf("%d\n", arvore->num);
        imprimir(arvore->esq, level + 1);
    }
}


void ler_arquivo(Arvore **arvore)
{

    FILE *arquivo = NULL;

    char operacao;
    int numero;

    arquivo = fopen("dados.txt", "r");

    if(!arquivo)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }
  
    while(!feof(arquivo))
    {    
        if(fscanf(arquivo, "%c,%d\n", &operacao, &numero) != 2) return;

        if(numero < -1000  || numero > 1000)
        {
            printf("Numero invalido!\n");
            exit(0);
        }

        if(operacao == '+') {
            *arvore = inserir(*arvore, numero);
        }
        else if(operacao == '-') {
            *arvore = remover(*arvore, numero);
        }
    }
}