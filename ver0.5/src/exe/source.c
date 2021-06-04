#include "../include/inc.h"


char* ch[4];
int count;
pid_t* figli;
cell (*head)[W];

void dieAndMore(int signum, siginfo_t* info, void* context){

    struct timespec up, up2;
    up.tv_sec = 4;
    up.tv_nsec = 0;

    if(signum == SIGUSR1){
        /**
        write(STDOUT_FILENO, "\nDEBUG: Sto partorendo una richiesta\n", 37);
        **/
        if((figli[count] = fork()) == -1){
            printf("\nDEBUG: RICHIESTA fallita\n");
        }else if(figli[count] == 0){
            execvp(ch[0], ch);
        }
        count++;
    }else if(signum == SIGTERM){
        free(figli);
        kill(0, SIGTERM);
        exit(EXIT_SUCCESS);
    }else
        ;;
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
    int semidapp = semget(APPKEY, 1, 0666);
    struct sembuf myopapp;

    head = shmat(getshmid(), NULL, 0);

    myopapp.sem_num = 0;
    myopapp.sem_flg = 0;
    myopapp.sem_op = 0;

    figli = (pid_t*)malloc(sizeof(pid_t)*100000);

    sa.sa_flags = SA_SIGINFO;
    sigemptyset(&sa.sa_mask);
    sa.sa_sigaction = dieAndMore;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGCHLD, &sa, NULL);

    up.tv_sec = 1;
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

    shmdt(head);

    myop.sem_op = 1;
    semop(semid, &myop, 1);


    sprintf(indexi, "%d", i);
    sprintf(indexy, "%d", j);

    ch[0] = "./exe/richiesta";
    ch[1] = indexi;
    ch[2] = indexy;
    ch[3] = NULL;

    count = 0;
/**
    free(indexi);
    free(indexy);
**/
    semop(semidapp, &myopapp, 1);


/**
    if((figli[count] = fork()) == -1){
        printf("\nDEBUG: RICHIESTA non generata");
    }else if(figli[count] == 0){
        execvp("./exe/richiesta", ch);
    }
    count++;
**/
    while(1){
        nanosleep(&up, &up2);
        /**
        printf("\nDEBUG: NUMERO MESSAGGI IN CODA: %d\n", inevasi());
        fflush(stdout);
        **/
        raise(SIGUSR1);

    }

    while(1)
        waitpid(WAIT_ANY, NULL, 0);

    return 0;

}
