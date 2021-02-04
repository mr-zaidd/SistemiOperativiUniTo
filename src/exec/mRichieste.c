#include "../include/inc.h"
#include "../include/mappa.h"
#include "../include/parse.h"

void createRichiesta(int, pid_t*, int);
void killAllRichieste(pid_t*, int);
void sigHandlerRich(int);

/* HANDLER */
void sigHandlerRich(int signum){

    switch(signum){

        case SIGTERM:
            printf("\n\nSIGTERM Arrivato a MASTER RICHIESTE\n\n");
            fflush(stdout);
            kill(0, SIGKILL);
            exit(0);
        default:
            kill(0, SIGTERM);
            exit(0);

    }

}

/* CREA RICHIESTA */
void createRichiesta(int j, pid_t* richild, int nSource){

    char* args[] = {NULL};
    if( (richild[j] = fork()) == -1 ){

        printf("\n\nErrore nella generazione di un processo richiesta. ERRNO = '%s'\n\n", strerror(errno));
        killAllRichieste(richild, nSource);
        exit(EXIT_FAILURE);

    }else if( richild[j] == 0 ){

        execvp("./richiesta", args);

    }

}

/* AMMAZZA TUTTE LE RICHIESTE */
void killAllRichieste(pid_t* richild, int nSource){

    int i = 0;

    for(; i < nSource; i++)
        kill(richild[i], SIGKILL);
    free(richild);
    exit(0);

}



int main(int argc, char* argv[]){

    int nSource = atoi(argv[1]);
    /*pid_t richild[nSource] = {0};*/
    pid_t* richild = (pid_t*) malloc(nSource*sizeof(pid_t));
    pid_t killedChild;
    int nbChild = 0;
    int i = 0;
    int j = 0;
    struct sigaction sa;
    char* args[] = {NULL};

    if(argc < 2){

        printf("Errore nel passare le variabili al Master Richieste");
        exit(EXIT_FAILURE);

    }

    bzero(&sa, sizeof(sa));
    sa.sa_handler = sigHandlerRich;
    sigaction(SIGTERM, &sa, NULL);


    /* CREAZIONE FIGLI RICHIESTE */
    for(; i < nSource; i++){

        if( (richild[i] = fork()) == -1 ){

            printf("\n\nErrore nella generazione di un processo richiesta. ERRNO = '%s'\n\n", strerror(errno));
            exit(EXIT_FAILURE);

        }else if( richild[i] == 0 ){

            execvp("./richiesta", args);

        }else
            ++nbChild;

    }


    /* ATTESA MORTE DI TUTTI I FIGLI */
    while(nbChild){

        killedChild = waitpid(WAIT_ANY, NULL, 0);
        for(; j < nSource; j++){

            if( killedChild == richild[j] ){
                printf("\n\nMorta la richiesta numero: %d con Pid: %d\n\n", i, (int)killedChild);
                createRichiesta(j, richild, nSource); /* SE PASSO RICHILD QUI IN QUESTO MODO IL PUNTATORE è SUL J O SULLO 0? */
                j = 0;
                ++nbChild;
            }
        }

        --nbChild;

    }

    free(richild);

    return 0;

}
