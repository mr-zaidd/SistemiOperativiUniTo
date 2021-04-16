#include "include/inc.h"
#include "include/mylib.h"

int main(int argc, int *argv[]){

    int key;
    int shmid;
    int (*shmAt)[H];
    int i = 0;
    int j = 0;

    key = ftok(".", 'b');
    createKeyFile(key);
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

    for(i=0; i<H; i++){

        for(j=0; j<W; j++){

            shmAt[i][j] = 1;

        }

    }


    for(i=0; i<H; i++){
        for(j=0; j<W; j++){
            printf("%d\t", shmAt[i][j]);
        }
        printf("\n");
    }

    shmdt(shmAt);
    shmctl(shmid, IPC_RMID, 0);

    return 0;

}
