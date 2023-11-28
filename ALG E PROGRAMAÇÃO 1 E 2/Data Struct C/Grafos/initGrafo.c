#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//Artur de Camargo e Julio Borges de Castilhos
//vertices são os nós
//As arestas, entretanto, são as conexões entre os vertices a partir de uma lógica em um set
//struct para vertices, struct para arestas
#define IS_UNDIRECTED_GRAPH 
#define RED "\x1b[91m"
#define CLR "\x1b[0m"

typedef struct node { 
  int vertex;
  struct node *next;
} node;

typedef struct graphType {
  int *visited;
  int numVertex;
  node **linkedList;
}graphType;

typedef struct matrix {
  int **matrix;
}matrixAdj;

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
    graph->visited = (int*)malloc(numVert * sizeof(int));
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

void depthFirstSearch(graphType *graph, int vertex) {
  node *temp = graph->linkedList[vertex];
  graph->visited[vertex] = 1;
  printf("Visitei %d \n", vertex);
  while (temp != NULL) {
    if (!graph->visited[temp->vertex]) {
      depthFirstSearch(graph, temp->vertex);
    }
    temp = temp->next;
  }
}

void depthFirstSearchInit(graphType *graph, int vertex) {
  int i;
  for (i = 0; i < graph->numVertex; i++) {
    graph->visited[i] = 0;
  }
  depthFirstSearch(graph, vertex);
}

void addEdge(graphType *graph, int originVertex, int destinationVertex) {
  if (!(originVertex >= graph->numVertex || destinationVertex >= graph->numVertex)) {
    if (!edgeExists(graph->linkedList[originVertex], destinationVertex)) {
      node *newNodeToOrigin = createNode(destinationVertex);
      if (newNodeToOrigin) {
        newNodeToOrigin->next = graph->linkedList[originVertex];
        graph->linkedList[originVertex] = newNodeToOrigin;
        #ifdef IS_UNDIRECTED_GRAPH 
          node *newNodeToDestination = createNode(originVertex);
          if (newNodeToDestination && originVertex != destinationVertex) {
            newNodeToDestination->next = graph->linkedList[destinationVertex];
            graph->linkedList[destinationVertex] = newNodeToDestination;
          }
        #endif
      }
    } else {
      printf("\nAresta entre os vertices %d e %d ja existe.\n", originVertex, destinationVertex);
    }
  } else {
    printf("\nCondicoes invalidas!");
  }
}


void printGraphByLinkedList(graphType *graph) {
  int j;
  for (j = 0; j < graph->numVertex; j++) {
    node *currentNode = graph->linkedList[j];
    printf("\nVertice %d: ", j);
    while(currentNode) {
      printf(CLR"%d  ", currentNode->vertex);
      if (currentNode->next != NULL) {
        printf(RED"->  ");
      }
      currentNode = currentNode->next;
    }
  }
}


int menuOption() {
  int op;
  do {
    printf("\n\n1 - inserir aresta\n2 - printar grafo\n3 - criar e printar matriz\n4 - busca com profundidade\n5 - halt\nEscolha uma opcao: ");
    scanf("%d", &op);
    system("clear||cls");
  } while(op > 5 || op < 1);
  return op;
}



void createAndInitMatrix(matrixAdj **matrix, int numMaxVertex) {
  int i, j;
  *matrix = (matrixAdj *)malloc(sizeof(matrixAdj));
  if (*matrix) {
    (*matrix)->matrix = (int **)malloc(numMaxVertex * numMaxVertex * sizeof(int *));
    for (i = 0; i < numMaxVertex; i++) {
      (*matrix)->matrix[i] = (int *)malloc(numMaxVertex * sizeof(int));
    }
    for (i = 0; i < numMaxVertex; i++) {
      for (j = 0; j < numMaxVertex; j++) {
        (*matrix)->matrix[i][j] = 0;
      }
    }
  }
}

bool isLessThanMax(int numMaxVert, int numVertCurrent) {
  if (numVertCurrent >= numMaxVert) {
    printf("\nVERTICE NAO EXISTE");
    return false;
  }
  return true;
}

void fillMatrixAndPrint(matrixAdj **matrix, int numMaxVertex, graphType *graph) {
  int k = 0, z;
  node *currentNode;
  while (k < numMaxVertex) {
    currentNode = graph->linkedList[k];
    while(currentNode) {
      (*matrix)->matrix[k][currentNode->vertex] = 1;
      currentNode = currentNode->next;
    }
    k++;
  }
  //Abaixo, não é complexo, é apenas uma lógica para printar de uma forma pretty. A matriz fica bem clean
  printf("\n ");
  for (k = 0; k < numMaxVertex; k++) {
    printf(RED" %d", k);
  }
  for (z = 0; z < numMaxVertex; z++) {
    printf(RED"\n%d ", z);
    for (k = 0; k < numMaxVertex; k++) {
      if ((*matrix)->matrix[z][k]) {
        printf(CLR"%d ", (*matrix)->matrix[z][k]);
      } else {
        printf(CLR"- ");
      }
    }
  }
}

int main() {
  graphType *graph;
  matrixAdj *matrix;
  int numMaxVertex = getGenericValue("\nInforme a quantidade de vertices do grafo: "), op, originVertex, destinationVertex;
  graph = createGraph(numMaxVertex);
  createAndInitMatrix(&matrix, numMaxVertex);
  if (graph && matrix) {
    do {
      op = menuOption();
      system("clear||cls");
      switch (op) {
        case 1:
          originVertex = getGenericValue("\nInforme o vertice origem: ");
          destinationVertex = getGenericValue("\nInforme o vertice de destino: ");
          addEdge(graph, originVertex, destinationVertex);
          break;
        case 2:
          printGraphByLinkedList(graph);
          break;
        case 3: 
          fillMatrixAndPrint(&matrix, numMaxVertex, graph);
          break;
        case 4:
          originVertex = getGenericValue("\nInforme o vertice para a busca: ");
          if (isLessThanMax(graph->numVertex, originVertex)) {
            depthFirstSearchInit(graph, originVertex);
          } 
          break;
        default:
          free(graph), free(matrix);
          printf("\nFIIIIIIIIIIIIIIM");
      }
    } while(op != 5);
  }
  return 0;
}