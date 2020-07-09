/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */
#ifndef __DRV_TIMER_H__
#define __DRV_TIMER_H__

#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"

typedef struct rt_systimer_device
{
    int  timer_id;
    rt_uint32_t cnt;
} rt_systimer_t;

int rt_hw_systimer_init(void);


#endif
