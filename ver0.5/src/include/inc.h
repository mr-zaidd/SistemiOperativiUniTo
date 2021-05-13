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

#endif
