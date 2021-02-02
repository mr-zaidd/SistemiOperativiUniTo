#ifndef MAPPA_H

    #define MAPPA_H

    typedef struct cella{

        int occupata;
        int attNSec;
        int capacity;
        int count;

        void* taxi;
        void* richieste;

    }cella;


    /* MAPPAH */
    int insertHoles(cella*);
    void createMappa(int, int);
    void printMX(cella*, int, int);


#endif
