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
const mode_t MODE = 0400;
const int BUF_SIZE = 64;
const int BUF_MAX = BUF_SIZE - 1;

int main(int argc, char** argv) {
	int fd = shm_open(SHM_NAME, OFLAG, MODE);
	uint8_t garbage[BUF_SIZE];
	garbage[BUF_MAX] = 0;

	while(true) {
		read(fd, garbage, BUF_SIZE);
		printf("%s\t%s\n", "got new string", (char*) garbage);
	}

	(void) munmap(NULL, BUF_SIZE);
	return (EXIT_SUCCESS);
}
