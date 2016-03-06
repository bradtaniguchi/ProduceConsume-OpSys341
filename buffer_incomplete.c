/**
 * Producer Consumer (page 253)
 * using counting semaphores as well as a mutex lock.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define TRUE 1
#define BUFFER_SIZE 5
#define MAX_SLEEP 5

#define MIN 0  //minimum value of an element in buffer
#define MAX 1000 //maximum value of an element in buffer

int buffer[BUFFER_SIZE];

pthread_mutex_t mutex;
sem_t empty;
sem_t full;

int insertPointer = 0, removePointer = 0;

void *producer(void *param);
void *consumer(void *param);

int myRand() {
   return rand() % (MAX - MIN + 1) + MIN;
}

int print_buffer(){
	int i;
	for (i=0; i< BUFFER_SIZE; i++)
		printf("slot %d: %d\n", i, buffer[i]);
	printf("\n");	
	return 0;
}

int init_buffer(){
	int i;
	for (i=0; i< BUFFER_SIZE; i++)
		buffer[i] = -1;
	return 0;
}

int insert_item(int item)
{
}

int remove_item()
{
}

int main(int argc, char *argv[])
{
	int sleepTime, producerThreads, consumerThreads;
	int i, j;

	if(argc != 4)
	{
		fprintf(stderr, "Useage: <sleep time> <producer threads> <consumer threads>\n");
		return -1;
	}

	sleepTime = atoi(argv[1]);
	producerThreads = atoi(argv[2]);
	consumerThreads = atoi(argv[3]);

	/* Initialize buffer to be -1 */
	init_buffer();

	/* Initialize the synchronization tools */
	printf("%d\n",pthread_mutex_init(&mutex, NULL));
	printf("%d\n",sem_init(&empty, 0, BUFFER_SIZE));
	printf("%d\n",sem_init(&full, 0, 0));
	srand(time(0));

	/* Create the producer and consumer threads */
	for(i = 0; i < producerThreads; i++)
	{
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, producer, NULL);
	}

	for(j = 0; j < consumerThreads; j++)
	{
		pthread_t tid;
		pthread_attr_t attr;
		pthread_attr_init(&attr);
		pthread_create(&tid, &attr, consumer, NULL);
	}

	/* Sleep for user specified time */
	sleep(sleepTime);
	return 0;
}


void *producer(void *param)
{
	int random;
	int r;

	int current_time=0;
	while(TRUE)
	{
		r = rand() % MAX_SLEEP;
		sleep(r);
		random = myRand();
		current_time+=r;

		printf("Producer tries to insert %d at time %d\n", random, current_time); 
		if(insert_item(random))
			fprintf(stderr, "Error");

	}

}

void *consumer(void *param)
{
	int r;
	int current_time=0;

	while(TRUE)
	{
		r = rand() % MAX_SLEEP;
		sleep(r);
		current_time+=r;
		
		printf("Consumer tries to consume at time %d\n", current_time, random); 

		if(remove_item())
			fprintf(stderr, "Error Consuming");
	}
}
