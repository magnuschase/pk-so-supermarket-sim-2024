#include "semaphores.h"

/*

Systemy operacyjne - projekt 2024/2025 - Supermarket (temat 10)
Imię i nazwisko: Jakub Kapała
Numer albumu: 151885
Kierunek: Informatyka, niestacjonarne

*/ 

int allocateSem(key_t semKey, int number, int flagi)
{
   int semID;
   if ( (semID = semget(semKey, number, flagi)) == -1)
   {
      perror("semget error (allocateSem): ");
      exit(1);
   }
   return semID;
}

void initSem(int semID, int number, int val)
{
   
   if ( semctl(semID, number, SETVAL, val) == -1 )
   {
      perror("semctl error (initSem): ");
      exit(1);
   }
}

int freeSem(int semID, int number)
{
   return semctl(semID, number, IPC_RMID, NULL);
}

int waitSem(int semID, int number, int flags)
{
   int result;
   struct sembuf operations[1];
   operations[0].sem_num = number;
   operations[0].sem_op = -1;
   operations[0].sem_flg = 0 | flags; //SEM_UNDO;
   
   if ( semop(semID, operations, 1) == -1 )
   {
      perror("semop error (waitSem)");
      return -1;
   }
   
   return 1;
}

void signalSem(int semID, int number)
{
   struct sembuf operations[1];
   operations[0].sem_num = number;
   operations[0].sem_op = 1;

   if (semop(semID, operations, 1) == -1 )
      perror("semop error (signalSem): ");

   return;
}

int valueSem(int semID, int number)
{
   return semctl(semID, number, GETVAL, NULL);
}