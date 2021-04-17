#include "include/inc.h"
#include "include/mylib.h"

int main(){

    int key;
    int shmid;
    cell (*shmAt)[W];
    int i = 0;
    int j = 0;

    key = ftok(".", 'b');
    createKeyFile(key);
    printf("DEBUG: READ KEY: %d\n", readKey());
    shmid = createshm();
    shmAt = shmat(shmid, NULL, 0);

    for(i=0; i<H; i++){
        for(j=0; j<W; j++){
            printf("%d\t", shmAt[i][j].one);
        }
        printf("\n");
    }

    shmdt(shmAt);
    removeAll(shmid);
    return 0;

}
