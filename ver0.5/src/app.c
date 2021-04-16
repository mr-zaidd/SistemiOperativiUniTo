#include "include/inc.h"
#include "include/mylib.h"

int main(int argc, int *argv[]){

    int key;
    int shmid;
    cell* shmAt[H][W];
    int i = 0;
    int j = 0;

    key = ftok(".", 'b');
    createKeyFile(key);
    shmid = createshm();

    for(i=0; i<H; i++){
        for(j=0; j<W; j++){
            printf("%d\t", shmAt[i][j]);
        }
        printf("\n");
    }

    removeshm(shmid, &shmAt);
    return 0;

}
