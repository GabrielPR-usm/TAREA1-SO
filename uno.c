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

	char string[150];
	sprintf(string, "%s/%s", ruta, "Revelada");

	DIR* dirp;
	dirp= opendir(string);
	struct dirent *ent;

	if (dirp == NULL){
		perror("No puedo abrir el directorio");
	}

	char *revelada;

	while ((ent = readdir (dirp)) != NULL){

		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
			revelada = strtok(ent->d_name, ".");//Se imprimen cartas sin el .txt
		}
	}
	closedir(dirp);

	char *valueRevelada = strtok(revelada, "_");
	char *colorRevelada = strtok(NULL, "_");

	jugarCarta(ruta, colorRevelada, 1, 2);
	/*
	pid_t pid;
	int jugador1,jugador2,jugador3,jugador4;
	int pipe1y2[2],pipe1y3[2],pipe1y4[2],pipe2y3[2],pipe2y4[2],pipe3y4[2];
	char mensaje[100];
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

	if(jugador1==getpid()){
		printf("CACA\n");
	}
	else if(jugador2==getpid()){
	}
	else if(jugador3==getpid()){
	}
	else{
	}

*/

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
	return 0;
}
