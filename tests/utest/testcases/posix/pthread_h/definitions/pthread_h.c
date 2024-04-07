/*
 * Copyright (c) 2002, Intel Corporation. All rights reserved.
 * Created by:  rolla.n.selbak REMOVE-THIS AT intel DOT com
 * This file is licensed under the GPL license.  For the full content
 * of this license, see the COPYING file at the top level of this
 * source tree.

 Test this function is defined:

 int pthread_mutexattr_destroy(pthread_mutexattr_t *);
 */

#include <pthread.h>

int     (*test_pthread_atfork)(void (*prepare)(void), void (*parent)(void), void (*child)(void));
int     (*test_pthread_attr_destroy)(pthread_attr_t *__attr);
int     (*test_pthread_attr_getdetachstate)(const pthread_attr_t *__attr, int *__detachstate);
int     (*test_pthread_attr_getguardsize)(const pthread_attr_t *__attr, size_t *__guardsize);
int     (*test_pthread_attr_getinheritsched)(const pthread_attr_t *__attr, int *__inheritsched);
int     (*test_pthread_attr_getschedparam)(const pthread_attr_t *__attr, struct sched_param *__param);
int     (*test_pthread_attr_getschedpolicy)(const pthread_attr_t *__attr, int *__policy);
int     (*test_pthread_attr_getscope)(const pthread_attr_t *__attr, int *__contentionscope);
int     (*test_pthread_attr_getstack)(const pthread_attr_t *attr, void **__stackaddr, size_t *__stacksize);
int     (*test_pthread_attr_getstackaddr)(const pthread_attr_t *__attr, void **__stackaddr);
int     (*test_pthread_attr_getstacksize)(const pthread_attr_t *__attr, size_t *__stacksize);
int     (*test_pthread_attr_init)(pthread_attr_t *__attr);
int     (*test_pthread_attr_setdetachstate)(pthread_attr_t *__attr, int __detachstate);
int     (*test_pthread_attr_setguardsize)(pthread_attr_t *__attr, size_t __guardsize);
int     (*test_pthread_attr_setinheritsched)(pthread_attr_t *__attr, int __inheritsched);
int     (*test_pthread_attr_setschedparam)(pthread_attr_t *__attr, const struct sched_param *__param);
int     (*test_pthread_attr_setschedpolicy)(pthread_attr_t *__attr, int __policy);
int     (*test_pthread_attr_setscope)(pthread_attr_t *__attr, int __contentionscope);
int     (*test_pthread_attr_setstack)(pthread_attr_t *attr, void *__stackaddr, size_t __stacksize);
int     (*test_pthread_attr_setstackaddr)(pthread_attr_t  *__attr, void *__stackaddr);
int     (*test_pthread_attr_setstacksize)(pthread_attr_t *__attr, size_t __stacksize);
int     (*test_pthread_cancel)(pthread_t __pthread);
void    (*test_pthread_cleanup_pop)(int execute);
void    (*test_pthread_cleanup_push)(void (*routine)(void*), void *arg);
int     (*test_pthread_cond_broadcast)(pthread_cond_t *__cond);
int     (*test_pthread_cond_destroy)(pthread_cond_t *__mutex);
int     (*test_pthread_cond_init)(pthread_cond_t *__cond, const pthread_condattr_t *__attr);
int     (*test_pthread_cond_signal)(pthread_cond_t *__cond);
int     (*test_pthread_cond_timedwait)(pthread_cond_t *__cond, pthread_mutex_t *__mutex, const struct timespec *__abstime);
int     (*test_pthread_cond_wait)(pthread_cond_t *__cond, pthread_mutex_t *__mutex);
int     (*test_pthread_condattr_destroy)(pthread_condattr_t *__attr);
int     (*test_pthread_condattr_getclock)(const pthread_condattr_t *__restrict __attr, clockid_t *__restrict __clock_id);
int     (*test_pthread_condattr_init)(pthread_condattr_t *__attr);
int     (*test_pthread_condattr_setclock)(pthread_condattr_t *__attr, clockid_t __clock_id);
int     (*test_pthread_create)(pthread_t *__pthread, const pthread_attr_t  *__attr, void *(*__start_routine)(void *), void *__arg);
int     (*test_pthread_detach)(pthread_t __pthread);
int     (*test_pthread_equal)(pthread_t __t1, pthread_t __t2);
void    (*test_pthread_exit)(void *__value_ptr);
int     (*test_pthread_getcpuclockid)(pthread_t thread, clockid_t *clock_id);
int     (*test_pthread_getconcurrency)(void);
int     (*test_pthread_getschedparam)(pthread_t __pthread, int *__policy, struct sched_param *__param);
void *  (*test_pthread_getspecific)(pthread_key_t __key);
int     (*test_pthread_join)(pthread_t __pthread, void **__value_ptr);
int     (*test_pthread_key_create)(pthread_key_t *__key, void (*__destructor)(void *));
int     (*test_pthread_key_delete)(pthread_key_t __key);
int     (*test_pthread_mutex_destroy)(pthread_mutex_t *__mutex);
int     (*test_pthread_mutex_getprioceiling)(const pthread_mutex_t *__restrict __mutex, int *__prioceiling);
int     (*test_pthread_mutex_init)(pthread_mutex_t *__mutex, const pthread_mutexattr_t *__attr);
int     (*test_pthread_mutex_lock)(pthread_mutex_t *__mutex);
int     (*test_pthread_mutex_setprioceiling)(pthread_mutex_t *__mutex, int __prioceiling, int *__old_ceiling);
int     (*test_pthread_mutex_trylock)(pthread_mutex_t *__mutex);
int     (*test_pthread_mutex_unlock)(pthread_mutex_t *__mutex);
int     (*test_pthread_mutexattr_destroy)(pthread_mutexattr_t *__attr);
int     (*test_pthread_mutexattr_getprioceiling)(const pthread_mutexattr_t *__attr, int *__prioceiling);
int     (*test_pthread_mutexattr_getprotocol)(const pthread_mutexattr_t *__attr, int *__protocol);
int     (*test_pthread_mutexattr_gettype)(const pthread_mutexattr_t *__attr, int *__kind);
int     (*test_pthread_mutexattr_init)(pthread_mutexattr_t *__attr);
int     (*test_pthread_mutexattr_setprioceiling)(const pthread_mutexattr_t *__attr, int __prioceiling);
int     (*test_pthread_mutexattr_setprotocol)(const pthread_mutexattr_t *__attr, int __protocol);
int     (*test_pthread_mutexattr_settype)(pthread_mutexattr_t *__attr, int __kind);
int     (*test_pthread_once)(pthread_once_t *__once_control, void (*__init_routine)(void));
pthread_t (*test_pthread_self)(void);
int     (*test_pthread_setcancelstate)(int __state, int *__oldstate);
int     (*test_pthread_setcanceltype)(int __type, int *__oldtype);
int     (*test_pthread_setconcurrency)(int new_level);
int     (*test_pthread_setschedparam)(pthread_t __pthread, int __policy, const struct sched_param *__param);
int     (*test_pthread_setschedprio)(pthread_t thread, int prio);
int     (*test_pthread_setspecific)(pthread_key_t __key, const void *__value);
void    (*test_pthread_testcancel)(void);


__attribute__((unused)) static void dummy_func()
{
    test_pthread_atfork = pthread_atfork;
    test_pthread_attr_destroy = pthread_attr_destroy;
    test_pthread_attr_getdetachstate = pthread_attr_getdetachstate;
    test_pthread_attr_getguardsize = pthread_attr_getguardsize;
    test_pthread_attr_getinheritsched = pthread_attr_getinheritsched;
    test_pthread_attr_getschedparam = pthread_attr_getschedparam;
    test_pthread_attr_getschedpolicy = pthread_attr_getschedpolicy;
    test_pthread_attr_getscope = pthread_attr_getscope;
    test_pthread_attr_getstack = pthread_attr_getstack;
    test_pthread_attr_getstackaddr = pthread_attr_getstackaddr;
    test_pthread_attr_getstacksize = pthread_attr_getstacksize;
    test_pthread_attr_init = pthread_attr_init;
    test_pthread_attr_setdetachstate = pthread_attr_setdetachstate;
    test_pthread_attr_setguardsize = pthread_attr_setguardsize;
    test_pthread_attr_setinheritsched = pthread_attr_setinheritsched;
    test_pthread_attr_setschedparam = pthread_attr_setschedparam;
    test_pthread_attr_setschedpolicy = pthread_attr_setschedpolicy;
    test_pthread_attr_setscope = pthread_attr_setscope;
    test_pthread_attr_setstack = pthread_attr_setstack;
    test_pthread_attr_setstackaddr = pthread_attr_setstackaddr;
    test_pthread_attr_setstacksize = pthread_attr_setstacksize;
    test_pthread_cancel = pthread_cancel;
    test_pthread_cleanup_pop = pthread_cleanup_pop;
    test_pthread_cleanup_push = pthread_cleanup_push;
    test_pthread_cond_broadcast = pthread_cond_broadcast;
    test_pthread_cond_destroy = pthread_cond_destroy;
    test_pthread_cond_init = pthread_cond_init;
    test_pthread_cond_signal = pthread_cond_signal;
    test_pthread_cond_timedwait = pthread_cond_timedwait;
    test_pthread_cond_wait = pthread_cond_wait;
    test_pthread_condattr_destroy = pthread_condattr_destroy;
    test_pthread_condattr_getclock = pthread_condattr_getclock;
    test_pthread_condattr_init = pthread_condattr_init;
    test_pthread_condattr_setclock = pthread_condattr_setclock;
    test_pthread_create = pthread_create;
    test_pthread_detach = pthread_detach;
    test_pthread_equal = pthread_equal;
    test_pthread_exit = pthread_exit;
    test_pthread_getcpuclockid = pthread_getcpuclockid;
    test_pthread_getconcurrency = pthread_getconcurrency;
    test_pthread_getschedparam = pthread_getschedparam;
    test_pthread_getspecific = pthread_getspecific;
    test_pthread_join = pthread_join;
    test_pthread_key_create = pthread_key_create;
    test_pthread_key_delete = pthread_key_delete;
    test_pthread_mutex_destroy = pthread_mutex_destroy;
    test_pthread_mutex_getprioceiling = pthread_mutex_getprioceiling;
    test_pthread_mutex_init = pthread_mutex_init;
    test_pthread_mutex_lock = pthread_mutex_lock;
    test_pthread_mutex_setprioceiling = pthread_mutex_setprioceiling;
    test_pthread_mutex_trylock = pthread_mutex_trylock;
    test_pthread_mutex_unlock = pthread_mutex_unlock;
    test_pthread_mutexattr_destroy = pthread_mutexattr_destroy;
    test_pthread_mutexattr_getprioceiling = pthread_mutexattr_getprioceiling;
    test_pthread_mutexattr_getprotocol = pthread_mutexattr_getprotocol;
    test_pthread_mutexattr_gettype = pthread_mutexattr_gettype;
    test_pthread_mutexattr_init = pthread_mutexattr_init;
    test_pthread_mutexattr_setprioceiling = pthread_mutexattr_setprioceiling;
    test_pthread_mutexattr_setprotocol = pthread_mutexattr_setprotocol;
    test_pthread_mutexattr_settype = pthread_mutexattr_settype;
    test_pthread_once = pthread_once;
    test_pthread_self = pthread_self;
    test_pthread_setcancelstate = pthread_setcancelstate;
    test_pthread_setcanceltype = pthread_setcanceltype;
    test_pthread_setconcurrency = pthread_setconcurrency;
    test_pthread_setschedparam = pthread_setschedparam;
    test_pthread_setschedprio = pthread_setschedprio;
    test_pthread_setspecific = pthread_setspecific;
    test_pthread_testcancel = pthread_testcancel;

    return;
}
