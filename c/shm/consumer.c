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

    void* mapped = mmap(NULL, BUF_SIZE, PROT_READ, MAP_SHARED, fd, 0);

    if (NULL == mapped || MAP_FAILED == mapped)
    {
        perror(NULL);
        return -1;
    }

    close(fd);

	while(! stop) {
		printf("%s\t%s\n", "got new string", (char*) mapped);
        usleep((int) 6E5);
	}

    munmap(mapped, BUF_SIZE);

	return (EXIT_SUCCESS);
}
