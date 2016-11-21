#include "funcoes.h"

// main
int main()
{
	int opcao = 0, carga;

	Trem *trem = criar_trem();
	do{
		printf("Selecione uma opcao:\n1 - Inserir Carga\n2 - Remover Carga\n3 - Mostrar Vagoes\n4 - Sair\n");
		scanf("%d", &opcao);

		switch(opcao)
		{
			case 1:
				printf("Digite a carga: (inteiro)\n");
				scanf("%d", &carga);
				if(inserir_carga(trem, carga))
				{
					printf("Erro ao inserir carga!\n");
					exit(1);
				}

				break;

			case 2:
				printf("Digite a carga: (inteiro)\n");
				scanf("%d", &carga);
				if(remover_carga(trem, carga))
				{
					printf("Erro ao remover carga!\n");
					exit(1);
				}
				break;

			case 3:
				imprimir_trem(trem);
				break;

			default: break;
		}
	} while(opcao != 4);

	return 0;
}