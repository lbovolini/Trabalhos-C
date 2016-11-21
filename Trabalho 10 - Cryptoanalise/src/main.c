#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Tamanho maximo da string
#define MAX 30

// Vetor de indices auxiliar
int indices[MAX];


void inicializaIndices();
void ordenaPalavra(char *palavra);
int getIndice(char *palavra, char letra, int tamanho);
void descrito(char *palavra_entrada, char *palavra_ordenada, int inicio);
void ler_arquivo();


void inicializaIndices()
{
	int i = 0;

	for(i = 0; i < MAX; i++) {
		indices[i] = 0;
	}
}


void ordenaPalavra(char *palavra)
{
	int i = 0,
		j = 0,
		tamanho = strlen(palavra);

	char aux;

	while(i < tamanho) {
		j = 0;
		while(j < tamanho) {
	        if(palavra[i] < palavra[j]) {
	        	aux = palavra[i];
	        	palavra[i] = palavra[j];
	        	palavra[j] = aux;
			}
			j++;
		}
		i++;
	}
}

int getIndice(char *palavra, char letra, int tamanho)
{
	int i = 0;

	for(i = 0; i < tamanho; i++) {
		if((palavra[i] == letra) && (indices[i] == 0)) {
			indices[i] = 1;
			return i;
		}
	}

	return MAX;
}

void descrito(char *palavra_entrada, char *palavra_ordenada, int inicio)
{
	char palavra[MAX];
	int i = 0, 
		tamanho;

	tamanho = strlen(palavra_entrada);

	indices[inicio] = 1;

	for(i = 0; (i < (MAX - 1)) && (inicio < MAX) ; i++) {
		palavra[i] = palavra_ordenada[inicio];
		inicio = getIndice(palavra_entrada, palavra_ordenada[inicio], tamanho);
	}
	palavra[tamanho] = '\0';

	printf("%s\n", palavra);
}


void ler_arquivo()
{

    FILE *arquivo = NULL;

    int i = 0, 
    	num;
    char palavra_entrada[MAX];
	char palavra_ordenada[MAX];

    arquivo = fopen("palavras.txt", "r");

    if(!arquivo)
    {
        printf("Erro ao abrir arquivo!\n");
        exit(1);
    }

	i = 1;  
    while(!feof(arquivo))
    {    
        if(fscanf(arquivo, "%s %d\n", palavra_entrada, &num) != 2) {
        	printf("Palavra invalida!\n");
        	exit(0);
		}

        inicializaIndices();
        strcpy(palavra_ordenada, palavra_entrada);

    	ordenaPalavra(palavra_ordenada);
		printf("%d - %s => ", i, palavra_entrada);
    	descrito(palavra_entrada, palavra_ordenada, (num - 1));
		i++;
    }
}


int main()
{
	ler_arquivo();

	return 0;
}