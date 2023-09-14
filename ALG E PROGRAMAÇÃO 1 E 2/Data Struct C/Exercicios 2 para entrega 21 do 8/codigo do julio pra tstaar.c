// 5.	Uma pizzaria predBsa cadastrar produtos, clientes e fazer o controle de vendas. É predBso ter o cadastro de 

//produto-pizza (código, nome da pizza, preço)
//cliente (código, nome, endereço)
//venda (código da pizza e código do cliente, qtd de pizza, valor pago)

// Faça um menu para:  
//		Gravar dados das pizzas
//      Gravar dados dos clientes
//      Gravar venda
//      Ler dados das pizzas
//      Ler dados dos clientes
//      Ler vendas

// a.	Grave os dados em arquivos.
// b.	Faça a leitura dos arquivos
// c.	Ao final do dia, imprimir a quantidade de pizzas vendidas e o valor total recebido.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define RED "\x1b[91m"  //R
#define GRE "\x1b[92m"  //G
#define BLU "\x1b[90m"  //B
#define YLW "\x1b[93m"  //Y
#define MAG "\x1b[95m"  //M
#define CYN "\x1b[96m"  //C
#define STT "\x1b[9m"   //STRIKETHROUGH
#define CLR "\x1b[0m"

//nem predBsa de lista

void clearStdin() {
    int c = getchar();
    while (c != '\n') {
        c = getchar();
    }
}

//NEM sempre é bom limpar o buffer
void clearVerifier (char *string, long unsigned int size) {
    if (strlen(string) + 1 == size) {
        int c = getchar();
		while (c != '\n') { //do while c == n || c == EOF?
        c = getchar();
		}
    }
}

void clear() {
#ifdef _WIN32
  system("cls");
#endif
#ifdef linux
  system("clear");
#endif
}

// int fileContents (FILE *dB, char *filename) {
//     int times = -1; //don't consider header in the linecount
//     char  dBLine[170];
//     if((dB = fopen(filename, "r")) == NULL) {
//          printf(RED"ERR:"CLR" Falha na leitura do arquivo!\n");
//          return times;
//     } else {
//         while (fgets(dBLine, sizeof(dBLine), dB))
//             times++;
//         fclose(dB);
//         return times; // printf("\n\n%d\n\n", times);
//     }
// }

//produto-pizza (código, nome da pizza, preço)
void addPizza(FILE *dB) {
	bool fail = false;
	if((dB = fopen("PizzaDB/menuPizzaria.tsv", "r")) == NULL) {
        if((dB = fopen("PizzaDB/menuPizzaria.tsv", "w")) == NULL) { //essa função nunca deveria retornar null, mas tá..
            printf("The file cannot be created in this directory, please check that you have the necessary permissions and try again. Press ENTER to continue.");
            getchar();
            clearStdin();
            fail = true;
        } else {
            fprintf(dB, "Name\tPrice\n");
            fclose(dB); //fecha o arquivo, afinal, o objetivo era apenas criá-lo.
        }
    } if (!fail) {
		char name[50];
		float price;
		clear();
		printf("Insert a name for your new pizza flavour: ");
		fgets(name, sizeof(name), stdin);
		name[strcspn(name, "\n")] = '\0'; 
		clearVerifier(name, sizeof(name));
		printf("%s\t Price: ", name);
		scanf("%f", &price);
		clearStdin();
		dB = fopen("PizzaDB/menuPizzaria.tsv", "a+");
		fprintf(dB, "%s\t%.2f\n", name, price);
		fclose(dB);
	}
}

//cliente (código, nome, endereço)
void addClient(FILE *dB) {
	bool fail = false;
	if((dB = fopen("PizzaDB/clientContacts.tsv", "r")) == NULL) {
        if((dB = fopen("PizzaDB/clientContacts.tsv", "w")) == NULL) { //essa função nunca deveria retornar null, mas tá..
            printf("The file cannot be created in this directory, please check that you have the necessary permissions and try again. Press ENTER to continue.");
            getchar();
            clearStdin();
            fail = true;
        } else {
            fprintf(dB, "Name\tAddress\n");
            fclose(dB); //fecha o arquivo, afinal, o objetivo era apenas criá-lo.
        }
    } if (!fail) {
		char name[50], address[50];
		clear();
		printf("Insert a name for your new client's name: ");
		fgets(name, sizeof(name), stdin);
		name[strcspn(name, "\n")] = '\0';
		clearVerifier(name, sizeof(name));
		printf("Insert %s's address: ", name);
		fgets(address, sizeof(address), stdin);
		address[strcspn(address, "\n")] = '\0';
		clearVerifier(address, sizeof(address));
		dB = fopen("PizzaDB/clientContacts.tsv", "a+");
		fprintf(dB, "%s\t%s\n", name, address);
		fclose(dB);
	}
}

//venda (código da pizza e código do cliente, qtd de pizza, valor pago)
void recordSale(FILE *dB) {
	bool fail = false;
	if((dB = fopen("PizzaDB/salesRecord.tsv", "r")) == NULL) {
        printf("\nBK 4");
        if((dB = fopen("PizzaDB/salesRecord.tsv", "w")) == NULL) { //essa função nunca deveria retornar null, mas tá..
            printf("The file cannot be created in this directory, please check that you have the necessary permissions and try again. Press ENTER to continue.");
            getchar();
            clearStdin();
            fail = true;
            printf("\nBK 5");
        } else {
            fprintf(dB, "P Code\tC Code\tP Ammout\tC Paid\n");
            fclose(dB); //fecha o arquivo, afinal, o objetivo era apenas criá-lo.
        }
    } if (!fail) {
		int PCode, CCode, PAmmount, PCodeCounter = 0;
		long PPrice = 0;
		float CPaid;
		char dBLine[170], *token, *auxPPrice, *endptr;
    const char t[2] = "\t";
		clear();
		printf("Insert the Pizza code: "); //we don't need no validation...
		scanf("%d", &PCode);
		clearStdin();
		printf("Insert the Client code: "); //we don't need no thought control...
		scanf("%d", &CCode);
		clearStdin();
		printf("Insert the Pizza ammount: "); //no dark sarcasm in the classroom...
		scanf("%d", &PAmmount);	
		clearStdin();
    printf("\nBK 10");
		dB = fopen("PizzaDB/menuPizzaria.tsv", "r");
    if( dB == NULL) {
      printf("\nAAAAAAAAAAAAAAAA");
      return;
    }
    printf("\nBK 11");
		fgets(dBLine, sizeof(dBLine), dB); 
    printf("\nBK 12");				//come a primeira linha
    	while (fgets(dBLine, sizeof(dBLine), dB)) {
			++PCodeCounter;
			token = strtok(dBLine, t);
      printf("\nBK 1");
			for (int i = 0; i < 2; i++) {
				printf("%s\t", token);
				token = strtok(NULL, t);

				if (PCodeCounter == PCode) {
					auxPPrice = token;
          printf("\nBK 0");
					PPrice = strtof(token, &endptr);
          PPrice = strtof(endptr, NULL);
          printf("\nBK 2");
				}
			}
		}
    printf("\nBK 3");
		CPaid = (float)PAmmount*PPrice;
    printf("\nTO AQ\n");
		// printf("Insert the price paid by the client: "); //hey, teacher! Leave them kids alone!
		// scanf("%f", &CPaid);
		// clearStdin();
		dB = fopen("PizzaDB/salesRecord.tsv", "a+"); //all in all, it's just a-nother brick in the wall
		fprintf(dB, "%d\t%d\t%d\t%.2f\n", PCode, CCode, PAmmount, CPaid);
		fclose(dB);
		getchar();
	}
}

void openMenu(FILE *dB) {
	int times = 0;
    char  dBLine[170];
	clear();
    if((dB = fopen("PizzaDB/menuPizzaria.tsv", "r")) == NULL) {
         printf(RED"ERR:"CLR" Failed to read file!\n");
    } else {
		fgets(dBLine, sizeof(dBLine), dB);
		printf("P Code\t%s", dBLine);
        while (fgets(dBLine, sizeof(dBLine), dB))
			printf("%.3d\t%s", ++times, dBLine);
        fclose(dB);
	}
	printf("Press RETURN to Main Menu");
	getchar(); clearStdin();

}

void openClientContacts(FILE *dB) {
	int times = 0;
    char  dBLine[170];
	clear();
    if((dB = fopen("PizzaDB/clientContacts.tsv", "r")) == NULL) {
         printf(RED"ERR:"CLR" Failed to read file!\n");
    } else {
		fgets(dBLine, sizeof(dBLine), dB); 
		printf("C Code\t%s", dBLine);
        while (fgets(dBLine, sizeof(dBLine), dB))
			printf("%d\t%s", times++, dBLine);
        fclose(dB);
	}
	printf("Press RETURN to Main Menu");
	getchar(); clearStdin();
}

void openSalesHistory(FILE *dB) {
	int times = 0;
    char  dBLine[170];
	clear();
    if((dB = fopen("PizzaDB/salesHistory.tsv", "r")) == NULL) {
         printf(RED"ERR:"CLR" Failed to read file!\n");
    } else {
		fgets(dBLine, sizeof(dBLine), dB);
		printf("%s", dBLine);
        while (fgets(dBLine, sizeof(dBLine), dB)) {
			printf("%d\t%s", times, dBLine);
		}
        fclose(dB);
	}
	printf("Press RETURN to Main Menu");
	getchar(); clearStdin();
}

void mMenu(int *men) {
	clear();
	printf(YLW"                                     ._\n                                   ,(  `-.\n                                 ,': `.   `.\n                               ,` *   `-.   \\\n                             ,'  ` :+  = `.  `.\n                           ,~  "RED"(o)"YLW":  .,   `.  `.\n                         ,'  ; :   ,"RED"(__)"YLW" x;`.  ;\n                       ,'  :'  itz  ;  ; ; _,-'\n                     .'"RED"O"YLW" ; = _' C ; ;'_,_ ;\n                   ,;  _;   ` : ;'_,-'   i'\n                 ,` `;"RED"(_)"YLW"  "RED"0"YLW" ; ','       :\n               .';6     ; ' ,-'~\n             ,' "RED"Q"YLW"  ,& ;',-.'\n           ,( :` ; _,-'~  ;\n         ,~.`c _','\n       .';^_,-' ~\n     ,'_;-''\n    ,,~\n    i'\n    :\n\n\n\n"RED"1"YLW"-New pizza flav"RED"o"YLW"ur\n"RED"2"YLW"-New client entry\n"RED"3"YLW"-Rec"RED"o"YLW"rd complete "RED"o"YLW"rder\n"RED"4"YLW"-Read pizza menu\n"RED"5"YLW"-Read client data\n"RED"6"YLW"-Read past sales\n"RED"7"YLW"-Exit\n\nInsert y"RED"o"YLW"ur "RED"o"YLW"ption: "RED);
	scanf("%d", men);
	while (*men < 1 || *men > 7) {
		printf("Invalid option, try again: ");
		scanf("%d", men);
	}
	clearStdin();
	printf(CLR);
}

int main () {
	FILE *dB;
	int men;
	system("mkdir PizzaDB");
        do {
			mMenu(&men);
			switch (men) {
				case 1: addPizza(dB);
				break;
				case 2: addClient(dB);
				break;
				case 3: recordSale(dB);
				break;
				case 4: openMenu(dB);
				break;
				case 5: openClientContacts(dB);
				break;
				case 6: openSalesHistory(dB);
				break;
			}
		} while (men != 7);
	clear();
}
