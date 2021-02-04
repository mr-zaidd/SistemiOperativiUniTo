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
    FILE* fp;
    char buff[16];
    conf* sConf = (conf*) malloc(sizeof(conf));
    char* pathConf = "../conf.csv";
    char* pathKey = "./tmp/key";
    pid_t figli[2];
    char* args[2];
    char str[12];

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
    createMappa(myKey, sConf->holes);

    /* CREAZIONE MASTER RICHIESTE */
    printf("\n\nStiamo creando il Master Richieste\n\n");
    args[0] = "./mRichieste";
    sprintf(str, "%d", sConf -> nSource);
    args[1] = str;
    if( (figli[1]  = fork()) == -1 ){

        perror("\n\nErrore nella generazione di Master Richieste\n\n");
        deallocazione(myKey, sConf);
        exit(EXIT_FAILURE);

    }else if( figli[1] == 0 )
        execvp(args[0], args);

    printf("\n\nAlarm Settato\n\n");
    alarm(sConf->dur);

    /* CREAZIONE MASTER TAXI */
    /* DA IMPLEMENTARE */

    /* ATTESA MORTE DI MASTER TAXI E MASTER RICHIESTE */
    /* DA IMPLEMENTARE */

    waitpid(figli[1], NULL, 0);

    /* RIMOZIONE ALLOCAZIONI GENERICHE */
    deallocazione(myKey, sConf);

    return 0;


}
