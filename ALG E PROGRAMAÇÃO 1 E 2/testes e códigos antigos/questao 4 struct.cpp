#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct data{
	char marca[15];
	int ano;
	float preco;   
}dados_carros;

void LeDadosCarros(dados_carros carros[]){
	int i;
	for(i = 0; i < 5; i ++){
		printf("\nInforme a marca do carro: ");
		fgets(carros[i].marca, 15, stdin);
		fflush(stdin);
		carros[i].marca[strcspn(carros[i].marca, "\n")] = '\0';
		
		do{
			printf("\nInforme o ano do carro: ");
			scanf("%d", &carros[i].ano);
		}while(carros[i].ano > 2023 || carros[i].ano < 1900);
		
		do{
			printf("\nInforme o preco do carro: (> 0): ");
			scanf("%f", &carros[i].preco);
		}while(carros[i].preco <= 0.0);
		getchar();
	}
}

void imprimeInfo(dados_carros marcasCarros[]){
	float value;
	int k;
	do {
		printf("\nInforme um valor para busca:  ");
		scanf("%f", &value);
		while(value < 0.0){
			printf("\nInforme um valor para busca:  ");
			scanf("%f", &value);
		}
		for(k=0; k<5; k++){
			if (marcasCarros[k].preco == value) {
			    printf("\nMarca: %s", marcasCarros[k].marca);
			    printf("Ano: %d\n", marcasCarros[k].ano);
			    printf("Preco: %.2f\n", marcasCarros[k].preco);
			}
		}
	}while(value != 0.0);
}
int main(){
	dados_carros autorias[5];
	LeDadosCarros(autorias);
	imprimeInfo(autorias);
	return 0;
}

