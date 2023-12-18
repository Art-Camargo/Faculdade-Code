#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int value;
    struct no *next_pointer;
} No;

void insere_inicio(No **point_inicio, int val) {
    No *ponteiro;
    ponteiro = (No*)malloc(sizeof(No));
    if (ponteiro != NULL) {
    	printf("\n\nPONTEIRO = %p\n\n", ponteiro);
    	printf("\n\nPONTEIRO INICIO = %p\n\n", point_inicio);
        ponteiro->value = val;
        if (*point_inicio == NULL) {
            ponteiro->next_pointer = NULL;
            *point_inicio = ponteiro;
        } else {
            ponteiro->next_pointer = *point_inicio;
            *point_inicio = ponteiro;
        }
    }
}
void imprime_lista(No *point_inicio) {
    No *point = point_inicio;  // Atribui o valor de point_inicio a point
    while (point != NULL) {
        printf("%d ", point->value);
        point = point->next_pointer;  // Avança para o próximo nó
    }
}
int main() {
    int valor;
    No *first = NULL;  // Corrigir o nome da variável
    do {
        printf("\nInforme um valor: ");
        scanf("%d", &valor);
        insere_inicio(&first, valor);
    } while (valor != 0);
    imprime_lista(first);
    return 0;
}

