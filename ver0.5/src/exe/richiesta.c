#include "../include/inc.h"

void muori(int signum, siginfo_t* info, void* context){

    printf("\nDEBUG: SIGNUM RICHIESTA: %d\n", signum);
    exit(33);

}

int main(int argc, char* argv[]){

    int i = atoi(argv[1]);
    int j = atoi(argv[2]);
    int msgid = msgget(MKEY, IPC_CREAT | 0666);
    struct sigaction sa;
    mex invio;
    size_t inviolength;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = muori;
    sigaction(SIGUSR1, &sa, NULL);

    invio.mtype = INVIO;
    invio.mi = i;
    invio.mj = j;
    invio.mx = 9;
    invio.my = 4;
    invio.pidRic = getpid();

    inviolength = sizeof(int)*4 + sizeof(pid_t);

    if((msgsnd(msgid, &invio, inviolength, IPC_NOWAIT)) < 0){

        printf("\nDEBUG: Messaggio non inviato da PID: %d\n", getpid());

    }

    return 0;

}
