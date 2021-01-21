#include "../include/inc.h"
#include "../include/mappa.h"

#define WIDTH 60
#define HEIGHT 20
#define HOLES 50

/*
typedef struct cella{

    int occupata;

}cella;

 Prototipi
int shmCreate(int, int);

 Codice */

int shmCreate(int mykey, int sizeMem){

    int shmid = shmget(mykey, sizeMem, IPC_CREAT | 0666);
    return shmid;

}


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
    idx = rand()%(WIDTH * HEIGHT);

    i = idx/WIDTH;
    j = idx-(i*WIDTH);

    if( (arr[idx].occupata == 1) || (i==0) || (j==0) || (i==(HEIGHT-1)) || (j==(WIDTH-1)) )
        return 0;
    else{

        aD = (i-1)*WIDTH+(j-1);
        aC = (i-1)*WIDTH+j;
        aS = (i-1)*WIDTH+(j+1);
        cD = i*WIDTH+(j-1);
        cS = i*WIDTH+(j+1);
        bD = (i+1)*WIDTH+(j-1);
        bC = (i+1)*WIDTH+j;
        bS = (i+1)*WIDTH+(j+1);

        if( (arr[aD].occupata == 0) && (arr[aC].occupata == 0) && (arr[aS].occupata == 0) && (arr[cD].occupata == 0) && (arr[cS].occupata == 0) && (arr[bD].occupata == 0)  && (arr[bC].occupata == 0) && (arr[bS].occupata == 0) ){

            arr[idx].occupata = 1;
            return 1;

        }
    }
    return 0;
}


int mainMappa(int mykey){

    cella* arr;

    int sizeMem = WIDTH*HEIGHT*sizeof(arr);
    int sizeMatrix = HEIGHT*WIDTH;

    int shmid = shmCreate(mykey,sizeMem);
    int i;
    int count;
    int b = 0;
    cella c;
    int a;


    arr = (cella*)shmat(shmid, NULL, 0);
    i = 0;
    count = HOLES;
    c.occupata = 0;
    for(i; i < sizeMatrix; i++){
        arr[i] = c;
    }

    printf("\n\nMAPPA:\n\n");

    for(a = 0; a < HEIGHT*WIDTH; a++){
        printf("%c  ", arr[a].occupata ? 'X' : '.');
        if(b == WIDTH-1){
            printf("\n\n");
            b = 0;
        }else
            b++;
    }


    printf("\n\nStiamo posizionando gli HOLES...");
    printf("\n\n\n");
    fflush(stdout);

    while(count > 0){
        if(insertHoles(arr)){
            count--;
        }
    }

    if(fork() == 0){

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

    wait(NULL);

    shmdt(arr);

    printf("\n\n");

    return 0;

}
