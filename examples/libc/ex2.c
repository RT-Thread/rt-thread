/* The classic producer-consumer example.
   Illustrates mutexes and conditions.
   All integers between 0 and 9999 should be printed exactly twice,
   once to the right of the arrow and once to the left. */

#include <stdio.h>
#include "pthread.h"

#define BUFFER_SIZE 16

/* Circular buffer of integers. */

struct prodcons {
  int buffer[BUFFER_SIZE];      /* the actual data */
  pthread_mutex_t lock;         /* mutex ensuring exclusive access to buffer */
  int readpos, writepos;        /* positions for reading and writing */
  pthread_cond_t notempty;      /* signaled when buffer is not empty */
  pthread_cond_t notfull;       /* signaled when buffer is not full */
};

/* Initialize a buffer */

static void init(struct prodcons * b)
{
  pthread_mutex_init(&b->lock, NULL);
  pthread_cond_init(&b->notempty, NULL);
  pthread_cond_init(&b->notfull, NULL);
  b->readpos = 0;
  b->writepos = 0;
}

/* Store an integer in the buffer */
static void put(struct prodcons * b, int data)
{
  pthread_mutex_lock(&b->lock);
  /* Wait until buffer is not full */
  while ((b->writepos + 1) % BUFFER_SIZE == b->readpos) {
    pthread_cond_wait(&b->notfull, &b->lock);
    /* pthread_cond_wait reacquired b->lock before returning */
  }
  /* Write the data and advance write pointer */
  b->buffer[b->writepos] = data;
  b->writepos++;
  if (b->writepos >= BUFFER_SIZE) b->writepos = 0;
  /* Signal that the buffer is now not empty */
  pthread_cond_signal(&b->notempty);
  pthread_mutex_unlock(&b->lock);
}

/* Read and remove an integer from the buffer */

static int get(struct prodcons * b)
{
  int data;
  pthread_mutex_lock(&b->lock);
  /* Wait until buffer is not empty */
  while (b->writepos == b->readpos) {
    pthread_cond_wait(&b->notempty, &b->lock);
  }
  /* Read the data and advance read pointer */
  data = b->buffer[b->readpos];
  b->readpos++;
  if (b->readpos >= BUFFER_SIZE) b->readpos = 0;
  /* Signal that the buffer is now not full */
  pthread_cond_signal(&b->notfull);
  pthread_mutex_unlock(&b->lock);
  return data;
}

/* A test program: one thread inserts integers from 1 to 10000,
   the other reads them and prints them. */

#define OVER (-1)

struct prodcons buffer;

static void * producer(void * data)
{
  int n;
  for (n = 0; n < 10000; n++) {
    printf("%d --->\n", n);
    put(&buffer, n);
  }
  put(&buffer, OVER);
  return NULL;
}

static void * consumer(void * data)
{
  int d;
  while (1) {
    d = get(&buffer);
    if (d == OVER) break;
    printf("---> %d\n", d);
  }
  return NULL;
}

int libc_ex2(void)
{
  pthread_t th_a, th_b;
  void * retval;

  init(&buffer);
  /* Create the threads */
  pthread_create(&th_a, NULL, producer, 0);
  pthread_create(&th_b, NULL, consumer, 0);
  /* Wait until producer and consumer finish. */
  pthread_join(th_a, &retval);
  pthread_join(th_b, &retval);
  return 0;
}
#include <finsh.h>
FINSH_FUNCTION_EXPORT(libc_ex2, example 2 for libc);
