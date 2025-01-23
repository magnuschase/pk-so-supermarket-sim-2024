#include "supermarket.h"
#include "ansi-color-codes.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <regex.h>

int *current_cashiers;
int *customers_in_store;
int *store_open;
pthread_mutex_t cashier_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cashier_cond = PTHREAD_COND_INITIALIZER;
sem_t *customer_signal;
FILE *log_file = NULL;
CashierQueue cashier_queues[MAX_CASHIERS];

// Print simulator header
void print_header() {
		printf(CLEAR_CONSOLE);
		printf(BRED "\nSUPERMARKET\t\t\t\t\tSIMULATOR\t" reset "\n");
		printf(BRED "---------------------------------------------------------" reset "\n\n");
}

// Helper function to remove ANSI escape codes from a string
void remove_ansi_escape_codes(char *dest, const char *src) {
		const char *ansi_escape_code_pattern = "\033\\[[0-9;]*[mK]";
		regex_t regex;
		regcomp(&regex, ansi_escape_code_pattern, REG_EXTENDED);

		regmatch_t match;
		const char *p = src;
		char *d = dest;

		while (regexec(&regex, p, 1, &match, 0) == 0) {
				size_t len = match.rm_so;
				strncpy(d, p, len);
				d += len;
				p += match.rm_eo;
		}
		strcpy(d, p);

		regfree(&regex);
}

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

		// Print to console with ANSI formatting
		printf("[%s] pid:%d > ", time_str, pid);
		vprintf(format, args);
		printf(reset "\n"); // Reset formatting after the message

		// Print to log file without ANSI formatting
		if (log_file) {
				char formatted_message[1024];
				char plain_message[1024];
				vsnprintf(formatted_message, sizeof(formatted_message), format, args);
				remove_ansi_escape_codes(plain_message, formatted_message);

				if (fprintf(log_file, "[%s] pid:%d > %s\n", time_str, pid, plain_message) < 0) {
						perror("Failed to write to log file");
				}
				if (fflush(log_file) != 0) {
						perror("Failed to flush log file");
				}
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
				if (fclose(log_file) != 0) {
						perror("Failed to close log file");
				}
		}
}