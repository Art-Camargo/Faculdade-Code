#include <ctype.h> //Funções: toupper(), isalpha(), isdigit(). 
#include <string.h>//Funções: strcmp(), strtok(), strstr().
#include <stdbool.h>//Inclui o tipo bool ao código
#include <stdio.h>//Função padrão de entrada e saída
#include <stdlib.h>//Funções: malloc(), atoi(), atof(), free(), system().
typedef struct informacoes{ // struct das informações do cliente atual. Tudo aqui será adicionado no arquivo criado.
    char nome[30], cpf[12], rua[35], bairro[30], data_compra[20], data_nasc[20], valor_acumulado[15]; 
}dados; 

int MenuOption(){ //Função que lê uma opção válida para o menu da função.
	int op;
	printf("\n1 - CADASTRAR CLIENTE");
	printf("\n2 - LISTAR CLIENTE POR DATA INFORMADA");
	printf("\n3 - INFORMAR QUANTOS CLIENTES MORAM EM UM BAIRRO INFORMADO");
	printf("\n4 - LISTAR CLIENTE COM MAIOR VALOR ACUMULADO");
	printf("\n5 - FIM");
	printf("\nInforme uma das opcoes acima: ");
	scanf("%d", &op);
	while(op > 5 || op < 1){ // Valida opção, aceitando apenas de 1 a 5
		printf("\nOpcao Invalida. Por favor, digite uma opcao valida: ");
		scanf("%d", &op);
	}
	return op; // retorna ao main a opcao que será utilziada em um switch case
}

void LeStringCadastro(char CadastroGenerico[], int TamanhoString) {
    bool refaz;
    int c;
    do {
        refaz = false;
        fgets(CadastroGenerico, TamanhoString, stdin);
        if (CadastroGenerico[strlen(CadastroGenerico) - 1] != '\n') { //Condição de limpar o buffer
            while ((c = getchar()) != '\n' && c != EOF) {}  // Limpa o Buffer
        }
        CadastroGenerico[strcspn(CadastroGenerico, "\n")] = '\0';  //além do buffer, o fgets armazena o \n na string, trocado pelo \0.
        if ((!isalpha(CadastroGenerico[0])) && (!isdigit(CadastroGenerico[0]))) { //verifica se a pessoa deu enter sem querer ou nao digitou nada
            refaz = true;
        }
        if (refaz) {
            printf("\nInvalido. Informe novamente o que foi solicitado: ");
        }
    } while (refaz);
}

bool BuscaCPFarquivo(char CpfSearch[], FILE *file){ //funcao que busca se o cpf já está cadastrado no arquivo utilizado no trabalho
	char linha_arquivo[170], *token_line; //ponteiro que recebe as linhas do arquivo
	bool var_retorno = false;
	while(fgets(linha_arquivo, 170, file) != NULL){
		token_line = strtok(linha_arquivo, ";");
		while(token_line != NULL){
			if(strcmp(token_line, CpfSearch) == 0){
				var_retorno = true;
				printf("\no Cpf %s Ja esta cadastrado no nosso sistema!", CpfSearch);
			}
			token_line = strtok(NULL, ";");
		}
	}
}

bool ValidaCpfs(char CPF[], FILE *arquivo_geral){
	bool aux_validacao = true, busca_cpf_arquivo; 
	int j, i, digito1 = 0, digito2 = 0, conta_iguais = 0;
    busca_cpf_arquivo = BuscaCPFarquivo(CPF, arquivo_geral);
	if(busca_cpf_arquivo){ //Caso o cpf ja esteja cadastrado no sistema.
    	aux_validacao = false;
    }
	for(j = 0; j < 11; j++){
        if(j > 0 && CPF[j - 1] == CPF[j]){ //caso todos os digitos do cpf sejam iguais, o que é valido pelo algoritmo mas não é valido pela receita federal.
            conta_iguais++;
        }
    }
    if(conta_iguais >= 10 || CPF[11] != '\0'){ //se houver menos digitos do que 11, ou se contar muitos dígitos iguais, atribui false
    	aux_validacao = false;
	}
	if(aux_validacao){ //caso nenhum erro anterior tenha acontecido, inicia-se a verificação do algoritmo do moduli 11
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

void LeCpfClientes(char client_cpf[], FILE *arqv){ //funcao que le, pela entrada de teclado, o cpf do cliente.
	bool valido;
	int chr;
	do{
		valido = true;
		printf("\nInforme o seu cpf: ");
		scanf("%12s", client_cpf);
        client_cpf[strcspn(client_cpf, "\n")] = '\0';  
        while ((chr= getchar()) != '\n' && chr != EOF) {}
        if(!ValidaCpfs(client_cpf, arqv) || !isdigit(client_cpf[0])){ // se o cpf nao for valido, mantem o loop.
        	valido = false;
        	printf("\nCpf invalido. Motivos: ou o cpf ja esta cadastrado no nosso sistema ou o cpf nao e valido pelo modulo 11");
		}
	}while(!valido); //ele faz enquando o cpf nao for valido ou o cpf for encontrado no arquivo.
}

void UpperCase(char palavra[]){ //funcao genérica utilizada pra por uma string em maiusculo.
    int v;
    for(v = 0; v < strlen(palavra); v++){
        palavra[v] = toupper(palavra[v]);
    }
}

void LeDatasGenerico(char DDMMYYYY[]){ //Função genérica para ler valores relacionados à data.
	int dia, mes, ano;
	printf("\nInforme o ano: "); //Para fins de um algoritmo simplificado, pede-se o ano primeiro
	scanf("%d", &ano);
	while (ano < 1890 || ano > 2023) { //até no ano atual.
	    printf("\nInvalido! Informe o ano(1890 - 2023): ");
	    scanf("%d", &ano);
	}
	printf("\nInforme o mes: ");
	scanf("%d", &mes);
	while (mes > 12 || mes < 1) {
	    printf("\nInvalido! Informe o mes: ");
	    scanf("%d", &mes);
	}
	printf("\nInforme o dia: ");
	scanf("%d", &dia);
	switch(mes){
		case 4:
		case 6:
		case 9:
		case 11: //cases relacionados a meses com, no máximo, 30 dias
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
		case 12: //cases relacionados a meses com, no máximo, 31 dias.
			while (dia > 31 || dia < 1) {
	            printf("\nDia invalido para o mes %d. Informe um dia valido: ", mes);
	            scanf("%d", &dia);
	        }
		break;
		case 2: //mês fevereiro tem duas opções de dias, sendo considerado um ano bissexto ou nao.
			if (ano % 400 == 0 || (ano % 4 == 0 && ano % 100 != 0)) { //Condição de ano bissexto
		        while (dia > 29 || dia < 1) {
		            printf("\nDia invalido para o mes %d. Informe um dia valido: ", mes);
		            scanf("%d", &dia);
		        }
		    } 
			else { //condição !ano bissexto, (negado hehe)
		        while (dia > 28 || dia < 1) {
		            printf("\nO ano nao e bissexto! Dia invalido. Informe um dia valido: ");
		            scanf("%d", &dia);
		        }
		    }
		break;
	}
	sprintf(DDMMYYYY, "%02d/%02d/%04d", dia, mes, ano); //atribui, via sprintf, a data à string passada por parâmetro, que é um vetor de char.
}
void LeValorAc(char VALOR_CLIENT[]){ //função para ler o valor acumulado
	float valor;
	printf("\nInforme o seu valor acumulado: ");
	scanf("%f", &valor);
	while(valor < 0.0){
		printf("\nInforme o seu valor acumulado: ");
		scanf("%f", &valor);
	}
	sprintf(VALOR_CLIENT, "%.2f", valor); //atribui ao valor acumulado (em string) via sprintf.
}
int ExtrairComponenteData(char Data[], int posicaoInicial) {
    int valorComponente;
    valorComponente = (int)atoi(Data + posicaoInicial);
    return valorComponente;
}
void CadastraCliente(dados *cliente, FILE *arquivo_db){
	getchar();
	printf("\nInforme o seu nome: ");
	LeStringCadastro(cliente->nome, 30); //Funcao generica de leitura de strings
	system("cls||clear");
	printf("\n%s, Informe o nome da sua rua e o numero. Caso nao haja numero de residencia, deixar em branco: ", cliente->nome);
	LeStringCadastro(cliente->rua, 35);
	system("cls||clear");
	LeCpfClientes(cliente->cpf, arquivo_db);
	system("cls||clear");
	printf("\nInforme o nome do seu bairro: ");
	LeStringCadastro(cliente->bairro, 30);
	system("cls||clear");
	UpperCase(cliente->bairro);
	printf("\nAbaixo, informe a sua data de nascimento valida para cadastro.");
	LeDatasGenerico(cliente->data_nasc);
	while(ExtrairComponenteData(cliente->data_nasc, 6) > 2022){ //Nao e permitirdo cadastros de pessoas com menos de 1,5 ano.
		printf("\nInvalido. Informe a sua data de nascimento novamente abaixo");
		LeDatasGenerico(cliente->data_nasc);
	}
	printf("\nAbaixo, Informe a data da sua ultima compra, ultima atualizacao: 05/2023");
	LeDatasGenerico(cliente->data_compra);
	while(ExtrairComponenteData(cliente->data_compra, 6) <= ExtrairComponenteData(cliente->data_nasc, 6) || (ExtrairComponenteData(cliente->data_compra, 6) == 2023 && ExtrairComponenteData(cliente->data_compra, 3) > 5)){
		printf("\nNao e possivel uma data de compra anterior a data de nascimento\nTambem nao e possivel uma data de compra posterior ao 05/2023\nInforme uma data de compra valida: ");
		LeDatasGenerico(cliente->data_compra);
	}
	strcat(cliente->data_compra, "#"); //digito verificador, o que ajuda a diferenciar a data de compra pela de nascimento na hora de ler o case 2
	LeValorAc(cliente->valor_acumulado);
	system("cls||clear");
}
void ContaPessoasBairro(char bairroBusca[], FILE *arqv){
	char *FileLine, *SplitLine; 
	int contaBairros = 0;
	FileLine = (char*)malloc(250 * sizeof(char));
	if(FileLine != NULL){
		while(fgets(FileLine, 250, arqv) != NULL){ //atribui linha a linha do arquivo à string FileLine
			SplitLine = strtok(FileLine, ","); //SUBDIVIDE a string linha do arquivo entre as ocorrencias de , para comparar a quantidade de bairros digitado para busca no arquivo
			while(SplitLine != NULL){ //caso chegue no final da string, um ponteiro retorna null
				if(strcmp(SplitLine, bairroBusca) == 0){ //se o bairro está em alguma substring, conta. A fim de nao ter erros, usa-se um digito diferenciados '.'
					contaBairros++;
				}
				SplitLine = strtok(NULL, ","); //ponteiro aponta para a proxima substring divida pelo ,
			}
		}
	}
	else{
		printf("\nHouve um problema de memoria!");
	}
	printf("\nHa %d clientes morando no bairro %s", contaBairros, bairroBusca);
	rewind(arqv); //reposiciona ponteiro do arquivo para o começo
}
void BuscaData(char date[], FILE *ArquivoGeral){
	char *linha; //mesma lógica da funcao do contabairros(), em que pega linha a linha do arquivo
	bool ComprouNaData = false; //caso nao haja um comprador na data informada
	int j;
	linha = (char*)malloc(250 * sizeof(char));
	if(linha != NULL){
		while(fgets(linha, 250, ArquivoGeral) != NULL){
			if(strstr(linha, date) != NULL){ //por ter digito verificador '#', verifica se a substring data de busca está em alguma linha do arquivo
				ComprouNaData = true;
				printf("\nComprou na data informada o seguinte cliente -> ");
				for(j = 0; linha[j] != '*'; j++){ //caso sim, printa apenas até o endereco, usando um digito de paarada nas linhas do arquivo, ''
					printf("%c", linha[j]);
				}
			}
		}
	}
	else{
		printf("\nHouve um problema de memoria");
	}
	rewind(ArquivoGeral);//reposiciona o ponteiro do arquivo
	if(!ComprouNaData){
		printf("\nNenhum cliente comprou na data informada");
	}
}
void valorMAXac(FILE *arquivoTOTAL) {
	char *token, *al, *char_aux;
	float max = 0.0, atual;
	int count_generic, h;
	if((al = (char*)malloc(250 * sizeof(char))) != NULL && (char_aux = (char*)malloc(30 * sizeof(char))) != NULL){//aloca duas variaveis locais, para usar para verificar qual o cliente  com maior valor acumukaldo
		while(fgets(al, 250, arquivoTOTAL) != NULL){ //le linha a linha do arquivo, a cada loop
			count_generic = 0; //como a string é divida em duas e eu só quero a segunda parte, uso um contador.
			token = strtok(al, ";"); //divido a linha do arquivo em duas strings, uma com o valor acumulado e outra com o resto
			while(token != NULL){
				if(count_generic > 0){
					atual = (float)atof(token); //atribuo a string para um float para haver comparações
					if(atual > max){
						max = atual; //pega o maior valor acumulado
					}
				}
				token = strtok(NULL, ";");
				count_generic++;
			}
		}
		count_generic = 0;
		sprintf(char_aux, "%.2f", max); //o valor maximo e atribuido a uma string
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
bool VerificaArquivo(FILE *file_db){
	fseek(file_db, 0, SEEK_END);  //poe o ponteiro do arquivo no fim
	int TAM_ARQ = ftell(file_db); //com o ponteiro no fim, verifica se o fim é igual a posição 0 (inicial)
	bool vazio = false; 
	if(TAM_ARQ == 0){ // se final == inicial, retorna true
		vazio = true;
	}
	rewind(file_db); //reposiciona o ponteiro do arquivo
	return vazio;
}
int main(){
	FILE *arquivo; //arquivo usado para armazenar os dados
	dados db_clients; // variável do tipo da struct
	int opcao;
	char bairros_busca[30], data_busca[20], url[] = "Cadastro-clientes.txt"; //url é uma variável para a abertura do arquivo
	do{
		opcao = MenuOption(); // atribui o valor da opcao 
		system("cls||clear"); 
		switch(opcao){
			case 1: 
				arquivo = fopen(url, "a+"); //abre o arquivo na função de append, ou seja, "concatenando" mais informaççoes sem reiniciar o arquivo
				if(arquivo){ //verifica se o arquivo pode abrir
					CadastraCliente(&db_clients, arquivo); // função que cadastra todos os dados do cliente
					fprintf(arquivo, "%s,%s, End: %s*,%s., data de nascimento: %s, data de compra: %s;%s\n", db_clients.nome, db_clients.cpf, db_clients.rua, db_clients.bairro, db_clients.data_nasc, db_clients.data_compra, db_clients.valor_acumulado);
	       			fclose(arquivo); // o f printf é usado para armazenar todos os valores no arquivo, com sintaxe (FILE *arquivo, "atributos", strings que vão ao arquivo)
				}
				else{
					printf("\nNao foi possivel abrir o arquivo!");
				}
			break;
			case 2:
			    arquivo = fopen(url, "r");
			    if(arquivo){
			    	if(!VerificaArquivo(arquivo)){
	    				printf("\nInforme a data de compra que deseja buscar: ");
	    				LeDatasGenerico(data_busca);
	    				strcat(data_busca, "#"); //para diferenciar data de nasc pela de compra, usae-se esse digito auxiiar de localização no arquivo
	    				BuscaData(data_busca, arquivo); //busca a data em uma função genérica
	    				fclose(arquivo);
	    			}
	    			else{
	    				printf("\nHa um arquivo mas nao ha clientes cadastrados");
					}
			    }
			    else{
			        printf("\nArquivo nao foi iniciado"); // abrir em read só acontece se ja existir o arquivo!
			    }
			break;
			case 3:
				getchar();
				arquivo = fopen(url, "r");
				if(arquivo){
					if(!VerificaArquivo(arquivo)){
						printf("\nInforme o bairro que deseja buscar: ");
						LeStringCadastro(bairros_busca, 30); // variável para busca no arquivo!
						UpperCase(bairros_busca); //põe o bairro em uppercase
						strcat(bairros_busca, "."); // concatena um digito verificador 
						ContaPessoasBairro(bairros_busca, arquivo); //Função genérica para encontrar clientes que moram em um bairro e contar
						fclose(arquivo);
					}
					else{
	    				printf("\nHa um arquivo mas nao ha clientes cadastrados");
					}
				}
				else{
					printf("\nArquivo nao foi iniciado");
				}
			break;
			case 4:
			    arquivo = fopen(url, "r");
			    if(arquivo){
			    	if(!VerificaArquivo(arquivo)){
			    		valorMAXac(arquivo); //Função que utiliza técnica de tokens em uma string de linha de arquivo para pegar os valores acumulados
			    		fclose(arquivo);
					}
					else{
	    				printf("\nHa um arquivo mas nao ha clientes cadastrados");
					}
			    }
			    else{
			        printf("\nArquivo nao foi iniciado");
			    }
			break;
			case 5:
				printf("\nPrograma finalizado e os seus clientes foram armazenados no seu arquivo!"); //finaliza o programa
			break;
		}
	}while(opcao != 5);
	return 0;
}
