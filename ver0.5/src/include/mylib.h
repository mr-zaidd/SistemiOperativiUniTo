#ifndef MYLIB

#define MYLIB

#include "inc.h"

int createshm();
void holeshm();
void removeAll(int shmid);
void fillshm(int holes);
int readKey();
void holesHandler();
void createKeyFile(int key);
void printConf(conf* confg);
void parseConf(conf* confg, char* path);
char* checkPosition(int i, int j);
int checkFreedom(int i, int j, char* pos);
void insertHole(int i, int j);
void printMatx();

#endif
