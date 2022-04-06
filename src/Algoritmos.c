// ROUND ROBIN
    // C program to implement Round Robin algoritm

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


// SJF


int sjf() {
    printf("Hello, World!\n");
    return 0;
}


// HPF

int hpf() {
    printf("Hello, World!\n");
    return 0;
}


// FIFO

int fifo() {
    printf("Hello, World!\n");
    return 0;
}
