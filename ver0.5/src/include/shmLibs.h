#ifndef SHM

#define SHM

int createshm();
void fillConf(); /* Da Fare */
void insertHole(int i, int j);
int getshmid();
void holesHandler();
int deleteshm();
void printMtx();
int checkFreedom(int i, int j, int pos);
int checkPosition(int i, int j);
int checkOne(int i, int j);


#endif
