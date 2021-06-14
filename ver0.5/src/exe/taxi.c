#include "../include/inc.h"

pid_t richiesta;
out* output;
cell (*head)[W];

void muoriPlease(int signum, siginfo_t* info, void* context){
    if(signum == SIGTERM){
        shmdt(head);
        shmdt(output);
        exit(EXIT_SUCCESS);
    }else if(signum == SIGALRM){
	int msgidOut = msgget(MKEY_OUT, 0666);
	mexSig messaggioSegnale;
	messaggioSegnale.mtype = (long)richiesta;
	messaggioSegnale.segnale = 35;
	msgsnd(msgidOut, &messaggioSegnale, sizeof(int), 0);
        shmdt(head);
        shmdt(output);
        exit(33);
    }
}

int main(int argc, char* argv[]){

    int dur = atoi(argv[1]);
    int i;
    int j;
    int tmp;
    int fals = 0;
    int shift = getpid();
    struct sembuf myop;
    struct sembuf myopapp;
    struct sigaction sa;
    int msgid = msgget(MKEY, IPC_CREAT | 0666);
    mex ricezione;
    int msglength = 4*sizeof(int) + sizeof(pid_t);
    int semid = semget(TKEY, 1, IPC_CREAT | 0666);
    int semidapp = semget(APPKEY, 1, 0666);
    struct timeval timeBefore;
    struct timeval timeAfter;
    int seconds = 0;
    int shmidOut = shmget(OUTPUT_KEY, 0, 0666);
    int semidOut = semget(OUTPUT_KEY, 1, 0666);
    struct sembuf myopOut;
    struct sembuf myopMsg;
    int countRichieste = 0;
    int semidMsg = semget(0x042, 1, IPC_CREAT | 0666);

    int msgidOut = msgget(MKEY_OUT, 0666);
    mexSig messaggioSegnale;

    head = shmat(getshmid(), NULL, 0);

    myopMsg.sem_num = 0;
    myopMsg.sem_flg = 0;
    myopMsg.sem_op = -1;


    myopOut.sem_num = 0;
    myop.sem_flg = 0;

    myopapp.sem_num = 0;
    myopapp.sem_flg = 0;
    myopapp.sem_op = 0;

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = muoriPlease;
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);


    myop.sem_num = 0;
    myop.sem_flg = 0;

    myop.sem_op = -1;


    while(!fals){
        i = randomizeNum(shift, H);
        j = randomizeNum(shift+2, W);
        tmp = checkOne(i,j);

        if(tmp == 1){
            head[i][j].soCap += 1;
            head[i][j].count += 1;
            fals = 1;
        }
    }

    shmdt(head);
    semop(semidapp, &myopapp, 1);

    alarm(dur);

    while(1){

        semop(semidMsg, &myopMsg, 1);

        msgrcv(msgid, &ricezione, msglength, INVIO, 0);

        myopMsg.sem_op = 1;
        semop(semidMsg, &myopMsg, 1);
        richiesta = ricezione.pidRic;

        gettimeofday(&timeBefore, NULL);

        movimentoManhattanSEC(&i, &j, ricezione.arrivi[0], ricezione.arrivi[1]);
        movimentoManhattanSEC(&i, &j, ricezione.arrivi[2], ricezione.arrivi[3]);
	messaggioSegnale.mtype = (long)richiesta;
	messaggioSegnale.segnale = 70;

	msgsnd(msgidOut, &messaggioSegnale, sizeof(int), 0);

        countRichieste += 1;

        gettimeofday(&timeAfter, NULL);

        seconds = (timeAfter.tv_sec + (timeAfter.tv_usec/1000000)) - (timeBefore.tv_sec * (timeBefore.tv_usec/1000000));

        output = shmat(shmidOut, NULL, 0);

        myopOut.sem_op = -1;
        semop(semidOut, &myopOut, 1);

        if(countRichieste > output -> staccanovistaTaxi){
            output -> staccanovistaTaxi = countRichieste;
            output -> taxiStaccanovista = getpid();
        }

        if(seconds > output -> tempoTaxi){
            output->tempoTaxi = seconds;
            output->taxiTempo = getpid();
        }

        myopOut.sem_op = 1;
        semop(semidOut, &myopOut, 1);
        shmdt(output);

        myop.sem_op = -1;

    }

   return 0;

}
