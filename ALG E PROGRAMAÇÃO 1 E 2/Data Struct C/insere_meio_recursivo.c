#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node {
  int value;
  struct node* next;
}TypeNode;

int returnIntValue() {
  int num;
  printf("\nEnter a int number: ");
  scanf("%d", &num);
  return num;
}

void addListBeginning(TypeNode **startList, int val) {
  TypeNode *node_var = (TypeNode*)malloc(sizeof(TypeNode));
  if (node_var != NULL) {
    if (*startList == NULL) {
      node_var->next = NULL;
      *startList = node_var;
    }
    else {
      node_var->next = *startList;
      *startList = node_var;
    }
    node_var->value = val;
  }
}

void printList(TypeNode *StartOfList) {
  TypeNode *start = StartOfList;
  printf("\n\n");
  if (start == NULL) {
    printf("\nThere is no list");
  }
  else {
    while(start != NULL) {
      printf("\nval: %d, end: %p, endprox: %p", start->value, start, start->next);
      start = start->next;
    }
  }
}

void addMidList(TypeNode **beg, int val, int mid) {
  TypeNode *aux = *beg, *beforePointer = NULL, *newNode; 
  bool inserted = false, thereIs = false; 
  if (*beg == NULL) {
    printf("\nNao ha nada na lista");
    thereIs = true;
  }
  else {
    while (aux != NULL) {
      if (aux->value == val) {
        newNode = (TypeNode*)malloc(sizeof(TypeNode));
        if (newNode != NULL) {
          newNode->value = mid;
          if (beforePointer == NULL) {
            newNode->next = *beg;
            *beg = newNode;
          } 
          else {
            newNode->next = aux;
            beforePointer->next = newNode;
          }
          inserted = true;
        }
      }
      beforePointer = aux;
      aux = aux->next;
    }
  }
  if (!inserted && !thereIs) {
    printf("\nNumero nao encontrado na lista");
  }
}

int menuOption() {
  int opcao;
  do {
    printf("\n1 - Insere inicio\n2 - insere Meio\n3 - printa LIsta\n4 - Buscar item na lista");
    printf("\n5 - Remover um numero do meio\n6 - FIM\nInsira uma opcao desejada: ");
    scanf("%d", &opcao);
  } while(opcao < 1 || opcao > 6);
  return opcao;
}

bool searchNumList(TypeNode *beg, int value) {
  TypeNode *aux = beg;
  bool achou = false;
  if (beg != NULL) {
    while(aux != NULL) {
      if (value == aux->value) {
        printf("\nNumero %d, current: %p, next: %p", aux->value, aux, aux->next);
        achou = true;
      }
      aux = aux->next;
    }
  }
  return achou;
} 

void removeFromList(TypeNode **begList, int value, TypeNode *current, TypeNode *prev) {
  TypeNode *freeP;
  if (current != NULL) {
    if (current->value == value) {
      if (prev == NULL) {
        *begList = current->next;
        freeP = current;
        current = current->next;
        free(freeP);
        removeFromList(begList, value, current, NULL);
      }
      else {
        prev->next = current->next;
        freeP = current;
        current = current->next;
        free(freeP);
        removeFromList(begList, value, current, prev);
      }
    }
    else {
      removeFromList(begList, value, current->next, current);
    }
  }
}

int main() {
  int op, val, meio;
  TypeNode *beginningOfList = NULL;
  do {
    op = menuOption();
    system("clear");
    switch (op) {
      case 1:
        val = returnIntValue();
        addListBeginning(&beginningOfList, val);
      break;
      case 2:
        printf("\nPara buscar na lista, digite o K: ");
        val = returnIntValue();
        printf("\nPara adicionar no meio, digite um numero: ");
        meio = returnIntValue();
        addMidList(&beginningOfList, val, meio);
      break;
      case 3:
        printList(beginningOfList);
      break;
      case 4:
        val = returnIntValue();
        if (searchNumList(beginningOfList, val)) {
          printf("\nAcima, numeros encontrados. ");
        }
        else {
          printf("\nNumero nao encontrado na lista");
        }
      break;
      case 5:
        printf("\nDigite um valor para ser removido da lista abaixo");
        val = returnIntValue();
        removeFromList(&beginningOfList, val, beginningOfList, NULL);
      break;
      case 6:
        printf("\nPrograma finalizado");
      break;
    }
  } while(op != 6);
  return 0;
}