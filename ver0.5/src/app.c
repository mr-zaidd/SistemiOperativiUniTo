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
    printf("DEBUG: prima creazione dopo file\n");
    fflush(stdout);
    shmid = createshm();
    shmAt = shmat(shmid, NULL, 0);

    for(i=0; i<H; i++){
        for(j=0; j<W; j++){
            printf("%d\t", shmAt[i][j].one);
        }
        printf("\n");
    }

    shmdt(shmAt);
    printf("DEBUG: READKEY2: %d", readKey());
    fflush(stdout);
    sleep(10);
    removeAll(shmid);
    return 0;

}
