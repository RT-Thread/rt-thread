/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-04-01     huijie.feng  first version
 */

#ifndef __BARRIER_H
#define __BARRIER_H

#define sev()   __asm__ __volatile__ ("sev" : : : "memory")
#define wfe()   __asm__ __volatile__ ("wfe" : : : "memory")
#define wfi()   __asm__ __volatile__ ("wfi" : : : "memory")

#define isb(option) __asm__ __volatile__ ("isb " #option : : : "memory")
#define dsb(option) __asm__ __volatile__ ("dsb " #option : : : "memory")
#define dmb(option) __asm__ __volatile__ ("dmb " #option : : : "memory")

#define mb()        dsb()
#define rmb()       dsb()
#define wmb()       dsb(st)
#define dma_rmb()   dmb(osh)
#define dma_wmb()   dmb(oshst)

#define __smp_mb()  dmb(ish)
#define __smp_rmb() __smp_mb()
#define __smp_wmb() dmb(ishst)

#endif
