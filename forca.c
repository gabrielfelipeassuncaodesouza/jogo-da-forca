#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "forca.h"
#include <time.h>

char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;
int nivel;
int pontos = 1000;
int m = 0;


void abertura() {

printf("\n\n/****************/\n");
printf("/ Jogo de Forca */\n");
printf("/****************/\n\n");

}



void chooselevel() {


	printf("\nSelecione o nível de dificuldade: \n");
	printf("(1) Fácil (2) Médio (3) Difícil ");
	scanf("%d", &nivel);

	switch(nivel) {

		default:
			nivel = FACIL;
			m = 200;
			break;
		case 2:
			nivel = MEDIO;
			m = 250;
			break;
		case 3:
			nivel = DIFICIL;
			m = 333;
			break;
	}
}




int letravalida(char letra) {

	int convertletra = (int)letra;

	if(convertletra >= 65 && convertletra <=90) {
		return 1;
	}
	return 0;
}




void chuta() {

	char chute;

	printf("\n\nQual letra? ");
	scanf(" %c", &chute);

	if(letravalida(chute)) {

	if(letraexiste(chute)) {

		printf("\n\n\033[32mVOCÊ ACERTOU :D\033[m\n");

	} else {
        	printf("\n\n\033[31mVOCÊ ERROU :(\033[m\n");
	}

	chutes[chutesdados] = chute;
	chutesdados++;

} else {

	printf("\n\033[31mCARARCTERE INVÁLIDO. USE SOMENTE LETRAS MAIÚSCULAS\033[m\n\n");

}
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

return chuteserrados() >= nivel;

}




int ganhou(){

	for(int i=0; i < strlen(palavrasecreta); i++) {

		if(!jachutou(palavrasecreta[i])) {
			return 0;
		}

	}

	return 1;
}




int palavraexiste(char* palavra) {

	FILE* f;
	f = fopen("palavras.txt", "r");

	int count;
	char palavraarquivo[TAMANHO_PALAVRA];

	fscanf(f, "%d", &count);

	for(int i = 0; i <= count; i++) {

		fscanf(f, "%s", palavraarquivo);
		int achou = 0;

		for(int j = 0; j < strlen(palavra); j++) {
		if(palavraarquivo[j] ==  palavra[j]) {
			achou = 1;
		} else {
			achou = 0;
		}
		}

		if (achou == 1){

			return 1;
		}
	}
	return 0;
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

		if(palavraexiste(novapalavra)) {

		printf("\n\033[33mESSA PALAVRA JÁ EXISTE!\033[m\n\n");

		} else {

		qtde++;

		fseek(f, 0, SEEK_SET);
		fprintf(f, "%04d", qtde);

		fseek(f, 0, SEEK_END);
		fprintf(f, "\n%s", novapalavra);

		fclose(f);
		}
	}
}


void addranking() {

	char quer;
	printf("\nDeseja adicionar seu nome no ranking [S/N]? ");
	scanf(" %c", &quer);

	if (quer == 'S') {
	char nome[20];

	printf("\nDigite seu nickname: ");
	scanf("%s", nome);

	FILE* f;
	f = fopen("ranking.txt", "a");

	fprintf(f, "\n%s %d", nome, pontos);
	fclose(f);
	}
}




void calculapontos() {

	pontos = pontos - (chuteserrados() * m);

}




int main() {

abertura();
escolhepalavra();
chooselevel();

do {

desenhaforca();
chuta();

} while(!ganhou() && !enforcou());

calculapontos();

if(ganhou()) {

printf("\n\033[32mParabéns, você ganhou!\033[m");
printf("\nVoce fez %d pontos!\n\n", pontos);
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

addword();
addranking();

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
