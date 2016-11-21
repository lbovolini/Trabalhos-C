/**
* Titulo: Trabalho 1 de LAB 2
* Descricao: Agenda telefonica com o uso de struct.
* Autor: Lucas Bovolini
**/

#include <stdio.h>
#include <stdio_ext.h> // __fpurge();
#include <stdlib.h>
#include <string.h>
#include "funcoes.h"

#define INCLUIR    1
#define BUSCAR     2
#define EXCLUIR    3
#define EXIBIR     4
#define EXIBIR_ORD 5
#define LER        6
#define ESCREVER   7
#define SAIR       0


// main
int main(int argc, char *argv[])
{
    int operacao,
        idade;
 
    int ind_apelido[MAX];
    
    char apelido[10],
         nome[30],
         telefone[12];
         
    struct agenda a[MAX];
    struct agenda *pa = NULL;
    pa = a;
    
    inicializa_agenda(a);
    inicializa_ind_apelido(ind_apelido);

    do {
        // 
        system("cls || clear");
        printf("### AGENDA TELEFONICA ###\n\n Selicione a operacao:\n 1 - Incluir contato\n 2 - Buscar telefone por apelido\n 3 - Excluir contato\n 4 - Mostrar agenda\n 5 - Mostrar agenda ordenada\n 6 - Abrir arquivo\n 7 - Salvar em arquivo\n 0 - Sair\n");
        
        // limpa buffer
        //fflush(stdin); // for windows
        __fpurge(stdin); // for linux
        scanf("%d", &operacao);
        // 
        system("cls || clear");

        switch (operacao)            
        {
            // incluir contato
            case INCLUIR:
                printf("Digite o apelido: ");
                // limpa buffer
                //fflush(stdin); // for windows
                __fpurge(stdin); // for unix
                fgets(apelido, sizeof(apelido), stdin);
                remover_quebra_linha(apelido);

                if(string_vazia(apelido))
                {
                    printf("Invalido.");
                    break;
                }

                printf("Digite o nome: ");
                // limpa buffer
                //fflush(stdin); // for windows
                __fpurge(stdin); // for unix
                fgets(nome, sizeof(nome), stdin);
                remover_quebra_linha(nome);

                if(string_vazia(nome))
                {
                    printf("Invalido.");
                    break;
                }
                
                printf("Digite o telefone: ");
                // limpa buffer
                //fflush(stdin); // for windows
                __fpurge(stdin); // for unix
                fgets(telefone, sizeof(telefone), stdin);
                remover_quebra_linha(telefone);

                if(string_vazia(telefone))
                {
                    printf("Invalido.");
                    break;
                }

                // limpa buffer
                //fflush(stdin); // for windows
                __fpurge(stdin); // for unix
                printf("Digite a idade: ");
                scanf("%d", &idade);
                
                // incluir contato na agenda "a"
                if(inclui_agenda(a, apelido, nome, telefone, idade, ind_apelido) == 1)
                {                  
                    printf("\nContato inserido com sucesso!\n");
                }
                else 
                {
                    printf("\nErro ao inserir contato, agenda cheia ou apelido existe.\n");
                }  

                break;
                
            // buscar telefone por apelido
            case BUSCAR:;
                printf("Digite o apelido do contato que deseja buscar: ");            
                // limpa buffer
                //fflush(stdin); // for windows
                __fpurge(stdin); // for unix
                fgets(apelido, sizeof(apelido), stdin);
                remover_quebra_linha(apelido);               

                // busca telefone
                int res = busca_binaria_apelido(a, ind_apelido, apelido);

                if(res == -1)
                {
                    printf("Nao encontrado.\n");                
                }
                else
                {
                    printf("Telefone de %s: %s\n", a[ind_apelido[res]].apelido, a[ind_apelido[res]].telefone);        
                }

                break;
                
            // remover contato
            case EXCLUIR:
                printf("Digite o apelido do contato que deseja remover: ");
                // limpa buffer
                //fflush(stdin); // for windows
                __fpurge(stdin); // for linux
                fgets(apelido, sizeof(apelido), stdin); 
                remover_quebra_linha(apelido);

                if(string_vazia(apelido))
                {
                    printf("Invalido.");
                    break;
                }
                // exclui contato
                if(exclui_agenda(a, apelido, ind_apelido))
                {
                    printf("Erro ao excluir!\n");
                }
                else
                {
                    printf("Contato exluido!\n");
                }

                break;
          
            
            // exibir agenda telefonica
            case EXIBIR:  
                if(exibir_agenda(a))
                {
                    printf("Erro ao exibir agenda telefonica!\n");
                } 

                break;           
            
            // exibir agenda telefonica ordenada por apelido
            case EXIBIR_ORD:
                if(exibir_agenda_ordenada(a, ind_apelido))
                {
                    printf("Erro ao exibir agenda telefonica!\n");
                }

                break;

            // ler arquivo
            case LER:
                printf("Digite o nome do arquivo: ");
                if(ler_arquivo(&pa, ind_apelido))
                {
                    printf("Erro ao abrir arquivo!\n");
                }
                else
                {
                    printf("Arquivo aberto com sucesso!\n");
                }
                break;
            
            // escrever arquivo
            case ESCREVER:
                printf("Digite o nome do arquivo: ");
                if(escrever_arquivo(&pa, ind_apelido))
                {
                    printf("Erro ao salvar arquivo!\n");
                }
                else
                {
                    printf("Arquivo salvo com sucesso!\n");
                }
                break;

            // sair
            case SAIR:
                return 0;  

            // opcao invalida        
            default:         
                printf("Opcao invalida!\n");        
                break;
        }

        // limpa buffer
        //fflush(stdin); // for windows
        __fpurge(stdin); // for linux
        getchar();
    } while(operacao != SAIR);
        
    return 0;
}
