//!TODO dividir em arquivos
//!TODO organizar

#include "funcoes.h"

void gera_numeros () {

    int i,j, v[40];

    for (i = 0; i < 40; i++) v[i] = 0;
    srand( (unsigned)time(NULL) );

    for (i = 0; i < 40; i++) {
       j = rand() % 40;
       while (v[j] == 1 ) j = ( j + 1 ) % 40;
       numeros[i] = j;
       v[j] = 1;
    }
    return;
}

int valor_carta (int i) {

    if  (i >= 0 && i <= 39)
        return numeros[i] % 10;
    else
        return -1;
}

char naipe_carta (int i) {

    char naipe[8] = { 'E','P','O','C','P','E','C','O' };

    if (i >= 0 && i <= 39)
        return naipe[numeros[i] / 5];
    else
        return ' ';
}


// aloca elemento e retorna
st_elemento *cria_elemento(int valor, char naipe)
{
    st_elemento *elemento = NULL;

    if(!(elemento = (st_elemento*)malloc(sizeof(st_elemento))))
    {
        printf("Falta de memoria!\n");
        exit(1);
    }
    
    elemento->valor = valor;
    elemento->naipe = naipe;
    
    return elemento;
}


/*// aloca lista circular e retorna
st_lista_circular *cria_lista_circular(int visivel)
{
    st_lista_circular *lista = NULL;
    
    if(!(lista = (st_lista_circular*)malloc(sizeof(st_lista_circular))))
    {
        printf("Falta de memoria!\n");
        exit(1);
    }
    
    lista->visivel = visivel;
    lista->carta = NULL;
    lista->ant = NULL;
    lista->prox = NULL;
    return lista;
}*/


// cria descritor pilha e retorna
tipo_descritor_pilha *cria_descritor_pilha(void)
{
    tipo_descritor_pilha *descritor = NULL;

    if(!(descritor = (tipo_descritor_pilha*)malloc(sizeof(tipo_descritor_pilha))))
    {
        printf("Falta de memoria!\n");
        exit(1);
    }

    descritor->n = 0;
    descritor->topo = NULL;

    return descritor;
}

// cria pilha e retorna
st_pilha *cria_pilha(st_elemento *carta, int visivel)
{
    st_pilha *pilha = NULL;

    pilha = (st_pilha*)malloc(sizeof(st_pilha));
    pilha->carta = carta;
    pilha->visivel = visivel;
    pilha->prox = NULL;

    return pilha;
}

// insere na pilha
void insere_pilha(tipo_descritor_pilha *descritor_pilha, st_elemento *elemento, int visivel)
{
    if(!descritor_pilha) return;

    tipo_descritor_pilha *percorrer = NULL;
    st_pilha *pilha = NULL;

    percorrer = descritor_pilha;
    pilha = cria_pilha(elemento, visivel);

    // pilha vazia
    if(!percorrer->topo)
    {
        percorrer->topo = pilha;
        percorrer->n++;
        return;
    }

    // insere no fim
    percorrer->n++;
    pilha->prox = percorrer->topo;
    percorrer->topo = pilha;

}


void imprime(tipo_descritor_pilha *descritor, int n)
{
	if(!descritor) return;

 	if(!descritor->topo) printf("[--]\t");
	else printf("[%d%c]\t", descritor->topo->carta->valor, descritor->topo->carta->naipe);
}



// insere no inicio
tipo_descritor_pilha *insere_inicio(tipo_descritor_pilha *descritor_pilha)
{
    if(!descritor_pilha) return NULL;

    tipo_descritor_pilha *novo = cria_descritor_pilha();

    st_pilha *percorrer = descritor_pilha->topo;

    while(percorrer)
    {
        insere_pilha(novo, cria_elemento(percorrer->carta->valor, percorrer->carta->naipe), percorrer->visivel);
        percorrer = percorrer->prox;
    }
    return novo;
}

//imprime pilha invertida
void imprime_pilha_invertida(tipo_descritor_pilha *descritor_pilha[], int n)
{
    int i = 0, repetir = 1;
    st_pilha *p[n];
    tipo_descritor_pilha *t[n];

    for(i = 0; i < n; i++){
        if(descritor_pilha[i])
            t[i] = insere_inicio(descritor_pilha[i]);
        else t[i] = NULL;
    }

    for(i = 0; i < n; i++){
    	printf("=P%d=\t", i);
        if(t[i])
            p[i] = t[i]->topo;
        else p[i] = NULL;
    }
    
	printf("\n");
    while(repetir)
    {
        repetir = 0;
        for(i = 0; i < n; i++)
        {
            if(p[i])
            {
            	if(p[i]->visivel)
            	{
               		printf("[%d%c]\t", p[i]->carta->valor, p[i]->carta->naipe);
               	}
               	else printf("[XX]\t");
                p[i] = p[i]->prox;
                repetir = 1;
            }
            else if(i < (n - 1)) printf("\t");
        }
        printf("\n");
    }
}

// remove elemento da pilha
void remove_pilha(tipo_descritor_pilha *descritor_pilha)
{ 
    if(!descritor_pilha) return NULL;

    st_pilha *remover = descritor_pilha->topo;

    if(remover)
    {
        descritor_pilha->topo = remover->prox;
        descritor_pilha->n--;
        free(remover);
    }
}


// cria descritor lista e retorna
tipo_descritor_lista *cria_descritor_lista(void)
{
    tipo_descritor_lista *descritor = NULL;

    if(!(descritor = (tipo_descritor_lista*)malloc(sizeof(tipo_descritor_lista))))
    {
        printf("Falta de memoria!\n");
        exit(1);
    }

    descritor->n = 0;
    descritor->prim = NULL;
    descritor->ult = NULL;

    return descritor;
}


// insere na lista
void insere_lista(tipo_descritor_lista *descritor, st_elemento *carta, int visivel)
{
    if(!descritor) return;

    tipo_descritor_lista *percorrer = NULL;
    st_lista_circular *lista = NULL;

    percorrer = descritor;
    lista = cria_lista(carta, visivel);

    // lista vazia
    if(!percorrer->prim && !percorrer->ult)
    {
        percorrer->prim = lista;
        percorrer->ult = lista;
        lista->ant = lista;
        lista->prox = lista;
        percorrer->n++;
        return;
    }

    // insere no fim
    percorrer->n++;
    percorrer->ult->prox = lista;
    lista->ant = percorrer->ult;
    lista->prox = percorrer->prim;
    percorrer->prim->ant = lista;
    percorrer->ult = lista;
}


// cria lista e retorna
st_lista_circular *cria_lista(st_elemento *carta, int visivel)
{
    st_lista_circular *lista = NULL;

    lista = (st_lista_circular*)malloc(sizeof(st_lista_circular));
    lista->carta = carta;
    lista->visivel = visivel;
    lista->ant = lista;
    lista->prox = lista;

    return lista;
}


// imprime lista
void imprime_lista(tipo_descritor_lista *descritor)
{
	st_lista_circular *percorrer = NULL;


	if(!descritor || !descritor->prim) return;

	percorrer = descritor->prim;

	while(percorrer)
	{
		printf("[%d%c]\n", percorrer->carta->valor, percorrer->carta->naipe);
		percorrer = percorrer->prox;
	}
}

// imprime elemento da lista
void imprime_elemento_lista(st_lista_circular *atual)
{
	if(!atual) printf("[--]");
	else printf("[%d%c]", atual->carta->valor, atual->carta->naipe);
}


// remove elemento da pilha e retorna
st_elemento *get_elemento_pilha(tipo_descritor_pilha *descritor_pilha)
{ 
    if(!descritor_pilha) return NULL;

    st_pilha *remover = descritor_pilha->topo;
	st_elemento *carta = NULL;

    if(remover)
    {
        descritor_pilha->topo = remover->prox;
        descritor_pilha->n--;
        carta = remover->carta;
        remover->carta = NULL;
        // torna a proxima carta visivel
        if(descritor_pilha->topo)
        {
        	if(descritor_pilha->topo->carta)
        		descritor_pilha->topo->visivel = 1;
        }
        free(remover);

        return carta;
    }
    return NULL;
}

// remove elemento da lista e retorna
st_elemento *get_elemento_lista(tipo_descritor_lista *descritor, st_lista_circular *atual)
{
	if(!descritor || ! atual) return NULL;

	st_elemento *carta = NULL;

	if(atual->ant == atual)
	{
		descritor->prim = NULL;
		descritor->ult = NULL;
		descritor->n--;
		carta = atual->carta;
		atual->carta = NULL;
		free(atual);

		return carta;
	}
	if(descritor->prim == atual)
	{
		descritor->prim = atual->prox;
	}
	else if(descritor->ult == atual)
	{
		descritor->ult = atual->ant;
	}

	atual->prox->ant = atual->ant;
	atual->ant->prox = atual->prox;

	carta = atual->carta;
	atual->carta = NULL;
	descritor->n--;
	free(atual);

	return carta;
}


// verifica se as cartas podem ser empilhadas na pilha de fileiras
int possivel_mover_fileira(st_elemento *elemento1, st_elemento *elemento2)
{
	if(!elemento1) return 0;
	if(!elemento2) return 1;

	if(elemento1->valor == (elemento2->valor - 1))
	{
		if((elemento2->naipe == 'E' 
			|| elemento2->naipe == 'P') 
			&& (elemento1->naipe == 'C' 
				|| elemento1->naipe == 'O'))
		{
			return 1;
		}
		else if((elemento2->naipe == 'C' 
			|| elemento2->naipe == 'O') 
			&& (elemento1->naipe == 'E'
				|| elemento1->naipe == 'P'))
		{
			return 1;
		}
	}

	return 0;
}

// retorna elemento do topo da pilha
st_elemento *consulta_pilha(tipo_descritor_pilha *descritor_pilha)
{
    if(!descritor_pilha) return NULL;

    if(descritor_pilha->topo) return descritor_pilha->topo->carta;
    
    return NULL;
}

// verifica se as cartas podem ser empilhadas na pilha de naipe
int possivel_mover_naipe(st_elemento *elemento1, st_elemento *elemento2)
{
	if(!elemento1) return 0;
	if(!elemento2)
	{
		if(elemento1->valor == 0) return 1;
		else return 0;
	}

	if(elemento1->valor == (elemento2->valor + 1))
	{
		if(elemento1->naipe == elemento2->naipe)
			return 1;
	}

	return 0;
}

// verifica se o jogador venceu a partida
int venceu(tipo_descritor_pilha *descritor_pilha[], int n)
{
	if(!descritor_pilha) return 0;

	int i = 0, venceu = 1;

	for(i = 0; i < n; i++)
	{
		if(descritor_pilha[i]->topo)
		{
			if(descritor_pilha[i]->topo->carta->valor != 9)
				venceu = 0;
		}
		else venceu = 0;
	}
	
	return venceu;
}