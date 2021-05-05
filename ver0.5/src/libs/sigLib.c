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
    system(cmd);

    strcpy(cmd2, "ipcrm -s");
    sprintf(key2, "%d", semid);
    strcat(cmd2, key2);
    system(cmd2);


    strcpy(cmd3, "ipcrm -s");
    sprintf(key3, "%d", semiddds);
    strcat(cmd3, key3);
    system(cmd3);


    printf("\nDEBUG: Arrivato segnale di INTERRUZIONE - shm e sems eliminati forzatamente\n");
    exit(EXIT_FAILURE);

}

