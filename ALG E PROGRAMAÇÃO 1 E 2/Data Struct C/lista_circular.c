#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

int menuOption() {
  int opcao;
  do {
    printf("\n1 - Insere fim\n2 - transforma em circular\n3 - printa lista\n4 - transfora em encadeada novamente");
    printf("\n5 - FIM\nInsira uma opcao desejada: ");
    scanf("%d", &opcao);
  } while(opcao < 1 || opcao > 5);
  return opcao;
}

void printStack(No *InicioStack) {
	No *toEndStack, *aux;
  bool valido = true;
  system("clear");
	if(InicioStack == NULL) {
		printf("\nNao ha pilha para printar!");
	} 
	else {
    toEndStack = InicioStack;
    aux = InicioStack;
		while(toEndStack != NULL && valido) {
      if (toEndStack->next == aux) {
        valido = false;
      }
			printf("\nvalor: %d, current: %p, next: %p", toEndStack->value, toEndStack, toEndStack->next);
      toEndStack = toEndStack->next;
		}
	}
}


void empilha_fim(No **TopoLista, int valor) {
	No *ponteiro = (No*)malloc(sizeof(No)), *ponteiroFinal = *TopoLista;
  bool valido = true;
	if(ponteiro != NULL) {
		ponteiro->value = valor;
		if(*TopoLista == NULL) {
			*TopoLista = ponteiro;
		} 
		else {
			while(ponteiroFinal->next != NULL && valido) {
        if (ponteiroFinal->next == *TopoLista) {
          valido = false;
        }
				else {
          ponteiroFinal = ponteiroFinal->next;
        }
			}
			ponteiroFinal->next = ponteiro;
		}
		if (!valido) {
      ponteiro->next = *TopoLista;
    }
    else {
      ponteiro->next = NULL;
    }
	}
}

void circular(No *doisPiR, No *aux) {
  if (doisPiR == NULL ) {
    printf("\nNAO TEM COMO TRANSFORMAR EM CIRCULAR");
  }
  else {
    if (aux->next == doisPiR || aux->next == NULL) {
      aux->next = doisPiR;
    }
    else {
      circular(doisPiR, aux->next);
    }
  }
}

void encadeado(No *PiRQuadrado, No *auxPi) {
  if (auxPi == NULL ) {
    printf("\nNao ha numeros na lista");
  }
  else {
    if (auxPi->next == PiRQuadrado || auxPi->next == NULL) {
      auxPi->next = NULL;
    } 
    else {
      encadeado(PiRQuadrado, auxPi->next);
    }
  }
}

int main() {
  int op, valor;
  No *inicio = NULL;
  do {
    op = menuOption();
    system("clear");
    switch (op) {
    case 1:
      valor = le_valor();
      empilha_fim(&inicio, valor);
    break;
    case 2:
      circular(inicio, inicio);
    break;
    case 3:
      printStack(inicio);
    break;
    case 4:
      encadeado(inicio, inicio);
    break;
    case 5:
      printf("\nFIM");
    break;
    }
  } while(op != 5);
  return 0;
}