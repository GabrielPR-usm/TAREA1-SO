#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>


const char Colors[5][8]={"Blue","Red","Green","Yellow","Black"};
const char Names[15][15]={"0","1","2","3","4","5","6","7","8","9","+2","Reverse","Jump","Change_color","+4"};

struct stat st = {0};

/*int Ncartas=108;

int SumaRobar=0;

int Nseleccionadas=0;

int OcurrenciaReverse=0;

int OcurrenciaJump=0;

char ChangeColor[15]="Sin color";*/

//Mueve carta(value) desde fichero from a to
void mover_carta(char* ruta, char* value, char* from, char* to){
	char string[150];
	sprintf(string,"mv '%s/%s/%s' %s/%s", ruta,from,value, ruta,to);
	system(string);
}
//Ver revelada
void ver_revelada(char*ruta,char*revelada,int*Nseleccionadas,int*OcurrenciaJump,int*OcurrenciaReverse,int*SumaRobar){
	char string[150];
	sprintf(string, "%s/%s", ruta, "Revelada");

	DIR* dirp;
	dirp= opendir(string);
	struct dirent *ent;

	if (dirp == NULL){
		perror("No puedo abrir el directorio");
	}


	while ((ent = readdir (dirp)) != NULL){

		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
			strcpy(revelada,strtok(ent->d_name, "."));//Se imprimen cartas sin el .txt
			char mostrada[50];
			strcpy(mostrada,revelada);
			char *valueRevelada = strtok(mostrada, "_");
			if(strcmp(valueRevelada,"+4")==0 && *Nseleccionadas==0){
				(*SumaRobar)+=4;
				}
			if(strcmp(valueRevelada,"+2")==0 && *Nseleccionadas==0){
				(*SumaRobar)+=2;
				}
			if(strcmp(valueRevelada,"Jump")==0 && *Nseleccionadas==0){
				*OcurrenciaJump=1;
				}
			if(strcmp(valueRevelada,"Reverse")==0 && *Nseleccionadas==0){
				*OcurrenciaReverse=1;
				}
		}
	}
	closedir(dirp);
	printf("Revelada: %s\n",revelada);
	return;
	}

//roba n cartas del mazo al jugador(playernumber)
void robarCartas(char *ruta, int playerNumber, int n, int *Ncartas){

	int i = 0;
	srand(time(NULL));

	char player[15];

	if( playerNumber == 5 )
		sprintf(player, "Revelada");
	else
		sprintf(player, "Jugador%d", playerNumber);

	while (i < n){

		if( *Ncartas == 0 ){
			printf("Ya no quedan mas cartas en el mazo\n");
			return;
		}

		int j = 0;
		int aleatorio = 1+rand()%(*Ncartas);

		char string[150];
		sprintf(string, "%s/%s", ruta, "Mazo");

		DIR* dirp;
		dirp= opendir(string);
		struct dirent *ent;

		if (dirp == NULL){
			perror("No puedo abrir el directorio");
		}


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

		(*Ncartas)--;
		i++;
	}
}

//Muestra por consola todas las cartas de la mano de un jugador y permite seleccionar la jugada deseada
void seleccionar_jugada(char* ruta, int jugador, char*jugada,char*revelada,char*mensaje,int*Ncartas){

	char string[150];
	sprintf(string, "%s/Jugador%d", ruta, jugador);
	int i = 1;

	DIR* dirp;
	dirp= opendir(string);
	struct dirent *ent;

	if (dirp == NULL){
		perror("No puedo abrir el directorio");
	}

	printf("\nCartas de Jugador%d\n", jugador);

	while ((ent = readdir (dirp)) != NULL){

		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
			printf("%d.- %s\n", i, ent->d_name);
			i++;
		}
	}
	
	if(i==1){
		printf("No tiene Cartas\n");
		strcpy(mensaje,"Hay Ganador");
		}
	
	if(i>1){
			int j=i;
			printf("%d.- Robar\n", i);
			closedir(dirp);

			printf("Ingresa el numero de tu jugada: ");
			scanf("%d",&i);
			
			if(j==i){
				robarCartas(ruta,jugador,1,Ncartas);
				dirp= opendir(string);
				struct dirent *ent;

				if (dirp == NULL){
					perror("No puedo abrir el directorio");
				}

				printf("\nCartas de Jugador%d\n", jugador);
				int k=1;
				while ((ent = readdir (dirp)) != NULL){

					if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
						printf("%d.- %s\n", k, ent->d_name);
						k++;
					}
				}
				printf("%d.- Paso\n",k);
				closedir(dirp);
				printf("Ingresa el numero de tu jugada: ");
				scanf("%d",&i);
				if(i==k){
					strcpy(jugada,"Paso");
					printf("Seleccionaste: %s\n",jugada);
					}
				else{
					dirp= opendir(string);
					struct dirent *ent;

					if (dirp == NULL){
						perror("No puedo abrir el directorio");
					}

					printf("\nCartas seleccionada\n");
					int k=0;
					while ((ent = readdir (dirp)) != NULL){

						if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
							k++;
							if(i==k){
								printf("%d.- %s\n", i, ent->d_name);
								strcpy(jugada,ent->d_name);
								}
						
						}
					
					}
					closedir(dirp);
				}
			}
		
			else{
				dirp= opendir(string);
				struct dirent *ent;

				if (dirp == NULL){
					perror("No puedo abrir el directorio");
				}

				printf("\nCarta seleccionada\n");
				int k=0;
				while ((ent = readdir (dirp)) != NULL){

					if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
						k++;
						if(i==k){
							printf("%d.- %s\n", i, ent->d_name);
							strcpy(jugada,ent->d_name);
							}
					
						}
					}
				closedir(dirp);
				}
			//printf("\n- Robar carta\n");
			//printf("Escriba el nombre ompleto de la carta (incluida su extensión .txt), o 'Robar' en otro caso: ");
			}
	
	return;
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
				sprintf(string,"0_%s_1",(char*)Colors[i]);
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
				sprintf(string,"+4_Black_%d",j);
				crearArchivo(string, pathMazo);
				j++;
			}

			j=1;
			while(j<5){
				sprintf(string,"ChangeColor_Black_%d",j);
				crearArchivo(string, pathMazo);
				j++;
			}
			i++;
		}


	}
	printf("Mazo creado satisfactoriamente\n");
}


//Reparte de manera aleatoria las cartas a los jugadores, moviendolas del mazo al respectivo jugador
void RepartirAleatorio(char *ruta,int*Ncartas){

	printf("REPARTIENDO\n");

	robarCartas(ruta, 1, 7,Ncartas);
	robarCartas(ruta, 2, 7,Ncartas);
	robarCartas(ruta, 3, 7,Ncartas);
	robarCartas(ruta, 4, 7,Ncartas);
	robarCartas(ruta, 5, 1,Ncartas);//Revelada
	printf("Cartas repartidas satisfactoriamente\n" );
}

//1 si es un movimiento valido, 0 si no
int movimiento_valido(char *valueRevelada, char*colorRevelada ,char *valueJugada,  char*colorJugada, char**ChangeColor){

	if( (strcmp(valueJugada, "+4") == 0) || strcmp(valueJugada, "ChangeColor") == 0)
		return 1;

	if(strcmp(valueJugada, valueRevelada) == 0 || strcmp(colorJugada, colorRevelada) == 0 || strcmp(colorJugada, *ChangeColor) == 0 )
		return 1;
	if(strcmp(*ChangeColor,"Sin color")==0 && strcmp(valueRevelada, "ChangeColor") == 0)
		return 1;
	return 0;

}

//1-4,  Cambio de color Blue, Red, Green, Yellow
void Change(char **ChangeColor){
	printf("1.- Blue\n");
	printf("2.- Red\n");
	printf("3.- Green\n");
	printf("4.- Yellow\n");
	printf("Ingresa un numero y seleciona el color: ");
	int color;
	scanf("%d",&color);
	if(color==1){
		*ChangeColor="Blue";
		}
	if(color==2){
		*ChangeColor="Red";
		}
	if(color==3){
		*ChangeColor="Green";
		}
	if(color==4){
		*ChangeColor="Yellow";
		}
	}
//Retorno para movimientos validos: 0 
//Retorno para movimiento invalido o Paso: 1
int jugarCarta(char*ruta,char*revelada ,char *jugada,char **ChangeColor,int currPlayer,int*SumaRobar,int*OcurrenciaReverse,int*Nseleccionadas,int*Ncartas){
	char carta[50];
	char remover[100];
	char currentP[15];
	
	strcpy(remover,ruta);
	sprintf(remover,"%s/Revelada/%s.txt",ruta,revelada);
	//printf("%s\n%s\n",jugada,remover);
	
	
	sprintf(currentP, "Jugador%d", currPlayer);
	
	
	char *valueRevelada = strtok(revelada, "_");
	char *colorRevelada = strtok(NULL, "_");
	
	if (strcmp(jugada,"Paso")==0){
		if(*SumaRobar!=0){
			printf("%d\n",*SumaRobar);
			robarCartas(ruta,currPlayer,*SumaRobar,Ncartas);
			*SumaRobar=0;
			printf("%d\n",*SumaRobar);
			}
		return 1;
		}
	else{
		(*Nseleccionadas)+=1;
		strcpy(carta,jugada);
		char *valueJugada = strtok(carta, "_");
		char *colorJugada = strtok(NULL, "_");
		//printf("\n%s %s %s %s\n",valueRevelada,colorRevelada,valueJugada,colorJugada);
		if(movimiento_valido(valueRevelada,colorRevelada,valueJugada,colorJugada,ChangeColor)==0){
			robarCartas(ruta,currPlayer,1,Ncartas);
			if((*SumaRobar)!=0){
				printf("%d\n",*SumaRobar);
				robarCartas(ruta,currPlayer,*SumaRobar,Ncartas);
				*SumaRobar=0;
				printf("%d\n",*SumaRobar);
				}
			return 1;
			}
		else{
			printf("%s\n%s\n",jugada,remover);
			printf("CACA\n");
			mover_carta(ruta,jugada,currentP,"Revelada");
			remove(remover);
			printf("CACA\n");
			if(strcmp(valueJugada,"ChangeColor")==0 || strcmp(valueJugada,"+4")==0){
				Change(ChangeColor);
				}
			else{
				
				strcpy(*ChangeColor,colorJugada);
				printf("%s\n",*ChangeColor);
				if(strcmp(valueJugada,"Reverse")==0){
					if(*OcurrenciaReverse==0){
						*OcurrenciaReverse=1;
						}
					else{
						*OcurrenciaReverse=0;
						}
					
					}
			
				}
			}
		return 0;	
		}
	return 1;
	
}

int N_cartas_en_mano(char*ruta, int jugador){
	char string[150];
	sprintf(string, "%s/Jugador%d", ruta, jugador);
	int i = 0;

	DIR* dirp;
	dirp= opendir(string);
	struct dirent *ent;

	if (dirp == NULL){
		perror("No puedo abrir el directorio");
	}

	while ((ent = readdir (dirp)) != NULL){

		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
			i++;
		}
	}
	closedir(dirp);
	return i;
	}
/*int jugarCarta(char *ruta, char *colorActual, int currPlayer){

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

	char revelada[30];
	char rev[30];

	while ((ent = readdir (dirp)) != NULL){

		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
			printf("ent-> %s\n", ent->d_name);
			strcpy(revelada, ent->d_name);
			strcpy(rev, ent->d_name);
		}
	}
	closedir(dirp);

	char valueRev[10];
	char colorRev[10];
	sprintf(valueRev, "%s", strtok(revelada, "_"));
	sprintf(colorRev, "%s", strtok(NULL, "_"));
	//---------------------------------------------------------//

	char choice[30];

	while(strcmp(choice, "Robar") != 0 && strcmp(choice, "robar") != 0){

		printf("revelada: %s\n", rev);
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
		printf("color actual: %s\n", colorActual);

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

			printf("Else\n" );
			printf("Antes del remove\n" );

			char rmvCard[100];
			printf("revelada: %s\n", rev);
			sprintf(rmvCard, "%s/%s", string, rev);
			int status = remove(rmvCard);

			if( status == 0 )
		        printf("%s file deleted successfully.\n",  rev);
		    else {
		        printf("\n\tUnable to delete the file");
		        perror("\n\tError");
		    }

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
}*/
