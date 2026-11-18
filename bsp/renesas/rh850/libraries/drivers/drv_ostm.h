/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#ifndef __DRV_OSTM_H__
#define __DRV_OSTM_H__

#include <rtdef.h>

void rh850_ostm_start_interval(rt_ubase_t base, rt_uint32_t cmp);
int rh850_tick_init(rt_ubase_t base, int vector, rt_uint32_t clk_hz);

#endif
