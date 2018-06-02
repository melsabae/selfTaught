#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <string.h>


const char *SHM_NAME = "simulation";
const int OFLAG = O_RDWR | O_CREAT | O_EXCL | O_TRUNC;
const mode_t MODE = 0400;
const int BUF_SIZE = 64;
const int BUF_MAX = BUF_SIZE - 1;

volatile bool stop = false;

void signal_handler(int signal) {
	stop = true;
	puts("received SIGINT, terminating");
}


int main(int argc, char** argv) {
	srand(time(NULL));

	signal(SIGINT, signal_handler);

	int fd = shm_open(SHM_NAME, OFLAG, MODE);
	uint8_t garbage[BUF_SIZE];
	garbage[BUF_MAX] = 0;


	while(! stop) {
		for(size_t i = 0; i < BUF_MAX; i ++) {
			garbage[i] = (rand() % (122 - 97)) + 97;
		}

		printf("%s\t%s\n", "writing new string", (char*) garbage);
		write(fd, garbage, BUF_SIZE);
		usleep(rand() % ((int) 5E6));

		if(0 == (rand() % 4)) {
			puts("truncating");
			ftruncate(fd, 0);
		}
	}

	(void) close(fd);
	(void) shm_unlink(SHM_NAME);
	return (EXIT_SUCCESS);
}
