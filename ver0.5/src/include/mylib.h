#ifndef MYLIB

#define MYLIB

#include "inc.h"

int createshm();
void holeshm();
void removeshm(int shmid, cell **shmAt);
void fillshm(int shmid);
int readKey();
void holeshm();
void createKeyFile(int key);
void printConf(conf* confg);
void parse(conf* confg, char* path);

#endif
