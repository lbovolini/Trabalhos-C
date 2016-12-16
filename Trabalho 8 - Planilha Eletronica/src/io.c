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


// carrega arquivo para a memoria e retorna
char *load_file_memory (char *file_name)
{
    FILE *file = NULL;
    char *buffer_file = NULL;
    long file_size = 0;
    size_t result = 0;

    file = fopen(file_name, "r");

    // obtain file size
    fseek (file, 0, SEEK_END);
    file_size = ftell (file);
    rewind (file);

    // empty file
    if (file_size <= 0) {
        printf("File %s is empty.\n", file_name);
        exit (EXIT_FAILURE);
    }

    // string terminator
    file_size += 1;
    // allocate memory to file
    buffer_file = (char *) malloc (sizeof (char) * file_size);
    if (!buffer_file) {
        printf ("Memory error!\n");
        exit (EXIT_FAILURE);
    }

    // copy file into buffer
    result = fread (buffer_file, 1, (file_size - 1), file);
    if (result != (file_size - 1)) {
        printf("Reading error!\n");
        exit (EXIT_FAILURE);
    }
    // add string terminator
    buffer_file[file_size] = '\0';

    fclose (file);

    return buffer_file;
}

int is_signal (char character) {

    if (character == '+' || character == '-')
        return 1
    return 0;
}

// retorna true se for operador
int is_operator(char character, int *parenteses) {

    if (character == '+' || character == '-' || character == '*' || character == '/' || character == '^') {
        return 1;
    }
    if (character == '(' ) {
        (*parenteses)++;
        return 1;
    }
    if (character == ')') {
        (*parenteses)--;
        return 1;
    }
    return 0;
}


// le arquivo com as operacoes
void ler_operacoes (tipo_descritor_lista *expressao)
{
    if (!expressao) {
        printf ("Erro ler_operacoes()\n");
        exit (EXIT_FAILURE);
    }


    int i = 0, parenteses = 0;

    char *sign = NULL;

    //tipo_descritor_lista *operacao = cria_descritor_lista();

    char *buffer_file = NULL;
    char *file_name = "operacao.txt";

    buffer_file = load_file_memory (file_name);

    // apenas uma expressao
    while (buffer_file[i] != '\0' && buffer_file[i])
    {
        // skip new lines
        while (buffer_file[i] == '\n') i++;

       // insere_lista (expressao, get_operando (buffer_file, &i));
       // i++;


        while (buffer_file[i] != '\n' && buffer_file[i])
        {

            // operador (
            if (is_operator (buffer_file[i], &parenteses))  {
                sign = (char *) malloc (sizeof (char) * 2);
                sign[0] = buffer_file[i];
                sign[1] = '\0';
                insere_lista (expressao, sign, STRING);
            }
            // letra
            else if (isalpha (buffer_file[i])) {
                insere_lista (expressao, get_operando (buffer_file, &i), STRING);
            }
            // numero
            else if (isdigit (buffer_file[i])) {
                //printf("BUFF %c\n", buffer_file[i]);
                //printf("i == %d\n", i);
                insere_lista (expressao, extrair_numero(buffer_file, &i, '+'), FLOAT);
                //printf("i == %d\n", i);
            }
            i++; 
        }

        //insere_lista(expressao, get_elemento_lista(operacao, operacao->ult));
    }

    if (parenteses != 0) {
        printf ("Erro de expressao.\n");
        exit (EXIT_FAILURE);
    }

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

