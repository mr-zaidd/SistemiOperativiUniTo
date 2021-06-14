#include "../include/inc.h"

void funzioneSuccessoAborto(int sig){

    int shmidOut = shmget(OUTPUT_KEY, 0, 0666);
    out* output;
    int semidOut = semget(OUTPUT_KEY, 1, 0666);
    struct sembuf myop;
    myop.sem_num = 0;
    myop.sem_flg = 0;
    myop.sem_op = -1;

    if(sig == 70){
        semop(semidOut, &myop, 1);

        output = shmat(shmidOut , NULL, 0);
        output -> successi = output->successi + 1;
        shmdt(output);

        myop.sem_op = 1;
        semop(semidOut, &myop, 1);
        exit(EXIT_SUCCESS);
    }else if(sig == 35){
        semop(semidOut, &myop, 1);

        output = shmat(shmidOut , NULL, 0);
        output -> abortiti = output->abortiti + 1;
        shmdt(output);

        myop.sem_op = 1;
        semop(semidOut, &myop, 1);
        exit(EXIT_FAILURE);
    }else{
    
    
	exit(33);

    }
}


void muori(int signum, siginfo_t* info, void* context){
    if(signum == SIGTERM){
        exit(EXIT_SUCCESS);
    }
}

int main(int argc, char* argv[]){

    int c = 0;

    int i = atoi(argv[1]);
    int j = atoi(argv[2]);
    int msgid = msgget(MKEY, IPC_CREAT | 0666);
    mex invio;
    int shift = randomizeNum(randomizeNum(4,getpid()),100);
    size_t inviolength;
    int semidapp = semget(APPKEY, 1, 0666);
    struct sembuf myopapp;
    struct sigaction sa;
    int signalW;
    sigset_t setW;
    int msgidOut = msgget(MKEY_OUT, 0666);
    mexSig messaggioSegnale;

    myopapp.sem_num = 0;
    myopapp.sem_flg = 0;
    myopapp.sem_op = 0;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = muori;

    sigaction(SIGTERM, &sa, NULL);

    srand(time(NULL));

    invio.mtype = INVIO;
    invio.arrivi[0] = i;
    invio.arrivi[1] = j;
    invio.arrivi[2] = rand()%H;
    invio.arrivi[3] = rand()%W;
    invio.pidRic = getpid();

    inviolength = sizeof(invio.arrivi) + sizeof(pid_t);

    semop(semidapp, &myopapp, 1);

    msgsnd(msgid, &invio, inviolength, 0);

    msgrcv(msgidOut, &messaggioSegnale, sizeof(int), (long)getpid(), 0);

    if(messaggioSegnale.segnale == 70){
    	funzioneSuccessoAborto(messaggioSegnale.segnale);
    }else if(messaggioSegnale.segnale == 35){
    	funzioneSuccessoAborto(messaggioSegnale.segnale);
    }else{
    	raise(SIGTERM);
    }

    return 0;

}
