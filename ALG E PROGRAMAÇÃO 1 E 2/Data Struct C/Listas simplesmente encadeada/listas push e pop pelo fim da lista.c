#include <stdio.h>
#include <stdlib.h>

typedef struct no {
	int value;
	struct no *next;
}No;

int le_valor() {
	int val;
	printf("\nInforme um valor: ");
	scanf("%d", &val);
	return val;	
}

void empilha_fim(No **TopoLista, int valor) {
	No *ponteiro = (No*)malloc(sizeof(No)), *ponteiroFinal = *TopoLista;
	if(ponteiro != NULL) {
		ponteiro->value = valor;
		if(*TopoLista == NULL) {
			*TopoLista = ponteiro;
		}
		else {
			while(ponteiroFinal->next != NULL) {
				ponteiroFinal = ponteiroFinal->next;
			}
			ponteiroFinal->next = ponteiro;
		}
		ponteiro->next = NULL;
	}
}

void desempilha(No **InicioAtual) {
	No *ponteiroFree = *InicioAtual, *ponteiroAnt = NULL;
	if(ponteiroFree == NULL) {
		printf("\nNao e possivel dar pop pelo fim");
	}
	else {
		if(ponteiroFree->next == NULL) {
			free(ponteiroFree);
			*InicioAtual = NULL;
		}
		else {
			while(ponteiroFree->next != NULL) {
				ponteiroAnt = ponteiroFree;
				ponteiroFree = ponteiroFree->next;
			}
			free(ponteiroFree);
			ponteiroAnt = NULL;
		}
	}
}

int main() {
	No *inicio = NULL;
	int continua, num;
	do {
		printf("\n1 - Empilhar pelo Fim");
		printf("\n2 - Desempilhar pelo Fim");
		printf("\n3 - Imprimir Lista");
		printf("\n4 - FIM");
		printf("\nEscolha uma opcao: ");
		scanf("%d", &continua);
		while(continua < 1 || continua > 4) {
			printf("\nEscolha uma opcao valida: ");
			scanf("%d", &continua);
		}
		if(continua != 4) {
			switch(continua) {
				case 1:
					num = le_valor();
					empilha_fim(&inicio, num);
				break;
				case 2:
					desempilha(&inicio);
				break;
				case 3:
				break;
			}
		}
	} while(continua != 4);
	return 0;	
}
