/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
/* Multi-thread searching.
   Illustrates: thread cancellation, cleanup handlers. */

#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>

/* Defines the number of searching threads */
#define NUM_THREADS 5

/* Function prototypes */
void *search(void *);
void print_it(void *);

/* Global variables */
pthread_t threads[NUM_THREADS];
pthread_mutex_t lock;
int tries;
volatile int started;

int libc_ex3()
{
  int i;
  int pid;

  /* create a number to search for */
  pid = getpid();
  printf("Searching for the number = %d...\n", pid);

  /* Initialize the mutex lock */
  pthread_mutex_init(&lock, NULL);

  /* Create the searching threads */
  for (started=0; started<NUM_THREADS; started++)
    pthread_create(&threads[started], NULL, search, (void *)pid);

  /* Wait for (join) all the searching threads */
  for (i=0; i<NUM_THREADS; i++)
    pthread_join(threads[i], NULL);

  printf("It took %d tries to find the number.\n", tries);

  /* Exit the program */
  return 0;
}
#include <finsh.h>
FINSH_FUNCTION_EXPORT(libc_ex3, example 5 for libc);

/* This is the cleanup function that is called
   when the threads are cancelled */

void print_it(void *arg)
{
  int *try = (int *) arg;
  pthread_t tid;

  /* Get the calling thread's ID */
  tid = pthread_self();

  /* Print where the thread was in its search when it was cancelled */
  printf("Thread %lx was canceled on its %d try.\n", tid, *try);
}

/* This is the search routine that is executed in each thread */

void *search(void *arg)
{
  int num = (int) arg;
  int i, j, ntries;
  pthread_t tid;

  /* get the calling thread ID */
  tid = pthread_self();

  /* use the thread ID to set the seed for the random number generator */
  /* Since srand and rand are not thread-safe, serialize with lock */

  /* Try to lock the mutex lock --
     if locked, check to see if the thread has been cancelled
     if not locked then continue */
  while (pthread_mutex_trylock(&lock) == EBUSY)
    pthread_testcancel();

  srand((int)tid);
  i = rand() & 0xFFFFFF;
  pthread_mutex_unlock(&lock);
  ntries = 0;

  /* Set the cancellation parameters --
     - Enable thread cancellation
     - Defer the action of the cancellation */

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

  while (started < NUM_THREADS)
    sched_yield ();

  /* Push the cleanup routine (print_it) onto the thread
     cleanup stack.  This routine will be called when the
     thread is cancelled.  Also note that the pthread_cleanup_push
     call must have a matching pthread_cleanup_pop call.  The
     push and pop calls MUST be at the same lexical level
     within the code */

  /* Pass address of `ntries' since the current value of `ntries' is not
     the one we want to use in the cleanup function */

  pthread_cleanup_push(print_it, (void *)&ntries);

  /* Loop forever */
  while (1) {
    i = (i + 1) & 0xFFFFFF;
    ntries++;

    /* Does the random number match the target number? */
    if (num == i) {
      /* Try to lock the mutex lock --
         if locked, check to see if the thread has been cancelled
         if not locked then continue */
      while (pthread_mutex_trylock(&lock) == EBUSY)
        pthread_testcancel();

      /* Set the global variable for the number of tries */
      tries = ntries;
      printf("Thread %lx found the number!\n", tid);

      /* Cancel all the other threads */
      for (j=0; j<NUM_THREADS; j++)
        if (threads[j] != tid) pthread_cancel(threads[j]);

      /* Break out of the while loop */
      break;
    }

    /* Every 100 tries check to see if the thread has been cancelled. */
    if (ntries % 100 == 0) {
      pthread_testcancel();
    }
  }

  /* The only way we can get here is when the thread breaks out
     of the while loop.  In this case the thread that makes it here
     has found the number we are looking for and does not need to run
     the thread cleanup function.  This is why the pthread_cleanup_pop
     function is called with a 0 argument; this will pop the cleanup
     function off the stack without executing it */

  pthread_cleanup_pop(0);
  return((void *)0);
}
