#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/errno.h>

int allocateSem(key_t semKey, int number, int flagi);
void initSem(int semID, int number, int val);
int freeSem(int semID, int number);
int waitSem(int semID, int number, int flags);
void signalSem(int semID, int number);
int valueSem(int semID, int number);