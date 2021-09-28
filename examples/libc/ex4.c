/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
/* Making a library function that uses static variables thread-safe.
   Illustrates: thread-specific data, pthread_once(). */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

/* This is a typical example of a library function that uses
   static variables to accumulate results between calls.
   Here, it just returns the concatenation of all string arguments
   that were given to it. */

#if 0

char * str_accumulate(char * s)
{
  static char accu[1024] = { 0 };
  strcat(accu, s);
  return accu;
}

#endif

/* Of course, this cannot be used in a multi-threaded program
   because all threads store "accu" at the same location.
   So, we'll use thread-specific data to have a different "accu"
   for each thread. */

/* Key identifying the thread-specific data */
static pthread_key_t str_key;
/* "Once" variable ensuring that the key for str_alloc will be allocated
   exactly once. */
static pthread_once_t str_alloc_key_once = PTHREAD_ONCE_INIT;

/* Forward functions */
static void str_alloc_key(void);
static void str_alloc_destroy_accu(void * accu);

/* Thread-safe version of str_accumulate */

char * str_accumulate(const char * s)
{
  char * accu;

  /* Make sure the key is allocated */
  pthread_once(&str_alloc_key_once, str_alloc_key);
  /* Get the thread-specific data associated with the key */
  accu = (char *) pthread_getspecific(str_key);
  /* It's initially NULL, meaning that we must allocate the buffer first. */
  if (accu == NULL) {
    accu = malloc(1024);
    if (accu == NULL) return NULL;
    accu[0] = 0;
    /* Store the buffer pointer in the thread-specific data. */
    pthread_setspecific(str_key, (void *) accu);
    printf("Thread %lx: allocating buffer at %p\n", pthread_self(), accu);
  }
  /* Now we can use accu just as in the non thread-safe code. */
  strcat(accu, s);
  return accu;
}

/* Function to allocate the key for str_alloc thread-specific data. */

static void str_alloc_key(void)
{
  pthread_key_create(&str_key, str_alloc_destroy_accu);
  printf("Thread %lx: allocated key %d\n", pthread_self(), str_key);
}

/* Function to free the buffer when the thread exits. */
/* Called only when the thread-specific data is not NULL. */

static void str_alloc_destroy_accu(void * accu)
{
  printf("Thread %lx: freeing buffer at %p\n", pthread_self(), accu);
  free(accu);
}

/* Test program */

static void *process(void * arg)
{
  char *res;
  res = str_accumulate("Result of ");
  res = str_accumulate((char *) arg);
  res = str_accumulate(" thread");
  printf("Thread %lx: \"%s\"\n", pthread_self(), res);
  return NULL;
}

int libc_ex4()
{
  char * res;
  pthread_t th1, th2;

  // res = str_accumulate("Result of ");
  pthread_create(&th1, NULL, process, (void *) "first");
  pthread_create(&th2, NULL, process, (void *) "second");
  // res = str_accumulate("initial thread");
  printf("Thread %lx: \"%s\"\n", pthread_self(), res);
  pthread_join(th1, NULL);
  pthread_join(th2, NULL);
}
#include <finsh.h>
FINSH_FUNCTION_EXPORT(libc_ex4, example 4 for libc);
