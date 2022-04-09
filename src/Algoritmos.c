
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
// Calculo de promedios de WT
float getPromedioWT(PCB queue[100]) { 
    float promedio = 0.0;
    float n = (float)getQueueSize(queue);
    int temp = 0;
    int j = getQueueSize(queue);
    for (int i = 0; i < j ; i++){
        temp = temp + queue[i].wt;
    }
    promedio = temp/n;
    return  promedio;
}
// Calculo de promedios de TAT

float getPromedioTAT(PCB queue[100]) { 
    float promedio = 0.0;
    float n = (float)getQueueSize(queue);
    int temp = 0;
    int j = getQueueSize(queue);
    for (int i = 0; i < j ; i++){
        temp = temp + queue[i].tat;
    }
    promedio = temp/n;
    return  promedio;
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

// Auxiliar para print de los Queue
void printQueue(PCB queue[100]) {
    printf("PID \t burst time \t waiting time \t turn around time\n");
    for (int j = 0 ; j < 10 ; j++){
        
        if (queue[j].PID == 0 & queue[j].burst == 0 & queue[j].priority==0){
            break;
        }
        else {
            
            printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n",readyQueue[j].PID,readyQueue[j].burst,readyQueue[j].wt,readyQueue[j].tat);
        }
        
    }
}


// ROUND ROBIN
/*
    n: number of processes
    qt: Quantum Time
    bt[]: Burst Time of Processes
*/
void roundRobin(int qt,PCB queue[100]) {
    // Cantidad de procesos
    int n =  getQueueSize(queue);
    int i;
    int temp;
    // Turn Around Time
    int tat[100];
    // Waiting Time
    int wt[100];
    // Remaining Burst Time
    int rem_bt[100];
    // Counter
    int count = 0;
    // SQ
    int sq = 0;
    
    // Number of proccesses for and burst copying
    for (i = 0; i < n ; i++){
        rem_bt[i] = queue[i].burst;
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
        wt[i] = tat[i] - queue[i].burst;
        printf("\n%d\t\t\t%d\t\t\t\t%d\t\t\t%d", i + 1,queue[i].burst,tat[i],wt[i]);
    }
    
}


// SJF
/*
    n: number of processes
    bt[]: Burst Time of Processes
    p[]: Process Number

*/
void sjf(PCB readyQueue[100]) {
    // Cantidad de procesos
    int n =  getQueueSize(queue);
    int i,j;
    PCB temp;
    // Waiting Time
    int wt[100];
    // Turn Around Time
    int tat[100];
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
    printf("process \t burst time \t waiting time \t turn around time\n");

    for (i = 0 ; i < n; i++)
    {
        wt[i]=0;
        tat[i]=0;
        for (j=0;j<i;j++)
        {
            wt[i] = wt[i]+readyQueue[j].burst;
        }
        tat[i]= wt[i]+readyQueue[i].burst;
        readyQueue[i].tat = tat[i];
        readyQueue[i].wt = wt[i];
        printf("%d\t\t\t %d\t\t\t %d\t\t\t %d\n", readyQueue[i].PID, readyQueue[i].burst, readyQueue[i].wt, readyQueue[i].tat);


    }
    
    

}


// HPF
/*
    n: number of processes
    bt[]: Burst Time of Processes
    pr[]: Priority
*/
void hpf(PCB readyQueue[100]) {

    // Cantidad de procesos
    int n =  getQueueSize(queue);
    // Contadores
    int i,j;
    // PCB Temporal
    PCB temp;
    // Waiting Time
    int wt[30];
    // Turn Around Time
    int tat[30];
    
    // Bubblesort por priority
    for (i = 0; i < n ; i++)
    {
        int pos=i;
        for(j=i+1;j<n;j++)
        {
            if(readyQueue[j].priority <readyQueue[pos].priority)
            {
                pos=j;
            }
        }
        temp=readyQueue[i];
        readyQueue[i]=readyQueue[pos];
        readyQueue[pos]=temp;

    }
    wt[0]=0;
    printf("process \t burst time\t priority \t waiting time \t turn around time\n");

    for (i=0 ; i < n; i++)
    {
        wt[i]=0;
        tat[i]=0;
        for (j=0;j<i;j++)
        {
            wt[i]=wt[i]+readyQueue[j].burst;
        }
        tat[i]=wt[i]+readyQueue[i].burst;
        // Iguala wt y tat en el PCB
        readyQueue[i].wt = wt[i];
        readyQueue[i].tat = tat[i];
        printf("%d\t\t\t %d\t\t\t %d\t\t\t %d\t\t\t %d\n", readyQueue[i].PID, readyQueue[i].burst, readyQueue[i].priority,wt[i], tat[i]);
    }

}


// FIFO
/*
    n: number of processes
    bt[]: Burst Time of Processes
   
*/
void fifo(PCB readyQueue[100]) {
    // Cantidad de procesos
    int n =  getQueueSize(queue);
    // Bursts
    int bt[100];
    int i,j;
    // Waiting Time
    int wt[100];
    // Turn Around Time
    int tat[100];

    printf("process\t\t burst time\t waiting time\t turn around time\n");
    for( i = 0 ; i < n ; i++)
    {
        wt[i] = 0;

        tat[i] = 0;

        for (j=0 ; j < i ; j++)
        {
            wt[i] = wt[i]+readyQueue[j].burst;
        }
        tat[i] = wt[i]+readyQueue[i].burst;
        // Iguala wt y tat en el PCB
        queue[i].wt = wt[i];
        queue[i].tat = tat[i];
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n",readyQueue[i].PID,readyQueue[i].burst,readyQueue[i].wt,readyQueue[i].tat);
    }

}




