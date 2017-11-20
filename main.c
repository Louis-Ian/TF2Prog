#include <stdio.h>
#include <stdlib.h>
#include "batalhanaval.h"

int main(){
	struct celula** mapa;
	inicializar(&mapa);
	criar(&mapa);
	mapear(&mapa);
	printmap(&mapa);
	return 0;
}
