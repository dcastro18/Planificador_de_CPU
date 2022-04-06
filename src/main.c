#include <stdio.h>
#include "Algoritmos.h"
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
int main() {
    int bt[30] = {7,5,1,6};
    int pr[30] = {4,1,2,3};
    hpf(4,bt,pr);
    return 0;
}
