#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct no{
	int value;
	struct no *next;	
}No;

void insere_inicio(No **IndexPointer, int valor, No **auxPoint, int *countador){
	No *ponteiro;
	ponteiro = (No*)malloc(sizeof(No));
	if(ponteiro != NULL){ //Valida se é possível alocar dinamicamente a memória
		(*countador)++;
		ponteiro->value = valor; //atribui o valor ao struct, com o seu ponteiro reservado
		if(*IndexPointer == NULL){ //se for feito a primeira vez, o index do inicio é igual a NULL
			ponteiro->next = NULL; //ponteiro aponta pra NULL, pro começo
			*IndexPointer = ponteiro; //ponteiro do inicio muda, não sendo mais NULL, pois dps irá apontar para o numero ja digitado
			*auxPoint = ponteiro;
		}
		else{
			ponteiro->next = *IndexPointer; //se n for a primeira vez, o ponteiro do struct apontará para o valor anterior
			*IndexPointer = ponteiro; //muda-se o valor do primeiro ponteiro de novo.
			*auxPoint = ponteiro;
		}
	}
}

void imprime_lista(No *PointerAtual) {
    No *ponteiroImprime = PointerAtual; //aponta para onde o ponteiro parou
    while (ponteiroImprime != NULL) { //se for diferente de NULL, ou seja, se o ponteiro ja apontar para algo, quer dizer que ja tem um numero na lista
        printf("%d  ", ponteiroImprime->value); //printa o valor
        ponteiroImprime = ponteiroImprime->next; //ponteiro muda para o anterior, até chegar no ultimo que é == NULL
    }
}

void insere_fim(No **IndPoint, int val, int *counter){
	No *StructPointer = (No*)malloc(sizeof(No));
	if(StructPointer != NULL){  // 1   1   2   3   
		(*counter)++;
		StructPointer->next = NULL;
		StructPointer->value = val;
		if(*IndPoint == NULL) { // empty list
			*IndPoint = StructPointer;
		} 
		else {
			No *FinalPointerList = *IndPoint;
			while(FinalPointerList->next != NULL ){
				FinalPointerList = FinalPointerList->next;
			}
			FinalPointerList->next = StructPointer;
		}
	}
}


int le_valor(){
	int num;
	printf("\nInforme um numero para a lista: ");
	scanf("%d", &num);
	return num;
}

int menu(){
	int op;
	printf("\n1 - Inserir no inicio da lista");
	printf("\n2 - Inserir no fim da lista");
	printf("\n3 - Imprimir a lista");
	printf("\n4 - Inserir no meio da lista");
	printf("\n5 - FIM");
	printf("\nInforme uma opcao: ");
	scanf("%d", &op);
	while(op < 1 || op > 5){
		system("cls||clear");
		printf("\n1 - Inserir no inicio da lista");
		printf("\n2 - Inserir no fim da lista");
		printf("\n3 - Imprimir a lista");
		printf("\n4 - FIM");
		printf("\nInforme uma opcao: ");
		scanf("%d", &op);
	}
}

void insere_meio(No **PonteiroTop, int num1, int *contador) {
	No *NewPoint = (No*)malloc(sizeof(No)), *PointAux = *PonteiroTop;
	int aux_count = 0;
	if(NewPoint != NULL) {
		(*contador)++;
		if(*PonteiroTop == NULL) {
			NewPoint->value = num1;
			NewPoint->next = NULL;
			*PonteiroTop = NewPoint;
		}
		else {
			while(aux_count < ( *contador / 2) - 1) {
				PointAux = PointAux->next;
				aux_count++;
			}
			NewPoint->value = num1;
			NewPoint->next = PointAux->next;
			PointAux->next = NewPoint;
		}
	}
}

int main(){
	No *firstPoint = NULL, *FirstPEver = NULL;
	int continua, numero, count = 0;
	do {
		continua = menu();
		system("cls||clear");
		switch(continua){
			case 1:
				numero = le_valor();
				insere_inicio(&firstPoint, numero, &FirstPEver, &count);
			break;
			case 2:
				numero = le_valor();
				insere_fim(&firstPoint, numero, &count);
			break;
			case 3:
				*firstPoint = *FirstPEver;
				imprime_lista(firstPoint);
			break;
			case 4:
				*firstPoint = *FirstPEver;
				numero = le_valor();
				insere_meio(&firstPoint, numero, &count);
			break;
			case 5:
				printf("\nPrograma Finalizado!!!!!!!!!!");
			break;
		}
	}while(continua != 5);
	return 0;
}
