/*Suponha que em um laboratório, cada paciente quando chega escolhe uma senha para atendimento.
Essa senha pode ser para realizar exames de sangue ou exames de imagem.
Quando um paciente é chamado pelo atendente ele deve informar o número da senha, seu nome, o plano de saúde(Unimed/Ipê) e o tipo de exame a fazer(sangue/imagem). 
Ao término do dia, cada atendente gera a listagem dos pacientes que ele atendeu. Apresente:

A listagem dos pacientes atendidos
A quantidade de pacientes atendidos que possuem Unimed.
A quantidade de pacientes atendidos para realizar exames de Sangue.

OBS: Apresente os dados com a seguinte construção (endereço do nó, valores do nó, valor do próximo). 
*/
//sComo não foi especificado qual ou como será a senha, assumi que a senha começa em 0 e incrementa a cada cliente.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

typedef struct pacientes {
  struct pacientes *next;
  char blood_teste_modality[7], health_insurance[7];
  int password;
}paciente;

int read_patient_data() {
  int opcao_data;
  do{
    printf("\nInforme apenas os numeros vvalidos: ");
    scanf("%d", &opcao_data);
  } while (opcao_data > 2 || opcao_data < 1);
  return opcao_data;
}

void aloca_ecolha(char escolha1[], char escolha2[], int opcao_escolha, char escolha_paciente[]) {
  if (opcao_escolha == 1) {
    strcpy(escolha_paciente, escolha1);
  }
  else {
    strcpy(escolha_paciente, escolha2);
  }
}

void get_patient_data(paciente **first, int pass) { //a inserção é feita pelo fim, a nível de fila
  paciente *newPacient = (paciente*)malloc(sizeof(paciente)), *aux = *first;
  int escolha;
  if (newPacient != NULL) {
    newPacient->password = pass;
    getchar();
    printf("\nInforme, em inteiro.\n1 - unimed ou 2 - ipe");
    escolha = read_patient_data();
    aloca_ecolha("unimed", "ipe", escolha, newPacient->health_insurance);

    printf("\nInforme, em inteiro.\n1 - exame de sangue ou 2 - exame de imagem");
    escolha = read_patient_data();
    aloca_ecolha("sangue", "imagem", escolha, newPacient->blood_teste_modality);
    if (*first == NULL) {
      newPacient->next = NULL;
      *first = newPacient;
    }
    else {
      while (aux->next != NULL) {
        aux = aux->next;
      }
      aux->next = newPacient;
      newPacient->next = NULL;
    }
  }
  else {
    printf("\nNao foi possivel alcoar memoria");
  }
} 

int menu_option() {
  int option;
  do {
    printf("\n1 - Chamar cliente pela senha\n2 - encerrar dia de trabalho\nEscolha uma opcao acima: ");
    scanf("%d", &option);
  } while(option > 2 || option < 1);
  return option;
}

void printa_tudo(paciente *first) {
  paciente *aux_print = first;
  while(aux_print != NULL) {
    printf("\nsenha: %d\tplano: %s\texame: %s\tponteiro: %p\tprox: %p", aux_print->password, aux_print->health_insurance, aux_print->blood_teste_modality, aux_print, aux_print->next);
    aux_print = aux_print->next;
  }
}

int exame_counter(char exame[], paciente *stPacient) {
  paciente *st = stPacient;
  int count = 0;
  if (stPacient == NULL) {
    return 0;
  }
  else {
    while(st != NULL) {
      if (!strcmp(st->blood_teste_modality, exame)) {
        count++;
      }
      st = st->next;
    }
  }
  return count;
}

int plano_counter(char planos[], paciente *comeco) {
  paciente *ini = comeco;
  int count_total = 0;
  if (comeco == NULL) {
    return 0;
  }
  else {
    while(ini != NULL) {
      if (!strcmp(ini->health_insurance, planos)) {
        count_total++;
      }
      ini = ini->next;
    }
  }
  return count_total;
}

int main() {
  paciente *first_patient = NULL;
  int op, senha = 0, count_exames = 0, count_plano = 0;
  do {
    op = menu_option();
    switch (op){
      case 1:
        get_patient_data(&first_patient, senha);
        senha++;
      break;
      case 2:
        //falta fazer o resto (printar quantos escolheram unimed, quantos exames de sague e total de pacientes);
        count_exames = exame_counter("sangue", first_patient);
        count_plano = plano_counter("unimed", first_patient);
      break;
    }
  } while(op != 2);
  printa_tudo(first_patient);
  printf("\ntotal de pacientes = %d, total de unimed = %d, total de sangue = %d", senha, count_plano, count_exames);
  return 0;
}