#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#include "Algoritmos.h"

#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>


// variables globales

PCB exeProcess;
PCB readyQueue[100];
PCB processHistory[100];
int processCounter = 0;

pthread_t jobscheduler;
pthread_t cpuscheduler;
pthread_t action;
pthread_t timer;

int algorithmID = 0;
int qt = 0;
int leisureTime= 0;
int burstSeconds = 0;

int tiempoTotal= 0;
int isFinished = 0 ;
int start = 0;


int server_sockfd, client_sockfd; // descriptores de sockets
int server_len, client_len; //tamaÃ±os de las estructuras
struct sockaddr_in server_address; //declaracion de estructuras
struct sockaddr_in client_address;
char c[1024]; //cadena del cliente
char ch[1024]; //cadena del servidor
int inicio = 0; //determina el inicio de sesion
char cs[1024]; //cadena del servidor
int ciclo = 1; //variable para ciclo de lectura escritura
int puerto; //variable para el puerto



void *startTimer () {

    while(1)
    {
        if(!isFinished){
            if(start)
            {
                if(exeProcess.PID != 0)
                {

                    if(burstSeconds<exeProcess.burst)
                    {
                        burstSeconds++;
                    }
                    else{
                        exeProcess.PID = 0;
                        burstSeconds = 0;
                    }
                }
                else
                {
                    leisureTime++;
                }

                tiempoTotal++;
                fflush(stdout);
                printf("\nTiempo total %d  : ", tiempoTotal);
                sleep(1);
            }
        }
        else{
            break;
        }

    }
}

void *startActionThread () {

    char msg[1];
    while(1)
    {
        if(!isFinished){
            scanf( "%s", msg );
            if(msg[0] == 'c')
            {
                fflush(stdout);
                printf("________________________________________________________\n");
                printReadyQueue(readyQueue);
                printf("________________________________________________________\n");

            }
            else if(msg[0] == 'd')
            {
                isFinished = 1;
                pthread_cancel(jobscheduler);
                pthread_cancel(cpuscheduler);
                pthread_cancel(timer);

                close(client_sockfd);
                close(server_sockfd);

                fflush(stdout);
                printf("\n --- Resumen de ejecución --- \n");
                int n =  getQueueSize(processHistory);
                printf("Cantidad de procesos ejecutados : %d\n",n);
                printf("Cantidad de segundos con CPU ocioso: %d\n",leisureTime);
                printQueue(processHistory);
                printf("\nPromedio de Waiting Time: %f\n", getPromedioWT(processHistory));
                printf("Promedio de Turn Around Time: %f\n", getPromedioTAT(processHistory));
                //break;
            }
        }
        else{
            break;
        }

    }

}

void bubbleSortSJF() {
    // Cantidad de procesos
    int n =  getQueueSize(readyQueue);
    // Contadores
    int i,j;
    // PCB Temporal
    PCB temp;
    // Applying bubble sort tecnique to sort according to burst time
    for (i = 0; i < n ; i++)
    {
        for (j = 0 ; j < n-i-1; j++ )
        {
            if (readyQueue[j].burst > readyQueue[j+1].burst)
            {
                temp = readyQueue[j];
                readyQueue[j] = readyQueue[j+1];
                readyQueue[j+1] = temp;

            }
        }

    }

}

void bubbleSortHPF() {
    // Cantidad de procesos
    int n =  getQueueSize(readyQueue);
    // Contadores
    int i,j;
    // PCB Temporal
    PCB temp;
    // Bubblesort por priority
    for (i = 0; i < n ; i++)
    {
        int pos=i;
        for(j=i+1;j<n;j++)
        {
            if(readyQueue[j].priority < readyQueue[pos].priority)
            {
                pos=j;
            }
        }
        temp=readyQueue[i];
        readyQueue[i]=readyQueue[pos];
        readyQueue[pos]=temp;
    }

}

int updateQueue()
{
    int lenProcessHistory = getQueueSize(processHistory);
    processHistory[lenProcessHistory] = readyQueue[0];
    int lenReadyQueue = getQueueSize(readyQueue);
    for (int i = 0; i < lenReadyQueue ; i++) {
        readyQueue[i] = readyQueue[i + 1];
    }
}

int updateRR()
{
    int existe=0;
    int lenProcessHistory = getQueueSize(processHistory);
    for (int j = 0; j < lenProcessHistory ; j++) {
        if(processHistory[j].PID == readyQueue[0].PID)
        {
            processHistory[j].burst = processHistory[j].burst + readyQueue[0].burst;
            processHistory[j].tat = readyQueue[0].tat;
            processHistory[j].wt =   readyQueue[0].tat - processHistory[j].burst;

            existe=1;
        }
    }
    if(!existe)
    {
        processHistory[lenProcessHistory] = readyQueue[0];
    }

    int lenReadyQueue = getQueueSize(readyQueue);
    for (int i = 0; i < lenReadyQueue ; i++) {
        readyQueue[i] = readyQueue[i + 1];
    }
}



void *startCPUScheduler () {


    while (1)
    {

        if(!isFinished){
            int lenReadyQueue = getQueueSize(readyQueue);
            int restante;
            int realWT;

            if(lenReadyQueue>0)
            {
                start=1;
                switch ( algorithmID ) {
                    case 1:
                        printf(" Proceso %d con burst %d entra en ejecución",readyQueue[0].PID,readyQueue[0].burst);
                        fifo(readyQueue);
                        exeProcess = readyQueue[0];
                        sleep(readyQueue[0].burst);
                        readyQueue[0].tat = tiempoTotal;
                        realWT = (readyQueue[0].tat-readyQueue[0].burst)-readyQueue[0].llegada;
                        if (realWT < 0){
                            realWT = 0;
                        }
                        readyQueue[0].wt = realWT;
                        printf("El proceso con ID: %d, ha finalizado\n",readyQueue[0].PID);
                        updateQueue();

                        break;

                    case 2:
                        bubbleSortSJF();
                        printf(" Proceso %d con burst %d entra en ejecución",readyQueue[0].PID,readyQueue[0].burst);
                        sjf(readyQueue);
                        exeProcess = readyQueue[0];
                        sleep(readyQueue[0].burst);
                        readyQueue[0].tat = tiempoTotal;
                        realWT = (readyQueue[0].tat-readyQueue[0].burst)-readyQueue[0].llegada;
                        if (realWT < 0){
                            realWT = 0;
                        }
                        readyQueue[0].wt = realWT;

                        printf("El proceso con ID: %d, ha finalzado\n",readyQueue[0].PID);
                        updateQueue();
                        break;

                    case 3:
                        bubbleSortHPF();
                        printf(" Proceso %d con burst %d entra en ejecución",readyQueue[0].PID,readyQueue[0].burst);
                        hpf(readyQueue);
                        exeProcess = readyQueue[0];
                        sleep(readyQueue[0].burst);
                        readyQueue[0].tat = tiempoTotal;
                        realWT = (readyQueue[0].tat-readyQueue[0].burst)-readyQueue[0].llegada;
                        if (realWT < 0){
                            realWT = 0;
                        }
                        readyQueue[0].wt = realWT;
                        printf("El proceso con ID: %d, ha finalzado\n",readyQueue[0].PID);
                        updateQueue();
                        break;

                    case 4:
                        printf(" Proceso %d con burst %d entra en ejecución",readyQueue[0].PID,readyQueue[0].burst);
                        if(readyQueue[0].burst > qt)
                        {
                            restante = readyQueue[0].burst - qt;
                            readyQueue[0].burst = qt;
                            exeProcess = readyQueue[0];
                            readyQueue[lenReadyQueue] = readyQueue[0];
                            readyQueue[lenReadyQueue].burst = restante;
                            if(readyQueue[0].wt != 0)
                            {
                                readyQueue[lenReadyQueue].wt = (readyQueue[0].tat-readyQueue[0].burst)-readyQueue[0].llegada;
                            }

                            sleep(qt);


                        }else{
                            exeProcess = readyQueue[0];
                            sleep(exeProcess.burst);
                            readyQueue[0].tat = tiempoTotal - readyQueue[0].llegada;
                            readyQueue[0].wt = readyQueue[0].tat-readyQueue[0].burst;
                            printf("El proceso con ID: %d, ha finalzado\n",readyQueue[0].PID);
                        }
                        updateRR();
                        break;
                }
            }
        }
        else{
            break;
        }
    }

}



void *startJobScheduler () {

    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 5000;
    server_len = sizeof(server_address);

    //avisamos al sistema operativo la creacion del socket
    bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

    //decimos al server que quede escuchando
    listen(server_sockfd,5);

    while(ciclo){

        if(!isFinished){
            //acepta la conexion con el cliente actual
            client_sockfd = accept(server_sockfd, (struct sockaddr *)&client_address, &client_len);
            if(inicio ==0) {
                printf("------SESION INICIADA------\n");
                printf("CLIENTE CONECTADO\n");
                strcpy(ch, "SERVIDOR CONECTADO...");
                send(client_sockfd, ch, 1024, 0);
                inicio = 1;
            }
            fflush(stdout);
            recv(client_sockfd, cs, 1024,0);
            processCounter++;

            char burst[10];

            for (int i = 0; i < strlen(cs)-1 ; ++i) {
                if(cs[i]!=';')
                {
                    burst[i] = cs[i];
                }
                else{
                    burst[i] = '\0';
                    break;
                }

            }
            char priority = cs[strlen(cs)-2];

            // Crea el PCB
            PCB pcbTemp;
            pcbTemp.PID = processCounter;
            pcbTemp.burst = atoi(burst);
            pcbTemp.priority = priority - '0';
            pcbTemp.llegada = tiempoTotal;

            printf(" Llego el proceso:  %d",processCounter);

            int lenReadyQueue = getQueueSize(readyQueue);

            readyQueue[lenReadyQueue] = pcbTemp;

            char PID[1024];
            sprintf(PID,"%d",processCounter);
            send(client_sockfd, PID, 1024,0);

            close(client_sockfd);
        }
        else{
            break;
        }
    }

    close(server_sockfd);
}




int main(int argc, char const *argv[])
{
    int opcion;

    do
    {
        printf( "\nBienvenido al menú del servidor");
        printf( "\n 1. FIFO." );
        printf( "\n 2. SJF.");
        printf( "\n 3. HPF." );
        printf( "\n 4. RR." );
        printf( "\n 5. Salir." );
        printf( "\n\n Seleccione el algoritmo que desee (1-4): ");

        scanf( "%d", &opcion );

        switch ( opcion )
        {
            case 1:
                algorithmID = 1;
                break;

            case 2:
                algorithmID = 2;
                break;

            case 3:
                algorithmID = 3;
                break;

            case 4:
                algorithmID = 4;
                printf( "\n\n Escriba el quantum que desee: ");
                scanf( "%d", &qt );

                break;
        }

    } while ( opcion < 0 || opcion > 4 );

    pthread_create(&jobscheduler,NULL, startJobScheduler,NULL);
    pthread_create(&cpuscheduler,NULL, startCPUScheduler,NULL);
    pthread_create(&action,NULL, startActionThread,NULL);
    pthread_create(&timer,NULL, startTimer,NULL);
    pthread_join(jobscheduler,NULL);
    pthread_join(cpuscheduler,NULL);
    pthread_join(action,NULL);
    pthread_join(timer,NULL);

    return 0;
}