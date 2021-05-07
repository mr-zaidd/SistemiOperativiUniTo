#include "include/inc.h"

void printCelle(){
    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    int i = 0;
    int j = 0;

    for(; i < W; i++){
        for(; j < H; j++){
            printf("\n###CELLA %d %d###\n", i, j);
            printf("\nOne: %d\nCapacità: %d\nAttraversamento: %d\n", head[i][j].one, head[i][j].soCap, head[i][j].soTime);
        }
    }


    shmdt(head);
}

void stampaStatusSem(int semid){

    int i = 0;
    int val;
    for(i; i < W*H; i++){
        val = semctl(semid, i, GETVAL);
        printf("\nDEBUG: Semaforo %d\tValore:%d\n", i, val);
    }

}


int main(){

    int key;
    int shmid;
    int c;
    cell (*shmAt)[W];
    char* fileConf = "../conf/conf.csv";
    char* ch[4];
    char* nTaxi = (char*)malloc(16*sizeof(char));
    char* timeout = (char*)malloc(16*sizeof(char));
    conf* confg;
    pid_t figli[2];
    struct sigaction sa;
    int semid;
    int arrZero[W*H] = {0};

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = ccHandler;
    sigaction(SIGINT, &sa, NULL);

    confg = (conf*) malloc(sizeof(conf));
    key = ftok(".", 'b');
    createKeyFile(key);
    printf("DEBUG: Verifica Chiave: %d\n", readKey());
    parseConf(confg, fileConf);
    printConf(confg);
    shmid = createshm();
    semid = semget(readKey(), W*H, IPC_CREAT | 0666);
    semctl(semid, 0, SETALL, arrZero);
    stampaStatusSem(semid);
    shmAt = shmat(shmid, NULL, 0);
    fillConf(confg);
    holesHandler(confg->soHoles);
    printMtx();

    sprintf(nTaxi, "%d", confg->soTaxi);
    sprintf(timeout, "%d", confg->soTimeOut);

    ch[0] = "./exe/taxiH";
    ch[1] = nTaxi;
    ch[2] = timeout;
    ch[3] = NULL;

    if((figli[0]=fork()) == -1){

        perror("\nDEBUG: FORK ANDATO MALE\n");
        shmdt(shmAt);
        deleteshm();
        free(timeout);
        free(nTaxi);
        free(confg);
        exit(EXIT_FAILURE);

    }else if(figli[0] == 0){
        execvp(ch[0], ch);
    }

    for(c=0; c<1; c++)
        waitpid(WAIT_ANY, NULL, 0);

    printf("\nDEBUG: Morto TaxiHandler\n");

    printMtx();

    shmdt(shmAt);
    deleteshm();
    semctl(semid, 0, IPC_RMID, 0);
    free(confg);
    free(timeout);
    free(nTaxi);

    return 0;

}

