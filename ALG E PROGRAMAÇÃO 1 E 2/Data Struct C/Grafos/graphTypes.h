
#ifndef GRAPHTYPES_H
#define GRAPHTYPES_H


typedef struct vertice {
  int valor;
} vertice;

typedef struct listaAdjacencia {
  vertice *vertc;
} listaAdjacencia;

typedef struct grafo {
  int numVertice;
  listaAdjacencia **listaAdj;
} grafo;


#endif // GRAFO_H