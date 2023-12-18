#include <stdio.h>
#include <stdlib.h>
#define colum 7
#define line 6
void PrintaJogo(int game[line][colum]){
	int i, j;
	for(i = 0; i < line; i++){
		for(j = 0; j < colum; j++){
			printf("%d   ", game[i][j]);
		}
		printf("\n");
	}
}
int ValidaColunaCheia(int gamezinho[line][colum], int col){
	int count = 0, valido = 1;
	if(gamezinho[0][col] != 0){
		printf("\nEssa coluna ja esta cheia!!!!!");
		valido = 0;
	}
	return valido;
}
void AlocaJogadaTabela(int matriz[line][colum], int jogadorAtual, int colu){
	int x, OnlyPlay = 0;
	for(x = line - 1; x >= 0; x--){
		if(matriz[x][colu] == 0 && OnlyPlay == 0){
			matriz[x][colu] = jogadorAtual;
			OnlyPlay++;
		}
	}
}
int TestaEmpate(int mat[line][colum]){
	int k, r, empate = 1, contador = 0;
	for(k = 0; k < line; k++){
		for(r = 0; r < colum; r++){
			if(mat[k][r] == 0){
				return 0;
			}
		}
	}	
	return 1;
}
int GanhouLinha(int jog[line][colum], int player){
	int u, h;
	for(u = 0; u < line; u++){
		for(h = 0; h < colum; h++){
			if(h <= 3 && jog[u][h] == 1 && jog[u][h + 1] == 1 && jog[u][h + 2] == 1 && jog[u][h + 3] == 1){
				printf("\nO jogador %d ganhou!", player);
				return 1;
			}
			if(h <= 3 && jog[u][h] == 2 && jog[u][h + 1] == 2 && jog[u][h + 2] == 2 && jog[u][h + 3] == 2){
				printf("\nO jogador %d ganhou!", player);
				return 1;
			}
		}
	}
	return 0;
}
void zeraTabela(int gam[line][colum]){
	int v, w;
	for(v = 0; v < line; v++){
		for(w = 0; w < colum; w++){
			gam[v][w] = 0;
		}
	}
}

int main(){
	int jogo[line][colum], gamer = 1, coluna, jogada = 0, continua, empatou, fim;
	do {
		zeraTabela(jogo);
		do {
			continua = 1;
			PrintaJogo(jogo);
			printf("\nJogador %d, digite uma coluna para jogar (0 - 6): ", gamer);
			scanf("%d", &coluna);
			while(coluna > 6 || coluna < 0|| !ValidaColunaCheia(jogo, coluna)){
				printf("\nJogador %d, digite uma coluna valida para jogar (0 - 6): ", gamer);
				scanf("%d", &coluna);
			}
			AlocaJogadaTabela(jogo, gamer, coluna);
			continua = !GanhouLinha(jogo, gamer);//retorna 0 se ganha na linha 
			if(continua == 1){
				empatou = !TestaEmpate(jogo);
			}
			jogada++;
			if(jogada %2 == 0){
				gamer = 1;
			}
			else{
				gamer = 2;
			}
		} while(continua == 1 || empatou == 0);	
		do {
			printf("\n\n1 --- FIM");
			printf("\n0 --- FIM");
			printf("\nEscolha uma opcao: ");
			scanf("%d", &fim);
		}while(fim > 1 || fim < 0);
	}while(fim == 1);
	return 0;
}

