#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct notas {
	float nota;
	char nomes[50];
}db_alunos;

void LeNotasAlunos(db_alunos discente[], int qtd, FILE *arq, char url[]) {
	int i;
	arq = fopen(url, "a+");
	if(arq) {
		for(i = 0; i < qtd; i++) {
			printf("\nInforme o seu nome: ");
			fgets(discente[i].nomes, 50, stdin);
			fflush(stdin);
			discente[i].nomes[strcspn(discente[i].nomes, "\n")] = '\0';
			printf("\nInforme a nota do aluno %s: ", discente[i].nomes);
			scanf("%f", &discente[i].nota);
			while(discente[i].nota < 0.0 || discente[i].nota > 10.00) {
				printf("\nInvalido. Informe a nota do aluno %s: ", discente[i].nomes);
				scanf("%f", &discente[i].nota);
			}
			fprintf(arq, "%s,%.2f\n", discente[i].nomes, discente[i].nota);
			getchar();
		}
		fclose(arq);
	}
	else {
		printf("\nNao foi possivel abrir o arquivo!");
	}
}

void printaReprovado(db_alunos NotasAlunos[], int qtd_notas, FILE *arqv_db, char urlOPEN[]) {
	char linha_arquivo[100], *split, count = 0;
	
}

int main(){
	db_alunos *alunos;
	FILE *arquivo;
	int qtd_alunos;
	char extensao[] = "Notas-Alunos.txt";
	printf("\nInforme quantos alunos possui a turma: ");
	scanf("%d", &qtd_alunos);
	while(qtd_alunos < 1) {
		printf("\nInvalido. Informe quantos alunos possui a turma: ");
		scanf("%d", &qtd_alunos);
	}
	getchar();
	alunos = (db_alunos*)malloc(qtd_alunos * sizeof(db_alunos));
	LeNotasAlunos(alunos, qtd_alunos, arquivo, extensao);
	printaReprovado(alunos, qtd_alunos, arquivo, extensao);
	return 0;	
}
