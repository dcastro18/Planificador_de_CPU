#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include "Algoritmos.h"




int randNumber(int min, int max) {
    time_t t;
    srand((unsigned) time(&t));
    int num = rand()%((max+1)-min)+min;
    return num;
}

void *sendData (void *args) {
    char *msg = (char *)args;
    //printf("%s",msg);
    // enviar msg por el socket
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

    // Number of lines in the file -1 is the amount of processes
    int amountOfProcess = -1;

    char con[fileSize]; // variable to read the content
    int i = 0;
    PCB readyQueue[100];
    while (fgets(con,fileSize, fp)!=NULL) { // reading file content

        if(i != 0)
        {
            //Espera dos segundos y y envia al server
            sleep(2);
            pthread_t pthread;
            pthread_create(&pthread,NULL, sendData, (void *)&con);
            pthread_join(pthread,NULL);
            
            // Recibo el PID y creo el hilo con ese ID (y con la info)
            // Crea el PCB
            PCB pcbTemp;
            pcbTemp.PID = i;
            pcbTemp.burst = con[0] - '0';
            pcbTemp.priority = con[2]- '0';
            
            readyQueue[i-1] = pcbTemp;
            // Crea numero random
            int randNum = randNumber(3,8);
            sleep(randNum);

        }
        i++;
    }
    fclose(fp); // closing file
    // Print de Procesos
    printf("Cantidad de procesos: %d\t\n",getQueueSize(readyQueue));
    printQueue(readyQueue);
    fifo(readyQueue);
    // Hacer el random para dormir el hilo unos segundos antes de leer la siguiente linea
    //printf("number is: %d\n", randNumber(3,8));

}











int main(int argc, char const *argv[])
{

    
    int n, opcion;

    do
    {
        printf( "\n   Bienvenido al menú del cliente");
        printf( "\n   1. Cliente manual." );
        printf( "\n   2. Cliente automático");
        printf( "\n   3. Salir." );
        printf( "\n\n   Introduzca opción que desee (1-3): ");

        scanf( "%d", &opcion );

        /* Inicio del anidamiento */

        pthread_t mainThread;

        switch ( opcion )
        {
            case 1:

                pthread_create(&mainThread,NULL, readFile,NULL);
                pthread_join(mainThread,NULL);
                break;

            case 2:
                break;

            case 3:
                break;
        }

        /* Fin del anidamiento */

    } while ( opcion < 0 || opcion > 3 );

    return 0;
}