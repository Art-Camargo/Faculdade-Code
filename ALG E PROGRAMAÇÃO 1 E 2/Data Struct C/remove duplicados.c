#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

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

void addListBeginning(TypeNode **startList) {
  int val;
  TypeNode *node_var = (TypeNode*)malloc(sizeof(TypeNode));
  if (node_var != NULL) {
    val = returnIntValue();
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

void removeDuplicatesFromList(TypeNode *initialPoint) {
    TypeNode *inicio = initialPoint, *proximo, *anterior, *aux;
    if (initialPoint == NULL) {
        printf("\nThere is no list");
    }
    else {
        while (inicio != NULL) {
            anterior = inicio;
            proximo = inicio->next;
            while (proximo != NULL) {
                if (inicio->value == proximo->value) {
                    aux = proximo;
                    anterior->next = proximo->next;
                    proximo = anterior->next;
                    free(aux);
                }
                else {
                    anterior = anterior->next;
                    proximo = proximo->next;
                }
            }
            inicio = inicio->next;
        }
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
      printf(" %d ", start->value);
      start = start->next;
    }
  }
}

int main() {
  int index;
  TypeNode *beginningOfList = NULL;
  for(index = 0; index < SIZE; index++) {
    addListBeginning(&beginningOfList);
  }
  removeDuplicatesFromList(beginningOfList);
  printList(beginningOfList);
  return 0;
}