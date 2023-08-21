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

int menuOption() {
  int menu;
  do {
    printf("\n0 - Inserir na lista\n1 - buscar valor na lista\n2 - fim\n");
    printf("\nEscolha uma opcao acima: ");
    scanf("%d", &menu);
  } while(menu > 2 || menu < 0);
  return menu;
}

void busca_valor_lista(Node *inicio_lista) {
  Node *busca_ponteiro = inicio_lista;
  int valor_busca;
  bool encontrou = false;
  if (busca_ponteiro == NULL) {
    printf("\nNao ha valores para buscar, pois a lista esta vazia!");
  }
  else {
    valor_busca = retorna_valor();
    while(busca_ponteiro != NULL) {
      if (valor_busca == busca_ponteiro->val) {
        encontrou = true;
        printf("\nNumero encontrado. Endereco: %p, valor: %d, Endereco proximo: %p", busca_ponteiro, busca_ponteiro->val, busca_ponteiro->nxt);
      }
      busca_ponteiro = busca_ponteiro->nxt;
    }
    if (!encontrou) {
      printf("\n\nNumero nao encotrado na lista!");
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
    break;
    case 1:
      busca_valor_lista(inicio);
    break;
    case 2:
      printf("\nFim da busca");
    break;
    }
  } while(op != 2);
  return 0;
}
