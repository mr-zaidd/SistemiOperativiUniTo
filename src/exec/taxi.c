#include "../include/inc.h"
#include "../include/mappa.h"
#include "../include/parse.h"
#include "../include/sigLib.h"

#define TYPE 7

int breaks = 1;

struct mesg_buffer{

    long type;
    int partenza;
    int destinazione;

}msg;

int movimento(cella* arr, int dest, int* path, int curr);
void sigHandlerTaxi(int);


int isLibera(cella x){

    if(x.occupata == 0)
        return 1;
    else
        return 0;

}

void sigHandlerTaxi(int signum){

    switch(signum){
        case SIGALRM:
            breaks = 0;
            break;
        default:
            exit(1);
    }

}

void prova(cella* arr, int partenza, int dest){
    int* path = malloc(H*W*sizeof(int));
    int o;
    int i;
    path[0] = partenza;
    if(movimento(arr, dest, path, 0)){
        printf("\n\nTrovato*****************************************\n\n");
        fflush(stdout);
        for(i = 1; path[i-1] != dest && i < 30; i++){
            o = path[i]/W;
            printf("(%d,%d)\n", o, path[i]-(o*W));
        }
    }
}

int movimento(cella* arr, int dest, int* path, int curr){

    int destra = path[curr]+1;
    int sinistra = path[curr]-1;
    int sopra = path[curr]-W;
    int sotto = path[curr]+W;

    int corrente = path[curr];

    printf("\n%d giro\n", curr);
    fflush(stdout);

    if(path[curr] == dest)
        return 1;
    if( corrente/W == destra/W && isLibera( arr[destra] ) ){
        path[curr+1] = destra;
        if( movimento(arr, dest, path, curr+1) ){
            return 1;
        }
    }
    if( corrente/W == sinistra/W && isLibera(arr[sinistra]) ){
        path[curr+1] = sinistra;
        if(movimento(arr, dest, path, curr+1))
                return 1;
    }
    if( corrente/W > 0 && isLibera(arr[sopra])){
        path[curr+1] = sopra;
        if(movimento(arr, dest, path, curr+1))
            return 1;
    }
    if( corrente/W < H-1 && isLibera(arr[sotto])){
        path[curr+1] = sotto;
        if(movimento(arr, dest, path, curr+1))
            return 1;
    }

    return 0;

}

int main(int argc, char* argv[]){

    cella* arr;
    int mykey;
    int shmid;
    int msgid;
    FILE* fp;
    char buff[32];
    int index;
    int timeOut = atoi(argv[1]);
    int capacity = atoi(argv[2]);
    struct sigaction sa;

    printf("\nSONO TAXi\n");

    fp = fopen("./tmp/key", "r");
    if(fp == NULL){

        printf("\nE' SBAGLIATO IL PATH DELLA KEY IN TAXI\n");
        exit(EXIT_FAILURE);

    }

    bzero(&sa, sizeof(sa));
    sa.sa_handler = sigHandlerTaxi;
    sigaction(SIGALRM, &sa, NULL);

    fgets(buff, 32, fp);
    mykey = atoi(buff);

    shmid = shmget(mykey, 0, IPC_CREAT | 0666);
    arr = (cella*) shmat(shmid, NULL, 0);

    msgid = msgget(mykey, IPC_CREAT | 0666);

    srand(time(0));
    index = rand()%(W*H);
    /*if( (arr[index].capacity < capacity) && (arr[index].occupata == 0) ){
    
        printf("Sono nell'If di taxi");
        fflush(stdout);
        *(arr[index].taxi + arr[index].capacity) = getpid();
        arr[index].capacity += 1;

    }else{

        shmdt(arr);
        exit(EXIT_FAILURE);

    }*/


    /* IMPLEMENTARE ATTESA SEGNALE START */

    alarm(timeOut);

    printf("SONO TAXI DOPO ALARM");

    msgrcv(msgid, &msg, 2*sizeof(int), TYPE, 0);
    if(arr[msg.destinazione].occupata == 1){
        /* Richiesta Aborted */
        shmdt(arr);
        exit(0);
    }
    prova(arr, msg.partenza, msg.destinazione);



    shmdt(arr);

    return 0;

}
