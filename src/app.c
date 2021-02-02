#include "./include/inc.h"
#include "./include/mappa.h"
#include "./include/parse.h"

int main(){

    int shmid;
    int myKey = ftok(".",'X');
    FILE* fp;
    char buff[16];
    conf* sConf = (conf*) malloc(sizeof(conf));
    char* pathConf = "../conf.csv";
    char* pathKey = "./tmp/key";

    /* CREAZIONE FILE KEY E SALVATAGGIO */
    sprintf(buff, "%d", myKey);
    fp = fopen(pathKey, "w");
    fprintf(fp, buff);
    fclose(fp);

    /* CREAZIONE E VERIFICA PARAMETRI E MAPPA */
    parse(sConf, pathConf);
    printConf(sConf);
    createMappa(myKey, sConf->holes);

    /* CREAZIONE FIGLI TAXI E FIGLI RICHIESTE */



    /* RIMOZIONE ALLOCAZIONI GENERICHE */
    free(sConf);
    shmid = shmget(myKey, 0, IPC_CREAT | 0666);
    shmctl(shmid, IPC_RMID, 0);


    return 0;


}
