#include "../include/inc.h"
#include <math.h>

void movimentoManhattan(int* startx, int* starty, int endx, int endy, int timer){

    int movimentoR = abs(*startx-endx);
    int movimentoC = abs(*starty-endy);

    long tempotot = 0;

    struct timespec tmp, tmp2;
    struct timespec sem;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    int semid = semget(readKey(), 0, IPC_CREAT | 0666);
    struct sembuf myop;

    myop.sem_flg = IPC_NOWAIT;
    myop.sem_op = -1;

/**    printf("\nDEBUG: Prima di movimento ->\t i: %d\tj: %d\n", *startx, *starty);
    printf("\nDEBUG: INIZIO MOVIMENTO\n");
**/
    sem.tv_sec = timer;
    sem.tv_sec = 0;
    tmp.tv_sec = 0;
    tmp.tv_nsec = head[0][0].soTime;

    for(movimentoR; movimentoR > 0; movimentoR--){

        myop.sem_num = (*startx)*W + (*starty);
        printf("\nDEBUG: semNum: %d\n", myop.sem_num);

        if(semtimedop(semid, &myop, 1, &sem) == -1){
            printf("RAISE");
            fflush(stdout);
            exit(EXIT_FAILURE);
        }else{
            printf("\nDEBUG: Sono dentro il primo semaforo\n");
            head[*startx][*starty].soCap -= 1;
            myop.sem_op = 1;
            semop(semid, &myop, 1);
        }
        if(*startx < endx){
            myop.sem_num = (*startx+1)*W+(*starty);
            myop.sem_op = -1;
            if(semtimedop(semid, &myop, 1, &sem) == -1)
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
            if(semtimedop(semid, &myop, 1, &sem) == -1)
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

        if(semtimedop(semid, &myop, 1, &sem) == -1)
            exit(EXIT_FAILURE);
        else{
            head[*startx][*starty].soCap -= 1;
            myop.sem_op = 1;
            semop(semid, &myop, 1);
        }

        if(*starty < endy){
            myop.sem_num = (*startx)*W+(*starty+1);
            myop.sem_op = -1;
            if(semtimedop(semid, &myop, 1, &sem) == -1)
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
            if(semtimedop(semid, &myop, 1, &sem) == -1)
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

