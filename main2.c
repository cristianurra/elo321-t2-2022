 
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include "funciones.h"
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SMOBJ_NAME1 "/client-host" //comunicacion entre el cliente y el host
#define SMOBJ_NAME2 "/host-printer" //comunicacion entre el cliente y el host
#define SMOBJ_SIZE 200


void *print_message_function( void *ptr );
void *leer_cola( void *ptr );
void *cliente();
void *impresora();
int main()
{
	//Creacion del espacio de memoria compartida en posix
	
	int fd1;
	fd1 = shm_open(SMOBJ_NAME1 , O_CREAT | O_RDWR, 00600);
	if(fd1 == -1){
		printf("hubo un error :c \n");
				exit(1);
	}

	if(-1 == ftruncate(fd1, SMOBJ_SIZE)){
		printf("la memoria compartida no pudo ser rezsizeada \n");
	}
	
	
	int fd2;
	fd2 = shm_open(SMOBJ_NAME2 , O_CREAT | O_RDWR, 00600);
	if(fd2 == -1){
		printf("hubo un error :c \n");
				exit(1);
	}

	if(-1 == ftruncate(fd2, SMOBJ_SIZE)){
		printf("la memoria compartida no pudo ser rezsizeada \n");
	}
	

    
    //seccion de lectura de archivo de texto
    int c = contar_pedidos();
    //printf("%d", c);

    Lista *lista_host = inicializacion();
    Elemento *actual_host;
    actual_host = NULL;
    //visualizacion(lista_cliente)
    //creacion de hilos
     pthread_t client, printer;
     char *message1 = "Contenido del client";
     char *message2 = "Contenido de la impresora";
     int   iret1,iret2;

    iret1 = pthread_create( &client, NULL, cliente, (void*) message1); //cliente
    iret2 = pthread_create( &printer, NULL, print_message_function, (void*) message2); //impresora


     pthread_join( iret1, NULL); 
     pthread_join( iret2, NULL); 
     sleep(2);
     printf("Thread 1 retorna: %d\n",iret1);
     printf("Thread 2 retorna: %d\n",iret2);
     
     printf("%d\n",global);
     exit(0);
}

void *print_message_function( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}

void *leer_cola( void *ptr )
{
     char *message;
     message = (char *) ptr;
     printf("%s \n", message);
}

void *cliente()
{
    Lista *lista_cliente = inicializacion();
    Elemento *actual_cliente;
    int c = contar_pedidos();
    pedido *pedidos = malloc(c * sizeof(pedido));
    FILE *fp = fopen("test.txt", "r");
    char *line = NULL;
    size_t len = 0;
    size_t read;

    if (fp == NULL)
    {
        exit(EXIT_FAILURE);
    }
    getline(&line, &len, fp);
    read_pedidos(pedidos , actual_cliente, lista_cliente); //
    fclose(fp);
    visualizacion(lista_cliente);    //
    sup_inicio(lista_cliente); //
	int condicion=1;
	while(condicion==1){
			int fd;
			char buf[]="proceso escrito\n";
			char *ptr;
			fd = shm_open(SMOBJ_NAME , O_RDWR, 0);
	
			if(fd == -1){
				printf("hubo un error :c \n");
				exit(1);
			}
	
			ptr = mmap(0, sizeof(buf), PROT_WRITE, MAP_SHARED,fd,0);
			if (ptr==MAP_FAILED){
				printf("Error mapeando \n");
				exit(1);
			}
		memcpy(ptr,buf,sizeof(buf));
		close(fd);	
		
		
	}

    return(0);
}

void *impresora()
{
}
