all: program

program: uno.c funciones.h
	gcc -Wall uno.c -o program
