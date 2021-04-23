#include "include/inc.h"

int main(){

    int key;
    int shmid;
    int c;
    cell (*shmAt)[W];
    char* fileConf = "../conf/conf.csv";
    char* ch[4];
    char* timeOut = (char*)malloc(16*sizeof(char));
    char* dur = (char*)malloc(16*sizeof(char));
    conf* confg;
    pid_t figli[2];

    confg = (conf*) malloc(sizeof(conf));
    key = ftok(".", 'b');
    createKeyFile(key);
    printf("DEBUG: READ KEY: %d\n", readKey());
    parseConf(confg, fileConf);
    printConf(confg);
    shmid = createshm();
    shmAt = shmat(shmid, NULL, 0);
    fillConf(confg);
    holesHandler(confg->soHoles);
    printMtx();
/**
    sprintf(timeOut, "%d", confg->soTimeOut);
    sprintf(dur, "%d", confg->soDuration);

    ch[0] = "./exe/taxiH";
    ch[1] = timeOut;
    ch[2] = dur;
    ch[3] = NULL;

    if((figli[0]=fork()) == -1){

        perror("\nDEBUG: FORK ANDATO MALE\n");
        shmdt(shmAt);
        removeAll(shmid);
        free(confg);
        exit(EXIT_FAILURE);

    }else if(figli[0] == 0){
        execvp(ch[0], ch);
    }

    if((figli[1]=fork()) == -1){

        perror("\nDEBUG: FORK ANDATO MALE\n");
        shmdt(shmAt);
        removeAll(shmid);
        free(confg);
        exit(EXIT_FAILURE);

    }else if(figli[1] == 0){

        execvp(ch[0], ch);
    }

    for(c=0; c<2;c++)
        waitpid(WAIT_ANY, NULL, 0);
**/

    shmdt(shmAt);
    deleteshm();;
    free(confg);
    free(dur);
    free(timeOut);
    return 0;

}

