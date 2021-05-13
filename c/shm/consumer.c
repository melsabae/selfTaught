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
const int OFLAG = O_RDONLY;
const mode_t MODE = 0666;
const int BUF_SIZE = 64;
const int BUF_MAX = BUF_SIZE - 1;
bool stop = false;

void signal_handler(int signal) {
	stop = true;
	puts("received SIGINT, terminating");
}

int main(int argc, char** argv) {
    signal(SIGINT, signal_handler);

	int fd = shm_open(SHM_NAME, OFLAG, MODE);
	uint8_t garbage[BUF_SIZE];
	garbage[BUF_MAX] = 0;



    if (0 >= fd)
    {
        perror(NULL);
        return -2;
    }

	while(! stop) {
        read(fd, garbage, BUF_SIZE);
		printf("%s\t%s\n", "got new string", (char*) garbage);
        usleep((int) 6E5);
	}

    close(fd);

	return (EXIT_SUCCESS);
}
