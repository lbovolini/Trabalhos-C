#ifndef FUNCOES
#define FUNCOES

#define MAX 30

// estrutura agenda telefonica
struct agenda
{
    char apelido[10];
    char nome[30];
    char telefone[12];
    int  idade;
};


/* setar o campo idade dos MAX elementos do vetor com o valor -1, 
significando que os elementos da agenda A estão disponíveis. */
int inicializa_agenda(struct agenda a[MAX]);


// inicializa vetor de indices de apelidos ordenados
int inicializa_ind_apelido(int ind_apelido[MAX]);


// desloca o vetor, em certo ponto, em uma posição para cima
void desloca_cima(int ind_apelido[MAX], int indice);


// desloca o vetor, em certo ponto, em uma posição para baixo
void desloca_baixo(int ind_apelido[MAX], int indice);


/* ind_apelido é um vetor auxiliar e este vetor que deve ser ordenado, 
não deve ser alterado o vetor agenda A. Esta função pode ser executada 
após a inclusão de um novo elemento, para deixar o ind_apelido sempre 
atualizado. */
int inclui_ind(struct agenda a[MAX], int ind_apelido[MAX], int i);


/* Localiza um elemeto do vetor A que possua idade = -1 e incluir 
os valores. Deve retornar 1 se incluir e 0 se não incluir devido 
duplicação do apelido. */
int inclui_agenda(struct agenda a[MAX], char apelido[10], char nome[30], char telefone[12], int idade, int ind_apelido[MAX]);


/* retorna o numero do telefone ou valor -1 se não encontrado. */
int busca_binaria_apelido(struct agenda a[MAX], int ind_apelido[MAX], char apelido[10]);


/* coloca o valor da idade deste apelido com valor -1, se existir. */
int exclui_agenda(struct agenda a[MAX], char apelido[10], int ind_apelido[MAX]);


// exibe agenda telefonica completa
int exibir_agenda(struct agenda a[MAX]);


// exibe agenda telefonica completa ordenada
int exibir_agenda_ordenada(struct agenda a[MAX], int ind_apelido[MAX]);


// remove a quebra de linha do final da sting
void remover_quebra_linha(char *string);


// verifica se a string esta vazia
int string_vazia(char *string);


// ler arquivo
int ler_arquivo(struct agenda **pa, int *ind_apelido);


// escrever no arquivo
int escrever_arquivo(struct agenda **pa, int *ind_apelido);


#endif
