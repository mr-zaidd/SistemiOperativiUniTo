#include "include/inc.h"

static void ccHandler(){

    char cmd[16];
    char key[8];
    strcpy(cmd, "ipcrm -m");
    sprintf(key, "%d", getshmid());
    strcat(cmd, key);
    system(cmd);
    printf("\nDEBUG: Arrivato segnale di INTERRUZIONE - shm eliminata forzatamente\n");
    exit(EXIT_FAILURE);

}

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
    struct sigaction sa;
    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = ccHandler;
    sigaction(SIGINT, &sa, NULL);

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

    waitpid(WAIT_ANY, NULL, 0);
    **/

    shmdt(shmAt);
    deleteshm();;
    free(confg);
    free(dur);
    free(timeOut);
    return 0;

}

