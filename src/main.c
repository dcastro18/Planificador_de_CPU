#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

typedef struct dato {
    int PID;
    int burst;
    int priority;
} PCB;

int randNumber(int min, int max) {
    time_t t;
    srand((unsigned) time(&t));
    int num = rand()%((max+1)-min)+min;
    return num;
}

void *readFile (void *args) {
    // leer archivos
    // enviar la infor por el socket

    // Recibo el PID y creo el hilo con ese ID (y con la info)

    // Hacer el random para dormir el hilo unos segundos antes de leer la siguiente linea
    //printf("number is: %d\n", randNumber(3,8));

    PCB *pcb =(PCB *)args;
    printf("%d\n",pcb->burst);

    pcb->burst = 2;

}

int main(int argc, char const *argv[])
{
    pthread_t mainThread;

    PCB pcb;
    pcb.PID= 1;
    pcb.burst = 4;
    pcb.priority = 1;

    PCB readyQueue[100];
    int lenProcesses=1;

    readyQueue[lenProcesses] = pcb;
    //int lenReadyQueue = sizeof(readyQueue)/sizeof(readyQueue[0]);;


    //pthread_create(&mainThread,NULL, readFile, (void *)&pcb);
    //pthread_join(mainThread,NULL);

    int pBurst = readyQueue[lenProcesses].PID;

    /*for (int i = PID_deleted; i < lenProcesses; ++i) {
        readyQueue[i] = readyQueue[i+1];
    }*/



    printf("%d\n",readyQueue[50].PID);
    return 0;
}