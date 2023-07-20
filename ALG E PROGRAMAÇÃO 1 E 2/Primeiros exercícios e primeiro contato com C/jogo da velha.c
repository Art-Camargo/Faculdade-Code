#include <stdio.h>
#include <ctype.h>
#define TAM 3
#define FALSE 0
#define TRUE 1
main()
{
	char jogo[TAM][TAM];
	int i, j, fim = FALSE, linha, coluna, count=0, continua = FALSE;
	for(i=0; i<TAM; i++){
		for(j=0; j<TAM; j++){
			jogo[i][j] = ' ';
		}
	}
	do
	{
		do
		{
			for(i=0; i<TAM; i++){
				for(j=0; j<TAM; j++){
					if(j == 0){
						if(i == 0){
							printf("\n\n");
						}
						printf("             ");
						printf("| ");
					}
					printf("%c | ", jogo[i][j]);
				}
				printf("\n");
			}
	
			if(count == 9){
				printf("\nJOGO ACABOU!!!");
				fim = TRUE;
			}
			else{
				printf("\nINFORME A LINHA QUE VC QUER JOGAR: ");
				scanf("%d", &linha);
				printf("\nINFORME A COLUNA QUE VC QUER JOGAR: ");
				scanf("%d", &coluna);
				while(jogo[linha][coluna] == 'X' || jogo[linha][coluna] == 'O'){
					printf("\nINFORME A LINHA QUE VC QUER JOGAR: ");
					scanf("%d", &linha);
					printf("\nINFORME A COLUNA QUE VC QUER JOGAR: ");
					scanf("%d", &coluna);
				}
				if(count%2 == 0){
					jogo[linha][coluna] = 'X';
				}
				else{
					jogo[linha][coluna] = 'O';
				}
			}
		
			count++;
			for(i=0; i<TAM; i++){
				for(j=0; j<TAM; j++){
					if(i == 0){
						if((jogo[i][j] == 'X' && jogo[i + 1][j] == 'X' && jogo[i + 2][j] == 'X') || (jogo[i][j] == 'O' && jogo[i + 1][j] == 'O' && jogo[i + 2][j] == 'O')){
							fim = TRUE;
							printf("\nTEMOS UM VENCEDOR !!!!!!!!!!!!");
							printf("\nO VENCEDOR FOI O JOGADOR DA LETRA ==== %c", jogo[linha][coluna]);
						}
					}
					if(j == 0){
						if((jogo[i][j] == 'X' && jogo[i][j + 1] == 'X' && jogo[i][j + 2] == 'X') || (jogo[i][j] == 'O' && jogo[i][j + 1] == 'O' && jogo[i][j + 2] == 'O')){
							fim = TRUE;
							printf("\nTEMOS UM VENCEDOR !!!!!!!!!!!!");
							printf("\nO VENCEDOR FOI O JOGADOR DA LETRA ==== %c", jogo[linha][coluna]);
						}
					}
					if(j == i){
						if((jogo[i][j] == 'X' && jogo[i + 1][j + 1] == 'X' && jogo[i + 2][j + 2] == 'X') || (jogo[i][j] == 'O' && jogo[i + 1][j + 1] == 'O' && jogo[i + 2][j + 2] == 'O')){
							fim = TRUE;
							printf("\nTEMOS UM VENCEDOR !!!!!!!!!!!!");
							printf("\nO VENCEDOR FOI O JOGADOR DA LETRA ==== %c", jogo[linha][coluna]);
						}
					}
				}
			}
		}while(fim == FALSE);
		count = 0;
		for(i=0; i<TAM; i++){
			for(j=0; j<TAM; j++){
				if(j == 0){
					if(i == 0){
						printf("\n\n");
					}
					printf("             ");
					printf("| ");
				}
				printf("%c | ", jogo[i][j]);
			}
			printf("\n");
		}
		printf("\n\nVC QUER CONTINUAR JOGANDO????");
		printf("\n0---SIM");
		printf("\n1---NAO: ");
		scanf("%d", &continua);
		while(continua > 1 || continua < 0){
			printf("\nVC QUER CONTINUAR JOGANDO????");
			printf("\n0---SIM ");
			printf("\n1---NAO: ");
			scanf("%d", &continua);
		}
		fim = FALSE;
		if(continua == 0){
			for(i=0; i<TAM; i++){
				for(j=0; j<TAM; j++){
					jogo[i][j] = ' ';
				}
			}	
		}
	}while(continua == FALSE);
}
