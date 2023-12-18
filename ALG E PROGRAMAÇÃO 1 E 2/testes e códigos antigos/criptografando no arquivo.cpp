#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void criptografa_mensagem(char msg_cript[]) {
	int i;
	for(i = 0; i < strlen(msg_cript); i++) {
		msg_cript[i] = msg_cript[i] + 3;
	}
}

void le_mensagem(FILE *arq, char msg[]) {
	char url[] = "mensagem-cripto.txt";
	printf("\nDigite uma mensagem para ser adicionada ao arquivo: ");
	fgets(msg, 250, stdin);
	fflush(stdin);
	criptografa_mensagem(msg);
	arq = fopen(url, "a+");
	if(arq) {
		fprintf(arq, "%s\n", msg);
		fclose(arq);
	}
	else {
		printf("\nNao foi possivel criar o arquivo!");
	}
}

int main() {
	FILE *arquivo;
	char mensagem[250];
	le_mensagem(arquivo, mensagem);
	printf("\nPrograma finalizado!!!!!!!");
	return 0;
}
