#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define W 60
#define H 50

int randomIndex(){

    srand(time(0));
    int i = rand()%(W*H);
    printf("\n\n%d\n\n", i);
    return i;

}

void verOcc(int i){

    int r = i/W;
    int c = i-(r*W);
    printf("\n\n%d\t%d\n\n", r, c);

}

int main(){

    int* array[W*H] = {0};

    int i = randomIndex();
    verOcc(i);

/*
    for(int j = 0; j < W*H; j++){
    
        if((i%2 == 0))
            array[i] = 1;
        else
            array[i] = 0;

    }
*/


    //printf("\n\n%d\n\n", randomIndex(array));



    return 0;



}
