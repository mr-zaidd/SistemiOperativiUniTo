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

typedef struct cella{

    int occupata;

}cella

int main(){


    int* arr;

    int mykey = ftok(".", 'x');
    int sizeMem = WIDTH*HEIGHT*sizeof(int);
    int sizeMatrix = HEIGHT*WIDTH;

    int shmid = shmget(mykey, sizeMem, IPC_CREAT | 0666);

    arr = (int*) shmat(shmid, NULL, 0);
    int i = 0;
    int j = 0;

    for(i; i < sizeMatrix; i++){
        arr[i] = i;
        //printf("\n%d\n", i);
    }

    if(fork() == 0){

        int shmidChild = shmget(mykey, sizeMem, IPC_CREAT);
        int* arrChild = shmat(shmidChild, 0, SHM_RDONLY);

        for(i = 0; i < HEIGHT*WIDTH; i++){
            if(j == WIDTH){
                j = 0;
                j++;
                printf("%d  ", arrChild[i]);
                printf("\n\n");
            }else{
                 j++;
                 printf("%d  ", arrChild[i]);
            }
        }

        shmdt((int*)shmidChild);
    }

    wait(NULL);

    shmdt((int*)shmid);

    shmctl(shmid, IPC_RMID, 0);


    return 0;

}
