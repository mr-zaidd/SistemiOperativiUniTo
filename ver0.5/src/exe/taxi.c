#include "../include/inc.h"


void muoriPlease(int signum, siginfo_t* info, void* context){

    printf("\nDEBUG: SEGNALE: %d\tInterrotto TAXI: %d per blocco su semaforo\n", signum, getpid());
    exit(33);

}

int main(int argc, char* argv[]){

    int dur = atoi(argv[1]);
    int i;
    int j;
    int tmp;
    int fals = 0;
    int shift = getpid();
    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    struct sembuf myop;
    struct sigaction sa;
    int msgid = msgget(MKEY, IPC_CREAT | 0666);
    mex ricezione;
    int msglength = 4*sizeof(int) + sizeof(pid_t);

    int semid = semget(TKEY, 1, IPC_CREAT | 0666);
/**
    printf("\nDEBUG: Dur: %d\tArgc: %d\n", dur, argc);
**/

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = muoriPlease;
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);

    myop.sem_num = 0;
    myop.sem_flg = 0;

    myop.sem_op = -1;
    semop(semid, &myop, 1);

    while(!fals){
        i = randomizeNum(shift, H);
        j = randomizeNum(shift+2, W);
        tmp = checkOne(i,j);
       /** printf("\nDEBUG: I: %d\tj: %d\n", i, j);
        printf("\nDEBUG: TMP: %d\n", tmp);**/
        if(tmp == 1){
            head[i][j].soCap += 1;
            head[i][j].count += 1;
            fals = 1;
        }
    }

    printf("\n\n### Taxi %d BEFORE ###", getpid());
    printf("\nIndex i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
            i,
            j,
            head[i][j].one,
            head[i][j].soCap,
            head[i][j].soTime,
            head[i][j].count);

    myop.sem_op = 1;
    semop(semid, &myop, 1);

    alarm(dur);

    while(1){

        msgrcv(msgid, &ricezione, msglength, INVIO, 0);

        printf("\nDEBUG: mi: %d\tmj: %d\tmx: %d\tmy: %d\n", ricezione.arrivi[0], ricezione.arrivi[1], ricezione.arrivi[2], ricezione.arrivi[3]);

        movimentoManhattanSEC(&i, &j, ricezione.arrivi[0], ricezione.arrivi[1]);
        movimentoManhattanSEC(&i, &j, ricezione.arrivi[2], ricezione.arrivi[3]);

        kill(ricezione.pidRic, SIGTERM);

    /**
        movimentoManhattanSEC(&i, &j, 8, 32);
    **/
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        printf("\n\n### Taxi %d AFTER ###", getpid());
        printf("\nIndex i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
                i,
                j,
                head[i][j].one,
                head[i][j].soCap,
                head[i][j].soTime,
                head[i][j].count);

        myop.sem_op = 1;
        semop(semid, &myop, 1);

    }

   shmdt(head);
   return 0;

}
