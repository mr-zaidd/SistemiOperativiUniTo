#include "./include/inc.h"
#include "./include/mappa.h"


int main(){

    int mykey = ftok(".",'X');
    int shmid;
    cella* tmp;

    shmid = shmget(mykey, 0, IPC_CREAT);
    mainMappa(mykey);
    /* creazione taxi && creazione richieste  */

    tmp = shmat(shmid);

    shmdt(
    shmctl(shmid, IPC_RMID, 0);


    return 0;


}
