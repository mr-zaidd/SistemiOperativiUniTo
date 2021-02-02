#ifndef PARSE_H
    #define PARSE_H

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

#endif
