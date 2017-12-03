#include <stdio.h>
#include <stdlib.h>
#include "batalhanaval.h"

int main(){
	struct celula** mapaJogador;
	struct celula** mapaPC;
	inicializar_mapa(&mapaJogador);
	inicializar_mapa(&mapaPC);
	criar_mapa(&mapaJogador);
	criar_mapa(&mapaPC);
	mapear(&mapaJogador);
	mapear(&mapaPC);
	printmap(&mapaJogador);
	printmap(&mapaPC);
	
	return 0;
}
