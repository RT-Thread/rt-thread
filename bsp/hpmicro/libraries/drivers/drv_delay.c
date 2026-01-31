/*
 * Copyright (c) 2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rtthread.h>
#include "hpm_clock_drv.h"

void rt_hw_us_delay(rt_uint32_t us)
{
    clock_cpu_delay_us(us);
}
