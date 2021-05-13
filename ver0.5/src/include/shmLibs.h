#ifndef SHM

#define SHM

int createshm();
void fillConf(conf* confg);
void insertHole(int i, int j);
int getshmid();
void holesHandler(int holes);
void deleteshm();
void printMtx();
int checkFreedom(int i, int j, int pos);
int checkPosition(int i, int j);
int checkOne(int i, int j);

int randomizeNum(int shift, int max);

void clearAll();

#endif
