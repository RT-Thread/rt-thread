/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-27     flybreak     the first version.
 */

#include <pthread.h>
#include <cstdlib>

typedef void (*destructor) (void *);

extern "C"
int __cxa_thread_atexit_impl(destructor dtor, void* obj, void* dso_symbol)
{
    pthread_key_t key_tmp;
    if (pthread_key_create(&key_tmp, dtor) != 0)
        abort();
    pthread_setspecific(key_tmp, obj);
    return 0;
}

#if defined(__GNUC__) && !defined(__ARMCC_VERSION)/*GCC*/
#include <cxxabi.h>

extern"C"
int __cxxabiv1::__cxa_thread_atexit(destructor dtor, void *obj, void *dso_handle)
{
    return __cxa_thread_atexit_impl(dtor, obj, dso_handle);
}
#endif
