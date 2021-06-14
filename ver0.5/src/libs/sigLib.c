#include "../include/inc.h"

void ccHandlerSEC(int signum, siginfo_t* info, void* context){

     if(signum == SIGALRM){
         kill(0, SIGTERM);
         printMtx();
         printStats();
         clearAll();
     }else if(signum == SIGINT){

        clearAll();
        kill(0, SIGTERM);
        exit(33);

     }else if(signum == SIGTERM){
         ;;
     }
}
