#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>
#include <unistd.h>

typedef struct{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	int helper;
} b_sem_t;

#define MAGIC_NUMBER 512

pthread_t threads[MAGIC_NUMBER];
pthread_t posters[MAGIC_NUMBER];
b_sem_t bsems[MAGIC_NUMBER];


void b_sem_create(b_sem_t* bsem)
{
	pthread_mutex_init(&bsem->mutex, NULL);
	pthread_cond_init(&bsem->cond, NULL);
	bsem->helper = 0;
}

void b_sem_post(b_sem_t* const bsem)
{
	assert(bsem->helper <= 1);
	pthread_mutex_lock(&bsem->mutex);

	assert(bsem->helper <= 1);
	if(bsem->helper == 0)
	{
		assert(bsem->helper <= 1);
		bsem->helper = 1;
		assert(bsem->helper <= 1);
		pthread_cond_signal(&bsem->cond);
	}

	assert(bsem->helper <= 1);
	pthread_mutex_unlock(&bsem->mutex);
	assert(bsem->helper <= 1);
}

void b_sem_wait(b_sem_t* const bsem)
{
	assert(bsem->helper <= 1);
	pthread_mutex_lock(&bsem->mutex);

	assert(bsem->helper <= 1);
	while(0 == bsem->helper)
	{
		assert(bsem->helper <= 1);
		pthread_cond_wait(&bsem->cond, &bsem->mutex);
	}

	assert(bsem->helper <= 1);
	bsem->helper = 0;

	assert(bsem->helper <= 0);
	pthread_mutex_unlock(&bsem->mutex);
	assert(bsem->helper <= 1);
}

void* routine(void* arg)
{
	int thread_no = 0;

	for(int i = 0; i < MAGIC_NUMBER; i++)
	{
		if(pthread_equal(threads[i], pthread_self()))
		{
			thread_no = i;
			break;
		}
	}

	while(1)
	{
		b_sem_wait(bsems + thread_no);
		printf("%d\n", thread_no);
		usleep(rand() % 1000);
	}
	return NULL;
}

void* poster(void* arg)
{
	int poster_num = 0;
	for(int i = 0; i < MAGIC_NUMBER; i++)
	{
		if(pthread_equal(posters[i], pthread_self()))
		{
			poster_num = i;
			break;
		}
	}

	while(1)
	{
		b_sem_post(bsems + poster_num);
	}
}

int main()
{
	srand(time(NULL));

	for(int i = 0; i < MAGIC_NUMBER; i++)
	{
		pthread_create(posters + i, NULL, poster, NULL);
		b_sem_create(bsems + i);
		pthread_create(threads + i, NULL, routine, NULL);
	}

	int random = 0;

	while(1)
	{
		random = rand() % MAGIC_NUMBER;
		b_sem_post(bsems + random);

		usleep( rand() % 5 );
	}

	exit (EXIT_SUCCESS);
}
