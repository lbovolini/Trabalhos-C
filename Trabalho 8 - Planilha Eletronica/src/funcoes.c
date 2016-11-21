/**
* Funcoes auxiliares
**/


#include "funcoes.h"


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
