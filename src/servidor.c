#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

typedef struct PCB {
    int PID;
    int burst;
    int priority;
} PCB;


// variables globales

PCB readyQueue[100];
PCB processHistory[100];
int processCounter = 0;

int server_sockfd, client_sockfd; // descriptores de sockets
int server_len, client_len; //tamaÃ±os de las estructuras
struct sockaddr_in server_address; //declaracion de estructuras
struct sockaddr_in client_address;
char c[1024]; //cadena del cliente
char ch[1024]; //cadena del servidor
char msg[1024]; //cadena del servidor
int inicio = 0; //determina el inicio de sesion
char cs[1024]; //cadena del servidor
int bufs; //almacenamiento del tamanio cadena server
int ciclo = 1; //variable para ciclo de lectura escritura
int puerto; //variable para el puerto


// crear 2 hilos distintos (Job y cpu scheduler)

void *startCPUScheduler (void *args) {
    //char *msg = (char *)args;
    //printf("%s",msg);
    // enviar msg por el socket

    // matar el thread
}

void *startJobScheduler () {

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    // se llena la estructura para el servidor con los datos necesarios
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 5000;
    server_len = sizeof(server_address);

    //avisamos al sistema operativo la creacion del socket
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    //decimos al server que quede escuchando
    listen(server_sockfd,5);

    while(ciclo){

        //acepta la conexion con el cliente actual
        client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
        if(inicio ==0) {
            printf("------SESION INICIADA------\n");
            printf("CLIENTE CONECTADO\n");
            strcpy(ch, "SERVIDOR CONECTADO...");
            send(client_sockfd, ch, 1024, 0);
            inicio = 1;
        }
        recv(client_sockfd, cs, 1024,0);
        printf("PCB Info : %s\n",cs);
        processCounter++;

        char PID[1024];
        sprintf(PID,"%d",processCounter);
       // send(client_sockfd, ch, 1024, 0);
        send(client_sockfd, PID, 1024,0);

        close(client_sockfd);
    }

    close(server_sockfd);
}




int main(int argc, char const *argv[])
{

    //int lenReadyQueue = sizeof(readyQueue)/sizeof(readyQueue[0]);;

    int n, opcion;

    pthread_t jobScheduler;
    pthread_t cpuScheduler;

    do
    {
        printf( "\n   Bienvenido al menú del servidor");
        printf( "\n   1. FIFO." );
        printf( "\n   2. SJF.");
        printf( "\n   3. RR." );
        printf( "\n   4. HPF." );
        printf( "\n   5. Salir." );
        printf( "\n\n   Seleccione el algoritmo que desee (1-4): ");

        scanf( "%d", &opcion );

        // crear el socket

        switch ( opcion )
        {
            case 1:
                pthread_create(&jobScheduler,NULL, startJobScheduler,NULL);
                pthread_join(jobScheduler,NULL);

                //pthread_create(&cpuScheduler,NULL, startCPUScheduler,NULL);
                //pthread_join(cpuScheduler,NULL);


                //aca se deben morir
                break;

            case 2:
                printf("wtf");
                break;

            case 3:

                break;

            case 4:

                break;
        }

        /* Fin del anidamiento */

    } while ( opcion < 0 || opcion > 4 );
    return 0;
}