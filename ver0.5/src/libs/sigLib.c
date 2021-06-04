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

     }else if(signum == SIGTERM)
         ;;
}

void ccHandler(int signum, siginfo_t* info, void* context){

     if(signum == SIGALRM){
         /**
         write(STDOUT_FILENO,"\nSTO MORENDO ORA.\n", 18);
         **/
         kill(0, SIGTERM);
         printMtx();
         printStats();
         clearAll();
     }else if(signum == SIGINT){

        char cmd[16];
        char key[8];

        char cmd2[16];
        char key2[8];
        int semid = semget(readKey(), 0, IPC_CREAT | 0666);

        char cmd3[16];
        char key3[8];
        int semidS = semget(SKEY, 0, IPC_CREAT | 0666);

        char cmd4[16];
        char key4[8];
        int semidT = semget(TKEY, 0, IPC_CREAT | 0666);

        char cmd5[16];
        char key5[8];
        int msgid = msgget(MKEY, IPC_CREAT | 0666);

        char cmd6[16];
        char key6[8];
        int semidApp = semget(APPKEY, 0, IPC_CREAT | 0666);



        char cmd7[16];
        char key7[8];
        int shmidOut = shmget(OUTPUT_KEY, 0, IPC_CREAT | 0666);

        char cmd8[16];
        char key8[8];
        int semidOut = semget(OUTPUT_KEY, 0, IPC_CREAT | 0666);




        strcpy(cmd, "ipcrm -m");
        sprintf(key, "%d", getshmid());
        strcat(cmd, key);
        if(system(cmd) == -1){
            printf("\nDEBUG: ID: %d Shared Memory non trovato - Non esiste\n", getshmid());
        }

        strcpy(cmd2, "ipcrm -s");
        sprintf(key2, "%d", semid);
        strcat(cmd2, key2);
        if(system(cmd2) == -1){
            printf("\nDEBUG: ID Semaforo Mappa non trovato - Non esiste\n");
        }

        strcpy(cmd3, "ipcrm -s");
        sprintf(key3, "%d", semidS);
        strcat(cmd3, key3);
        if(system(cmd3) == -1){
            printf("\nDEBUG: ID Semaforo Taxi non trovato - Non esiste\n");
        }


        strcpy(cmd4, "ipcrm -s");
        sprintf(key4, "%d", semidT);
        strcat(cmd4, key4);
        if(system(cmd4) == -1){
            printf("\nDEBUG: ID non trovato - Non esiste\n");
        }

        strcpy(cmd5, "ipcrm -q");
        sprintf(key5, "%d", msgid);
        strcat(cmd5, key5);
        if(system(cmd5) == -1){
            printf("\nDEBUG: ID non trovato - Non esiste\n");
        }

        strcpy(cmd6, "ipcrm -s");
        sprintf(key6, "%d", semidApp);
        strcat(cmd6, key6);
        if(system(cmd6) == -1){
            printf("\nDEBUG: ID non trovato - Non esiste\n");
        }




        strcpy(cmd7, "ipcrm -m");
        sprintf(key7, "%d", shmidOut);
        strcat(cmd7, key7);
        if(system(cmd7) == -1){
            printf("\nDEBUG: ID Semaforo Mappa non trovato - Non esiste\n");
        }

        strcpy(cmd8, "ipcrm -s");
        sprintf(key8, "%d", semidOut);
        strcat(cmd8, key8);
        if(system(cmd8) == -1){
            printf("\nDEBUG: ID Semaforo Taxi non trovato - Non esiste\n");
        }





        kill(0, SIGTERM);

        printf("\nDEBUG: Arrivato segnale di INTERRUZIONE - shm e sems eliminati forzatamente\n");
        exit(EXIT_FAILURE);
    }else if(signum == SIGTERM)
        ;;
}

