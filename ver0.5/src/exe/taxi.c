#include "../include/inc.h"

int main(int argc, char* argv[]){

    int dur = atoi(argv[1]);

    printf("\nUNUSED ARGC TAXI: %d\n", argc);

    printf("\nDormo per %d secondi...\n", dur);
    fflush(stdout);
    sleep(dur);

    return 0;

}
