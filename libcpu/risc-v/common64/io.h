/*
 * Copyright (c) 2019-2020, Xim
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */
#ifndef ARCH_IO_H
#define ARCH_IO_H
#include <rtthread.h>
#define RISCV_FENCE(p, s) \
        __asm__ __volatile__ ("fence " #p "," #s : : : "memory")

/* These barriers need to enforce ordering on both devices or memory. */
#define mb()            RISCV_FENCE(iorw,iorw)
#define rmb()           RISCV_FENCE(ir,ir)
#define wmb()           RISCV_FENCE(ow,ow)

#define __arch_getl(a)                  (*(unsigned int *)(a))
#define __arch_putl(v, a)               (*(unsigned int *)(a) = (v))

#define dmb() mb()
#define __iormb() rmb()
#define __iowmb() wmb()

static inline void writel(uint32_t val, volatile void *addr)
{
    __iowmb();
    __arch_putl(val, addr);
}

static inline uint32_t readl(const volatile void *addr)
{
    uint32_t val;

    val = __arch_getl(addr);
    __iormb();
    return val;
}

static inline void write_reg(
    uint32_t val, volatile void *addr, unsigned offset)
{
    writel(val, (void *)((rt_size_t)addr + offset));
}

static inline uint32_t read_reg(
    const volatile void *addr, unsigned offset)
{
    return readl((void *)((rt_size_t)addr + offset));
}

#endif // ARCH_IO_H
