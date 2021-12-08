#ifndef __DEFERRABLE_H__
#define __DEFERRABLE_H__

/*
* File      : deferrable.h
* This file is part of RT-Thread RTOS
* COPYRIGHT (C) 2006, RT-Thread Development Team
*
* The license and distribution terms for this file may be
* found in the file LICENSE in this distribution or at
* http://www.rt-thread.org/license/LICENSE.
*
* Change Logs:
* Date           Author                         Notes
* 2021-12-08    Nicola di Gruttola Giardino     First version
*
*/

#include <rtthread.h>

#define DEBUG_DEFERRABLE 0

#define DEFERRABLE_SERVER_STACK_SIZE 4096

rt_uint8_t rt_deferrable_stack[DEFERRABLE_SERVER_STACK_SIZE];

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

    rt_uint32_t capacity;

    rt_uint32_t capacity_left;

    struct rt_timer tim_capacity;

    struct rt_timer tim_server;

    rt_list_t asyncTask;

};

struct rt_deferrable_t deferrable_server;

void rt_timer_deferrable_capacity(void* param);

void rt_timer_deferrable_period(void* param);

void rt_thread_deferrable_entry(void *param);

rt_err_t rt_thread_deferrable_init(rt_uint32_t capacity, rt_uint32_t period, rt_uint8_t priority);

rt_thread_t rt_thread_deferrable_gethandler();

void rt_thread_deferrable_insert_task(struct rt_aperiodic_task *task);

#endif /*__DEFERRABLE_H__*/
