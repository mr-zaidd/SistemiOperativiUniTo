#include "../include/inc.h"
#include <math.h>

void movimentoY(int* startx, int* starty, int endy){

    cell (*head)[W] = shmat(getshmid(), 0, IPC_CREAT | 0666);
    int semid = semget(readKey(), 0, IPC_CREAT | 0666);
    struct timespec attr, arr;
    struct sembuf myop;

    attr.tv_sec = 0;
    attr.tv_nsec = head[0][0].soTime;

    myop.sem_flg = 0;
    myop.sem_op = -1;
    myop.sem_num = (*startx)*W + (*starty);

    semop(semid, &myop, 1);
    head[*startx][*starty].soCap -= 1;

    myop.sem_op = 1;
    semop(semid, &myop, 1);


    if(*starty < endy){

        myop.sem_num = (*startx)*W + (*starty+1);
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        *starty += 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        nanosleep(&attr, &arr);

        myop.sem_op = 1;
        semop(semid, &myop, 1);

    }else{

        myop.sem_num = (*startx)*W + (*starty-1);
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        *starty -= 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        nanosleep(&attr, &arr);

        myop.sem_op = 1;
        semop(semid, &myop, 1);

    }

    printf("\nMovimento Colonna\n");
    shmdt(head);

}



void movimentoX(int* startx, int* starty, int endx){

    cell (*head)[W] = shmat(getshmid(), 0, IPC_CREAT | 0666);
    int semid = semget(readKey(), 0, IPC_CREAT | 0666);
    struct timespec attr, arr;
    struct sembuf myop;

    attr.tv_sec = 0;
    attr.tv_nsec = head[0][0].soTime;

    printf("\nDEBUG: PID: %d\tMovimento Riga 1\n", getpid());
    fflush(stdout);

    myop.sem_flg = 0;
    myop.sem_op = -1;
    myop.sem_num = (*startx)*W + (*starty);

    semop(semid, &myop, 1);
    head[*startx][*starty].soCap -= 1;

    myop.sem_op = 1;
    semop(semid, &myop, 1);

    printf("\nMovimento Riga 2\n");

    if(*startx < endx){

        myop.sem_num = (*startx+1)*W + (*starty);
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        *startx += 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        nanosleep(&attr, &arr);

        myop.sem_op = 1;
        semop(semid, &myop, 1);

    }else{

        myop.sem_num = (*startx-1)*W + (*starty);
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        *startx -= 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        nanosleep(&attr, &arr);

        myop.sem_op = 1;
        semop(semid, &myop, 1);

    }

    shmdt(head);

}

void movimentoManhattanSEC(int* startx, int* starty, int endx, int endy){

    int movimentoR = abs(*startx-endx);
    int movimentoC = abs(*starty-endy);

    for(movimentoR; movimentoR > 0; movimentoR--){

        movimentoX(startx, starty, endx);

    }

    for(movimentoC; movimentoC > 0; movimentoC--){

        movimentoY(startx, starty, endy);

    }

}
void movimentoManhattan(int* startx, int* starty, int endx, int endy, int timer){

    int movimentoR = abs(*startx-endx);
    int movimentoC = abs(*starty-endy);

    long tempotot = 0;

    struct timespec tmp, tmp2;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    int semid = semget(readKey(), 0, IPC_CREAT | 0666);
    struct sembuf myop;

    printf("\nDEBUG: PID:%d\tStartx: %d\tStarty: %d\tEndx: %d\tEndy: %d\n",getpid(), *startx, *starty, endx, endy);

    myop.sem_flg = 0;
    myop.sem_op = -1;

/**    printf("\nDEBUG: Prima di movimento ->\t i: %d\tj: %d\n", *startx, *starty);
    printf("\nDEBUG: INIZIO MOVIMENTO\n");
**/
    printf("\nDEBUG: Timer Manhattan: %d\n", timer);
    tmp.tv_sec = 0;
    tmp.tv_nsec = head[0][0].soTime;

    for(movimentoR; movimentoR > 0; movimentoR--){

        myop.sem_num = (*startx)*W + (*starty);
        printf("\nDEBUG: ValoreSemaforo PRIMAs di %d: %d", getpid(), semctl(semid, myop.sem_num, GETVAL));

        if(semop(semid, &myop, 1) == -1){
            printf("\nDEBUG: ValoreSemaforo DOPOs di %d: %d", getpid(), semctl(semid, myop.sem_num, GETVAL));
            fflush(stdout);
            raise(SIGTERM);
        }else{
            head[*startx][*starty].soCap -= 1;
            myop.sem_op = 1;
            semop(semid, &myop, 1);
        }
        if(*startx < endx){
            myop.sem_num = (*startx+1)*W+(*starty);
            myop.sem_op = -1;
            if(semop(semid, &myop, 1) == -1)
                exit(EXIT_FAILURE);
            else{
                *startx += 1;
                head[*startx][*starty].count += 1;
                head[*startx][*starty].soCap += 1;
                nanosleep(&tmp, &tmp2);
                myop.sem_op = 1;
                semop(semid, &myop, 1);
            }
        }else if(*startx > endx){
            myop.sem_num = (*startx-1)*W+(*starty);
            myop.sem_op = -1;
            if(semop(semid, &myop, 1) == -1)
                exit(EXIT_FAILURE);
            else{
                *startx -= 1;
                head[*startx][*starty].count += 1;
                head[*startx][*starty].soCap += 1;
                nanosleep(&tmp, &tmp2);
                myop.sem_op = 1;
                semop(semid, &myop, 1);
            }
        }
        tempotot += head[0][0].soTime;
    }

    for(movimentoC; movimentoC > 0; movimentoC--){

        myop.sem_num = (*startx)*W + (*starty);

        if(semop(semid, &myop, 1) == -1)
            exit(EXIT_FAILURE);
        else{
            head[*startx][*starty].soCap -= 1;
            myop.sem_op = 1;
            semop(semid, &myop, 1);
        }

        if(*starty < endy){
            myop.sem_num = (*startx)*W+(*starty+1);
            myop.sem_op = -1;
            if(semop(semid, &myop, 1) == -1)
                exit(EXIT_FAILURE);
            else{
                *starty += 1;
                head[*startx][*starty].count += 1;
                head[*startx][*starty].soCap += 1;
                nanosleep(&tmp, &tmp2);
                myop.sem_op = 1;
                semop(semid, &myop, 1);
            }
        }else if(*starty > endy){
            myop.sem_num = (*startx)*W+(*starty-1);
            myop.sem_op = -1;
            if(semop(semid, &myop, 1) == -1)
                exit(EXIT_FAILURE);
            else{
                *starty -= 1;
                head[*startx][*starty].count += 1;
                head[*startx][*starty].soCap += 1;
                nanosleep(&tmp, &tmp2);
                myop.sem_op = 1;
                semop(semid, &myop, 1);
            }
        }
        tempotot += head[0][0].soTime;
    }
/**
    printf("\nDEBUG: Dopo movimento ->\t i: %d\tj: %d\n", *startx, *starty);
    printf("\nDEBUG: Tempo impiegato nel movimento: %f\n", (tempotot*pow(10,-9)));
**/
    shmdt(head);

}

