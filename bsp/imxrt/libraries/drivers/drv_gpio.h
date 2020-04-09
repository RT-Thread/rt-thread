/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-4-30     misonyo     the first version.
 */
 
#ifndef DRV_GPIO_H__
#define DRV_GPIO_H__

#include <rtthread.h> 
#include <rtdevice.h> 

#define GET_PIN(PORTx, PIN)      (32 * (PORTx - 1) + (PIN & 31))    /* PORTx:1,2,3,4,5 */

int rt_hw_pin_init(void);

#endif
