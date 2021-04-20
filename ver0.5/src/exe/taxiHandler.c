#include "../include/inc.h"
#include "../include/mylib.h"

int main(int argc, char* argv[]){

    int nTaxi = atoi(argv[1]);
    char* dur = argv[2];
    pid_t figli[nTaxi];
    int tmp = 0;
    int c;
    char* ch[3] = {"echo", dur, NULL};

    while(tmp != nTaxi){

        if((figli[tmp] = fork()) == -1){

            printf("Taxi %d non generato", tmp);

        }else if(figli[tmp] == 0){

            execvp(ch[0], ch);

        }
        tmp++;

    }

    for(c=0; c<nTaxi; c++)
        waitpid(WAIT_ANY, NULL, 0);

    return 0;

}
