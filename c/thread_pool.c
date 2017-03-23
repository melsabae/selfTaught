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
#define NUM_THREADS 8

bool keep_running = true;
int caught_signal = 0;
mqd_t prio_queue;

pthread_t thread_pool[NUM_THREADS];

typedef struct
{
  ptrdiff_t thread_num;
  ssize_t len_payload;
  void *payload;
} thread_util;

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
}

void *loop (void *arg)
{
  if (NULL == arg)
  {
    //pthread_exit(NULL);
  }

  int ret_val = 0;
  thread_util *util = calloc (1, sizeof (thread_util));
  struct mq_attr attr;

  memset (&attr, 0, sizeof (attr));
  util->thread_num = 0;
  util->payload = NULL;

  ret_val = mq_getattr (prio_queue, &attr);
  if (0 != ret_val)
  {
    perror ("mq_getattr :");
    pthread_exit (NULL);
  }

  util->payload = calloc (1, attr.mq_msgsize);
  if (NULL == util->payload)
  {
    pthread_exit (NULL);
  }

  char *message = util->payload;

  for (size_t i = 0; i < NUM_THREADS; i++)
  {
    if (0 != pthread_equal (pthread_self (), thread_pool[i]))
    {
      util->thread_num = i;
    }
  }

  ret_val = pthread_setcanceltype (PTHREAD_CANCEL_DEFERRED, NULL);
  if (0 != ret_val)
  {
    perror ("setcanceltype: ");
    pthread_exit (NULL);
  }

  while (true)
  {
    pthread_cleanup_push (cleanup_thread_util, util);
    ret_val = pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, NULL);
    if (0 != ret_val)
    {
      perror ("setcancelstate: ");
      pthread_exit (NULL);
    }

    util->len_payload = mq_receive (prio_queue, message, attr.mq_msgsize, NULL);

    ret_val = pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, NULL);
    if (0 != ret_val)
    {
      perror ("setcancelstate: ");
      pthread_exit (NULL);
    }
    pthread_cleanup_pop (0);

    /*
     * generic queue processing
     */
    if (util->len_payload > 0)
    {
      message[util->len_payload] = '\0';
      printf ("loop %ld: %s\n", util->thread_num, message);
      usleep (rand () % 1000000);
    }
  }

  return NULL;
}

int main ()
{
  int ret_val = 0;
  size_t i = 0;
  struct mq_attr attr;

  signal (SIGINT, signal_handler);
  srand (time (NULL));

  memset (&attr, 0, sizeof (attr));

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

  prio_queue = mq_open (THREAD_POOL_NAME, O_CREAT | O_RDWR, 0600, &attr);
  if (((mqd_t) - 1) == prio_queue)
  {
    perror ("open: ");
    exit (EXIT_FAILURE);
  }

  for (i = 0; i < NUM_THREADS; i++)
  {
    ret_val = pthread_create (thread_pool + i, NULL, loop, NULL);

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
    //      if(errno != EINTR)
    //      {
    //              perror("pause: ");
    //      }
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
    char *leftovers = calloc (1, attr.mq_msgsize);

    if (NULL == leftovers)
    {
      perror ("calloc: ");
      exit (EXIT_FAILURE);
    }

    while (0 != len)
    {
      len = mq_receive (prio_queue, leftovers, attr.mq_msgsize, NULL);

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

  printf ("%s %s %d: %s\n",
	  __FUNCTION__,
	  "ended by signal:", caught_signal, strsignal (caught_signal));

  return 0;
}

