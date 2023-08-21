#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

typedef struct produto_pizza {
  float preco_pizza;
  char nome_pizza[30];
}pizza;

typedef struct cliente_pizzaria {
  char nome[30], endereco[30];
  int codigo;
}cliente;

typedef struct cadastro_venda {
  int codigo_pizza, codigo_cliente, qtd_pizza;
  float valor_venda;
}venda;

void cadastra_pizzas(FILE *arq_pizzas, char URL[]) {
  pizza *prod_pizzas;
  bool fim = false;
  int code = -1, op;
  arq_pizzas = fopen(URL, 'w+');
  do {
    system("clear||cls");
    code++;
    do {
      printf("\nInforme o preco da pizza %d: ", code);
      scanf("%f", &prod_pizzas->preco_pizza);
    } while(prod_pizzas->preco_pizza <= 0.0);
    do {
      printf("\nInforme, corretamente, o nome da pizza de codifo %d: ");
      fgets(prod_pizzas->nome_pizza, 30, stdin);
      fflush(stdin);
      prod_pizzas->nome_pizza[strcspn(prod_pizzas->nome_pizza, "\n")] = '\0';
    } while(!isalpha(prod_pizzas->nome_pizza[0]));
    fprintf(arq_pizzas, "%s;%f;%d\n", prod_pizzas->nome_pizza, prod_pizzas->preco_pizza, code);
    printf("\n1 - cadastrar mais pizzas\nqualquer tecla - exit\nEscolha uma opcao acima: ");
    scanf("%d", &op);
    if(op != 1) {
      fim = true;
    }
  } while(!fim);
  fclose(arq_pizzas);
}

int menuOption() {
  int option;
  do {
    printf("\n1 - Cadastrar compra do cliente\n2 - printar as pizzas\n3 - printar dados dos clientes");
    printf("\n4 - printar dados de venda\nEscolha uma opcao acima: ");
    scanf("%d", option);
  }while(option > 4 || option < 1);
  return option;
}

void cadastra_cliente(FILE *cl, char URL_C[]) {
  
}

void cadastra_venda_cliente(FILE *vendas, char URL_VENDAS[]) {

}

int main() {
  FILE *arq_venda, *cliente, *pizzas;
  char URL_VENDA = "vendas.txt", URL_CLIENT = "clientes.txt", URL_PIZZAS = "pizzas.txt";
  bool dia_acabou = false;
  int opcao;
  cadastra_pizzas(pizzas, URL_PIZZAS);
  do {
    system("clear||cls");
    opcao = menuOption();
    switch (opcao){
    case 1: 
      cadastra_cliente(cliente, URL_CLIENT);
      cadastra_venda_cliente(arq_venda,URL_VENDA);
    break;
    case 2: 
    break;
    case 3: 
    break;
    case 4: 
    break;
    }
  } while(!dia_acabou);
  return 0;
}