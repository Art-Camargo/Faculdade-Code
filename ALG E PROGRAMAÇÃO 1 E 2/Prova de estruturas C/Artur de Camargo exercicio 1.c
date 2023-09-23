#include <stdio.h>
#include <stdlib.h>

typedef struct lista {
  struct lista *next;
  int val;
}lista;

int menu() {
  int opcao;
  do {
    printf("\n\t1 - inserir na pilha\n\t2 - somar um numero em todos os numeros da lista e adicionar ele no fim");
    printf("\n\t3 - printar a lista\n\t4 - terminar o programa");
    printf("\n\n\tInforme uma opcao acima: ");
    scanf("%d", &opcao);
  } while(opcao < 1 || opcao > 4);
  return opcao;
}

void printaLista(lista *StartOfList) {
  lista *start = StartOfList;
  printf("\n\n");
  if (start == NULL) {
    printf("\nNao ha lista craida ainda :)");
  }
  else {
    while(start != NULL) {
      printf("\nval: %d, end: %p, endprox: %p", start->val, start, start->next);
      start = start->next;
    }
  }
  printf("\n\n");
}

void empilha_fim(lista **TopoLista, int valor) {
	lista *ponteiro = (lista*)malloc(sizeof(lista)), *ponteiroFinal = *TopoLista;
	if(ponteiro != NULL) {
		ponteiro->val = valor;
		if(*TopoLista == NULL) {
			*TopoLista = ponteiro;
		}
		else {
			while(ponteiroFinal->next != NULL) {
				ponteiroFinal = ponteiroFinal->next;
			}
			ponteiroFinal->next = ponteiro;
		}
		ponteiro->next = NULL;
	}
}

int retornaValor() {
  int num;
  printf("\nDigite um numero: ");
  scanf("%d", &num);
  return num;
}

void soma_valores_lista(lista **listaOriginal, int valor_somado) {
  lista *aux = *listaOriginal;
  if (*listaOriginal == NULL) {
    printf("\nO numero apenas sera inserido na lista, pois nao ha outro numero na lista ;)");
  }
  else {
    while(aux != NULL) {
      aux->val += valor_somado;
      aux = aux->next;
    }
  }
  empilha_fim(listaOriginal, valor_somado);
}

int main() {
  int opcao, val;
  lista *listaOficial = NULL;
  do {
    opcao = menu();
    system("cls||clear");
    switch (opcao) {
      case 1:
        val = retornaValor();
        empilha_fim(&listaOficial, val);
        break;
      case 2:
        printf("\nEsse valor somara em todos os itens da lista");
        val = retornaValor();
        soma_valores_lista(&listaOficial, val);
        break;
      case 3:
        printaLista(listaOficial);
        break;
      case 4:
        printf("\nPrograma finalizado com sucesso!");
        break;
    }
  } while(opcao != 4);
  return 0;
}