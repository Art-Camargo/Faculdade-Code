#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//vertices são os nós
//As arestas, entretanto, são as conexões entre os vertices a partir de uma lógica em um set
//struct para vertices, struct para arestas

typedef struct node {
  int vertex;
  struct node *next;
} node;

typedef struct graphType {
  int numVertex;
  node **linkedList;
}graphType;

int getGenericValue(char mssg[]) {
  int num;
  do {
    printf("\n\t%s", mssg);
    scanf("%d", &num);
  } while(num < 0);
  return num;
}

node *createNode(int vertex) {
  node *newNode = (node*)malloc(sizeof(node));
  if (newNode) {
    newNode->vertex = vertex;
    newNode->next = NULL;
  }
  return newNode != NULL ? newNode : NULL;
}

graphType *createGraph(int numVert) {
  int i;
  graphType *graph = (graphType*)malloc(sizeof(graphType));
  if (graph) {
    graph->numVertex = numVert;
    graph->linkedList = (node**)malloc(numVert * sizeof(node*));
    if (graph->linkedList) {
      for (i = 0; i < numVert; i++) {
        graph->linkedList[i] = NULL;
      }
    }
  }
  return graph != NULL ? graph : NULL;
}


bool edgeExists(node *head, int destinationVertex) {
  node *currentNode = head;
  while (currentNode) {
    if (currentNode->vertex == destinationVertex) {
      return true; 
    }
    currentNode = currentNode->next;
  }
  return false; 
}

void addEdge(graphType *graph, int originVertex, int destinationVertex) {
  if (!(originVertex >= graph->numVertex || destinationVertex >= graph->numVertex)) {
    if (!edgeExists(graph->linkedList[originVertex], destinationVertex)) {
      node *newNodeToOrigin = createNode(destinationVertex);
      if (newNodeToOrigin) {
        newNodeToOrigin->next = graph->linkedList[originVertex];
        graph->linkedList[originVertex] = newNodeToOrigin;
      }
    } else {
      printf("\nAresta entre os vértices %d e %d já existe.\n", originVertex, destinationVertex);
    }
  } else {
    printf("\nCondições inválidas!");
  }
}


void printGraph(graphType *graph) {
  int j;
  for (j = 0; j < graph->numVertex; j++) {
    node *currentNode = graph->linkedList[j];
    printf("\nVertice %d: ", j);
    while(currentNode) {
      printf("%d -> ", currentNode->vertex);
      currentNode = currentNode->next;
    }
  }
}

int menuOption() {
  int op;
  do {
    printf("\n1 - inserir aresta\n2 - printar grafo\n3 - halt\nEscolha uma opcao: ");
    scanf("%d", &op);
    system("clear||cls");
  } while(op > 3 || op < 1);
  return op;
}

int main() {
  graphType *graph;
  int numMaxVertex = getGenericValue("\nInforme a quantidade de vertices do grafo: "), op, originVertex, destinationVertex;
  graph = createGraph(numMaxVertex);
  if (graph) {
    do {
      op = menuOption();
      switch (op) {
        case 1:
          originVertex = getGenericValue("\nInforme o vertice origem: ");
          destinationVertex = getGenericValue("\nInforme o vertice de destino: ");
          addEdge(graph, originVertex, destinationVertex);
          break;
        case 2:
          printGraph(graph);
          break;
        default:
          printf("\nFIIIIIIIIIIIIIIM");
      }
    } while(op != 3);
  }
  return 0;
}