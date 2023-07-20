#include <stdio.h>
main()
{
	int totalpessoas=0, qtd, qtd_fazendas=0;
	float quantidadegraos, totalrei=0;
	do
	{
		printf("\nInforme a quantidade de graos da sua fazenda: ");
		scanf("%f", &quantidadegraos);
		while(quantidadegraos<0)
		{
			printf("\nInforme a quantidade de graos da sua fazenda: ");
			scanf("%d", &quantidadegraos);
		}
		if(quantidadegraos==0)
		{
			printf("\nPROGRAMA FINALIADO\n");
			printf("\nTOTAL DE FAZENDAS ===== %d", qtd_fazendas);
			printf("\nTOTAL DE PESSOAS ==== %d", totalpessoas);
			printf("\nTOTAL ARMAZENADO PARA O REI ==== %.2f", totalrei);
		}
		else
		{
			qtd_fazendas++;
			printf("\nQUANTAS PESSOAS VIVEM NESSA PROPRIEDADE? ");
			scanf("%d", &qtd);
			while(qtd<=0)
			{
				printf("\nQUANTAS PESSOAS VIVEM NESSA PROPRIEDADE? ");
				scanf("%d", &qtd);	
			}
			totalpessoas += qtd;
			printf("\nPARA ESSA PROPRIEDADE, O REI LEVARA %.2f DOS GRAOS, EQUILVALENTE A 45 por cento", quantidadegraos*0.45);
			totalrei += quantidadegraos*0.45;
		}
	}while(quantidadegraos!=0);
}
