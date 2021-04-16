#include "../include/mylib.h"

int createshm(){

    int shmid;
    int size;
    cell* shmAt[H][W];
    size = W*H*sizeof(cell);;
    shmid = shmget(readKey(), size, IPC_CREAT | 0666);

    if(shmid == -1){
        perror("SHMGET");
        exit(1);
    }

    fillshm(shmid);
    return shmid;

}

int readKey(){

    FILE* fp;
    int key;
    char k;
    fp = fopen("tmp/key","r");
    k = fgetc(fp);
    key = atoi(&k);
    fclose(fp);
    return key;
}

void removeshm(int shmid, cell** shmAt){

    shmdt(*shmAt);
    shmctl(shmid, IPC_RMID, 0);

}

void fillshm(int shmid){

    int i;
    int j;
    cell* head[W][H];
    head[W][H] = (cell*)shmat(shmid,NULL,0);
    for(i=0; i<W; i++){
        for(j=0;j<H; j++){
            if((i%2) != 0)
                head[i][j] -> one = 1;
            else
                head[i][j] -> one = 0;
        }
    }
}

void holeshm(){}

void createKeyFile(int key){

    FILE* tmp = fopen("tmp/key","w");
    if(tmp == NULL){
        puts("\nImpossibile creare file tmp...\n");
        exit(EXIT_FAILURE);
    }else{
        puts("\nCreazione file tmp...\n");
        fputs(key,tmp);
        fclose(tmp);
    }
}

void printConf(conf* confg){

    printf(
            "\nTAXI: %d\nSOURCE: %d\nHOLES: %d\nCAPACITA: %d\nATTRAVERSAMENTO CELLA: %d\nTIMEOUT: %d\nDURATION: %d\n",
            confg -> soTaxi,
            confg -> soSources,
            confg -> soHoles,
            confg -> soCap,
            confg -> soTime,
            confg -> soTimeOut,
            confg -> soDuration
            );

}

void parse(conf* confg, char* path){

    FILE* fp = fopen(path, "r");
    char line[512];
    int confs[9] = {0};
    int j = 0;

    if(fp == NULL){

        perror("\nFile di Configurazione non trovato...\n");
        exit(1);

    }

    while(fgets(line, sizeof(line), fp)){

        char* tok;
        tok = strtok(line, ",");

        while(tok != NULL){

            if(isdigit(*tok)){

                confs[j] = atoi(tok);
                j++;

            }

            tok = strtok(NULL, ",");

        }

    }

    srand(time(0));

    confg -> soTaxi = confs[0];
    confg -> soSources = confs[1];
    confg -> soHoles = confs[2];
    confg -> soCap = (rand()%(confs[4]-confs[3]+1)) + confs[3];
    confg -> soTime = (rand()%(confs[6]-confs[5]+1)) + confs[5];
    confg -> soTimeOut = confs[7];
    confg -> soDuration = confs[8];

    if(
        !(confg -> soTaxi > 0
        &&
        confg -> soSources > 0
        &&
        confg -> soHoles < W*H
        &&
        confg -> soCap > 0
        &&
        confg -> soTime > 0
        &&
        confg -> soTimeOut > 0
        &&
        confg -> soDuration > 0)
    ){
        perror("Parametri del file di Configurazione Non Validi");
        exit(EXIT_FAILURE);
    }
}
