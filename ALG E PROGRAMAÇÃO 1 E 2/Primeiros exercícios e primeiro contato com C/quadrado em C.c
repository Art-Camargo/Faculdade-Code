#include <stdio.h>
main()
{
	int i, j, TAM;
	printf("\nINFORME O TAMANHO DO LADO DO QUADRADO: ");
	scanf("%d", &TAM);
	while(TAM<=0)
	{
		printf("\nINFORME UM TAMANHO  VALIDO PARA O LADO DO QUADRADO: ");
		scanf("%d", &TAM);
	}
	for(i=0; i<TAM; i++)
	{
		for(j=0; j<TAM; j++)
		{
			if(i == 0 || i == TAM - 1)
			{
				printf("* ");
			}
			else
			{
				if(j == 0 || j == TAM - 1)
				{
					printf("* ");
				}
				else
				{
					printf("  ");
				}
			}
		}
		printf("\n");
	}
}
