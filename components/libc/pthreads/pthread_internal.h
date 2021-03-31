/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#ifndef __PTHREAD_INTERNAL_H__
#define __PTHREAD_INTERNAL_H__

#include <rtthread.h>
#include <pthread.h>
#include <sys/time.h>

struct _pthread_cleanup
{
    void (*cleanup_func)(void *parameter);
    void *parameter;

    struct _pthread_cleanup *next;
};
typedef struct _pthread_cleanup _pthread_cleanup_t;

struct _pthread_key_data
{
    int is_used;
    void (*destructor)(void *parameter);
};
typedef struct _pthread_key_data _pthread_key_data_t;

#ifndef PTHREAD_NUM_MAX
#define PTHREAD_NUM_MAX 32
#endif

#define PTHREAD_MAGIC   0x70746873
struct _pthread_data
{
    rt_uint32_t magic;
    pthread_attr_t attr;
    rt_thread_t tid;

    void* (*thread_entry)(void *parameter);
    void *thread_parameter;

    /* return value */
    void *return_value;

    /* semaphore for joinable thread */
    rt_sem_t joinable_sem;

    /* cancel state and type */
    rt_uint8_t cancelstate;
    volatile rt_uint8_t canceltype;
    volatile rt_uint8_t canceled;

    _pthread_cleanup_t *cleanup;
    void** tls; /* thread-local storage area */
};
typedef struct _pthread_data _pthread_data_t;

_pthread_data_t *_pthread_get_data(pthread_t thread);

void posix_mq_system_init(void);
void posix_sem_system_init(void);
void pthread_key_system_init(void);

#endif
