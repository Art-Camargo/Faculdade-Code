#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
typedef struct node {
  int value;
  struct node* next;
}TypeNode;

void push(TypeNode **FirstPoint, int valor) {
	TypeNode *NovoPonteiro;
	NovoPonteiro = (TypeNode*)malloc(sizeof(TypeNode));
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

void removeFromListPart2(TypeNode **begList, int valor) {
  TypeNode *ptr = *begList, *before = NULL, *auxFree;
  while (ptr != NULL) {
    if (ptr->value == valor) {
      if (before == NULL) {    //       b   x p
        *begList = ptr->next; //  2 3 4 5  NULL
        auxFree = ptr;
        ptr = ptr->next;
        free(auxFree);
      } 
      else {
        before->next = ptr->next;
        auxFree = ptr;
        ptr = ptr->next;
        free(auxFree);
      }
    } 
    else {
      before = ptr;
      ptr = ptr->next;
    }
  }
}


int main() {
  TypeNode *ini = NULL;
  time_t inicio, fim;
  
  for(long long i = 0; i < 1000000; i++) {
    push(&ini, 0);
  }

  inicio = time(NULL);
  removeFromList(&ini, 0, ini, NULL);
  fim = time(NULL);
  system("cls||clear");
  printf("\n\nRECURSIVAMENTE DEMOROU %.2lf segundos", (double)(fim - inicio)*1000);
  return 0;
}