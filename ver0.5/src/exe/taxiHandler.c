#include "../include/inc.h"
#include "../include/mylib.h"

int main(int argc, char* argv[]){

    int nTaxi = atoi(argv[1]);
    char* dur = argv[2];
    pid_t* figli = (pid_t*)malloc(nTaxi*sizeof(pid_t));
    int tmp = 0;
    int c;
    char* ch[3];
    ch[0] = "echo";
    ch[1] = dur;
    ch[2] = NULL;

    printf("\nDEBUG: ARGC %d\n", argc);

    while(tmp != nTaxi){

        if((figli[tmp] = fork()) == -1){

            printf("Taxi %d non generato", tmp);

        }else if(figli[tmp] == 0){

            execvp(ch[0], ch);

        }
        printf("\nDEBUG: TMP TH: %d\n", tmp);
        tmp++;

    }

    for(c=0; c<nTaxi; c++)
        waitpid(WAIT_ANY, NULL, 0);

    free(figli);

    return 0;

}
