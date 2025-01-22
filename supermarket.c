#include "supermarket.h"
#include "ansi-color-codes.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>

/*

Systemy operacyjne - projekt 2024/2025 - Supermarket (temat 10)
Imię i nazwisko: Jakub Kapała
Numer albumu: 151885
Kierunek: Informatyka, niestacjonarne

*/


// Sockets are used to communicate with the firefighter process
// when a fire alarm is triggered
void *socket_server(void *arg) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Attach socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    // Read the message from the firefighter process
    read(new_socket, buffer, 1024);
		sleep(1);
    log_message("Fire alarm received: %s", buffer);

    // Signal store closure
    pthread_mutex_lock(&cashier_mutex);
    *store_open = 0;
    pthread_cond_broadcast(&cashier_cond);
    pthread_mutex_unlock(&cashier_mutex);

    close(new_socket);
    close(server_fd);
    return NULL;
}

// Shared memory is used to store:
// - the number of customers in the store
// - the store status (open/closed)
// - the number of cash registers currently open
int create_shared_memory(const char *name, int size) {
    // Unlink the shared memory object if it already exists
    shm_unlink(name);

    int fd = shm_open(name, O_CREAT | O_RDWR, 0644);
    if (fd == -1) {
        perror("shm_open failed");
        exit(EXIT_FAILURE);
    }
    if (ftruncate(fd, size) == -1) {
        perror("ftruncate failed");
        fprintf(stderr, "Failed to set size of shared memory object %s to %d bytes\n", name, size);
        close(fd);
        shm_unlink(name);
        exit(EXIT_FAILURE);
    }
    return fd;
}

// Print welcome message and start the simulation
void print_welcome_message() {
	int option = 0;
	while (option != 1 && option != 2) {
		printf(CLEAR_CONSOLE);
		printf(BRED "\nSUPERMARKET\t\t\t\t\tSIMULATOR\t" reset "\n");
		printf(BRED "---------------------------------------------------------" reset "\n\n");
		printf(BHCYN CYNHB "\tAuthor: Jakub Kapała | Album no: 151885" reset "\n\n");
		printf(BHMAG MAGHB "\t\tPolitechnika Krakowska" reset "\n\n");

		printf(BBLK "Choose an option:" reset "\n");
		printf(YELHB "[1]" reset BYEL " Start the simulation" reset "\n");
		printf(YELHB "[2]" reset BYEL " Exit" reset "\n");
		printf(BBLK "\nEnter your choice..." reset "\n");

		if (scanf("%d", &option) != 1) {
			// Clear invalid input
			while (getchar() != '\n');
			option = 0;
		}

		if (option != 1 && option != 2) {
			printf(BRED "Invalid option. Please choose a new one." reset "\n");
			sleep(1);
		}
	}

	if (option == 2) {
		exit(EXIT_SUCCESS);
	}

	printf(CLEAR_CONSOLE);
	printf(BRED "\nSUPERMARKET\t\t\t\t\tSIMULATOR\t" reset "\n");
	printf(BRED "---------------------------------------------------------" reset "\n\n");
}

int main() {
    pid_t pid_customer, pid_manager, pid_firefighter;
    pthread_t server_thread;

		print_welcome_message();
		
    // Create logs directory if it doesn't exist
    system("mkdir -p logs");

    // Open log file that will store all messages
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char log_filename[256];
    strftime(log_filename, sizeof(log_filename) - 1, "logs/log_%Y-%m-%d_%H-%M-%S.txt", t);
    init_log_file(log_filename);

		// Open named semaphore - it is used to signal the manager process that a customer has either
		// left or entered the store
    customer_signal = sem_open("/customer_signal", O_CREAT, 0644, 0);
    if (customer_signal == SEM_FAILED) {
        perror("sem_open failed");
        exit(EXIT_FAILURE);
    }

    // Create shared memory for customers_in_store
    int fd = create_shared_memory("/customers_in_store", sizeof(int));
    customers_in_store = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (customers_in_store == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    close(fd);
    *customers_in_store = 0;

    // Create shared memory for store_open
    fd = create_shared_memory("/store_open", sizeof(int));
    store_open = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (store_open == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    close(fd);
    *store_open = 1;

    // Create shared memory for current_cashiers
    fd = create_shared_memory("/current_cashiers", sizeof(int));
    current_cashiers = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (current_cashiers == MAP_FAILED) {
        perror("mmap failed");
        exit(EXIT_FAILURE);
    }
    close(fd);
    *current_cashiers = MIN_CASHIERS;

    // Start the socket server in a separate thread
    pthread_create(&server_thread, NULL, socket_server, NULL);

    // Fork `customer` process - it will manage the customers entering and leaving the store
    if ((pid_customer = fork()) == 0) {
        execl("./build/customer", "customer", log_filename, NULL);
        perror("execl failed");
        exit(1);
    }

    // Fork `manager` process - it will manage the cashiers and the store status
    if ((pid_manager = fork()) == 0) {
        execl("./build/manager", "manager", log_filename, NULL);
        perror("execl failed");
        exit(1);
    }

    // Fork firefighter process - it will handle fire alarms
    if ((pid_firefighter = fork()) == 0) {
        execl("./build/firefighter", "firefighter", log_filename, NULL);
        perror("execl failed");
        exit(1);
    }

    // Wait for the firefighter process to signal closure
    waitpid(pid_firefighter, NULL, 0);

    // Signal store closure
    pthread_mutex_lock(&cashier_mutex);
    *store_open = 0;
    pthread_cond_broadcast(&cashier_cond);
    pthread_mutex_unlock(&cashier_mutex);

    // Terminate all child processes
    kill(pid_customer, SIGTERM);
    kill(pid_manager, SIGTERM);

    // Wait for all child processes to finish
    waitpid(pid_customer, NULL, 0);
    waitpid(pid_manager, NULL, 0);

    // Wait for the server thread to finish
    pthread_join(server_thread, NULL);

    // Close log file
    close_log_file();

    // Close named semaphore
    sem_close(customer_signal);
    sem_unlink("/customer_signal");

    // Unmap shared memory
    munmap(customers_in_store, sizeof(int));
    munmap(store_open, sizeof(int));
    munmap(current_cashiers, sizeof(int));
    shm_unlink("/customers_in_store");
    shm_unlink("/store_open");
    shm_unlink("/current_cashiers");

    return 0;
}