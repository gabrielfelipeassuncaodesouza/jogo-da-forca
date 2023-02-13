#include <stdio.h>
#include <stdlib.h>

int main() {

	FILE* f;
	f = fopen("teste.txt", "r+");
	char nword[20];

	printf("\nAdd new word? ");
	scanf("%s", nword);

	int qtd;
	fscanf(f, "%d", &qtd);
	char word[20];

	int existe = 0;

	for(int i = 0; i < qtd; i++) {

		fscanf(f, "\n%s", word);

	for(int j = 0; j <= strlen(nword); j++) {
		if(word[j] == nword[j]) {
			printf("\nErro\n");
			existe = 1; 
	} else {
		existe = 0;
	}


	}
		if(existe == 1) {
			break;
		}
	}

	if(existe == 0) {

		qtd++;
		fseek(f, 0, SEEK_SET);
		fprintf(f, "%04d", qtd); 

	}

	fclose(f);
}
