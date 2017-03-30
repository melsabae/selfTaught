#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int caught_signal = 0;

void main(int, void**);

void signal_handler(int signal)
{
	switch(signal)
	{
		case SIGHUP:
			while(0 != on_exit(main, NULL))
			{
				puts("registering");
			}
			break;

		default:
			caught_signal = signal;
			break;
	}
}

void  main(int argc, void** argv)
{
	printf("argc: %d\n", argc);
	signal(SIGHUP, signal_handler);
	signal(SIGINT, signal_handler);
	signal(SIGTERM, signal_handler);

	if(0 != caught_signal)
	{
		printf("caught signal: %d\n", signal);
	}

	pause();
}
