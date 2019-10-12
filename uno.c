#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include "funciones.h"

int main(){

	char ruta[100];
	getcwd(ruta, sizeof(ruta));//current work directory

	//printf("Antes de comezar escriba la ruta de accesso hasta la carpeta TAREA1_SO_2019_2 que contiene el juego -> ");
	//scanf("%s",ruta);

	printf("\nBienvenido a UNO, que comienze el Juego!\n");
	crear_mazo(ruta);
	RepartirAleatorio(ruta);



	
	pid_t pid;
	int jugador1,jugador2,jugador3,jugador4;
	int pipe1y2[2],pipe1y3[2],pipe1y4[2],pipe2y3[2],pipe2y4[2],pipe3y4[2];
	
	pipe(pipe1y2);

	jugador1=getpid();
	printf("%d\n", getpid());
	pid = fork();

	if(pid==0){
		jugador2=getpid();
		printf("%d\n", getpid());

	}
	if (pid>0){
    	pid=fork();

    	if(pid==0){
			jugador3=getpid();
			printf("%d\n", getpid());
		}
		if (pid>0){
			pid=fork();

			if(pid==0){
				jugador4=getpid();
				printf("%d\n", getpid());
			}
		}
	}
	sleep(5);
	char mensaje[100]="Sin ganador";
	char revelada[50];
	char jugada[50];
	if(jugador1==getpid()){
		while(strcmp(mensaje,"Hay Ganador")!=0){
			//printf("%d\n",Ncartas);
			ver_revelada(ruta,revelada);
			printf("%s\n",ChangeColor);
			seleccionar_jugada(ruta,1,jugada,revelada,mensaje);
			if (strcmp(mensaje,"Hay Ganador")!=0){
				//printf("\n%s %s\n",jugada,revelada);
				jugarCarta(ruta,revelada, jugada,ChangeColor,1);
				//jugar carta
				//esperar
			}
		printf("EL jugador 1 es el GANADOR");
		}
	}
	if(jugador2==getpid()){
		while(strcmp(mensaje,"Hay Ganador")!=0){
			//printf("%d\n",Ncartas);
			ver_revelada(ruta,revelada);
			printf("%s\n",ChangeColor);
			seleccionar_jugada(ruta,2,jugada,revelada,mensaje);
			if (strcmp(mensaje,"Hay Ganador")!=0){
				//printf("\n%s %s\n",jugada,revelada);
				jugarCarta(ruta,revelada, jugada,ChangeColor,1);
				//jugar carta
				//esperar
			}
		printf("EL jugador 2 es el GANADOR");
		}
	}
	if(jugador3==getpid()){
		while(strcmp(mensaje,"Hay Ganador")!=0){
			//printf("%d\n",Ncartas);
			ver_revelada(ruta,revelada);
			printf("%s\n",ChangeColor);
			seleccionar_jugada(ruta,3,jugada,revelada,mensaje);
			if (strcmp(mensaje,"Hay Ganador")!=0){
				//printf("\n%s %s\n",jugada,revelada);
				jugarCarta(ruta,revelada, jugada,ChangeColor,1);
				//jugar carta
				//esperar
			}
		printf("EL jugador 3 es el GANADOR");
		}
	}
	if(jugador4==getpid()){
		while(strcmp(mensaje,"Hay Ganador")!=0){
			//printf("%d\n",Ncartas);
			ver_revelada(ruta,revelada);
			printf("%s\n",ChangeColor);
			seleccionar_jugada(ruta,4,jugada,revelada,mensaje);
			if (strcmp(mensaje,"Hay Ganador")!=0){
				//printf("\n%s %s\n",jugada,revelada);
				jugarCarta(ruta,revelada, jugada,ChangeColor,1);
				//jugar carta
				//esperar
			}
		printf("EL jugador 4 es el GANADOR");
		}
	}

	return 0;
}

/*	pid_t pid;
	char mensaje[100];
	int num;
	int pipe1y2[2];
	pipe(pipe1y2);
	if(pid==0){
		close(pipe1y2[0]);
		write(pipe1y2[1],"abcde",5);
		write(pipe1y2[1],"abcdeSDFSD",10);

		exit(0);
		}
	else if(pid==-1){
		printf("Error, no se pudo crear el proceso\n");
		}
	else{
		close(pipe1y2[1]);
		num = read(pipe1y2[0],mensaje, sizeof(mensaje));
		printf("Padre lee %d bytes: %s \n",num,mensaje);
		memset(mensaje,'\0',100);
		num = read(pipe1y2[0],mensaje, sizeof(mensaje));
		printf("Padre lee %d bytes: %s \n",num,mensaje);
		close(pipe1y2[0]);
		}
*/
