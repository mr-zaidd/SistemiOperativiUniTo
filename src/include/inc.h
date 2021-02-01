#ifndef INCLUDEALL
    #define INCLUDEALL

    #include <stdio.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <string.h>
    #include <stdlib.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <sys/wait.h>
    #include <time.h>
    #include <ctype.h>

#if (!defined(W) && !defined(H)) || (!defined(W) || !defined(H))
    #error "W e H NON SONO STATE DEFINITE! (-D W60 -D H20)"
#endif

typedef struct cella{

    int occupata;
    int attNSec;
    int capacity;
    int count;

    void* taxi;
    void* richieste;

}cella;

typedef struct conf{

    int nTaxi;
    int nSource;
    int holes;
    int cap;
    int attCell;
    int tOut;
    int dur;

}conf;

/* PARSEH */
void parse(conf*, char*);
void printConf(conf* sConf);

/* MAPPAH */
int insertHoles(cella*);
void mainMappa(int);


#endif
