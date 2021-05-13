#include "../include/inc.h"

void muori(int signum, siginfo_t* info, void* context){

    if(signum == SIGTERM){
        exit(EXIT_SUCCESS);
    }else if(signum == SIGUSR1){
        printf("\nDEBUG: Richiesta completata\n");
        fflush(stdout);
        exit(EXIT_SUCCESS);
    }else{

        printf("\nDEBUG: SIGNUM RICHIESTA: %d\n", signum);
        exit(33);
    }

}

int main(int argc, char* argv[]){

    int c = 0;

    int i = atoi(argv[1]);
    int j = atoi(argv[2]);
    int msgid = msgget(MKEY, IPC_CREAT | 0666);
    struct sigaction sa;
    mex invio;
    int shift = randomizeNum(randomizeNum(4,getpid()),100);
    size_t inviolength;
    int semidapp = semget(APPKEY, 1, 0666);
    struct sembuf myopapp;

    myopapp.sem_num = 0;
    myopapp.sem_flg = 0;
    myopapp.sem_op = 0;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = muori;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    invio.mtype = INVIO;
    invio.arrivi[0] = i;
    invio.arrivi[1] = j;
    invio.arrivi[2] = randomizeNum(getpid()*shift, H);
    invio.arrivi[3] = randomizeNum(getpid()*shift+2, W);
    invio.pidRic = getpid();

    inviolength = sizeof(invio.arrivi) + sizeof(pid_t);

    semop(semidapp, &myopapp, 1);

    if((msgsnd(msgid, &invio, inviolength, IPC_NOWAIT)) < 0){

        printf("\nDEBUG: Messaggio non inviato da PID: %d\n", getpid());

    }

    return 0;

}
