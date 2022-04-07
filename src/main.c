#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    
    FILE *fp; // declaration of file pointer
    
    fp = fopen("prueba.txt","r"); // opening of file
    if (!fp) // checking for error
        return 1;

    fseek(fp, 0 , SEEK_END);
    long fileSize = ftell(fp);
    fseek(fp, 0 , SEEK_SET);// needed for next read from beginning of file
    printf("%ld\n",fileSize);
    
    // Number of lines in the file -1 is the amount of processes
    int amountOfProcess = -1;
    
    char con[fileSize]; // variable to read the content

    while (fgets(con,fileSize, fp)!=NULL) { // reading file content
        //Espera dos segundos y y envia al server
        printf("%s\n",con);
        amountOfProcess++;
    }
    
    printf("%d\n",amountOfProcess);
    fclose(fp); // closing file
    int num;
    

    time_t t;

    /* Initialization to get random differents numbers each time */
    srand((unsigned) time(&t));

    /*generates random number*/
    int min = 3;
    int max = 8;
    num = rand()%((max+1)-min)+min;
    printf("number is: %d\n",num);

    return 0;
}
