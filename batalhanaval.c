#include "batalhanaval.h"

#define true 1
#define false 0

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

void inicializar_mapa(struct celula*** mapa){
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

void criar_mapa(struct celula ***mapa){
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
		if(j==12){
			i++;
			j%=12;
		}
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

int range(int i,int j){
	return i+(rand()%(j-i+1));
}

struct celula* acesso(struct celula*** mapa,int linha, int coluna){
	struct celula* it=(*mapa)[linha];
	while(coluna>0){
		it=it->dir;
		coluna--;
	}
	return it;
}

int distribuir_embarcacoes(struct celula ***mapa){
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
				it= acesso(mapa,i,j);
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