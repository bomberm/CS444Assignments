#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>
#include "functions.h"

#define QUEUE_SIZE 32
#define DEBUG_MODE 1

struct buf_object{
  int payload;
  int delay;
};

/*
 * For the purposes of this assignment, 'front' defines where an item is
 * dequeued. 'Back' defines where an item is enqueued. In other words, 
 * consumer will use the front. Producer will use the back
 */
struct queue{
  int front, back, size;
  struct buf_object *data;
  pthread_mutex_t lock;
};

typedef struct cpuid_struct {
  unsigned int eax;
  unsigned int ebx;
  unsigned int ecx;
  unsigned int edx;
} cpuid_t;

struct queue *create_buffer();
void enqueue(struct queue *buffer, struct buf_object *object);
struct buf_object dequeue(struct queue *buffer);
void *producer_actions(void *buffer);
void *consumer_actions(void *buffer);
struct buf_object *make_object();
int get_random(int min, int max);
pthread_cond_t added_item;
pthread_cond_t removed_item;
int _is_intel_cpu();
void cpuid (cpuid_t *info, unsigned int leaf, unsigned int subleaf);
int get_drng_support();

int is_supported;
int rdrand32(uint32_t *rand);

// Copied from intel website
// https://software.intel.com/en-us/articles/intel-digital-random-number-generator-drng-software-implementation-guide
//***************************


#define DRNG_NO_SUPPORT 0x0
#define DRNG_HAS_RDRAND 0x1
#define DRNG_HAS_RDSEED 0x2


int _is_intel_cpu ()
{
	static int intel_cpu= -1;
	cpuid_t info;

	if ( intel_cpu == -1 ) {
		cpuid(&info, 0, 0);

		if (
			memcmp((char *) &info.ebx, "Genu", 4) ||
			memcmp((char *) &info.edx, "ineI", 4) ||
			memcmp((char *) &info.ecx, "ntel", 4)
		) {
			intel_cpu= 0;
		} else {
			intel_cpu= 1;
		}
	}

	return intel_cpu;
}

void cpuid (cpuid_t *info, unsigned int leaf, unsigned int subleaf)
{
	asm volatile("cpuid"
	: "=a" (info->eax), "=b" (info->ebx), "=c" (info->ecx), "=d" (info->edx)
	: "a" (leaf), "c" (subleaf)
	);
}


int get_drng_support()
{
	static int drng_features= -1;

	/* So we don't call cpuid multiple times for 
 * 	 * the same information */

	if ( drng_features == -1 ) {
		drng_features= DRNG_NO_SUPPORT;

		if ( _is_intel_cpu() ) {
			cpuid_t info;

			cpuid(&info, 1, 0);

			if ( (info.ecx & 0x40000000) == 0x40000000 ) {
				drng_features|= DRNG_HAS_RDRAND;
			}

			cpuid(&info, 7, 0);

			if ( (info.ebx & 0x40000) == 0x40000 ) {
				drng_features|= DRNG_HAS_RDSEED;
			}
		} 
	}

	return drng_features;
}

// *******************************

int main(void)
{
  is_supported = get_drng_support();

  struct queue *buffer = create_buffer();
  pthread_t producer;
  pthread_t consumer;
  int returnValue = 0;

  init_genrand(time(NULL));
  if(buffer == NULL){
		if(DEBUG_MODE) {
			printf("Failed to create buffer\n");
			}
    returnValue = (-1);
  }
  else {
		if(DEBUG_MODE) {
			printf("Spawning threads\n");
		}
    pthread_create(&producer, NULL, producer_actions, (void *)buffer);
    pthread_create(&consumer, NULL, consumer_actions, (void *)buffer);
    while(1);
    free(buffer);
  }

  printf("%d\n", get_random(2,5)); 
  return returnValue;
}

int rdrand32(uint32_t *rand)
{
	unsigned char ok;
	
	if(DEBUG_MODE){
		printf("Executing assembly instruction.\n");
	}
	asm volatile ("rdrand %0; setc %1"
			: "=r" (*rand), "=qm" (ok));

	if(DEBUG_MODE){
		printf("Successfully executed assembly instruction\n");
	}
	return (int) ok;
}

int get_random(int min, int max)
{
  int returnVal;

  if(is_supported){
    int retries = 10; // intel recomend retrying 10 times
    while(retries > 0){
      uint32_t *rand = malloc(sizeof(uint32_t));
      if(rdrand32(rand)){
				if(DEBUG_MODE){
					printf("Successfully returned from rdrand32\n");
				}
        retries = 0;
        returnVal = (((int) *rand)&(max-min+1))+min;
      }
      retries--;
    }
  }
  else{
		if(DEBUG_MODE){
			printf("No rdrand, using Mersenne Twister\n");
		}
    returnVal = (genrand_int32()%(max-min+1))+min;
  }
  return returnVal;
}

/*
 * Initialize all the elements of our buffer. If there is an error creating
 * any element, the return will be a null ptr
 */
struct queue *create_buffer()
{
  struct queue *buffer;
  int temp;

  buffer = malloc(sizeof(struct queue));
  if(buffer == NULL){
    printf("Error allocating memory, terminating program\n");
    }
  else{ 
    buffer->size = 0;
    buffer->front = 0;
    buffer->back = 0;

    buffer->data = malloc(sizeof(struct buf_object)*QUEUE_SIZE);
    temp = pthread_mutex_init(&buffer->lock, NULL);
    if(temp != 0){
      printf("Error generating lock, terminating program\n");
      free(buffer);
    }
  }

  return buffer;
}

void enqueue(struct queue *buffer, struct buf_object *object)
{
  pthread_mutex_lock(&buffer->lock);

  if(buffer->size==32){
		if(DEBUG_MODE){
			printf("Blocking until queue has space\n");
		}
    pthread_cond_wait(&removed_item, &buffer->lock);
  }
	if(DEBUG_MODE){
		printf("Adding a new item to the queue\n");
	}
  buffer->data[buffer->front].payload = object->payload;
  buffer->data[buffer->front].delay = object->delay;

  buffer->front = (buffer->front+1)%QUEUE_SIZE;
  buffer->size++;

  pthread_mutex_unlock(&buffer->lock);

  pthread_cond_signal(&added_item);
}   

struct buf_object dequeue(struct queue *buffer)
{
  struct buf_object returnValue;

  pthread_mutex_lock(&buffer->lock);
  if(buffer->size == 0) {
		if(DEBUG_MODE){
			printf("Blocking until there is an item in the queue\n");
		}
    pthread_cond_wait(&added_item, &buffer->lock);
  }
 
	if(DEBUG_MODE){
		printf("Removing an item from the queue\n");
	}
  returnValue.payload = buffer->data[buffer->back].payload;
  returnValue.delay = buffer->data[buffer->back].delay;
    
  buffer->back = (buffer->back+1)%QUEUE_SIZE;
  buffer->size--;
  
  pthread_mutex_unlock(&buffer->lock);

  pthread_cond_signal(&removed_item);
  return returnValue;
}

void *producer_actions(void *buffer)
{
  while(1)
  {
    enqueue((struct queue*)buffer, make_object());
    sleep(get_random(3, 7)); 
  }
}

void *consumer_actions(void *buffer){
  while(1){
    struct buf_object temp = dequeue(buffer);
    printf("%d\n", temp.payload);
    sleep(temp.delay);
  }
}

struct buf_object *make_object()
{
  struct buf_object *newItem = malloc(sizeof(struct buf_object));

  newItem->payload = get_random(0, 100);
  newItem->delay = get_random(2, 9);

  return newItem;
}


void *consumer_Actions(void *buffer){
  while(1){
    struct buf_object temp = dequeue(buffer);
    printf("%d\n", temp.payload);
    sleep(temp.delay);
  }
}

