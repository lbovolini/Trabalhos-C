#ifndef STRUCTURES
#define STRUCTURES

#define OPERAND  1
#define OPERATOR 2
#define VARIABLE 3


typedef struct st_celula
{
  struct st_celula *prox;

  int   lin, 
        col;

  float val;

} tipo_celula;


typedef struct tipo_matriz_esparsa
{
  int i, 
      j;

  tipo_celula *prim_celula, 
              *ult_celula;

} matriz_esparsa;


typedef struct lista_circular 
{
    void *dado;
    int type;
    struct lista_circular *ant, 
                          *prox;
} st_lista_circular ;


typedef struct
{
    int n; // numero de elementos da lista
    st_lista_circular *prim, 
                      *ult;
} tipo_descritor_lista;

#endif