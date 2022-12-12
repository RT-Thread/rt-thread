/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
