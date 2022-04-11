#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

//Para Sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<arpa/inet.h>


// VARIABLES GLOBALES
int sockfd;
int len;
struct sockaddr_in address;
int result;
char ch[1024];
char c[1024];
int buf;
int inicio = 0;
char cs[1024];
int bufs;
int ciclo =1;
char ipserver[16] = "127.0.0.1";
int puerto = 5000;



int randNumber(int min, int max) {
    time_t t;
    srand((unsigned) time(&t));
    int num = rand()%((max+1)-min)+min;
    return num;
}

void *sendData (void *args) {
    char *msg = (char *)args;
    // enviar msg por el socket

    sockfd = socket(AF_INET, SOCK_STREAM,0);
    //llenado de la estructura de datos
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ipserver);
    address.sin_port = puerto;
    len = sizeof(address);

    //conectar con el server
    result = connect(sockfd, (struct sockaddr *)&address, len);
    if(result ==-1){
        perror("ERROR EN LA CONEXION\n");
        close(sockfd);
    }

    //validar el inicio de sesion
    if(inicio==0){
        printf("--------------- SESION INICIADA --------------\n");
        recv(sockfd, ch, 1024,0);
        printf("%s\n",ch);
        inicio = 1;
    }
    send(sockfd,msg, 1024,0);

    recv(sockfd, c, 1024,0);
    printf("Proceso recibido! El PID asignado es el número: %s\n",c);
    close(sockfd);
    // matar el thread
}

typedef struct Rango {
    int min;
    int max;
} Rango;

char numToASCII(int num) {
    return (char)num;
}

void *automatic (void *args)
{
    Rango *r1 = (Rango *)args;
    pthread_t pthread;

    char con[20];
    
    while(1)
    {
        sleep(2);
        int randBurst = randNumber(r1->min,r1->max);
        int randPriority = randNumber(1,5);

        con[0] = randBurst + '0';
        con[1] = ';';
        con[2] = randPriority + '0';

        printf("Palabra:  %s",con);

        pthread_create(&pthread,NULL, sendData, (void *)&con);
        pthread_join(pthread,NULL);

        int randNum = randNumber(3,8);
        sleep(randNum);
    }

}

void *readFile (void *args) {
    // leer archivos
    FILE *fp; // declaration of file pointer

    fp = fopen("prueba.txt","r"); // opening of file
    if (!fp) // checking for error
        printf("No se encontro el archivo");

    fseek(fp, 0 , SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0 , SEEK_SET);// needed for next read from beginning of file

    char con[fileSize]; // variable to read the content
    int i = 0;

    pthread_t pthread;

    while (fgets(con,fileSize, fp)!=NULL) { // reading file content

        if(i != 0)
        {
            //Espera dos segundos y y envia al server
            sleep(2);

            pthread_create(&pthread,NULL, sendData, (void *)&con);
            pthread_join(pthread,NULL);

            int randNum = randNumber(3,8);
            sleep(randNum);
        }
        i++;
    }

    fclose(fp); // closing file
    pthread_exit(&pthread);
}

int main(int argc, char const *argv[])
{

    pthread_t mainThread;


    int min, max, opcion;

    do
    {
        printf( "\nBienvenido al menú del cliente");
        printf( "\n 1. Cliente manual." );
        printf( "\n 2. Cliente automático");
        printf( "\n 3. Salir." );
        printf( "\n\n  Introduzca opción que desee (1-3): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */


        switch ( opcion )
        {
            case 1:
                pthread_create(&mainThread,NULL, readFile,NULL);
                pthread_join(mainThread,NULL);
                break;

            case 2:
                printf( "\nIngrese el valor minimo y maximo del rango, separados por un espacio: ");
                scanf( "%d %d", &min, &max );


                Rango r1;
                r1.min = min;
                r1.max = max;

                pthread_create(&mainThread,NULL, (void *)automatic,(void *)&r1);
                pthread_join(mainThread,NULL);
                break;

            case 3:
                break;
        }

        /* Fin del anidamiento */

    } while ( opcion < 0 || opcion > 3 );

    return 0;
}