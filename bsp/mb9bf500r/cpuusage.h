/*
 * File      : cpuusage.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-03     lgnq
 */
 
#ifndef __CPUUSAGE_H__
#define __CPUUSAGE_H__

#define CPU_UPDATE 1

void cpu_usage_get(rt_uint8_t *major, rt_uint8_t *minor);
void rt_hw_cpu_init(void);

#endif /*__ADC_H__ */
