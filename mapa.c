#include <stdio.h>
#include <stdlib.h>

struct celula{
	int linha;
	int coluna;
	int existe;
	struct celula* dir;
	struct celula* esq;
	struct celula* top;
	struct celula* bot; 
};
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

void criar(struct celula ***mapa){
	struct celula *it3;
	struct celula *it;
	struct celula *it2;
	for (int i = 0; i < 12; ++i)
	{
		int c=11;
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

void mapear(struct celula ***mapa){
	struct celula *it=((*mapa)[0]);
	int i=0;
	int j=0;
	while(it!=NULL){
		it->linha=i;
		it->coluna=j;
		if(it!=NULL) it=it->dir;
		j++;
		if(j==12){i++;j%=12;}
	}
}

void printmap(struct celula ***mapa){
	struct celula *it=(*mapa)[0];
	int j=0;
	while(it!=NULL){
		printf("%d,%d  ",it->linha , it->coluna);
		if(it!=NULL) it=it->dir;
		j++;
		if(j==12){j%=12;printf("\n");}
	}
}
	/*
	void printmap(struct celula ***mapa){
		struct celula *it=(*mapa)[0]->dir;
		struct celula *it2=(*mapa)[0]->dir;
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

struct celula* acesso(struct celula*** mapa,int linha, int coluna){
	struct celula* it=(*mapa)[linha];
	while(coluna>0){
		it=it->dir;
		coluna--;
	}
	return it;
}

int main(){
	struct celula** mapa;
	inicializar(&mapa);
	criar(&mapa);
	mapear(&mapa);
	printmap(&mapa);
	struct celula* i=acesso(&mapa,11,11);
	printf("testizin : %d,%d\n", i->linha, i->coluna );
	return 0;
}
