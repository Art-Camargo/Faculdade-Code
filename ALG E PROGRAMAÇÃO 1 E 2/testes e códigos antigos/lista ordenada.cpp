#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int value;
	struct no* next;	
}No;

void push(No **PonteiroInicio, int val) {
	No *proxP;
	proxP = (No*)malloc(sizeof(No));
	if(proxP != NULL) {
		proxP->value = val;
		if(*PonteiroInicio == NULL) {
			proxP->next = NULL;
			*PonteiroInicio = proxP;
		}
		else {
			proxP->next = *PonteiroInicio;
			*PonteiroInicio = proxP;
		}
	}
}

int le_valor() {
	int num;
	printf("\nInforme o valor: ");
	scanf("%d", &num);
	return num;
}

void PreencherVetor(No *ponteiroF, int vet[]) {
	No *ponteiroAux = ponteiroF;
	int j;
	for(j = 0; j < 10; j++) {
		vet[j] = ponteiroAux->value;
		ponteiroAux = ponteiroAux->next;
	}
}

void BSort(int vect[]) {
	int k, aux;;
	for(k = 0; k < 9; k++) {
		if(vect[k] > vect[k + 1]) {
			aux = vect[k];
			vect[k] = vect[k + 1];
			vect[k + 1] = aux;
			k = -1;
		}
	}	
}

void printa_vetor(int vetor1[]) {
	int y;
	for(y = 0; y < 10; y++) {
		printf("%d   ", vetor1[y]);
	}
}

int main() {
	int i, valor;
	No *inicioP = NULL;
	int *vetor;
	for(i = 0; i < 10; i++) {
		valor = le_valor();
		push(&inicioP, valor);
	}
	vetor = (int*)malloc(10 * sizeof(int));
	if(vetor != NULL) {
		PreencherVetor(inicioP, vetor);
		BSort(vetor);
		printa_vetor(vetor);
	}
	return 0;
}
