
#include <stdio.h>
#define TAM 4
main()
{
	int palindromo[TAM], i, count = 0;
	for(i=0; i<TAM; i++){
		printf("\nINFORME O VALOR POSITIVO DA POSICAO %d: ", i+1);
		scanf("%d", &palindromo[i]);
		while(palindromo[i] < 0){
			printf("\nINFORME O VALOR VALIDO E POSITIVO DA POSICAO %d: ", i+1);
			scanf("%d", &palindromo[i]);
		}
	}
	for(i=0; i<TAM; i++){
		if(palindromo[i] == palindromo[(TAM - 1) - i]){
			count++;
		}
	}
	if(count == TAM){
		printf("\no numero e palindromo!!!!");
	}
	else{
		printf("\no numero n e palindromo!!!!");
	}
}
