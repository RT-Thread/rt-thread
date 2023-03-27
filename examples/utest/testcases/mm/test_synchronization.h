/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-24     WangXiaoyao  Complete testcase for synchronization
 */
#ifndef __TEST_SYNCHRONIZATION_H__
#define __TEST_SYNCHRONIZATION_H__

#include "common.h"
#include "semaphore.h"

#ifdef RT_USING_SMP

#define THREAD_CNT RT_CPUS_NR
#define TEST_TIMES 2000
#define PRIO (UTEST_THR_PRIORITY + 1)
/* size of mapping buffer */
#define BUF_SIZE (64ul << 10)

/* engage with sibling */
struct rt_semaphore done;
static semaphore_t sem1[THREAD_CNT / 2];
static semaphore_t sem2[THREAD_CNT / 2];

static void *map(void)
{
    int err;
    int flags = MMF_PREFETCH;
    size_t attr = MMU_MAP_K_RWCB;
    void *vaddr = 0;
    err =
        rt_aspace_map(&rt_kernel_space, &vaddr, BUF_SIZE, attr, flags, &rt_mm_dummy_mapper, 0);
    if (err)
        uassert_true(0);
    return vaddr;
}

static void unmap(void *buf)
{
    int err;
    err =
        rt_aspace_unmap(&rt_kernel_space, buf);
    if (err)
        uassert_true(0);
    return ;
}

static void group1_entry(void *param)
{
    const size_t id = (size_t)param;
    size_t test_times = TEST_TIMES;
    size_t alive = test_times / 10;
    void *buf;

    while (test_times--)
    {
        if (test_times % alive == 0)
            uassert_true(1);

        buf = map();

        memset(buf, 'A' + id, BUF_SIZE);
        /* if other core write to our cache, force the changes to be visible to us */
        rt_hw_dmb();

        if (memtest(buf, 'A' + id, BUF_SIZE))
            uassert_true(0);

        semaphore_signal(&sem1[id]);
        semaphore_wait(&sem2[id]);
        unmap(buf);
    }

    rt_sem_release(&done);
    return;
}

static void group2_entry(void *param)
{
    const size_t id = (size_t)param;
    size_t test_times = TEST_TIMES;
    size_t alive = test_times / 10;
    void *buf;

    while (test_times--)
    {
        if (test_times % alive == 0)
            uassert_true(1);

        semaphore_signal(&sem2[id]);
        semaphore_wait(&sem1[id]);
        buf = map();

        memset(buf, 'a' + id, BUF_SIZE);
        /* if other core write to our cache, force the changes to be visible to us */
        rt_hw_dmb();

        if (memtest(buf, 'a' + id, BUF_SIZE))
            uassert_true(0);

        unmap(buf);
    }

    rt_sem_release(&done);
    return;
}

/**
 * @brief On a smp system, we create at least 4 threads
 * 2 doing map, 2 doing unmapping at the same moment
 */

static void synchronization_tc(void)
{
    rt_thread_t group1[THREAD_CNT / 2];
    rt_thread_t group2[THREAD_CNT / 2];

    rt_sem_init(&done, __func__, 0, RT_IPC_FLAG_FIFO);

    for (size_t i = 0; i < THREAD_CNT / 2; i++)
    {
        char name[RT_NAME_MAX];
        rt_sprintf(name, "grp1_%d", i);
        group1[i] =
            rt_thread_create(name, group1_entry, (void *)i, ARCH_PAGE_SIZE, PRIO, 10);
        uassert_true(!!group1[i]);
        semaphore_init(&sem1[i], 0);

        uassert_true(!rt_thread_startup(group1[i]));
    }

    for (size_t i = 0; i < THREAD_CNT / 2; i++)
    {
        char name[RT_NAME_MAX];
        rt_sprintf(name, "grp2_%d", i);
        group2[i] =
            rt_thread_create(name, group2_entry, (void *)i, ARCH_PAGE_SIZE, PRIO, 10);
        uassert_true(!!group2[i]);
        semaphore_init(&sem2[i], 0);

        uassert_true(!rt_thread_startup(group2[i]));
    }

    /* wait all thread exit */
    for (size_t i = 0; i < (THREAD_CNT / 2 * 2); i++)
    {
        rt_sem_take(&done, RT_WAITING_FOREVER);
    }
    LOG_I("all threads exit");
    rt_sem_detach(&done);
}

#else /* RT_USING_SMP */

static void synchronization_tc(void)
{
    uassert_true(1);
}
#endif /* RT_USING_SMP */

#endif /* __TEST_SYNCHRONIZATION_H__ */
