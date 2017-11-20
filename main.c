#include <stdio.h>
#include <stdlib.h>
#include "batalhanaval.h"

int main(){
	//Precisam ser 2 tabuleiros.
	struct celula** mapa;
	inicializar(&mapa);
	criar(&mapa);
	mapear(&mapa);
	printmap(&mapa);
	
	return 0;
}
