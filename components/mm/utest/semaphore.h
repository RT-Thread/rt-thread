/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-24     WangXiaoyao  Complete testcase for synchronization
 */
#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include <stdatomic.h>

typedef struct {
    atomic_int count;
} semaphore_t;

void semaphore_init(semaphore_t *sem, int count)
{
    atomic_init(&sem->count, count);
}

void semaphore_wait(semaphore_t *sem)
{
    int count;
    do {
        count = atomic_load(&sem->count);
    } while (count == 0 || !atomic_compare_exchange_weak(&sem->count, &count, count - 1));
}

void semaphore_signal(semaphore_t *sem)
{
    atomic_fetch_add(&sem->count, 1);
}

#endif /* __SEMAPHORE_H__ */
