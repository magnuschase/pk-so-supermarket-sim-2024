#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdarg.h>
#include <stdio.h>
#include <semaphore.h>

/*

Systemy operacyjne - projekt 2024/2025 - Supermarket (temat 10)
Imię i nazwisko: Jakub Kapała
Numer albumu: 151885
Kierunek: Informatyka, niestacjonarne

*/

#define MIN_CASHIERS 2
#define MAX_CASHIERS 10
#define K 2 // Number of customers per cash register
#define PORT 151885 // Port for socket communication

#define QUEUE_PER_CUSTOMER 10 // Time in seconds needed to serve a single customer
#define SHOPPING_TIME_MIN 10 // Minimum shopping time in seconds
#define SHOPPING_TIME_MAX 70 // Maximum shopping time in seconds
#define CUSTOMER_WAIT_MIN 5 // Minimum time between customer arrivals in seconds
#define CUSTOMER_WAIT_MAX 20 // Maximum time between customer arrivals in seconds
#define FIRE_WAIT_MIN 5 // Minimum time before which fire alarm is triggered
#define FIRE_WAIT_MAX 20 // Maximum time before which fire alarm is triggered

extern int *current_cashiers; // Open cash registers
extern int *customers_in_store; // Customers present in store
extern int *store_open; // Store status
extern pthread_mutex_t cashier_mutex; // Mutex for cashier operations
extern pthread_cond_t cashier_cond; // Condition variable for cashier operations
extern sem_t *customer_signal; // Semaphore for customer-manager signaling
extern FILE *log_file; // Log file

typedef struct {
    int customers;
    pthread_cond_t cond;
} CashierQueue;

extern CashierQueue cashier_queues[MAX_CASHIERS];

void log_message(const char *format, ...); // Log a message to the console and log file
void init_log_file(const char *filename); // Initialize the log file
void close_log_file(); // Close the log file

#endif // SUPERMARKET_H