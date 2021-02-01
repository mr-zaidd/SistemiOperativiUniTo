#include "../include/inc.h"

#define HOLES 50

int insertHoles(cella* arr){


    int idx;
    int i;
    int j;
    int aD;
    int aC;
    int aS;
    int cD;
    int cS;
    int bD;
    int bC;
    int bS;



    srand(time(0));
    idx = rand()%(W * H);

    i = idx/W;
    j = idx-(i*W);

    if( (arr[idx].occupata == 1) || (i==0) || (j==0) || (i==(H-1)) || (j==(W-1)) )
        return 0;
    else{

        aD = (i-1) * W + (j-1);
        aC = (i-1) * W + j;
        aS = (i-1) * W + (j+1);
        cD = i * W + (j-1);
        cS = i * W + (j+1);
        bD = (i+1) * W + (j-1);
        bC = (i+1) * W + j;
        bS = (i+1) * W + (j+1);

        if( (arr[aD].occupata == 0) && (arr[aC].occupata == 0) && (arr[aS].occupata == 0) && (arr[cD].occupata == 0) && (arr[cS].occupata == 0) && (arr[bD].occupata == 0)  && (arr[bC].occupata == 0) && (arr[bS].occupata == 0) ){

            arr[idx].occupata = 1;
            return 1;

        }
    }
    return 0;
}


void mainMappa(int mykey){

    cella* arr;

    int sizeMatrix = H * W;

    int i;
    int count;
    int b = 0;
    cella c;
    int a;

    int sizeMem = W * H * sizeof(cella);

    int shmid = shmget(mykey, sizeMem, IPC_CREAT | 0666);

    if(shmid == -1)
        printf("SHMGET NON HA FUNZIONATO");


    arr = (cella*)shmat(shmid, NULL, 0);
    i = 0;
    count = HOLES;
    c.occupata = 0;
    for(; i < sizeMatrix; i++){
        arr[i] = c;
    }

    printf("\n\n\nCreazione MAPPA =>\n\n");

    printf("\n\nStiamo posizionando gli HOLES...");
    printf("\n\n\n");
    fflush(stdout);

    while(count > 0){
        if(insertHoles(arr)){
            count--;
            printf("\rETA: %2ds", count);
            fflush(stdout);
        }
    }

    printf("\n\nMAPPA:\n\n");

    for(a = 0; a < H * W; a++){
        printf("%c  ", arr[a].occupata ? 'X' : '.');
        if(b == W - 1){
            printf("\n\n");
            b = 0;
        }else
            b++;
    }


  /*  if(fork() == 0){

        int shmidChild = shmget(mykey, sizeMem, IPC_CREAT);
        int i;
        int j;
        cella* arrChild = (cella*)shmat(shmidChild, 0, SHM_RDONLY);
        j = 0;
        printf("\n\nMAPPA CON HOLES:\n\n");
        for(i = 0; i < HEIGHT*WIDTH; i++){
            printf("%c  ", arr[i].occupata ? 'X' : '.');
            if(j == WIDTH-1){
                printf("\n\n");
                j = 0;
            }else
                j++;
        }

        shmdt(arrChild);
    }
*/
    wait(NULL);

    shmdt(arr);

    printf("\n\n");

}
/*
int main(){


    int mykey = ftok(".", 'X');
    int shmid;

    mainMappa(mykey);

    shmid = shmget(mykey, 0, IPC_CREAT | 0666);
    shmctl(shmid, IPC_RMID, 0);

    return 0;

}*/
