#ifndef MAPPA_H

    #define MAPPA_H

    typedef struct cella{

        int occupata;
        int attNSec;
        int capacity;
        int count;

        pid_t* taxi;
        pid_t richiesta;

    }cella;


    /* MAPPAH */
    int insertHoles(cella*);
    void updateCella(cella*, int, int);
    void createMappa(int, int, int, int);
    void printMX(cella*, int, int);


#endif
