/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2017-12-23     Bernard           first version
 */

#ifndef CPUTIME_H__
#define CPUTIME_H__

struct rt_clock_cputime_ops
{
    float    (*cputime_getres) (void);
    uint32_t (*cputime_gettime)(void);
};

float    clock_cpu_getres(void);
uint32_t clock_cpu_gettime(void);

uint32_t clock_cpu_microsecond(uint32_t cpu_tick);
uint32_t clock_cpu_millisecond(uint32_t cpu_tick);

int clock_cpu_setops(const struct rt_clock_cputime_ops *ops);

#endif
