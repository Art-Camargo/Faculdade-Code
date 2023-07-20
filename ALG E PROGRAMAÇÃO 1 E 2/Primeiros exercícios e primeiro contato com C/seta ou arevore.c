

#include <stdio.h>
#define TAM 13
int main()
{

	int i, j, aux = TAM/2, auxj = TAM/2;
	char mat[TAM][TAM];
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			if(i <= TAM/2){
				if(j == 0 && i!=0){
					aux++;
					auxj--;
				}
				if(j >= auxj && j <= aux){
					mat[i][j] = '*';
				}
				else{
					mat[i][j] = ' ';
				}
			}
		}
	}
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			if(i>TAM/2){
				if(j == TAM / 2 || j == (TAM/2) + 1 || j == (TAM/2) - 1){
					mat[i][j] = '*';
				}
				else{
					mat[i][j] = ' ';
				}
			}
		}
	}
	printf("\n\n\n\n\n\n                        \n");
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			printf("%c", mat[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}

