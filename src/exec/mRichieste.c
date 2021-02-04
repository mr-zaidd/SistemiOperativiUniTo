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
            kill(SIGKILL, 0);
            exit(0);
        default:
            kill(SIGTERM, 0);
            exit(0);

    }

}

/* CREA RICHIESTA */
void createRichiesta(int j, pid_t* richild, int nSource){

    if( (richild[j] = fork()) == -1 ){

        perror("\n\nErrore nella generazione di un processo richiesta. ERRNO = '%s'\n\n", strerror(errno));
        killAllRichiesta(richild, nSource);
        exit(EXIT_FAILURE);

    }else if( richild[j] == 0 ){

        execvp("./richiesta", NULL);

    }

}

/* AMMAZZA TUTTE LE RICHIESTE */
void killAllRichieste(pid_t* richild, int nSource){

    int i = 0;

    for(; i < nSource; i++)
        kill(richild[i], SIGKILL);
    exit(0);

}



int main(int argc, char* argv[]){

    int nSource = atoi(argv[1]);
    pid_t richild[nSource] = {0}
    pid_t killedChild;
    int nbChild = 0;
    int i = 0;
    int j = 0;
    struct sigaction sa;

    bzero(&sa, sizeof(sa));
    sa.sa_handler = sigHandlerRich;
    sigaction(SIGTERM, &sa, NULL);


    /* CREAZIONE FIGLI RICHIESTE */
    for(; i < nSource; i++){

        if( (richild[i] = fork()) == -1 ){

            perror("\n\nErrore nella generazione di un processo richiesta. ERRNO = '%s'\n\n", strerror(errno));
            exit(EXIT_FAILURE);

        }else if( richild[i] == 0 ){

            execvp("./richiesta", NULL);

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


    return 0;

}
