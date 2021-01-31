#include "../include/inc.h"


void parse(conf* sConf, char* path){

    FILE* fp = fopen(path, "r");
    if(fp == NULL){
        perror("\n\nFile di Configurazione non trovato\n\n");
        exit(1);
    }
    char line[1024];
    int conf[9] = {0};
    int j = 0;

    while(fgets(line, sizeof(line), fp)){

        char* tok;
        tok = strtok(line, ",");


        while(tok != NULL){

            if(isdigit(*tok)){
                conf[j] = atoi(tok);
                j++;
            }

            tok = strtok(NULL, ",");
        }

    }

    srand(time(0));

    sConf -> nTaxi = conf[0];
    sConf -> nSource = conf[1];
    sConf -> holes = conf[2];
    sConf -> cap = (rand()%(conf[4]-conf[3]+1)) + conf[3];
    sConf -> attCell = (rand()%(conf[6]-conf[5]+1)) + conf[5];
    sConf -> tOut = conf[7];
    sConf -> dur = conf[8];

    if(
            !(sConf -> nTaxi > 0
            &&
            sConf -> nSource > 0
            &&
            sConf -> holes < W*H
            &&
            sConf -> cap > 0
            &&
            sConf -> attCell > 0
            &&
            sConf -> tOut > 0
            &&
            sConf -> dur > 0)
        ){
        perror("Parametri del file di Configurazione: NON validi");
        exit(EXIT_FAILURE);

    }
}

int main(){


    char* path = "../../conf.csv";
    conf* sConf = (conf*) malloc(sizeof(conf));



    parse(sConf, path);
    
    printf(
            "\n\nTAXI: %d\nSOURCE: %d\nHOLES: %d\nCAPACITA': %d\nATTRAVERSAMENTO CELLA: %d\nTIMEOUT: %d\nDARATION: %d\n\n",
            sConf -> nTaxi,
            sConf -> nSource,
            sConf -> holes,
            sConf -> cap,
            sConf -> attCell,
            sConf -> tOut,
            sConf -> dur
          );


    free(sConf);

    return 0;

}
