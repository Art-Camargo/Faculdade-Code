#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
bool ClearBuffer(){
	int c, count = 0;
	while((c = getchar()) != '\n'){
		count++;
	}
	if(count > 0){
		return true;
	} else{
		return false;
	}
}
int main(){
	char string[20];
	bool refaz;
	
	do{
		refaz = true;
		fgets(string, 20, stdin);
		ClearBuffer();
		if(strlen(string) == 1){
			refaz = false;
		}
		printf("\n\n%d", strlen(string));
	}while(!refaz);
	return 0;
}
