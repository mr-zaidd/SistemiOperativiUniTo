#include "../include/inc.h"

int main(int argc, char* argv[]){

    int nSources = atoi(argv[1]);
    pid_t* figli = (pid_t*)malloc(nSources*sizeof(pid_t));
    int counter = 0;
    int semid;
    int msgid;
    char* ch[3];
    ch[0] = "./exe/source";
    ch[1] = NULL;

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

    printf("\nDEBUG: Morti tutti i fligi di SourcesHandler\n");


    semctl(semid, 0, IPC_RMID, 0);
    msgctl(msgid, IPC_RMID, NULL);
    free(figli);

    return 0;

}
