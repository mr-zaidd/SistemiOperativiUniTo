#include "../include/inc.h"
#include "../include/mappa.h"

void printMX(cella* arr, int size, int enter){

    int count = 0;
    int capo = 0;

    for(; count < size; count++){

        printf("%c  ", arr[count].occupata ? 'X' : '.');
        if(capo == (enter-1)){
            printf("\n\n");
            capo = 0;
        }else
            capo++;

    }
}


void updateCella(cella* arr, int att, int cap){

    int i = 0;
    for(; i < W*H; i++){

        arr[i].attNSec = att;
        arr[i].capacity = cap;
        arr[i].richiesta = 0;

    }

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


void createMappa(int myKey, int holes, int att, int cap){

    cella* arr;

    int sizeMem;
    int sizeMatx;

    int shmid;
    int i;
    int count;
    cella c;

    sizeMem = W * H * sizeof(cella);
    sizeMatx = W * H;
    shmid = shmget(myKey, sizeMem, IPC_CREAT | 0666);

    if(shmid == -1)
        printf("SHMGET NON HA FUNZIONATO");

    arr = (cella*)shmat(shmid, NULL, 0);
    i = 0;
    count = holes;
    c.occupata = 0;

    for(; i < sizeMatx; i++){
        arr[i] = c;
    }

    printf("\nCreazione MAPPA =>\n");
    printf("\nImpostazione di attributi celle...\n");
    updateCella(arr, att, cap);
    printf("\nStiamo posizionando gli HOLES...");
    printf("\n\n");

    fflush(stdout);

    while(count > 0){
        if(insertHoles(arr)){
            count--;
            printf("\rETA: %2ds", count);
            fflush(stdout);
        }
    }

    printf("\n\nMAPPA:\n\n");
    printMX(arr, sizeMatx, W);

    shmdt(arr);

    printf("\n\n");

}

