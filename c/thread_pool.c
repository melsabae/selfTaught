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

#define THREAD_POOL_NAME "/thread_pool_test"
#define NUM_THREADS 8

bool keep_running = true;
int caught_signal = 0;
mqd_t prio_queue;

pthread_t thread_pool[NUM_THREADS];
int thread_args[NUM_THREADS] = { 0 };
int thread_posi[NUM_THREADS] = { 0 };

void signal_handler (int signal)
{
  keep_running = false;
  caught_signal = signal;
}

void cleanup (void *arg)
{
  const int thread_num = *(int *) (arg);

  printf ("cleanup thread: %d at %d\n", thread_num, thread_posi[thread_num]);
}

void *loop (void *arg)
{
  if (NULL == arg)
  {
    pthread_exit (NULL);
  }

  const int thread_num = *(int *) (arg);
  char message[8192] = { 0 };
  ssize_t len = 0;
  int ret_val = 0;

  ret_val = pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
  if (0 != ret_val)
  {
    perror ("setcancelstate: ");
    pthread_exit (NULL);
  }

  ret_val = pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED, NULL);
  if (0 != ret_val)
  {
    perror ("setcanceltype: ");
    pthread_exit (NULL);
  }

  pthread_cleanup_push (cleanup, arg);

  while (true)
  {
    thread_posi[thread_num] = 1;
    len = mq_receive (prio_queue, message, 8192, NULL);
    thread_posi[thread_num] = 2;

    if (len > 0)
    {
      thread_posi[thread_num] = 3;
      message[len] = '\0';

      thread_posi[thread_num] = 4;
      printf ("loop %d: %s\n", thread_num, message);

      thread_posi[thread_num] = 5;
      usleep (rand () % 1000000);
    }

    thread_posi[thread_num] = 6;
  }

  thread_posi[thread_num] = 7;
  pthread_cleanup_pop (0);

  thread_posi[thread_num] = 8;
  return NULL;
}

int main ()
{
  int ret_val = 0;
  size_t i = 0;

  signal (SIGINT, signal_handler);
  srand (time (NULL));

  prio_queue = mq_open (THREAD_POOL_NAME, O_CREAT | O_RDWR, 0600, NULL);
  if (((mqd_t) - 1) == prio_queue)
  {
    perror ("open: ");
    exit (EXIT_FAILURE);
  }

  for (i = 0; i < NUM_THREADS; i++)
  {
    thread_args[i] = i;
    ret_val = pthread_create (thread_pool + i, NULL, loop, thread_args + i);

    if (0 != ret_val)
    {
      perror ("create: ");
      exit (EXIT_FAILURE);
    }
  }

  while (keep_running)
  {
		// just messing about
		//ret_val = pause();

		//if(0 != ret_val)
		//{
		//	if(errno != EINTR)
		//	{
		//		perror("pause: ");
		//	}
		//}

    ret_val = mq_send (prio_queue, "ahoy matey", strlen ("ahoy matey"), 1);
    if (0 != ret_val)
    {
      perror ("mq_send: ");
      exit (EXIT_FAILURE);
    }

    usleep (rand () % 20000);
  }

  for (i = 0; i < NUM_THREADS; i++)
  {
    ret_val = pthread_cancel (thread_pool[i]);

    if (0 != ret_val)
    {
      perror ("cancel: ");
      exit (EXIT_FAILURE);
    }

    ret_val = pthread_join (thread_pool[i], NULL);

    if (0 != ret_val)
    {
      perror ("create: ");
      exit (EXIT_FAILURE);
    }
  }

  // TODO: process all remaining messages in the queue
  {
    ssize_t len = 0;
    char leftovers[8192] = { 0 };

    while (0 != len)
    {
      len = mq_receive (prio_queue, leftovers, 8192, NULL);

      //service the remaining messages
    }
  }

  ret_val = mq_close (prio_queue);
  if (0 != ret_val)
  {
    perror ("mq_close: ");
    exit (EXIT_FAILURE);
  }

  ret_val = mq_unlink (THREAD_POOL_NAME);
  if (0 != ret_val)
  {
    perror ("unlink: ");
    exit (EXIT_FAILURE);
  }

  for (i = 0; i < NUM_THREADS; i++)
  {
    printf ("thread %lu ended at %d\n", i, thread_posi[i]);
  }

  printf ("%s %s %d: %s\n",
	  __FUNCTION__,
	  "ended by signal:", caught_signal, strsignal (caught_signal));

  return 0;
}
