#include "../include/inc.h"

int main(int argc, char* argv[]){

    int dur = atoi(argv[1]);
    int i;
    int j;
    int tmp;
    int fals = 0;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);

    srand(time(NULL));
    while(!fals){
        i = rand()%(H+1);
        j = rand()%(W+1);
        tmp = checkOne(i,j);
        if(tmp == 1){
            if(head[i][j].soCap < 3){
                ++head[i][j].soCap;
                fals = 1;
            }
        }
    }

    printf("\n\n### Taxi BEFORE ###");
    printf("\n Index i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
            i,
            j,
            head[i][j].one,
            head[i][j].soCap,
            head[i][j].soTime,
            head[i][j].count);

    movimentoManhattan(&i, &j, 0, 0);

    printf("\n\n### Taxi AFTER ###");
    printf("\n Index i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
            i,
            j,
            head[i][j].one,
            head[i][j].soCap,
            head[i][j].soTime,
            head[i][j].count);

    shmdt(head);

    return 0;

}
