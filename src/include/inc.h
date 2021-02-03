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
    #include <sys/wait.h>
    #include <time.h>
    #include <ctype.h>
    #include <signal.h>

    #if (!defined(W) && !defined(H)) || (!defined(W) || !defined(H))
            #error "W e H NON SONO STATE DEFINITE! (-D W60 -D H20)"
    #endif

#endif
