/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date          Author                          Notes
 * 2021-12-08    Nicola di Gruttola Giardino     First version
 */

#ifndef TASKSERVER_H__
#define TASKSERVER_H__

#include <rtthread.h>

struct rt_aperiodic_task
{

    char name[RT_NAME_MAX];

    void (*thd_fun)(void*);

    void *args;

    rt_list_t tlist;

};

typedef struct rt_aperiodic_task rt_aperiodic_task_t;

struct rt_deferrable_t
{

    struct rt_thread deferrable;

    rt_uint8_t priority;

    rt_uint32_t capacity;

    rt_uint32_t capacity_left;

    struct rt_timer tim_capacity;

    struct rt_timer tim_server;

    rt_list_t asyncTask;
    
};

void rt_timer_deferrable_capacity(void* param);

void rt_timer_deferrable_period(void* param);

rt_err_t rt_thread_deferrable_init(rt_uint32_t capacity, rt_uint32_t period, rt_uint8_t priority);

rt_thread_t rt_thread_deferrable_gethandler(void);

void rt_thread_deferrable_insert_task(struct rt_aperiodic_task *task);

#endif /*TASKSERVER_H__*/
