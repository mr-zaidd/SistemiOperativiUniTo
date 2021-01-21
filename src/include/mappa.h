#ifndef MAPPAH
#define MAPPAH

typedef struct cella{

    int occupata;

}cella;

int shmCreate(int, int);

int insertHoles(cella*);

int mainMappa(int);

#endif
