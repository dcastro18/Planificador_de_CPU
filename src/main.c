#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <time.h>


// Cola
typedef struct PCB {
    int PID;
    int burst;
    int priority;
    int tat;
    int wt;
} PCB;

// Variable global
PCB readyQueue[100];

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

// Auxiliar para obtener la cantidad de procesos en el Queue
int getQueueSize(PCB queue[100]) {
    int i = 0;
    int counter = 0;
    for (i = 0 ; i < 100 ; i++) {
        if (queue[i].PID == 0 & queue[i].burst == 0 & queue[i].priority==0){
            break;
        }
        else
            counter++;

    }
    return counter;
}

// Print para los Queue
void printQueue(PCB queue[100]) {
    printf("process \t burst time\t priority \t waiting time \t turn around time\n");
    for (int j = 0 ; j < 10 ; j++){
        
        if (queue[j].PID == 0 & queue[j].burst == 0 & queue[j].priority==0){
            break;
        }
        else {
            
            printf("%d\t\t\t%d\t\t%d\t\t%d\t\t\t%d\n",readyQueue[j].PID,readyQueue[j].burst,readyQueue[j].priority,readyQueue[j].wt,readyQueue[j].tat);
        }
        
    }
}


// ROUND ROBIN
/*
    n: number of processes
    qt: Quantum Time
    bt[]: Burst Time of Processes
*/
void roundRobin(int n, int qt, int bt[10]) {
    
    int i,temp;
    // Turn Around Time
    int tat[10];
    // Waiting Time
    int wt[10];
    // Remaining Burst Time
    int rem_bt[10];
    // Counter
    int count = 0;
    // SQ
    int sq = 0;
    
    // Number of proccesses for and burst copying
    for (i = 0; i < n ; i++){
        
        rem_bt[i] = bt[i];
    }

    while (1) {

        for (i = 0, count = 0; i < n ; i++) 
        {
            
            temp = qt;

            if (rem_bt[i] == 0)
            {
                count++;
                continue;
            }

            if (rem_bt[i] > qt)
                rem_bt[i] = rem_bt[i]- qt;
            else 
                if (rem_bt[i] >= 0)
                {
                    temp = rem_bt[i];
                    rem_bt[i] = 0;
                }
                sq = sq + temp;
                tat[i] = sq;

            
        }
        if (n == count) 
            break;
    }

    printf("\nprocess\tburst time\tturnaround time\twaiting time\n");

    for ( i = 0; i < n ; i++){
        wt[i] = tat[i] - bt[i];
        printf("\n%d\t\t\t%d\t\t\t\t%d\t\t\t%d", i + 1,bt[i],tat[i],wt[i]);
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

    // Number of lines in the file -1 is the amount of processes
    int amountOfProcess = -1;

    char con[fileSize]; // variable to read the content
    int i = 0;

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
    printf("Cantidad de procesos: %d\t",getQueueSize(readyQueue));
    printQueue(readyQueue);
    hpf(readyQueue);
    printf("Despues de algoritmo: \n");
    printQueue(readyQueue);
    
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