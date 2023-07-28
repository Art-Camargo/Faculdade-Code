#include <stdio.h>
#include <stdlib.h>
#define TAM 3 //para fins didáticos, usa-se duas matriz de tamanhos de linhae coluna = ao TAM para ambas as matrizes

//Função que lê, via teclado, os dados inteiros de cada posição da matriz
void preenche_matriz(int mat[TAM][TAM], int tamanho) {
  int i, j;
  for(i = 0; i < tamanho; i++) {
    for(j = 0; j < tamanho; j++) {
      system("cls||clear");
      printf("\nInforme o valor da posicao [%d, %d] da matriz: ", i, j);
      scanf("%d", &mat[i][j]);
    }
  }
}

//Função que zera todas as posições da matriz obtida após a multiplicação das outras matrizes
void zera_matriz(int matt[TAM][TAM], int tam) {
  int x, y;
  for(x = 0; x < tam; x++) {
    for(y = 0; y < tam; y++) {
      matt[x][y] = 0;
    }
  }
}

//função que imprime as matrizes 
void imprime_matriz(int array_2d[TAM][TAM], int comprimento_array) {
  int g, u;
  for(g = 0; g < comprimento_array; g++) {
    for(u = 0; u < comprimento_array; u++) {
      printf("%d    ", array_2d[g][u]);
    }
  }
}

//função que realiza o cálculo da multiplicação da matriz matrix pela matrix2
void multiplica_matriz(int matrix[TAM][TAM], int matrix2[TAM][TAM], int size) {
  int k, r, matriz_final[size][size], t, acumulador;
  zera_matriz(matriz_final, size);
  for(k = 0; k < size; k++) {
    for(r = 0; r < size; r++) {
      acumulador = 0;
      for(t = 0; t < size; t++) {
        acumulador += matrix[k][t] * matrix2[t][r];
      }
      matriz_final[k][r] = acumulador;
    }
  }
  //imprime a primeira matriz
  printf("\nABAIXO A PRIMEIRA MATRIZ\n");
  imprime_matriz(matrix, size);

  //imprime a segunda matriz
  printf("\nABAIXO A SEGUNDA MATRIZ\n");
  imprime_matriz(matrix2, size);
  
  // imprime o resutultado da multiplicação das matrizes acima
  printf("\nABAIXO A MATRIZ RESULTADO DA MULTIPLICACAO\n");
  imprime_matriz(matriz_final, size);
}

int main() {
  int matriz[TAM][TAM], matriz2[TAM][TAM];
  preenche_matriz(matriz, TAM);
  preenche_matriz(matriz2, TAM);
  multiplica_matriz(matriz, matriz2, TAM);
  return 0;
}