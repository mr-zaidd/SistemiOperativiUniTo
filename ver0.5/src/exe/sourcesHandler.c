#include "../include/inc.h"


pid_t* figli;
int semid;
int msgid;

void muoio(int signum, siginfo_t* info, void* context){

    if(signum == SIGTERM){
        semctl(semid, 0, IPC_RMID, 0);
        /**msgctl(msgid, IPC_RMID, NULL);**/
        free(figli);
        kill(0, SIGTERM);
        exit(EXIT_SUCCESS);
    }

}

int main(int argc, char* argv[]){

    int nSources = atoi(argv[1]);
    int counter = 0;
    char* ch[3];
    struct sigaction sa;
    ch[0] = "./exe/source";
    ch[1] = NULL;

    figli = (pid_t*)malloc(nSources*sizeof(pid_t));

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = muoio;
    sigaction(SIGTERM, &sa, NULL);

    semid = semget(SKEY, 1, IPC_CREAT | 0666);
    semctl(semid, 0, SETVAL, 1);

    msgid = msgget(MKEY, IPC_CREAT | 0666);

    if(msgid == -1){
        printf("\nDEBUG: ");
        perror(strerror(errno));
    }

    while(counter != nSources){

        if((figli[counter] = fork()) == -1){

            printf("\nDEBUG: Source non generata da SourceHandler\n");

        }else if(figli[counter] == 0){

            execvp("./exe/source", ch);
        }

        counter++;

    }

    for(counter = 0; counter < nSources; counter++)
        waitpid(WAIT_ANY, NULL, 0);

    return 0;

}
