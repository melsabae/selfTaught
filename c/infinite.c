#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

size_t counter = 0;

void exit_handler(void);
int main(int, char**);
void signal_handler(int);

void signal_handler(int signal)
{
	switch(signal)
	{
		case SIGHUP:
			atexit(exit_handler);
			break;

		default:
			break;
	}
}

void exit_handler(void)
{
	main(counter, NULL);
}

int main(int argc, char** argv)
{
	signal(SIGHUP, signal_handler);
	signal(SIGSEGV, signal_handler);
	counter = argc;

	// this program runs for a while then segfaults
	// the only thing it's doing is handling the HUP signal, then restarting
	// so why does it segfault?

	printf("argc: %d\n", argc);
	counter ++;
	pause();

	exit (EXIT_FAILURE);
}
