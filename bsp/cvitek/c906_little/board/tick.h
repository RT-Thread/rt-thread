/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/01/11     flyingcys    The first version
 */

#ifndef __TICK_H__
#define __TICK_H__


int tick_isr(void);
int rt_hw_tick_init(void);

#endif /* __TICK_H__ */
