#include <ctype.h> //Fun��es: toupper(), isalpha(), isdigit(). 
#include <string.h>//Fun��es: strcmp(), strtok(), strstr().
#include <stdbool.h>//Inclui o tipo bool ao c�digo
#include <stdio.h>//Fun��o padr�o de entrada e sa�da
#include <stdlib.h>//Fun��es: malloc(), atoi(), atof(), free(), system().
typedef struct informacoes{ // struct das informa��es do cliente atual. Tudo aqui ser� adicionado no arquivo criado.
    char nome[30], cpf[12], rua[30], bairro[30], data_compra[20], data_nasc[20], valor_acumulado[15];
    int num_rua; 
}dados; 
int MenuOption(){ //Fun��o que l� uma op��o v�lida para o menu da fun��o.
	int op;
	printf("\n1 - CADASTRAR CLIENTE");
	printf("\n2 - LISTAR CLIENTE POR DATA INFORMADA");
	printf("\n3 - INFORMAR QUANTOS CLIENTES MORAM EM UM BAIRRO INFORMADO");
	printf("\n4 - LISTAR CLIENTE COM MAIOR VALOR ACUMULADO");
	printf("\n5 - FIM");
	printf("\nInforme uma das opcoes acima: ");
	scanf("%d", &op);
	while(op > 5 || op < 1){ // Valida op��o, aceitando apenas de 1 a 5
		printf("\nOpcao Invalida. Por favor, digite uma opcao valida: ");
		scanf("%d", &op);
	}
	return op; // retorna ao main a opcao que ser� utilziada em um switch case
}
void LeStringCadastro(char CadastroGenerico[]){ // fun��o utilizada para entrada de dados em strings de tamanho igual e que n�o aceitam numeros, como nome, rua e bairro.
	bool continua = true; //vari�vel que verifica se ha numeros na string 
	int i;
	while(continua){
		continua = false; //inicializa, ap�s a entrada do while, em false, pois n�o ir� continuar
		fgets(CadastroGenerico, 30, stdin);
		CadastroGenerico[strcspn(CadastroGenerico, "\n")] = '\0';
		for(i = 0; i < strlen(CadastroGenerico); i++){
			if(isdigit(CadastroGenerico[i])){ //Caso ache algum digito, continua recebe true e um recadastro ser� necessa�rio, for�ando o user a n�o digitar numeros nessa etapa
				continua = true;
			}
		}
		if(continua){
			printf("\nNumeros nessa area nao sao permitidos. Por favor, digite novamente o que foi solicitado: ");
		}
	}
}
bool BuscaCPFarquivo(char CpfSearch[], FILE *file){ //funcao que busca se o cpf j� est� cadastrado no arquivo utilizado no trabalho
	char *linha_arquivo; //ponteiro que recebe as linhas do arquivo
	bool var_retorno = false;
	linha_arquivo = (char*)malloc(250 * sizeof(char)); //aloca dinamicamente, pois � uma string mt grande
	if(linha_arquivo != NULL){
		while(fgets(linha_arquivo, 250, file) != NULL){ //a fun��o fgets recebe, a cada while, por haver \n, uma nova linha do arquivo. Caso receba NULL, n�o h� mais linha para ler no fgets e o while termina.
			if(strstr(linha_arquivo, CpfSearch) != NULL){ //compara se a substring CpfSearch est� presente na linha do arquivo. CpfSearch recebe o cpf lido do teclado.
				var_retorno = true;
			}
		}
	}
	else{
		printf("\nHouve um problema de memoria!");
	}
	rewind(file); //reposiciona o arquivo para o in�cio do txt, para futuras leituras
	free(linha_arquivo);
	return var_retorno;
}
bool ValidaCpfs(char CPF[], FILE *arquivo_geral){
	bool aux_validacao = true, busca_cpf_arquivo; 
	int j, i, digito1 = 0, digito2 = 0, conta_iguais = 0;
    busca_cpf_arquivo = BuscaCPFarquivo(CPF, arquivo_geral);
	if(busca_cpf_arquivo){ //Caso o cpf ja esteja cadastrado no sistema.
    	aux_validacao = false;
    }
	for(j = 0; j < 11; j++){
        if(isalpha(CPF[j])){
            aux_validacao = false; //caso haja algum caracter que n�o seja numero
        }
        if(j > 0 && CPF[j - 1] == CPF[j]){ //caso todos os digitos do cpf sejam iguais, o que � valido pelo algoritmo mas n�o � valido pela receita federal.
            conta_iguais++;
        }
    }
    if(conta_iguais >= 10 || CPF[11] != '\0'){ //se houver menos digitos do que 11, ou se contar muitos d�gitos iguais, atribui false
    	aux_validacao = false;
	}
	if(aux_validacao){ //caso nenhum erro anterior tenha acontecido, inicia-se a verifica��o do algoritmo do moduli 11
		for(i = 0, j = 10; i < 9; i++, j--){
            digito1 += j * (CPF[i] - '0'); // o o primeiro digito � o resultado de somas de produtos dos termos do cpf, at� o nono termo
        }
        if((digito1%11 < 2 && CPF[9] == '0') || (digito1%11 >= 2 && CPF[9] == (11 - digito1%11)) + 48){
            for(i = 0, j = 11; i < 10; i++, j--){
                digito2 += j *(CPF[i] - '0'); //ap�s validar o d�gito 10 do cpf, valida-se o ultimo digito a partir dos numeros anteriores
            }
            if((digito2%11 < 2 && CPF[10] == '0') || (digito2%11 >= 2 && CPF[10] == (11 - digito2%11) + 48)){ //realiza a valida��o do cpf por ascii
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
void LeCpfClientes(char client_cpf[], FILE *arqv){ //funcao que le, pela entrada de teclado, o cpf do cliente.
	bool valido;
	do{
		valido = true;
		printf("\nInforme o seu cpf: ");
		scanf("%12s", client_cpf);
        client_cpf[strcspn(client_cpf, "\n")] = '\0';  
        getchar();
        if(!ValidaCpfs(client_cpf, arqv)){ // se o cpf nao for valido, mantem o loop.
        	valido = false;
        	printf("\nCpf invalido. Motivos: ou o cpf ja esta cadastrado no nosso sistema ou o cpf nao e valido pelo modulo 11");
		}
	}while(!valido); //ele faz enquando o cpf nao for valido ou o cpf for encontrado no arquivo.
}
int NumCasa(){ //funcao que l� pelo teclado o numero de residencia do cliente
	int num; 
	printf("\nInforme o numero da casa: ");
	scanf("%d", &num);
	while(num < 0){
		printf("\nINVALIDO! Informe o numero da casa: ");
		scanf("%d", &num);
	}
	return num;
}
void UpperCase(char palavra[]){ //funcao gen�rica utilizada pra por uma string em maiusculo.
    int v;
    for(v = 0; v < strlen(palavra); v++){
        palavra[v] = toupper(palavra[v]);
    }
}
void LeDatasGenerico(char DDMMYYYY[]){ //Fun��o gen�rica para ler valores relacionados � data.
	int dia, mes, ano;
	printf("\nInforme o ano: "); //Para fins de um algoritmo simplificado, pede-se o ano primeiro
	scanf("%d", &ano);
	while (ano < 1 || ano > 2023) { //at� no ano atual.
	    printf("\nInv�lido! Informe o ano: ");
	    scanf("%d", &ano);
	}
	printf("\nInforme o mes: ");
	scanf("%d", &mes);
	while (mes > 12 || mes < 1) {
	    printf("\nInv�lido! Informe o mes: ");
	    scanf("%d", &mes);
	}
	printf("\nInforme o dia: ");
	scanf("%d", &dia);
	switch(mes){
		case 4:
		case 6:
		case 9:
		case 11: //cases relacionados a meses com, no m�ximo, 30 dias
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
		case 12: //cases relacionados a meses com, no m�ximo, 31 dias.
			while (dia > 31 || dia < 1) {
	            printf("\nDia invalido para o mes %d. Informe um dia valido: ", mes);
	            scanf("%d", &dia);
	        }
		break;
		case 2: //m�s fevereiro tem duas op��es de dias, sendo considerado um ano bissexto ou nao.
			if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)) { //Condi��o de ano bissexto
		        while (dia > 29 || dia < 1) {
		            printf("\nDia invalido para o mes %d. Informe um dia valido: ", mes);
		            scanf("%d", &dia);
		        }
		    } 
			else { //condi��o !ano bissexto, (negado hehe)
		        while (dia > 28 || dia < 1) {
		            printf("\nO ano nao e bissexto! Dia invalido. Informe um dia valido: ");
		            scanf("%d", &dia);
		        }
		    }
		break;
	}
	sprintf(DDMMYYYY, "%02d/%02d/%04d", dia, mes, ano); //atribui, via sprintf, a data � string passada por par�metro, que � um vetor de char.
}
void LeValorAc(char VALOR_CLIENT[]){ //fun��o para ler o valor acumulado
	float valor;
	printf("\nInforme o seu valor acumulado: ");
	scanf("%f", &valor);
	while(valor < 0.0){
		printf("\nInforme o seu valor acumulado: ");
		scanf("%f", &valor);
	}
	sprintf(VALOR_CLIENT, "%.2f", valor); //atribui ao valor acumulado (em string) via sprintf.
}
int RetornaAnos(char Ano[], int PosicaoStr){ //fun��o para valida��o de ano de compra, uma vez que o ano de compra n�o pode ser inferior ou igual a o ano de nascimento.
    int AnoChar;
    AnoChar = (int)atoi(Ano + PosicaoStr); //Atoi(string). No entando, podemos assumir a posi��o de inicio que ela quer ler, com um inteiro somado � string. Ap�s isso, caso haja outro caracter, ele para de atribuir.
    return AnoChar;
}
void CadastraCliente(dados *cliente, FILE *arquivo_db){
	getchar();
	printf("\nInforme o seu nome: ");
	LeStringCadastro(cliente->nome);
	printf("\n%s, Informe o nome da sua rua: ", cliente->nome);
	LeStringCadastro(cliente->rua);
	cliente->num_rua = NumCasa();
	LeCpfClientes(cliente->cpf, arquivo_db);
	printf("\nInforme o nome do seu bairro: ");
	LeStringCadastro(cliente->bairro);
	UpperCase(cliente->bairro);
	do{
		printf("\nAbaixo, informe a sua data de nascimento. So sao permitidos cadastros de pessoas nascidas anteriores a 2023");
		LeDatasGenerico(cliente->data_nasc);
	}while(RetornaAnos(cliente->data_nasc, 6) > 2022);
	do{
		printf("\nAbaixo, Informe a data da sua ultima compra. Obs: nao e possivel uma data de compra anterior a data de nascimento ou uma data de compra posterior a 05/2023");
		LeDatasGenerico(cliente->data_compra);
	}while(RetornaAnos(cliente->data_compra, 6) <= RetornaAnos(cliente->data_nasc, 6) || (RetornaAnos(cliente->data_compra, 6) == 2023 && RetornaAnos(cliente->data_compra, 3) > 5));
	strcat(cliente->data_compra, "#");
	LeValorAc(cliente->valor_acumulado);
	system("cls||clear");
}
void ContaPessoasBairro(char bairroBusca[], FILE *arqv){
	char *FileLine, *SplitLine;
	int contaBairros = 0;
	FileLine = (char*)malloc(250 * sizeof(char));
	if(FileLine != NULL){
		while(fgets(FileLine, 250, arqv) != NULL){
			SplitLine = strtok(FileLine, ",");
			while(SplitLine != NULL){
				if(strcmp(SplitLine, bairroBusca) == 0){
					contaBairros++;
				}
				SplitLine = strtok(NULL, ",");
			}
		}
	}
	else{
		printf("\nHouve um problema de memoria!");
	}
	printf("\nHa %d clientes morando no bairro %s", contaBairros, bairroBusca);
	rewind(arqv);
}
void BuscaData(char date[], FILE *ArquivoGeral){
	char *linha;
	bool ComprouNaData = false;
	int j;
	linha = (char*)malloc(250 * sizeof(char));
	if(linha != NULL){
		while(fgets(linha, 250, ArquivoGeral) != NULL){
			if(strstr(linha, date) != NULL){
				ComprouNaData = true;
				printf("\nComprou na data informada o seguinte cliente -> ");
				for(j = 0; linha[j] != '*'; j++){
						printf("%c", linha[j]);
				}
			}
		}
	}
	else{
		printf("\nHouve um problema de memoria");
	}
	rewind(ArquivoGeral);
	if(!ComprouNaData){
		printf("\nNenhum cliente comprou na data informada");
	}
}
void valorMAXac(FILE *arquivoTOTAL) {
	char *token, *al, *char_aux;
	float max = 0.0, atual;
	int count_generic, h;
	if((al = (char*)malloc(250 * sizeof(char))) != NULL && (char_aux = (char*)malloc(20 * sizeof(char))) != NULL){
		while(fgets(al, 250, arquivoTOTAL) != NULL){
			count_generic = 0;
			token = strtok(al, ";");
			while(token != NULL){
				if(count_generic > 0){
					atual = (float)atof(token);
					if(atual > max){
						max = atual;
					}
				}
				token = strtok(NULL, ";");
				count_generic++;
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
					for(h = 0; al[h] != ','; h++){
						printf("%c", al[h]);
					}
				}
			}
		}
	}
	free(char_aux);
	free(al);
}
int main(){
	FILE *arquivo; //arquivo usado para armazenar os dados
	dados db_clients; // vari�vel do tipo da struct
	int opcao;
	char bairros_busca[30], data_busca[20], url[] = "Cadastro-clientes.txt"; //url � uma vari�vel para a abertura do arquivo
	do{
		opcao = MenuOption(); // atribui o valor da opcao 
		system("cls||clear"); 
		switch(opcao){
			case 1: 
				arquivo = fopen(url, "a+"); //abre o arquivo na fun��o de append, ou seja, "concatenando" mais informa��oes sem reiniciar o arquivo
				if(arquivo){ //verifica se o arquivo pode abrir
					CadastraCliente(&db_clients, arquivo); // fun��o que cadastra todos os dados do cliente
					fprintf(arquivo, "%s, cpf: %s, Endereco: %s, %d*,%s., data de nascimento: %s, data de compra: %s;%s\n", db_clients.nome, db_clients.cpf, db_clients.rua, db_clients.num_rua, db_clients.bairro, db_clients.data_nasc, db_clients.data_compra, db_clients.valor_acumulado);
	       			fclose(arquivo); // o f printf � usado para armazenar todos os valores no arquivo, com sintaxe (FILE *arquivo, "atributos", strings que v�o ao arquivo)
				}
				else{
					printf("\nNao foi possivel abrir o arquivo!");
				}
			break;
			case 2:
			    arquivo = fopen(url, "r");
			    if(arquivo){
    				printf("\nInforme a data de compra que deseja buscar: ");
    				LeDatasGenerico(data_busca);
    				strcat(data_busca, "#"); //para diferenciar data de nasc pela de compra, usae-se esse digito auxiiar de localiza��o no arquivo
    				BuscaData(data_busca, arquivo); //busca a data em uma fun��o gen�rica
    				fclose(arquivo);
			    }
			    else{
			        printf("\nNao ha clientes cadastrados e nem um arquivo iniciado!"); // abrir em read s� acontece se ja existir o arquivo!
			    }
			break;
			case 3:
				getchar();
				arquivo = fopen(url, "r");
				if(arquivo){
					printf("\nInforme o bairro que deseja buscar: ");
					LeStringCadastro(bairros_busca); // vari�vel para busca no arquivo!
					UpperCase(bairros_busca); //p�e o bairro em uppercase
					strcat(bairros_busca, "."); // concatena um digito verificador 
					ContaPessoasBairro(bairros_busca, arquivo); //Fun��o gen�rica para encontrar clientes que moram em um bairro e contar
					fclose(arquivo);
				}
				else{
					printf("\nNao ha clientes cadastrados e nem um arquivo iniciado!");
				}
			break;
			case 4:
			    arquivo = fopen(url, "r");
			    if(arquivo){
			    	valorMAXac(arquivo); //Fun��o que utiliza t�cnica de tokens em uma string de linha de arquivo para pegar os valores acumulados
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
