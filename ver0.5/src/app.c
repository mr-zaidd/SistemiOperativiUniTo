#include "include/inc.h"

int main(){


        char* nTaxi;
        char* nSources;
        conf* confg;
        char* timeout;
        cell (*shmAt)[W];
        int key;
        int shmid;
        int semidapp; /** WAIT 0 semaphore **/
        int semid;
        int c;
        char* fileConf = "../conf/conf.csv";
        char* ch[4];
        char* sCh[3];
        pid_t figli[2];
        struct sigaction sa;
        int g;
        int outshmid;
        int outsemid;
        out* output;
        sigset_t set;
        int* x;
        int* y;
        int fals = 1;
        int cPrint = 0;

        nTaxi = (char*)malloc(16*sizeof(char));
        timeout = (char*)malloc(16*sizeof(char));
        nSources = (char*)malloc(16*sizeof(char));

        semidapp = semget(APPKEY, 1, IPC_CREAT | 0666);
        semctl(semidapp, 0, SETVAL, 1);

        sa.sa_flags = SA_SIGINFO;
        sigemptyset(&sa.sa_mask);
        sa.sa_sigaction = ccHandlerSEC;
        sigaction(SIGINT, &sa, NULL);
        sigaction(SIGALRM, &sa, NULL);
        sigaction(SIGTERM, &sa, NULL);

        /** OUTPUT **/
        outshmid = shmget(OUTPUT_KEY, sizeof(out), IPC_CREAT | 0666);
        outsemid = semget(OUTPUT_KEY, 1, IPC_CREAT | 0666);
        semctl(outsemid, 0, SETVAL, 1);

        output = shmat(outshmid, NULL, 0);
        output -> successi = 0;
        output -> inevasi = 0;
        output -> abortiti = 0;
        output -> taxiStrada = (pid_t)0;
        output -> taxiTempo = (pid_t)0;
        output -> taxiStaccanovista = (pid_t)0;

        shmdt(output);

        confg = (conf*) malloc(sizeof(conf));
        key = ftok(".", 'b');
        createKeyFile(key);
        parseConf(confg, fileConf);
        printConf(confg);
        shmid = createshm();
        semid = semget(readKey(), W*H, IPC_CREAT | 0666);

        for(g = 0; g<W*H; g++)
            semctl(semid, g, SETVAL, 1);

        shmAt = shmat(shmid, NULL, 0);
        fillConf(confg);
        holesHandler(confg->soHoles);

        sprintf(nSources, "%d", confg->soSources);
        sprintf(nTaxi, "%d", confg->soTaxi);
        sprintf(timeout, "%d", confg->soTimeOut);

        ch[0] = "./exe/taxiH";
        ch[1] = nTaxi;
        ch[2] = timeout;
        ch[3] = NULL;

        sCh[0] = "./exe/sourceH";
        sCh[1] = nSources;
        sCh[2] = NULL;

        if((figli[0]=fork()) == -1){

            perror("\nDEBUG: FORK ANDATO MALE\n");
            shmdt(shmAt);
            deleteshm();
            free(timeout);
            free(nTaxi);
            free(nSources);
            free(confg);
            exit(EXIT_FAILURE);

        }else if(figli[0] == 0){
            execvp(ch[0], ch);
        }

        if((figli[1]=fork()) == -1){

            perror("\nDEBUG: FORK ANDATO MALE\n");
            shmdt(shmAt);
            deleteshm();
            free(timeout);
            free(nTaxi);
            free(nSources);
            free(confg);
            exit(EXIT_FAILURE);

        }else if(figli[1] == 0){
            execvp(sCh[0], sCh);
        }

        shmdt(shmAt);
        free(timeout);
        free(nTaxi);
        free(nSources);

        alarm(confg->soDuration);

        while(fals){
            printMtxSEC(cPrint);
            sleep(1);
            cPrint++;
            if(cPrint == (confg->soDuration - 1)){
                fals = 0;
                free(confg);
            }
        }


        for(c=0; c<2; c++)
            waitpid(WAIT_ANY, NULL, 0);

        return 0;

    }

