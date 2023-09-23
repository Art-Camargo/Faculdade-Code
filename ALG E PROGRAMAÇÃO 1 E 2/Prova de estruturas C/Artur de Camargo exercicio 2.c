//Artur de Camargo
#include <stdio.h>
#include <stdlib.h>

typedef struct show {
  int pessoa;
  struct show *next;
}show;

int menu() {
  int opcao;
  do {
    printf("\n\t1 - tentar entrar na fila do portao informada");
    printf("\n\t2 - printar as filas dos portoes\n\t3 - autorizar a entrada da primeira pessoa de algum portao");
    printf("\n\t4 - fechar os portoes e encaminhar todos para dentro ");
    printf("\n\n\tInforme uma opcao acima: ");
    scanf("%d", &opcao);
  } while(opcao < 1 || opcao > 4);
  return opcao;
}

void printafila(show *StartOfList) {
  show *start = StartOfList;
  if (start == NULL) {
    printf("\nNao ha ninguem nessa fila!");
  }
  else {
    while(start != NULL) {
      printf("\nsenha: %d, end: %p, endprox: %p", start->pessoa, start, start->next);
      start = start->next;
    }
  }
  printf("\n\n-------------------------"); //usado para estilizar a tela
}

void empilha_fim(show **Toposhow, int pessoa) {
	show *ponteiro = (show*)malloc(sizeof(show)), *ponteiroFinal = *Toposhow;
	if(ponteiro != NULL) {
		ponteiro->pessoa = pessoa;
		if(*Toposhow == NULL) {
			*Toposhow = ponteiro;
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

int qtd_pessoas_fila(show *fila) {
  int qtd = 0;
  while(fila != NULL) {
    qtd++;
    fila = fila->next;
  }
  return qtd;
}

void entra_fila(show **fila, show **fila2, show **fila3, int num_fila, int senha) {
  int qtd1, qtd2, qtd3, flag = 0;
  qtd1 = qtd_pessoas_fila(*fila); 
  qtd2 = qtd_pessoas_fila(*fila2);
  qtd3 = qtd_pessoas_fila(*fila3);
  //
  switch (num_fila) {
    case 1:
      if (qtd1 - qtd2 >= 3) {
        empilha_fim(fila2, senha);
        flag = 1;
      }
      else if (qtd1 - qtd3 >= 3) {
        flag = 1;
        empilha_fim(fila3, senha);
      }
      else {
        empilha_fim(fila, senha);
      }
      break;
    case 2:
      if (qtd2 - qtd1 >= 3) {
        flag = 1;
        empilha_fim(fila, senha);
      }
      else if (qtd2 - qtd3 >= 3) {
        flag = 1;
        empilha_fim(fila3, senha);
      }
      else {
        empilha_fim(fila2, senha);
      }
      break;
    case 3:
      if (qtd3 - qtd1 >= 3) {
        flag = 1;
        empilha_fim(fila, senha);
      }
      else if (qtd3 - qtd2 >= 3) {
        flag = 1;
        empilha_fim(fila2, senha);
      }
      else {
        empilha_fim(fila3, senha);
      }
      break;
  }
  if (flag) {
    printf("\nA fila %d estava cheia e voce foi encaminhado para outra fila!", num_fila);
  }
}


int retorna_fila_autorizada() {
  int fila;
  do {
    printf("\nInforme a fila: ");
    scanf("%d", &fila);
  } while(fila > 3 || fila < 1);
  return fila;
}

void entrar_show(show **FirstPointer) {
	show *PointerStruct = *FirstPointer;
	if(*FirstPointer == NULL) { 
		printf("\nNao ha nenhuma pessoa na fila para entrar no show");
	} 
	else { 
		*FirstPointer = PointerStruct->next;
		free(PointerStruct);
	}
}

int main() {
  show *fila1 = NULL, *fila2 = NULL, *fila3 = NULL;
  int senhaGeral = 0, opcao, fila;
  do { 
    opcao = menu();
    system("clear||cls");
    switch (opcao) {
      case 1:
        fila = retorna_fila_autorizada();
        entra_fila(&fila1, &fila2, &fila3, fila, senhaGeral);
        senhaGeral++;
        break;
      case 2:
        printf("\nPrimeira fila abaixo");
        printafila(fila1);
        printf("\nSegunda fila abaixo");
        printafila(fila2);
        printf("\nTerceira fila abaixo");
        printafila(fila3);
        break;
      case 3:
        fila = retorna_fila_autorizada();
        switch (fila) {
          case 1:
            entrar_show(&fila1);
            break;
          case 2:
            entrar_show(&fila2);
            break;
          case 3:
            entrar_show(&fila3);
            break;
        }
        break;
      case 4:
        printf("\nAs pessoas que estavam na fila entraram e os portoes foram fechados para o show da Ariana Grande\n");
        break;
    }
  } while(opcao != 4);
  return 0;
}