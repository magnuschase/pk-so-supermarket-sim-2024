#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

/*

Systemy operacyjne - projekt 2024/2025 - Supermarket (temat 10)
Imię i nazwisko: Jakub Kapała
Numer albumu: 151885
Kierunek: Informatyka, niestacjonarne

*/ 

// Logic for a single customer process
void *customer_thread(void *arg) {
		// Only operate when store is opened
    pthread_mutex_lock(&cashier_mutex);
    if (!*store_open) {
        pthread_mutex_unlock(&cashier_mutex);
        return NULL;
    }
    (*customers_in_store)++;
    log_message("Customer entered. Total customers: %d", *customers_in_store);
 		// Signal manager process
    sem_post(customer_signal);
    pthread_mutex_unlock(&cashier_mutex);
		// Simulate shopping time - between 10 and 70 seconds
    sleep(rand() % (SHOPPING_TIME_MAX - SHOPPING_TIME_MIN) + SHOPPING_TIME_MIN);

    // Queue customer for a cashier
    int cashier_index = rand() % *current_cashiers;
    cashier_queues[cashier_index].customers++;
		log_message("Customer queued at cashier %d. Queue length: %d", cashier_index, cashier_queues[cashier_index].customers);
    pthread_cond_signal(&cashier_queues[cashier_index].cond);
		// Queue should take 10 seconds per customer
    sleep(cashier_queues[cashier_index].customers * QUEUE_PER_CUSTOMER); 

    pthread_mutex_lock(&cashier_mutex);
    if (!*store_open) {
        pthread_mutex_unlock(&cashier_mutex);
        return NULL;
    }
    (*customers_in_store)--;
    log_message("Customer left. Total customers: %d", *customers_in_store);

    // Dequeue customer from the cashier
    cashier_queues[cashier_index].customers--;
    pthread_cond_signal(&cashier_queues[cashier_index].cond);

    sem_post(customer_signal); // Signal manager process
    pthread_mutex_unlock(&cashier_mutex);

    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <log_filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Initialize log file
    init_log_file(argv[1]);

    // Open named semaphore
    customer_signal = sem_open("/customer_signal", 0);
    if (customer_signal == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    // Open shared memory for customers_in_store
    int fd = shm_open("/customers_in_store", O_RDWR, 0644);
    if (fd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }
    customers_in_store = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (customers_in_store == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    close(fd);

    // Open shared memory for store_open
    fd = shm_open("/store_open", O_RDWR, 0644);
    if (fd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }
    store_open = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (store_open == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    close(fd);

    // Open shared memory for current_cashiers
    fd = shm_open("/current_cashiers", O_RDWR, 0644);
    if (fd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }
    current_cashiers = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (current_cashiers == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    close(fd);

    // Continuously create new customers until the store is closed
    while (*store_open) {
        pthread_t customer_thread_id;
        pthread_create(&customer_thread_id, NULL, customer_thread, NULL);
        pthread_detach(customer_thread_id); // Detach the thread to allow it to run independently
        sleep(rand() % (CUSTOMER_WAIT_MAX - CUSTOMER_WAIT_MIN) + CUSTOMER_WAIT_MIN); // Customers enter at random intervals between 5 and 20 seconds
    }

    // Check for store closure
    pthread_mutex_lock(&cashier_mutex);
    while (*store_open) {
        pthread_cond_wait(&cashier_cond, &cashier_mutex);
    }
    pthread_mutex_unlock(&cashier_mutex);

    // Close log file
    close_log_file();

    // Close named semaphore
    sem_close(customer_signal);

    // Unmap shared memory
    munmap(customers_in_store, sizeof(int));
    munmap(store_open, sizeof(int));
    munmap(current_cashiers, sizeof(int));

    return 0;
}