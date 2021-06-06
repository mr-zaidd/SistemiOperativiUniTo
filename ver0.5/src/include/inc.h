#ifndef INCLUDEALL

    #define _GNU_SOURCE

    #define INCLUDEALL

    #include <stdio.h>
    #include <unistd.h>
    #include <sys/types.h>
    #include <string.h>
    #include <strings.h>
    #include <stdlib.h>
    #include <sys/ipc.h>
    #include <sys/shm.h>
    #include <sys/sem.h>
    #include <sys/msg.h>
    #include <sys/wait.h>
    #include <time.h>
    #include <ctype.h>
    #include <signal.h>
    #include <errno.h>
    #include <limits.h>

    #if (!defined(W) && !defined(H)) || (!defined(W) || !defined(H))
            #error "W e H NON SONO STATE DEFINITE! (-D W=60 -D H=20)"
    #endif

typedef struct conf{

    int soTaxi;
    int soSources;
    int soHoles;
    int soCap;
    int soTime;
    int soTimeOut;
    int soDuration;

}conf;

typedef struct cell{

    int one;
    int soCapMax;
    int soCap;
    int soTime;
    int source;
    int count;

}cell;

typedef struct mex{

    long mtype;
    int arrivi[4];
    pid_t pidRic;

}mex;

typedef struct mexSig{

    long mtype;
    int segnale;

}mexSig;

typedef struct out{

    int successi;
    int inevasi;
    int abortiti;
    pid_t taxiStrada;
    int stradaTaxi;
    pid_t taxiTempo;
    int tempoTaxi;
    pid_t taxiStaccanovista;
    int staccanovistaTaxi;

}out;

    #include "key.h"
    #include "sigLib.h"
    #include "shmLibs.h"
    #include "conf.h"
    #include "manhattan.h"

#define TKEY 0x11
#define SKEY 0x1B
#define MKEY 0x5E
#define APPKEY 0x7B

#define INVIO 50

#define OUTPUT_KEY 0x2A
#define MKEY_OUT 0x3E7


#define CWHITE   "\x1B[37m"
#define CRED     "\x1b[31m"
#define CGREEN   "\x1b[32m"
#define CYELLOW  "\x1b[33m"
#define CBLUE    "\x1b[34m"
#define CMAGENTA "\x1b[35m"
#define CCYAN    "\x1b[36m"
#define CRESET   "\x1b[0m"

#endif
