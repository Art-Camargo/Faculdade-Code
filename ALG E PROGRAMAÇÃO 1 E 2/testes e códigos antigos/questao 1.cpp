#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
typedef struct notas{
	float nota[3], media;
	char nome[50];
	int matricula;
}turma;

float LeNotasGenerico(char nome_atual[], int index){
	float notaF;
	system("cls||clear");
	printf("\nInforme a sua Nota da prova %d, %s: ", index, nome_atual);
	scanf("%f", &notaF);
	while(notaF < 0.0 || notaF > 10.0){
		printf("\nInvalido. Informe a sua Nota da prova %d, %s: ", index, nome_atual);
		scanf("%f", &notaF);
	}
	return notaF;
}

void CadastraNotasAlunos(turma alunos[]){
	int j;
	for(j = 0; j < 5; j ++){
		system("cls||clear");
		printf("\nInforme o seu nome: ");
		fgets(alunos[j].nome, 50, stdin);
		fflush(stdin);
		alunos[j].nome[strcspn(alunos[j].nome, "\n")] = '\0';
		
		alunos[j].nota[0] = LeNotasGenerico(alunos[j].nome, 1);
		alunos[j].nota[1] = LeNotasGenerico(alunos[j].nome, 2);
		alunos[j].nota[2] = LeNotasGenerico(alunos[j].nome, 3);
		
		alunos[j].media = (alunos[j].nota[0] + alunos[j].nota[1] + alunos[j].nota[2]) / 3;
		
		alunos[j].matricula = j * j;
		getchar();
	}
}

void MaxNota(turma notamax[]){
	int i, CountFirst = 0;
	float max;
	for(i = 0; i < 5; i++){
		if(i == 0){
			max = notamax[i].nota[0];
		}
		else if(notamax[i].nota[0] > max){
			max = notamax[i].nota[0];
		}
	}
	for(i = 0; i < 5; i++){
		if(notamax[i].nota[0] == max && CountFirst == 0){
			printf("\n%.2f foi a maior nota da primeira prova, alcancada por %s!", notamax[i].nota[0], notamax[i].nome);
		}
	}
}

void SearchMaiorMedia(turma aluninho[]){
	int k, count = 0;
	float maxMedia, minMedia;
	for(k = 0; k < 5; k++){
		if(k == 0){
			maxMedia = aluninho[k].media;
			minMedia = aluninho[k].media;
		}
		else if(aluninho[k].media > maxMedia){
			maxMedia = aluninho[k].media;
		}
		else if(aluninho[k].media < minMedia){
			minMedia = aluninho[k].media;
		}
	}
	for(k = 0; k < 5; k++){
		if(aluninho[k].media == maxMedia && count == 0){
			printf("\n\n%.2f foi a maior media geral da turma, alcancada por %s!", aluninho[k].media, aluninho[k].nome);
		}
	}
	for(k = 0, count = 0; k < 5; k++){
		if(aluninho[k].media == minMedia && count == 0){
			printf("\n\n%.2f foi a menor media geral da turma, alcancada por %s!", aluninho[k].media, aluninho[k].nome);
		}
	}
}

void ValidaReprovado(turma fulano[]){
	int y;
	for(y = 0; y < 5; y++){
		if(fulano[y].media < 6){
			printf("\nO aluno %s esta reprovado!", fulano[y].nome);
		}
		else{
			printf("\nO aluno %s esta aprovado!", fulano[y].nome);
		}
	}
}

int main(){
	turma cadastros[5];
	CadastraNotasAlunos(cadastros);
	system("cls||clear");
	MaxNota(cadastros);
	ValidaReprovado(cadastros);
	return 0;
}
