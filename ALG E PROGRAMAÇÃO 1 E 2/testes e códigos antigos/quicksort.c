#include <stdio.h>
#include <stdlib.h>
void LeVetor(int vet[], int size){
	int i;
	for(i = 0; i < size; i++){
		printf("\nInforme o valor da posicao %d: ", i);
		scanf("%d", &vet[i]);
	}
}
void QuickSort(int vect[], int tam, int maior){
	int aux;
	if(tam > 1){
		if(maior > 0){
			if(vect[maior] < vect[maior - 1]){
				aux = vect[maior];
				vect[maior] = vect[maior - 1];
				vect[maior - 1] = aux;
				QuickSort(vect, tam, maior - 1); 
			}	
		}
		else{
			if(vect[maior] > vect[maior + 1]){
				aux = vect[maior];
				vect[maior] = vect[maior + 1];
				vect[maior + 1] = aux;
				QuickSort(vect, tam, maior + 1); 
			}	
		}
	}
}
int main(){
	int *vetor, tamanho, high;
	do{
		printf("\nInforme o tamanho do vetor: ");
		scanf("%d", &tamanho);
	}while(tamanho < 1);
	vetor = (int *) malloc(tamanho * sizeof(int));
	high = tamanho - 1;
	if(vetor != NULL){
		LeVetor(vetor, tamanho);
		QuickSort(vetor, tamanho, high);
	}
	else{
		printf("\nMemoria insuficiente");
	}
	free(vetor);
	return 0;
}
