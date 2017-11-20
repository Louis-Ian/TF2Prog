#include <stdio.h>

struct celula{
	int linha;
	int coluna;
	int existe;
	struct celula* dir;
	struct celula* esq;
	struct celula* top;
	struct celula* bot; 
};

void inicializar(struct celula*** mapa);
void inserir(struct celula** lista);
void criar(struct celula*** mapa);
void mapear(struct celula*** mapa );
void printmap(struct celula*** mapa);
int jogadaRand(int i,int j);
int jogada();