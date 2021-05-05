#include "../include/inc.h"

int main(int argc, char* argv[]){

    int dur = atoi(argv[1]);
    int i;
    int j;
    int tmp;
    int fals = 0;
    int shift = 30;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    struct sembuf myop;

    int semid = semget(17, 1, IPC_CREAT | 0666);
/**
    printf("\nDEBUG: Dur: %d\tArgc: %d\n", dur, argc);
**/
    myop.sem_num = 0;
    myop.sem_flg = 0;
    myop.sem_op = -1;

    semop(semid, &myop, 1);

    while(!fals){
        i = randomizeNum(shift, H);
        j = randomizeNum(shift+2, W);
        tmp = checkOne(i,j);
       /** printf("\nDEBUG: I: %d\tj: %d\n", i, j);
        printf("\nDEBUG: TMP: %d\n", tmp);**/
        if(tmp == 1){
            head[i][j].soCap += 1;
            head[i][j].count += 1;
            fals = 1;
        }
    }

    printf("\n\n### Taxi %d BEFORE ###", getpid());
    printf("\nIndex i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
            i,
            j,
            head[i][j].one,
            head[i][j].soCap,
            head[i][j].soTime,
            head[i][j].count);

    movimentoManhattan(&i, &j, randomizeNum(20, H), randomizeNum(30, W), dur);

    printf("\n\n### Taxi %d AFTER - Dopo 3 percorsi ###", getpid());
    printf("\nIndex i: %d\nIndex j:%d\nOccupata: %d\nCapacità: %d\nAttraversamento: %d\nContatore: %d\n\n",
            i,
            j,
            head[i][j].one,
            head[i][j].soCap,
            head[i][j].soTime,
            head[i][j].count);

    myop.sem_op = 1;
    semop(semid, &myop, 1);

    shmdt(head);

    return 0;

}
