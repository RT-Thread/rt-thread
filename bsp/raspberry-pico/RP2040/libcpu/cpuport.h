/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-22     rose_man     add RT_USING_SMP
 */

#ifndef  CPUPORT_H__
#define  CPUPORT_H__

typedef union {
    unsigned long slock;
    struct __arch_tickets {
        unsigned short owner;
        unsigned short next;
    } tickets;
} rt_hw_spinlock_t;

#endif  /*CPUPORT_H__*/
