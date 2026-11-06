/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#ifndef __DRV_INTC_H__
#define __DRV_INTC_H__

#include <rtdef.h>

#define RH850_INTC_PRIO_LOWEST 15

void rh850_intc_set_priority(int vector, rt_uint32_t prio);
void rh850_intc_raise(int vector);
rt_bool_t rh850_intc_pending(int vector);
void rh850_intc_clear(int vector);

#endif
