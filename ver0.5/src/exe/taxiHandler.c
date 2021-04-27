#include "../include/inc.h"

int main(int argc, char* argv[]){

    int nTaxi = atoi(argv[1]);
    char* dur = argv[2];
    pid_t* figli = (pid_t*)malloc(nTaxi*sizeof(pid_t));
    int tmp = 0;
    int c;
    char* ch[3];
    ch[0] = "./taxi";
    ch[1] = dur;
    ch[2] = NULL;

    if(argc>3)
        /** Rise segnale per exit(1) e chiusura di HandlerSource e chiusura App **/

    printf("\nDEBUG: Numero dei Taxi da generare %d\n", nTaxi);

    while(tmp != nTaxi){

        if((figli[tmp] = fork()) == -1){

            printf("Taxi %d non generato", tmp);

        }else if(figli[tmp] == 0){

            /**
            printf("\nDEBUG: FIGLIO del TAXI\n");
            exit(0);
            **/
            printf("\nDEBUG: Figlio partorito da taxiHandler!\n");
            execvp("./exe/taxi", ch);
            perror("DEBUG EXEC:");
            exit(1);

        }
        tmp++;

    }

    for(c=0; c<nTaxi; c++)
        waitpid(WAIT_ANY, NULL, 0);

    printf("\nDEBUG: Morti tutti i figli del TaxiHandler\n");

    free(figli);

    return 0;

}
