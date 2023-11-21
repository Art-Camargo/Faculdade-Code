#include <stdio.h>
#include <stdlib.h>
#include "graphTypes.h"

int getMaxGrafo() {
  int max;
  do {
    printf("\nInforme o numero maximo de grafos: ");
    scanf("%d", &max);
  } while( max <= 0);
  return max;
}

int getOptionMenu() {
  int option;
  do {
    printf("\n\t1 - Adicionar um grafo\n\t2 - FIM\n\tEscolha uma opcao acima: ");
    scanf("%d", &option);
  } while( option < 1 || option > 2);
  return option;
}

int getNumVertice(int maxSize) {
  int num;
  do {
    printf("\n\tInforme a quantidade de vertices: ");
    scanf("%d", &num);
  } while( num > maxSize || num < 0);
  return num;
}

void newGrafo(grafo *collection, int maxSize){
  static int idx;
  int verticesMax;
  if (idx < maxSize) {
    verticesMax = getNumVertice(maxSize);
    collection[idx].numVertice = verticesMax;
    collection[idx].listaAdj = (listaAdjacencia*)malloc(verticesMax * sizeof(listaAdjacencia*));
    idx++;
  }
}

int main() {
  int const maxGrafo = getMaxGrafo();
  int op;
  grafo *collection;
  collection = (grafo*)malloc(maxGrafo * sizeof(grafo));  

  do {
    op = getOptionMenu();
    system("cls||clear");
    switch (op) {
      case 1:
        newGrafo(collection, maxGrafo);
        break;
      default:
        printf("\nFim");
        break;
    }
  } while(op != 2);
  return 0;
}