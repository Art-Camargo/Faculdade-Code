#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct informacoes{
    char nome[30];
    int cpf;
    char rua[30];
    int num_rua;
    char bairro[30];
    float valor_acumulado;
    int dia_nasc;
    int mes_nasc;
    int ano_nasc;
    int dia_compra;
    int mes_compra;
    int ano_compra;
}dados;
void nome_rua_bairro(dados client[], int atual)
{
    getchar();
    printf("\nInforme o seu nome: ");
    fgets(client[atual].nome, 30, stdin);
    client[atual].nome[strcspn(client[atual].nome, "\n")] = '\0'; 
    printf("\nInforme o seu bairro: ");
    fgets(client[atual].bairro, 30, stdin);
    client[atual].bairro[strcspn(client[atual].bairro, "\n")] = '\0'; 
    printf("\nInforme a sua rua: ");
    fgets(client[atual].rua, 30, stdin);
    client[atual].rua[strcspn(client[atual].rua, "\n")] = '\0'; 
    printf("\nInforme o numero da sua casa: ");
    scanf("%d", &client[atual].num_rua);
    while(client[atual].num_rua < 0){
        printf("\nInvalido!! Informe o numero da sua casa: ");
        scanf("%d", &client[atual].num_rua);
    }
}

void printa_menu()
{
    printf("\n1 - Cadastras Cliente");
    printf("\n2 - Listar Cliente por data de compra");
    printf("\n3 - Informar quantos clientes moram em um bairro");
    printf("\n4 - Listar cliente com maior valor acumulado em compras");
    printf("\n5 - FIM");
}
int escolha_menu()
{
    int op;
    printf("\nEscolha uma opcao acima: ");
    scanf("%d", &op);
    while(op < 1 || op > 5){
        printf("\nInvalido! Escolha uma opcao valida acima: ");
        scanf("%d", &op);
    }
    return op;
}
int main(){
    dados *clientes;
    int qtd_clientes, operacao, cliente_atual = 0;
    printf("\nInforme quantos clientes a empresa possui: ");
    scanf("%d", &qtd_clientes);
    while(qtd_clientes < 1){
        printf("\nInvalido! Informe quantos clientes a empresa possui: ");
        scanf("%d", &qtd_clientes);
    }
    clientes = (dados *)malloc(qtd_clientes * sizeof(dados));
    if(clientes != NULL){
        do{
            system("clear||cls");
            printa_menu();
            operacao = escolha_menu();
            system("clear||cls");
            switch(operacao){
                case 1: 
                    if(cliente_atual < qtd_clientes){
                        nome_rua_bairro(clientes, cliente_atual);
                    }
                    else{
                        printf("\nTodos os clientes ja foram cadastrados!!!!");  
                    }
                    cliente_atual++;
                break;
                case 2:
                break;
                case 3:
                break;
                case 4:
                break;
                case 5: 
                    printf("\n\n*****Programa Finalizado*****");
                break;
            }
        }while(operacao < 5);
    }
    else{
        printf("\n\nMemoria insuficente para armazenar %d clientes!!!", qtd_clientes);
    }
    free(clientes);
    return 0;
}
