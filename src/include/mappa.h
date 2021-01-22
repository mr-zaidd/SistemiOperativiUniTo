#ifndef MAPPAH
#define MAPPAH

typedef struct cella{

    int occupata;

    int attNSec;
    int capacity;

    int count;
    void* taxi;
    void* richieste;

}cella;

int shmCreate(int, int);

int insertHoles(cella*);

void mainMappa(int);

#endif
