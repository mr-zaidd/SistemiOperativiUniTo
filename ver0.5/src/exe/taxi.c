#include "../include/inc.h"

int main(int argc, char* argv[]){

    int dur = atoi(argv[1]);
    int i;
    int j;
    int tmp;
    int fals = 0;
    int shift = 30;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);

    printf("\nDEBUG: Dur: %d\tArgc: %d\n", dur, argc);

    while(!fals){
        i = randomizeNum(shift, H);
        j = randomizeNum(shift+2, W);
        tmp = checkOne(i,j);
        printf("\nDEBUG: I: %d\tj: %d\n", i, j);
        printf("\nDEBUG: TMP: %d\n", tmp);
        if(tmp == 1){
            head[i][j].soCap += 1;
            head[i][j].count += 1;
            fals = 1;
        }
    }

    printf("\n\n### Taxi BEFORE ###");
    printf("\nIndex i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
            i,
            j,
            head[i][j].one,
            head[i][j].soCap,
            head[i][j].soTime,
            head[i][j].count);

    movimentoManhattan(&i, &j, randomizeNum(20, H), randomizeNum(30, W));

    movimentoManhattan(&i, &j, randomizeNum(25, H), randomizeNum(35, W));

    movimentoManhattan(&i, &j, randomizeNum(15, H), randomizeNum(55, W));

    printf("\n\n### Taxi AFTER - Dopo 3 percorsi ###");
    printf("\nIndex i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
            i,
            j,
            head[i][j].one,
            head[i][j].soCap,
            head[i][j].soTime,
            head[i][j].count);

    shmdt(head);

    return 0;

}
