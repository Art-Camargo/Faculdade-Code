#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct informacoes {
	float nota1, nota2, nota3, media;
	char nome[70];
}db; //db == data base (banco de dados)

float Notas(int numProva, char name[]) { 
	float num;
	printf("\nInforme a nota da prova %d do aluno %s: ", numProva, name);
	scanf("%f", &num);
	while(num > 10.00 || num < 0.00) {
		system("cls||clear");
		printf("\nInvalido. Informe a nota da prova %d do aluno %s: ", numProva, name);
		scanf("%f", &num);
	}
	return num;
}
void CadastraNotas(FILE *arq, db *aluno) {
	char url[] = "Todas-Notas.txt";
	arq = fopen(url, "a+");
	if(arq) {
		printf("\nInforme o seu nome: ");
		fgets(aluno->nome, 70, stdin);
		fflush(stdin);
		aluno->nome[strcspn(aluno->nome, "\n")] = '\0';
		aluno->nota1 = Notas(1, aluno->nome);
		aluno->nota2 = Notas(2, aluno->nome);
		aluno->nota3 = Notas(3, aluno->nome);
		getchar();
		aluno->media = (aluno->nota1 + aluno->nota2 + aluno->nota3) / 3;
		fprintf(arq, "%s,%.2f,%.2f,%.2f,%.2f\n", aluno->nome, aluno->nota1, aluno->nota2, aluno->nota3, aluno->media);
		fclose(arq);
		system("cls||clear");
	}
	else {
		printf("\nNao foi possivel abrir o arquivo");
	}
}

void PrintaReprovados(FILE *database, db *turma) {
	char link[] = "Todas-Notas.txt", *token, line[100];
	database = fopen(link, "r");
	int opcao;
	if(database) {
		while(fgets(line, 100, database) != NULL){
		    opcao = 0;
		    token = strtok(line, ",");
		    while(token != NULL) {
		        switch(opcao) {
		            case 0:
		                strcpy(turma->nome, token);
		            break;
		            case 1:
		                turma->nota1 = (float)atof(token);
		            break;
		            case 2:
		                turma->nota2 = (float)atof(token);
		            break;
		            case 3:
		                turma->nota3 = (float)atof(token);
		            break;
		            case 4:
		                turma->media = (float)atof(token);
		            break;
		        }
		        opcao++;
		        token = strtok(NULL, ",");
		    }
		    if(turma->media >= 6) {
		        printf("\n%s aprovado", turma->nome);
		    }
		    else {
		        printf("\n%s reprovado", turma->nome);
		    }
		} 
		fclose(database);
	}
	else {
		printf("\nNao foi possivel abrir o arquivo");
	}
}

int main() {
	FILE *arquivo;
	db alunos;
	int continua;
	do {
		CadastraNotas(arquivo, &alunos);
		printf("\nDeseja adicionar notas de outros alunos?");
		printf("\n1 - Sim");
		printf("\n2 - Nao");
		printf("\nEscolha uma opcao acima: ");
		scanf("%d", &continua);
		while(continua > 2 || continua < 1){
			printf("\nInvalido. Informe uma opcao valida: ");
			scanf("%d", &continua);
		}
		getchar();
	} while(continua == 1);
	PrintaReprovados(arquivo, &alunos);
	return 0;
}
