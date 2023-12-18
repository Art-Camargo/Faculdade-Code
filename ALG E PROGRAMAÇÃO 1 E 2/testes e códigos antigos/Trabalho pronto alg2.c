#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct informacoes{ // struct das informações do cliente atual. Tudo aqui será adicionado no arquivo criado.
    char nome[30], cpf[12], rua[30], bairro[30], data_compra[10], data_nasc[10], valor_acumulado[15];
    int num_rua; 
}dados; 
void print_menu(){ // função que printa as opcoes do menu. É chamada no main a cada ciclo de programa.
	printf("\n1 - CADASTRAR CLIENTE");
	printf("\n2 - LISTAR CLIENTE POR DATA INFORMADA");
	printf("\n3 - INFORMAR QUANTOS CLIENTES MORAM EM UM BAIRRO INFORMADO");
	printf("\n4 - LISTAR CLIENTE COM MAIOR VALOR ACUMULADO");
	printf("\n5 - FIM");
}
int MenuOption(){ //Função que lê uma opção válida para o menu da função print_menu ();
	int op;
	printf("\nInforme uma das opcoes acima: ");
	scanf("%d", &op);
	while(op > 5 || op < 1){ // Valida opção, aceitando apenas de 1 a 5
		printf("\nOpcao Invalida. Por favor, digite uma opcao valida: ");
		scanf("%d", &op);
	}
	return op; // retorna ao main a opcao que será utilziada em um switch case
}
void Nome_e_RUA_e_BAIRRO(char NOMEorRUAorBAIRRO[]) { // função genérica para ler strings de 30 digitos, as quais não aceitamo números, apenas digitos
    int i = 0, c;
    fgets(NOMEorRUAorBAIRRO, 30, stdin); //lê a string passada por parâmetro
    NOMEorRUAorBAIRRO[strcspn(NOMEorRUAorBAIRRO, "\n")] = '\0'; //Após ler a string, a fim de evitar um erro de quebra de linha pelo buffer  do teclado acumulado, substitui-se o "\n" concatenado na string pelo fgets pelo caaracter nulo
    while (NOMEorRUAorBAIRRO[i] != '\0') {
        if (isdigit(NOMEorRUAorBAIRRO[i])) { // condição de parada caso haja algum numero na string, o que é inválido nos casos das strings passadas por parâmetro
            printf("\nNao sao validos numeros nessa area! Digite novamente o solicitado: ");
            fgets(NOMEorRUAorBAIRRO, 30, stdin);
            NOMEorRUAorBAIRRO[strcspn(NOMEorRUAorBAIRRO, "\n")] = '\0';
            i = -1; // assumindo que ha um numero, após reescever a string, assumes-se que i tem que ser -1, pois somará logo na var, = 0
        }
        i++;
    }
}
bool GENERIC_SEARCH(char generico_char[], FILE *arquivoDOSclientes){ // pelo nome, realiza uma busca genérica em uma string. No caso, foi utilizado para o cpf
	char *linha_arquivo;
	linha_arquivo = (char*)malloc(250 * sizeof(char));
	bool var_retorno = false; 
	if(linha_arquivo == NULL){
	    printf("\nNao aloquei!!");
	}
	else{
    	while(fgets(linha_arquivo, 250, arquivoDOSclientes) != NULL){ // a cada loop, a funçao fgets le uma linha do arquivo e adc na string linha_arquivo
        	if(strstr(linha_arquivo, generico_char) != NULL){ // caso a substring genérica (cpf) seja encontrado em alguma linha, significa que esse cpf ja foi cadastrado!!!
        		var_retorno = true; //retorna true, pois ja está no arquivo!
    		}
    	}
    	free(linha_arquivo);
	}
	rewind(arquivoDOSclientes);
	return var_retorno;
}
bool valida_cpfs(char CPF[], FILE *arquivo_geral){
	bool aux_validacao = true, busca_cpf_arquivo;
	int j, i, digito1 = 0, digito2 = 0, conta_iguais = 0;
    busca_cpf_arquivo = GENERIC_SEARCH(CPF, arquivo_geral);
	if(busca_cpf_arquivo){
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
			printf("\nInvalido. Ou o cpf informado é invalido ou ele ja esta cadastrado no nosso sistema!");
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
	switch(mes){
		case 4:
		case 6:
		case 9:
		case 11:
			 while (dia > 30 || dia < 1) {
	            printf("\nDia invalido para o mes %d. Informe um dia valido: ", mes);
	            scanf("%d", &dia);
	        }
		break;
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			while (dia > 31 || dia < 1) {
	            printf("\nDia invalido para o mes %d. Informe um dia valido: ", mes);
	            scanf("%d", &dia);
	        }
		break;
		case 2:
			if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)) {
		        while (dia > 29 || dia < 1) {
		            printf("\nDia invalido para o mes %d. Informe um dia valido: ", mes);
		            scanf("%d", &dia);
		        }
		    } 
		else {
	        while (dia > 28 || dia < 1) {
	            printf("\nO ano nao e bissexto! Dia invalido. Informe um dia valido: ");
	            scanf("%d", &dia);
	        }
	    }
		break;
	}
	*datasVALIDAS = ano;
	sprintf(DDMMYYYY, "%02d%02d%04d", dia, mes, ano);
}
void VALOR_AC(char VALOR_CLIENT[]){
	float valor;
	printf("\nInforme o seu valor acumulado: ");
	scanf("%f", &valor);
	while(valor < 0.0){
		printf("\nInforme o seu valor acumulado: ");
		scanf("%f", &valor);
	}
	sprintf(VALOR_CLIENT, "%.2f", valor);
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
	    printf("\nInforme a data da sua ultima compra abaixo. Nao e possivel uma data de compra anterior ao ano de nascimento!");
	    GENERIC_DATE(clientes->data_compra, &anoCOMPRA);
	}while(anoCOMPRA <= anoNASC);
	strcat(clientes->data_compra, "#");
	VALOR_AC(clientes->valor_acumulado);
	system("cls||clear");
}
void GENERIC_COUNT(char bairrosORdate[], FILE *arqvs, int opcaoOR){
	char *line, c;
	int countBAIRROS = 0, aux_count = 0, i, count_ast = 0;
	line = (char*)malloc(250 * sizeof(char));
	if(line != NULL){
    	while(fgets(line, 250, arqvs) != NULL){
    	    count_ast = 0; //adicionei por ultimo!
        	if(strstr(line, bairrosORdate) != NULL){
        		if(opcaoOR == 0){
        			countBAIRROS++;
    			}
    			else{
    			    aux_count++;
    			    printf("\nComprou->");
    			    for(i = 0; i < strlen(line); i++){
    			        if(line[i] == '*'){
    			            count_ast++;
    			        }
    			        else{
    			            if(count_ast == 0){
        			            printf("%c", line[i]);
        			        }
    			        }
    			    }
    			}
    		}
    	}
	}
	if(opcaoOR == 0){
		printf("\nHa %d clientes no bairro %s", countBAIRROS, bairrosORdate);
	}
	if(aux_count == 0 && opcaoOR == 1){
	    printf("\nNenhum cliente comprou na data informada");
	}
	free(line);
}
void valorMAXac(FILE *arquivoTOTAL) {
	char *token, *al, *char_aux;
	float max = 0.0, atual;
	int count_generic, h;
	bool found_ast = false;
	if((al = (char*)malloc(250 * sizeof(char))) != NULL && (char_aux = (char*)malloc(20 * sizeof(char))) != NULL){
		while(fgets(al, 250, arquivoTOTAL) != NULL){
			count_generic = 0;
			token = strtok(al, ";");
			while(token != NULL){
				count_generic++;
				if(count_generic > 0){
					atual = (float)atof(token);
					if(atual > max){
						max = atual;
					}
				}
				token = strtok(NULL, ";");
			}
		}
		count_generic = 0;
		sprintf(char_aux, "%.2f", max);
		rewind(arquivoTOTAL);
		while(fgets(al, 250, arquivoTOTAL) != NULL){
			if(strstr(al, char_aux) != NULL){
				count_generic++;
				if(count_generic == 1){
					printf("\nCliente mais fiel (maior comprador) - > ");
					for(h = 0; h < strlen(al); h++){
						if(al[h] == '*'){
							found_ast = true;
						}
						if(!found_ast){
							printf("%c", al[h]);
						}
					}
				}
			}
		}
	}
	free(char_aux);
	free(al);
}
int main(){
	FILE *arquivo; //arquivo usado para armaenar os dados
	dados db_clients; // variável do tipo da struct
	int opcao, auxx;
	char bairros_busca[30], data_busca[10], url[] = "Cadastro-clientes.txt"; //url é uma variável para a abertura do arquivo
	do{
		print_menu(); // printa o menu
		opcao = MenuOption(); // atribui o valor da opcao 
		system("cls||clear"); 
		switch(opcao){
			case 1: 
				arquivo = fopen(url, "a+"); //abre o arquivo na função de append, ou seja, "concatenando" mais informaççoes sem reiniciar o arquivo
				if(arquivo){ //verifica se o arquivo pode abrir
					CadClient(&db_clients, arquivo); // função que cadastra todos os dados do cliente
					fprintf(arquivo, "%s, cpf: %s, rua: %s, %d*, bairro: %s., data de nascimento: %s, data de compra: %s;%s\n", db_clients.nome, db_clients.cpf, db_clients.rua, db_clients.num_rua, db_clients.bairro, db_clients.data_nasc, db_clients.data_compra, db_clients.valor_acumulado);
	       			fclose(arquivo); // o f printf é usado para armazenar todos os valores no arquivo, com sintaxe (FILE *arquivo, "atributos", strings que vão ao arquivo)
				}
				else{
					printf("\nNao foi possivel abrir o arquivo!");
				}
			break;
			case 2:
			    arquivo = fopen(url, "r");
			    if(arquivo){
    				printf("\nInforme a data de compra que deseja buscar: ");
    				GENERIC_DATE(data_busca, &auxx);
    				strcat(data_busca, "#"); //para diferenciar data de nasc pela de compra, usae-se esse digito auxiiar de localização no arquivo
    				GENERIC_COUNT(data_busca, arquivo, 1); //busca a data em uma função genérica, a msm que procura o bairro
    				fclose(arquivo);
			    }
			    else{
			        printf("\nNao ha clientes cadastrados e nem um arquivo iniciado!"); // abrir em read só acontece se ja existir o arquivo!
			    }
			break;
			case 3:
				getchar();
				arquivo = fopen(url, "r");
				if(arquivo){
					printf("\nInforme o bairro que deseja buscar: ");
					Nome_e_RUA_e_BAIRRO(bairros_busca); // variável para busca no arquivo!
					while(strlen(bairros_busca) < 4){ // não existe bairro com menos de 4 letras!
						printf("\nNão ha bairros com menos de 4 digitos no Brasil!. Informe o bairro que deseja buscar: ");
						Nome_e_RUA_e_BAIRRO(bairros_busca);
					}
					UpperCase(bairros_busca); //põe o bairro em uppercase
					strcat(bairros_busca, "."); // concatena um digito verificador 
					GENERIC_COUNT(bairros_busca, arquivo, 0); //Função genérica para encontrar clientes que moram em um bairro e contar
					fclose(arquivo);
				}
				else{
					printf("\nNao ha clientes cadastrados e nem um arquivo iniciado!");
				}
			break;
			case 4:
			    arquivo = fopen(url, "r");
			    if(arquivo){
			    	valorMAXac(arquivo); //Função que utiliza técnica de tokens em uma string de linha de arquivo para pegar os valores acumulados
			    	fclose(arquivo);
			    }
			    else{
			        printf("\nNao ha clientes cadastrados e nem um arquivo iniciado!");
			    }
			break;
			case 5:
				printf("\nPrograma finalizado e os seus clientes foram armazenados no seu arquivo!"); //finaliza o programa
			break;
		}
	}while(opcao != 5);
	return 0;
}
