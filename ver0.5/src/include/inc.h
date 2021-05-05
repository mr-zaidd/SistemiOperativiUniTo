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
    int soCap;
    int soTime;
    int count;

}cell;

    #include "key.h"
    #include "sigLib.h"
    #include "shmLibs.h"
    #include "conf.h"
    #include "manhattan.h"

#endif
