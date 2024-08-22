/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2019-05-06     Zero-Free       first version
 * 2024-07-04     wdfk-prog       lptimer is register with hwtimer, only supports pm calls,the timer function is not supported
 */

#ifndef  __DRV_PMTIMER_H__
#define  __DRV_PMTIMER_H__

#include <rtthread.h>

/* 0x20 - 0x3F udevice control commands*/
typedef enum
{
    DRV_HW_LPTIMER_CTRL_GET_TICK_MAX    = 0x20, /* get the maximum tick value*/
    DRV_HW_LPTIMER_CTRL_GET_FREQ        = 0X21, /* get the timer frequency*/
    DRV_HW_LPTIMER_CTRL_START           = 0X22, /* set the timeout value*/
    DRV_HW_LPTIMER_CTRL_GET_COUNT       = 0X23, /* get the current count value*/
} drv_hw_lptimer_ctrl_t;

#endif /* __DRV_PMTIMER_H__ */
