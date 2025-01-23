#include "supermarket.h"
#include "ansi-color-codes.h"
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
		CustomerConfig *customer_config = (CustomerConfig *)arg;

		// Only operate when store is opened
		pthread_mutex_lock(&cashier_mutex);
		if (!*store_open) {
				pthread_mutex_unlock(&cashier_mutex);
				return NULL;
		}
		(*customers_in_store)++;
		log_message(YELHB BYEL " Ding dong! " reset GRNHB BGRN " Customer entered. " reset BHGRN " Total customers: %d" reset, *customers_in_store);
 		// Signal manager process
		sem_post(customer_signal);
		pthread_mutex_unlock(&cashier_mutex);
		// Simulate shopping time - default 10s-70s
		sleep(rand() % (customer_config->shopping_time_max - customer_config->shopping_time_min) + customer_config->shopping_time_min);

		// Queue customer for a cashier
		int cashier_index = rand() % *current_cashiers;
		cashier_queues[cashier_index].customers++;
		log_message(CYNHB BCYN " Cashier %d. " reset MAGHB BMAG " Customer queued. " reset BHCYN " Queue length: %d" reset, cashier_index, cashier_queues[cashier_index].customers);
		pthread_cond_signal(&cashier_queues[cashier_index].cond);
		// Queue should take specified amount of seconds per customer (default 10s)
		sleep(cashier_queues[cashier_index].customers * customer_config->queue_per_customer); 

		pthread_mutex_lock(&cashier_mutex);
		if (!*store_open) {
				pthread_mutex_unlock(&cashier_mutex);
				return NULL;
		}
		(*customers_in_store)--;
		log_message(YELHB BYEL " Ding dong! " reset REDHB BRED " Customer left. " reset BHRED " Total customers: %d" reset, *customers_in_store);

		// Dequeue customer from the cashier
		cashier_queues[cashier_index].customers--;
		pthread_cond_signal(&cashier_queues[cashier_index].cond);

		sem_post(customer_signal); // Signal manager process
		pthread_mutex_unlock(&cashier_mutex);

		return NULL;
}

int main(int argc, char *argv[]) {
		if (argc < 7) {
				fprintf(stderr, "Usage: %s <log_filename> <queue_per_customer> <shopping_time_min> <shopping_time_max> <customer_wait_min> <customer_wait_max>\n", argv[0]);
				exit(EXIT_FAILURE);
		}

		// Initialize log file
		init_log_file(argv[1]);

		// Read configuration values from command-line arguments
		CustomerConfig config;
		config.queue_per_customer = atoi(argv[2]);
		config.shopping_time_min = atoi(argv[3]);
		config.shopping_time_max = atoi(argv[4]);
		config.customer_wait_min = atoi(argv[5]);
		config.customer_wait_max = atoi(argv[6]);

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
				if (pthread_create(&customer_thread_id, NULL, customer_thread, &config) != 0) {
						perror("pthread_create failed");
						exit(EXIT_FAILURE);
				}
				pthread_detach(customer_thread_id); // Detach the thread to allow it to run independently
				sleep(rand() % (config.customer_wait_max - config.customer_wait_min) + config.customer_wait_min); // Customers enter at random intervals in specified range (default 5s-20s)
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
		if (sem_close(customer_signal) != 0) {
				perror("sem_close failed");
		}

		// Unmap shared memory
		if (munmap(customers_in_store, sizeof(int)) != 0) {
				perror("munmap customers_in_store failed");
		}
		if (munmap(store_open, sizeof(int)) != 0) {
				perror("munmap store_open failed");
		}
		if (munmap(current_cashiers, sizeof(int)) != 0) {
				perror("munmap current_cashiers failed");
		}

		return 0;
}