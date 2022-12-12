/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-27     flybreak     the first version.
 */

#pragma once
#ifndef __cplusplus
void ARMTPLInit();
#else
#include <rtthread.h>

#define ARM_TPL_MAX_DELAY 1000
#define ARM_TPL_THREAD_STACK_SIZE 4096

enum arm_tpl_mutex_type
{
    NORMAL,
    RECURSIVE,
};

struct arm_tpl_mutex_struct
{
    rt_mutex_t mutex;
    arm_tpl_mutex_type type;
};

struct arm_tpl_thread_struct
{
    rt_thread_t task;
    void *(*func)(void *);
    void *arg;
    rt_sem_t join_sem;
    rt_sem_t detach_sem;
};

class arm_tpl_cv
{
public:
    arm_tpl_cv();
    ~arm_tpl_cv();
    void wait(rt_mutex_t lock, bool recursive);
    int timedwait(rt_mutex_t lock, bool recursive, unsigned int timeout_ms);
    void signal();
    void broadcast();
private:
    rt_sem_t s;
    rt_sem_t h;
    rt_mutex_t x;
};

#endif
