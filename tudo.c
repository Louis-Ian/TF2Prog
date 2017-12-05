#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*		ASCII - LOCALE
#include <locale.h>
setlocale(LC_ALL,"");
mar = 177;
invisivel = 219;
*/

#define true 1
#define false 0

#define clear_screen() printf("\033[H\033[J")

typedef struct celula{
	int linha;
	int coluna;
	int existe;
	int repetido;
	int atingido;
	char conteudo;
	struct celula* dir;
	struct celula* esq;
	struct celula* top;
	struct celula* bot; 
}celula;

void inicializar_mapa(celula*** mapa){
	(*mapa) = (celula**)malloc(12*sizeof(celula*));
	for (int i = 0; i < 12; i++){
		(*mapa)[i] = NULL;
	}
}

void inserir_celula(celula** lista){

	celula* novo = (celula*)malloc(sizeof(celula));
	novo->top = NULL;
	novo->bot = NULL;
	novo->existe = 0;
	novo->repetido = 0;
	novo->atingido = false;
	novo->conteudo = ' ';

	if ((*lista) == NULL){
		(*lista) = novo;
		novo->dir = NULL;
		novo->esq = NULL;
	}else{
		novo->dir = (*lista)->dir;
		novo->esq = (*lista);
		if((*lista)->dir != NULL)
			(*lista)->dir->esq = novo;		
		(*lista)->dir = novo;
	}
}

void criar_mapa(celula ***mapa){
	celula *it3;
	celula *it;
	celula *it2;

	for (int i = 0; i < 12; ++i){

		int c=12;
		while (--c >= 0){
			inserir_celula(&((*mapa)[i]));
		}

	}

	for(int i = 0; i < 11; i++){

		it = ((*mapa)[i]);
		it2 = ((*mapa)[i+1]);

		while(it != NULL){
			it->bot = it2;
			it2->top = it;
			if(it->dir == NULL)
				it3 = it;
			if(it != NULL)
				it = it->dir;
			if(it2 != NULL)
				it2 = it2->dir;
		}

		it3->dir = ((*mapa)[i+1]);
		((*mapa)[i+1])->esq = it3;	
	}
}

void mapear(celula ***mapa){
	celula *it = ((*mapa)[0]);
	int i,j;
	i = j = 0;

	while(it != NULL){
		it->linha = i;
		it->coluna = j;
		if(it != NULL)
			it = it->dir;
		j++;
		if(j ==12){
			i++;
			j %= 12;
		}
	}
}

void printmap(celula ***mapaJogador, celula ***mapaPC){
	celula *it = (*mapaJogador)[0];
	celula *it2;
	int j = 0;
	int i = 1;

	printf("                 HUMANO                                               COMPUTADOR\n");
	printf("     ╔══╦═╦═╦═╦═╦═╦═╦═╦═╦═╦═╦═╦═╗                       ╔══╦═╦═╦═╦═╦═╦═╦═╦═╦═╦═╦═╦═╗\n");
	printf("     ║  ║A║B║C║D║E║F║G║H║I║J║K║L║                       ║  ║A║B║C║D║E║F║G║H║I║J║K║L║\n");

	while(it != NULL){

		if(j == 0 && i < 10)
			printf("     ║%d ",i);
		if(j == 0 && i >= 10)
			printf("     ║%d",i);

		printf("║%c",it->conteudo);
		if(it != NULL)
			it = it->dir;
		j++;

		if(j == 12){
			printf("║                       ");
			it2 = (*mapaPC)[i-1];
			int c = 12;

			while(--c >= 0){
				if(i < 10 && c == 11)
					printf("║%d ",i);
				if(i >= 10 && c == 11)
					printf("║%d",i);

				if(it2->atingido == false)
					printf("║ ");
				else
					printf("║%c", it2->conteudo);
				
				if(it2 != NULL)
					it2 = it2->dir;
			}

			j %= 12;
			i++;
			printf("║\n");
		}
	}
	printf("     ╚══╩═╩═╩═╩═╩═╩═╩═╩═╩═╩═╩═╩═╝                       ╚══╩═╩═╩═╩═╩═╩═╩═╩═╩═╩═╩═╩═╝\n");
}

/*	void printmap(celula ***mapa){
		celula *it=(*mapa)[0]->dir;
		celula *it2=(*mapa)[0]->dir;
		while(it2!=NULL){
			printf("%d,%d\t",it->linha , it->coluna);
			if(it->dir != it2->bot){
				it=it->dir;
			}else{
				printf("\n");
				it=it2->bot;
				it2=it2->bot;
			}
		}
} */

celula* acessar_coordenada(celula*** mapa, int linha, int coluna){
	celula* it = (*mapa)[linha];

	while(coluna>0){
		it = it->dir;
		coluna--;
	}

	return it;
}

int range(int i,int j){
	return i+(rand()%(j-i+1));
}

int distribuir_embarcacoes(celula ***mapa){
	int n = 9;
	int i, j, d;
	celula* it;
	while(--n >= 0){
		d = range(0,1); // 0 horizonal 1 vertical;
		if(n == 8){	//portaaviao
			if(d == 0){
				do{
				i = range(0,11);
				j = range(0,7);
				it = acessar_coordenada(mapa,i,j);
				}while(it->existe == 1 || it->dir->existe == 1 || it->dir->dir->existe == 1 || it->dir->dir->dir->existe == 1 || it->dir->dir->dir->dir->existe == 1);
				it->conteudo = '<';
				it->dir->conteudo = '#';
				it->dir->dir->conteudo = '#';
				it->dir->dir->dir->conteudo = '#';
				it->dir->dir->dir->dir->conteudo = '>';
				it->existe = 1;
				it->dir->existe = 1;
				it->dir->dir->existe = 1;
				it->dir->dir->dir->existe = 1;
				it->dir->dir->dir->dir->existe = 1;
			}else{
				do{
				i = range(0,7);
				j = range(0,11);
				it = acessar_coordenada(mapa,i,j);
				}while(it->existe == 1 || it->bot->existe == 1 || it->bot->bot->existe == 1 || it->bot->bot->bot->existe == 1 || it->bot->bot->bot->bot->existe == 1);
				it->conteudo = '^';
				it->bot->conteudo = '#';
				it->bot->bot->conteudo = '#';
				it->bot->bot->bot->conteudo = '#';
				it->bot->bot->bot->bot->conteudo = 'v';
				it->existe = 1;
				it->bot->existe = 1;
				it->bot->bot->existe = 1;
				it->bot->bot->bot->existe = 1;
				it->bot->bot->bot->bot->existe = 1;
			}
		}
		if(n == 7 || n == 6){ //destroyer
			if(d == 0){
				do{
				i = range(0,11);
				j = range(0,9);
				it = acessar_coordenada(mapa,i,j);
				}while(it->existe == 1 || it->dir->existe == 1 || it->dir->dir->existe == 1);
				it->conteudo = '<';
				it->dir->conteudo = '#';
				it->dir->dir->conteudo = '>';
				it->existe = 1;
				it->dir->existe = 1;
				it->dir->dir->existe = 1;
			}else{
				do{
				i = range(0,9);
				j = range(0,11);
				it = acessar_coordenada(mapa,i,j);
				}while(it->existe == 1 || it->bot->existe == 1 || it->bot->bot->existe == 1);
				it->conteudo = '^';
				it->bot->conteudo = '#';
				it->bot->bot->conteudo = 'v';
				it->existe = 1;
				it->bot->existe = 1;
				it->bot->bot->existe = 1;
			}
		}
		if(n == 5 || n == 4 || n == 3){ //fragata
			if(d == 0){
				do{
				i = range(0,11);
				j = range(0,10);
				it = acessar_coordenada(mapa,i,j);
				}while(it->existe == 1 || it->dir->existe == 1);
				it->conteudo = '<';
				it->dir->conteudo = '>';
				it->existe = 1;
				it->dir->existe = 1;
			}else{
				do{
				i = range(0,10);
				j = range(0,11);
				it = acessar_coordenada(mapa,i,j);
				}while(it->existe == 1 || it->bot->existe == 1);
				it->conteudo = '^';
				it->bot->conteudo = 'v';
				it->existe = 1;
				it->bot->existe = 1;
			}
		}
		if(n == 2 || n == 1){ //submarino	
				do{
				i = range(0,11);
				j = range(0,11);
				it = acessar_coordenada(mapa,i,j);
				}while(it->existe == 1);
				it->conteudo = '@';	
				it->existe = 1;			
		}
		if(n == 0){ //jangada	
				do{
				i = range(0,11);
				j = range(0,11);
				it = acessar_coordenada(mapa,i,j);
				}while(it->existe == 1);
				it->conteudo = '&';
				it->existe = 1;			
		}
	}
}

typedef struct no{
	char c;
	struct no* prox;
	struct no* fim;
}no;

void inicializar_fila(no** fila){
	(*fila) = NULL;
}

void incluir_fila(no** fila, char x){
	no* novo = malloc(sizeof(no));
	novo->c = x;
	novo->prox = NULL;
	if ((*fila) == NULL){
		(*fila) = novo;
	}else{	
		(*fila)->fim->prox = novo;
	}
	(*fila)->fim = novo;
}

void remover_fila(no** fila){
		no* i = (*fila);
		(*fila) = (*fila)->prox;
		free(i);
}

int tamanho_fila(no** fila){
	int i = 0;
	no* it = (*fila);
	while(it != NULL){
		i++;
		it = it->prox;
	}
	return i;
}

void percorrer_fila(no** fila){
	no* it = (*fila);
	while(it != NULL){
		printf("%c",it->c);
		it = it->prox;
	}
	printf("\n");
}

int entrada_linha(no** fila){
	no* it = (*fila);
	int num;
	while(it != NULL){
		if((it->c) >= '1' && (int)(it->c) <= '9'){
			num=((int)(it->c))-48-1;
			if(it->prox != NULL && ((it->prox->c) >= '0' && (it->prox->c) <= '9')){
				num++;
				num *= 10;
				num += ((int)(it->prox->c))-48-1;
				return num;
			}
		}	
		it = it->prox;
	}
	return num;
}

int entrada_coluna(no** fila){
	no* it = (*fila);
	char c;
	while(it != NULL){
		if(((it->c) >= 'A' && (it->c) <= 'L') || ((it->c) >= 'a' && (it->c) <= 'l')){
			c = it->c;
		}	
		it = it->prox;
	}
	if (c >= 'A' && c <= 'L')
		return (int)c - 65;
	else
		return (int)c - 97;
}

celula* receber_coord_jogador(no** fila, celula*** mapa){
	int okNum, okChar, ok, i;
	char *entrada = malloc(100*sizeof(char));	
	char c0, c1;
	ok = 0;

	while(ok == 0){
		printf("\nCoordenadas do bombardeio:");		
		scanf("%[^\n]",entrada);
		getchar();
		okNum = okChar = 0;

		for(i = 0; entrada[i] != '\0' && ok == 0; i++){
			
			c0 = entrada[i];
			if(okNum && okChar){
				okNum=0;
				okChar=0;
				ok=1;
			}
			
			if (c0 >= '1' && c0 <= '9'){//numero
				if(okNum){
					okNum = 0;
					ok = 1;
				}else{
					okNum = 1;
					incluir_fila(fila,c0);
					i++;
					if(entrada[i] != '\0'){
						c1 = entrada[i];
						if(!(c1 >= '0' && c1 <= '9') && okNum && okChar){
							if(c1 != ' '){
								okNum = 0;
								ok = 1;
							}
						}//ValidoXX a1... X qqr
						if(c0 == '1'){ //1X
							if(c1 >= '0' && c1 <= '2'){ //10-12
								incluir_fila(fila,c1);
								i++;
								if(entrada[i] != '\0'){
									c1 = entrada[i];
									if(c1 >= '0' && c1 <= '9' || okNum && okChar){ // XXX... ou ValidoXXX a12... X qqr
										if(c1 != ' '){
											okNum=0;
											ok = 1;
										}
									}
								}
							}
							if(c1 >= '3' && c1 <= '9'){ //13-19
								okNum = 0;
								ok = 1;
							}
						}
						if(c0 > '1' && c0 <= '9'){ //X0-X9 X>1
							if(c1 >= '0' && c1 <= '9'){
								okNum = 0;
								ok = 1;
							}
						}
					}
				}
			}

			c0=entrada[i];

			if((c0 >= 'A' && c0 <= 'Z') || (c0 >= 'a' && c0 <= 'z')){ //letrastotais
				if(((c0 >= 'A' && c0 <= 'L') || (c0 >= 'a' && c0 <= 'l')) && !okChar){ //letravalidas
					okChar=1;
					incluir_fila(fila,c0);
					if(entrada[i+1] != '\0'){
						if(okNum && okChar){
							if(entrada[i+1]!=' '){
								okNum=0;
								okChar=0;
								ok=1;
							}
						}//ValidoXXX... X qqr
					}
				}else{
					okNum=0;
					okChar=0;
					ok=1;
				}
			}

			if (okNum && okChar){
				celula* t = acessar_coordenada(mapa,entrada_linha(fila),entrada_coluna(fila));
				if(t->repetido==0){
					t->repetido=1;
					while(tamanho_fila(fila) != 0){
						remover_fila(fila);
					}
					free(entrada);
					return t;
				}
				printf("Jogada já feita - ");
			} 
		}
		ok=0;
		printf("Entrada Invalida\n");
		while(tamanho_fila(fila)!=0){
			remover_fila(fila);
		}
	}
}

void ataque_contra_PC(celula*** mapa, int linha, int coluna){
	celula* it = acessar_coordenada(mapa, linha, coluna);

	if(it->conteudo != ' '){
		//it->conteudo = '*';
	}else{
		it->conteudo = 'O';
	}
	it->atingido = true;
}

void ataque_contra_jogador(celula*** mapa, int linha, int coluna){
	celula* it = acessar_coordenada(mapa, linha, coluna);
	
	char mar = 177;
	char invisivel = 219;

	if(it->conteudo != ' '){
		it->conteudo = '*';
	}else{
		it->conteudo = 'O';
	}
	it->atingido = true;
}

void *itoa(int numLinha, int numColuna, char coluna, char linhaDez, char linhaUni){

	coluna = (char)(numColuna + 95);
	if(numLinha < 10){
		linhaUni = (char)(numLinha);
		linhaDez = '0';
	}else{
		linhaDez = '1';
		linhaUni = numLinha - 10;
	}
}

celula* gerar_coord_pc(celula ***mapa){
	int tentativaLinha, tentativaColuna;
	celula *it;

	do{
		tentativaLinha = range(0,11);
		tentativaColuna = range(0,11);

		it = acessar_coordenada(mapa, tentativaLinha, tentativaColuna);
	}while(it->atingido == true);

	return it;
}



int main(){
	char ultimaJogadaH0;
	int ultimaJogadaH1, ultimaJogadaH2;
	
	char ultimaJogadaPC0;
	int ultimaJogadaPC1, ultimaJogadaPC2;


	int primeiraRodada = true;

	clear_screen();

	srand(time(NULL));
	celula** mapaJogador;
	inicializar_mapa(&mapaJogador);
	criar_mapa(&mapaJogador);
	mapear(&mapaJogador);
	distribuir_embarcacoes(&mapaJogador);

	celula** mapaPC;
	inicializar_mapa(&mapaPC);
	criar_mapa(&mapaPC);
	mapear(&mapaPC);
	distribuir_embarcacoes(&mapaPC);
	printmap(&mapaJogador,&mapaPC);

	no* fila;
	inicializar_fila(&fila);

	celula* jogadaH = (celula*)malloc(sizeof(celula));
	celula* jogadaPC = (celula*)malloc(sizeof(celula));
	while(1){
		if(primeiraRodada == true){
			jogadaH = receber_coord_jogador(&fila,&mapaPC);
			clear_screen();

			ultimaJogadaH0 = (char)jogadaH->coluna+65;
			if(jogadaH->linha < 9){
				ultimaJogadaH2 = jogadaH->linha+1;
				ultimaJogadaH1 = 0;
			}else{
				ultimaJogadaH1 = 1;
				ultimaJogadaH2 = jogadaH->linha - 9;
			}

			//itoa(t->linha, t->coluna, ultimaJogadaH[0], ultimaJogadaH[1], ultimaJogadaH[2]);
			
			ataque_contra_PC(&mapaPC, jogadaH->linha, jogadaH->coluna);

			jogadaPC = gerar_coord_pc(&mapaJogador);

			ultimaJogadaPC0 = (char)jogadaPC->coluna+65;
			if(jogadaPC->linha < 9){
				ultimaJogadaPC2 = jogadaPC->linha+1;
				ultimaJogadaPC1 = 0;
			}else{
				ultimaJogadaPC1 = 1;
				ultimaJogadaPC2 = jogadaPC->linha - 9;
			}

			ataque_contra_jogador(&mapaJogador, jogadaPC->linha, jogadaPC->coluna);
			printmap(&mapaJogador, &mapaPC);
			printf("\n Último ataque - Jogador: %c%d%d \n", ultimaJogadaH0, ultimaJogadaH1, ultimaJogadaH2);
			printf("\n Último ataque - Computador: %c%d%d \n", ultimaJogadaPC0, ultimaJogadaPC1, ultimaJogadaPC2);

		}else{
			primeiraRodada = false;

			jogadaH = receber_coord_jogador(&fila,&mapaPC);

			ultimaJogadaH0 = (char)jogadaH->coluna+65;
			if(jogadaH->linha < 9){
				ultimaJogadaH2 = jogadaH->linha+1;
				ultimaJogadaH1 = 0;
			}else{
				ultimaJogadaH1 = 1;
				ultimaJogadaH2 = jogadaH->linha - 9;
			}

			//itoa(t->linha, t->coluna, ultimaJogadaH[0], ultimaJogadaH[1], ultimaJogadaH[2]);
			
			ataque_contra_PC(&mapaPC, jogadaH->linha, jogadaH->coluna);

			jogadaPC = gerar_coord_pc(&mapaJogador);

			ultimaJogadaPC0 = (char)jogadaPC->coluna+65;
			if(jogadaPC->linha < 9){
				ultimaJogadaPC2 = jogadaPC->linha+1;
				ultimaJogadaPC1 = 0;
			}else{
				ultimaJogadaPC1 = 1;
				ultimaJogadaPC2 = jogadaPC->linha - 9;
			}

			ataque_contra_jogador(&mapaJogador, jogadaPC->linha, jogadaPC->coluna);
			printmap(&mapaJogador, &mapaPC);
			printf("\n Último ataque - Jogador: %c%d%d \n", ultimaJogadaH0, ultimaJogadaH1, ultimaJogadaH2);
			printf("\n Último ataque - Computador: %c%d%d \n", ultimaJogadaPC0, ultimaJogadaPC1, ultimaJogadaPC2);
		}
	}
	return 0;
}
