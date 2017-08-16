#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <mqueue.h>
#include <string.h>
#include <errno.h>
#include <stddef.h>
#include <assert.h>
#include <inttypes.h>

#define THREAD_POOL_NAME "/thread_pool_test"
#define NUM_THREADS 128

typedef struct
{
	ptrdiff_t thread_num;
	ssize_t len_payload;
	void *payload;
} thread_util;

bool keep_running = true;
int caught_signal = 0;
pthread_t thread_pool[NUM_THREADS];

void signal_handler (int signal)
{
	keep_running = false;
	caught_signal = signal;
}

void cleanup_thread_util (void *arg)
{
	if (NULL == arg)
	{
		return;
	}

	thread_util *util = arg;

	if (NULL != util->payload)
	{
		uint8_t *payload = util->payload;

		printf ("%ld %s: ", util->thread_num, "payload");
		for (ssize_t i = 0; i < util->len_payload; i++)
		{
			printf ("%.2X", payload[i]);
		}
		puts ("");

		free (util->payload);
	}

	free (util);
}

void *loop (void *arg)
{
	if (NULL == arg)
	{
		//pthread_exit(NULL);
	}

	int ret_val = 0;
	thread_util* util = NULL;
	struct mq_attr attr;
	mqd_t prio_queue;

	memset (&attr, 0, sizeof (attr));
	memset (&prio_queue, 0, sizeof(prio_queue));

	ret_val = pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED, NULL);
	if (0 != ret_val)
	{
		fprintf(stderr, "%s%s\n", "setcanceltype: ", strerror(errno));
		pthread_exit (NULL);
	}

	{
		sigset_t set;
		sigfillset(&set);
		ret_val = pthread_sigmask(SIG_BLOCK, &set, NULL);
		if(0 != ret_val)
		{
			fprintf(stderr, "%s\n", "pthread_sigmask failure");
			pthread_exit (NULL);
		}
	}

	ret_val = prio_queue = mq_open (THREAD_POOL_NAME, O_RDONLY);
	if (((mqd_t) - 1) == prio_queue)
	{
		fprintf(stderr, "%s%s\n", "mq_open (thread): ", strerror(errno));
		exit (EXIT_FAILURE);
	}

	ret_val = mq_getattr (prio_queue, &attr);
	if (0 != ret_val)
	{
		fprintf(stderr, "%s%s\n", "mq_getattr: ", strerror(errno));
		pthread_exit (NULL);
	}

	util = calloc (1, sizeof (thread_util));
	if(NULL == util)
	{
		fprintf(stderr, "%s%s\n", "calloc: ", strerror(errno));
		pthread_exit(NULL);
	}

	pthread_cleanup_push(cleanup_thread_util, util);

	util->payload = calloc (1, attr.mq_msgsize);
	if (NULL == util->payload)
	{
		fprintf(stderr, "%s%s\n", "calloc: ", strerror(errno));
		pthread_exit (NULL);
	}

	for (size_t i = 0; i < NUM_THREADS; i++)
	{
		if (0 != pthread_equal (pthread_self (), thread_pool[i]))
		{
			util->thread_num = i;
			break;
		}
	}

	char *message = util->payload;

	while (true)
	{
		ret_val = pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
		if (0 != ret_val)
		{
			fprintf(stderr, "%s%s\n", "setcancelstate (enable): ", strerror(errno));
			pthread_exit (NULL);
		}

		pthread_testcancel();
		util->len_payload = mq_receive (prio_queue, message, attr.mq_msgsize, NULL);

		ret_val = pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, NULL);
		if (0 != ret_val)
		{
			fprintf(stderr, "%s%s\n", "setcancelstate (disable): ", strerror(errno));
			pthread_exit (NULL);
		}

		if(-1 == util->len_payload)
		{
			fprintf(stderr, "%s%s\n", "mq_receive: ", strerror(errno));
			pthread_exit (NULL);
		}

		/*
		 * generic queue processing
		 */
		if (0 < util->len_payload)
		{
			message[util->len_payload] = '\0';
			printf ("loop %ld: %s\n", util->thread_num, message);

			ret_val = usleep (rand () % 100);
			if(0 != ret_val)
			{
				fprintf(stderr, "%s%s\n", "usleep: ", strerror(errno));
				pthread_exit (NULL);
			}
		}
	}

	pthread_cleanup_pop (0);
	return NULL;
}

int main ()
{
	int ret_val = 0;
	size_t i = 0;
	struct mq_attr attr;
	mqd_t prio_queue;

	memset (&prio_queue, 0, sizeof(prio_queue));
	memset (&attr, 0, sizeof(attr));

	signal(SIGINT, signal_handler);

	/*
	 * number of messages, maximum
	 * maximum for the system is in /proc/sys/fs/mqueue/msg_max
	 */
	attr.mq_maxmsg = 10;

	/*
	 * size of message in bytes, maximum
	 * maximum for the system is in /proc/sys/fs/mqueue/msgsize_max
	 */
	attr.mq_msgsize = 32;

	srand (time (NULL));

	prio_queue = mq_open (THREAD_POOL_NAME, O_CREAT | O_RDWR | O_NONBLOCK,
			0600, &attr);
	if (((mqd_t) - 1) == prio_queue)
	{
		fprintf(stderr, "%s%s\n", "mq_open: ", strerror(errno));
		exit (EXIT_FAILURE);
	}

	for (i = 0; i < NUM_THREADS; i++)
	{
		ret_val = pthread_create (thread_pool + i, NULL, loop, NULL);

		if (0 != ret_val)
		{
			fprintf(stderr, "%s%s\n", "pthread_create: ", strerror(errno));
			exit (EXIT_FAILURE);
		}
	}

	while (keep_running)
	{
		// just messing about
		//ret_val = pause();

		//if(0 != ret_val)
		//{
		//      if(errno != EINTR)
		//      {
		//              perror("pause: ");
		//      }
		//}

		// mq is in nonblocking mode, main will spin its wheels a bunch""
		ret_val = mq_send (prio_queue, "ahoy matey", strlen ("ahoy matey"), 1);
		if(0 != ret_val)
		{
			//fprintf(stderr, "%s%s\n", "mq_send: ", strerror(errno));
		}

		usleep (rand () % 5000);
	}

	for (i = 0; i < NUM_THREADS; i++)
	{
		ret_val = pthread_cancel (thread_pool[i]);

		if (0 != ret_val)
		{
			fprintf(stderr, "%s%s\n", "pthread_cancel: ", strerror(errno));
			exit (EXIT_FAILURE);
		}

		ret_val = pthread_join (thread_pool[i], NULL);

		if (0 != ret_val)
		{
			fprintf(stderr, "%s%s\n", "pthread_join: ", strerror(errno));
			exit (EXIT_FAILURE);
		}
	}

	// TODO: process all remaining messages in the queue
	{
		ssize_t len = 0;
		char *leftovers = calloc (1, attr.mq_msgsize);

		if (NULL == leftovers)
		{
			fprintf(stderr, "%s%s\n", "calloc: ", strerror(errno));
			exit (EXIT_FAILURE);
		}

		while (0 != len)
		{
			len = mq_receive (prio_queue, leftovers, attr.mq_msgsize, NULL);

			//service the remaining messages
		}

		free(leftovers);
	}

	ret_val = mq_close (prio_queue);
	if (0 != ret_val)
	{
		fprintf(stderr, "%s%s\n", "mq_close: ", strerror(errno));
		exit (EXIT_FAILURE);
	}

	ret_val = mq_unlink (THREAD_POOL_NAME);
	if (0 != ret_val)
	{
		fprintf(stderr, "%s%s\n", "mq_unlink: ", strerror(errno));
		exit (EXIT_FAILURE);
	}

	printf ("%s %s %d: %s\n",
			__FUNCTION__,
			"ended by signal:", caught_signal, strsignal (caught_signal));

	return 0;
}

