#include <stdio.h>
main()
{
	int mat[5][5], i, j, vetor[25], cont=-1;
	for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		{
			printf("\nInforme o valor da posicao [%d, %d]: ", i, j);
			scanf("%d", &mat[i][j]);
			while(mat[i][j] <= 10 || mat[i][j]%2!=0)
			{
				printf("\nInforme o valor valido da posicao [%d, %d]: ", i, j);
				scanf("%d", &mat[i][j]);
			}
		}
	}
	printf("\n\nMATRIZ DADA PELO TECLADO ABAIXO\n\n");
	for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		{
			printf("  %d  ", mat[i][j]);
		}
		printf("\n");
	}
	for(i=0; i<5; i++)
	{
		mat[i][i]=mat[i][4-i];
	}
	printf("\n\nMATRIZ MODIFICADA abaixo!\n\n");
	for(i=0; i<5; i++)
	{
		for(j=0; j<5; j++)
		{
			printf("  %d  ", mat[i][j]);
			if(mat[i][j]>40)
			{
				cont++;
				vetor[cont] = mat[i][j];
			}
		}
		printf("\n");
	}
	printf("\n\nVetor de trás pra frente abaixo!\n");
	for(i=cont; i>=0; i--)
	{
		printf("  %d ", vetor[i]);
	}
}
