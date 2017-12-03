#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "batalhanaval.h"

#define true 1
#define false 0

struct no{
	char c;
	struct  no* prox;
	struct no* fim;
};

void inicializar_fila(struct no **fila){
	(*fila)=NULL;
}

void incluir_fila(struct no **fila,char x){
	struct no* novo=malloc(sizeof(struct no));
	novo->c=x;
	novo->prox=NULL;
	if ((*fila)==NULL){
		(*fila)=novo;
	}else{	
		(*fila)->fim->prox=novo;
	}
	(*fila)->fim=novo;
}

void remover_fila(struct no **fila){
		struct no* i=(*fila);
		(*fila)=(*fila)->prox;
		free(i);
}

int tamanho_fila(struct no **fila){
	int i=0;
	struct no* it=(*fila);
	while(it!=NULL){
		i++;
		it=it->prox;
	}
	return i;
}

void percorrer_fila(struct no **fila){
	struct no* it=(*fila);
	while(it!=NULL){
		printf("%c",it->c);
		it=it->prox;
	}
	printf("\n");
}

int validar_numero(char c){
	if (c >= '0' && c <= '9'){
		return true;
	}
	return false;
}

int validar_char(char c){
	if ((c >= 'a' && c <= 'z')||(c >= 'A' && c <= 'Z')){
		return true;
	}
	return false;
}

void entrada(struct no** fila){
	int okNum,okChar,ok,i;
	char *entrada=malloc(30*sizeof(char));	
	char c0,c1;
	ok=0;
	while(ok==0){		
		scanf("%[^\n]",entrada);
		getchar();
		okNum=okChar=0;

		for(i=0; entrada[i]!='\0' && ok==0; i++){
			c0=entrada[i];

			if (validar_numero(c0)){
				okNum=1;
				incluir_fila(fila,c0);

				if(entrada[i+1]!='\0'){	
					c1=entrada[i+1];
					if (c0 == '1' && c1 >= '0' && c1 <= '2'){
						incluir_fila(fila,c1);
						i++;
					}
				}

				if(entrada[i+1]!='\0'){
					//c1=entrada[i+1];
					//if (((int)c1>=48 && (int)c1<=57) || (((int)c1>=65 && (int)c1<=90)||((int)c1>=97 && (int)c1<=122) && okChar==1)){
					//	ok=1;
					//	okNum=0;
				//	}
					if(okNum && okChar){
						ok=1;okNum=0;okChar=0;
					}
				}
			}

			if(validar_char(c0)){
				okChar=1;
				incluir_fila(fila,c0);
				if(entrada[i+1]!='\0'){
					//c1=entrada[i+1];
					//if ((((int)c1>=65 && (int)c1<=90) || ((int)c1>=97 && (int)c1<=122) ) || ((int)c1>=48 && (int)c1<=57 && okNum==1)){
					//	ok=1;
					//	okChar=0;
					//}
					if(okNum && okChar) {ok=1;okNum=0;okChar=0;}
				}

			}
			if (okNum && okChar) return;
		}
		ok=0;
		printf("entrada invalida\n");
		while(tamanho_fila(fila)!=0){
			remover_fila(fila);
		}
	}

}

int linha(struct no** fila){
	struct no* it=(*fila);
	int num;
	while(it!=NULL){
		if(validar_numero(it->c)){
			num=((int)(it->c))-48-1;
			if(it->prox != NULL && ((int)(it->prox->c) >= 48 && (int)(it->prox->c) <= 57)){
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

int coluna(struct no** fila){
	struct no* it=(*fila);
	char c;
	while(it!=NULL){
		if(validar_char(it->c)){
			c=it->c;
		}	
		it=it->prox;
	}
	if (c >= 'a' && c <= 'z')
		return c - 'a';
	else
		return c - 'A';

}

void inicializar(struct celula*** mapa){
	(*mapa)=(struct celula**)malloc(12*sizeof(struct celula*));
	for (int i = 0; i < 12; i++){
		(*mapa)[i]=(struct celula*)malloc(sizeof(struct celula));
		(*mapa)[i]->dir=NULL;
		(*mapa)[i]->esq=NULL;
	}
}

void inserir(struct celula** lista){
	struct celula* novo=(struct celula*)malloc(sizeof(struct celula));
	novo->top=NULL;
	novo->bot=NULL;
	novo->existe=1;
	if ((*lista)->dir==NULL){
		(*lista)->dir=novo;
		novo->dir=NULL;
		novo->esq=(*lista);
	}else{
		novo->dir=(*lista)->dir;
		novo->esq=(*lista);
		(*lista)->dir->esq=novo;		
		(*lista)->dir=novo;
	}
}

void criar(struct celula ***mapa){
	for (int i = 0; i < 12; ++i)
	{
		int c=12;
		while (--c>=0){
			inserir(&((*mapa)[i]));
		}
	}
	for(int i=0; i < 11; i++){
		struct celula *it=(*mapa)[i];
		struct celula *it2=(*mapa)[i+1];
		while(it->dir!=NULL){
			it->dir->bot=it2->dir;
			it2->dir->top=it->dir;
			it=it->dir;
			it2=it2->dir;
		}

	}
}

void mapear(struct celula ***mapa){
	struct celula *it=(*mapa)[0]->dir;
	struct celula *it2=(*mapa)[0]->dir;
	int i=0;
	int j=0;
	while(it2!=NULL){
		it->linha=i;
		it->coluna=j;
		if(it->dir != NULL){
			it=it->dir;
		}else{
			it=it2->bot;
			it2=it2->bot;
		}
		j++;
		if(j==12){i++;j%=12;}

	}
}

void printmap(struct celula ***mapa){
	struct celula *it=(*mapa)[0]->dir;
	struct celula *it2=(*mapa)[0]->dir;
	while(it2!=NULL){
		printf("%d,%d\t",it->linha , it->coluna);
		if(it->dir != NULL){
			it=it->dir;
		}else{
			printf("\n");
			it=it2->bot;
			it2=it2->bot;
		}
	}
}

int jogadaRand(int i,int j){
	//srand(time(NULL));
	return i+(rand()%(j-i+1));
}