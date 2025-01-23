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

// Cash register management functions
void open_cashier() {
		if (*current_cashiers < MAX_CASHIERS) {
				(*current_cashiers)++;
				log_message(WHTHB BBLK " Opened a new cash register. Available cash registers: %d " reset, *current_cashiers);
		}
}

void close_cashier(int cashier_index) {
		if (*current_cashiers > MIN_CASHIERS) {
				// Wait for the cashier to serve all queued customers
				while (cashier_queues[cashier_index].customers > 0) {
						pthread_cond_wait(&cashier_queues[cashier_index].cond, &cashier_mutex);
				}
				(*current_cashiers)--;
				log_message(BLKHB BWHT " Closed a cash register. Available cash registers: %d " reset, *current_cashiers);
		}
}

int main(int argc, char *argv[]) {
		// Logfile name must be provided as an argument
		if (argc < 2) {
				fprintf(stderr, "Usage: %s <log_filename>\n", argv[0]);
				exit(EXIT_FAILURE);
		}

		// Initialize log file
		init_log_file(argv[1]);

		// Open named semaphore to communicate with customer process
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

		// Initialize cashier queues
		for (int i = 0; i < MAX_CASHIERS; i++) {
				cashier_queues[i].customers = 0;
				pthread_cond_init(&cashier_queues[i].cond, NULL);
		}

		while (1) {
				// Check if the store is open
				pthread_mutex_lock(&cashier_mutex);
				if (!*store_open) {
						pthread_mutex_unlock(&cashier_mutex);
						break;
				}
				pthread_mutex_unlock(&cashier_mutex);

				// Wait for customer signal
				if (sem_wait(customer_signal) == -1) {
						perror("sem_wait failed");
						continue;
				}

				pthread_mutex_lock(&cashier_mutex);
				// At least N * K cash registers should be open
				// They should be closed when there are less customers present than K * (N-1)
				if (*customers_in_store > K * *current_cashiers) {
						open_cashier();
				} else if (*customers_in_store < K * (*current_cashiers - 1)) {
						close_cashier(*current_cashiers - 1);
				}
				pthread_mutex_unlock(&cashier_mutex);
		}

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