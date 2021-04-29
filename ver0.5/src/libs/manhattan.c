#include "../include/inc.h"

void movimentoManhattan(int* startx, int* starty, int endx, int endy){

    int movimentoR = abs(*startx-endx);
    int movimentoC = abs(*starty-endy);

    cell (*head)[W] = shmat(getshmid(), NULL, 0);

    struct timespec tmp, tmp2;
    tmp.tv_sec = 0;
    tmp.tv_nsec = head[0][0].soTime;

    printf("\n\n\n************** Attraversamento: %d ****************\n\n\n", head[*startx][*starty].soTime);

    for(movimentoR; movimentoR < 0; movimentoR--){
        if(*startx < endx){
            *startx++;
            nanosleep(&tmp,&tmp2);
        }else if(*startx > endx){
            *startx--;
            nanosleep(&tmp,&tmp2);
        }
    }

    for(movimentoC; movimentoC < 0; movimentoC--){
        if(*starty < endy){
            *starty++;
            nanosleep(&tmp,&tmp2);
        }else if(*starty > endy){
            *starty--;
            nanosleep(&tmp,&tmp2);
        }
    }

    shmdt(head);

}
