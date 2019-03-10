/*
 * File      : drv_pin.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-03-13     Liuguang     the first version. 
 * 2018-03-19     Liuguang     add GPIO interrupt mode support.
 */
 
#ifndef __DRV_PIN_H__
#define __DRV_PIN_H__

#include <rtthread.h> 
#include <rtdevice.h> 

int rt_hw_pin_init(void);

#endif
