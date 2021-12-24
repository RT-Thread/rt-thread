/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-07     Meco Man     first Version
 */
#ifndef __DELAY_H__
#define __DELAY_H__

void msleep(unsigned int msecs);
void ssleep(unsigned int seconds);
void mdelay(unsigned long msecs);
void udelay(unsigned long usecs);
void ndelay(unsigned long nsecs);

#endif
