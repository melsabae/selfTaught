#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


const size_t file_size = 255;
const char* const file_name = "test";
const int file_flags = O_RDWR | O_CREAT | O_EXCL;
const mode_t file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

struct
{
    bool signaled;
    sigset_t signals;
    struct sigaction signal_action;
    void* buffer;
}
program_state;


void at_exit(void)
{
    if (0 != munmap(program_state.buffer, file_size))
    {
        fprintf(stderr, "failed to munmap\n");
    }

    if (0 != shm_unlink(file_name))
    {
        fprintf(stderr, "failed to unlink shm file\n");
    }
}


void signal_handler(int signal)
{
    program_state.signaled = true;
    (void) signal;
}


int main(int argc, char** argv)
{
    if (0 != atexit(at_exit))
    {
        fprintf(stderr, "failed to install exit handler\n");
        return -__LINE__;
    }

    if (0 != sigemptyset(&program_state.signals))
    {
        fprintf(stderr, "failed to do a signal thing\n");
        return -__LINE__;
    }

    program_state.signaled = false;
    program_state.signal_action.sa_handler = signal_handler;
    program_state.signal_action.sa_mask = program_state.signals;
    program_state.signal_action.sa_flags = 0;

    if (0 != sigaction(SIGINT, &program_state.signal_action, NULL))
    {
        fprintf(stderr, "failed to sigaction\n");
        return -__LINE__;
    }

    // create a file path to share memory with
    const int fd = shm_open(file_name, file_flags, file_mode);

    if (0 > fd)
    {
        fprintf(stderr, "failed to open shm file\n");
        return -__LINE__;
    }

    // resize the file path for the expected size of the input data
    if (0 != ftruncate(fd, file_size))
    {
        fprintf(stderr, "failed to ftruncate file\n");
        return -__LINE__;
    }

    // create a virtual mapping so the file contents can be dealt with as a pointer
    program_state.buffer = mmap(NULL, file_size, PROT_WRITE, MAP_SHARED, fd, 0);

    if (NULL == program_state.buffer)
    {
        fprintf(stderr, "failed to mmap file\n");
        return -__LINE__;
    }

    size_t i = 0;
    while(false == program_state.signaled)
    {
        snprintf(program_state.buffer, file_size, "%s %d", "ahoy matey!", i);
        ++ i;
        usleep(1E3);
    }

    return 0;
}

