#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#define TAMANHO 100
void BubbleSort(int vetor[], int tamanho_vetor) {
	int j, aux;
	for(j = 0; j < tamanho_vetor - 1; j++) {
		if(vetor[j] > vetor[j + 1]) {
			aux = vetor[j];
			vetor[j] = vetor[j + 1];
			vetor[j + 1] = aux;
			j = -1;
		}
	}
}

void preenche_vetor(int vector[], int tam_vetor) {
	int i;
	for(i = 0; i<tam_vetor; i++) {
		vector[i] = rand() % 100;
	}
} 

int binary_search(int vetorz[], int num_busca, int tam) {
    int up = tam - 1;
    int down = 0;

    while (down <= up) {
        int posicao = (up + down) / 2;

        if (vetorz[posicao] == num_busca) {
            return posicao; // Elemento encontrado
        } else if (vetorz[posicao] < num_busca) {
            down = posicao + 1;
        } else {
            up = posicao - 1;
        }
    }

    return -1; // Elemento não encontrado
}


int main() {
	srand((unsigned int)time(NULL));
	int numero_busca, k, vet[TAMANHO], index;
	preenche_vetor(vet, TAMANHO);
	BubbleSort(vet, TAMANHO);
	numero_busca = rand() % 100;
	index = binary_search(vet, numero_busca, TAMANHO);
	printf("%d ", index);
	return 0;
}
