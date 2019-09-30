all: uno

program: uno.c funciones.h
	gcc -Wall uno.c -o uno
