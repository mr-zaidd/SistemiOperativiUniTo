#include "../include/inc.h"


char* ch[4];
int count;
pid_t* figli;

void dieAndMore(int signum, siginfo_t* info, void* context){
    if(signum == 10){
        if((figli[count] = fork()) == -1){
            printf("\nDEBUG: RICHIESTA fallita\n");
        }else if(figli[count] == 0){
            execvp(ch[0], ch);
        }
        count++;
    }else if(signum == SIGTERM){
        kill(0, SIGTERM);
        exit(EXIT_SUCCESS);
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
    struct timespec up, up2;
    struct sembuf myop;
    struct sigaction sa;
    int semid = semget(SKEY, 1, IPC_CREAT | 0666);
    char* indexi = (char*)malloc(16*sizeof(char));
    char* indexy = (char*)malloc(16*sizeof(char));
    cell (*head)[W] = shmat(getshmid(), NULL, 0);
    int semidapp = semget(APPKEY, 1, 0666);
    struct sembuf myopapp;

    myopapp.sem_num = 0;
    myopapp.sem_flg = 0;
    myopapp.sem_op = 0;

    figli = (pid_t*)malloc(sizeof(pid_t)*1000);

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = dieAndMore;
    sigaction(SIGALRM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);

    up.tv_sec = 5;
    up.tv_nsec = 0;

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

    semop(semidapp, &myopapp, 1);

    sprintf(indexi, "%d", i);
    sprintf(indexy, "%d", j);

    ch[0] = "./exe/richiesta";
    ch[1] = indexi;
    ch[2] = indexy;
    ch[3] = NULL;

    count = 0;

    if((figli[count] = fork()) == -1){
        printf("\nDEBUG: RICHIESTA non generata");
    }else if(figli[count] == 0){
        execvp("./exe/richiesta", ch);
    }
    count++;

    while(1){

        nanosleep(&up, &up2);
        raise(SIGUSR1);

    }

    return 0;

}
