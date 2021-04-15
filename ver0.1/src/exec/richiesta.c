#include "../include/inc.h"
#include "../include/mappa.h"
#include "../include/parse.h"
#include "../include/sigLib.h"

#define TYPE 7

struct mesg_buffer{

    long type;
    int partenza;
    int destinazione;

}msg;

int main(){

    cella* arr;
    int mykey;
    int shmid;
    int msgid;
    FILE* fp;
    char buff[32];
    int index;
    int destinazione;

    fp = fopen("./tmp/key", "r");
    if(fp == NULL){

        printf("\nE' SBAGLIATO IL PATH DELLA KEY IN RICHIESTA\n");
        exit(EXIT_FAILURE);

    }
    fgets(buff, 32, fp);
    mykey = atoi(buff);

    shmid = shmget(mykey, 0, IPC_CREAT | 0666);
    arr = (cella*)shmat(shmid, NULL, 0);

    msgid = msgget(mykey, IPC_CREAT | 0666);

    srand(time(0));
    index = rand()%(W*H);
    if( (arr[index].richiesta == 0) && (arr[index].occupata == 0) )
        arr[index].richiesta = getpid();
    else{
        shmdt(arr);
        exit(EXIT_FAILURE);
    }

    destinazione = rand()%(W*H);

    msg.type = TYPE;
    msg.partenza = index;
    msg.destinazione = (destinazione != index) ? destinazione : 0;

    msgsnd(msgid, &msg, 2*sizeof(int), 0);

    shmdt(arr);

    return 0;

}
