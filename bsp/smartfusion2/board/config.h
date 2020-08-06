/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-06     whik         first version
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "mss_gpio.h"
#include "mss_uart.h"

#include <rthw.h>
#include <rtthread.h>

void sw0_isr(void *args);
void sw1_isr(void *args);
void boardInit(void);
void sayHello(void);

#endif
