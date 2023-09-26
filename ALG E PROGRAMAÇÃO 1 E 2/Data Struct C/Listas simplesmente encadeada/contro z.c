#include <stdio.h>
#include <stdlib.h>

typedef struct pilemain {
  int value;
  struct pilemain *next;
}Pilemain;

typedef struct pileaux {
  int value;
  struct pileaux *next;
}Pileaux;

int menuOption() {
  int opcao;   
  do {
    printf("\n\n1 - empilhar frase\n2 - desempilhar a frase\n3 - printar a lista\n4 - corrigir (control z)\n5 - fim\nInforme uma opcao acima: ");
    scanf("%d", &opcao);
  } while(opcao < 1 || opcao > 5);
  return opcao;
}

void pop(Pilemain **FirstPointer) {
	Pilemain *PointerStruct = *FirstPointer;
	if(*FirstPointer == NULL) { 
		printf("\nNao e possivel dar pop na pilha!!");
	} 
	else { 
		*FirstPointer = PointerStruct->next;
		free(PointerStruct);
	}
}

void push(Pilemain **FirstPoint, int val) {
	Pilemain *NovoPonteiro;
	NovoPonteiro = (Pilemain*)malloc(sizeof(Pilemain));
	if(NovoPonteiro) {
    NovoPonteiro->value = val;
    if (*FirstPoint == NULL) {
      NovoPonteiro->next = NULL;
      *FirstPoint = NovoPonteiro;
    }
    else {
      NovoPonteiro->next = *FirstPoint;
      *FirstPoint = NovoPonteiro;
    }
	}
}

int retorna_int() {
  int ch;
  printf("\nInforme um numero: ");
  scanf("%d", &ch);
  return ch;
}

void printStack(Pilemain *InicioStack) {
	Pilemain *toEndStack;
	if(InicioStack == NULL) {
		printf("\nNao ha pilha para printar!");
	} 
	else {
		toEndStack = InicioStack;
		while(toEndStack != NULL) {
			printf("\n%d", toEndStack->value);
			toEndStack = toEndStack->next;
		}
	}
}

void corrigir(Pilemain **start, Pileaux *startaux) {
  Pilemain *startmain = *start; 
  if (startaux != NULL) { 
    if (startaux == startmain) {
      printf("\nNao ha nada para retornar");
    }
    else {
      while(startaux->next != startmain && startaux->next != NULL) {
        startaux = startaux->next;
      }
      push(start, startaux->value);
    }
  }
}

int main() {
  int op, ch;
  Pileaux *pileStartAux = NULL;
  Pilemain *pileStartMain = NULL;
  do {
    op = menuOption();
    switch (op) {
      case 1:
        ch = retorna_int();
        push(&pileStartMain, ch);
        push(&pileStartAux, ch);
      break;
      case 2:
        pop(&pileStartMain);
      break;
      case 3:
        printStack(pileStartMain);
      break;
      case 4:
        corrigir(&pileStartMain, pileStartAux);
      break;
      case 5:
        printf("\nFIM");
      break;
    }
  } while(op != 5);
  return 0;
}