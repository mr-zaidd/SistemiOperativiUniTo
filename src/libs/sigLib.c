#include "../include/inc.h"

void sigHandlerDefault(int signum){

    FILE* fp;
    char buff[32];
    int myKey;
    int shmid;



    switch(signum){

        case SIGALRM:
            printf("\n\nAlarm ricevuto ad APP\n\n");
            kill(0, SIGTERM);
            break;
        default: 
            printf("\n\nRICEVUTO SEGNALE: %s\n\n", strsignal(signum));
            fflush(stdout);
            fp = fopen("./tmp/key", "r");
            if(fp == NULL)
                printf("\n\nE' SBAGLIATO IL PATH DELLA KEY IN SIGLIB\n\n");
            fgets(buff, 32, fp);
            myKey = atoi(buff);

            shmid = shmget(myKey, 0, IPC_CREAT | 0666);
            shmctl(shmid, IPC_RMID, 0);

            exit(EXIT_FAILURE);
    }
}
