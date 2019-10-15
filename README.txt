Martin Menares Valencia
201573536-0
Gabriel Pezoa Riutor
201673562-3

Para el correcto funcionamiento del programa, solo hace falta ingresar a la carpeta del programa via terminal e ingresar el comando "Make", seguido por el comando "./uno"

El juego funciona mediante el uso de pipes entre 4 diferentes procesos. El proceso 1 funciona como orquestador de los pipes y todos los mensajes pasan por él. En cada turno, los procesos muestran la carta revelada, seguido del respectivo jugador. Este elige una de las opciones, y de ser válido cambia la última carta revelada por la nueva jugada.
Dentro de funciones.h, se puede observar, arriba de cada función, su retorno y lo que realiaz en pocas palabras. Hay funciones que sirven para crear el entorno de ejecución y las carpetas necesarias, mientras que otras serán llamadas recurrentemente durante cada turno por los procesos.
Tambien fué necesario el uso de variables en memoria compartida para poder cubrir el caso, por ejemplo de tener que guardar el color que se escoge luego de una carta negra; guardar la cantidad de cartas a robar, luego de una seguidilla de +2, etc. Estas variables son pasadas como parámetros a aquellas funciones que lo requieran.
								 
	
