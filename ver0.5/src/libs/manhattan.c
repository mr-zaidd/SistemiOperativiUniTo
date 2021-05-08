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

        *starty += 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        nanosleep(&attr, &arr);

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

        *starty -= 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        nanosleep(&attr, &arr);

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

        myop.sem_num = (*startx+1)*W + (*starty);
        myop.sem_op = -1;
        semop(semid, &myop, 1);

        *startx += 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        nanosleep(&attr, &arr);

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

        *startx -= 1;
        head[*startx][*starty].soCap += 1;
        head[*startx][*starty].count += 1;
        nanosleep(&attr, &arr);

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

    printf("\n\nDEBUG: Startx: %d\tStarty: %d\tEndx: %d\tEndy: %d\n\n", *startx, *starty, endx, endy);

    for(movimentoR; movimentoR > 0; movimentoR--){

        movimentoX(startx, starty, endx);

    }

    for(movimentoC; movimentoC > 0; movimentoC--){

        movimentoY(startx, starty, endy);

    }

}
void movimentoManhattan(int* startx, int* starty, int endx, int endy){

    int movimentoR = abs(*startx-endx);
    int movimentoC = abs(*starty-endy);

    struct timespec tmp, tmp2;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);

    tmp.tv_sec = 0;
    tmp.tv_nsec = head[0][0].soTime;

    for(movimentoR; movimentoR > 0; movimentoR--){

        head[*startx][*starty].soCap -= 1;

        if(*startx < endx){

            *startx += 1;
            head[*startx][*starty].count += 1;
            head[*startx][*starty].soCap += 1;
            nanosleep(&tmp, &tmp2);

        }else if(*startx > endx){

            *startx -= 1;
            head[*startx][*starty].count += 1;
            head[*startx][*starty].soCap += 1;
            nanosleep(&tmp, &tmp2);
        }
    }

    for(movimentoC; movimentoC > 0; movimentoC--){

        head[*startx][*starty].soCap -= 1;

        if(*starty < endy){

            *starty += 1;
            head[*startx][*starty].count += 1;
            head[*startx][*starty].soCap += 1;
            nanosleep(&tmp, &tmp2);
        }else if(*starty > endy){

            *starty -= 1;
            head[*startx][*starty].count += 1;
            head[*startx][*starty].soCap += 1;
            nanosleep(&tmp, &tmp2);
        }
    }

    shmdt(head);

}

