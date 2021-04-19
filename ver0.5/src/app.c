#include "include/inc.h"
#include "include/mylib.h"

int main(){

    int key;
    int shmid;
    cell (*shmAt)[W];
    char* fileConf = "../conf/conf.csv";
    int i = 0;
    int j = 0;
    conf* confg;

    confg = (conf*) malloc(sizeof(conf));
    key = ftok(".", 'b');
    createKeyFile(key);
    printf("DEBUG: READ KEY: %d\n", readKey());
    parseConf(confg, fileConf);
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

/****
 *
 *
 *              (I) PRENDERE I DATI DI CONFIG DAL FILE E SALVARLI IN STRUTTURA
 *
 *              (II) PASSARE IL NUMERO DI HOLES A FILLSHM()
 *
 *
 */


