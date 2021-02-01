#include "./include/inc.h"


int main(){

    int mykey = ftok(".",'X');
    int shmid;
    conf* sConf = (conf*) malloc(sizeof(conf));
    char* path = "../conf.cs";

    /* CREAZIONE E VERIFICA PARAMETRI E MAPPA */
    parse(sConf, path);
    printConf(sConf);
    mainMappa(mykey);

    /* CREAZIONE FIGLI TAXI E FIGLI RICHIESTE */



    /* RIMOZIONE ALLOCAZIONI GENERICHE */
    free(sConf);
    shmid = shmget(mykey, 0, IPC_CREAT | 0666);
    shmctl(shmid, IPC_RMID, 0);


    return 0;


}
