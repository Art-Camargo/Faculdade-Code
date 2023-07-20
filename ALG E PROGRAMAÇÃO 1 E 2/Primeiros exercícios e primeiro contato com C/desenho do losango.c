#include <stdio.h>
#define TAM 33
main()
{
	int i, j, auxJ, contaJ, auxI;
	char matriz[TAM][TAM];
	for(i=0; i<TAM; i++)
	{
		for(j=0; j<TAM; j++)
		{
			matriz[i][j] = ' ';	
		}
	}
	auxJ = TAM/2;
	contaJ = TAM/2;
	auxI = TAM/2;
	for(i=0; i<TAM; i++)
	{
		for(j=0; j<TAM; j++)
		{
			if(i == TAM-TAM || i == TAM - 1)
			{
				auxJ = (TAM/2);
				if(j==auxJ)
				{
					matriz[i][j] = 'X';
				}	
			}
			else
			{
				if(i <= auxI)
				{
					
					if(j == TAM - TAM)
					{
						auxJ++;
						contaJ--;
					}
					if(j==auxJ || j==contaJ)
					{
						
						matriz[i][j] = 'X';
					}
				}
				else
				{
					if(j == TAM - TAM)
					{
						auxJ--;
						contaJ++;
					}
					if(j==auxJ || j==contaJ)
					{
						matriz[i][j] = 'X';
					}
					
				}
			}
		}	
	}
	for(i=0; i<TAM; i++)
	{
		for(j=0; j<TAM; j++)
		{
			printf("%c", matriz[i][j]);
		}
		printf("\n");
	}
}

