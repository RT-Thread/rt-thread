/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-10-26     Bernard      the first version
 */

#ifndef __PTHREAD_H__
#define __PTHREAD_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#include <posix_types.h>
#include <sched.h>

#define PTHREAD_KEY_MAX             8

#define PTHREAD_COND_INITIALIZER    {-1, 0}
#define PTHREAD_RWLOCK_INITIALIZER  {-1, 0}
#define PTHREAD_MUTEX_INITIALIZER   {-1, 0}

#define PTHREAD_CREATE_JOINABLE     0x00
#define PTHREAD_CREATE_DETACHED     0x01

#define PTHREAD_EXPLICIT_SCHED      0
#define PTHREAD_INHERIT_SCHED       1

typedef long pthread_t;
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

struct sched_param
{
    int sched_priority;
};

struct pthread_attr
{
    void* stackaddr;        /* stack address of thread */
    int   stacksize;        /* stack size of thread */

    int   inheritsched;     /* Inherit parent prio/policy */
    int   schedpolicy;      /* scheduler policy */
    struct sched_param schedparam; /* sched parameter */

    int   detachstate;      /* detach state */
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
int pthread_attr_setdetachstate(pthread_attr_t *attr, int state);
int pthread_attr_getdetachstate(pthread_attr_t const *attr, int *state);
int pthread_attr_setschedpolicy(pthread_attr_t *attr, int policy);
int pthread_attr_getschedpolicy(pthread_attr_t const *attr, int *policy);
int pthread_attr_setschedparam(pthread_attr_t *attr,struct sched_param const *param);
int pthread_attr_getschedparam(pthread_attr_t const *attr,struct sched_param *param);
int pthread_attr_setstacksize(pthread_attr_t *attr, size_t stack_size);
int pthread_attr_getstacksize(pthread_attr_t const *attr, size_t *stack_size);
int pthread_attr_setstackaddr(pthread_attr_t *attr, void *stack_addr);
int pthread_attr_getstackaddr(pthread_attr_t const *attr, void **stack_addr);
int pthread_attr_setstack(pthread_attr_t *attr,
                          void           *stack_base,
                          size_t          stack_size);
int pthread_attr_getstack(pthread_attr_t const *attr,
                          void                **stack_base,
                          size_t               *stack_size);
int pthread_attr_setguardsize(pthread_attr_t *attr, size_t guard_size);
int pthread_attr_getguardsize(pthread_attr_t const *attr, size_t *guard_size);
int pthread_attr_setscope(pthread_attr_t *attr, int scope);
int pthread_attr_getscope(pthread_attr_t const *attr);
int pthread_system_init(void);
int pthread_create (pthread_t *tid, const pthread_attr_t *attr,
    void *(*start) (void *), void *arg);

int pthread_detach (pthread_t thread);
int pthread_join (pthread_t thread, void **value_ptr);

rt_inline int pthread_equal (pthread_t t1, pthread_t t2)
{
    return t1 == t2;
}

pthread_t pthread_self (void);

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

#ifdef __cplusplus
}
#endif

#endif
