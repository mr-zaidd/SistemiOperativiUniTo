#include "../include/inc.h"
#include "../include/mappa.h"
#include "../include/parse.h"

int maxTaxi = 0;

void createTaxi(int, pid_t*, int, int);
void killAllTaxi(pid_t*, int);
void sigHanderTax(int);

void createTaxi(int j, pid_t* taxchild, int nTaxi, int timeOut){

    char str[12];
    char* args[2];
    sprintf(str, "%d", timeOut);
    args[0] = "./taxi";
    args[1] = str;
    if( (taxchild[j] = fork()) == -1 ){
        printf("\nERRORE NELLA GENERAZIONE DI UN PROCESSO TAXI. ERRNO = '%s'\n", strerror(errno));
        killAllTaxi(taxchild, nTaxi);
    }else if( taxchild[j] == 0 )
        execvp("./taxi", args);

}

void killAllTaxi(pid_t* taxchild, int nTaxi){

    int i = 0;

    for(; i < nTaxi; i++)
        kill(taxchild[i], SIGKILL);
    free(taxchild);
    exit(0);

}

void sigHandlerTax(int signum){

    int i;

    switch(signum){

        case SIGTERM:
            kill(0, SIGTERM);
            for(i = 0; i < maxTaxi; i++)
                wait(NULL);
            exit(0);
        default:
            kill(0, SIGTERM);
            for(i = 0; i < maxTaxi; i++)
                wait(NULL);
            exit(0);
    }

}


int main(int argc, char* argv[]){

    int nTaxi = atoi(argv[1]);
    int timeOut = atoi(argv[2]);
    int capacity = atoi(argv[3]);
    pid_t* taxchild = (pid_t*) malloc(nTaxi*sizeof(pid_t));
    pid_t killedTaxi;
    int nCT = 0;
    int i;
    int j;
    struct sigaction sa;
    char* args[3];
    char str[12];
    char rts[12];
    maxTaxi = nTaxi;

    printf("SONO IL MTAXI");
    fflush(stdout);

    sprintf(rts, "%d", capacity);
    sprintf(str, "%d", timeOut);
    args[0] = "./taxi";
    args[1] = str;
    args[2] = rts;

    if(argc < 3){

        printf("\nERRORE NEL PASSARE LE VARIABILI AL MASTER TAXI\n");
        exit(EXIT_FAILURE);

    }

    bzero(&sa, sizeof(sa));
    sa.sa_handler = sigHandlerTax;
    sigaction(SIGTERM, &sa, NULL);

    printf("\n nTaxi: %d\n", nTaxi);
    /* CREAZIONE FIGLI TAXI */
    for(i = 0; i < nTaxi; i++){

        if( (taxchild[i] = fork()) == -1 ){

            printf("\nERRORE NELLA GENERAZIONE DI UN PROCESSO TAXI. ERRNO = '%s'\n", strerror(errno));
            exit(EXIT_FAILURE);

        }else if( taxchild[i] == 0 ){

            execvp("./taxi", args);

        }else
            ++nCT;

    }


    /* ATTESA MORTE DI TUTTI I FIGLI FALZO */
    while(nCT){

        killedTaxi = waitpid(WAIT_ANY, NULL, 0);
        for(j = 0; j < nTaxi; j++){

            if( killedTaxi == taxchild[i] ){

                printf("\nMORTO IL TAXI NUMERO: %d CON PID:%d\n", j, (int)killedTaxi);
                createTaxi(j, taxchild, nTaxi, timeOut);
                ++nCT;

            }

        }
        --nCT;

    }

    free(taxchild);

    return 0;

}
