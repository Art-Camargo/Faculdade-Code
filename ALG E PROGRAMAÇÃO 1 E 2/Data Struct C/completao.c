//Artur de Camargo


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
typedef struct node { //Struct padrão para manipular a lista
  int value;
  struct node* next;
}TypeNode;

int returnIntValue() { //para inserir valores, a função retorna o valor a ser inserido
  int num;
  printf("\nEnter a int number: ");
  scanf("%d", &num);
  return num;
}

//Adiciona um número no começo da lista
void addListBeginning(TypeNode **startList, int val) { 
  TypeNode *node_var = (TypeNode*)malloc(sizeof(TypeNode));
  if (node_var != NULL) {
    if (*startList == NULL) {
      node_var->next = NULL;
      *startList = node_var;
    }
    else {
      node_var->next = *startList;
      *startList = node_var;
    }
    node_var->value = val;
  }
}

//Printa os valores da lista (caso esteja circular, printa circular)
void printList(TypeNode *InicioStack) {
	TypeNode *toEndStack, *aux;
  bool valido = true;
  system("clear");
	if(InicioStack == NULL) {
		printf("\nNao ha pilha para printar!");
	} 
	else {
    toEndStack = InicioStack;
    aux = InicioStack;
		while(toEndStack != NULL && valido) {
      if (toEndStack->next == aux) {
        valido = false;
      }
			printf("\nvalor: %d, current: %p, next: %p", toEndStack->value, toEndStack, toEndStack->next);
      toEndStack = toEndStack->next;
		}
	}
}


//Função que adiciona um elemento antes do K (todas as ocorrências) no meio
void addMidList(TypeNode **beg, int val, int mid) {
  TypeNode *aux = *beg, *beforePointer = NULL, *newNode; 
  bool inserted = false, thereIs = false; 
  if (*beg == NULL) {
    printf("\nNao ha nada na lista");
    thereIs = true;
  }
  else {
    while (aux != NULL) {
      if (aux->value == val) {
        newNode = (TypeNode*)malloc(sizeof(TypeNode));
        if (newNode != NULL) {
          newNode->value = mid;
          if (beforePointer == NULL) {
            newNode->next = *beg;
            *beg = newNode;
          } 
          else {
            newNode->next = aux;
            beforePointer->next = newNode;
          }
          inserted = true;
        }
      }
      beforePointer = aux;
      aux = aux->next;
    }
  }
  if (!inserted && !thereIs) {
    printf("\nNumero nao encontrado na lista");
  }
}

//Remove do começo
void pop(TypeNode **FirstPointer) {
	TypeNode *PointerStruct = *FirstPointer;
	if(*FirstPointer == NULL) { 
		printf("\nNao e possivel dar pop na pilha!!");
	} 
	else { 
		*FirstPointer = PointerStruct->next;
		free(PointerStruct);
	}
}

//remove do fim
void desempilha(TypeNode **InicioAtual) {
	TypeNode *ponteiroFree = *InicioAtual, *ponteiroAnt;
	if(ponteiroFree == NULL) {
		printf("\nNao e possivel dar pop pelo fim");
	}
	else {
		if(ponteiroFree->next == NULL) {
			free(ponteiroFree);
			*InicioAtual = NULL;
		}
		else {
			while(ponteiroFree->next != NULL) {
				ponteiroAnt = ponteiroFree;
				ponteiroFree = ponteiroFree->next;
			}
			free(ponteiroFree);
			ponteiroAnt->next = NULL;
		}
	}
}

//Retorna o Menu
int menuOption() {
  int opcao;
  do {
    printf("\n1 - Insere inicio\n2 - insere Meio\n3 - printa LIsta\n4 - Buscar item na lista");
    printf("\n5 - Remover um numero do meio\n6 - Insere fim\n7 - Remove fim\n8 - Remove Inicio");
    printf("\n9 - Transforma em circular\n10 - transforma em encadeada (CASO ESTEJA EM CIRCULAR)\n11 - ordena lista\n12 - Fim");
    printf("\nEscolha uma opcao acima: ");
    scanf("%d", &opcao);
  } while(opcao < 1 || opcao > 12);
  return opcao;
}

//Adiciona no fim
void empilha_fim(TypeNode **TopoLista, int valor) {
	TypeNode *ponteiro = (TypeNode*)malloc(sizeof(TypeNode)), *ponteiroFinal = *TopoLista;
  bool valido = true;
	if(ponteiro != NULL) {
		ponteiro->value = valor;
		if(*TopoLista == NULL) {
			*TopoLista = ponteiro;
		} 
		else {
			while(ponteiroFinal->next != NULL && valido) {
        if (ponteiroFinal->next == *TopoLista) {
          valido = false;
        }
				else {
          ponteiroFinal = ponteiroFinal->next;
        }
			}
			ponteiroFinal->next = ponteiro;
		}
		if (!valido) {
      ponteiro->next = *TopoLista;
    }
    else {
      ponteiro->next = NULL;
    }
	}
}

//procura um valor na lista
bool searchNumList(TypeNode *beg, int value) {
  TypeNode *aux = beg;
  bool achou = false;
  if (beg != NULL) {
    while(aux != NULL) {
      if (value == aux->value) {
        printf("\nNumero %d, atual: %p, prox: %p", aux->value, aux, aux->next);
        achou = true;
      }
      aux = aux->next;
    }
  }
  return achou;
}

//Ordena a lista com bubble sort
void bubbleSortList(TypeNode *inicio_lista) {
  TypeNode *ponteiro_atual, *proximo_ponteiro;
  int valor_troca, troca_realizada;
  if (inicio_lista != NULL) {
    do {
      troca_realizada = 0;
      ponteiro_atual = inicio_lista;
      proximo_ponteiro = inicio_lista->next;
      while (proximo_ponteiro != NULL) {
        if (ponteiro_atual->value > proximo_ponteiro->value) {
          valor_troca = ponteiro_atual->value;
          ponteiro_atual->value = proximo_ponteiro->value;
          proximo_ponteiro->value = valor_troca;
          troca_realizada = 1;
        }
        ponteiro_atual = ponteiro_atual->next;
        proximo_ponteiro = proximo_ponteiro->next;
      }
    } while (troca_realizada);
  }
}

//remove um valor do meio da lista
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

//Transforma a lista em circular
void circular(TypeNode *comeco_circulo, TypeNode *aux) {
  if (comeco_circulo == NULL ) {
    printf("\nNAO TEM COMO TRANSFORMAR EM CIRCULAR");
  }
  else {
    if (aux->next == comeco_circulo || aux->next == NULL) {
      aux->next = comeco_circulo;
    }
    else {
      circular(comeco_circulo, aux->next);
    }
  }
}

//Transforma em encadeada (caso esteja em circular)
void encadeado(TypeNode *comeco_encadeada, TypeNode *auxPi) {
  if (auxPi == NULL || comeco_encadeada == NULL) {
    printf("\nNao ha numeros na lista");
  }
  else {
    if (auxPi->next == comeco_encadeada || auxPi->next == NULL) {
      auxPi->next = NULL;
    } 
    else {
      encadeado(comeco_encadeada, auxPi->next);
    }
  }
}

int main() {
  int op, val, meio;
  TypeNode *beginningOfList = NULL;
  do {
    op = menuOption();
    system("clear||cls");
    switch (op) {
      case 1:
        encadeado(beginningOfList, beginningOfList);
        val = returnIntValue();
        addListBeginning(&beginningOfList, val);
      break;
      case 2:
        encadeado(beginningOfList, beginningOfList);
        printf("\nPara buscar na lista, digite o K: ");
        val = returnIntValue();
        printf("\nPara adicionar no meio, digite um numero: ");
        meio = returnIntValue();
        addMidList(&beginningOfList, val, meio);
      break;
      case 3:
        printList(beginningOfList);
      break;
      case 4:
        encadeado(beginningOfList, beginningOfList);
        val = returnIntValue();
        if (searchNumList(beginningOfList, val)) {
          printf("\nAcima, numeros encontrados. ");
        }
        else {
          printf("\nNumero nao encontrado na lista");
        }
      break;
      case 5:
        encadeado(beginningOfList, beginningOfList);
        printf("\nDigite um valor para ser removido da lista abaixo");
        val = returnIntValue();
        removeFromList(&beginningOfList, val, beginningOfList, NULL);
      break;
      case 6:
        val = returnIntValue();
        empilha_fim(&beginningOfList, val);
      break;
      case 7:
        encadeado(beginningOfList, beginningOfList);
        desempilha(&beginningOfList);
      break;
      case 8:
        pop(&beginningOfList);
      break;
      case 9:
        circular(beginningOfList, beginningOfList);
        printf("\nAbaixo, lista circular");
        printList(beginningOfList);
      break;
      case 10:
        encadeado(beginningOfList, beginningOfList);
      break;
      case 11:
        encadeado(beginningOfList, beginningOfList);
        bubbleSortList(beginningOfList);
      break;
      case 12:
        printf("\nFim do programa!");
      break;
    }
  } while(op != 12);
  return 0;
}