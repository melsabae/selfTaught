#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>


const char* const file_name = "test";
const int file_flags = O_RDWR | O_CREAT | O_EXCL;
const mode_t file_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
const char* test_data = "ahoy, matey!";

struct
{
    bool signaled;
    sigset_t signals;
    struct sigaction signal_action;
}
program_state;


void at_exit(void)
{
    if (0 != shm_unlink(file_name))
    {
        fprintf(stderr, "failed to unlink shm file\n");
    }
}


void catch_stop(int signal)
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
    program_state.signal_action.sa_handler = catch_stop;
    program_state.signal_action.sa_mask = program_state.signals;
    program_state.signal_action.sa_flags = 0;

    if (0 != sigaction(SIGINT, &program_state.signal_action, NULL))
    {
        fprintf(stderr, "failed to sigaction\n");
        return -__LINE__;
    }

    const int fd = shm_open(file_name, file_flags, file_mode);

    if (0 > fd)
    {
        fprintf(stderr, "failed to open shm file\n");
        return -__LINE__;
    }

    if (0 != ftruncate(fd, strlen(test_data) + 1))
    {
        fprintf(stderr, "failed to ftruncate shm file\n");
        return -__LINE__;
    }

    if (strlen(test_data) != write(fd, test_data, strlen(test_data)))
    {
        fprintf(stderr, "failed to write to shm file\n");
        return -__LINE__;
    }

    while(false == program_state.signaled)
    {
        //fprintf(stderr, "pause returned %d\n", pause());
        sigsuspend(NULL);
    }

    return 0;
}

