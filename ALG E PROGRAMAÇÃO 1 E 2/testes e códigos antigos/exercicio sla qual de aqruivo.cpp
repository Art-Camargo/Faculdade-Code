#include <stdio.h>
#include <string.h>
#include <ctype.h>
typedef struct dados{
	char code[3], name[30];	
}db;
void LeDadosArq(FILE *arquivoF, char nome[], char codigo[]){
	bool erro;
	int j;
	printf("\nInforme o seu nome, sem numeros aqui: ");
	fgets(nome, 30, stdin);
	nome[strcspn(nome, "\n")] = '\0';
	fflush(stdin);
	printf("\nInforme o seu codigo, apenas digitos: ");
	fgets(codigo, 3, stdin);
	codigo[strcspn(codigo, "\n")] = '\0';
	fprintf(arquivoF, "%s,%s\n", nome, codigo);
}
int main(){
	FILE *arquivo;
	db dados_pessoas;
	int num = 0;
	char url[] = "Progama-1.txt";
	arquivo = fopen(url, "a+");
	if(arquivo){
		do{
			LeDadosArq(arquivo, dados_pessoas.name, dados_pessoas.code);
			num++;
		}while (num < 6);
		fclose(arquivo);
	}
	else{
		printf("\nErro ao abrir o arquivo");
	}
	return 0;
}
