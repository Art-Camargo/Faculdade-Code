
#include <stdlib.h>
#include <stdio.h>
#define TAM 10
int main()
{
	int vet[10], i, random, count = 0;
	for(i=0; i<TAM; i++){
		vet[i] = rand() % 100;
	}
	printf("\nEnter a int [0, 100]: ");
	scanf("%d", &random);
	while(random > 100 || random < 0){
		printf("\nEnter a true int [0, 100]: ");
		scanf("%d", &random);
	}
	for(i=0; i<TAM; i++){
		if(random == vet[i]){
			printf("\n number found in array!!!  index [%d]", i);
		}
		else{
			count++;
		}
	}
	if(count == TAM){
		printf("\nnumber not found in array !!!!");
	}
	return 0;
}

