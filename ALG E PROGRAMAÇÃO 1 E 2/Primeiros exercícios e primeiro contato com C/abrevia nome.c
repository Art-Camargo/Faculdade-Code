#include <stdio.h>
#include <string.h>
#include <ctype.h>
main()
{
	char nome[25];
	int i, cont=0;
	printf("Informe o seu nome: \n");
	gets(nome);
	for(i=0; i<strlen(nome); i++)
	{
		nome[i] = toupper(nome[i]);
	}
	for(i=0; i<strlen(nome); i++)
	{
		if(i==0)
		{
			printf("%c", nome[i]);
		}
		else
		{
			if(nome[i] == ' ' && nome[i + 1] == 'D' && (nome[i + 2] == 'A' || nome[i + 2] == 'O' || nome[i + 2] == 'E' ) && nome[i + 3] == ' ')
			{
				cont++;
			}
			else
			{
				if(nome[i] == ' ')
				{
					printf(".");
					printf("%c", nome[i + 1]);
				}
			}
		}
	}
	printf(".");
	if(cont > 0)
	{
		printf("\n\n DE/DA/DO foram desconsiderados da sigla do nome");
	}
}
