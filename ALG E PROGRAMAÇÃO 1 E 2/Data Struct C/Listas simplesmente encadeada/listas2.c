#include <stdio.h>
#include <stdlib.h>
typedef struct no {
	int value;
	struct no *next;
}node;

int le_valor() {
	int num;
	printf("\nInforme um valor para adicionar a pilha: ");
	scanf("%d", &num);
	return num;
}

void push(node **FirstPoint, int valor) {
	node *NovoPonteiro;
	NovoPonteiro = (node*)malloc(sizeof(node));
	if(NovoPonteiro != NULL) {
		NovoPonteiro->value = valor;
		if(*FirstPoint == NULL){
			NovoPonteiro->next = NULL;
			*FirstPoint = NovoPonteiro;	
		}
		else {
			NovoPonteiro->next = *FirstPoint;
			*FirstPoint = NovoPonteiro;
		}
	}
}

void pop(node **FirstPointer) {
	node *PointerStruct = *FirstPointer;
	if(*FirstPointer == NULL) { 
		printf("\nNao e possivel dar pop na pilha!!");
	} 
	else { 
		*FirstPointer = PointerStruct->next;
		free(PointerStruct);
	}
}

void printStack(node *InicioStack) {
	node *toEndStack;
	if(InicioStack == NULL) {
		printf("\nNao ha pilha para printar!");
	} 
	else {
		toEndStack = InicioStack;
		while(toEndStack != NULL) {
			printf("%d   ", toEndStack->value);
			toEndStack = toEndStack->next;
		}
	}
}

void FreeMemory(node **IndexPoint) {
	node *StructP = *IndexPoint, *prox;
	while(StructP != NULL) {
		prox = StructP->next;
		free(StructP);
		StructP = prox;
	}
}
int main(){
	int continua, val, op;
	node *first = NULL;
	do {
		system("cls||clear");
		do {
			printf("\n1 - Push");
			printf("\n2 - Pop");
			printf("\n3 - Imprime Lista");
			printf("\nEscolha uma opcao: ");	
			scanf("%d", &op);
		}while(op > 3|| op < 1);
		switch(op) {
			case 1:
				val = le_valor();
				push(&first, val);
			break;
			case 2:
				pop(&first);
			break;
			case 3:
				printStack(first);
			break;
		}
		do {
			printf("\n1 - SIM");
			printf("\n0 - NAO");
			printf("\nDeseja Continua: ");
			scanf("%d", &continua);
		} while(continua > 1 || continua < 0);
	}while(continua == 1);
	FreeMemory(&first);
	return 0;
}
