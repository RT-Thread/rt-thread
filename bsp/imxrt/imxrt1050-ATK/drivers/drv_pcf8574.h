/*
 * File      : drv_pcf8574.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006-2013, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-06-12     zylx     the first version.
 */
#ifndef __PCF8574_H
#define __PCF8574_H

#include <rtthread.h>
#include "rtdevice.h"

#define PCF8574_ADDR 0X20	

rt_uint8_t pcf8574_read_byte(void);
void pcf8574_write_byte(rt_uint8_t data);
void pcf8574_write_bit(rt_uint8_t bit, rt_uint8_t sta);
rt_uint8_t pcf8574_read_bit(rt_uint8_t bit);

#endif

