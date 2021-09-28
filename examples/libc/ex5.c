/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
/* The classic producer-consumer example, implemented with semaphores.
   All integers between 0 and 9999 should be printed exactly twice,
   once to the right of the arrow and once to the left. */

#include <stdio.h>
#include "pthread.h"
#include "semaphore.h"

#define BUFFER_SIZE 16

/* Circular buffer of integers. */

struct prodcons {
  int buffer[BUFFER_SIZE];      /* the actual data */
  int readpos, writepos;        /* positions for reading and writing */
  sem_t sem_read;               /* number of elements available for reading */
  sem_t sem_write;              /* number of locations available for writing */
};

/* Initialize a buffer */

void init(struct prodcons * b)
{
  sem_init(&b->sem_write, 0, BUFFER_SIZE - 1);
  sem_init(&b->sem_read, 0, 0);
  b->readpos = 0;
  b->writepos = 0;
}

/* Store an integer in the buffer */

void put(struct prodcons * b, int data)
{
  /* Wait until buffer is not full */
  sem_wait(&b->sem_write);
  /* Write the data and advance write pointer */
  b->buffer[b->writepos] = data;
  b->writepos++;
  if (b->writepos >= BUFFER_SIZE) b->writepos = 0;
  /* Signal that the buffer contains one more element for reading */
  sem_post(&b->sem_read);
}

/* Read and remove an integer from the buffer */

int get(struct prodcons * b)
{
  int data;
  /* Wait until buffer is not empty */
  sem_wait(&b->sem_read);
  /* Read the data and advance read pointer */
  data = b->buffer[b->readpos];
  b->readpos++;
  if (b->readpos >= BUFFER_SIZE) b->readpos = 0;
  /* Signal that the buffer has now one more location for writing */
  sem_post(&b->sem_write);
  return data;
}

/* A test program: one thread inserts integers from 1 to 10000,
   the other reads them and prints them. */

#define OVER (-1)

struct prodcons buffer;

static void *producer(void * data)
{
  int n;
  for (n = 0; n < 10000; n++) {
    printf("%d --->\n", n);
    put(&buffer, n);
  }
  put(&buffer, OVER);
  return NULL;
}

static void *consumer(void * data)
{
  int d;
  while (1) {
    d = get(&buffer);
    if (d == OVER) break;
    printf("---> %d\n", d);
  }
  return NULL;
}

int libc_ex5(void)
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
FINSH_FUNCTION_EXPORT(libc_ex5, example 5 for libc);

