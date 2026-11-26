/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SPACEMIT_V2D_INTERNAL_H__
#define __SPACEMIT_V2D_INTERNAL_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <v2d.h>

#define DBG_TAG "soc.spacemit.v2d"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

void v2d_hw_set_base(void *base);
int v2d_global_reset(void);
uint32_t v2d_irq_status(void);
uint32_t v2d_irqerr_status(void);
void v2d_dump_irqraw_status(void);
void v2d_irq_clear(uint32_t irq_status);
void v2d_irqerr_clear(uint32_t irq_error);
void v2d_irq_enable(void);
void v2d_irq_disable(void);
void config_v2d_hw(V2D_SUBMIT_TASK_S *task);

#endif /* __SPACEMIT_V2D_INTERNAL_H__ */
