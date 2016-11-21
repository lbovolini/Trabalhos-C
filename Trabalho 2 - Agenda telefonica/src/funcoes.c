#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"


// tamanho da agenda telefonica
int A_TAMANHO = 0;


/* setar o campo idade dos MAX elementos do vetor com o valor -1, 
significando que os elementos da agenda A estão disponíveis. */
int inicializa_agenda(struct agenda a[MAX])
{
    //
    int i = 0;

    for(i = 0; i < MAX; i++)
    {
        a[i].idade = -1;
    }

    return 0;
}


// inicializa vetor de indices de apelidos ordenados
int inicializa_ind_apelido(int ind_apelido[MAX])
{
    int i = 0;

    for(i = 0; i < MAX; i++)
    {
        ind_apelido[i] = -1;
    }
    return 0;
}


// desloca o vetor, em certo ponto, em uma posição para cima
void desloca_cima(int ind_apelido[MAX], int indice)
{
    int i;
    
    for(i = indice; i < A_TAMANHO; i++)
    {
        if(i + 1 < MAX)
        {
            ind_apelido[i] = ind_apelido[i + 1];
        }
    }
    ind_apelido[MAX - 1] = -1; 
}


// desloca o vetor, em certo ponto, em uma posição para baixo
void desloca_baixo(int ind_apelido[MAX], int indice)
{
    int i;
    
    for(i = MAX - 1; i > indice; i--)
    {
        ind_apelido[i] = ind_apelido[i - 1];
    } 
}


/* ind_apelido é um vetor auxiliar e este vetor que deve ser ordenado, 
não deve ser alterado o vetor agenda A. Esta função pode ser executada 
após a inclusão de um novo elemento, para deixar o ind_apelido sempre 
atualizado. */
int inclui_ind(struct agenda a[MAX], int ind_apelido[MAX], int i)
{
    int j, sai = 0;

    for(j = 0; j < MAX && !sai; j++)
    {
        if(ind_apelido[j] == -1)
        {
            ind_apelido[j] = i;
            sai = 1;
        }
        else if(strcmp(a[i].apelido, a[ind_apelido[j]].apelido) < 0)
        {
            desloca_baixo(ind_apelido, j);
            ind_apelido[j] = i;
            sai = 1;
        }
    }
    
    return 0;
}


/* Localiza um elemeto do vetor A que possua idade = -1 e incluir 
os valores. Deve retornar 1 se incluir e 0 se não incluir devido 
duplicação do apelido. */
int inclui_agenda(struct agenda a[MAX], char apelido[10], char nome[30], char telefone[12], int idade, int ind_apelido[MAX])
{
    //
    int i = 0;

    // verifica se apelido ja existe
    for(i = 0; i < A_TAMANHO; i++)
    {
        if(a[i].idade != -1)
        {
            if(strcmp(a[i].apelido, apelido) == 0)
            {
                // apelido existe
                return 0;
            }
        }
    }

    // verifica se existe entrada disponivel na agenda telefonica
    for(i = 0; i < MAX; i++)
    {
        // se ha entrada inclui novo contato na agenda telefonica
        if(a[i].idade == -1)
        {
            strcpy(a[i].apelido , apelido);
            strcpy(a[i].nome    , nome);
            strcpy(a[i].telefone, telefone);
            a[i].idade = idade;
            // atualiza tamanho
            A_TAMANHO++;

            // atualiza vetor de indices de apelidos ordenados
            inclui_ind(a, ind_apelido, i);
            return 1;
        }
    }

    // nao ha entrada disponivel
    return 0;
}


/* retorna o numero do telefone ou valor -1 se não encontrado. */
int busca_binaria_apelido(struct agenda a[MAX], int ind_apelido[MAX], char apelido[10])
{
    int inf = 0;
    int sup = A_TAMANHO - 1;
    int meio;
    int compara;

    while(inf <= sup) 
    {
        meio = (inf + sup) / 2;
        compara = strcmp(apelido, a[ind_apelido[meio]].apelido);

        if (compara == 0)
        {
            return meio;
        }
        else if(compara < 0)
        {
            sup = meio - 1;
        }
        else
        {
            inf = meio + 1;
        }
    }

    // nao encontrado
    return -1;
    }


/* coloca o valor da idade deste apelido com valor -1, se existir. */
int exclui_agenda(struct agenda a[MAX], char apelido[10], int ind_apelido[MAX])
{
    int i = 0;

    // procura apelido na agenda telefonica
    for(i = 0; i < MAX; i++)
    {
        if(a[ind_apelido[i]].idade != -1)
        {
            if(strcmp(a[ind_apelido[i]].apelido, apelido) == 0)
            {
                // remove contato
                a[ind_apelido[i]].idade = -1;
                ind_apelido[i] = -1;
                // desloca
                desloca_cima(ind_apelido, i);
                // atualiza tamanho
                A_TAMANHO--;
                // removido
                return 0;
            }   
        }
    }
    // apelido nao encontrado
    return 1;
}


// exibe agenda telefonica completa
int exibir_agenda(struct agenda a[MAX])
{
    int i = 0;
    
    for(i = 0; i < MAX; i++)
    {
        if(a[i].idade != -1)
        {
            printf("Apelido: %s\t" , a[i].apelido);
            printf("Nome: %s\t"    , a[i].nome);
            printf("Telefone: %s\t", a[i].telefone);
            printf("Idade: %d\n"   , a[i].idade);
        }
    }

    return 0;
}


// exibe agenda telefonica completa ordenada
int exibir_agenda_ordenada(struct agenda a[MAX], int ind_apelido[MAX])
{
    int i = 0;
    
    for(i = 0; i < MAX; i++)
    {
        if(ind_apelido[i] != -1)
        {
            printf("Apelido: %s\t" , a[ind_apelido [i]].apelido);
            printf("Nome: %s\t"    , a[ind_apelido [i]].nome);
            printf("Telefone: %s\t", a[ind_apelido [i]].telefone);
            printf("Idade: %d\n"   , a[ind_apelido [i]].idade);
        }
    }

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


// verifica se a string esta vazia
int string_vazia(char *string)
{
    if (strlen(string) == 0)
    {
        return 1;
    }

    return 0;
}


// ler arquivo
int ler_arquivo(struct agenda **pa, int *ind_apelido)
{
    int i = 0,
        idade = 0;

    char apelido[19],
         nome[36],
         telefone[22],
         str_idade[11],
         entrada[20];

    FILE *arquivo = NULL;

    scanf("%s", entrada);
    
    arquivo = fopen(entrada, "r");
    if(!arquivo)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    //
    do
    {
        if(!fgets(apelido, sizeof(apelido), arquivo)) return 1;
        remover_quebra_linha(apelido);
        if(strlen(apelido) < 10) return 1;
        //printf("%s\n", apelido);

        if(!fgets(nome, sizeof(nome), arquivo)) return 1;
        remover_quebra_linha(nome);
        if(strlen(nome) < 7) return 1;
        //printf("%s\n", nome);

        if(!fgets(telefone, sizeof(telefone), arquivo)) return 1;
        remover_quebra_linha(telefone);
        if(strlen(telefone) < 11) return 1;
        //printf("%s\n", telefone);

        if(fscanf(arquivo, "%s" "%d\n", str_idade, &idade) != 2) return 1;
        //if(!fgets(idade, sizeof(idade), arquivo)) return 1;
        //remover_quebra_linha(idade);
        if(strlen(str_idade) < 6) return 1;
        //printf("%s %d\n", str_idade, idade);

        inclui_agenda(**(&pa), &apelido[9], &nome[6], &telefone[10], idade, *(&ind_apelido));
        i++;
    } while(!feof(arquivo) && (A_TAMANHO + i) < 30);

    fclose(arquivo);

    return 0;
}


// escrever no arquivo
int escrever_arquivo(struct agenda **pa, int *ind_apelido)
{
    int i = 0;

    char saida[20];

    FILE *arquivo = NULL;

    scanf("%s", saida);
    
    arquivo = fopen(saida, "w");
    if(!arquivo)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    //
    do
    {
        fprintf(arquivo, "Apelido: %s\n" , (*pa + *(ind_apelido + i))->apelido);
        fprintf(arquivo, "Nome: %s\n"    , (*pa + *(ind_apelido + i))->nome);
        fprintf(arquivo, "Telefone: %s\n", (*pa + *(ind_apelido + i))->telefone);
        fprintf(arquivo, "Idade: %d\n"   , (*pa + *(ind_apelido + i))->idade);

        if((i + 1 < A_TAMANHO))
        {
            fprintf(arquivo, "\n");
        }

        i++;
    } while(i < A_TAMANHO);

    fclose(arquivo);

    return 0;
}


/*// organiza vetor
int organiza_vetor(struct agenda a[MAX], int indice)
{
    int i = 0;
    struct agenda aux;

    for(i = indice; i < A_TAMANHO; i++)
    {
        aux = a[i + 1];
        a[i] = aux;
    }

}*/


/*// calcula o numero de entradas ocupadas na agenda telefonica
int calcula_tamanho(struct agenda a[MAX])
{
    int tamanho = 0;

    // incrementa contador "tamanho" se entrada esta ocupada
    while(a[tamanho].idade != -1)
    {
        tamanho++;
    }
    
    return tamanho;
   
}*/
