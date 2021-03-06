/**
 * Producer Consumer (page 253)
 * using counting semaphores as well as a mutex lock.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <time.h>

#define TRUE 1
#define BUFFER_SIZE 5
#define MAX_SLEEP 5

#define MIN 0  //minimum value of an element in buffer
#define MAX 1000 //maximum value of an element in buffer

int buffer[BUFFER_SIZE];

pthread_mutex_t mutex; 
sem_t empty; 
sem_t full;

time_t my_time;

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
    /* Wait for there to be at least one empty spot */
    sem_wait(&empty);

    /* Lock the mutex */
    pthread_mutex_lock(&mutex);

    /* CRITICAL SECTION */
    buffer[insertPointer] = item; 
    my_time = time(NULL);
    printf("Producer %lu produced %d at time %s\n", pthread_self(), \
        buffer[insertPointer], ctime(&my_time));
    insertPointer = (insertPointer+1) % BUFFER_SIZE; 
    
    /* Print the buffer */
    print_buffer();

    /* Unlock the mutex */
    pthread_mutex_unlock(&mutex);

    /* Post to full semaphore */
    sem_post(&full);
    return 0; //false
}

int remove_item()
{
    /* Wait for there to be at least one empty spot */
    sem_wait(&full);

    /* Lock the mutex */
    pthread_mutex_lock(&mutex);

    /* CRITICAL SECTION */
    my_time = time(NULL);
    printf("Consumer %lu consumed %d at time %s\n", pthread_self(), \
        buffer[removePointer], ctime(&my_time));
    buffer[removePointer] = -1; 
    removePointer = (removePointer+1) % BUFFER_SIZE; 

    /* Print the buffer */
    print_buffer();
    
    /* Unlock the mutex */
    pthread_mutex_unlock(&mutex);
    
    /* Post to empty semaphore */
    sem_post(&empty);

    return 0; //false
}

int main(int argc, char *argv[])
{
	int sleepTime, producerThreads, consumerThreads;
	int i, j;
    my_time = time(NULL);

	if(argc != 4)
	{
		fprintf(stderr, "Useage: <sleep time> <producer threads> \
                <consumer threads>\n");
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
  
        my_time = time(NULL);

		printf("Producer %lu tries to insert %d at time %s\n", \
            pthread_self(), random, ctime(&my_time)); 
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
	
        my_time = time(NULL);

		printf("Consumer %lu tries to consume at time %s\n", pthread_self(), \
             ctime(&my_time)); 
		if(remove_item())
			fprintf(stderr, "Error Consuming");
	}
}
