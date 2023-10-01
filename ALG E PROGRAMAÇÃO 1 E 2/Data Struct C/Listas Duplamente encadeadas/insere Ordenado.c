#include <stdio.h>
#include <stdlib.h>
#include "funcoes.c"

int main() {
  int op, val;
  list *beggining = NULL;
  do {
    op = menuOpiton();
    switch (op) {
      case 1:
        val = returnInt("Informe um valor a ser inserido: ");
        sortedInsert(&beggining, val);
        break;
      case 2:
        printList(beggining);
        break;
      case 3:
        printf("\nFim do programa");
        break;
    }
  } while(op != 3);
  return 0;
}