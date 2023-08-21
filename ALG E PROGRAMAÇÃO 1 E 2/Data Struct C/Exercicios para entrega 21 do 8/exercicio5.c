#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

//ARTUR DE CAMARGO E GABRIEL PINOS CAMARGO

#define URL_PIZZAS "pizzas.txt"
#define URL_CLIENT "clientes.txt"
#define URL_VENDA "vendas.txt"

typedef struct produto_pizza {
  float preco;
  int codigo;
  char nome[30];
}pizza;

typedef struct cliente_pizzaria {
  char nome[30], endereco[30];
  int codigo;
}cliente;

typedef struct cadastro_venda {
  int codigo_pizza, codigo_cliente, qtd;
  float valor;
}venda;

bool procura_pizza(int codigo) {
  FILE *arquivo;
  char linha_arquivo[70], *valor_ascii;
  bool encontrado = false;

  arquivo = fopen(URL_PIZZAS, "a+");

  if(arquivo == NULL) {
    printf("Nenhuma pizza encontrada\n");
    return false;
  } else {
    while(fgets(linha_arquivo, 70, arquivo) != NULL) {
      valor_ascii = strtok(linha_arquivo, ";");
      if(codigo == atoi(valor_ascii)){
        encontrado = true;
      }
    }
    fclose(arquivo);
    return encontrado;
  }
}

bool procura_cliente(int codigo) {
  FILE *arquivo;
  char linha_arquivo[70], *valor_ascii;
  bool encontrado = false;

  arquivo = fopen(URL_CLIENT, "a+");

  if(arquivo == NULL) {
    printf("Nenhuma cliente encontrada\n");
    return false;
  } else {
    while(fgets(linha_arquivo, 70, arquivo) != NULL) {
      valor_ascii = strtok(linha_arquivo, ";");
      if(codigo == atoi(valor_ascii)){
        encontrado = true;
      }
    }
    fclose(arquivo);
    return encontrado;
  }
}

void cadastrar_pizza() {
  pizza pizza_cadastrar;
  FILE *arquivo;

  do {
    printf("Digite o codigo da pizza: ");
    scanf("%d", &pizza_cadastrar.codigo);
  } while(pizza_cadastrar.codigo < 0);
  getchar();
  do {
    printf("Digite o nome da pizza: ");
    fgets(pizza_cadastrar.nome, 30, stdin);
    fflush(stdin);
    pizza_cadastrar.nome[strcspn(pizza_cadastrar.nome, "\n")] = '\0';
  } while(strlen(pizza_cadastrar.nome) < 2);
  do {
    printf("Digite o valor da pizza: ");
    scanf("%f", &pizza_cadastrar.preco);
  } while (pizza_cadastrar.preco < 0);

  arquivo = fopen(URL_PIZZAS, "a+");

  if (arquivo != NULL) {
    fprintf(arquivo, "%d;%s;%.2f;\n", pizza_cadastrar.codigo, pizza_cadastrar.nome, pizza_cadastrar.preco);
    printf("Pizza cadastrado com sucesso!");
    fclose(arquivo);
  }

}

void cadastrar_cliente() {
  cliente cliente_cadastrar;
  FILE *arquivo;

  do {
    printf("Digite o codigo da cliente: ");
    scanf("%d", &cliente_cadastrar.codigo);
  } while(cliente_cadastrar.codigo < 0);
  getchar();
  do {
    printf("Digite o nome da cliente: ");
    fgets(cliente_cadastrar.nome, 30, stdin);
    fflush(stdin);
    cliente_cadastrar.nome[strcspn(cliente_cadastrar.nome, "\n")] = '\0';
  } while(strlen(cliente_cadastrar.nome) < 2);
  do {
    printf("Digite o endereco da cliente: ");
    fgets(cliente_cadastrar.endereco, 30, stdin);
    fflush(stdin);
    cliente_cadastrar.endereco[strcspn(cliente_cadastrar.endereco, "\n")] = '\0';
  } while(strlen(cliente_cadastrar.endereco) < 2);
  arquivo = fopen(URL_CLIENT, "a+");

  if (arquivo != NULL) {
    fprintf(arquivo, "%d;%s;%s;\n", cliente_cadastrar.codigo, cliente_cadastrar.nome, cliente_cadastrar.endereco);
    printf("Cliente cadastrado com sucesso!");
    fclose(arquivo);
  }

}

void cadastrar_venda() {
  FILE *arquivo;
  venda venda_cadastrar;

  do {
    printf("Digite o codigo da pizza: ");
    scanf("%d", &venda_cadastrar.codigo_pizza);
  } while(venda_cadastrar.codigo_pizza < 0 || !procura_pizza(venda_cadastrar.codigo_pizza));
  do {
    printf("Digite o codigo da cliente: ");
    scanf("%d", &venda_cadastrar.codigo_cliente);
  } while(venda_cadastrar.codigo_cliente < 0 || !procura_cliente(venda_cadastrar.codigo_cliente));
  do {
    printf("Digite a quantidade de pizzas vendidas:");
    scanf("%d", &venda_cadastrar.qtd);
  } while(venda_cadastrar.qtd < 0);
  do {
    printf("Digite o preco da venda:");
    scanf("%f", &venda_cadastrar.valor);
  } while(venda_cadastrar.valor < 0);

  arquivo = fopen(URL_VENDA, "a+");

  if(arquivo == NULL) {
    printf("Nao foi possivel abrir o arquivo!");
  } else {
    fprintf(arquivo, "%d;%d;%d;%f;\n", venda_cadastrar.codigo_pizza, venda_cadastrar.codigo_cliente, venda_cadastrar.qtd, venda_cadastrar.valor);
    printf("Cliente cadastrado com sucesso!");
    fclose(arquivo);
  }

}

void listar_pizzas() {
  FILE *arquivo;
  char linha_arquivo[70], *codigo_ascii, *nome, *preco;

  arquivo = fopen(URL_PIZZAS, "r");

  if(arquivo == NULL) {
    printf("Nenhuma pizza encontrada\n");
  } else {
    while(fgets(linha_arquivo, 70, arquivo) != NULL) {
      codigo_ascii = strtok(linha_arquivo, ";");
      nome = strtok(NULL, ";");
      preco = strtok(NULL, ";");
      printf("Codigo pizza: %d, nome: %s, preco: %.2f\n", atoi(codigo_ascii), nome, atof(preco));
    }
    fclose(arquivo);
  }
}

void listar_cliente() {
  FILE *arquivo;
  char linha_arquivo[70], *codigo_ascii, *nome, *endereco;

  arquivo = fopen(URL_CLIENT, "r");

  if(arquivo == NULL) {
    printf("Nenhum cliente encontrada\n");
  } else {
    while(fgets(linha_arquivo, 70, arquivo) != NULL) {
      codigo_ascii = strtok(linha_arquivo, ";");
      nome = strtok(NULL, ";");
      endereco = strtok(NULL, ";");
      printf("Codigo cliente: %d, nome: %s, endereco: %s\n", atoi(codigo_ascii), nome, endereco);
    }
    fclose(arquivo);
  }
}

void listar_vendas() {
  FILE *arquivo;
  char linha_arquivo[70], *codigo_ascii_pizza, *codigo_ascii_cliente, *qtd_ascii, *preco_ascii;

  arquivo = fopen(URL_VENDA, "r");

  if(arquivo == NULL) {
    printf("Nenhuma venda encontrada\n");
  } else {
    while(fgets(linha_arquivo, 70, arquivo) != NULL) {
      codigo_ascii_pizza = strtok(linha_arquivo, ";");
      codigo_ascii_cliente = strtok(NULL, ";");
      qtd_ascii = strtok(NULL, ";");
      preco_ascii = strtok(NULL, ";");
      printf("Codigo pizza: %d, codigo cliente: %d, qtd: %d, valor: %f\n", atoi(codigo_ascii_pizza), atoi(codigo_ascii_cliente), atoi(qtd_ascii), atof(preco_ascii));
    }
    fclose(arquivo);
  }
}

void finalizar_dia() {
  FILE *arquivo;
  char linha_arquivo[70], *preco_ascii;
  float precoTotal = 0;
  int qtdVenda = 0;

  arquivo = fopen(URL_VENDA, "r");

  if(arquivo == NULL) {
    printf("Nenhuma venda encontrada\n");
  } else {
    while(fgets(linha_arquivo, 70, arquivo) != NULL) {
      strtok(linha_arquivo, ";");
      strtok(NULL, ";");
      strtok(NULL, ";");
      preco_ascii = strtok(NULL, ";");
      qtdVenda++;
      precoTotal += atof(preco_ascii);
    }
    fclose(arquivo);
  }

  printf("Qtd de vendas: %d. valor total: %.2f", qtdVenda, precoTotal);
}


int menuOption() {
  int option;
  do {
    printf("\n1 - Cadastrar Pizza\n2 - Cadastrar cliente\n3 - Cadastrar venda");
    printf("\n4 - Imprimir pizzas cadastradas\n5 - Imprimir dados dos clientes\n6 - Imprimir vendas");
    printf("\n7 - finalizar dia\nEscolha uma opcao acima: ");
    scanf("%d", &option);
  }while(option > 7 || option < 1);
  return option;
}

int main() {
  bool dia_acabou = false;
  int opcao;
  do {
    opcao = menuOption();
    system("clear||cls");
    switch (opcao){
    case 1: 
      cadastrar_pizza();
      break;
    case 2:
      cadastrar_cliente(); 
      break;
    case 3:
      cadastrar_venda();
      break;
    case 4:
      listar_pizzas();
      break;
    case 5:
      listar_cliente();
      break;
    case 6:
      listar_vendas();
      break;
    case 7:
      finalizar_dia();
      dia_acabou = 1;
      break;
    }
  } while(!dia_acabou);
  return 0;
}