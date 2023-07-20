//CRITOGRAFA VOGAIS EM ASTERISCOS, CONSOANTES R, S e T SAO '#'; LETRAS COMO D, F, G, H SAO '@'; as demais, iguais;
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define TAM 80
main()
{
	char frase[TAM], frasee[TAM], i;
	int senha, autenticacao;
	printf("\nDIGITE UMA FRASE: ");
	gets(frase);
	printf("\nQUAL A SENHA DE ACESSO? (NUMEROS INTEIROS DE N DIGITOS)");
	scanf("%d", &senha);
	for(i=0; i<strlen(frase); i++){
		frasee[i] = frase[i];
		frase[i] = toupper(frase[i]);
		
	}
	for(i=0; i<strlen(frase); i++){
		if(frase[i] == 'R' || frase[i] == 'S' || frase[i] == 'T'){
			frase[i] = '#';
		}
		else{
			if(frase[i] == 'D' || frase[i] == 'F' || frase[i] == 'G' || frase[i] == 'H'){
				frase[i] = '@';
			}
			else{
					if(frase[i] == 'A' || frase[i] == 'E' || frase[i] == 'I' || frase[i] == 'O' || frase[i] == 'U'){
						frase[i] = '*';
					}
			}
		}
	}
	printf("\nFRASE CRIPTOGRAFADA ABAIXO!!!!\n\n");
	for(i=0; i<strlen(frase); i++){
		printf("%c", frase[i]);
	}
	printf("\nSE QUISER DESCRIPTOGRAFAER, DIGITE A SENHA: ");
	scanf("%d", &autenticacao);
	while(autenticacao != senha){
		printf("\nvoce errou a senha!!!!!!");
		printf("\nSE QUISER DESCRIPTOGRAFAER, DIGITE A SENHA CORRETAMENTE: ");
		scanf("%d", &autenticacao);
	}
	printf("\nFRASE DESCRIPTOGRAFADA ABAIXO!!!!!!!!!!!!!!!!!!!!!\n\n");
	for(i=0; i<strlen(frase); i++){
		if(frase[i] != frasee[i]){
			frase[i] = frasee[i];
		}
		printf("%c", frase[i]);
	}
}
