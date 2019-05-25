/*Grupo: El compilado.
Integrantes: Hourcade, Geronimo && Flores Wittich, Pablo && Farber, Juan.
Tutor: Younes, Jose.
Enunciado: Se desea llevar el registro del estado de las máquinas del gabinete de computación. Para
esto se debe almacenar
--->Numero de identificacion
--->Marca
--->estado. El estado de una máquina puede ser (a)FUNCIONADO, (b)HARDWARE,
(c)SOFTWARE, para identificar cuál es el inconveniente existente.
El gabinete cuenta con 40 equipos. Se solicita generar un programa con un menú con las
siguientes opciones:
1. Alta de un nuevo equipo.
2. Mostrar la lista de máquinas del gabinete
3. Mostrar la lista de máquinas agrupadas por estado.
4.Dar de baja un equipo, sin eliminarlo del archivo, buscando por número de
identificación.
5. Salir.*/
#include <unistd.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TAM 40						//Definimos TAM para modificar los valores facilmente en caso de necesitarlo.

typedef struct
{
	char marca[30];
	char estado[15];
	int numero_identificacion;
}maquina;


void apertura(char archivo[TAM]);  //Funcion para crear el archivo.
maquina ingresarmaquina(char archivo[TAM]);			  //Funcion para ingresar los datos de nuestra estructura.
void mostrarmaquina(maquina compu);	//Funcion para mostrar la lista de registros.
void escrituramaquina(char archivo[TAM]);	//Funcion para escribir nuestro archivo.
void lecturamaquina(char archivo[TAM]);	//Funcion para leer nuestro archivo.
void orden_estado(char archivo[TAM]);		//Funcion para ordenar nuestros registros por estado.
void baja_maquina (char archivo[TAM]);		//Funcion para dar de baja una maquina sin eliminarla de nuestro archivo.
void recuperar_maquina (char archivo[TAM]);		//Funcion para recuperar una maquina previamente dada de baja en nuestro archivo.

int main()
{
	int salir=0;
	int opcion;
	char archivo[]="maquinas.txt";
	printf("\n\n\t\tBienvenido!");
		system ("clear");
		while(salir==0){
			do{
				printf("%C[%dm\n\tMENU\n\n",0x1B,36);			//Usamos el color violeta para escribir en la terminal.
				printf("1. Alta de un nuevo equipo.\n");
				printf("2. Mostrar la lista de maquinas ingresadas.\n");
				printf("3. Mostrar lista de maquinas agrupadas por estado.\n");
				printf("4. BAJA, buscando por numero de identificacion.\n");
				printf("5. RECUPERAR MAQUINA, buscando por numero de identificacion.\n");
				printf("6. Salir del programa\n\n");
				printf("-Ingrese una opcion: ");
				scanf("%d",&opcion);
				getchar();
				if(opcion<1 || opcion>6)
					printf("\n\n\tERROR. Ingrese una opcion valida.\n\n");
				}while (opcion<1 || opcion>6);
		printf("\n\n");
		apertura(archivo);				//Creamos el archivo.
		switch (opcion)
		{
			case 1:
					system("clear");
					escrituramaquina(archivo);			//Pide los datos de una nueva maquina.					
					break;
			case 2:
					system("clear");
					lecturamaquina(archivo);	//Funcion para mostrar registros.
					break;
			case 3:
					system("clear");
					orden_estado(archivo);		//Ordenamos por estado.
					break;
			case 4:
					system("clear");
					baja_maquina(archivo);		//Baja de maquina mediante su numero de identificacion.
					break;
			case 5:
					system("clear");
					recuperar_maquina(archivo);		//Alta de maquina mediante su numero de identificacion.
					break;
			case 6:
					system("clear");
					printf("\nMuchas gracias por usar nuestra plataforma.\n\n");
					salir=1;
					break;
		}
	}
}

void apertura(char archivo[TAM]){
FILE *p;
p=fopen(archivo,"rb");

if(p==NULL){
	printf("El archivo no existe. Se intentara crear. \n\n");
	p=fopen(archivo,"w");
	}																//Funcion para crear el archivo.
if(p==NULL){
	printf("El archivo no se pudo crear. Hasta luego. \n\n");
	exit(0);	
	}
fclose(p);
}

void escrituramaquina(char archivo[TAM])
{
	maquina compu;
	FILE *p;
	p=fopen(archivo,"ab");
	compu=ingresarmaquina(archivo);
	fwrite(&compu,sizeof(compu),1,p);		//Funcion para escribir nuestro archivo.
	fclose(p);									
	return ;
}


maquina ingresarmaquina(char archivo[TAM])
{
	FILE *p;
	p=fopen(archivo,"r+b");
	maquina maq1,compu;
	int eleccion, bandera;
	printf("-Ingrese la marca: ");
	fgets(maq1.marca,50,stdin);								//Funcion para ingresar los datos de nuestra estructura.
	maq1.marca[strlen(maq1.marca)-1]='\0';
	printf("\nEstado:\n\n");
	printf("\t\t1: Problema de SOFTWARE\n");
	printf("\t\t2: Problema de HARDWARE\n"); 	//Eleccion segun los tres estados posibles de una maquina.
	printf("\t\t3: FUNCIONANDO\n\n");
	printf("-Ingrese su eleccion: ");
	do
	{
		scanf("%d",&eleccion);
		if(eleccion<1 || eleccion>3)
				{
					printf("\nError. Ingrese opcion valida.");		//Control de eleccion correcta
					printf("\n-Ingrese su eleccion: ");
				}
	}while(eleccion>3 || eleccion<1);
	if(eleccion==1)
	{
		strcpy(maq1.estado,"SOFTWARE");
	}
	if(eleccion==2)
	{
		strcpy(maq1.estado,"HARDWARE");		
	}
	if(eleccion==3)				//Usamos la funcion strcpy para que estado tome la cadena correspondiente a la eleccion.
	{
		strcpy(maq1.estado,"FUNCIONANDO");
	}

	do
	{
		printf("-Ingrese el numero de identificacion: ");
		scanf("%d",&maq1.numero_identificacion);
		getchar();
		bandera=2;
		if(maq1.numero_identificacion<1 || maq1.numero_identificacion>TAM)
		{
			bandera=0;				//Control para que las maquinas no excedan el limite permitido.
			printf("\n Error. Solo hay %d maquinas. Reingrese su valor. Solo se admiten numeros.\n",TAM);
		}															
		fread(&compu,sizeof(compu),1,p);
		while(feof(p)==0)	
		{
			if(compu.numero_identificacion==maq1.numero_identificacion)
			{
				bandera=1;
			}
			fread(&compu,sizeof(compu),1,p);
		}
		rewind(p);
		if(bandera==1)
		{
			printf("\nID erroneo. Recuerde solo ingresar numeros no repetidos.\n");			
		}
										//Controlamos que no se pueda ingresar un ID repetido.
	}while(bandera!=2);
	return maq1;
}

void lecturamaquina(char archivo[TAM])
{
	FILE *p;
	p=fopen(archivo,"rb");			//Se accede a nuestro archivo para realizar la lectura.
	maquina compu;	
	int bandera=0;
	fread(&compu,sizeof(compu),1,p);
	if(feof(p)!=0)
	{								
		printf("\nNo se ingresaron maquinas.\n");	
	}		
	else												//Deben ingresarse maquinas previamente para poder acceder al listado.
	{			
		while(feof(p)==0)
		{
			if(strcmp(compu.estado,"BAJA")!=0)
			{
				bandera=1;
			}
			fread(&compu,sizeof(compu),1,p);
		}	
	rewind(p);
	if(bandera==1)
	{
		printf("Las maquinas ingresadas son: \n\n");
		printf("MARCA:");
		printf("\t\t\t\tESTADO:");		
		printf("\t\t\t\tNUMERO ID:\n");
		do
		{
			fread(&compu,sizeof(compu),1,p);
			if(feof(p)==0)
			{
				if(strcmp(compu.estado,"BAJA")!=0)	//Usamos la funcion strcmp para no mostrar los registros dados de BAJA.
				{		
					printf("\n");
					mostrarmaquina(compu);
				}
			}
		}while(feof(p)==0);
	}
		else			//No se podra mostrar la lista cuando las maquinas esten dadas de baja.
		{				
			printf("\nTodas las maquinas estan dadas de BAJA.\n\n");
		}
	}
	fclose(p);
	return;
}

void mostrarmaquina(maquina compu)
{
	printf("%s",compu.marca);
	printf("\t\t\t\t%s",compu.estado);		//Mostramos nuestros registros.
	printf("\t\t\t\t%d\n",compu.numero_identificacion);
	return;
}

void orden_estado(char archivo[TAM])
{
	FILE *p;
	int bandera=0;
	maquina compu;
	p=fopen(archivo,"rb");
	long i,e;
	fread(&compu,sizeof(compu),1,p);
	if(feof(p)!=0)									//Deben ingresarse maquinas previamente para poder acceder al listado.
	{
		printf("\nNo se ingresaron maquinas.\n");
	}	
	else
	{			
		while(feof(p)==0)
		{
			if(strcmp(compu.estado,"BAJA")!=0)
			{
				bandera=1;
			}
			fread(&compu,sizeof(compu),1,p);
			if(strcmp(compu.estado,"BAJA")==0)
			{
				bandera=2;
			}
		}
	}	
	rewind(p);
	if(bandera==2)					//No se podra mostrar la lista cuando todas las maquinas esten dadas de BAJA.
	{
		printf("\nTodas las maquinas estan dadas de BAJA.\n\n");
	}	
	if(bandera==1)
	{			
		fseek(p,0,2);					//Funcion para ordenar nuestros registros por estado.
		e=ftell(p)/sizeof(compu);
		rewind(p);
		printf("\nMaquinas agrupadas por estado:\n\n");
		printf("MARCA:");
		printf("\t\t\t\tESTADO:");		
		printf("\t\t\t\tNUMERO ID:\n\n");
		for(i=0;i<e;i++)
		{
			fread(&compu,sizeof(compu),1,p);
			if(strcmp(compu.estado,"SOFTWARE")==0)		//Recorremos el archivo filtrando por estado.
			{
				printf("%s",compu.marca);
				printf("\t\t\t\t%s",compu.estado);
				printf("\t\t\t\t%d\n",compu.numero_identificacion);
				printf("\n");
			}
		}
		rewind(p);				//Usamos rewind para volver al inicio del archivo cada vez que lo recorremos.
		for(i=0;i<e;i++)
		{
			fread(&compu,sizeof(compu),1,p);
			if(strcmp(compu.estado,"HARDWARE")==0)
			{
				printf("%s",compu.marca);
				printf("\t\t\t\t%s",compu.estado);
				printf("\t\t\t\t%d\n",compu.numero_identificacion);
				printf("\n");
			}
		}
		rewind(p);
		for(i=0;i<e;i++)
		{
			fread(&compu,sizeof(compu),1,p);
			if(strcmp(compu.estado,"FUNCIONANDO")==0)
			{
				printf("%s",compu.marca);
				printf("\t\t\t\t%s",compu.estado);
				printf("\t\t\t\t%d\n",compu.numero_identificacion);
				printf("\n");
			}
		}
	}
	fclose(p);
	return;	
}

void baja_maquina (char archivo[TAM])	
{
	int pos,bandera=0;
	int identificacion;
	FILE *p;
	maquina compu;
	p=fopen(archivo,"r+b");
	fread(&compu,sizeof(compu),1,p);						
	while(feof(p)==0)
	{													//Funcion para dar de baja una maquina sin eliminarla de nuestro archivo.
		if(strcmp(compu.estado,"BAJA")!=0)
		{
			bandera=1;
		}
		fread(&compu,sizeof(compu),1,p);
	}	
	rewind(p);
	if(bandera==1)
	{
		long i,e;
		fseek(p,0,2);
		e=ftell(p)/sizeof(compu);
		lecturamaquina(archivo);
		printf("\n");
		rewind(p);
		printf("-Ingrese el numero de identificacion de su maquina a dar de BAJA: ");
		scanf("%d",&identificacion);
		while(identificacion<1 || identificacion>TAM)
		{
			printf("\n Error. Solo hay %d maquinas. Reingrese su valor\n",TAM);
			printf("-Ingrese el numero de identificacion: ");
			scanf("%d",&identificacion);
		}
		for(i=0;i<e;i++)
		{
			fread(&compu,sizeof(compu),1,p);
			if(identificacion==compu.numero_identificacion)
			{
				strcpy(compu.estado,"BAJA");    //Damos de BAJA mediante numero de identificacion. Filtramos al mostrar.
				pos=ftell(p)-sizeof(maquina);
         	fseek(p,pos,SEEK_SET);
         	fwrite(&compu, sizeof(maquina), 1, p);
         	printf("\n\t\tSe dio de baja la maquina de identificacion: %d \n",identificacion);
				fread(&compu, sizeof(maquina), 1, p);
			}
		}
	}
	else			//Mensaje de error cuando no haya maquinas para dar de baja y se acceda a la opcion.
	{
		printf("\nNo hay maquinas para dar de BAJA.\n\n");
	}
}

void recuperar_maquina (char archivo[TAM])
{
	int pos, bandera=0;
	int identificacion, eleccion;
	FILE *p;
	maquina compu;
	p=fopen(archivo,"r+b");
	fread(&compu,sizeof(compu),1,p);
	while(feof(p)==0)
	{
		if(strcmp(compu.estado,"BAJA")==0)
		{
			bandera=1;
		}
		fread(&compu,sizeof(compu),1,p);
	}	
	rewind(p);
	if(bandera==1)
	{
		long i,e;				//Funcion para recuperar una maquina previamente dada de baja en nuestro archivo.
		fseek(p,0,2);
		e=ftell(p)/sizeof(compu);
		rewind(p);
		printf("\nLista de maquinas dadas de BAJA:\n\n");
		printf("MARCA:");
		printf("\t\t\t\tESTADO:");		
		printf("\t\t\t\tNUMERO ID:\n\n");
		for(i=0;i<e;i++)
		{
			fread(&compu,sizeof(compu),1,p);
			if(strcmp(compu.estado,"BAJA")==0)
			{
				printf("%s",compu.marca);
				printf("\t\t\t\t%s",compu.estado);
				printf("\t\t\t\t%d\n",compu.numero_identificacion);
				printf("\n");
			}
		}
		rewind(p);
		printf("-Ingrese el numero de identificacion de su maquina a recuperar:");
		scanf("%d",&identificacion);
		printf("\n");
		for(i=0;i<e;i++)
		{							
			fread(&compu,sizeof(compu),1,p);
			if(identificacion==compu.numero_identificacion)
			{														//Damos de ALTA mediante numero de identificacion. ALTA con 3 estados posibles.
				printf("\t\t1: Problema de SOFTWARE\n");
				printf("\t\t2: Problema de HARDWARE\n");	
				printf("\t\t3: FUNCIONANDO\n\n");
				printf("-Ingrese su eleccion: ");
				do
				{
					scanf("%d",&eleccion);
					if(eleccion<1 || eleccion>3)
					{
						printf("\nError. Ingrese opcion valida.");
						printf("\n-Ingrese su eleccion: ");
					}
				}while(eleccion<1 || eleccion>3);
				if(eleccion==1)
				{
					strcpy(compu.estado,"SOFTWARE");
				}
				if(eleccion==2)
				{
					strcpy(compu.estado,"HARDWARE");
				}
				if(eleccion==3)
				{
					strcpy(compu.estado,"FUNCIONANDO");
				}
				pos=ftell(p)-sizeof(maquina);
       		fseek(p,pos,SEEK_SET);
         	fwrite(&compu, sizeof(maquina), 1, p);
         	printf("\n\t\tSe dio de alta la maquina de identificacion: %d\n",identificacion);
				fread(&compu, sizeof(maquina), 1, p);
			}
		}
	}
	else			//No se podra recupera una maquina si no se registraron BAJAS.
	{
		printf("\nNo hay maquinas para RECUPERAR.\n\n");
	}
}
