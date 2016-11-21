#include "funcoes.h"


// Cria vagao
Vagao *criar_vagao(int carga)
{
	Vagao *vagao = (Vagao*)malloc(sizeof(Vagao));
	vagao->carga = carga;
	vagao->prox = NULL;

	return vagao;
}


// Cria trem
Trem *criar_trem()
{
	Trem *trem = (Trem*)malloc(sizeof(Trem));
	trem->n_vagoes = 0;
	trem->ult_vagao = NULL;

	return trem;
}


/* Se tiver lugar vago insere carga no ultimo vagao, 
se não possuir, adiciona mais um vagão. Recursivamente */
int inserir_carga(Trem *trem, int carga)
{
	// Trem nao inicializado
	if(!trem) return 1;

	// Nao ha carga para ser inserida
	if(carga == 0) return 0;

	// Trem sem vagoes, cria vagao sem carga
	if(!trem->ult_vagao)
	{
		Vagao *vagao = criar_vagao(0);
		trem->ult_vagao = vagao;
		trem->n_vagoes++;
	}

	/* Ultimo vagao com espaco disponivel, 
	insere carga no ultimo vagao */
	if(trem->ult_vagao->carga < MAX)
	{
		while(trem->ult_vagao->carga < 40 && carga > 0)
		{
			trem->ult_vagao->carga++;
			carga--;
		}
	}

	/* Ultimo vagao sem espaco disponivel. Cria vagao */
	else
	{
		Vagao *vagao = criar_vagao(0);
		vagao->prox = trem->ult_vagao;
		trem->ult_vagao = vagao;
		trem->n_vagoes++;

		while(trem->ult_vagao->carga < 40 && carga > 0)
		{
			trem->ult_vagao->carga++;
			carga--;
		}		
	}

	if(inserir_carga(trem, carga))
	{
		printf("Erro ao inserir carga!\n");
		exit(1);
	}

	return 0;
}


/* Remove uma quantidade de carga a partir do ultimo vagão. 
Se a quantidade de carga removida esvazia o vagão, 
ele é removido do trem. Recursivamente */
int remover_carga(Trem *trem, int carga)
{
	// Trem nao inicializado
	if(!trem) return 1;

	// Nao ha carga para ser removida
	if(carga == 0) return 0;

	// Trem sem vagoes
	if(!trem->ult_vagao)
	{
		printf("Trem sem vagoes, impossivel remover %d tol.\n", carga);
		return 0;
	}

	// Remove carga do ultimo vagao
	while(trem->ult_vagao->carga > 0 && carga > 0)
	{
		trem->ult_vagao->carga--;
		carga--;
	}

	// Vagao sem carga, remove vagao
	if(trem->ult_vagao->carga == 0)
	{
		Vagao *remover = NULL;

		remover = trem->ult_vagao;
		trem->ult_vagao = trem->ult_vagao->prox;
		trem->n_vagoes--;
		remover->prox = NULL;

		free(remover);
	}

	if(remover_carga(trem, carga))
	{
		printf("Erro ao remover carga!\n");
		exit(1);
	}

	return 0;
}


// Exibe vagoes e a quantidade de carga de cada um
int imprimir_trem(Trem *trem)
{
	// Trem nao inicializado
	if(!trem) return 0;

	// Trem sem vagoes
	if(!trem->ult_vagao)
	{
		printf("Trem sem vagoes.\n");
		return 0;
	}

	Vagao *percorrer = NULL;

	percorrer = trem->ult_vagao;
	int i = trem->n_vagoes;
	while(percorrer)
	{
		printf("Vagao: %d, Carga: %d\n", i, percorrer->carga);
		i--;
		percorrer = percorrer->prox;
	}

	return 0;
}