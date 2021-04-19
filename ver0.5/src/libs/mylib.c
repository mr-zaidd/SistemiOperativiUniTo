#include "../include/mylib.h"

int createshm(){

    int shmid;
    int size;
    size = W*H*sizeof(cell);
    shmid = shmget(readKey(), size, IPC_CREAT | 0666);

    if(shmid == -1){
        perror("SHMGET");
        exit(1);
    }

    printf("DEBUG: Creata SHM\n");

    fillshm(shmid);
    return shmid;

}

int getshmid(){

    int shmid;
    shmid = shmget(readKey(), 0, IPC_CREAT | 0666);
    if(shmid == -1)
        return -1;
    return shmid;

}

int readKey(){

    FILE* fp = fopen("tmp/key", "r");
    int k = 0;

    while(!feof(fp))
        fscanf(fp, "%d", &k);
    fclose(fp);
    return k;

}

void removeAll(int shmid){

    struct shmid_ds shmid_ds, *buf;
    char* path = "tmp/key";
    buf = &shmid_ds;

    shmctl(shmid, IPC_STAT, buf);
    if(buf->shm_nattch == 0){
        if((shmctl(shmid, IPC_RMID, 0)) == -1){
            perror("\nEliminazione SHM non andata a buon fine, att -> 0\n");
        }else
            printf("\nSHM ELIMINATA\n");
    }else{
        perror("\nCi sono ancora attachments alla shm da altri processi\n");
        /* Scrivere la funzione di uccisione di tutti i processi */
    }

    remove(path);

}

void fillshm(int shmid){

    int i;
    int j;
    cell (*head)[W];
    head = shmat(shmid,NULL,0);
    for(i=0; i<H; i++){
        for(j=0;j<W; j++){
            if((i%2) != 0)
                head[i][j].one = 1;
            else
                head[i][j].one = 0;
        }
    }
    shmdt(head);
    printf("DEBUG: FILL SHM eseguito\n");
}

void insertHole(int i, int j){

    int shmid = getshmid();
    cell (*head)[W] = shmat(shmid, NULL, 0);

    head[i][j].one = 1;

    shmdt(head);

}

int checkFreedom(int i, int j, char* pos){

    int shmid = getshmid();
    cell (*head)[W] = shmat(shmid, NULL, 0);
    int intPos = 0;
    if(strcmp(pos,"angoloSxA") == 0)
        intPos = 1;
    if(strcmp(pos,"angoloDxA") ==  0)
        intPos = 2;
    if(strcmp(pos, "angoloSxB") == 0)
        intPos = 3;
    if(strcmp(pos, "angoloDxB") == 0)
        intPos = 4;
    if(strcmp(pos, "latoSx") == 0)
        intPos = 5;
    if(strcmp(pos, "latoDx") == 0)
        intPos = 6;
    if(strcmp(pos, "latoA") == 0)
        intPos = 7;
    if(strcmp(pos,"latoB") == 0)
        intPos = 8;

    switch(intPos){

        case 1:
            if(head[i][j+1].one == 0){
                if(head[i+1][j].one == 0){
                    if(head[i+1][j+1].one == 0){
                        shmdt(head);
                        return 1;
                    }
                }
            }
            shmdt(head);
            return 0;
        case 2:
            if(head[i][j-1].one == 0){
                if(head[i+1][j].one == 0){
                    if(head[i+1][j-1].one == 0){
                        shmdt(head);
                        return 1;
                    }
                }
            }
            shmdt(head);
            return 0;
        case 3:
            if(head[i][j+1].one == 0){
                if(head[i-1][j].one == 0){
                    if(head[i-1][j+1].one == 0){
                        shmdt(head);
                        return 1;
                    }
                }
            }
            shmdt(head);
            return 0;
        case 4:
            if(head[i][j-1].one == 0){
                if(head[i-1][j].one == 0){
                    if(head[i-1][j-1].one == 0){
                        shmdt(head);
                        return 1;
                    }
                }
            }
            shmdt(head);
            return 0;
        case 5:
            if(head[i][j+1].one == 0){
                if(head[i+1][j].one == 0){
                    if(head[i-1][j+1].one == 0){
                        if(head[i+1][j+1].one == 0){
                            if(head[i-1][j].one == 0){
                                shmdt(head);
                                return 1;
                            }
                        }
                    }
                }
            }
            shmdt(head);
            return 0;
        case 6:
            if(head[i][j-1].one == 0){
                if(head[i+1][j].one == 0){
                    if(head[i-1][j-1].one == 0){ 
                        if(head[i+1][j-1].one == 0){
                            if(head[i-1][j].one == 0){
                                shmdt(head);
                                return 1;
                            }
                        }
                    }
                }
            }
            shmdt(head);
            return 0;
        case 7:
            if(head[i][j-1].one == 0){
                if(head[i+1][j].one == 0){ 
                    if(head[i+1][j-1].one == 0){
                        if(head[i-1][j].one == 0){
                            if(head[i-1][j-1].one == 0){
                                shmdt(head);
                                return 1;
                            }
                        }
                    }
                }
            }
            shmdt(head);
            return 0;
        case 8:
            if(head[i][j-1].one == 0){
                if(head[i][j+1].one == 0){
                    if(head[i-1][j].one == 0){
                        if(head[i-1][j-1].one == 0){
                            if(head[i-1][j+1].one == 0){
                                shmdt(head);
                                return 1;
                            }
                        }
                    }
                }
            }
            shmdt(head);
            return 0;
        default:
            if(head[i][j+1].one == 0){
                if(head[i][j-1].one == 0){
                    if(head[i+1][j].one == 0){
                        if(head[i+1][j+1].one == 0){
                            if(head[i+1][j-1].one == 0){
                                if(head[i-1][j].one == 0){
                                    if(head[i-1][j+1].one == 0){
                                        if(head[i-1][j-1].one == 0){
                                            shmdt(head);
                                            return 1;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            shmdt(head);
            return 0;
    }
}

void holesHandler(){

    char* pos;
    int tmp;
    int i;
    int j;
    int ins = 1;

    srand(time(0));

    while(ins){

        i = rand()%(H+1);
        j = rand()%(W+1);
        pos = checkPosition(i, j);
        tmp = checkFreedom(i, j, pos);
        if(tmp){
            insertHole(i, j);
            ins = 0;
        }

    }
}

char* checkPosition(int i, int j){

    char* posizione;
    if(i==0 && j==0)
        return posizione="angoloSxA";
    else if(i==0 && j==W)
        return posizione="angoloDxA";
    else if(i!=H && i!=0 && j==0)
        return posizione="latoSx";
    else if(i!=H && i!=0 && j==W)
        return posizione="latoDx";
    else if(i==H && j==0)
        return posizione="angoloSxB";
    else if(i==H && j==W)
        return posizione="angoloDxB";
    else if(i==0 && j!=0 && j!=W)
        return posizione="latoA";
    else if(i==H && j!=0 && j!=W)
        return posizione="latoB";
    else
        return posizione="interno";
}

void createKeyFile(int key){

    FILE* tmp = fopen("tmp/key","w");
    char k[16];
    sprintf(k, "%d", key);
    if(tmp == NULL){
        puts("\nImpossibile creare file tmp...\n");
        exit(EXIT_FAILURE);
    }else{
        puts("\nCreazione file tmp...\n");
        fputs(k,tmp);
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

void parseConf(conf* confg, char* path){

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
