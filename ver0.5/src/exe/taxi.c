#include "../include/inc.h"


int* movimento(int i, int j, int x, int y){
    /** Opzioni:
     *
     *      1- Manhattan Algo
     *          + Calcoliamo la distanza in celle che non sono holes e
     *          calcoliamo il tempo come celle * tempoDiAttraversamento
     *      2- BFS (con costruzione albero e tutto il circo)
     *      3- Ricorsiva ricerca di un percorso (greedy algo)
     *
     * **/
}


int main(int argc, char* argv[]){

    int dur = atoi(argv[1]);
    struct timespec sec, sec2;

    printf("\nDEBUG: Argc di Taxi.c: %d\n", argc);

    printf("\nDormo per %d secondi...\n", dur);
    fflush(stdout);
    sec.tv_sec = dur;
    sec.tv_nsec = 0;
    nanosleep(&sec, &sec2);

    return 0;

}
