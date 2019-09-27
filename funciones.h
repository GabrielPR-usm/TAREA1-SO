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

typedef struct Cartas{
	char name[30];
	struct Cartas *next;
}Carta;

struct stat st = {0};

int Ncartas=108;

Carta *iniciarListaMazo(){

	Carta *C =(Carta*) malloc(sizeof(Carta));
	strcpy(C->name,"Uno");
	C->next=NULL;
	return C;
}

void addCarta(Carta *base,char*archivo){
	int i=0;

	Carta *nuevo =(Carta*)malloc(sizeof(Carta));
	strcpy(nuevo->name,archivo);
	nuevo->next=NULL;

	Carta *aux=base;
	if(aux->next==NULL){
		base->next=nuevo;
		}
	else{
		//printf("%s\n",base->name);
		while(aux->next!=NULL){
			aux=aux->next;
			//printf("%s\n",aux->name);
			i++;
			}
		aux->next=nuevo;
		i++;
		//printf("%d\n",i);
	}

}

void mover_carta(char* ruta, char* value, char* from, char* to){
	char string[150];
	sprintf(string,"mv '%s/%s/%s' %s/%s", ruta,from,value, ruta,to);
	system(string);
}

char *eliminar_carta_del_mazo(Carta *base,int aleatorio,char*archivo){
	int i=1;
	Carta *ant=base;
	Carta *aux=base->next;
	if(aux->next==NULL){
		printf("El juego ha finalizado, no quedan cartas en el Mazo");
		return base->name;
		}
	else{
		//printf("%s\n",base->name);
		while(aux!=NULL && i<aleatorio){
			ant=ant->next;
			aux=aux->next;
			//printf("%s\n",aux->name);
			i++;
		}
		ant->next=aux->next;
		strcpy(archivo,aux->name);
		free(aux);
		return archivo;
	}
}

void ver_mano(char* ruta, char* jugador){

	char string[150];
	sprintf(string, "%s/%s", ruta, jugador);

	DIR* dirp;
	dirp= opendir(string);
	struct dirent *ent;

	if (dirp == NULL){
		perror("No puedo abrir el directorio");
	}

	printf("\n||||Cartas de %s\n", jugador);

	while ((ent = readdir (dirp)) != NULL){

		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
			char *token = strtok(ent->d_name, ".");//Se imprimen cartas sin el .txt
			printf("||||%s\n", token);
		}
	}
	closedir(dirp);
}

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

void RepartirAleatorio(char *ruta){

	char pathMazo[100];
	sprintf(pathMazo,"%s/Mazo",ruta);

	DIR* dirp;
	dirp= opendir(pathMazo);
	struct dirent *ent;

	int i=1;
	char archivo[30];
	char *repartido;
	Carta *base=iniciarListaMazo();
	srand(time(NULL));
	int aleatorio;
	//printf("%s\n",base->name);
	//char string[150];
	/* Miramos que no haya error */
    if (dirp == NULL){
		perror("No puedo abrir el directorio");
	}

    /* Una vez nos aseguramos de que no hay error, ¡vamos a jugar! */
    /* Leyendo uno a uno todos los archivos que hay */
    while ((ent = readdir (dirp)) != NULL){
	    /* Nos devolverá el directorio actual (.) y el anterior (..), como hace ls */
		if ( (strcmp(ent->d_name, ".")!=0) && (strcmp(ent->d_name, "..")!=0) ){
			  strcpy(archivo,ent->d_name);
			  //printf("%d-> %s\n", i, archivo);
			  addCarta(base,archivo);
			}
	}
	closedir(dirp);
	printf("REPARTIENDO\n");
	while (i<30){
		aleatorio = 1+rand()%(Ncartas);

		repartido = eliminar_carta_del_mazo(base,aleatorio,archivo);
		dirp= opendir(pathMazo);

		while ((ent = readdir (dirp)) != NULL){
			if (strcmp(ent->d_name,repartido)==0){

				if(0<i && i<8){
					mover_carta(ruta, repartido, "Mazo", "Jugador1");
				}
				if(7<i && i<15){
				  	mover_carta(ruta, repartido, "Mazo", "Jugador2");
			  	}
			 	if(14<i && i<22){
					mover_carta(ruta, repartido, "Mazo", "Jugador3");
				}
		  		if(21<i && i<29){
			  		mover_carta(ruta, repartido, "Mazo", "Jugador4");
		  		}
			  	if(i==29){
				  	mover_carta(ruta, repartido, "Mazo", "Revelada");
		  		}

			}
		}
		closedir(dirp);
		Ncartas--;
		i++;
	}
	printf("Cartas repartidas satisfactoriamente\n" );

}
