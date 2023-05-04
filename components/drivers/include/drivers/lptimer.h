/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-10-11     zhangsz      the first version
 */

#ifndef __LPTIMER_H__
#define __LPTIMER_H__

#include <rtthread.h>

struct rt_lptimer
{
    struct rt_timer timer;
    rt_list_t list;
};
typedef struct rt_lptimer *rt_lptimer_t;

void rt_lptimer_init(rt_lptimer_t  timer,
                   const char *name,
                   void (*timeout)(void *parameter),
                   void       *parameter,
                   rt_tick_t   time,
                   rt_uint8_t  flag);

rt_err_t rt_lptimer_detach(rt_lptimer_t timer);
rt_err_t rt_lptimer_start(rt_lptimer_t timer);
rt_err_t rt_lptimer_stop(rt_lptimer_t timer);

rt_err_t rt_lptimer_control(rt_lptimer_t timer, int cmd, void *arg);

rt_tick_t rt_lptimer_next_timeout_tick(void);

#endif
