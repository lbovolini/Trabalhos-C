#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <math.h> 
#include "funcoes.h"


// inicializa os vetores de polinômio
int inicializa_polinomio(float *polinomio)
{
    int i = 0;

    for(i = 0; i < MAX; i++)
    {
        *(polinomio + i) = 0;
    }

    return 0;
}


// extrai numero de uma string
float extrair_numero(char *string, int *ind_inicio_num, char sinal)
{
    int   ind_fim_num = *ind_inicio_num;
    float float_num;

    char  string_num[100];

    // parte inteira do numero
    while(isdigit(string[ind_fim_num]))
    {
        ind_fim_num++;
    }

    // parte fracionaria do numero
    if(string[ind_fim_num] == '.' || string[ind_fim_num] == ',')
    {
        ind_fim_num++;
        while(isdigit(string[ind_fim_num]))
        {
            ind_fim_num++;
        }
    }
    //ind_fim_num--;

    // extrai numero para string_num
    strncpy(string_num, &string[*ind_inicio_num], (ind_fim_num - *ind_inicio_num));

    // adiciona caractere de fim de string
    string_num[ind_fim_num - *ind_inicio_num] = '\0';
    
    // convert string_num para float
    float_num = atof(string_num);

    if(sinal == '-')
    {
        float_num *= -1;
    }

    *ind_inicio_num = ind_fim_num;
    // retorna numero
    return float_num;
}


//float *polinomio1, *float *polinomio2
int ler_arquivo_polinomio(float **polinomio1, float **polinomio2, float *x, FILE **saida)
{
    FILE *arquivo = NULL;
    int aux = 2;          
    char *linha = NULL;

    linha = (char *)malloc(100 * sizeof(char));

    arquivo = fopen("p-input.txt", "r");

    if(!arquivo)
    {
        printf("Erro ao abrir arquivo!\n");
        return 1;
    }

    // le linha do arquivo
    fscanf(arquivo, "%s\n", linha);
    printf("%s\n", linha);
    fprintf(*saida, "%s\n", linha);
    *polinomio1 = ler_polinomio(linha);

    // le linha do arquivo
    fscanf(arquivo, "%s\n", linha);
    printf("%s\n", linha);
    fprintf(*saida, "%s\n", linha);
    *polinomio2 = ler_polinomio(linha);

    // le linha do arquivo
    fscanf(arquivo, "%s\n", linha);

    *x = extrair_numero(linha, &aux, '+');
    printf("x=%.2f\n", *x);
    fprintf(*saida, "x=%.2f\n", *x);

    fclose(arquivo);
    
    return 0;
}


//
float *ler_polinomio(char *linha)
{

    int i = 0, cont = 0;

    float float_num = 1,
          aux_float_num = 1;

    float *polinomio = NULL;
    
    char  sinal = '\0';

    polinomio = (float *)malloc(10 * sizeof(float));
    inicializa_polinomio(polinomio);

    // pula os 2 primeiros caracteres da string
    i = 2;
    while(*(linha + i) != '\0')
    {

        if(sinal == 'x')
        {
            aux_float_num = float_num;
            
            if(*(linha + i) == '-' || *(linha + i) == '+' || i == 3)
            {
                //printf("1 x 1\n");
                //inserir(1, 1);
                carrega_polinomio(1, 1, &polinomio);
                cont = 0;
            }
        }
        
        //if(cont != 2

        // se caractere for um numero
        if(isdigit(*(linha + i)))
        {
            float_num = extrair_numero(linha, &i, sinal);
            cont++;

            if(sinal == 'x')
            {
                //printf("%.2f x %.2f\n", aux_float_num, float_num);
                //incluir();
                carrega_polinomio(aux_float_num, (int)float_num, &polinomio);
                sinal = '+';
                cont = 0;
            }
        }
        
        else if(*(linha + i) == '-' || *(linha + i) == '+' || isalpha(*(linha + i)))
        {
            sinal = *(linha + i);
            i++;
        }
    }

    if(cont == 1)
    {
        //printf("%.2f x 0\n", float_num);
        //incluir();
        carrega_polinomio(float_num, 0, &polinomio);
        //printf("A\n");

    }

    //
    return polinomio;
}


// carrega polinomio
int carrega_polinomio(float coeficiente, int grau, float **polinomio)
{
    *(*polinomio + grau) = coeficiente;
    return 0;
}


// exibe polinomio
void exibe_polinomio(float **polinomio, FILE **saida)
{
    int i = 0;

    for(i = 0; i < MAX; i++)
    {
        printf("%d = %f\n", i, *(*polinomio + i));
        fprintf(*saida, "%d = %f\n", i, *(*polinomio + i));
    }
}


// calcula
float calcula(float **polinomio, float *x, char c, FILE **saida)
{
    int i = 0;
    float soma = 0;


    //
    for(i = 0; i < MAX; i++)
    {
        if(*(*polinomio + i) != 0.0)
        {
            soma += *(*polinomio + i) * pow(*x, i);
            //printf("%+.2f\n", *(polinomio + i));
        }
    }
    printf("%c(2.3)=%.2f\n", c, soma);
    fprintf(*saida, "%c(2.3)=%.2f\n", c, soma);

    return soma;
}


// refatorar
// soma polinomios
void soma(float **polinomio1, float **polinomio2, float *x, FILE **saida)
{
    int   i = 0, 
          cont = 0;
    float *polinomio = NULL;
    float soma = 0;

    polinomio = (float *)malloc(10 * sizeof(float));
    inicializa_polinomio(polinomio);
    
    for(i = 0; i < MAX; i++)
    {
        *(polinomio + i) = *(*polinomio1 + i) + *(*polinomio2 + i);
    }

    printf("Soma P+Q=");
    fprintf(*saida, "Soma P+Q=");
    for(i = 1; i < MAX; i++)
    {
        if(*(polinomio + i) != 0.0)
        {
            if(cont == 0)
            {
                printf("%.2fx%d", *(polinomio + i), i);
                fprintf(*saida, "%.2fx%d", *(polinomio + i), i);
                cont = 1;
            }
            else
            {
                printf("%+.2fx%d", *(polinomio + i), i);
                fprintf(*saida, "%+.2fx%d", *(polinomio + i), i);
            }
         }
    }
    
    if(*(polinomio + 0) != 0.0)
    {
        if(cont == 0)
        {
            printf("%.2f", *(polinomio + 0));
            fprintf(*saida, "%.2f", *(polinomio + 0));
        }
        else
        {
            printf("%+.2f", *(polinomio + 0));
            fprintf(*saida, "%+.2f", *(polinomio + 0));
        }
    }
    else
    {
        printf("0");
        fprintf(*saida, "0");
    }
    
    printf("\n");
    fprintf(*saida, "\n");
    
    //
    for(i = 0; i < MAX; i++)
    {
        if(*(polinomio + i) != 0.0)
        {
            soma += pow(*(polinomio + i) * *x, i);
            //printf("%+.2f\n", *(polinomio + i));
        }
    }

    printf("Soma(2.3)=%.2f\n", soma);
    fprintf(*saida, "Soma(2.3)=%.2f\n", soma);
}


// subtrai polinomios
void subtrai(float **polinomio1, float **polinomio2, float *x, FILE **saida)
{
    int   i = 0, 
          cont = 0;
    float *polinomio = NULL;
    float subtracao = 0;

    polinomio = (float *)malloc(10 * sizeof(float));
    inicializa_polinomio(polinomio);
    
    for(i = 0; i < MAX; i++)
    {
        *(polinomio + i) = *(*polinomio1 + i) - *(*polinomio2 + i);
    }

    printf("Subtracao P-Q=");
    fprintf(*saida, "Subtracao P-Q=");
    for(i = 1; i < MAX; i++)
    {
        if(*(polinomio + i) != 0.0)
        {
            if(cont == 0)
            {
                printf("%.2fx%d", *(polinomio + i), i);
                fprintf(*saida, "%.2fx%d", *(polinomio + i), i);
                cont = 1;
            }
            else
            {
                printf("%+.2fx%d", *(polinomio + i), i);
                fprintf(*saida, "%+.2fx%d", *(polinomio + i), i);
            }
         }
    }
    if(*(polinomio + 0) != 0.0)
    {
        if(cont == 0)
        {
            printf("%.2f", *(polinomio + 0));
            fprintf(*saida, "%.2f", *(polinomio + 0));
        }
        else
        {
            printf("%+.2f", *(polinomio + 0));
            fprintf(*saida, "%+.2f", *(polinomio + 0));
        }
    }
    else
    {
        printf("0");
        fprintf(*saida, "0");
    }
    
    printf("\n");
    fprintf(*saida, "\n");
    
    //((3*2.3)^5+((2*2.3)-1) +((−(4*2.3)^9)+((+3*2.3)^3)−1)
    for(i = 0; i < MAX; i++)
    {
        if(*(polinomio + i) != 0.0)
        {
            subtracao += pow(*(polinomio + i) * *x, i);
            //printf("\n== %f ==\n", pow(*(polinomio + i) * *x, i));
            //printf("%+.2f\n", *(polinomio + i));
        }
    }

    printf("Subtracao(2.3)=%.2f\n", subtracao);
    fprintf(*saida, "Subtracao(2.3)=%.2f\n", subtracao);
}


// calcula derivada
void derivada(float **polinomio1, float *x, char c, FILE **saida)
{
    int   i = 0, 
          cont = 0;
    float valor = 0;
    float *polinomio = NULL;

    polinomio = (float *)malloc(10 * sizeof(float));
    inicializa_polinomio(polinomio);

    //
    *(polinomio) = 0.0;
    for(i = 1; i < MAX; i++)
    {
        if(*(*polinomio1 + i) != 0.0)
        {
            *(polinomio + (i - 1)) = i * (*(*polinomio1 + i));
            //printf("%+.2f\n", *(polinomio + i));
        }
    }

    printf("Derivada %c=", c);
    fprintf(*saida, "Derivada %c=", c);
    for(i = 1; i < MAX; i++)
    {
        if(*(polinomio + i) != 0.0)
        {
            if(cont == 0)
            {
                printf("%.2fx%d", *(polinomio + i), i);
                fprintf(*saida, "%.2fx%d", *(polinomio + i), i);
                cont = 1;
            }
            else
            {
                printf("%+.2fx%d", *(polinomio + i), i);
                fprintf(*saida, "%+.2fx%d", *(polinomio + i), i);
            }
        }
    }

    if(*(polinomio + 0) != 0.0)
    {
        if(cont == 0)
        {
            printf("%.2f", *(polinomio + 0));
            fprintf(*saida, "%.2f", *(polinomio + 0));
        }
        else
        {
            printf("%+.2f", *(polinomio + 0));
            fprintf(*saida, "%+.2f", *(polinomio + 0));
        }
        
    }
    if(cont == 0)
    {
        printf("0");
        fprintf(*saida, "0");

    }
    
    printf("\nDerivada ");
    fprintf(*saida, "\nDerivada ");

    valor = calcula(&polinomio, &*x, c, &*saida);
}


// calcula integral
void integral(float **polinomio1, float *x, char c, FILE **saida)
{
    int i = 0, 
        cont = 0;
    float valor = 0;
    float *polinomio = NULL;

    polinomio = (float *)malloc(10 * sizeof(float));
    inicializa_polinomio(polinomio);

    //
    //*(polinomio) = 0.0;
    for(i = 0; i < MAX; i++)
    {
        if(*(*polinomio1 + i) != 0.0)
        {
            *(polinomio + (i + 1)) =  *(*polinomio1 + i) / (i + 1);
            //printf("%+.2f\n", *(polinomio + i));
        }
    }

    printf("Integral %c=", c);
    fprintf(*saida, "Integral %c=", c);
    for(i = 0; i < MAX; i++)
    {
        if(*(polinomio + i) != 0.0)
        {
            if(cont == 0)
            {
                printf("%.2fx%d", *(polinomio + i), i);
                fprintf(*saida, "%.2fx%d", *(polinomio + i), i);
                cont = 1;   
            }
            else
            {
                printf("%+.2fx%d", *(polinomio + i), i);
                fprintf(*saida, "%+.2fx%d", *(polinomio + i), i);
            }
        }
    }
    if(cont == 0)
    {
        printf("0");
        fprintf(*saida, "0");

    }
    
    //*(polinomio + 0) = 0.0;
    printf("\nIntegral ");
    fprintf(*saida, "\nIntegral ");

    valor = calcula(&polinomio, &*x, c, &*saida);   
}
