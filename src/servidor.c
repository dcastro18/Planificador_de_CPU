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

PCB readyQueue[100];
PCB processHistory[100];

// crear 2 hilos distintos (Job y cpu scheduler)

int main(int argc, char const *argv[])
{
    /*
    PCB pcb;
    pcb.PID= 1;
    pcb.burst = 4;
    pcb.priority = 1;


    int lenProcesses=1;

    readyQueue[lenProcesses] = pcb;
    //int lenReadyQueue = sizeof(readyQueue)/sizeof(readyQueue[0]);;

    */

    int n, opcion;

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

                break;

            case 2:

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