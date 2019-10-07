#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>


const char Colors[5][8]={"Blue","Red","Green","Yellow","Black"};
const char Names[15][15]={"0","1","2","3","4","5","6","7","8","9","+2","Reverse","Jump","Change_color","+4"};

struct stat st = {0};

int Ncartas=108;

//Mueve carta(value) desde fichero from a to
void mover_carta(char* ruta, char* value, char* from, char* to){
	char string[150];
	sprintf(string,"mv '%s/%s/%s' %s/%s", ruta,from,value, ruta,to);
	system(string);
}

//Muestra por consola todas las cartas de la mano de (jugador)
void ver_mano(char* ruta, char* jugador){

	char string[150];
	sprintf(string, "%s/%s", ruta, jugador);

	int i = 1;

	DIR* dirp;
	dirp= opendir(string);
	struct dirent *ent;

	if (dirp == NULL){
		perror("No puedo abrir el directorio");
	}

	printf("\nCartas de %s\n", jugador);

	while ((ent = readdir (dirp)) != NULL){

		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
			printf("- %s\n", ent->d_name);
			i++;
		}
	}
	closedir(dirp);
	printf("\n- Robar carta\n");
	printf("Escriba el nombre ompleto de la carta (incluida su extensión .txt), o 'Robar' en otro caso: ");
}

//Crea las carpetas especificadas en el enunciado dentro de la carpeta JUEGO
void crearCarpetas(char *ruta){

	strcat(ruta, "/JUEGO");
	mkdir(ruta,0700);
	//Se crea carpeta JUEGO para mantener el orden

	char string[100];
	sprintf(string,"%s/Mazo",ruta);
	if(stat(string,&st)==-1){
		mkdir(string,0700);
		}
	sprintf(string,"%s/Revelada",ruta);
	if(stat(string,&st)==-1){
		mkdir(string,0700);
	}
	sprintf(string,"%s/Jugador1",ruta);
	if(stat(string,&st)==-1){
		mkdir(string,0700);
		}
	sprintf(string,"%s/Jugador2",ruta);
	if(stat(string,&st)==-1){
		mkdir(string,0700);
		}
	sprintf(string,"%s/Jugador3",ruta);
	if(stat(string,&st)==-1){
		mkdir(string,0700);
	}
	sprintf(string,"%s/Jugador4",ruta);
	if(stat(string,&st)==-1){
		mkdir(string,0700);
		}

	printf("Carpetas creadas satisfactoriamente\n");
	}

//Crea carta(path) en el fichero (directory)
void crearArchivo(char path[],char directory[]){
   /* Creación y apertura del fichero */
   char string[100];
   sprintf(string,"%s/%s.txt",directory,path);
   int fichero = open (string, O_CREAT,0644);

   /* Comprobación de errores */
   if (fichero==-1)
   {
        perror("Error al abrir fichero:");
        exit(1);
   }

   /* Escritura de la cadena */
   close(fichero);
	}

/*crea el mazo con las 108 cartas*/
void crear_mazo(char*ruta){

	crearCarpetas(ruta);
	int i=0;
	int j;
	char string[20];
	char pathMazo[100];
	sprintf(pathMazo,"%s/Mazo",ruta);

	while(i<5){

		if(strcmp((char*)Colors[i],"Yellow")==0 ||strcmp((char*)Colors[i],"Blue")==0 || strcmp((char*)Colors[i],"Green")==0 || strcmp((char*)Colors[i],"Red")==0){
			//Carta corresponde a algun color

			j=1;
			while(j<10){//numeros del 1 al 9

				sprintf(string,"%d_%s_%d",j,(char*)Colors[i],1);
				crearArchivo(string, pathMazo);

				sprintf(string,"%d_%s_%d",j,(char*)Colors[i],2);
				crearArchivo(string, pathMazo);
				j++;
			}

			j=1;
			while(j<5){//0 y +2
				sprintf(string,"0_%s",(char*)Colors[i]);
				crearArchivo(string, pathMazo);


				sprintf(string,"+2_%s_%d",(char*)Colors[i],1);
				crearArchivo(string, pathMazo);

				sprintf(string,"+2_%s_%d",(char*)Colors[i],2);
				crearArchivo(string, pathMazo);
				j++;
			}

			j=1;
			while(j<5){//jumps
				sprintf(string,"Jump_%s_%d",(char*)Colors[i],1);
				crearArchivo(string, pathMazo);

				sprintf(string,"Jump_%s_%d",(char*)Colors[i],2);
				crearArchivo(string, pathMazo);
				j++;
			}

			j=1;
			while(j<5){//reverses
				sprintf(string,"Reverse_%s_%d",(char*)Colors[i],1);
				crearArchivo(string, pathMazo);

				sprintf(string,"Reverse_%s_%d",(char*)Colors[i],2);
				crearArchivo(string, pathMazo);
				j++;
			}

			i++;
		}
		else{
			//carta es +4 o cambio de color
			j=1;
			while(j<5){
				sprintf(string,"+4_%d",j);
				crearArchivo(string, pathMazo);
				j++;
			}

			j=1;
			while(j<5){
				sprintf(string,"Change_color_%d",j);
				crearArchivo(string, pathMazo);
				j++;
			}
			i++;
		}


	}
	printf("Mazo creado satisfactoriamente\n");
}

//roba n cartas del mazo al jugador(playernumber)
void robarCartas(char *ruta, int playerNumber, int n){

	int i = 0;
	srand(time(NULL));

	char player[15];

	if( playerNumber == 5 )
		sprintf(player, "Revelada");
	else
		sprintf(player, "Jugador%d", playerNumber);

	while (i < n){

		if( Ncartas == 0 ){
			printf("Ya no quedan mas cartas en el mazo\n");
			return;
		}

		int j = 0;
		int aleatorio = 1+rand()%(Ncartas);

		char string[150];
		sprintf(string, "%s/%s", ruta, "Mazo");

		DIR* dirp;
		dirp= opendir(string);
		struct dirent *ent;

		if (dirp == NULL){
			perror("No puedo abrir el directorio");
		}

		char *revelada;

		while ((ent = readdir (dirp)) != NULL){

			if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
				if( j == aleatorio ){
					mover_carta(ruta, ent->d_name, "Mazo", player);
					break;
				}
				j++;

			}
		}
		closedir(dirp);

		Ncartas--;
		i++;
	}
}

//Reparte de manera aleatoria las cartas a los jugadores, moviendolas del mazo al respectivo jugador
void RepartirAleatorio(char *ruta){

	printf("REPARTIENDO\n");

	robarCartas(ruta, 1, 7);
	robarCartas(ruta, 2, 7);
	robarCartas(ruta, 3, 7);
	robarCartas(ruta, 4, 7);
	robarCartas(ruta, 5, 1);//Revelada

	printf("Cartas repartidas satisfactoriamente\n" );
}

//1 si es un movimiento valido, 0 si no
int movimiento_valido(char *ruta, char *newCarta, char *oldCarta){

	char card[30];
	sprintf(card, "%s", newCarta);

	printf("carta: %s\n", newCarta);

	char *valueCarta = strtok(card, "_");
	char *colorCarta = strtok(NULL, "_");

	printf("value carta: %s\n", valueCarta);
	printf("color carta: %s\n", colorCarta);

	if( (strcmp(valueCarta, "+4") == 0) || strcmp(valueCarta, "Change") == 0 )
		return 1;



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



	if(strcmp(valueCarta, valueRevelada) == 0 || strcmp(colorCarta, colorRevelada) == 0)
		return 1;

	return 0;

}

//1-4,  Cambio de color Blue, Red, Green, Yellow
//5-8,	color mas Salto de jugador(salto, +2, +4)
//9-12, color mas Cambio de sentido
int jugarCarta(char *ruta, char *colorActual, int currPlayer, int nextPlayer){

	char nextP[15];
	sprintf(nextP, "Jugador%d", nextPlayer);

	char currentP[15];
	sprintf(currentP, "Jugador%d", currPlayer);
	
	//-------------------EXTRAE CARTA REVELADA------------------//
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

	char *valueRev = strtok(revelada, "_");
	char *colorRev = strtok(NULL, "_");
	//---------------------------------------------------------//

	char choice[30];

	while(strcmp(choice, "Robar") != 0 && strcmp(choice, "robar") != 0){

		printf("Carta Revelada: %s_%s.png\n", valueRev, colorRev);

		ver_mano(ruta, currentP);
		scanf("%s", choice);

		//----------------------EXTRAE CARTA NUEVA------------------//
		char *card = strtok(choice, ".");

		char *valueCarta = strtok(card, "_");
		char *colorCarta = strtok(NULL, "_");
		//---------------------------------------------------------//

		printf("\nCOMPARANDO\n");
		printf("REV value: %s\nREV color: %s\n", valueRev, colorRev);
		printf("NEW value: %s\nNEW color: %s\n", valueCarta, colorCarta);

		if( (strcmp(valueCarta, valueRev) != 0) && (strcmp(colorCarta, colorActual) != 0) ){

			if( (strcmp(valueCarta, "+4") == 0) || strcmp(valueCarta, "Change") == 0 ){


				printf("Antes del remove\n" );

				char rmvCard[40];
				sprintf(rmvCard, "%s/%s.txt", string, revelada);
				int status = remove(rmvCard);

				printf("Despues del remove\n" );

				mover_carta(ruta, choice, currentP, "Revelada");

				int newColor;
				int poder = 0;

				printf("Color: \n");
				printf("1.- Blue\n");
				printf("2.- Red\n");
				printf("3.- Green\n");
				printf("4.- Yellow\n");
				printf("Elija un numero: \n");
				scanf("%d", &newColor);

				if(strcmp(valueCarta, "+4") == 0){
					robarCartas(ruta, nextPlayer, 4);
					poder = 4;
				}


				return newColor + poder;
			}

			printf("No es posible jugar esta carta, intenta con otra\n\n\n\n" );
		}
		else{//movimiento valido
			printf("Antes del remove\n" );
			char rmvCard[40];
			sprintf(rmvCard, "%s/%s.txt", string, revelada);
			int status = remove(rmvCard);

			printf("Despues del remove\n" );

			mover_carta(ruta, choice, currentP, "Revelada");

			int poder = 0;//4, salto/8, reverse

			if( strcmp(valueCarta, "+2") ){
				poder = 4;
				robarCartas(ruta, nextPlayer, 2);
			}
			else if( strcmp(valueCarta, "Reverse") )
				poder = 8;
			else if( strcmp(valueCarta, "Jump") ){
				poder = 4;
			}

			if( strcmp(colorCarta, "Blue") == 0 )
				return 1+poder;
			else if( strcmp(colorCarta, "Red") == 0 )
				return 2+poder;
			else if( strcmp(colorCarta, "Green") == 0 )
				return 3+poder;
			else if( strcmp(colorCarta, "Yellow") == 0 )
				return 4+poder;

		}

	}
	return 0;
}
