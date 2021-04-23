#include "../include/inc.h"

void createKeyFile(int key){

    FILE* tmp = fopen("tmp/key","w");
    char k[16];
    sprintf(k, "%d", key);
    if(tmp == NULL){
        puts("\nImpossibile creare file tmp...\n");
        exit(EXIT_FAILURE);
    }else{
        puts("\nCreazione file tmp...\n");
        fputs(k,tmp);
        fclose(tmp);
    }

}

int readKey(){

    FILE* fp = fopen("tmp/key", "r");
    int k = 0;

    while(!feof(fp))
        fscanf(fp, "%d", &k);
    fclose(fp);
    return k;

}


void deleteKeyFile(){

    remove("tmp/key");

}
