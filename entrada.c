#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct no{
	char c;
	struct  no* prox;
	struct no* fim;
};

void inicializarfila(struct no **fila){
	(*fila)=(struct no*)malloc(sizeof(struct no));
	(*fila)->prox=NULL;
	(*fila)->fim=NULL;
}

void incluirfila(struct no **fila,char x){
	struct no* novo=malloc(sizeof(struct no));
	novo->c=x;
	novo->prox=NULL;
	if ((*fila)->fim==NULL){
		(*fila)->prox=novo;
	}else{	
		(*fila)->fim->prox=novo;
	}
	(*fila)->fim=novo;
}

void removerfila(struct no **fila){
		struct no* i=(*fila)->prox;
		(*fila)->prox=i->prox;
		free(i);
		if((*fila)->prox==NULL) (*fila)->fim=NULL;
}
int tamanhofila(struct no **fila){
	int i=0;
	struct no* it=(*fila)->prox;
	while(it!=NULL){
		i++;
		it=it->prox;
	}
	return i;
}
void percorrer(struct no **fila){
	struct no* it=(*fila)->prox;
	while(it!=NULL){
		printf("%c",it->c);
		it=it->prox;
	}
	printf("\n");
}
int validonumero(char c){
	if ((int)c>=49 && (int)c<=57){
		return 1;
	}
	return 0;
}
int validochar(char c){
	if (((int)c>=65 && (int)c<=77)||((int)c>=97 && (int)c<=108)){
		return 1;
	}
	return 0;
}
void entrada(struct no** fila){
	int ok1,ok2,ok,i;
	char *entrada=malloc(30*sizeof(char));	
	char c0,c1;
	ok=0;
	while(ok==0){		
		scanf("%[^\n]",entrada);
		getchar();
		ok1=ok2=0;
			ok=0;
		for(i=0; entrada[i]!='\0' && ok==0; i++){
			c0=entrada[i];
			if (validonumero(c0)){
				ok1=1;
				incluirfila(fila,c0);
				if(entrada[i+1]!='\0'){	
					c1=entrada[i+1];
					if ((int)c0==49 && (int)c1>=48 && (int)c1<=50){
						incluirfila(fila,c1);
						i++;		
					}
				}
				if(entrada[i+1]!='\0'){
					c1=entrada[i+1];
					if ((int)c1>=48 && (int)c1<=57){
						ok=1;
						ok1=0;
					}
				}
			}		
			
			if(validochar(c0)){
				ok2=1;
				incluirfila(fila,c0);
				if(entrada[i+1]!='\0'){
					c1=entrada[i+1];
					if (((int)c1>=65 && (int)c1<=77)||((int)c1>=97 && (int)c1<=108)){
						ok=1;
						ok2=0;
					}
				}
			}
		
			if (ok1 && ok2) {return;}
		}
		ok=0;
		printf("entrada invalida\n");
		while(tamanhofila(fila)!=0){
			removerfila(fila);
		}
	}

}


int linha(struct no** fila){
	struct no* it=(*fila)->prox;
	int num;
	while(it!=NULL){
		if(validonumero(it->c)){
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

int coluna(struct no** fila){
	struct no* it=(*fila)->prox;
	char c;
	while(it!=NULL){
		if(validochar(it->c)){
			c=it->c;
		}	
		it=it->prox;
	}
	if ((int)c>=65 && (int)c<=77)return (int)c - 65;
	else return (int)c - 97;

}


int main(){
	struct no* fila;
	inicializarfila(&fila);
	entrada(&fila);
	printf("lista: ");
	percorrer(&fila);
	int a=linha(&fila);
	int b=coluna(&fila);
	printf("coord lxc : %d,%d\n", a, b);
	return 0;
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
