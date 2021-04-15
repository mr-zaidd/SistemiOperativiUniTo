#include "inc.h"

int main(int argc, int *argv[]){

    int key;
    int shmid;
    int (*shmAt)[H];

    key = ftok(".", 'b');
    shmid = shmget(key,sizeof(int[H][W]), IPC_CREAT | 0666);

    if(shmid == -1){
        perror("SHMGET");
        exit(1);
    }else{
        printf("Creazione nuovo segmento SHM\n");
        shmAt = shmat(shmid, 0, 0);
        if(shmAt == (void*) -1){
            perror("SHMAT");
            exit(1);
        }
    }
}
