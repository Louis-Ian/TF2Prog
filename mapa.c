#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct celula{
	int linha;
	int coluna;
	int existe;
	char conteudo;
	struct celula* dir;
	struct celula* esq;
	struct celula* top;
	struct celula* bot; 
};
void inicializar(struct celula*** mapa){
	(*mapa)=(struct celula**)malloc(12*sizeof(struct celula*));
	for (int i = 0; i < 12; i++){
		(*mapa)[i]=NULL;
	}
}
void inserir(struct celula** lista){
	struct celula* novo=(struct celula*)malloc(sizeof(struct celula));
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

void criar(struct celula ***mapa){
	struct celula *it3;
	struct celula *it;
	struct celula *it2;
	for (int i = 0; i < 12; ++i)
	{

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
	int i=1;
	printf("  |A|B|C|D|E|F|G|H|I|J|K|L|\n");
	//printf("-------------------------\n");
	while(it!=NULL){
		if(j==0 && i<10) printf("%d ",i);
		if (j==0 && i>=10) printf("%d",i);
		printf("|%c",it->conteudo);
		if(it!=NULL) it=it->dir;
		j++;
		if(j==12){j%=12;i++;printf("|\n");}
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


int range(int i,int j){
	return i+(rand()%(j-i+1));
}

int inializarjogo(struct celula ***mapa){
	int n=9;
	int i,j,d;
	struct celula* it;
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

int main(){
	srand(time(NULL));
	struct celula** mapa;
	inicializar(&mapa);
	criar(&mapa);
	mapear(&mapa);
	inializarjogo(&mapa);
	printmap(&mapa);
	return 0;
}
