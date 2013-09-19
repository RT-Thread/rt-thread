/*
 * File      : pthread.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#ifndef __PTHREAD_H__
#define __PTHREAD_H__

#include <rtthread.h>
#include <posix_types.h>

#define PTHREAD_KEY_MAX             8

#define PTHREAD_COND_INITIALIZER    {-1, 0}
#define PTHREAD_RWLOCK_INITIALIZER  {-1, 0}
#define PTHREAD_MUTEX_INITIALIZER   {-1, 0}

#define PTHREAD_CREATE_JOINABLE     0x00
#define PTHREAD_CREATE_DETACHED     0x01

#define PTHREAD_EXPLICIT_SCHED      0
#define PTHREAD_INHERIT_SCHED       1

typedef rt_thread_t pthread_t;
typedef long pthread_condattr_t;
typedef long pthread_rwlockattr_t;
typedef long pthread_mutexattr_t;
typedef long pthread_barrierattr_t;

typedef int pthread_key_t;
typedef int pthread_once_t;

enum
{
    PTHREAD_CANCEL_ASYNCHRONOUS = 0,
    PTHREAD_CANCEL_ENABLE,
    PTHREAD_CANCEL_DEFERRED,
    PTHREAD_CANCEL_DISABLE,
    PTHREAD_CANCELED
};

enum
{
    PTHREAD_MUTEX_NORMAL = 0,
    PTHREAD_MUTEX_RECURSIVE = 1,
    PTHREAD_MUTEX_ERRORCHECK = 2,
    PTHREAD_MUTEX_ERRORCHECK_NP = PTHREAD_MUTEX_ERRORCHECK,
    PTHREAD_MUTEX_RECURSIVE_NP  = PTHREAD_MUTEX_RECURSIVE,
    PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
};

/* init value for pthread_once_t */
#define PTHREAD_ONCE_INIT       0

enum
{
    PTHREAD_PRIO_INHERIT =0,
    PTHREAD_PRIO_NONE,
    PTHREAD_PRIO_PROTECT,
};

#define PTHREAD_PROCESS_PRIVATE  0
#define PTHREAD_PROCESS_SHARED   1

#define PTHREAD_SCOPE_PROCESS   0
#define PTHREAD_SCOPE_SYSTEM    1

struct pthread_attr
{
    void*       stack_base;
    rt_uint16_t stack_size;     /* stack size of thread */

    rt_uint8_t priority;        /* priority of thread */
    rt_uint8_t detachstate;     /* detach state */
    rt_uint8_t policy;          /* scheduler policy */
    rt_uint8_t inheritsched;    /* Inherit parent prio/policy */
};
typedef struct pthread_attr pthread_attr_t;

struct pthread_mutex
{
    pthread_mutexattr_t attr;
    struct rt_mutex lock;
};
typedef struct pthread_mutex pthread_mutex_t;

struct pthread_cond
{
    pthread_condattr_t attr;
    struct rt_semaphore sem;
};
typedef struct pthread_cond pthread_cond_t;

struct pthread_rwlock
{
    pthread_rwlockattr_t attr;

    pthread_mutex_t      rw_mutex;          /* basic lock on this struct */
    pthread_cond_t       rw_condreaders;    /* for reader threads waiting */
    pthread_cond_t       rw_condwriters;    /* for writer threads waiting */

    int rw_nwaitreaders;    /* the number of reader threads waiting */
    int rw_nwaitwriters;    /* the number of writer threads waiting */
    int rw_refcount;    /* 0: unlocked, -1: locked by writer, > 0 locked by n readers */
};
typedef struct pthread_rwlock pthread_rwlock_t;

/* spinlock implementation, (ADVANCED REALTIME THREADS)*/
struct pthread_spinlock
{
    int lock;
};
typedef struct pthread_spinlock pthread_spinlock_t;

struct pthread_barrier
{
    int count;
    pthread_cond_t cond;
    pthread_mutex_t mutex;
};
typedef struct pthread_barrier pthread_barrier_t;

/* pthread thread interface */
int pthread_attr_destroy(pthread_attr_t *attr);
int pthread_attr_init(pthread_attr_t *attr);

int pthread_system_init(void);
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

/* pthread cleanup */
void pthread_cleanup_pop(int execute);
void pthread_cleanup_push(void (*routine)(void*), void *arg);

/* pthread cancel */
int pthread_cancel(pthread_t thread);
void pthread_testcancel(void);
int pthread_setcancelstate(int state, int *oldstate);
int pthread_setcanceltype(int type, int *oldtype);

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));
int pthread_kill(pthread_t thread, int sig);

/* pthread mutex interface */
int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);

int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);
int pthread_mutexattr_gettype(const pthread_mutexattr_t *attr, int *type);
int pthread_mutexattr_settype(pthread_mutexattr_t *attr, int type);
int pthread_mutexattr_setpshared(pthread_mutexattr_t *attr, int  pshared);
int pthread_mutexattr_getpshared(pthread_mutexattr_t *attr, int *pshared);

/* pthread condition interface */
int pthread_condattr_destroy(pthread_condattr_t *attr);
int pthread_condattr_init(pthread_condattr_t *attr);

/* ADVANCED REALTIME feature in IEEE Std 1003.1, 2004 Edition */
int pthread_condattr_getclock(const pthread_condattr_t *attr,
                              clockid_t                *clock_id);
int pthread_condattr_setclock(pthread_condattr_t *attr,
                              clockid_t           clock_id);

int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
int pthread_cond_destroy(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_signal(pthread_cond_t *cond);

int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t        *cond,
                           pthread_mutex_t       *mutex,
                           const struct timespec *abstime);

/* pthread rwlock interface */
int pthread_rwlockattr_init (pthread_rwlockattr_t *attr);
int pthread_rwlockattr_destroy (pthread_rwlockattr_t *attr);
int pthread_rwlockattr_getpshared (const pthread_rwlockattr_t *attr, int *pshared);
int pthread_rwlockattr_setpshared (pthread_rwlockattr_t *attr, int pshared);

int pthread_rwlock_init (pthread_rwlock_t *rwlock, const pthread_rwlockattr_t *attr);
int pthread_rwlock_destroy (pthread_rwlock_t *rwlock);

int pthread_rwlock_rdlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_tryrdlock (pthread_rwlock_t *rwlock);

int pthread_rwlock_timedrdlock (pthread_rwlock_t *rwlock, const struct timespec *abstime);
int pthread_rwlock_timedwrlock (pthread_rwlock_t *rwlock, const struct timespec *abstime);

int pthread_rwlock_unlock (pthread_rwlock_t *rwlock);

int pthread_rwlock_wrlock (pthread_rwlock_t *rwlock);
int pthread_rwlock_trywrlock (pthread_rwlock_t *rwlock);

/* pthread spinlock interface */
int pthread_spin_init (pthread_spinlock_t *lock, int pshared);
int pthread_spin_destroy (pthread_spinlock_t *lock);

int pthread_spin_lock (pthread_spinlock_t * lock);
int pthread_spin_trylock (pthread_spinlock_t * lock);
int pthread_spin_unlock (pthread_spinlock_t * lock);

/* pthread barrier interface */
int pthread_barrierattr_destroy(pthread_barrierattr_t *attr);
int pthread_barrierattr_init(pthread_barrierattr_t *attr);
int pthread_barrierattr_getpshared(const pthread_barrierattr_t *attr, int *pshared);
int pthread_barrierattr_setpshared(pthread_barrierattr_t *attr, int pshared);

int pthread_barrier_destroy(pthread_barrier_t *barrier);
int pthread_barrier_init(pthread_barrier_t           *barrier,
                         const pthread_barrierattr_t *attr,
                         unsigned                     count);

int pthread_barrier_wait(pthread_barrier_t *barrier);

/*  Signal Generation and Delivery, P1003.1b-1993, p. 63
    NOTE: P1003.1c/D10, p. 34 adds sigev_notify_function and
          sigev_notify_attributes to the sigevent structure.  */
union sigval
{
    int    sival_int;    /* Integer signal value */
    void  *sival_ptr;    /* Pointer signal value */
};

struct sigevent
{
    int              sigev_notify;               /* Notification type */
    int              sigev_signo;                /* Signal number */
    union sigval     sigev_value;                /* Signal value */
    void           (*sigev_notify_function)( union sigval );
                                               /* Notification function */
    pthread_attr_t  *sigev_notify_attributes;    /* Notification Attributes */
};

/* posix clock and timer */
#define MILLISECOND_PER_SECOND  1000UL
#define MICROSECOND_PER_SECOND  1000000UL
#define NANOSECOND_PER_SECOND   1000000000UL

#define MILLISECOND_PER_TICK    (MILLISECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define MICROSECOND_PER_TICK    (MICROSECOND_PER_SECOND / RT_TICK_PER_SECOND)
#define NANOSECOND_PER_TICK     (NANOSECOND_PER_SECOND  / RT_TICK_PER_SECOND)

#ifndef CLOCK_REALTIME
#define CLOCK_REALTIME      0
#endif

int clock_getres  (clockid_t clockid, struct timespec *res);
int clock_gettime (clockid_t clockid, struct timespec *tp);
int clock_settime (clockid_t clockid, const struct timespec *tp);

#endif

