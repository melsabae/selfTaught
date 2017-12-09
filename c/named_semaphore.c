#include <stdio.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>

const char SEM_NAME[] = "/my_named_semaphore";

int main(void)
{
	int value = 0;
	sem_t* semaphore = sem_open(SEM_NAME, O_CREAT, 0600, 1);


	sem_getvalue(semaphore, &value);
	printf("%d\n", value);
	sem_wait(semaphore);
	sem_getvalue(semaphore, &value);
	printf("%d\n", value);
	sem_post(semaphore);
	sem_getvalue(semaphore, &value);
	printf("%d\n", value);

	sem_close(semaphore);
	sem_unlink(SEM_NAME);
	return (0);
}
