#include <stdio.h>
#include <stdlib.h>

#include "batalhanaval.h"

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