#include <stdio.h>
#define TAM 123
main()
{
	int i, j, aux, aux2;
	aux = TAM/2;
	aux2 = aux;
	for(i=0; i<TAM; i++)
	{
		for(j=0; j<TAM; j++)
		{
			if(i==0)
			{
				if(j == aux)
				{
					printf("&");
				}
				else
				{
					printf(" ");
				}
			}
			else
			{
				if(i <= TAM/2)
				{
					if(j == 0)
					{
						aux++;
						aux2--;
					}
					if(j>=aux2 && j<=aux)
					{
						printf("&");
					}
					else
					{
						printf(" ");
					}
				}
				else
				{
					if(j==0)
					{
						aux--;
						aux2++;
					}
					if(j >= aux2 && j<=aux)
					{
						printf("&");
					}
					else
					{
						printf(" ");
					}
				}
			}
		}
		printf("\n");
	}
}
