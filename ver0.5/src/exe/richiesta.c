#include "../include/inc.h"

void muori(int signum, siginfo_t* info, void* context){

    printf("\nDEBUG: SIGNUM RICHIESTA: %d\n", signum);
    exit(33);

}

int main(int argc, char* argv[]){

    int c = 0;

    int inutile;


    int i = atoi(argv[1]);
    int j = atoi(argv[2]);
    int msgid = msgget(MKEY, IPC_CREAT | 0666);
    struct sigaction sa;
    mex invio;
    int shift = randomizeNum(randomizeNum(4,getpid()),100);
    size_t inviolength;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = muori;
    sigaction(SIGUSR1, &sa, NULL);

    invio.mtype = INVIO;
    invio.arrivi[0] = i;
    invio.arrivi[1] = j;
    invio.arrivi[2] = randomizeNum(getpid()*shift, H);
    invio.arrivi[3] = randomizeNum(getpid()*shift+2, W);
    invio.pidRic = getpid();

    inviolength = sizeof(invio.arrivi) + sizeof(pid_t);

    if((msgsnd(msgid, &invio, inviolength, IPC_NOWAIT)) < 0){

        printf("\nDEBUG: Messaggio non inviato da PID: %d\n", getpid());

    }

    return 0;

}
