#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


#define FILE_SIZE (255)
const int file_flags = O_RDWR | O_CREAT | O_EXCL;
const mode_t file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

struct
{
    bool signaled;
    sigset_t signals;
    struct sigaction signal_action;
    void* buffer;
    char file_name[FILE_SIZE];
    int fd;
}
program_state;


void at_exit(void)
{
    if (0 != munmap(program_state.buffer, FILE_SIZE))
    {
        fprintf(stderr, "failed to munmap\n");
    }

    if (0 != close(program_state.fd))
    {
        fprintf(stderr, "failed to close file\n");
    }

    if (0 != unlink(program_state.file_name))
    {
        fprintf(stderr, "failed to unlink file\n");
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

    snprintf(program_state.file_name, FILE_SIZE, "%s", "/tmp/producerXXXXXX");

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
    program_state.fd = mkostemp(program_state.file_name, 6, file_flags);

    if (0 > program_state.fd)
    {
        fprintf(stderr, "failed to open file\n");
        return -__LINE__;
    }

    // resize the file path for the expected size of the input data
    if (0 != ftruncate(program_state.fd, FILE_SIZE))
    {
        fprintf(stderr, "failed to ftruncate file\n");
        return -__LINE__;
    }

    // create a virtual mapping so the file contents can be dealt with as a pointer
    program_state.buffer = mmap(NULL, FILE_SIZE, PROT_WRITE, MAP_SHARED, program_state.fd, 0);

    if (NULL == program_state.buffer)
    {
        fprintf(stderr, "failed to mmap file\n");
        return -__LINE__;
    }

    size_t i = 0;
    while(false == program_state.signaled)
    {
        snprintf(program_state.buffer, FILE_SIZE, "%s %d", "ahoy matey!", i);
        ++ i;
        usleep(1E3);

        // TODO: this is where you would send the filename to the consumer so that it can do a work
    }

    return 0;
}

