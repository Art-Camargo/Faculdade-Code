#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node {
  struct node *nxt;
  int val;
}Node;

int retorna_valor() {
  int value;
  printf("\nInforme um valor: ");
  scanf("%d", &value);
  return value;
}

void insere_fim(Node **ini) {
  int valor;
  Node *ponteiro = (Node*)malloc(sizeof(Node)), *aux = *ini;
  if(ponteiro != NULL) {
    valor = retorna_valor();
    ponteiro->val = valor;
    if(*ini == NULL) {
      ponteiro->nxt = NULL;
      *ini = ponteiro;
    }
    else {
      while(aux->nxt != NULL) {
        aux = aux->nxt;
      }
      aux->nxt = ponteiro;
      ponteiro->nxt = NULL;
    }
  }
  else {
    printf("\nErro ao alocar memoria!");
  }
}

void ordena_lista(Node *beg) {
  Node *aux_beg = beg, *proxPonteiro;
  int auxiliador;
  if (aux_beg->nxt != NULL) {
    while(aux_beg != NULL) {
      proxPonteiro = aux_beg->nxt;
      while(proxPonteiro != NULL) {
        if(aux_beg->val > proxPonteiro->val) {
          auxiliador = proxPonteiro->val;
          proxPonteiro->val = aux_beg->val;
          aux_beg->val = auxiliador;
          proxPonteiro = aux_beg;
        }
        proxPonteiro = proxPonteiro->nxt;
      }
      aux_beg = aux_beg->nxt;
    }
  }
}

int menuOption() {
  int menu;
  do {
    printf("\n0 - Inserir na lista\n1 - imprimir a lista e os seus enderecos\n2 - fim\n");
    printf("\nEscolha uma opcao acima: ");
    scanf("%d", &menu);
  } while(menu > 2 || menu < 0);
  return menu;
}

void printa_lista(Node *inicio_list) {
  Node *aux_print = inicio_list;
  if(aux_print == NULL) {
    printf("\nA sua lista esta vazia");
  }
  else {
    while(aux_print != NULL) {
      printf("\nendereco: %p, valor: %d, proximo endereco: %p", aux_print, aux_print->val, aux_print->nxt);
      aux_print = aux_print->nxt;
    }
  }
}

int main() {
  Node *inicio = NULL;
  int op;
  do {
    op = menuOption();
    system("cls||clear");
    switch (op){
    case 0:
      insere_fim(&inicio);
      ordena_lista(inicio);
    break;
    case 1:
      printa_lista(inicio);
    break;
    case 2:
      printf("\nFim da busca");
    break;
    }
  } while(op != 2);
  return 0;
}
