#include "../include/inc.h"

 void ccHandler(){

    char cmd[16];
    char key[8];
    strcpy(cmd, "ipcrm -m");
    sprintf(key, "%d", getshmid());
    strcat(cmd, key);
    system(cmd);
    printf("\nDEBUG: Arrivato segnale di INTERRUZIONE - shm eliminata forzatamente\n");
    exit(EXIT_FAILURE);

}

