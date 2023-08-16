#include <stdio.h>
#include <stdbool.h>

int retorna_num() {
  int val;
  printf("\nInforme um valor inteiro: ");
  scanf("%d", &val);
  return val;
}

void le_valores_vetor(int vect[], int tamVet) {
  int i;
  for(i = 0; i < tamVet; i++) {
    printf("\nInforme o valor da posicao %d: ", i);
    scanf("%d", &vect[i]);
  } 
}

bool indexSearch(int vet[], int tam, int search, int *ind) {
  int j;
  for(j = 0; j < tam; j++) {
    if(vet[j] == search) {
      *ind = j;
      return true;
    }
  }
  return false;
}

int main() {
  bool found;
  int index, busca, valores[20];
  le_valores_vetor(valores, 20);
  busca = retorna_num();
  found = indexSearch(valores, 20, busca, &index);
  if (found) {
    printf("\nNUMERO %d ENCONTRADO NA POSICAO %d DO VETOR!", busca, index);
  }
  else {
    printf("\nNUMERO %d NAO ENCOTRADO VETOR!", busca);
  }
  return 0;
}