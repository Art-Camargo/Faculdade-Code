#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
typedef struct informacoes {
	char titulo[30], autor[15];
	int ano;
}livros;

void UpperCase(char texto[]) {
	int v;
	for(v = 0; v < strlen(texto); v++) {
		texto[v] = toupper(texto[v]);
	}
}

void le_dados(livros dados[]) {
	int i;
	for(i = 0; i < 5; i++) {
		printf("\nInforme o nome do seu livro: ");
		fgets(dados[i].titulo, 30, stdin);
		fflush(stdin);
		dados[i].titulo[strcspn(dados[i].titulo, "\n")] = '\0';
		UpperCase(dados[i].titulo);
				
		printf("\nInforme o nome do autor do livro %s: ", dados[i].titulo);
		fgets(dados[i].autor, 15, stdin);
		fflush(stdin);
		dados[i].autor[strcspn(dados[i].autor, "\n")] = '\0';
		
		printf("\nInforme o um ano de nascimento: ");
		scanf("%d", &dados[i].ano);
		while(dados[i].ano < 0) {
			printf("\nInvalido. Informe o um ano de nascimento: ");
			scanf("%d", &dados[i].ano);
		}
		getchar();
	}
}

void procura_titulo(livros db[]) {
	int j;
	char nome_livro[30];
	printf("\nInforme o nome do seu livro: ");
	fgets(nome_livro, 30, stdin);
	fflush(stdin);
	nome_livro[strcspn(nome_livro, "\n")] = '\0';
	UpperCase(nome_livro);
	for(j = 0; j < 5; j++) {
		if(strcmp(db[j].titulo, nome_livro) == 0) {
			printf("\nTITULO: %s", db[j].titulo);
			printf("\nAUTOR: %s", db[j].autor);
			printf("\nANO: %d", db[j].ano);
		}
	}
}

int main() {
	livros infos[5];
	le_dados(infos);
	procura_titulo(infos);
	return 0;
}
