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
/*
    n: number of processes
    bt[]: Burst Time of Processes
    p[]: Process Number

*/
void sjf(int n,int p[30], int bt[30]) {
    
    int i,j,t;
    // Waiting Time
    int wt[30];
    // Turn Around Time
    int tat[30];
    // Applying bubble sort tecnique to sort according to burst time
    for (i = 0; i < n ; i++)
    {
        for (j = 0 ; j < n-i-1; j++ )
        {
            if (bt[j] > bt[j+1]) 
            {
                t = bt[j];
                bt[j] = bt[j+1];
                bt[j+1] = t;

                t = p[j];
                p[j] = p[j+1];
                p[j+1] = t;

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
            wt[i] = wt[i]+bt[j];
        }
        tat[i]= wt[i]+bt[i];
        printf("%d\t\t\t %d\t\t\t %d\t\t\t %d\n", p[i], bt[i], wt[i], tat[i]);
    }
    
    

}


// HPF
/*
    n: number of processes
    bt[]: Burst Time of Processes
    pr[]: Priority
*/
void hpf(int n, int bt[30], int pr[30]) {
    int i,j,t;
    // Waiting Time
    int wt[30];
    // Turn Around Time
    int tat[30];


    for (i = 0; i < n ; i++)
    {
        int pos=i;
        for(j=i+1;j<n;j++)
        {
            if(pr[j]<pr[pos])
            {
                pos=j;
            }
        }
        t=pr[i];
        pr[i]=pr[pos];
        pr[pos]=t;

        t=bt[i];
        bt[i]=bt[pos];
        bt[pos]=t;
    }
    wt[0]=0;
    printf("process \t burst time\t priority \t waiting time \t turn around time\n");

    for (i=0 ; i < n; i++)
    {
        wt[i]=0;
        tat[i]=0;
        for (j=0;j<i;j++)
        {
            wt[i]=wt[i]+bt[j];
        }
        tat[i]=wt[i]+bt[i];
        printf("%d\t\t\t %d\t\t\t %d\t\t\t %d\t\t\t %d\n", i+1, bt[i], pr[i],wt[i], tat[i]);
    }

}


// FIFO
/*
    n: number of processes
    bt[]: Burst Time of Processes
   
*/
void fifo(int n, int bt[30]) {
    

    int i,j;
    // Waiting Time
    int wt[30];
    // Turn Around Time
    int tat[30];

    printf("process\t burst time\t waiting time\t turn around time\n");
    for( i = 0 ; i < n ; i++)
    {
        wt[i] = 0;

        tat[i] = 0;

        for (j=0 ; j < i ; j++)
        {
            wt[i] = wt[i]+bt[j];
        }
        tat[i] = wt[i]+bt[i];
        printf("%d\t\t\t%d\t\t\t%d\t\t\t%d\n",i+1,bt[i],wt[i],tat[i]);
    }

}




