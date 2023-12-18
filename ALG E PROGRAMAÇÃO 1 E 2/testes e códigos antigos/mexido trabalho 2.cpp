#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct informacoes{
    char nome[30], cpf[12], rua[30], bairro[30]; //nome da pessoa // estou usando um digito a mais pois, usando string em C, ha um \n adicionado no final da string pelo fgets //nome da rua
    int num_rua, data_compra[3], data_nasc[3]; //numero da rua //nome do bairro
    float valor_acumulado; //valor acumulado em compras
}dados;
void nome_e_rua(char rua[], char nomes[], int *num_casa){ // Função obter alguns dados iniciais, como nome, rua e bairro
    getchar();  //limpa o buffer do teclado para não haver \n no final
    printf("\nInforme o seu nome: ");
    fgets(nomes, 30, stdin);
    nomes[strcspn(nomes, "\n")] = '\0'; // remove o \n no final da string em todos os casos!!
    printf("\nInforme a sua rua: ");
    fgets(rua, 30, stdin);
    rua[strcspn(rua, "\n")] = '\0'; 
    printf("\nInforme o numero da sua casa: ");
    scanf("%d", &(*num_casa));
    while(*num_casa < 0){ //verifica se o número é negativo, pois não existe numero de casa negativo!!
        printf("\nInvalido!! Informe o numero da sua casa: ");
        scanf("%d", &(*num_casa));
    }
}
void printa_menu(){ //printa o menu inicial 
    printf("\n1 - Cadastras Cliente");
    printf("\n2 - Listar Cliente por data de compra");
    printf("\n3 - Informar quantos clientes moram em um bairro");
    printf("\n4 - Listar cliente com maior valor acumulado em compras");
    printf("\n5 - FIM");
}
int escolha_menu(){ //função para obter a opção do menu, de 1 a 5
    int op;
    printf("\nEscolha uma opcao acima: ");
    scanf("%d", &op);
    while(op < 1 || op > 5){
        printf("\nInvalido! Escolha uma opcao valida acima: ");
        scanf("%d", &op);
    }
    return op; 
}
bool valida_cpf(char Cpf[], dados CPF_CLIENTES[], int qtd_CPFS){ //funcao booleana para validar o cpf
    bool auxiliador_validacao = true;
    int j, i, digito1 = 0, digito2 = 0, conta_iguais = 0;
    for(j = 0; j < 11; j++){
        if(isalpha(Cpf[j])){
            auxiliador_validacao = false;
        }
        if(j > 0 && Cpf[j - 1] == Cpf[j]){
            conta_iguais++;
        }
    }
    for(j = 0; j < qtd_CPFS; j++){
    	if(strcmp(Cpf, CPF_CLIENTES[j].cpf) == 0){
    		auxiliador_validacao = false;
    		printf("\n CPF JA CADASTRADO NO SISTEMA!!!");
		}
	}
    if(auxiliador_validacao && Cpf[11] == '\0' && conta_iguais < 10){
        for(i = 0, j = 10; i < 9; i++, j--){
            digito1 += j * (Cpf[i] - '0'); // o o primeiro digito é o resultado de somas de produtos dos termos do cpf, até o nono termo
        }
        if((digito1%11 < 2 && Cpf[9] == '0') || (digito1%11 >= 2 && Cpf[9] == (11 - digito1%11)) + 48){
            for(i = 0, j = 11; i < 10; i++, j--){
                digito2 += j *(Cpf[i] - '0'); //após validar o dígito 10 do cpf, valida-se o ultimo digito a partir dos numeros anteriores
            }
            if((digito2%11 < 2 && Cpf[10] == '0') || (digito2%11 >= 2 && Cpf[10] == (11 - digito2%11) + 48)){ //realiza a validação do cpf por ascii
                auxiliador_validacao = true; 
            }
            else{
                auxiliador_validacao = false;
            }
        }
        else{
            auxiliador_validacao = false;
        }
    }
    else{
        auxiliador_validacao = false;
    }
    return auxiliador_validacao; // após validar, retorna true or false
}
void testa_cpf(char CPF[], bool *cpf_valido, dados clientes_cpf[], int qtd_cpf){
    int j;
    do{
        printf("\nInforme o seu cpf: ");
        scanf("%12s", CPF);
        CPF[strcspn(CPF, "\n")] = '\0';
        //getchar();
        if(valida_cpf(CPF, clientes_cpf, qtd_cpf)){
            printf("\nCPF valido!");
            *cpf_valido = true;
        }
        else{
            printf("\nInvalido!!!!");
            *cpf_valido = false; 
        }
    }while(!(*cpf_valido)); //faz enquanto o cpf não é valido!
}
void valor_clientes(dados valor_ac[], int index_client){ //função para obter o valor de compra dos clientes, de forma genérica
	printf("\nInforme o valor acumulado do cliente: ");
	scanf("%f", &valor_ac[index_client].valor_acumulado);
	while(valor_ac[index_client].valor_acumulado< 0.0){
		printf("\nInvalido! Informe um valor maior ou igual a 0 acumulado do cliente: ");
		scanf("%f", &valor_ac[index_client].valor_acumulado);
	}
}
void datas_generico(int data[]){ //essa função pode ser usada em mais de uma opção do menu, tornando-a genérica. Assim, posicao 0 = dia, 1 = mes, 2 = ano
	printf("\nInforme o ano: ");
	scanf("%d", &data[2]);
	while(data[2] > 2023 || data[2] < 1){
		printf("\nInvalido!! Informe o ano: "); //faz a verificação dos anos
		scanf("%d", &data[2]);
	}
	printf("\nInforme o mes: ");
	scanf("%d", &data[1]);
	while(data[1] > 12 || data[1] < 1){
		printf("\nInvalido!! Informe o mes: "); //faz a verificação dos meses
		scanf("%d", &data[1]);
	}
	printf("\nInforme o dia: ");
	scanf("%d", &data[0]);
	if(data[1] == 2){ // aqui, após digitar o dia, verifica-se se não é um ano bissexto ou se o usuário digitar algo errado
		if(data[2]%400 == 0 || (data[2]%4 == 0 && data[2]%100 != 0)){ //essa condição é para se ano = bissexto
			while(data[0] > 29 || data[0] < 1){ // se sim, e o mes = 2, aceita-se até o dia 29
				printf("\nDia invalido para o mes %d. Informe um dia valido: ", data[1]);
				scanf("%d", &data[0]);
			}
		}
		else{
			while(data[0] > 28 || data[0] < 1){ //nao é bissexto. Logo, pode até o dia 28 de fevereiro!
				printf("\nO ano não é bissexto!!! Dia invalido, Informe um dia valido: ");
				scanf("%d", &data[0]);
			}
		}
	}
	else{ //meses diferentes de fevereiro, sem se preocupar se é ano bissexto ou não
		if(data[1] == 4 || data[1] == 6 || data[1] == 7 || data[1] == 11){ //meses de até 30 dias, abril, junho, setembro e novembro
			while(data[0] > 30 || data[0] < 1){
				printf("\nDia invalido para o mes %d. Informe um dia valido: ", data[1]);
				scanf("%d", &data[0]);
			}
		}
		else{//meses de até 31 dias, janeiro, março, maio, julho, agosto, outubro, dezembro
			while(data[0] > 31 || data[0] < 1){
				printf("\nDia invalido para o mes %d. Informe um dia valido: ", data[1]);
				scanf("%d", &data[0]);
			}
		}
	}
}
void maior_valor(dados clientes_valores[], int qtd){
	int k, primeiro = 0;
	float maior;
	for(k = 0; k < qtd; k++){ //estrutura de repetição que valida o maior valor acumulado
		if(k == 0){
			maior = clientes_valores[k].valor_acumulado;
		}else{
			if(clientes_valores[k].valor_acumulado > maior){
				maior = clientes_valores[k].valor_acumulado;
			}
		}
	}
	for(k = 0; k < qtd; k++){
		if(primeiro == 0 && clientes_valores[k].valor_acumulado == maior){ //se houver mais de um valor sendo o maior, usa-se o primeiro, com a flag "primeiro".
			primeiro++;
			printf("O cliente %s tem o maior valor acumulado, sendo igual a %.2f", clientes_valores[k].nome, clientes_valores[k].valor_acumulado);
		}
	}
}
void UpperCase(char palavra[]){
    int v;
    for(v = 0; v < strlen(palavra); v++){
        palavra[v] = toupper(palavra[v]);
    }
}
void conta_clientes(dados usuarios[], int ultimo_clt){
	int h, moram_bairro = 0; // a flag "moram_bairro" é um contador de quantas pessoas moram em um bairro digitado pelo teclado
	char bairro_informado[30];
	if(ultimo_clt > 0){
		printf("\nInforme um bairro: ");
		fgets(bairro_informado, 30, stdin);
		bairro_informado[strcspn(bairro_informado, "\n")] = '\0';
		UpperCase(bairro_informado);
		for(h = 0; h < ultimo_clt; h++){ //mantem todos os bairros da struct em uppercase
		    UpperCase(usuarios[h].bairro);
			if(strcmp(bairro_informado, usuarios[h].bairro) == 0){ //compara bairro por bairro
				moram_bairro++;
			}
		}
		printf("\nHa %d compradores no bairro %s", moram_bairro, bairro_informado);
	}
	else{
		printf("\nNao ha clientes cadastrados!!!");
	}
}
int main(){
    dados *clientes; //struct dinâmica para o programa geral
    bool valido = false; //variável booleana para validar cpf
    int qtd_clientes, operacao, cliente_atual = 0, DATA_BUSCA[3], x, y, aux_busca = 0, count = 0; //x e y são flags de for
    printf("\nInforme quantos clientes a empresa possui: ");
    scanf("%d", &qtd_clientes);
    while(qtd_clientes < 1){
        printf("\nInvalido! Informe quantos clientes a empresa possui: ");
        scanf("%d", &qtd_clientes); //não existe quantidade negativa de clientes
    }
    clientes = (dados *)malloc(qtd_clientes * sizeof(dados));
    if(clientes != NULL){ //se houver espaço na memória, o programa roda
        do{
            printa_menu(); //funcao de print de menu
            operacao = escolha_menu(); //funcao de escolha de menu
            system("clear||cls"); //funcao para dar clear no cmd
            switch(operacao){
                case 1: 
                    if(cliente_atual < qtd_clientes){
                        nome_e_rua(clientes[cliente_atual].rua, clientes[cliente_atual].nome, &clientes[cliente_atual].num_rua);
                        getchar(); 
                        testa_cpf(clientes[cliente_atual].cpf, &valido, clientes, cliente_atual);
                        getchar();
                        valor_clientes(clientes, cliente_atual);
                        printf("\nAbaixo, informe a sua data de nascimento, dd/mm/yyyy: ");
                        datas_generico(clientes[cliente_atual].data_nasc); 
                        printf("\nAbaixo, informe a sua data de ultima compra, dd/mm/yyyy: ");
                        datas_generico(clientes[cliente_atual].data_compra); 
                        getchar();
                        printf("\nInforme o seu bairro: ");
                        fgets(clientes[cliente_atual].bairro, 30, stdin);
                        clientes[cliente_atual].bairro[strcspn(clientes[cliente_atual].bairro, "\n")] = '\0';
                        cliente_atual++;
                    }
                    else{
                        printf("\nTodos os clientes ja foram cadastrados!!!!");  
                    }
                break;
                case 2:
	                if(cliente_atual > 0){
	                    count = 0;
						printf("\nPara buscar alguem pelo cadastro, informe a data de compra da pessoa: ");
		               	datas_generico(DATA_BUSCA);
		               	for(x = 0; x < cliente_atual; x++){
		               		aux_busca = 0;
		               		for(y = 0; y < 3; y++){
		               			if(DATA_BUSCA[y] == clientes[x].data_compra[y]){
		               				aux_busca++;
								}
							}
							if(aux_busca == 3){
								printf("\nO cliente %s, cpf: %s, rua: %s numero %d comprou na data informada", clientes[x].nome, clientes[x].cpf, clientes[x].rua, clientes[x].num_rua);
								count++;
							}
						}
						if(count == 0){
							printf("\nNenhum cliente comprou na data informada!!!");
						}
					}
					else{
						printf("\nNao ha clientes cadastrados ainda!");
					}
                break;
                case 3:
                	getchar();
                	conta_clientes(clientes, cliente_atual);
                break;
                case 4:
                	if(cliente_atual > 0){
                		maior_valor(clientes, qtd_clientes);
					}
					else{
						printf("\nNao ha clientes cadastrados ainda!!");
					}
                break;
                case 5: 
                    printf("\n\n*Programa Finalizado*");
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
