#define MAX 10

// inicializa os vetores de polinômio
int inicializa_polinomio(float *polinomio);


//float *polinomio1, *float *polinomio2
int ler_arquivo_polinomio(float **polinomio1, float **polinomio2, float *x, FILE **saida);


// carrega polinomio
int carrega_polinomio(float coeficiente, int grau, float **polinomio);


//
float *ler_polinomio(char *linha);


// calcula
float calcula(float **polinomio, float *x, char c, FILE **saida);


// soma polinomios
void soma(float **polinomio1, float **polinomio2, float *x, FILE **saida);


// subtrai polinomios
void subtrai(float **polinomio1, float **polinomio2, float *x, FILE **saida);


// calcula derivada
void derivada(float **polinomio1, float *x, char c, FILE **saida);


// calcula integral
void integral(float **polinomio1, float *x, char c, FILE **saida);
