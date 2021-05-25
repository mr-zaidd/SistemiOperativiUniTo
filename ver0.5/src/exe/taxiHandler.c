#include "../include/inc.h"

int semid;
pid_t* figli;
char* ch[3];
int c;

void createAgain(int signum, siginfo_t* info, void* context){

    if(signum == SIGUSR1){
        if((figli[c] = fork()) == -1){
            printf("Taxi %d non generato", figli[c]);
        }else if(figli[c] == 0){
            /**
            printf("\nDEBUG: FIGLIO del TAXI\n");
            exit(0);**/
            printf("\nDEBUG: Figlio partorito da taxiHandler! PidT: %d\n", getpid());
            execvp("./exe/taxi", ch);
        }
    }else if(signum == SIGTERM){
        kill(0, SIGTERM);
        exit(EXIT_SUCCESS);
    }
}



int main(int argc, char* argv[]){

    int nTaxi = atoi(argv[1]);
    char* dur = argv[2];
    int tmp = 0;
    struct sigaction sa;
    pid_t killed;
    int semidapp = semget(APPKEY, 1, IPC_CREAT | 0666);

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = createAgain;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    figli = (pid_t*)malloc(nTaxi*sizeof(pid_t));

    ch[0] = "./taxi";
    ch[1] = dur;
    ch[2] = NULL;

    if(argc>3)
        /** Rise segnale per exit(1) e chiusura di HandlerSource e chiusura App **/

    printf("\nDEBUG: Numero dei Taxi da generare %d\n", nTaxi);

    semid = semget(TKEY, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 1);

    while(tmp != nTaxi){

        if((figli[tmp] = fork()) == -1){

            printf("Taxi %d non generato", tmp);

        }else if(figli[tmp] == 0){

            /**
            printf("\nDEBUG: FIGLIO del TAXI\n");
            exit(0);
            **/
            printf("\nDEBUG: Figlio partorito da taxiHandler! PidT: %d\n", getpid());
            execvp("./exe/taxi", ch);

        }
        ++tmp;

    }



    semctl(semidapp, 0, SETVAL, 0);



    while(1){
        killed = waitpid(WAIT_ANY, NULL, 0);
        for(c = 0; c < nTaxi; c++){
            if(killed == figli[c]){
                raise(SIGUSR1);
                /**break;**/
            }
        }
    }

/**
    for(c=0; c<nTaxi; c++)
        waitpid(WAIT_ANY, NULL, 0);
**/

    printf("\nDEBUG: Morti tutti i figli del TaxiHandler\n");
    semctl(semid, 0, IPC_RMID, 0);

    free(figli);

    return 0;

}
