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
    printf("\n\t1 - Inserir inicio\n\t2 - Inserir fim");
    printf("\n\t3 - printar lista encadeada\n\t4 - remover Inicio");
    printf("\n\t5 - remover fim\n\t6 - remover meio");
    printf("\n\t7 - adicionar meio\n\t8 - printar lista circular\n\t9 - Ordenar\n\t10 - Finaliza");
    printf("\n\tEscolha uma opcao acima: ");
    scanf("%d", &op);
  } while(op > 10 || op < 1);
  return op;
}

int menuOpiton() {
  int op;
  do {
    printf("\n\t1 - Inserir Ordenado");
    printf("\n\t2 - printa Lista ordenada");
    printf("\n\t3 - Finalizar programa\n\tEScolha uma opcao acima: ");
    scanf("%d", &op);
  } while(op > 3 || op < 1);
  return op;
}

void encadeada(list **beg, list *aux) {
  if (*beg != NULL && aux != NULL) {
    if (aux->next == *beg) {
      aux->next->prev = NULL;
      aux->next = NULL;
    }
    else {
      encadeada(beg, aux->next);
    }
  }
}

void transformaCircular(list *start, list *end) {
  if (start != NULL) {
    if (end->next != NULL) {
      transformaCircular(start, end->next);
    }
    else {
      end->next = start;
      start->prev = end;
    }
  }
}

void swap(list *start, list *aux) {
  int Swap = start->value;
  start->value = aux->value;
  aux->value = Swap;
}

void sort(list *start) { 
  if (start != NULL) {
    list *current = start->next;
    while (current != NULL) {
      if (start->value > current->value) {
        swap(start, current);
        current = start;
      }
      current = current->next;
    }
    sort(start->next); 
  }
}

void printCircular(list *beg, list *auxPrint, bool first) {
  if (beg != NULL ) {
    if (auxPrint != beg || first) {
      printf("\nAtual: %p, Anterior: %p, Valor: %d, proximo: %p", auxPrint, auxPrint->prev, auxPrint->value, auxPrint->next);
      printCircular(beg, auxPrint->next, false);
    }
  }
  else {
    printf("\nNao ha nada na lista");
  }
}

void push(list **beg, int val) {
  list *newVal = (list*)malloc(sizeof(list)), *aux = *beg;
  if (newVal != NULL) {
    newVal->value = val;
    if (*beg == NULL) {
      *beg = newVal;
      newVal->next = NULL;
    }
    else {
      newVal->next = *beg;
      *beg = newVal;
      aux->prev = newVal;
    }
    
  }
}

int returnInt(char frase[]) {
  int num;
  printf("\n\t%s", frase);
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
    if (aux->next == NULL && aux != NULL) {
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

void sorted(list **beg, list *ptr, int val) {
  if (ptr == NULL) {
    toEnd(beg, val);
  }
  else if(ptr == *beg) {
    push(beg, val);
  }
  else {
    list *newNode = (list*)malloc(sizeof(list));
    if (newNode) {
      newNode->value = val;
      ptr->prev->next = newNode;
      newNode->prev = ptr->prev;
      ptr->prev = newNode;
      newNode->next = ptr;
    }
  }
}

void sortedInsert(list **beg, int valor) {
  list *aux = *beg, *ptr = NULL;
  bool find = false;
  while (aux != NULL) {
    if (valor < aux->value && !find) {
      ptr = aux;
      find = true;
    }
    aux = aux->next;
  }
  sorted(beg, ptr, valor);
}