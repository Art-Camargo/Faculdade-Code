#include <stdio.h>
#define TAM 10
main()
{
	int i, j, matriz[TAM][TAM], aux = 1;
	for(i=0; i<TAM; i++){
		for(j=0; j<=i; j++){
			if(j == 0){
				aux = 1;
				matriz[i][j] = aux;
			}
			else{
				aux++;
				matriz[i][j] = aux;
			}
		}
	}
	for(i=0; i<TAM; i++){
		for(j=0; j<=i; j++){
			printf("%d ", matriz[i][j]);
		}
		printf("\n");
	}
}
