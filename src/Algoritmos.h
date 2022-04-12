
// Cola
typedef struct PCB {
    int PID;
    int burst;
    int priority;
    int tat;
    int wt;
    int estado;
} PCB;

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


// Auxiliar para print de los Queue
void printQueue(PCB queue[100]) {
    printf("\nPID\t\t\tBurst Time\t\tWaiting Time\t\tTurn Around Time\n");
    for (int j = 0 ; j < 100 ; j++){
        
        if (queue[j].PID == 0 & queue[j].burst == 0 & queue[j].priority==0){
            break;
        }
        else {
            
            printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n",queue[j].PID,queue[j].burst,queue[j].wt,queue[j].tat);
        }
        
    }
}

void printReadyQueue(PCB queue[100]) {
    printf("\nPID\t\t\tBurst Time\t\tPrioridad\n");
    for (int j = 0 ; j < 100 ; j++){

        if (queue[j].PID == 0 & queue[j].burst == 0 & queue[j].priority==0){
            break;
        }
        else {

            printf("%d\t\t\t%d\t\t\t%d\n",queue[j].PID,queue[j].burst,queue[j].priority);
        }

    }
}


// ROUND ROBIN
/*
    n: number of processes
    qt: Quantum Time
    bt[]: Burst Time of Processes
*/
void roundRobin(int qt, PCB queue[100]) {


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
        printf("\n%d\t\t\t%d\t\t\t\t%d\t\t\t%d", queue[i].PID,queue[i].burst,tat[i],wt[i]);
    }
    
}

// SJF
/*
    n: number of processes
    bt[]: Burst Time of Processes
    p[]: Process Number

*/
void sjf(PCB queue[100]) {
    // Cantidad de procesos
    int n =  getQueueSize(queue);
    int i,j;
    PCB temp;
    // Waiting Time
    int wt[100];
    // Turn Around Time
    int tat[100];
    
    printf("Proceso %d con burst %d entra en ejecución \n",queue[0].PID,queue[0].burst);
    for (i = 0 ; i < n; i++)
    {
        //wt[i]=0;
        tat[i]=0;
        for (j=0;j<i;j++)
        {
            wt[i] = wt[i]+queue[j].burst;
        }
        tat[i]= queue[i].wt+queue[i].burst;
        queue[i].tat = tat[i];
        //queue[i].wt = wt[i];
        


    }
    
    

}


// HPF
/*
    n: number of processes
    bt[]: Burst Time of Processes
    pr[]: Priority
*/
void hpf(PCB queue[100]) {

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
    
    //wt[0]=0;
    
    printf("Proceso %d con burst %d entra en ejecución \n",queue[0].PID,queue[0].burst);
    for (i=0 ; i < n; i++)
    {
        //wt[i]=0;
        tat[i]=0;
        for (j=0;j<i;j++)
        {
            wt[i]=wt[i]+queue[j].burst;
        }
        tat[i]=queue[i].wt+queue[i].burst;
        // Iguala wt y tat en el PCB
        //queue[i].wt = wt[i];
        queue[i].tat = tat[i];
        
    }

}


// FIFO
/*
    n: number of processes
    bt[]: Burst Time of Processes
   
*/
void fifo(PCB queue[100]) {
    // Cantidad de procesos
    int n =  getQueueSize(queue);
    // Bursts
    int bt[100];
    int i,j;
    // Waiting Time
    int wt[100];
    // Turn Around Time
    int tat[100];

    printf("Proceso %d con burst %d entra en ejecución \n",queue[0].PID,queue[0].burst);

   
    for( i = 0 ; i < n ; i++)
    {
        //wt[i] = 0;

        tat[i] = 0;

        for (j=0 ; j < i ; j++)
        {
            wt[i] = wt[i]+queue[j].burst;
        }
        tat[i] = queue[i].wt+queue[i].burst;
        // Iguala wt y tat en el PCB
        //queue[i].wt = wt[i];
        queue[i].tat = tat[i];

    }

}




