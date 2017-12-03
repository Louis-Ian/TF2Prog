all: exe
	make limpar
	make jogar

exe: main.o batalhanaval.o
	gcc main.o batalhanaval.o -o JOGO

jogar: exe
	./JOGO

main: main.c
	gcc -c main.c -o main.o

batalhaNaval: batalhanaval.c batalhanaval.h
	gcc -c batalhanaval.c -o batalhanaval.o

limpar:
	rm *.o

desinstalar:
	rm JOGO