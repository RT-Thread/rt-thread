/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-22     Jesven       first version
 */

#ifndef DRV_TIMER_H__
#define DRV_TIMER_H__

void timer_init(int timer, unsigned int preload);
void timer_clear_pending(int timer);

#endif
