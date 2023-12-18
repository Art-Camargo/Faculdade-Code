#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
typedef struct informacoes{
    char nome[30], cpf[12], rua[30], bairro[30], data_compra[9], data_nasc[9];
    int num_rua; //numero da rua //nomedo bairro
    float valor_acumulado; //valor acumulado em compras
}dados;
void print_menu(){
	printf("\n1 - CADASTRAR CLIENTE");
	printf("\n2 - LISTAR CLIENTE POR DATA INFORMADA");
	printf("\n3 - INFORMAR QUANTOS CLIENTES MORAM EM UM BAIRRO INFORMADO");
	printf("\n4 - LISTAR CLIENTE COM MAIOR VALOR ACUMULADO");
	printf("\n5 - FIM");
}
int MenuOption(){
	int op;
	printf("\nInforme uma das opcoes acima: ");
	scanf("%d", &op);
	while(op > 5 || op < 1){
		printf("\nOpcao Invalida. Por favor, digite uma opcao valida: ");
		scanf("%d", &op);
	}
	return op;
}
void Nome_e_RUA_e_BAIRRO(char NOMEorRUAorBAIRRO[]) {
    int i = 0, c;
    fgets(NOMEorRUAorBAIRRO, 30, stdin);
    NOMEorRUAorBAIRRO[strcspn(NOMEorRUAorBAIRRO, "\n")] = '\0';
    //while ((c = getchar()) != '\n' && c != EOF);
    while (NOMEorRUAorBAIRRO[i] != '\0') {
        if (isdigit(NOMEorRUAorBAIRRO[i])) {
            printf("\nNao sao validos numeros nessa area! Digite novamente o solicitado: ");
            fgets(NOMEorRUAorBAIRRO, 30, stdin);
            NOMEorRUAorBAIRRO[strcspn(NOMEorRUAorBAIRRO, "\n")] = '\0';
            i = -1;
        }
        i++;
    }
}
bool GENERIC_SEARCH(char generico_char[], FILE *arquivoDOSclientes){
	char linha_arquivo[180];
	bool var_retorno = false; 
	while(fgets(linha_arquivo, sizeof(linha_arquivo), arquivoDOSclientes) != NULL){
    	if(strstr(linha_arquivo, generico_char) != NULL){
    		var_retorno = true;
		}
	}
	return var_retorno;
}
bool valida_cpfs(char CPF[], FILE *arquivo_geral){
	bool aux_validacao = true, busca_cpf_arquivo;
	int j, i, digito1 = 0, digito2 = 0, conta_iguais = 0;
	busca_cpf_arquivo = GENERIC_SEARCH(CPF, arquivo_geral);
	if(busca_cpf_arquivo && CPF[11] == '\0'){
		aux_validacao = false;
	}
	for(j = 0; j < 11; j++){
        if(isalpha(CPF[j])){
            aux_validacao = false;
        }
        if(j > 0 && CPF[j - 1] == CPF[j]){
            conta_iguais++;
        }
    }
    if(conta_iguais >= 10 || CPF[11] != '\0'){
    	aux_validacao = false;
	}
	if(aux_validacao){
		for(i = 0, j = 10; i < 9; i++, j--){
            digito1 += j * (CPF[i] - '0'); // o o primeiro digito é o resultado de somas de produtos dos termos do cpf, até o nono termo
        }
        if((digito1%11 < 2 && CPF[9] == '0') || (digito1%11 >= 2 && CPF[9] == (11 - digito1%11)) + 48){
            for(i = 0, j = 11; i < 10; i++, j--){
                digito2 += j *(CPF[i] - '0'); //após validar o dígito 10 do cpf, valida-se o ultimo digito a partir dos numeros anteriores
            }
            if((digito2%11 < 2 && CPF[10] == '0') || (digito2%11 >= 2 && CPF[10] == (11 - digito2%11) + 48)){ //realiza a validação do cpf por ascii
                aux_validacao = true; 
            }
            else{
                aux_validacao = false;
            }
        }
        else{
            aux_validacao = false;
        }
	}
	return aux_validacao;
}
void CPFs(char client_cpf[], FILE *arqv){
	bool valido;
	do{
		printf("\nInforme o seu cpf: ");
		scanf("%12s", client_cpf);
        client_cpf[strcspn(client_cpf, "\n")] = '\0';
        getchar();
        if(valida_cpfs(client_cpf, arqv)){
        	valido = true;
		}
		else{
			valido = false;
			printf("\nCPF INVALIDO!!");
		}
	}while(!valido);
}
int NUM_CASA(){
	int num;
	printf("\nInforme o numero da casa: ");
	scanf("%d", &num);
	while(num < 0){
		printf("\nINVALIDO! Informe o numero da casa: ");
		scanf("%d", &num);
	}
	return num;
}
void UpperCase(char palavra[]){
    int v;
    for(v = 0; v < strlen(palavra); v++){
        palavra[v] = toupper(palavra[v]);
    }
}
void GENERIC_DATE(char DDMMYYYY[], int *datasVALIDAS){
	int dia, mes, ano;
	printf("\nInforme o ano: ");
	scanf("%d", &ano);
	while (ano > 2023 || ano < 1) {
	    printf("\nInválido! Informe o ano: ");
	    scanf("%d", &ano);
	}
	printf("\nInforme o mes: ");
	scanf("%d", &mes);
	while (mes > 12 || mes < 1) {
	    printf("\nInválido! Informe o mes: ");
	    scanf("%d", &mes);
	}
	printf("\nInforme o dia: ");
	scanf("%d", &dia);
	if (mes == 2) {
	    if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)) {
	        while (dia > 29 || dia < 1) {
	            printf("\nDia inválido para o mes %d. Informe um dia válido: ", mes);
	            scanf("%d", &dia);
	        }
	    } 
		else {
	        while (dia > 28 || dia < 1) {
	            printf("\nO ano nao e bissexto! Dia invalido. Informe um dia valido: ");
	            scanf("%d", &dia);
	        }
	    }
	} 
	else {
	    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) {
	        while (dia > 30 || dia < 1) {
	            printf("\nDia invalido para o mes %d. Informe um dia valido: ", mes);
	            scanf("%d", &dia);
	        }
	    } 
		else {
	        while (dia > 31 || dia < 1) {
	            printf("\nDia invalido para o mes %d. Informe um dia valido: ", mes);
	            scanf("%d", &dia);
	        }
	    }
	}
	*datasVALIDAS = ano;
	sprintf(DDMMYYYY, "%02d%02d%04d", dia, mes, ano);
}
float VALOR_AC(){
	float valor;
	printf("\nInforme o seu valor acumulado: ");
	scanf("%f", &valor);
	while(valor < 0.0){
		printf("\nInforme o seu valor acumulado: ");
		scanf("%f", &valor);
	}
	return valor;
}
void CadClient(dados *clientes, FILE *arquivo_c){
    int anoCOMPRA, anoNASC;
	getchar();
	printf("\nInforme o seu NOME abaixo: ");
	Nome_e_RUA_e_BAIRRO(clientes->nome);
	printf("\n%s, Informe o nome da sua RUA abaixo: ", clientes->nome);
	Nome_e_RUA_e_BAIRRO(clientes->rua);
	clientes->num_rua = NUM_CASA();
	CPFs(clientes->cpf, arquivo_c);
	printf("\nEntre com o nome do seu bairro abaixo: ");
	Nome_e_RUA_e_BAIRRO(clientes->bairro);
	UpperCase(clientes->bairro);
	printf("\nInforme a sua data de nascimento abaixo");
	GENERIC_DATE(clientes->data_nasc, &anoNASC);
	do{
	    printf("\nInforme a data da sua ultima compra abaixo");
	    GENERIC_DATE(clientes->data_compra, &anoCOMPRA);
	}while(anoCOMPRA <= anoNASC);
	clientes->valor_acumulado = VALOR_AC();
}
void GENERIC_COUNT(char bairrosORdate[], FILE *arqvs, int opcaoOR){
	char line[256];
	int countBAIRROS = 0, aux_count = 0;
	while(fgets(line, sizeof(line), arqvs) != NULL){
    	if(strstr(line, bairrosORdate) != NULL){
    		if(opcaoOR == 0){
    			countBAIRROS++;
			}
			else{
				printf("\nO cliente %s comprou na data informada!", line);
				aux_count++;
			}
		}
	}
	if(opcaoOR == 0){
		printf("\nHa %d clientes no bairro %s", countBAIRROS, bairrosORdate);
	}
	if(aux_count == 0 && opcaoOR == 1){
	    printf("\nNenhum cliente comprou na data informada");
	}
}
float valorMAXac(FILE *arquivoTOTAL){
    
}
int main(){
	FILE *arquivo;
	dados db_clients;
	int opcao, auxx;
	char bairros_busca[30], data_busca[10];
	do{
		print_menu();
		opcao = MenuOption();
		system("cls||clear");
		switch(opcao){
			case 1: 
				arquivo = fopen("Cadastro-clientes.txt", "a+");
				if(arquivo){
					CadClient(&db_clients, arquivo);
					fprintf(arquivo, "Nome: %s, cpf: %s, rua: %s, num: %d, bairro: %s, data de nascimento: %s, data de compra: %s, valor acumulado: %.2f\n", 
	       			db_clients.nome, db_clients.cpf, db_clients.rua, db_clients.num_rua, 
	       			db_clients.bairro, db_clients.data_nasc, db_clients.data_compra, db_clients.valor_acumulado);
	       			fclose(arquivo);
				}
				else{
					printf("\nNao foi possivel abrir o arquivo!");
				}
			break;
			case 2:
			    arquivo = fopen("Cadastro-clientes.txt", "r");
			    if(arquivo){
    				printf("\nInforme a data de compra que deseja buscar: ");
    				GENERIC_DATE(data_busca, &auxx);
    				GENERIC_COUNT(data_busca, arquivo, 1);
    				fclose(arquivo);
			    }
			    else{
			        printf("\nNao foi possivel abrir o arquivo para a busca da data!");
			    }
			break;
			case 3:
				getchar();
				arquivo = fopen("Cadastro-clientes.txt", "r");
				if(arquivo){
					printf("\nInforme o bairro que deseja buscar: ");
					Nome_e_RUA_e_BAIRRO(bairros_busca);
					UpperCase(bairros_busca);
					GENERIC_COUNT(bairros_busca, arquivo, 0);
					fclose(arquivo);
				}
				else{
					printf("\nNao foi possivel abrir o arquivo!");
				}
			break;
			case 4:
			    arquivo = fopen("Cadastro-clientes.txt", "r");
			    if(arquivo){
			        
			    }
			    else{
			        printf("\nNao foi possivel abrir o arquivo para a busca do valor acumulado!");
			    }
			break;
			case 5:
				printf("\nPrograma finalizado e os seus clientes foram armazenados no seu arquivo!");
			break;
		}
	}while(opcao != 5);
	fclose(arquivo);
	return 0;
}
