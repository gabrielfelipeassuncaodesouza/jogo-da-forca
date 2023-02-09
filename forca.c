#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"
#include <time.h>

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura() {

printf("\n\n/****************/\n");
printf("/ Jogo de Forca */\n");
printf("/****************/\n\n");

}

void chuta() {

char chute;

printf("\n\nQual letra? ");
scanf(" %c", &chute);

if(letraexiste(chute)) {
	printf("\n\n\033[32mVOCÊ ACERTOU :D\033[m\n");
} else {
	printf("\n\n\033[31mVOCÊ ERROU :(\033[m\n");
}


chutes[chutesdados] = chute;
chutesdados++;

}

int jachutou(char letra) {

int achou = 0;

for(int j = 0; j < chutesdados; j++) {

                if(letra == chutes[j]) {
                        achou = 1;
                        break;
                }
        }

	return achou;
}

void desenhaforca() {

int erros = chuteserrados();

printf(" _______ 	\n");
printf(" |/ | 		\n");
printf(" | %c%c%c	\n", (erros>=1?'(':' '),
 (erros>=1? '_':' '),(erros>=1? ')':' '));
printf(" | %c%c%c 	\n", (erros>=3?'\\':' '),
 (erros>=2?'|':' '), (erros>=3?'/':' '));
printf(" |  %c 		\n", (erros>=2?'|': ' '));
printf(" | %c %c 	\n", (erros>=4?'/':' '),
 (erros>=4?'\\':' '));
printf(" | 		\n");
printf("_|___ 		\n");
printf("\n\n");

for(int i = 0; i < strlen(palavrasecreta); i++) {

        if (jachutou(palavrasecreta[i])) {

                printf("%c", palavrasecreta[i]);

	} else {
                printf("_ ");
        }

}
}

void escolhepalavra() {

	FILE* f;
	f = fopen("palavras.txt", "r");

	if (f == 0) {
		printf("\nError 404 not found\n");
		exit(1);
	}

	int qdepalavras;
	fscanf(f, "%d", &qdepalavras);

	srand(time(0));
	int rando = rand() % qdepalavras;

	for(int i = 0; i <= rando; i++) {
		fscanf(f, "%s", palavrasecreta);
	}

	fclose(f);
}

int letraexiste(char letra) {

	for(int j = 0; j < strlen(palavrasecreta); j++) {

	if(letra == palavrasecreta[j]) {
		return 1;
	}
}

return 0;

}

int chuteserrados() {

int erros = 0;

for(int i = 0; i < chutesdados; i++) {


	if(!letraexiste(chutes[i])) erros++;

}

return erros;

}

int enforcou() {

return chuteserrados() >= 5;

}

int ganhou(){

	for(int i=0; i < strlen(palavrasecreta); i++) {

		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}

	}

return 1;
}

void addword() {
	char quer;
	printf("Deseja adicionar uma nova palavra no banco de dados? ");
	scanf(" %c", &quer);

	if(quer == 'S') {
		char novapalavra[TAMANHO_PALAVRA];
		printf("Digite a nova palavra: ");
		scanf("%s", novapalavra);

		FILE* f;
		f = fopen("palavras.txt", "r+");

		if(f == 0) {
			printf("Error 404 not found");
			exit(1);
		}

		int qtde;
		fscanf(f, "%d", &qtde);

		qtde++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%d", qtde);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novapalavra);

		fclose(f);
	}
}


int main() {

abertura();
escolhepalavra();

do {

desenhaforca();
chuta();

} while(!ganhou() && !enforcou());

if(ganhou()) {

printf("\n\033[32mParabéns, você ganhou!\033[m\n\n");
printf("\033[33m      ___________ 		\n");
printf("     '._==_==_=_.' 		\n");
printf("     .-\\:      /-. 		\n");
printf("     | (|:.     |) | 		\n");
printf("      '-|:.     |-' 		\n");
printf("        \\::.   / 		\n");
printf("         '::. .' 		\n");
printf("           ) ( 			\n");
printf("         _.' '._ 		\n");
printf("        '-------' 		\033[m\n\n");

} else {

printf("\n\033[33mPuxa, você foi enforcado!\033[m\n");
printf("A palavra era **\033[32m%s\033[m**\n\n", palavrasecreta);

printf("\033[31m      _______________ 			\n");
printf("     /               \\ 		\n");
printf("    /                 \\ 		\n");
printf("  //                   \\/\\ 		\n");
printf("  \\|    XXXX    XXXX   | / 		\n");
printf("   |    XXXX    XXXX   |/ 		\n");
printf("   |    XXX      XXX   | 		\n");
printf("   |                   | 		\n");
printf("    \\__     XXX      __/ 		\n");
printf("      |\\    XXX     /| 		\n");
printf("      | |           | | 		\n");
printf("      | I I I I I I I | 		\n");
printf("      |  I I I I I I  | 		\n");
printf("      \\_             _/ 		\n");
printf("        \\_         _/ 			\n");
printf("          \\_______/ 			\033[m\n\n");

}

}
