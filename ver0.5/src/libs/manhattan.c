#include "../include/inc.h"

void movimentoManhattan(int* startx, int* starty, int endx, int endy){

    int movimentoR = abs(*startx-endx);
    int movimentoC = abs(*starty-endy);

    int i = *startx;
    int j = *starty;

    struct timespec tmp, tmp2;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    printf("\nDEBUG: MOVIMENTO-R: %d\nDEBUG: MOVIMENTO-C: %d\n", movimentoR, movimentoC);

    tmp.tv_sec = 0;
    tmp.tv_nsec = head[0][0].soTime;

    printf("\nDEBUG: Attraversamento ORIGINE in manhattan: %d\n", head[0][0].soTime);
    printf("\nDEBUG: Attraversamento I e J in manhattan: %d\n", head[*startx][*starty].soTime);
    printf("\nDEBUG: Attraversamento I e J DEFERENCES in manhattan: %d\n", head[i][j].soTime);
    printf("\nDEBUG: Attraversamento W e H in manhattan: %d\n", head[W][H].soTime);
    printf("\nDEBUG: Attraversamento 10 e 10 in manhattan: %d\n", head[10][10].soTime);

    for(movimentoR; movimentoR > 0; movimentoR--){

        if(*startx < endx){
            *startx += 1;
            nanosleep(&tmp, &tmp2);
        }else if(*startx > endx){
            *startx -= 1;
            nanosleep(&tmp, &tmp2);
        }
        printf("\nDEBUG: Sono dentro MovimentoR");
    }

    for(movimentoC; movimentoC > 0; movimentoC--){
        if(*starty < endy){
            *starty += 1;
            nanosleep(&tmp, &tmp2);
        }else if(*starty > endy){
            *starty -= 1;
            nanosleep(&tmp, &tmp2);
        }
        printf("\nDEBUG: Sono dentro MovimentoC");
    }

    printf("\nDEBUG: startx: %d\nDEBUG: starty: %d\n", *startx, *starty);

    shmdt(head);

}
