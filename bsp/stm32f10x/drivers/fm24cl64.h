/*
 * File      : fm24cl64.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-07-17     aubrcool@qq.com   1st version
 */

#ifndef __FM24CL64_H__
#define __FM24CL64_H__

#include <rtthread.h>

extern int rt_hw_fm24cl64_init(const char *fm_device_name, const char *i2c_bus);

#endif /*__FM24CL64_H__*/
