#include "./include/inc.h"
#include "./include/mappa.h"


int main(){

    int mykey = ftok(".",'X');
    int shmid;
    cella* tmp;

    mainMappa(mykey);

    /* creazione taxi && creazione richieste */

    shmid = shmget(mykey, 0, (void*)0);
    shmctl(shmid, IPC_RMID, 0);


    return 0;


}
