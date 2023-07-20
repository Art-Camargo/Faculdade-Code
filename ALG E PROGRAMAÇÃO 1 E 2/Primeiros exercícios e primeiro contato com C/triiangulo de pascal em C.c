//triangulo de pascal em C
#include <stdio.h>
#define TAM 5
int main()
{
	int i, j, mat[TAM][TAM];
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			mat[i][j] = 0;
		}
	}
	for(i=0; i<TAM; i++){
		for(j=0; j<=i; j++){
			if(j == i || j == 0){
				mat[i][j] = 1;
			}
			else{
				mat[i][j] += mat[i - 1][j - 1] + mat[i - 1][j];
			}
		}
	}
	for(i=0; i<TAM; i++){
		for(j=0; j<=i; j++){
			printf("%d ", mat[i][j]);
		}
		printf("\n");
	}

	return 0;
}
