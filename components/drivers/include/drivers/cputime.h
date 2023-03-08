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

#include <stdint.h>
#include "cputimer.h"

struct rt_clock_cputime_ops
{
    double (*cputime_getres)(void);
    uint64_t (*cputime_gettime)(void);
    int (*cputime_settimeout)(uint64_t tick, void (*timeout)(void *param), void *param);
};

double clock_cpu_getres(void);
uint64_t clock_cpu_gettime(void);
int clock_cpu_settimeout(uint64_t tick, void (*timeout)(void *param), void *param);
int clock_cpu_issettimeout(void);

uint64_t clock_cpu_microsecond(uint64_t cpu_tick);
uint64_t clock_cpu_millisecond(uint64_t cpu_tick);

int clock_cpu_setops(const struct rt_clock_cputime_ops *ops);

#endif
