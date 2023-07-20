#include <stdio.h>
#include <ctype.h>
main()
{
	char jogo[4][4];
	int i, j, cont=0;
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			printf("\nINFORME A LETRA DA POSICAO [%d, %d]: ", i, j);
			scanf("%s", &jogo[i][j]);
			jogo[i][j]=toupper(jogo[i][j]);
		}
	}
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			printf("%c ", jogo[i][j]);
		}
		printf("\n");
	}
	for(i=0; i<4; i++)
	{
		for(j=0; j<4; j++)
		{
			if(i==0)
			{
				if(jogo[i][j] == 'C' && jogo[i + 1][j] == 'A' && jogo[i + 2][j] == 'F' && jogo[i + 3][j] == 'E')
				{
					printf("\nPALAVRA CAFE ENCONTRADA NA POSICAO [%d, %d], [%d, %d], [%d, %d], [%d, %d]!!!!!", i, j, i+1, j, i+2, j, i+3, j);
					cont++;
				}
				else
				{
					if(jogo[i][j] == 'C' && jogo[i][j + 1] == 'A' && jogo[i][j + 2] == 'F' && jogo[i][j + 3] == 'E')
					{
						printf("\nPALAVRA CAFE ENCONTRADA NA POSICAO [%d, %d], [%d, %d], [%d, %d], [%d, %d]!!!!!", i, j , i, j + 1, i, j + 2, i, j + 3);
						cont++;
					}
				}
			}
			else
			{
				if(jogo[i][j] == 'C' && jogo[i][j + 1] == 'A' && jogo[i][j + 2] == 'F' && jogo[i][j + 3] == 'E')
				{
					printf("\nPALAVRA CAFE ENCONTRADA NA POSICAO [%d, %d], [%d, %d], [%d, %d], [%d, %d]!!!!!", i, j , i, j + 1, i, j + 2, i, j + 3);
					cont++;
				}
			}
		}
	}
	for(i=0; i<4; i++)
	{
		for(j=0; i<4; j++)
		{
			if(i==j)
			{
				if(jogo[i][j]== 'C' && jogo[i + 1][j + 1] == 'A' && jogo [i + 2][j + 2]== 'F' && jogo[i + 3][j + 3] == 'E')
				{
					printf("\nA palavra foi encontrada na diagona principal!!!!!! com as posicoes [0, 0], [1, 1], [2, 2], [3, 3]!!");
					cont++;
				}
			}
		}
	}
	if(cont==0)
	{
		printf("\nPALAVRA NAO ENCONTRADA!!!!!!!!!");
	}	
}
