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



#define WIDTH 60
#define HEIGHT 20
#define HOLES 50

int shmCreate(int, int);

typedef struct cella{

    int occupata;

}cella;

int shmCreate(int mykey, int sizeMem){

    int shmid = shmget(mykey, sizeMem, IPC_CREAT | 0666);
    return shmid;

}

int main(){


    cella* arr;

    int mykey = ftok(".", 'x');
    int sizeMem = WIDTH*HEIGHT*sizeof(arr);
    int sizeMatrix = HEIGHT*WIDTH;

    int shmid = shmCreate(mykey,sizeMem);
    arr = (cella*)shmat(shmid, NULL, 0);
    int i = 0;
    int j = 0;

    for(i; i < sizeMatrix; i++){
        cella c;
        c.occupata = 1;
        arr[i] = c;
    }

    if(fork() == 0){

        int shmidChild = shmget(mykey, sizeMem, IPC_CREAT);
        cella* arrChild = (cella*)shmat(shmidChild, 0, SHM_RDONLY);

        for(i = 0; i < HEIGHT*WIDTH; i++){
            if(j == WIDTH){
                printf("%d  ", arrChild[i].occupata);
                printf("\n\n");
                printf("\n\n%d\n\n", j);
                j = 0;
                j++;
            }else{
                 j++;
                 printf("%d  ", arrChild[i].occupata);
            }
        }

        shmdt(arrChild);
    }

    wait(NULL);

    shmdt(arr);

    shmctl(shmid, IPC_RMID, 0);

    printf("\n\n");

    return 0;

}
