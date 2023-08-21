#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef struct dados {
  char cpf[12], curso[30], data_inicio[12];
  struct dados *next;
}dado;


bool valida_cpf(char userCpf[]) {
  int i, j, digito1 = 0, digito2 = 0;
  char count[sizeof(int)*8+1];
  for(i = 0; i <= 9; i++) {
    itoa(i, count, 10);
    if((strspn(userCpf, count) == 11)) {
      return false;
    }
  }
  if(strlen(userCpf) != 11) {
    return false;
  }
  for(i = 0, j = 10; i < 9; i++, j--){
    digito1 += j * (userCpf[i] - '0'); // o o primeiro digito é o resultado de somas de produtos dos termos do cpf, até o nono termo
  }
  if((digito1%11 < 2 && userCpf[9] == '0') || (digito1%11 >= 2 && userCpf[9] == (11 - digito1%11)) + 48){
    for(i = 0, j = 11; i < 10; i++, j--){
      digito2 += j *(userCpf[i] - '0'); //após validar o dígito 10 do userCpf, valida-se o ultimo digito a partir dos numeros anteriores
    }
    if((digito2%11 < 2 && userCpf[10] == '0') || (digito2%11 >= 2 && userCpf[10] == (11 - digito2%11) + 48)){ //realiza a validação do cpf por ascii
      return true; 
    }
  }
  return false;
}

void recebe_cpf(char cpf[]) {
  bool cpf_valido;
  do {
    getchar();
    printf("\nInforme o seu cpf: ");
    fgets(cpf, 12, stdin);
    fflush(stdin);
    cpf[strcspn(cpf, "\n")] = '\0';
    cpf_valido = valida_cpf(cpf);
  } while(!cpf_valido);
  printf("\nCPF %s VALIDO", cpf);
}

bool valida_data(int dia, int mes, int ano) {
  int ano_atual, mes_atual;
  time_t now;
  struct tm *tm;
  now = time(NULL);
  tm = localtime(&now);
  ano_atual = tm->tm_year + 1900;
  mes_atual = tm->tm_mon + 1;
  if (ano_atual < ano) {
    return false;
  }
  else if(ano_atual == ano && mes_atual < mes) {
    return false;
  }
  else {
    switch (mes){
      case 4:
      case 6:
      case 9: 
      case 11:
        if(dia > 30) {
          return false;
        }
      break;
      case 2: 
        if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)) {
          if(dia > 29) {
            return false;
          }
        } 
        else {
          if(dia > 28) {
            return false;
          }
        }
      break;
    }
  }
  return true;
}

void recebe_data(char data[]) {
  bool data_valida;
  int dd, mm, yyyy;
  do {
    do {
      printf("\nInforme o dia: ");
      scanf("%d", &dd);
    }while(dd < 1 || dd > 31);

    do {
      printf("\nInforme o mes: ");
      scanf("%d", &mm);
    }while(mm < 1 || mm > 12);
    
    do {
      printf("\nInforme o ano: ");
      scanf("%d", &yyyy);
    } while(yyyy < 1);
    data_valida = valida_data(dd, mm, yyyy);
  } while(!data_valida);
  sprintf(data, "%02d/%02d/%04d", dd, mm, yyyy);
  getchar();
}

void getUndergraduateCourses(char curso[]) {
  do {
    printf("\nInforme o seu curso: ");
    fgets(curso, 30, stdin);
    fflush(stdin);
    curso[strcspn(curso, "\n")] = '\0';
  } while(!isalpha(curso[0]));
}

void insere_fim(dado **firstPointer) {
  dado *pull = (dado*)malloc(sizeof(dado)), *aux = *firstPointer;
  if (pull != NULL) {
    recebe_cpf(pull->cpf);
    recebe_data(pull->data_inicio);
    getUndergraduateCourses(pull->curso);
    if (*firstPointer == NULL) {
      pull->next = NULL;
      *firstPointer = pull;
    }
    else {
      while(aux->next != NULL) {
        aux = aux->next;
      }
      aux->next = pull;
      pull->next = NULL;
    }
  }
  else {
    printf("\nErro de memoria");
  }
}

int menuOption() {
  int val;
  do {
    printf("\n1 - insere fim\n2 - lista pessoas\n3 - fim\nInforme uma opcao acima: ");
    scanf("%d", &val);
  } while(val > 3 || val < 1);
  return val;
}

void printa_lista(dado *node) {
  dado *aux_node = node;
  if(node == NULL) {
    printf("\nnao ha nada para printar");
  }
  else {
    while(aux_node != NULL) {
      
      printf("\nEndereco do No: %p, cpf: %s, curso: %s, inicio: %s, proximo No: %p", aux_node, aux_node->cpf, aux_node->curso, aux_node->data_inicio, aux_node->next);
      aux_node = aux_node->next;   
    }
  }
}

int main() {
  int op;
  dado *first = NULL;
  do {
    op = menuOption();
    switch (op){
    case 1:
      insere_fim(&first);
    break;
    case 2:
      printa_lista(first);
    break;
    case 3:
      printf("\nPrograma finalizado com sucesso");
    break;
    }
  } while(op != 3);
  return 0;
}