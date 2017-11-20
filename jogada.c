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
	char jogada[10];
	int linha = 0;
	int coluna = 0;
	char s[10];
	char c;
	int i = 0;
	int countChars = 0;
	int dezOuUnid = 10;

	printf("Insira as coordenadas do baombardeio: ");
	scanf("%[^\n]",jogada);
	printf("0\n");
	/*do{
		printf("%d\n", i);
		s[0] = getchar();
		jogada[i] = s[0];
		i++;
		countChars++;
	}while(strcmp(s,"\n") != 0);*/
	
	printf("1\n");
	printf("%d\n",countChars);

	i = 0;//trava aqui!
	do{
		c = jogada[i];
		if(c >= 'A' && c <= 'L'){
			printf("coluna: %d\n",c-'A'+1);
			coluna += c - 'A' + 1;
		}
		else if(c >= 'a' && c <= 'l'){
			printf("coluna: %d\n",c - 'a' + 1);
			coluna += c - 'a' + 1;
		}
		else if((c >= 48 && c <= 57)){
			s[0] = c;
			linha += atoi(s);
			printf("linha: %d\n",linha);
			dezOuUnid = 1;
		}
		i++;
	}while(i<10);
	printf("l=%d ; c=%d\n", linha, coluna);

	return 10*(linha-1) + coluna;
}

int main(int argc, char const *argv[])
{
	int jog = jogada();
	printf("%d\n", jog);

	return 0;
}