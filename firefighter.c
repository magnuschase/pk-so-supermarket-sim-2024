#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

/*

Systemy operacyjne - projekt 2024/2025 - Supermarket (temat 10)
Imię i nazwisko: Jakub Kapała
Numer albumu: 151885
Kierunek: Informatyka, niestacjonarne

*/ 

// Inititate a fire alarm, that triggers store to be closed.
// Customers should exit the store and cashiers should immediately stop serving customers.
// The fire alarm should be sent to the supermarket process via a socket connection.
void fire_alarm() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char *message = "Fire alarm!";

    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        log_message("Socket creation error");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        log_message("Invalid address/ Address not supported");
        return;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        log_message("Connection Failed");
        return;
    }

    // Send the message
    send(sock, message, strlen(message), 0);
    log_message("Fire alarm sent");

    close(sock);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <log_filename> <fire_wait_min> <fire_wait_max>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Initialize log file
    init_log_file(argv[1]);

		// Read configuration values from command-line arguments
    int fire_wait_min = atoi(argv[2]);
    int fire_wait_max = atoi(argv[3]);

    // Simulate fire alarm after some time - default: minimum 5 minutes, maximum 20 minutes
		sleep(rand() % ((fire_wait_max - fire_wait_min) * 60) + (fire_wait_min * 60));
    fire_alarm();

    // Close log file
    close_log_file();

    return 0;
}