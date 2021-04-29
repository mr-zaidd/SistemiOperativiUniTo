#include "../include/inc.h"

void movimentoManhattan(int* startx, int* starty, int endx, int endy){

    int movimentoR = abs(*startx-endx);
    int movimentoC = abs(*starty-endy);

    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    printf("\nDEBUG: MOVIMENTO-R: %d\nDEBUG: MOVIMENTO-C: %d\n", movimentoR, movimentoC);

    struct timespec tmp, tmp2;
    tmp.tv_sec = 0;
    tmp.tv_nsec = head[0][0].soTime;

    printf("\nDEBUG: Attraversamento in manhattan: %d\n", head[*startx][*starty].soTime);

    for(movimentoR; movimentoR > 0; movimentoR--){
        if(*startx < endx){
            *startx++;
            nanosleep(&tmp, &tmp2);
        }else if(*startx > endx){
            *startx--;
            nanosleep(&tmp, &tmp2);
        }
        printf("\nDEBUG: Sono dentro MovimentoR");
    }

    for(movimentoC; movimentoC > 0; movimentoC--){
        if(*starty < endy){
            *starty++;
            nanosleep(&tmp, &tmp2);
        }else if(*starty > endy){
            *starty--;
            nanosleep(&tmp, &tmp2);
        }
        printf("\nDEBUG: Sono dentro MovimentoC");
    }

    printf("\nDEBUG: startx: %d\nDEBUG: starty: %d\n", *startx, *starty);

    shmdt(head);

}
