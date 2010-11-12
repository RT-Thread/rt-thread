/*
 * File      : pthread.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */
#ifndef __PTHREAD_H__
#define __PTHREAD_H__

#include <rtthread.h>
#include <errno.h>

#include "pthread_attr.h"
#include "pthread_mutex.h"

typedef rt_thread_t pthread_t;

typedef long pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;

enum {
	PTHREAD_CANCEL_ASYNCHRONOUS = 0,
	PTHREAD_CANCEL_ENABLE,
	PTHREAD_CANCEL_DEFERRED,
	PTHREAD_CANCEL_DISABLE,
	PTHREAD_CANCELED
};

#define PTHREAD_COND_INITIALIZER
#define PTHREAD_RWLOCK_INITIALIZER
#define PTHREAD_MUTEX_INITIALIZER	{-1, 0}

#define PTHREAD_CREATE_JOINABLE		0x00
#define PTHREAD_CREATE_DETACHED		0x01

#define PTHREAD_EXPLICIT_SCHED		0
#define PTHREAD_INHERIT_SCHED		1

enum {
    PTHREAD_MUTEX_NORMAL = 0,
    PTHREAD_MUTEX_RECURSIVE = 1,
    PTHREAD_MUTEX_ERRORCHECK = 2,
    PTHREAD_MUTEX_ERRORCHECK_NP = PTHREAD_MUTEX_ERRORCHECK,
    PTHREAD_MUTEX_RECURSIVE_NP  = PTHREAD_MUTEX_RECURSIVE,
    PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
};

/* init value for pthread_once_t */
#define PTHREAD_ONCE_INIT		0

enum {
	PTHREAD_PRIO_INHERIT =0,
	PTHREAD_PRIO_NONE,
	PTHREAD_PRIO_PROTECT,
};

#define PTHREAD_PROCESS_PRIVATE  0
#define PTHREAD_PROCESS_SHARED   1


#define PTHREAD_SCOPE_PROCESS	0
#define PTHREAD_SCOPE_SYSTEM	1

struct sched_param {
	int	sched_priority;
};

/*
 * Scheduling policies required by IEEE Std 1003.1-2001
 */
#define	SCHED_OTHER	0	/* Behavior can be FIFO or RR, or not */
#define	SCHED_FIFO	1
#define	SCHED_RR	2

int pthread_init (void);
int pthread_create (pthread_t *tid, const pthread_attr_t *attr, 
	void *(*start) (void *), void *arg);

int pthread_detach (pthread_t thread);
int pthread_join (pthread_t thread, void **value_ptr);

rt_inline int pthread_equal (pthread_t t1, pthread_t t2)
{
	return t1 == t2;
}

rt_inline pthread_t pthread_self (void)
{
	return rt_thread_self();
}

void pthread_exit (void *value_ptr);

int pthread_once(pthread_once_t * once_control, void (*init_routine) (void));

/* pthread cancel */
int pthread_cancel(pthread_t thread);
void pthread_testcancel(void);

int pthread_setcancelstate(int state, int *oldstate);
int pthread_setcanceltype(int type, int *oldtype);

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));

#endif

