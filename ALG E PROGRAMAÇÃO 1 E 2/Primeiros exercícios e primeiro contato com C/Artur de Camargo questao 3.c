#include <stdio.h>
float consiste_altura(float alt)
{
	while(alt<0)
	{
		printf("\nINFORME UM VALOR VALIDO PARA ALTURA: ");
		scanf("%f", &alt);
	}
	return alt;
}

float media_alturas(float acumulaltura, int somapessoas)
{
	float media;
	media = acumulaltura / somapessoas;
	return media;
}

main()
{
	float altura, maioraltura, menoraltura, somaltura=0;
	int contapessoas=0, conta_menor_media=0, mediatotal;
	do
	{
		printf("\nINFORME A SUA ALTURA EM METROS: ");
		scanf("%f", &altura);
		if(altura < 0){
			altura = consiste_altura(altura);
		}
		if(altura == 0){
			printf("\n\nPROGRAMA FINALIZADO\n\n");
		}
		else{
			contapessoas++;
			somaltura += altura;
			if(contapessoas == 1){
				maioraltura = altura;
				menoraltura = altura;
			}
			else{
				if(altura>maioraltura){
					maioraltura = altura;
				}
				else{
					if(altura<menoraltura){
						menoraltura = altura;
					}
				}
			}
			if(altura<1.50){
				conta_menor_media++;
			}
		}	
	}while(altura!=0);
	printf("\nA MAIOR ALTURA E ======== A %.2f", maioraltura);
	printf("\nA MENOR ALTURA E ======== A %.2f", menoraltura);
	if(contapessoas == 0){
		printf("\nMEDIA ==== 0");
	}
	else{
		printf("\nA MEDIA DAS ALTURAS ====== %.2f", media_alturas(somaltura, contapessoas));
	}
	printf("\nO TOTAL DE ALTURAS MENORES QUE A MEDIA (1.5  metros definido) ====== %d", conta_menor_media);
}

