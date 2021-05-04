#include "../include/inc.h"

void printConf(conf* confg){

    printf("\n### CONFIGURAZIONE:");
    printf("\nTAXI: %d\nSOURCE: %d\nHOLES: %d\nCAPACITA: %d\nATTRAVERSAMENTO CELLA: %d\nTIMEOUT: %d\nDURATION: %d\n",
            confg -> soTaxi,
            confg -> soSources,
            confg -> soHoles,
            confg -> soCap,
            confg -> soTime,
            confg -> soTimeOut,
            confg -> soDuration
            );

}

void parseConf(conf* confg, char* path){

    FILE* fp = fopen(path, "r");
    char line[512];
    int confs[9] = {0};
    int j = 0;

    if(fp == NULL){

        perror("\nFile di Configurazione non trovato...\n");
        exit(1);

    }

    while(fgets(line, sizeof(line), fp)){

        char* tok;
        tok = strtok(line, ",");

        while(tok != NULL){

            if(isdigit(*tok)){

                confs[j] = atoi(tok);
                j++;

            }

            tok = strtok(NULL, ",");

        }

    }

    srand(time(0));

    confg -> soTaxi = confs[0];
    confg -> soSources = confs[1];
    confg -> soHoles = confs[2];
    confg -> soCap = (rand()%(confs[4]-confs[3]+1)) + confs[3];
    confg -> soTime = (rand()%(confs[6]-confs[5]+1)) + confs[5];
    confg -> soTimeOut = confs[7];
    confg -> soDuration = confs[8];

    if(
        !(confg -> soTaxi > 0
        &&
        confg -> soSources > 0
        &&
        confg -> soHoles < W*H
        &&
        confg -> soCap > 0
        &&
        confg -> soTime > 0
        &&
        confg -> soTimeOut > 0
        &&
        confg -> soDuration > 0)
    ){
        perror("Parametri del file di Configurazione Non Validi");
        exit(EXIT_FAILURE);
    }
}

