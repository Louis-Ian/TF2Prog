#include <stdio.h>

#define true 1
#define false 0

struct no{
	char c;
	struct  no* prox;
	struct no* fim;
};

/* MAIN - ENTRADA
int main(){
	struct no* fila;
	inicializar_fila(&fila);
	entrada(&fila);
	printf("lista: ");
	percorrer_fila(&fila);
	int a=linha(&fila);
	int b=coluna(&fila);
	printf("coord lxc : %d,%d\n", a, b);
	return 0;
}
*/

struct celula{
	int linha;
	int coluna;
	int existe;
	struct celula* dir;
	struct celula* esq;
	struct celula* top;
	struct celula* bot; 
};

void inicializar_fila(struct no **fila);
void incluir_fila(struct no **fila,char x);
void remover_fila(struct no **fila);
int tamanho_fila(struct no **fila);
void percorrer_fila(struct no **fila);
int validar_numero(char c);
int validar_char(char c);
int linha(struct no** fila);
int coluna(struct no** fila);
void entrada(struct no** fila);
void inicializar(struct celula*** mapa);
void inserir(struct celula** lista);
void criar(struct celula*** mapa);
void mapear(struct celula*** mapa );
void printmap(struct celula*** mapa);
int jogadaRand(int i,int j);
int jogada();