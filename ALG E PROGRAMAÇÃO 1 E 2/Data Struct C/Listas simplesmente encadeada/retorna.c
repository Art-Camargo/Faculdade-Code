#include <stdio.h>
#include <stdlib.h>

typedef struct filemain {
  int value;
  struct filemain *next;
}filemain;

typedef struct fileaux {
  int value;
  struct fileaux *next;
}fileaux;

void push(filemain **FirstPoint, int valor) {
	filemain *NovoPonteiro;
	NovoPonteiro = (filemain*)malloc(sizeof(filemain));
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

void pop(filemain **FirstPointer) {
	filemain *PointerStruct = *FirstPointer;
	if(*FirstPointer == NULL) { 
		printf("\nNao e possivel dar pop na pilha!!");
	} 
	else { 
		*FirstPointer = PointerStruct->next;
	}
}


int readValue() {
	int num;
	printf("\nInforme um valor para adicionar a pilha: ");
	scanf("%d", &num);
	return num;
}


void printStack(filemain *InicioStack) {
	filemain *toEndStack;
	if(InicioStack == NULL) {
		printf("\nNao ha pilha para printar!");
	} 
	else {
		toEndStack = InicioStack;
		while(toEndStack != NULL) {
			printf("\nValor: %d, posicao: %p, proximo: %p ", toEndStack->value, toEndStack, toEndStack->next);
			toEndStack = toEndStack->next;
		}
	}
}

void printStackBeginning(fileaux *InicioStack) {
	fileaux *toEndStack;
	if(InicioStack == NULL) {
		printf("\nNao ha pilha para printar!");
	} 
	else {
		toEndStack = InicioStack;
		while(toEndStack != NULL) {
			printf("\nValor: %d, posicao: %p, proximo: %p ", toEndStack->value, toEndStack, toEndStack->next);
			toEndStack = toEndStack->next;
		}
	}
}

int menuOption() {
  int opcao;
  do {
    printf("\n1 - push\n2 - pop\n3 - printa lista atual\n4 - retorna um valor removido\n5 - printar lista original\n6 - fim\nEscolha uma opcao acima: ");
    scanf("%d", &opcao);
  } while(opcao < 1 || opcao > 6);
  return opcao;
}

void fromMainToAux(fileaux **startAux, filemain *start) {
  *startAux = start;
}

void realocMemToList(fileaux *aux, filemain **mainList) {
  if (aux != NULL && aux != *mainList) {
    while(aux->next != *mainList) {
      aux = aux->next;
    }
    *mainList = aux;
  }
  else {
    printf("\nLista é NULL ou a lista esta em seu estado completo!");
  }
}

int main() {
  int op, val;
  filemain *startMain = NULL;
  fileaux *startAux = NULL;
  do {
    printf("\n\n");
    op = menuOption();
    system("clear||cls");
    switch (op) {
      case 1:
        val = readValue();
        push(&startMain, val);
        fromMainToAux(&startAux, startMain);
      break;
      case 2:
        pop(&startMain);
      break;
      case 3:
        printStack(startMain);
      break;
      case 4:
        realocMemToList(startAux, &startMain);
      break;
      case 5:
        printStackBeginning(startAux);
      break;
      case 6:
        printf("\nFim do programa!!");
      break;
    }
  } while(op != 6);
}