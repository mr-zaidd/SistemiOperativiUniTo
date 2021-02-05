#include "./include/inc.h"
#include "./include/mappa.h"
#include "./include/parse.h"
#include "./include/sigLib.h"

void deallocazione(int, conf*);

void deallocazione(int mykey, conf* sConf){

    int shmid = shmget(mykey, 0, IPC_CREAT | 0666);
    int msgid = msgget(mykey, IPC_CREAT | 0666);
    printf("\n\nSto deallocando tutto\n\n");
    fflush(stdout);
    shmctl(shmid, IPC_RMID, 0);
    msgctl(msgid, IPC_RMID, NULL);
    free(sConf);

}

int main(){

    struct sigaction sa;
    int myKey = ftok(".",'X');
    int c = 0;
    FILE* fp;
    char buff[16];
    conf* sConf = (conf*) malloc(sizeof(conf));
    char* pathConf = "../conf.csv";
    char* pathKey = "./tmp/key";
    pid_t figli[2];
    char* argR[2];
    char str[12];
    char* argT[4];
    char rts[12];
    char trs[12];
    char rst[12];

    /* IMPOSTAZIONE SIGNAL HANDLER */
    bzero(&sa, sizeof(sa));
    sa.sa_handler = sigHandlerDefault;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGCHLD, &sa, NULL);

    /* CREAZIONE FILE KEY E SALVATAGGIO */
    sprintf(buff, "%d", myKey);
    fp = fopen(pathKey, "w");
    fprintf(fp, buff);
    fclose(fp);

    /* CREAZIONE E VERIFICA PARAMETRI E MAPPA */
    parse(sConf, pathConf);
    printConf(sConf);
    createMappa(myKey, sConf->holes, sConf->attCell, sConf->cap);

    /* CREAZIONE MASTER RICHIESTE */
    printf("\nStiamo creando il Master Richieste\n");
    argR[0] = "./mRichieste";
    sprintf(str, "%d", sConf -> nSource);
    argR[1] = str;
    if( (figli[0]  = fork()) == -1 ){

        perror("\n\nErrore nella generazione di Master Richieste\n\n");
        deallocazione(myKey, sConf);
        exit(EXIT_FAILURE);

    }else if( figli[0] == 0 )
        execvp(argR[0], argR);

    /* CREAZIONE MASTER TAXI
    printf("\nStiamo creando il Master Taxi\n");*/
    argT[0] = "./mTaxi";
    sprintf(rts, "%d", sConf -> nTaxi);
    argT[1] = rts;
    sprintf(trs, "%d", sConf -> tOut);
    argT[2] = trs;
    sprintf(rst, "%d", sConf -> cap);
    argT[3] = rst;
    if( (figli[1] = fork()) == -1 ){

        perror("\n\nErrore nella generazione di Master Taxi\n\n");
        deallocazione(myKey, sConf);
        exit(EXIT_FAILURE);

    }else if( figli[1] == 0 ){
        execvp(argT[0], argT);
    }

    /* TIMER DURATION */
    printf("\n\nAlarm Settato\n\n");
    alarm(sConf->dur);

    /* ATTESA MORTE DI MASTER TAXI E MASTER RICHIESTE */
    for(; c < 2; c++)
        waitpid(WAIT_ANY, NULL, 0);

    /* RIMOZIONE ALLOCAZIONI GENERICHE */
    deallocazione(myKey, sConf);

    return 0;


}
