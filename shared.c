#include "supermarket.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

int *current_cashiers;
int *customers_in_store;
int *store_open;
pthread_mutex_t cashier_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cashier_cond = PTHREAD_COND_INITIALIZER;
sem_t *customer_signal;
FILE *log_file = NULL;
CashierQueue cashier_queues[MAX_CASHIERS];

// Message format: [HH:MM:SS] pid:${PID} > ${message}
void log_message(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // Get current time in HH:MM:SS format
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char time_str[9]; // HH:MM:SS
    strftime(time_str, sizeof(time_str), "%H:%M:%S", t);

    // Get process ID
    pid_t pid = getpid();

    // Print to console
    printf("[%s] pid:%d > ", time_str, pid);
    vprintf(format, args);
    printf("\n");

    // Print to log file
    if (log_file) {
        fprintf(log_file, "[%s] pid:%d > ", time_str, pid);
        vfprintf(log_file, format, args);
        fprintf(log_file, "\n");
        fflush(log_file);
    }

    va_end(args);
}

void init_log_file(const char *filename) {
    log_file = fopen(filename, "a");
    if (!log_file) {
        perror("Failed to open log file");
        exit(EXIT_FAILURE);
    }
}

void close_log_file() {
    // Close log file
    if (log_file) {
        fclose(log_file);
    }
}