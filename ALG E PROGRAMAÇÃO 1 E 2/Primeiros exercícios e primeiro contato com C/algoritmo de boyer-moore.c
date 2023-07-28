#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
//algoritmo de Boyer-Moore
//pré processamento de condições

//Função para deixar as strings em maiúsculo, -65 em ascii para retornar à posição do vetor
void upper_case(char str[]) {
	int i;
	for (i = 0; i < strlen(str); i++) {
		str[i] = toupper(str[i]);
	}
}

//Função que realiza o pré processamento da string menor
void pre_processa_palavra(int pre_processamento_str[], char str[]) {
	int j, k, aux = 1;
	for(j = 0; j < 26; j++) {
		pre_processamento_str[j] = strlen(str);
	}
	for(j = 0; j < strlen(str) - 1 ; j++) {
		for(k = 0; k < 26; k++) {
			if((str[j] - 65) == k) {
				pre_processamento_str[k] = strlen(str) - aux;
				aux++;
			}
		}
	}
}

bool boyer_moore(int pre_processado[], char substring[], char string[]) {
    int aux, x, y, counter;
    bool achou = false;
    for (x = strlen(substring) - 1; x < strlen(string);) {
        counter = 0;
        aux = x;
        for (y = strlen(substring) - 1; y >= 0 && aux >= 0; y--) {
            if (substring[y] == string[aux]) {
                counter++;
                aux--;
            } else {
                x += pre_processado[string[x] - 'A'];
                y = -1;
            }
        }
        if (counter == strlen(substring)) {
            achou = true;
            x = strlen(string);
        }
    }
    return achou;
}

int main() {
	char palavra[] = "Teste", string_fonte[] = "dsjhfajDKFSDfsdkkTESTjjfokaskkskdteste";
	int pre_processamento_palavra[26];
	bool encontrou;
	upper_case(palavra);
	upper_case(string_fonte);
	pre_processa_palavra(pre_processamento_palavra, palavra);
	encontrou = boyer_moore(pre_processamento_palavra, palavra, string_fonte);
	if(encontrou) {
		printf("\nPalavra %s encontrada", palavra);
	}
	else {
		printf("\nPalavra %s nao encontrada", palavra);
	}
	return 0;
}
