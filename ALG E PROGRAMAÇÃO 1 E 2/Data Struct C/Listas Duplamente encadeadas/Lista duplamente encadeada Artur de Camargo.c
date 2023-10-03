#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funcoes.c"

int main() {
  list *beggining = NULL;
  int option, val, searchVal;
  do {
    option = menu();
    system("cls||clear");
    switch (option) {
    case 1: 
      val = returnInt("Informe um valor para ser inserido no comeco: ");
      push(&beggining, val);
      break;
    case 2:
      val = returnInt("Informe um valor para ser inserido no fim: ");
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
      val = returnInt("Para remover no meio, informe um valor a ser removido: ");
      removeMid(&beggining, beggining, val, true);
      break;
    case 7:
      val = returnInt("Para Inserir no meio, informe o valor que sera inserido: ");
      searchVal = returnInt("Para Inserir no meio, informe o valor que sera interpratdo com o K (valor do meio): ");
      addMid(&beggining, beggining, val, searchVal, true);
      break;
    case 8:
      transformaCircular(beggining, beggining);
      printCircular(beggining, beggining, true);
      encadeada(&beggining, beggining);
      break;
    case 9:
      sort(beggining);
      break;
    case 10:
      val = returnInt("Digite um valor a ser buscado");
      search(beggining, val, false);
      break;
    case 11:
      printf("\nPrograma finalizado\n");
      break;
    }
  } while(option != 11);
}