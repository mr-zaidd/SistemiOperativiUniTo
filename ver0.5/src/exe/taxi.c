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
        kill(richiesta, SIGUSR2);
        /**printf("\nDEBUG: SEGNALE: %d\tInterrotto TAXI: %d per blocco su semaforo o arrivato signalAlarm\n", signum, getpid());**/
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
    int countRichieste = 0;


    head = shmat(getshmid(), NULL, 0);


    myopOut.sem_num = 0;
    myop.sem_flg = 0;

    myopapp.sem_num = 0;
    myopapp.sem_flg = 0;
    myopapp.sem_op = 0;

    sa.sa_flags = SA_SIGINFO | SA_NODEFER;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = muoriPlease;
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGPIPE, &sa, NULL);


    myop.sem_num = 0;
    myop.sem_flg = 0;

    myop.sem_op = -1;
/**    semop(semid, &myop, 1);**/

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

    shmdt(head);

/**    printf("\n\n### Taxi %d BEFORE ###", getpid());
    printf("\nIndex i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
            i,
            j,
            head[i][j].one,
            head[i][j].soCap,
            head[i][j].soTime,
            head[i][j].count);

    fflush(stdout);

    myop.sem_op = 1;
    semop(semid, &myop, 1);
**/
    semop(semidapp, &myopapp, 1);

    alarm(dur);

    while(1){

        msgrcv(msgid, &ricezione, msglength, INVIO, 0);
        printf("\nDEBUG: Richiesta presa in incarico\tpi: %d\tpy: %d\ti: %d\tj: %d\tx: %d\ty: %d\tPidRichiesta: %d\n",
                i,
                j,
                ricezione.arrivi[0],
                ricezione.arrivi[1],
                ricezione.arrivi[2],
                ricezione.arrivi[3],
                (int)ricezione.pidRic);
        fflush(stdout);

        richiesta = ricezione.pidRic;

        gettimeofday(&timeBefore, NULL);

        movimentoManhattanSEC(&i, &j, ricezione.arrivi[0], ricezione.arrivi[1]);
        movimentoManhattanSEC(&i, &j, ricezione.arrivi[2], ricezione.arrivi[3]);

        kill(richiesta, SIGPIPE);

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
/**        semop(semid, &myop, 1);

        printf("\n\n### Taxi %d AFTER ###", getpid());
        printf("\nIndex i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
                i,
                j,
                head[i][j].one,
                head[i][j].soCap,
                head[i][j].soTime,
                head[i][j].count);

        fflush(stdout);

        myop.sem_op = 1;
        semop(semid, &myop, 1);
**/
    }

   return 0;

}
