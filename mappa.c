#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

#define WIDTH 60
#define HEIGHT 20
#define HOLES 50

/* Strutture */
typedef struct cella{

    int occupata;

}cella;

/* Prototipi */
int shmCreate(int, int);

/* Codice */

int shmCreate(int mykey, int sizeMem){

    int shmid = shmget(mykey, sizeMem, IPC_CREAT | 0666);
    return shmid;

}


int insertHoles(cella* arr){

    srand(time(0));
    int idx = rand()%(WIDTH * HEIGHT);

    int i = idx/WIDTH;
    int j = idx-(i*WIDTH);

    if( (arr[idx].occupata == 1) || (i==0) || (j==0) || (i==(HEIGHT-1)) || (j==(WIDTH-1)) )
        return 0;
    else{

        int aD = (i-1)*WIDTH+(j-1);
        int aC = (i-1)*WIDTH+j;
        int aS = (i-1)*WIDTH+(j+1);
        int cD = i*WIDTH+(j-1);
        int cS = i*WIDTH+(j+1);
        int bD = (i+1)*WIDTH+(j-1);
        int bC = (i+1)*WIDTH+j;
        int bS = (i+1)*WIDTH+(j+1);

        if( (arr[aD].occupata == 0) && (arr[aC].occupata == 0) && (arr[aS].occupata == 0) && (arr[cD].occupata == 0) && (arr[cS].occupata == 0) && (arr[bD].occupata == 0)  && (arr[bC].occupata == 0) && (arr[bS].occupata == 0) ){

            arr[idx].occupata = 1;
            return 1;

        }
    }
    return 0;
}


int main(){


    cella* arr;

    int mykey = ftok(".", 'x');
    int sizeMem = WIDTH*HEIGHT*sizeof(arr);
    int sizeMatrix = HEIGHT*WIDTH;

    int shmid = shmCreate(mykey,sizeMem);
    arr = (cella*)shmat(shmid, NULL, 0);
    int i = 0;
    int j;
    int count = HOLES;


    cella c;
    c.occupata = 0;

    for(i; i < sizeMatrix; i++){
        arr[i] = c;
    }

    int b = 0;
    for(int a = 0; a < HEIGHT*WIDTH; a++){
        printf("%c  ", arr[a].occupata ? 'X' : '.');
        if(b == WIDTH-1){
            printf("\n\n");
            b = 0;
        }else
            b++;
    }


    printf("\n\n\n");

    while(count > 0){
        //printf("\n%d\n", tmp);
        if(insertHoles(arr)){
            count--;
            printf("\n%d\n", count);
        }
    }

    if(fork() == 0){

        int shmidChild = shmget(mykey, sizeMem, IPC_CREAT);
        cella* arrChild = (cella*)shmat(shmidChild, 0, SHM_RDONLY);
        int j = 0;
        for(int i = 0; i < HEIGHT*WIDTH; i++){
            printf("%c  ", arr[i].occupata ? 'X' : '.');
            if(j == WIDTH-1){
                printf("\n\n");
                j = 0;
            }else
                j++;
        }

        shmdt(arrChild);
    }

    wait(NULL);

    shmdt(arr);

    shmctl(shmid, IPC_RMID, 0);

    printf("\n\n");

    return 0;

}
