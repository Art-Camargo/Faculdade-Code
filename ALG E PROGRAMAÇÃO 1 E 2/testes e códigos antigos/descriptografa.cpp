#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void descriptografa_mensagem(char msg_cript[]) {
	int i;
	for(i = 0; i < strlen(msg_cript); i++) {
		msg_cript[i] = msg_cript[i] - 3;
	}
}



int main() {
	FILE *arquivo;
	char mensag[250];
	arquivo = fopen("mensagem-cripto.txt", "r");
	if(arquivo) {
		fgets(mensag, 250, arquivo);
		descriptografa_mensagem(mensag);
		printf("\nMensagem descriptografada: %s", mensag);
		rewind(arquivo);
	}
	else {
		printf("\nNao foi possivel abrir o arquivo");
	}
	printf("\nPrograma finalizado!!!!!!!");
	return 0;
}
