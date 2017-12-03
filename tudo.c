#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct celula{
	int linha;
	int coluna;
	int existe;
	char conteudo;
	struct celula* dir;
	struct celula* esq;
	struct celula* top;
	struct celula* bot; 
}celula;

void inicializar(celula*** mapa){
	(*mapa)=(celula**)malloc(12*sizeof(celula*));
	for (int i = 0; i < 12; i++){
		(*mapa)[i]=NULL;
	}
}

void inserir(celula** lista){

	celula* novo=(celula*)malloc(sizeof(celula));
	novo->top=NULL;
	novo->bot=NULL;
	novo->existe=0;
	novo->conteudo=' ';

	if ((*lista)==NULL){
		(*lista)=novo;
		novo->dir=NULL;
		novo->esq=NULL;
	}else{
		novo->dir=(*lista)->dir;
		novo->esq=(*lista);
		if((*lista)->dir!=NULL) (*lista)->dir->esq=novo;		
		(*lista)->dir=novo;
	}
}

void criar(celula ***mapa){
	celula *it3;
	celula *it;
	celula *it2;

	for (int i = 0; i < 12; ++i){

		int c=12;
		while (--c>=0){
			inserir(&((*mapa)[i]));
		}

	}

	for(int i=0; i < 11; i++){

		it=((*mapa)[i]);
		it2=((*mapa)[i+1]);

		while(it!=NULL){
			it->bot=it2;
			it2->top=it;
			if(it->dir==NULL){
				it3=it;
			}
			if(it!=NULL) it=it->dir;
			if(it2!=NULL) it2=it2->dir;
		}

		it3->dir=((*mapa)[i+1]);
		((*mapa)[i+1])->esq=it3;	
	}
}

void mapear(celula ***mapa){
	celula *it=((*mapa)[0]);
	int i,j;
	i=j=0;

	while(it!=NULL){
		it->linha=i;
		it->coluna=j;
		if(it!=NULL) it=it->dir;
		j++;
		if(j==12){i++;j%=12;}
	}

}

void printmap(celula ***mapa, celula***mapa2){
	celula *it=(*mapa)[0];
	celula *it2;
	int j=0;
	int i=1;
	printf("  |A|B|C|D|E|F|G|H|I|J|K|L|                   |A|B|C|D|E|F|G|H|I|J|K|L|\n");

	while(it!=NULL){

		if(j==0 && i<10) printf("%d ",i);
		if (j==0 && i>=10) printf("%d",i);
		printf("|%c",it->conteudo);
		if(it!=NULL) it=it->dir;
		j++;

		if(j==12){
			printf("|                 ");
			it2=(*mapa2)[i-1];
			int c=12;

			while(--c>=0){
				if(i<10 && c==11) printf("%d ",i);
				if (i>=10 && c==11) printf("%d",i);
				printf("|%c",it2->conteudo);
				if(it2!=NULL) it2=it2->dir;
			}

			j%=12;
			i++;
			printf("|\n");
		}
	}
}
	/*
	void printmap(celula ***mapa){
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
	}
	*/

celula* acesso(celula*** mapa, int linha, int coluna){
	celula* it=(*mapa)[linha];

	while(coluna>0){
		it=it->dir;
		coluna--;
	}

	return it;
}


int range(int i,int j){
	return i+(rand()%(j-i+1));
}

int inializarjogo(celula ***mapa){
	int n=9;
	int i,j,d;
	celula* it;
	while(--n>=0){
		d=range(0,1); // 0 horizonal 1 vertical;
		if(n==8){	//portaaviao
			if(d==0){
				do{
				i=range(0,11);
				j=range(0,7);
				it=acesso(mapa,i,j);
				}while(it->existe==1 || it->dir->existe==1 || it->dir->dir->existe==1 || it->dir->dir->dir->existe==1 || it->dir->dir->dir->dir->existe==1);
				it->conteudo='<';
				it->dir->conteudo='#';
				it->dir->dir->conteudo='#';
				it->dir->dir->dir->conteudo='#';
				it->dir->dir->dir->dir->conteudo='>';
				it->existe=1;
				it->dir->existe=1;
				it->dir->dir->existe=1;
				it->dir->dir->dir->existe=1;
				it->dir->dir->dir->dir->existe=1;
			}else{
				do{
				i=range(0,7);
				j=range(0,11);
				it=acesso(mapa,i,j);
				}while(it->existe==1 || it->bot->existe==1 || it->bot->bot->existe==1 || it->bot->bot->bot->existe==1 || it->bot->bot->bot->bot->existe==1);
				it->conteudo='^';
				it->bot->conteudo='#';
				it->bot->bot->conteudo='#';
				it->bot->bot->bot->conteudo='#';
				it->bot->bot->bot->bot->conteudo='v';
				it->existe=1;
				it->bot->existe=1;
				it->bot->bot->existe=1;
				it->bot->bot->bot->existe=1;
				it->bot->bot->bot->bot->existe=1;
			}
		}
		if(n==7 || n==6){ //destroyer
			if(d==0){
				do{
				i=range(0,11);
				j=range(0,9);
				it=acesso(mapa,i,j);
				}while(it->existe==1 || it->dir->existe==1 || it->dir->dir->existe==1);
				it->conteudo='<';
				it->dir->conteudo='#';
				it->dir->dir->conteudo='>';
				it->existe=1;
				it->dir->existe=1;
				it->dir->dir->existe=1;
			}else{
				do{
				i=range(0,9);
				j=range(0,11);
				it=acesso(mapa,i,j);
				}while(it->existe==1 || it->bot->existe==1 || it->bot->bot->existe==1);
				it->conteudo='^';
				it->bot->conteudo='#';
				it->bot->bot->conteudo='v';
				it->existe=1;
				it->bot->existe=1;
				it->bot->bot->existe=1;
			}
		}
		if(n==5 || n==4 || n==3){ //fragata
			if(d==0){
				do{
				i=range(0,11);
				j=range(0,10);
				it=acesso(mapa,i,j);
				}while(it->existe==1 || it->dir->existe==1);
				it->conteudo='<';
				it->dir->conteudo='>';
				it->existe=1;
				it->dir->existe=1;
			}else{
				do{
				i=range(0,10);
				j=range(0,11);
				it=acesso(mapa,i,j);
				}while(it->existe==1 || it->bot->existe==1);
				it->conteudo='^';
				it->bot->conteudo='v';
				it->existe=1;
				it->bot->existe=1;
			}
		}
		if(n==2 || n==1){ //submarino	
				do{
				i=range(0,11);
				j=range(0,11);
				it=acesso(mapa,i,j);
				}while(it->existe==1);
				it->conteudo='@';	
				it->existe=1;			
		}
		if(n==0){ //jangada	
				do{
				i=range(0,11);
				j=range(0,11);
				it=acesso(mapa,i,j);
				}while(it->existe==1);
				it->conteudo='&';
				it->existe=1;			
		}
	}
}

typedef struct no{
	char c;
	struct no* prox;
	struct no* fim;
}no;

void inicializar_fila(no** fila){
	(*fila)=NULL;
}

void incluir_fila(no** fila, char x){
	no* novo=malloc(sizeof(no));
	novo->c=x;
	novo->prox=NULL;
	if ((*fila)==NULL){
		(*fila)=novo;
	}else{	
		(*fila)->fim->prox=novo;
	}
	(*fila)->fim=novo;
}

void remover_fila(no** fila){
		no* i=(*fila);
		(*fila)=(*fila)->prox;
		free(i);
}
int tamanho_fila(no** fila){
	int i=0;
	no* it=(*fila);
	while(it!=NULL){
		i++;
		it=it->prox;
	}
	return i;
}
void percorrer_fila(no** fila){
	no* it=(*fila);
	while(it!=NULL){
		printf("%c",it->c);
		it=it->prox;
	}
	printf("\n");
}
int linha(no** fila){
	no* it=(*fila);
	int num;
	while(it!=NULL){
		if((int)(it->c)>=49 && (int)(it->c)<=57){
			num=((int)(it->c))-48-1;
			if(it->prox!=NULL && ((int)(it->prox->c)>=48 && (int)(it->prox->c)<=57)){
				num++;
				num*=10;
				num+=((int)(it->prox->c))-48-1;
				return num;
			}
		}	
		it=it->prox;
	}
	return num;
}

int coluna(no** fila){
	no* it=(*fila);
	char c;
	while(it!=NULL){
		if(((int)(it->c)>=65 && (int)(it->c)<=77)||((int)(it->c)>=97 && (int)(it->c)<=108)){
			c=it->c;
		}	
		it=it->prox;
	}
	if ((int)c>=65 && (int)c<=77)return (int)c - 65;
	else return (int)c - 97;

}

//qqr coisa confusa eh desconsiderada por exemplo 'a' '1' '2' ' ' torna-se confuso, visto o espaco no fim q pode ter sido fruto de uma falha motora
celula* entrada(no** fila, celula*** mapa){
	int ok1,ok2,ok,i;
	char *entrada=malloc(100*sizeof(char));	
	char c0,c1;
	ok=0;
	while(ok==0){
		printf("entrada:");		
		scanf("%[^\n]",entrada);
		getchar();
		ok1=ok2=0;
		for(i=0; entrada[i]!='\0' && ok==0; i++){
			
			c0=entrada[i];
			if( !(((int)c0>=65 && (int)c0<=90)||((int)c0>=97 && (int)c0<=122)) && !((int)c1>=48 && (int)c1<=57)&& !ok1 && !ok2){ok=1;} //,,,,,,,,a1
			if ((int)c0>=49 && (int)c0<=57){//numero
				if(ok1){ok1=0;ok=1;}
				else{
					ok1=1;
					incluir_fila(fila,c0);
					i++;
					if(entrada[i]!='\0'){
						c1=entrada[i];
						if(!((int)c1>=48 && (int)c1<=57) && ok1 && ok2){ok1=0;ok=1;}//ValidoXX a1... X qqr
						if((int)c0==49){ //1X
							if((int)c1>=48 && (int)c1<=50){ //10-12
								incluir_fila(fila,c1);
								i++;
								if(entrada[i]!='\0'){
									c1=entrada[i];
									if((int)c1>=48 && (int)c1<=57 || ok1 && ok2){ // XXX... ou ValidoXXX a12... X qqr
										ok1=0;ok=1;
									}
								}
							}
							if((int)c1>=51 && (int)c1<=57){ //12-19
								ok1=0;ok=1;
							}
						}
						if((int)c0>49 && (int)c0<=57){ //X0-X9 X>1
							if((int)c1>=48 && (int)c1<=57){
								ok1=0;ok=1;
							}
						}
					}
				}
			}

			c0=entrada[i];

			if(((int)c0>=65 && (int)c0<=90)||((int)c0>=97 && (int)c0<=122)){ //letrastotais
				if((((int)c0>=65 && (int)c0<=77)||((int)c0>=97 && (int)c0<=108)) && !ok2){ //letravalidas
					ok2=1;
					incluir_fila(fila,c0);
					if(entrada[i+1]!='\0'){
						if(ok1 && ok2){ok1=0;ok2=0;ok1=1;}//ValidoXXX... X qqr
					}
				}else{
					ok1=0;ok2=0;ok=1;
				}
			}


			if (ok1 && ok2){
				celula* t=acesso(mapa,linha(fila),coluna(fila));
				if(t->existe!=1){
					while(tamanho_fila(fila)!=0){
						remover_fila(fila);
					}
					free(entrada);
					return t;
				}
			} 
		}
		ok=0;
		printf("entrada invalida\n");
		while(tamanho_fila(fila)!=0){
			remover_fila(fila);
		}
	}

}



int main(){
	srand(time(NULL));
	celula** mapa;
	inicializar(&mapa);
	criar(&mapa);
	mapear(&mapa);
	inializarjogo(&mapa);
	celula** mapa2;
	inicializar(&mapa2);
	criar(&mapa2);
	mapear(&mapa2);
	inializarjogo(&mapa2);
	printmap(&mapa,&mapa2);
	no* fila;
	inicializar_fila(&fila);
	while(1){
		celula* t=entrada(&fila,&mapa);
		printf("coord lxc : %d,%d\n", t->linha, t->coluna);
	}
	return 0;
}
