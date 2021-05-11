#include "../include/inc.h"


char* ch[4];

void dieAndMore(int signum, siginfo_t* info, void* context){
    if(signum == 10){
        execvp(ch[0], ch);
    }else{
        printf("\nDEBUG: Signal: %d\n", signum);
        exit(33);
    }
}

int main(){

    int i;
    int j;
    int one;
    int fals = 0;
    int shift = getpid();
    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    struct timespec up, up2;
    struct sembuf myop;
    struct sigaction sa;
    int semid = semget(SKEY, 1, IPC_CREAT | 0666);
    char* indexi = (char*)malloc(16*sizeof(char));
    char* indexy = (char*)malloc(16*sizeof(char));

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = dieAndMore;
    sigaction(SIGALRM, &sa, NULL);

    up.tv_sec = 0;
    up.tv_nsec = 500000000;

    myop.sem_num = 0;
    myop.sem_flg = 0;
    myop.sem_op = -1;
    semop(semid, &myop, 1);

    while(!fals){
        i = randomizeNum(shift, H);
        j = randomizeNum(shift+2, W);
        one = checkOne(i,j);
        if(one == 1 && head[i][j].source == 0){
            head[i][j].source += 1;
            fals = 1;
        }
    }

    myop.sem_op = 1;
    semop(semid, &myop, 1);

    sprintf(indexi, "%d", i);
    sprintf(indexy, "%d", j);

    ch[0] = "./richiesta";
    ch[1] = indexi;
    ch[2] = indexy;
    ch[3] = NULL;

    while(1){
        nanosleep(&up, &up2);
        raise(SIGUSR1);
    }

    return 0;

}
