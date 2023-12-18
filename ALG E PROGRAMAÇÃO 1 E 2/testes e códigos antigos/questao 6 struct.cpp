#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct info{
	char compromisso[100];
	int ano, mes;
}agenda;

void LeData(int *year, int* month){
	system("cls||clear");
	printf("\nInforme o mes do compromisso: ");
	scanf("%d", &(*month));
	while(*month > 12 || *month < 0){
		printf("\nInvalido. Informe o mes do compromisso: ");
		scanf("%d", &(*month));
	}
	
	printf("\nInforme o ano do compromisso: ");
	scanf("%d", &(*year));
	while(*year < 2022){
		printf("\nInvalido. Informe o ano do compromisso: ");
		scanf("%d", &(*year));
	}
}
void LeCompromissos(agenda preencher[]){
	int i;
	for(i = 0; i < 5; i++){
		printf("\nInforme um compromisso: ");
		fgets(preencher[i].compromisso, 100, stdin);
		fflush(stdin);
		preencher[i].compromisso[strcspn(preencher[i].compromisso, "\n")] = '\0';
		
		do{

			LeData(&preencher[i].ano, &preencher[i].mes);
			system("cls||clear");
		}while(preencher[i].mes == 0);
		getchar();
	}
}

void PrintaCompromissos(agenda comp[]){
	int j, mes2, ano2;
	do{
		printf("\nPara buscar algum compromisso, digita o mes e o ano: ");
		LeData(&ano2, &mes2);
		if(ano2 == comp[j].ano && mes2 == comp[j].mes){
			puts(comp[j].compromisso);
			printf("\n");
		}
	}while(mes2 != 0);
}

int main(){
	agenda marcados[5];
	LeCompromissos(marcados);
	PrintaCompromissos(marcados);
	return 0;	
 }
