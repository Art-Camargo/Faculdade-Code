#include <stdio.h>
#include <stdlib.h>
int menuOption() {
	int value;
	printf("\n1 - Cadastrar tecido");
	printf("\n2 - Remover tecido");
	printf("\n3 - quantidade de rolos estocados por tipo");
	printf("\n4 - tipos de tecido sem estoque");
	printf("\n5 - quantidade total de rolos de tecido estocados");
	printf("\n6 - QUANTIDADE em metros quadrados estocados");
	printf("\n7 - FIM");
	printf("\nEscolha uma opcao acima: ");
	scanf("%d", &value);
	while(value > 7 || value < 1) {
		printf("\nInvalido. Escolha uma opcao acima: ");
		scanf("%d", &value);
	}
	return value;
}
int generico_tipo() {
	int tipo_generico;
	printf("\nQual tipo voce deseja: ");
	scanf("%d", &tipo_generico);
	while(tipo_generico > 3 || tipo_generico < 1) {
		printf("\nInvalido. Qual tipo voce deseja: ");
		scanf("%d", &tipo_generico);
	}
	return tipo_generico;
}
void CadastraTecido(int clienteAtual, int tipos[], int qtd_est[]) { //case 1
	int k;
	for(k = 4; k >= 0; k--) {
		if(!tipos[k]) {
			clienteAtual = k;
		}
	}
	if(clienteAtual > 4) {
		printf("\nO Estoque esta cheio!");
	}
	else {
		printf("\nInforme o tipo do seu tecido do produto %d: ", clienteAtual);
		tipos[clienteAtual] = generico_tipo();
		
		printf("\nInforme a quantidade de rolos de tecido do produto %d: ", clienteAtual);
		scanf("%d", &qtd_est[clienteAtual]);
		while(qtd_est[clienteAtual] < 0) {
			printf("\nInvalido. Informe a quantidade de rolos de tecido do produto %d: ", clienteAtual);
			scanf("%d", &qtd_est[clienteAtual]);
		}
	}
}
void removerTecido(int type[], int qtd[]) { //case 2
	int indexRemove;
	printf("\nInforme o codigo do produto que deseja remover: ");
	scanf("%d", &indexRemove);
	while(indexRemove > 4 || indexRemove < 0) {
		printf("\nInvalido. Informe o codigo do produto que deseja remover: ");
		scanf("%d", &indexRemove);
	}	
	if(!type[indexRemove]) {
		printf("\nProduto ainda nao cadastrado!");
	}
	else {
		type[indexRemove] = 0;
		qtd[indexRemove] = 0;
	}
}
int qtd_tipo(int qtd_estocada[], int tiposTec[]) { //case 3
	int op, count = 0, i;	
	op = generico_tipo();
	for(i = 0; i < 5; i++) {
		if(tiposTec[i] == op) {
			count += qtd_estocada[i];
		}
	}
	return count;
} 
void conta_sem_estoque(int qtd_rolos[], int tipos_rolos[], int index, int *count_aux) { //case 4
	int j, aux = 0;
	for(j = 0; j < 5; j++) {
		if(tipos_rolos[j] == index) {
			aux += qtd_rolos[j];
		}
	}
	if(aux == 0) { //lembrar de zerar o count_aux no main no case a cada chamada e passar o indice um a um
		printf("\n O tipo %d nao possui estoque!", index);
		*count_aux += 1;
	}
}
int qtd_total(int qtd_total[]) { //case 5
	int v, total = 0;
	for(v = 0; v < 5; v++) {
		total += qtd_total[v];
	}
	return total;
}
int total_metrosq(int qtd_metros[], int tiposTEC[]) { //case 6
	int h, total_metros = 0;
	for(h = 0; h < 5; h++) {
		if(tiposTEC[h] == 1) {
			total_metros += qtd_metros[h] * 5;
		} 
		else if(tiposTEC[h] == 2) {
			total_metros += qtd_metros[h] * 10;
		}
		else {
			total_metros += qtd_metros[h] * 6;
		}
	}	
	return total_metros;
}
void printa_tudo(int Type_tec[], int qtd_tec[]) {
	int y;
	printf("\nCodigo         tipo         quantidade");
	for(y = 0; y < 5; y ++) {
		if(Type_tec[y] == 0) {
			printf("\n  %d              -                 -", y);
		}
		else {
			printf("\n  %d              %d                %d", y, Type_tec[y], qtd_tec[y]);
		}
	}
}
int main() {
	int qtd_TIPOS, aux_count;
	int opcao, produtoAtual = 0, TIPOS[] = {0, 0, 0, 0, 0}, QTD[] = {0, 0, 0, 0, 0};
	do {
		opcao = menuOption();
		system("cls||clear");
		switch(opcao) {
			case 1:
				CadastraTecido(produtoAtual, TIPOS, QTD);
				produtoAtual++;
			break;
			case 2:
				removerTecido(TIPOS, QTD);
			break;
			case 3:
				qtd_TIPOS = qtd_tipo(QTD, TIPOS);
				printf("\nTotal do tipo escolhido = %d", qtd_TIPOS);
			break;
			case 4:
				aux_count = 0;
				conta_sem_estoque(QTD, TIPOS, 1, &aux_count);
				conta_sem_estoque(QTD, TIPOS, 2, &aux_count);
				conta_sem_estoque(QTD, TIPOS, 3, &aux_count);
				if(aux_count == 0) {
					printf("\nTodos os tipos estao cadastrados!");
				}
			break;
			case 5:
				printf("\nHa %d de metais cadastrados", qtd_total(QTD));
			break;
			case 6:
				printf("\nHa %d de metros quadrados armazenados", total_metrosq(QTD, TIPOS));
			break;
			case 7:
				printf("\nPrograma finalizado!");
			break;
		}
		printa_tudo(TIPOS, QTD);
	}while(opcao != 7); 
	return 0;
}
