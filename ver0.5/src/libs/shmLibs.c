#include "../include/inc.h"

int createshm(){

    int shmid;
    int size;
    size = W*H*sizeof(cell);
    shmid = shmget(readKey(), size, IPC_CREAT | 0666);

    if(shmid == -1){
        perror("SHMGET");
        exit(1);
    }

    return shmid;

}

int getshmid(){

    int shmid;
    shmid = shmget(readKey(), 0, IPC_CREAT | 0666);
    if(shmid == -1)
        return -1;
    return shmid;

}

void deleteshm(){

    struct shmid_ds shmid_ds, *buf;
    buf = &shmid_ds;

    shmctl(getshmid(), IPC_STAT, buf);
        if((shmctl(getshmid(), IPC_RMID, 0)) == -1){
            perror("\nEliminazione SHM Aborted");
        }else
            printf("\nSHM ELIMINATA\n");
}

int checkOne(int i, int j){

    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    if(head[i][j].one == 1){
        shmdt(head);
        return 0;
    }else{
        shmdt(head);
        return 1;
    }

}


int checkPosition(int i, int j){

    int pos;

    if(i==0 && j==0){
        pos = 1; /* angolo alto sinistro */
    }else if(i==0 &&j==W){
        pos = 2; /* angolo alto destro */
    }else if(i!=H && i!=0 && j==0){
        pos = 3; /* lato sinistro */
    }else if(i!=H && i!=0 && j==W){
        pos = 4; /* lato destro */
    }else if(i==H && j==0){
        pos = 5; /* angolo basso sinistro */
    }else if(i==H && j==W){
        pos = 6; /* angolo basso destro */
    }else if(i==0 && j!=0 && j!=W){
        pos = 7; /* lato alto */
    }else if(i==H && j!=0 && j!=W){
        pos = 8; /* lato basso */
    }else
        pos = 9; /* posizione libera */

    return pos;
}

/* Ritorna ZERO se è occupato */
int checkFreedom(int i, int j, int pos){

    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    int ret = 1;

    switch(pos){

        case 1: /* angolo alto sinistro */
            if(head[i][j+1].one == 1 || head[i+1][j+1].one == 1 || head[i+1][j].one == 1)
                ret = 0;
            break;
        case 2: /* angolo alto destro */
            if(head[i][j-1].one == 1 || head[i+1][j-1].one == 1 || head[i+1][j].one == 1)
                ret = 0;
            break;
        case 3: /* lato sinistro */
            if(head[i+1][j+1].one == 1 || head[i-1][j+1].one == 1 || head[i+1][j].one == 1 || head[i][j+1].one == 1 ||head[i-1][j].one == 1)
                ret = 0;
            break;
        case 4: /* lato destro */
            if(head[i-1][j].one == 1 || head[i+1][j].one == 1 || head[i-1][j-1].one == 1 || head[i+1][j-1].one == 1 || head[i][j-1].one == 1)
                ret = 0;
            break;
        case 5: /* angolo basso sinistro */
            if(head[i][j+1].one == 1 || head[i-1][j+1].one == 1 || head[i-1][j].one == 1)
                ret = 0;
            break;
        case 6: /* angolo basso destro */
            if(head[i-1][j].one == 1 || head[i-1][j-1].one == 1 || head[i][j-1].one == 1)
                ret = 0;
            break;
        case 7: /* lato alto */
            if(head[i+1][j+1].one == 1 || head[i+1][j-1].one == 1 || head[i+1][j].one == 1 || head[i][j-1].one == 1 || head[i][j+1].one == 1)
                ret = 0;
            break;
        case 8: /* lato basso */
            if(head[i][j-1].one == 1 || head[i][j+1].one == 1 || head[i-1][j].one == 1 || head[i-1][j-1].one == 1 || head[i-1][j+1].one == 1)
                ret = 0;
            break;
        case 9: /* posizione libera */
            if(head[i][j+1].one == 1 || head[i][j-1].one == 1 || head[i+1][j].one == 1 || head[i+1][j+1].one == 1 || head[i+1][j-1].one == 1 || head[i-1][j].one == 1 || head[i-1][j+1].one == 1 || head[i-1][j-1].one == 1)
                ret = 0;
            break;
        default:
            printf("\nPosizione:%d\n", pos);
    }

    shmdt(head);
    return ret;

}

void insertHole(int i, int j){

    cell (*head)[W] = shmat(getshmid(), NULL, 0);

    head[i][j].one = 1;

    shmdt(head);

}

void holesHandler(int holes){

    int i;
    int j;
    int pos;
    int tmp;
    int free;
    int shift;
    int inpiu = 0;
    int semid = semget(readKey(), 0, IPC_CREAT | 0666);

    /**srand(time(NULL));**/
    shift = 24;
    srand(time(NULL));
    while(holes != 0){
        /**
        i = randomizeNum(shift, H);
        j = randomizeNum(shift+2, W);
        **/
        i = (rand() % H);
        j = (rand() % W);
        tmp = checkOne(i,j);
        if(tmp == 1){
            pos = checkPosition(i,j);
            free = checkFreedom(i, j, pos);
            if(free == 1){
                inpiu += 1;
                /**printf("\nHOLES: %d\n", inpiu);**/
                insertHole(i, j);
                semctl(semid, (i*W+j), SETVAL, 0);
                holes--;
            }
        }
        shift = shift*2;
    }
}


void printMtx(){

    int i;
    int j;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);

    int max1 = 0;
    int max2 = 0;
    int max3 = 0;
    int x;
    int y;

    max1 = massimorelativo(&x, &y, INT_MAX);
    max2 = massimorelativo(&x, &y, max1);
    max3 = massimorelativo(&x, &y, max2);


    printf("\n### MAPPA FINALE ###\n");
    for(i = 0; i < H; i++){
        for(j = 0; j < W; j++){

            if((head[i][j].source == 1) && (max1 == head[i][j].count || max2 == head[i][j].count || max3 == head[i][j].count))
                printf(CWHITE"T  "CRESET);
            else if(head[i][j].source == 1)
                printf(CMAGENTA"S  "CRESET);
            else if(head[i][j].one == 1)
                printf(CCYAN"X  "CRESET);
            else if((head[i][j].count == max1 || head[i][j].count == max2 || head[i][j].count == max3) && head[i][j].count != 0){
                if(head[i][j].count < 10)
                    printf(CRED"%d  "CRESET, head[i][j].count);
                else if(head[i][j].count >= 10 && head[i][j].count < 100)
                    printf(CRED"%d "CRESET, head[i][j].count);
                else if(head[i][j].count >= 100)
                    printf(CRED"%d"CRESET, head[i][j].count);
            }else
                printf(".  ");
        }
        printf("\n");
    }
    shmdt(head);
    printf("\n### X Holes\t. Libera\tT TopCell/Source\tS Source\t# Attraversamenti ###\n");
}


void printMtxSEC(int tmp){

    int i;
    int j;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);

    printf("\n### MAPPA: SECONDO -> %d ###\n", tmp);
    for(i = 0; i < H; i++){
        for(j = 0; j < W; j++){

            if(head[i][j].source == 1)
                printf(CMAGENTA"S  "CRESET);
            else if(head[i][j].one == 1)
                printf(CCYAN"X  "CRESET);
            else if(head[i][j].soCap > 0)
                printf(CRED"1  "CRESET);
            else
                printf(".  ");
            fflush(stdout);
        }
        printf("\n");
        fflush(stdout);
    }
    shmdt(head);
}


/**
void printMtx(){
    int i;
    int j;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);

    int x;
    int y;
    int arrTC[6] = {0};
    int max = INT_MAX;
    int c = 0;

    while(c < 6){
        max = massimorelativo(&x, &y, max);
        arrTC[c] = x;
        arrTC[c+1] = y;
        printf("\nDEBUG: MAX: %d\t%d: %d\t%d: %d\n", max, c, arrTC[c], c+1, arrTC[c+1]);
        c = c+2;
    }

    c = 0;

    printf("\n### MAPPA ###\n");
    for(i = 0; i < H; i++){
        for(j = 0; j < W; j++){
            if((head[i][j].source == 1) && ((i == arrTC[0] && j == arrTC[1]) ||  (i == arrTC[2] && j == arrTC[3]) || (i == arrTC[4] && j == arrTC[5]))){
                printf(CWHITE"T   "CRESET);
            }else if((head[i][j].source == 1)){
                printf(CMAGENTA"S   "CRESET);
            }else if(head[i][j].one == 1)
                printf(CCYAN"X   "CRESET);
            else if((head[i][j].count >= 0) && ((i != arrTC[0] && j != arrTC[1]) && (i != arrTC[2] && j != arrTC[3]) && (i != arrTC[4] && j != arrTC[5])))
                printf(".   ");
            else if((i == arrTC[0] && j == arrTC[1]) ||  (i == arrTC[2] && j == arrTC[3]) || (i == arrTC[4] && j == arrTC[5])){
                if(head[i][j].count < 10)
                    printf(CRED"%d   "CRESET, head[i][j].count);
                else if(head[i][j].count > 10 && head[i][j].count < 100)
                    printf(CRED"%d  "CRESET, head[i][j].count);
                else if(head[i][j].count > 100)
                    printf(CRED"%d "CRESET, head[i][j].count);
            }else
                printf("%d   ", head[i][j].count);
        }
        printf("\n");
    }
    shmdt(head);
    printf("\n### X Holes\t. Libera\tT TopCell/Source\tS Source\t# Attraversamenti ###\n");
}
**/

int massimorelativo(int* i, int* j, int tmp){

    cell (*head)[W];
    int x;
    int y;
    int max = 0;

    if((head = shmat(getshmid(), NULL, 0)) == (void*)-1)
        printf("\nDEBUG: Errore shmat in shmLibs massimorelativo\n");

    for(x = 0; x < H; x++){

        for(y = 0; y < W; y++){

            if((max <= head[x][y].count) && (head[x][y].count < tmp)){

                max = head[x][y].count;
                *i = x;
                *j = y;

            }
        }
    }


    shmdt(head);

    return max;

}




void fillConf(conf* confg){

    int i;
    int j;
    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    for(i = 0; i < H; i++){
        for(j = 0; j < W; j++){
            head[i][j].one = 0;
            head[i][j].soCap = 0;
            head[i][j].soCapMax = confg -> soCap;
            head[i][j].soTime = confg -> soTime;
            head[i][j].source = 0;
            head[i][j].count = 0;
        }
    }
    shmdt(head);
}

int randomizeNum(int shift, int max){

    srand(time(NULL)*shift);
    return (rand()%max);

}


void clearAll(){

    int tkey = semget(TKEY, 0, 0666);
    int skey = semget(SKEY, 0, 0666);
    int mkey = msgget(MKEY, 0666);
    int semid = semget(readKey(), 0, 0666);
    int semidapp = semget(APPKEY, 0, 0666);
    int shmidOut = shmget(OUTPUT_KEY, 0, 0666);
    int semidOut = semget(OUTPUT_KEY, 0, 0666);
    int semid42 = semget(0x42, 0, 0666);
    int msgidOut = msgget(MKEY_OUT, 0666);

    deleteshm();
    shmctl(shmidOut, IPC_RMID, NULL);
    semctl(semidOut, 0, IPC_RMID, 0);
    semctl(semid, 0, IPC_RMID, 0);
    semctl(skey, 0, IPC_RMID, 0);
    semctl(tkey, 0, IPC_RMID, 0);
    semctl(semidapp, 0, IPC_RMID, 0);
    msgctl(mkey, IPC_RMID, NULL);
    semctl(semid42, 0, IPC_RMID, 0);
    msgctl(msgidOut, IPC_RMID, NULL);

}

int inevasi(){

    int msgid = msgget(MKEY, 0666);
    struct msqid_ds buf;
    int msglength = 4*sizeof(int) + sizeof(pid_t);
    msgctl(msgid, IPC_STAT, &buf);
    return buf.msg_qnum;

}

void printStats(){

    int outid = shmget(OUTPUT_KEY, 0, 0666);
    out* output = shmat(outid, NULL, 0);

    output -> inevasi = inevasi();
    printf("\n## STATISTICHE: ##\n");
    printf("\nSuccessi: %d\nInevasi: %d\nAbortiti: %d\nTaxi con più Strada: %ld\nTaxi tempo per richiesta: %ld\nTaxiStaccanovista: %ld\n",
            output->successi,
            output->inevasi,
            output->abortiti,
            (long)output->taxiStrada,
            (long)output->taxiTempo,
            (long)output->taxiStaccanovista);

    shmdt(output);

}


