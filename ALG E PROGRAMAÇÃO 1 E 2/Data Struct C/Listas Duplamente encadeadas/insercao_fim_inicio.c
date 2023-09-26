#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct list {
  int value;
  struct list *next;
  struct list *prev;
}list;

int menu() {
  int op;
  do {
    printf("\n\t1 - Inserir inicio");
    printf("\n\t2 - Inserir fim");
    printf("\n\t3 - printar lista");
    printf("\n\t4 - remover Inicio");
    printf("\n\t5 - remover fim");
    printf("\n\t6 - remover meio");
    printf("\n\t7 - adicionar meio");
    printf("\n\t8 - Kill terminal");
    printf("\n\tEscolha uma opcao acima: ");
    scanf("%d", &op);
  } while(op > 8 || op < 1);
  return op;
}

int returnInt() {
  int num;
  printf("\n\tInforme um valor: ");
  scanf("%d", &num);
  return num;
}

void addMid(list **beg, list *auxBeg, int valPrev, int valSearch, bool isBeg) {
  list *newValue;
  if (*beg != NULL && auxBeg != NULL) {
    if (auxBeg->value == valSearch) {
      if (isBeg) {
        push(beg, valPrev);
        addMid(beg, auxBeg->next, valPrev, valSearch, false);
      }
      else {
        newValue = (list*)malloc(sizeof(list));
        if (newValue != NULL) {
          newValue->value = valPrev;
          auxBeg->prev->next = newValue;
          newValue->next = auxBeg;
          newValue->prev = auxBeg->prev;
          auxBeg->prev = newValue;
          addMid(beg, auxBeg->next, valPrev, valSearch, false);
        }
      }
    }
    else {
      addMid(beg, auxBeg->next, valPrev, valSearch, false);
    }
  }
}

void removeMid(list **beg, list *auxBeg, int val, bool isBeg) {
  list *auxFree = auxBeg, *prev;
  if (*beg != NULL && auxBeg != NULL) {
    if (auxBeg->value == val) {
      if (isBeg) {
        auxBeg = auxBeg->next;
        *beg = auxBeg;
        if (auxBeg != NULL) {
          auxBeg->prev = NULL;
          free(auxFree);
          removeMid(beg, auxBeg, val, true);
        }
      }
      else {
        prev = auxBeg->prev;
        prev->next = auxBeg->next;
        if (auxBeg->next != NULL) {
          auxBeg->next->prev = prev;
        }
        auxBeg = auxBeg->next;
        free(auxFree);
        removeMid(beg, auxBeg, val, false);
      }
    }
    else {
      removeMid(beg, auxBeg->next, val, false);
    }
  }
}

void push(list **beg, int val) {
  list *newVal = (list*)malloc(sizeof(list)), *aux = *beg;
  if (newVal != NULL) {
    newVal->value = val;
    if (*beg == NULL) {
      *beg = newVal;
      newVal->next = NULL;
      newVal->prev = NULL;
    }
    else {
      newVal->next = *beg;
      *beg = newVal;
      newVal->prev = NULL;
      aux->prev = newVal;
    }
  }
}

void toEnd(list **beg, int val) {
  list *newVal = (list*)malloc(sizeof(list)), *aux = *beg;
  if (newVal != NULL) {
    newVal->value = val;
    if (aux == NULL) {
      *beg = newVal;
    }
    else {
      while(aux->next != NULL) {
        aux = aux->next;
      }
      aux->next = newVal; 
    }
    newVal->next = NULL;
    newVal->prev = aux;
  }
}

void printList(list *StartOfList) {
  list *start = StartOfList;
  printf("\n\n");
  if (start == NULL) {
    printf("\nNao ha nada na list");
  }
  else {
    printf("\nValor\t Endereco\tAnterior\tProximo\t");
    while(start != NULL) {
      printf("\n %d\t%p\t%p\t%p", start->value, start, start->prev, start->next);
      start = start->next;
    }
  }
  printf("\n\n");
}

void pop(list **beg) {
  list *aux = *beg;
  if (*beg == NULL) {
    printf("\nNao ha numeros na lista");
  }
  else {
    if (aux->next == NULL) {
      *beg = NULL;
    }
    else {
      *beg = aux->next;
      aux->next->prev = NULL;
    }
    free(aux);
  }
}

void removeEnd(list **beg) {
  list *freeEnd = *beg, *newEnd;
  if (*beg == NULL) {
    printf("\nNao ha nada para remover da lista");
  }
  else {
    while(freeEnd->next != NULL) {
      freeEnd = freeEnd->next;
    }
    newEnd = freeEnd->prev;
    newEnd->next = NULL;
    free(freeEnd);
  }
}

int main() {
  list *beggining = NULL;
  int option, val, search;
  do {
    option = menu();
    system("cls||clear");
    switch (option) {
    case 1: 
      val = returnInt();
      push(&beggining, val);
      break;
    case 2:
      val = returnInt();
      toEnd(&beggining, val);
      break;
    case 3:
      printList(beggining);
      break;
    case 4:
      pop(&beggining);
      break;
    case 5:
      removeEnd(&beggining);
      break;
    case 6:
      printf("\nPara remover no meio, informe");
      val = returnInt();
      removeMid(&beggining, beggining, val, true);
      break;
    case 7:
      printf("\n\tPara Inserir no meio, informe o valor que sera inserido\n");
      val = returnInt();
      printf("\n\tPara Inserir no meio, informe o valor que sera interpratdo com o K (valor do meio)\n");
      search = returnInt();
      addMid(&beggining, beggining, val, search, true);
      break;
    case 8:
      printf("\nPrograma finalizado");
      break;
    }
  } while(option != 8);
}