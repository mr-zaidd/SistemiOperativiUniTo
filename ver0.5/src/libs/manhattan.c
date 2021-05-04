#include "../include/inc.h"
#include <math.h>

void movimentoManhattan(int* startx, int* starty, int endx, int endy){

    int movimentoR = abs(*startx-endx);
    int movimentoC = abs(*starty-endy);

    long tempotot = 0;

    struct timespec tmp, tmp2;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);

    printf("\nDEBUG: Prima di movimento ->\t i: %d\tj: %d\n", *startx, *starty);
    printf("\nDEBUG: INIZIO MOVIMENTO\n");

    tmp.tv_sec = 0;
    tmp.tv_nsec = head[0][0].soTime;

    for(movimentoR; movimentoR > 0; movimentoR--){

        if(*startx < endx){
            *startx += 1;
            head[*startx][*starty].count += 1;
            nanosleep(&tmp, &tmp2);
        }else if(*startx > endx){
            *startx -= 1;
            head[*startx][*starty].count += 1;
            nanosleep(&tmp, &tmp2);
        }
        tempotot += head[0][0].soTime;
    }

    for(movimentoC; movimentoC > 0; movimentoC--){
        if(*starty < endy){
            *starty += 1;
            head[*startx][*starty].count += 1;
            nanosleep(&tmp, &tmp2);
        }else if(*starty > endy){
            *starty -= 1;
            head[*startx][*starty].count += 1;
            nanosleep(&tmp, &tmp2);
        }
        tempotot += head[0][0].soTime;
    }

    printf("\nDEBUG: Dopo movimento ->\t i: %d\tj: %d\n", *startx, *starty);
    printf("\nDEBUG: Tempo impiegato nel movimento: %f\n", (tempotot*pow(10,-9)));

    shmdt(head);

}

