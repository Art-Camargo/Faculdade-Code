#include <stdio.h>
void parametro_por_referencia(int *valor) {
  *valor = 10;
}

void parametro_por_valor(int value) {
  value = 25;
}


int main() {
  int num = 1;
  parametro_por_referencia(&num); //modifica o valor, pois aponta para a posicao na memória
  parametro_por_valor(num); //modifica o valor apenas no escopo da função
  return 0;
}