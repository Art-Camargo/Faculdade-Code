#include <stdio.h>
main()
{
	int i, j, mat[4][4];
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			printf("INFORME O VALOR DA POSICAO [%d, %d]: ", i, j);
			scanf("%d", &mat[i][j]);
		}
	}
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			if(mat[i][j] < 0){
				mat[i][j] = mat[i][j] * -1;
			}
		}
	}
	for(i=0; i<4; i++){
		for(j=0; j<4; j++){
			printf("%d |", mat[i][j]);
		}
		printf("\n");
	}
	
}
