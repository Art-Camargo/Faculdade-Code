//Faça um código que, após obter 10 valores em uma lista, ordena os valores. Não usar vetor, e sim listas encadeadas.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define TAM 10

typedef struct no {
  int value;
  struct no* next;
}No;

void addList(No **inicio, int val) {
  No *novo_ponteiro = (No*)malloc(sizeof(No));
  if (*inicio == NULL) {
    novo_ponteiro->next = NULL; // 1 NULL
    novo_ponteiro->value = val;
    *inicio = novo_ponteiro; //NULL, 50F
  }
  else {
    novo_ponteiro->next = *inicio;
    novo_ponteiro->value = val;
    *inicio = novo_ponteiro;
  }
}

int retornaValor() {
  int valor;
  printf("\nInforme um valor para adicionar na lista: ");
  scanf("%d", &valor);
  return valor;
}

void bubbleSortList(No *inicio_lista) {
  No *ponteiro_atual = inicio_lista, *proximo_ponteiro = inicio_lista->next;
  int valor_troca;
  while(ponteiro_atual->next != NULL) {
    if (ponteiro_atual->value > proximo_ponteiro->value) {
      valor_troca = ponteiro_atual->value;
      ponteiro_atual->value = proximo_ponteiro->value;
      proximo_ponteiro->value = valor_troca;
      proximo_ponteiro = inicio_lista->next;
      ponteiro_atual = inicio_lista;
    }
    else {
      ponteiro_atual = proximo_ponteiro;
      proximo_ponteiro = proximo_ponteiro->next;
    }
  }
}

void printa_lista_ordenada(No *comeco_lista_ordenada) {
  No *aux_free = comeco_lista_ordenada;
  while(comeco_lista_ordenada != NULL) {
    printf("%d  ", comeco_lista_ordenada->value);
    comeco_lista_ordenada = comeco_lista_ordenada->next;
    free(aux_free);
    aux_free = comeco_lista_ordenada;
  }
}

int main() {
  int numero, i;
  No *ini = NULL;
  for(i = 0; i < TAM; i++) {
    system("cls||clear");
    numero = retornaValor();
    addList(&ini, numero);
  }
  bubbleSortList(ini);
  printa_lista_ordenada(ini);
  return 0;
}
// 0  1   2  3 ...
// 10 11 12  13 ...

// 0   1    2    3
// 10  212  20F  1000000F