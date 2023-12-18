#include <stdio.h>
int main() {
	FILE *arquivo;
	char line[150];
	int i = 1;
	arquivo = fopen("listas.cpp", "r");
	if(arquivo != NULL) {
		while(fgets(line, 250, arquivo) != NULL) {
			printf("%d: %s\n", i, line);
			i++;
		}
	}
}
