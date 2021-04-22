
#include "../include/inc.h"

int createshm(){

    int shmid;
    int size;
    size = W*H*sizeof(cell);
    shmid = shmget(readKey(), size, IPC_CREAT | 0666);

    if(shmid == -1){
        perror("SHMGET");
        exit(1);
    }

    return shmid;

}

int getshmid(){

    int shmid;
    shmid = shmget(readKey(), 0, IPC_CREAT | 0666);
    if(shmid == -1)
        return -1;
    return shmid;

}

void deleteshm(){

    struct shmid_ds shmid_ds, *buf;
    buf = &shmid_ds;

    shmctl(getshmid(), IPC_STAT, buf);
    if(buf->shm_nattch == 0){
        if((shmctl(getshmid(), IPC_RMID, 0)) == -1){
            perror("\nEliminazione SHM Aborted");
        }else
            printf("\nSHM ELIMINATA\n");
    }else{
        perror("\nAttachments alla shm\n");
    }

}

int checkOne(int i, int j){

    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    if(head[i][j].one == 1){
        shmdt(head);
        return 0;
    }else{
        shmdt(head);
        return 1;
    }

}


int checkPosition(int i, int j){

    int pos;

    if(i==0 && j==0){
        pos = 1; /* angolo alto sinistro */
    }else if(i==0 &&j==W){
        pos = 2; /* angolo alto destro */
    }else if(i!=H && i!=0 && j==0){
        pos = 3; /* lato sinistro */
    }else if(i!=H && i!=0 && j==W){
        pos = 4; /* lato destro */
    }else if(i==H && j==0){
        pos = 5; /* angolo basso sinistro */
    }else if(i==H && j==W){
        pos = 6; /* angolo basso destro */
    }else if(i==0 && j!=0 && j!=W){
        pos = 7; /* lato alto */
    }else if(i==H && j!=0 && j!=W){
        pos = 8; /* lato basso */
    }else
        pos = 9; /* posizione libera */

    return pos;
}

int checkFreedom(int i, int j, int pos){

    

}


void holesHandler(int holes){

    int i;
    int j;
    int pos;
    int tmp;
    int free;

    while(holes != 0){
        srand(time(NULL));
        i = rand()%(H+1);
        j = rand()%(W+1);
        tmp = checkOne(i,j);
        if(tmp == 1){
            pos = checkPosition(i,j);
            free = checkPosition(i, j, pos);
            if(free == 1){
                insertHole(i, j);
                holes--;
            }
        }
    }

}







