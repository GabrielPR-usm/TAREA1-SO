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
	//int num12,num13,num14,num23,num24,num34;	
	char mensaje12[10],mensaje13[10],mensaje14[10],mensaje23[10],mensaje24[10],mensaje34[10];
	int pipe12[2],pipe13[2],pipe14[2],pipe23[2],pipe24[2],pipe34[2];
	
	pipe(pipe12);
	pipe(pipe13);
	pipe(pipe14);
	pipe(pipe23);
	pipe(pipe24);
	pipe(pipe34);

	jugador1=getpid();
	printf("%d\n", getpid());
	pid = fork();

	if(pid==0){
		jugador2=getpid();
		//printf("%d\n", getpid());

	}
	if (pid>0){
    	pid=fork();

    	if(pid==0){
			jugador3=getpid();
			//printf("%d\n", getpid());
		}
		if (pid>0){
			pid=fork();

			if(pid==0){
				jugador4=getpid();
				//printf("%d\n", getpid());
			}
		}
	}
	char mensaje[50]="TURNO1";
	char revelada[50];
	char jugada[50];
	int mov_valido;
	char valueRevelada[20];
	char valueJugada[20];
	
	if(jugador1==getpid()){
		
		//printf("CACA\n");

			while(strcmp(mensaje,"Hay Ganador")!=0){
				
				/*memset(mensaje12,'\0',10);
				read(pipe12[0],mensaje12, sizeof(mensaje12));
				memset(mensaje13,'\0',10);
				read(pipe12[0],mensaje13, sizeof(mensaje13));
				memset(mensaje14,'\0',10);
				read(pipe14[0],mensaje14, sizeof(mensaje14));
				memset(mensaje23,'\0',10);
				read(pipe23[0],mensaje23, sizeof(mensaje23));
				memset(mensaje24,'\0',10);
				read(pipe24[0],mensaje24, sizeof(mensaje24));
				memset(mensaje34,'\0',10);
				read(pipe34[0],mensaje34, sizeof(mensaje34));*/
				
				if(strcmp(mensaje12,"TURNO1")==0 || strcmp(mensaje13,"TURNO1")==0
				 || strcmp(mensaje14,"TURNO1")==0 || strcmp(mensaje23,"TURNO1")==0 
				 || strcmp(mensaje24,"TURNO1")==0 || strcmp(mensaje34,"TURNO1")==0){
					 
					 strcpy(mensaje,"TURNO1");
					 
					}
				
				if(Ncartas==0 || strcmp(mensaje,"Hay Ganador")==0){
					break;
					}
				if(strcmp(mensaje,"TURNO1")==0){
					printf("CACA\n");
						//printf("%d\n",Ncartas);
						ver_revelada(ruta,revelada);
						strcpy(valueRevelada,revelada);
						strcpy(valueRevelada,strtok(valueRevelada,"_"));
						printf("%s\n",valueRevelada);
						printf("%d %d\n",OcurrenciaJump,OcurrenciaReverse);
						if(strcmp(valueRevelada,"Jump")==0 && OcurrenciaJump==1 && Nseleccionadas==0){//FUNCIONA
								
							OcurrenciaJump=0;
							memset(mensaje12,'\0',10);
							write(pipe12[1],"TURNO2",6);
							strcpy(mensaje,"TURNO2");
							printf("caca");
							continue;
								
							}
							
						if(strcmp(valueRevelada,"Reverse")==0 && OcurrenciaReverse==1 && Nseleccionadas==0){//FUNCIONA
							
							memset(mensaje14,'\0',10);
							write(pipe14[1],"TURNO4",6);
							strcpy(mensaje,"TURNO4");
							printf("caca");
							continue;
							
							}
							
						printf("%s\n",ChangeColor);
						seleccionar_jugada(ruta,1,jugada,revelada,mensaje);
						if (strcmp(mensaje,"Hay Ganador")!=0){
							//printf("\n%s %s\n",jugada,revelada);
							mov_valido = jugarCarta(ruta,revelada, jugada,ChangeColor,1);
							
							strcpy(valueJugada,strtok(jugada,"_"));
							
							/*if(mov_valido==0){
								
									if(strcmp(valueJugada,"Jump")==0){
											
											memset(mensaje13,'\0',10);
											write(pipe13[1],"TURNO3",6);
											strcpy(mensaje,"TURNO3");
											continue;
										}
									
									if(OcurrenciaReverse==0){
										
										if(strcmp(valueJugada,"Reverse")==0){
											
											memset(mensaje14,'\0',10);
											write(pipe14[1],"TURNO4",6);
											strcpy(mensaje,"TURNO4");
											continue;
										}
										if(strcmp(valueJugada,"+4")==0){
											
											SumaRobar+=4;
											memset(mensaje12,'\0',10);
											write(pipe12[1],"TURNO2",6);
											strcpy(mensaje,"TURNO2");
											continue;
										}
										if(strcmp(valueJugada,"+2")==0){
											SumaRobar+=2;
											memset(mensaje12,'\0',10);
											write(pipe12[1],"TURNO2",6);
											strcpy(mensaje,"TURNO2");
											continue;
										}
										else{
											
											memset(mensaje12,'\0',10);
											write(pipe12[1],"TURNO2",6);
											strcpy(mensaje,"TURNO2");
											continue;
										}
									}
									
									if(OcurrenciaReverse==1){
										
										if(strcmp(valueJugada,"Reverse")==0){
											
											memset(mensaje12,'\0',10);
											write(pipe12[1],"TURNO2",6);
											strcpy(mensaje,"TURNO2");
											continue;
										}
										if(strcmp(valueJugada,"+4")==0){
											
											SumaRobar+=4;
											memset(mensaje14,'\0',10);
											write(pipe14[1],"TURNO4",6);
											strcpy(mensaje,"TURNO4");
											continue;
										}
										if(strcmp(valueJugada,"+2")==0){
											SumaRobar+=2;
											memset(mensaje14,'\0',10);
											write(pipe14[1],"TURNO4",6);
											strcpy(mensaje,"TURNO4");
											continue;
										}
										else{
											
											memset(mensaje14,'\0',10);
											write(pipe14[1],"TURNO4",6);
											strcpy(mensaje,"TURNO4");
											continue;
										}
										
									}
									
							}
							else{
									if(OcurrenciaReverse==0){
										
											memset(mensaje12,'\0',10);
											write(pipe12[1],"TURNO2",6);
											strcpy(mensaje,"TURNO2");
											continue;
										
										}
									if(OcurrenciaReverse==1){
										
											memset(mensaje14,'\0',10);
											write(pipe14[1],"TURNO4",6);
											strcpy(mensaje,"TURNO4");
											continue;
										}
							}*/
							//jugar carta
							//esperar
						}				
				}
			}
			if(N_cartas_en_mano(ruta,1)==0){
				printf("EL jugador 1 es el GANADOR\n");
			}
			if(Ncartas==0){
				printf("Se han acabado las cartas, esto es un EMPATE\n");
			}
	}
	if(jugador2==getpid()){
		
			while(strcmp(mensaje,"Hay Ganador")!=0){
				
				/*memset(mensaje12,'\0',10);
				num12=read(pipe12[0],mensaje12, sizeof(mensaje12));
				memset(mensaje13,'\0',10);
				num13=read(pipe12[0],mensaje13, sizeof(mensaje13));
				memset(mensaje14,'\0',10);
				num14=read(pipe14[0],mensaje14, sizeof(mensaje14));
				memset(mensaje23,'\0',10);
				num23=read(pipe23[0],mensaje23, sizeof(mensaje23));
				memset(mensaje24,'\0',10);
				num24=read(pipe24[0],mensaje24, sizeof(mensaje24));
				memset(mensaje34,'\0',10);
				num34=read(pipe34[0],mensaje34, sizeof(mensaje34));*/
				
				if(strcmp(mensaje12,"TURNO2")==0 || strcmp(mensaje13,"TURNO2")==0
				 || strcmp(mensaje14,"TURNO2")==0 || strcmp(mensaje23,"TURNO2")==0 
				 || strcmp(mensaje24,"TURNO2")==0 || strcmp(mensaje34,"TURNO2")==0){
					 
					 strcpy(mensaje,"TURNO2");
					 
					}
				
				if(Ncartas==0 || strcmp(mensaje,"Hay Ganador")==0){
					break;
					}
				if(strcmp(mensaje,"TURNO2")==0){
						//printf("%d\n",Ncartas);
						ver_revelada(ruta,revelada);
						
						printf("%s\n",ChangeColor);
						seleccionar_jugada(ruta,2,jugada,revelada,mensaje);
						if (strcmp(mensaje,"Hay Ganador")!=0){
							//printf("\n%s %s\n",jugada,revelada);
							mov_valido = jugarCarta(ruta,revelada, jugada,ChangeColor,2);
							//jugar carta
							//esperar
						}
				}
				
			}
			if(N_cartas_en_mano(ruta,2)==0){
				printf("EL jugador 2 es el GANADOR");
			}
	}
	if(jugador3==getpid()){
		
			while(strcmp(mensaje,"Hay Ganador")!=0){
				
				/*memset(mensaje12,'\0',10);
				num12=read(pipe12[0],mensaje12, sizeof(mensaje12));
				memset(mensaje13,'\0',10);
				num13=read(pipe12[0],mensaje13, sizeof(mensaje13));
				memset(mensaje14,'\0',10);
				num14=read(pipe14[0],mensaje14, sizeof(mensaje14));
				memset(mensaje23,'\0',10);
				num23=read(pipe23[0],mensaje23, sizeof(mensaje23));
				memset(mensaje24,'\0',10);
				num24=read(pipe24[0],mensaje24, sizeof(mensaje24));
				memset(mensaje34,'\0',10);
				num34=read(pipe34[0],mensaje34, sizeof(mensaje34));*/
				
				if(strcmp(mensaje12,"TURNO3")==0 || strcmp(mensaje13,"TURNO3")==0
				 || strcmp(mensaje14,"TURNO3")==0 || strcmp(mensaje23,"TURNO3")==0 
				 || strcmp(mensaje24,"TURNO3")==0 || strcmp(mensaje34,"TURNO3")==0){
					 
					 strcpy(mensaje,"TURNO3");
					 
					}
				
				if(Ncartas==0 || strcmp(mensaje,"Hay Ganador")==0){
					break;
					}
				if(strcmp(mensaje,"TURNO3")==0){
						//printf("%d\n",Ncartas);
						ver_revelada(ruta,revelada);
						
						printf("%s\n",ChangeColor);
						seleccionar_jugada(ruta,3,jugada,revelada,mensaje);
						if (strcmp(mensaje,"Hay Ganador")!=0){
							//printf("\n%s %s\n",jugada,revelada);
							mov_valido = jugarCarta(ruta,revelada, jugada,ChangeColor,3);
							//jugar carta
							//esperar
						}
				}
				
			}			
			if(N_cartas_en_mano(ruta,3)==0){
				printf("EL jugador 3 es el GANADOR");
			}
	}
	if(jugador4==getpid()){
		
			while(strcmp(mensaje,"Hay Ganador")!=0){
				
				/*memset(mensaje12,'\0',10);
				num12=read(pipe12[0],mensaje12, sizeof(mensaje12));
				memset(mensaje13,'\0',10);
				num13=read(pipe12[0],mensaje13, sizeof(mensaje13));
				memset(mensaje14,'\0',10);
				num14=read(pipe14[0],mensaje14, sizeof(mensaje14));
				memset(mensaje23,'\0',10);
				num23=read(pipe23[0],mensaje23, sizeof(mensaje23));
				memset(mensaje24,'\0',10);
				num24=read(pipe24[0],mensaje24, sizeof(mensaje24));
				memset(mensaje34,'\0',10);
				num34=read(pipe34[0],mensaje34, sizeof(mensaje34));*/
				
				if(strcmp(mensaje12,"TURNO4")==0 || strcmp(mensaje13,"TURNO4")==0
				 || strcmp(mensaje14,"TURNO4")==0 || strcmp(mensaje23,"TURNO4")==0 
				 || strcmp(mensaje24,"TURNO4")==0 || strcmp(mensaje34,"TURNO4")==0){
					 
					 strcpy(mensaje,"TURNO4");
					 
					}
				
				if(Ncartas==0 || strcmp(mensaje,"Hay Ganador")==0){
					break;
					}
				if(strcmp(mensaje,"TURNO4")==0){
						//printf("%d\n",Ncartas);
						ver_revelada(ruta,revelada);
						
						printf("%s\n",ChangeColor);
						seleccionar_jugada(ruta,4,jugada,revelada,mensaje);
						if (strcmp(mensaje,"Hay Ganador")!=0){
							//printf("\n%s %s\n",jugada,revelada);
							mov_valido = jugarCarta(ruta,revelada, jugada,ChangeColor,4);
							//jugar carta
							//esperar
						}
				}
				
			}
			if(N_cartas_en_mano(ruta,4)==0){
				printf("EL jugador 4 es el GANADOR");
			}
	}
	close(pipe12[0]);
	close(pipe12[1]);
	
	close(pipe13[0]);
	close(pipe13[1]);
	
	close(pipe14[0]);
	close(pipe14[1]);
	
	close(pipe23[0]);
	close(pipe23[1]);
	
	close(pipe24[0]);
	close(pipe24[1]);
	
	close(pipe34[0]);
	close(pipe34[1]);
	
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
