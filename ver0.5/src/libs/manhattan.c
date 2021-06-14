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


    nanosleep(&attr, &arr);

    if((head[*startx][*starty].soCap == head[*startx][*starty].soCapMax) && semctl(semid, myop.sem_num, GETVAL) == 0){
        head[*startx][*starty].soCap -= 1;
        semctl(semid, myop.sem_num, SETVAL, 1);
    }else{
        semop(semid, &myop, 1);
        head[*startx][*starty].soCap -= 1;
        myop.sem_op = +1;
        semop(semid, &myop, 1);
    }

    if(*starty < endy){

        myop.sem_num = (*startx)*W + (*starty+1);
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        *starty = (*starty) + 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;

        if(head[*startx][*starty].soCap == head[*startx][*starty].soCapMax){
            semctl(semid, myop.sem_num, SETVAL, 0);
        }else{
            myop.sem_op = +1;
            semop(semid, &myop, 1);
        }

    }else{

        myop.sem_num = (*startx)*W + (*starty-1);
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        *starty = (*starty) - 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        if(head[*startx][*starty].soCap == head[*startx][*starty].soCapMax){
            semctl(semid, myop.sem_num, SETVAL, 0);
        }else{
            myop.sem_op = +1;
            semop(semid, &myop, 1);
        }

    }

    shmdt(head);

}

void movimentoX(int* startx, int* starty, int endx){

    cell (*head)[W] = shmat(getshmid(), 0, IPC_CREAT | 0666);
    int semid = semget(readKey(), 0, IPC_CREAT | 0666);
    struct timespec attr, arr;
    struct sembuf myop;

    attr.tv_sec = 0;
    attr.tv_nsec = head[0][0].soTime;

    myop.sem_flg = 0;
    myop.sem_op = -1;
    myop.sem_num = (*startx)*W + (*starty);


    nanosleep(&attr, &arr);

    if((head[*startx][*starty].soCap == head[*startx][*starty].soCapMax) && semctl(semid, myop.sem_num, GETVAL) == 0){
        head[*startx][*starty].soCap -= 1;
        semctl(semid, myop.sem_num, SETVAL, 1);
    }else{
        semop(semid, &myop, 1);
        head[*startx][*starty].soCap -= 1;
        myop.sem_op = +1;
        semop(semid, &myop, 1);
    }

    if(*startx < endx){

        myop.sem_num = ((*startx)+1)*W + (*starty);
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        *startx = (*startx) + 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;

        if(head[*startx][*starty].soCap == head[*startx][*starty].soCapMax){
            semctl(semid, myop.sem_num, SETVAL, 0);
        }else{
            myop.sem_op = +1;
            semop(semid, &myop, 1);
        }

    }else{

        myop.sem_num = (*startx-1)*W + (*starty);
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        *startx = (*startx) - 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        if(head[*startx][*starty].soCap == head[*startx][*starty].soCapMax){
            semctl(semid, myop.sem_num, SETVAL, 0);
        }else{
            myop.sem_op = +1;
            semop(semid, &myop, 1);
        }

    }

    shmdt(head);

}

void movimentoManhattanSEC(int* startx, int* starty, int endx, int endy){

    int movimentoR = abs(*startx-endx);
    int movimentoC = abs(*starty-endy);

    int shmidOut = shmget(OUTPUT_KEY, 0, 0666);
    out* output;
    int semidOut = semget(OUTPUT_KEY, 1, 0666);
    struct sembuf myop;
    myop.sem_num = 0;
    myop.sem_flg = 0;
    myop.sem_op = -1;

    for(movimentoR; movimentoR > 0; movimentoR--){

        movimentoX(startx, starty, endx);

    }

    for(movimentoC; movimentoC > 0; movimentoC--){

        movimentoY(startx, starty, endy);

    }

    semop(semidOut, &myop, 1);

    output = shmat(shmidOut , NULL, 0);
    output -> stradaTaxi  = movimentoR + movimentoC;
    output -> taxiStrada = getpid();
    shmdt(output);

    myop.sem_op = 1;
    semop(semidOut, &myop, 1);




}
