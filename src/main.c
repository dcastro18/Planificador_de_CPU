#include <stdio.h>
#include "Algoritmos.h"
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
int main() {
    int p[30] = {1,2,3,4};
    int bt[30] = {3,2,5,7};
    sjf(4,p,bt);
    return 0;
}
