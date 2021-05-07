#include "../include/inc.h"

 void ccHandler(){

    char cmd[16];
    char key[8];

    char cmd2[16];
    char key2[8];
    int semid = semget(readKey(), 0, IPC_CREAT | 0666);

    char cmd3[16];
    char key3[8];
    int semiddds = semget(17, 0, IPC_CREAT | 0666);


    strcpy(cmd, "ipcrm -m");
    sprintf(key, "%d", getshmid());
    strcat(cmd, key);
    if(system(cmd) == -1){
        printf("\nDEBUG: ID: %d Shared Memory non trovato - Non esiste\n", getshmid());
    }

    strcpy(cmd2, "ipcrm -s");
    sprintf(key2, "%d", semid);
    strcat(cmd2, key2);
    if(system(cmd2) == -1){
        printf("\nDEBUG: ID Semaforo Mappa non trovato - Non esiste\n");
    }

    strcpy(cmd3, "ipcrm -s");
    sprintf(key3, "%d", semiddds);
    strcat(cmd3, key3);
    if(system(cmd3) == -1){
        printf("\nDEBUG: ID Semaforo Taxi non trovato - Non esiste\n");
    }

    printf("\nDEBUG: Arrivato segnale di INTERRUZIONE - shm e sems eliminati forzatamente\n");
    exit(EXIT_FAILURE);

}

