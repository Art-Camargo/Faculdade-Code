#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pilha {
  struct pilha *next;
  int val;
} pilha;

int returnIntValue() {
  int num;
  printf("\nInforme um numero: ");
  scanf("%d", &num);
  return num;
}

void empilha_fim(pilha **Topopilha, int val) {
	pilha *ponteiro = (pilha*)malloc(sizeof(pilha)), *ponteiroFinal = *Topopilha;
	if(ponteiro != NULL) {
		ponteiro->val = val;
		if(*Topopilha == NULL) {
			*Topopilha = ponteiro;
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

void push(pilha **startList, int val) {
  pilha *node_var = (pilha*)malloc(sizeof(pilha));
  if (node_var != NULL) {
    node_var->val = val;
    if (*startList == NULL) {
      node_var->next = NULL;
      *startList = node_var;
    }
    else {
      node_var->next = *startList;
      *startList = node_var;
    }
  }
}

int menuOption() {
  int opcao;
  do {
    printf("\n1 - insere na primeira pilha\n2 - insere na segunda pilha\n3 - printa pilha 1\n4 - printar pilha 2");
    printf("\n5 - criar lista a partir das pilhas\n6 - FIM\nEscolha uma opcao acima: ");
    scanf("%d", &opcao);
  } while(opcao < 1 || opcao > 6);
  return opcao;
}

void printList(pilha *StartOfList) {
  pilha *start = StartOfList;
  printf("\n\n");
  if (start == NULL) {
    printf("\nNao ha nada na pilha");
  }
  else {
    while(start != NULL) {
      printf("\nval: %d, end: %p, endprox: %p", start->val, start, start->next);
      start = start->next;
    }
  }
  printf("\n\n");
}

void transformarEmLista(pilha **lista, pilha *pilhaAux1, pilha *pilhaAux2) {
  bool flag = true;
  if (pilhaAux1 == NULL && pilhaAux2 == NULL) {
    printf("\nNao ha como criar, as pilhas estao vazias!");
  }
  else {
    printf("\nAbaixo, lista criada a partir das pilhas: ");
    while(pilhaAux2 != NULL || pilhaAux1 != NULL) {
      if (flag) {
        if (pilhaAux1 != NULL) {
          empilha_fim(lista, pilhaAux1->val);
          pilhaAux1 = pilhaAux1->next;
        }
      }
      else {
        if (pilhaAux2 != NULL) {
          empilha_fim(lista, pilhaAux2->val);
          pilhaAux2 = pilhaAux2->next;
        }
      }
      flag = !flag;
    }
  }
}

void FreeMemory(pilha **IndexPoint) {
	pilha *StructP = *IndexPoint, *prox;
	while(StructP != NULL) {
		prox = StructP->next;
		free(StructP);
		StructP = prox;
	}
}

int qtd_pilha(pilha *pilhaqtd) {
  int qtd = 0;
  while(pilhaqtd != NULL) {
    qtd++;
    pilhaqtd = pilhaqtd->next;
  }
  return qtd;
}

int main() {
  pilha *pilha1 = NULL, *pilha2 = NULL, *lista = NULL;
  int opcao, val;
  do {
    opcao = menuOption();
    system("cls||clear");
    switch (opcao) {
      case 1:
        val = returnIntValue();
        push(&pilha1, val);
        break;
      case 2:
        val = returnIntValue();
        push(&pilha2, val);
        break;
      case 3:
        printf("\nPrintando a primeira pilha abaixo\n");
        printList(pilha1);
        break;
      case 4:
        printf("\nPrintando a segunda pilha abaixo\n");
        printList(pilha2);
        break;
      case 5:
        printf("\nQuantidade de desmpilhado da pilha 1 = %d", qtd_pilha(pilha1));
        printf("\nQuantidade de desmpilhado da pilha 2 = %d", qtd_pilha(pilha2));
        transformarEmLista(&lista, pilha1, pilha2);
        printList(lista);
        FreeMemory(&lista);
        lista = NULL;
        break;
      case 6:
        printf("\nPrograma finalizado com sucesso");
    }
  } while(opcao != 6);
  return 0;
}