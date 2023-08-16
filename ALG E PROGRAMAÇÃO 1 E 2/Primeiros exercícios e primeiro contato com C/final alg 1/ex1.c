/*
Crie um vetor de 16 posições de inteiros (receba os valores pelo teclado para serem armazenados). 
Posteriormente, troque os 8 primeiros valores pelos 8 últimos e vice-e-versa. 
Escreva ao final o vetor obtido.
*/
#include <stdio.h>
#define TAM_VETOR 10
void troca_posicao(int vet[], int tam) {
  int j, aux, size = tam;
  tam--;

  for(j = 0; j < size / 2; j++, tam--) {
    aux = vet[j];
    vet[j] = vet[tam];
    vet[tam] = aux; 
  }
  // tam = 9, j == 0; tam = 8, j = 1
}

void le_valores_vetor(int vect[], int tamVet) {
  int i;
  for(i = 0; i < tamVet; i++) {
    printf("\nInforme o valor da posicao %d: ", i);
    scanf("%d", &vect[i]);
  } 
}

void printa_vetor(int vetor_trocado[], int tamanho) {
  int k;
  for(k = 0; k < tamanho; k++) {
    printf("%d   ", vetor_trocado[k]);
  }
}

int main() {
  int vetor[TAM_VETOR];
  le_valores_vetor(vetor, TAM_VETOR);
  troca_posicao(vetor, TAM_VETOR);
  printa_vetor(vetor, TAM_VETOR);
  return 0;
}