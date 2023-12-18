#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct no {
	char nome[50];
	struct no *next;	
}No;


void insere_fim(No **TopStack, char name[]) {
	No *ponteiroAtual = (No*)malloc(sizeof(No)), *ToEndStack = *TopStack;
	if(ponteiroAtual != NULL) {
		ponteiroAtual->next = NULL;
		strcpy(ponteiroAtual->nome, name);
		if(*TopStack == NULL) {
			*TopStack = ponteiroAtual;
		}
		else {
			while(ToEndStack->next != NULL) {
				ToEndStack = ToEndStack->next;
			}
			ToEndStack->next = ponteiroAtual;
		}
	}
}


int main() {
	No *PointerMain = NULL, nomesStruct;
	int count = 0;
	do {
		printf("\nInforme o seu nome: ");
		fgets(nomesStruct.nome, 50, stdin);
		fflush(stdin);
		insere_fim(&PointerMain, nomesStruct.nome);
		count++;
	}while(count < 10);
	return 0;
}
