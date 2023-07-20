#include <stdio.h>
#include <stdlib.h>
typedef struct no {
	int value;
	struct no *next;
}node;

void Push(node **TopStack, int val) {
	node *ponteiro;
	ponteiro = (node*)malloc(sizeof(node));
	if(ponteiro != NULL) {
		ponteiro->value = val;
		if(*TopStack == NULL) {
			ponteiro->next = NULL;
			*TopStack = ponteiro;
		}
		else {
			ponteiro->next = *TopStack;
			*TopStack = ponteiro;
		}
	}
}

void printList(node vetor[]) {
	int k;
	for(k = 0; k < 10; k++) {
		printf("%d   ", vetor[k].value);
	}	
}

void BubbleSortList(node vector[]) {
	int j, aux;
	for(j = 0; j < 9; j++) {
		if(vector[j + 1].value < vector[j].value) {
			aux = vector[j].value;
			vector[j].value = vector[j + 1].value;
			vector[j + 1].value = aux;
			j = -1;
		}
	}	
}

void PreencheVetAux(node vetorAux[], node *PonteiroAtual) {
	int y;
	node *AuxPoint = PonteiroAtual;
	for(y = 0; y < 10; y++) {
		vetorAux[y].value = AuxPoint->value;
		printf("%d  ", vetorAux[y].value);
		AuxPoint = AuxPoint->next;
	}
	printf("\n\n\n");
} 

int main() {
	int i, valor, count = 0;
	node *FirstPoint = NULL, *qtd_list;
	for(i = 0; i < 10; i++) {
		printf("\nInforme o numero %d da pilha: ", i);
		scanf("%d", &valor);
		Push(&FirstPoint, valor);
	}
	qtd_list = (node*)malloc(10 * sizeof(node));
	if(qtd_list != NULL) {
		PreencheVetAux(qtd_list, FirstPoint);
		BubbleSortList(qtd_list);
		printList(qtd_list);
	}
	free(qtd_list);
	return 0;
}




