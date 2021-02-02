#include "../include/inc.h"
#include "../include/sigLib.h"

void sigHandlerDefault(int signum){

    FILE* fp;
    int shmid;
    char buff[32];
    int myKey;

    fp = fopen("../../tmp/key", "r");
    fgets(buff, 32, fp);
    myKey = atoi(buff);

    shmid = shmget(myKey, 0, IPC_CREAT | 0666);
    shmctl(shmid, IPC_RMID, 0);

}
