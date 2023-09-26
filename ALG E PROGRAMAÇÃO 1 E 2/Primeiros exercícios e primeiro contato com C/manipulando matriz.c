#include <stdio.h>
#define TAM 6
main() {
	int i, j, matriz[TAM][TAM], aux = TAM - 1, acima=0, abaixo=0;
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			printf("\nINFORME O VALOR DA POSICAO [%d, %d]: ", i, j);
			scanf("%d", &matriz[i][j]);
		}
	}
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			if(i != TAM - 1){
				if(j==0){
					aux--;
				}
				if(j <= aux){
					acima += matriz[i][j];
				}
			}
		}
	}
	aux = TAM - 1;
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			if(i != 0){
				if(j == 0 && i != 1){
					aux--;
				}
				if(j >= aux){
					abaixo += matriz[i][j];
				}
			}
		}
	}
	printf("\na soma dos numeros acima da diagonal secundaria ==== %d", acima);
	printf("\n soma dos numeros abaixo da diagonal secundaria ==== %d", abaixo);
}
