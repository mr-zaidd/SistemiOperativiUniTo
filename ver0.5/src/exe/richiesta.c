#include "../include/inc.h"

#define signalErr(s,m) if((s) == -1) {perror(m); exit(errno);}

void muori(int signum){

    int shmidOut = shmget(OUTPUT_KEY, 0, 0666);
    out* output;
    int semidOut = semget(OUTPUT_KEY, 1, 0666);
    struct sembuf myop;
    myop.sem_num = 0;
    myop.sem_flg = 0;
    myop.sem_op = -1;

    if(signum == SIGTERM){
        exit(EXIT_SUCCESS);
    }else if(signum == SIGPIPE){
        write(STDOUT_FILENO, "\nDEBUG: SIGUSR1 ricevuto da richiesta\n", 38);
        semop(semidOut, &myop, 1);

        output = shmat(shmidOut , NULL, 0);
        output -> successi = output->successi + 1;

        myop.sem_op = 1;
        semop(semidOut, &myop, 1);

        write(STDOUT_FILENO, "\nDEBUG: *** RICHIESTA COMPLETATA ***\n", 39);

        exit(EXIT_SUCCESS);
    }else if(signum == SIGUSR2){

        semop(semidOut, &myop, 1);

        output = shmat(shmidOut , NULL, 0);
        output -> abortiti = output->abortiti + 1;

        myop.sem_op = 1;
        semop(semidOut, &myop, 1);

        write(STDOUT_FILENO, "\nDEBUG: RICHIESTA ABORTITA\n", 28);
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

    int signalW;
    sigset_t setW;

    myopapp.sem_num = 0;
    myopapp.sem_flg = 0;
    myopapp.sem_op = 0;

    sa.sa_flags = SA_NODEFER;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = muori;
    sigaction(SIGUSR2, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGPIPE, &sa, NULL);

    invio.mtype = INVIO;
    invio.arrivi[0] = i;
    invio.arrivi[1] = j;
    invio.arrivi[2] = randomizeNum(getpid()*shift, H);
    invio.arrivi[3] = randomizeNum(getpid()*shift+2, W);
    invio.pidRic = getpid();

    inviolength = sizeof(invio.arrivi) + sizeof(pid_t);

    semop(semidapp, &myopapp, 1);

    msgsnd(msgid, &invio, inviolength, 0);
    printf("\nDEBUG: pidRICHIESTA: %d\n", getpid());
    fflush(stdout);
/**
    if((msgsnd(msgid, &invio, inviolength, IPC_NOWAIT)) < 0){

        printf("\nDEBUG: Messaggio non inviato da PID: %d\n", getpid());

    }
    sigwait(&setW, &signalW);

**/
    pause();
    return 0;

}
