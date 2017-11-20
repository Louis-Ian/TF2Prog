//'Escrito' por Louis Ian
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct celula{
	int linha;
	int coluna;
	int existe;
	struct celula* dir;
	struct celula* esq;
	struct celula* top;
	struct celula* bot; 
} Celula;

int jogada(){
	char* jogada;
	int linha = 0;
	int coluna = 0;
	char s;
	char c;
	int i = 0;
	int countChars = 0;
	int dezOuUnid = 10;

	printf("Insira as coordenadas do baombardeio: ");
	scanf("%[^\n]");//trava aqui!
	printf("0\n");
	/*do{
		printf("%d\n", i);
		s[0] = getchar();
		jogada[i] = s[0];
		i++;
		countChars++;
	}while(strcmp(s,"\n") != 0);*/
	
	printf("1\n");

	i = 0;
	do{
		c = jogada[i];
		if(c >= 65 && c <= 76){
			coluna += (c %65)+1;
		}
		else if(c >= 97 && c <= 108){
			coluna += (c %97)+1;
		}
		else if((c >= 48 && c <= 57)){
			linha += ((c %48)+1) * dezOuUnid;
			dezOuUnid = 1;
		}
		i++;
	}while(i<countChars);

	return 10*(linha-1) + coluna;
}

int main(int argc, char const *argv[])
{
	int jog = jogada();
	printf("%d\n", jog);

	return 0;
}