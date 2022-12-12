/*
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2019 Western Digital Corporation or its affiliates.
 *
 * Authors:
 *   Anup Patel <anup.patel@wdc.com>
 */

#ifndef __RISCV_IO_H__
#define __RISCV_IO_H__

static inline uint32_t  __raw_hartid(void)
{
    extern int boot_hartid;
    return boot_hartid;
}

static inline void __raw_writeb(rt_uint8_t val, volatile void *addr)
{
    asm volatile("sb %0, 0(%1)"
                 :
                 : "r"(val), "r"(addr));
}

static inline void __raw_writew(rt_uint16_t val, volatile void *addr)
{
    asm volatile("sh %0, 0(%1)"
                 :
                 : "r"(val), "r"(addr));
}

static inline void __raw_writel(rt_uint32_t val, volatile void *addr)
{
    asm volatile("sw %0, 0(%1)"
                 :
                 : "r"(val), "r"(addr));
}

#if __riscv_xlen != 32
static inline void __raw_writeq(rt_uint64_t val, volatile void *addr)
{
    asm volatile("sd %0, 0(%1)"
                 :
                 : "r"(val), "r"(addr));
}
#endif

static inline rt_uint8_t __raw_readb(const volatile void *addr)
{
    rt_uint8_t val;

    asm volatile("lb %0, 0(%1)"
                 : "=r"(val)
                 : "r"(addr));
    return val;
}

static inline rt_uint16_t __raw_readw(const volatile void *addr)
{
    rt_uint16_t val;

    asm volatile("lh %0, 0(%1)"
                 : "=r"(val)
                 : "r"(addr));
    return val;
}

static inline rt_uint32_t __raw_readl(const volatile void *addr)
{
    rt_uint32_t val;

    asm volatile("lw %0, 0(%1)"
                 : "=r"(val)
                 : "r"(addr));
    return val;
}

#if __riscv_xlen != 32
static inline rt_uint64_t __raw_readq(const volatile void *addr)
{
    rt_uint64_t val;

    asm volatile("ld %0, 0(%1)"
                 : "=r"(val)
                 : "r"(addr));
    return val;
}
#endif

/* FIXME: These are now the same as asm-generic */

/* clang-format off */

#define __io_rbr()      do {} while (0)
#define __io_rar()      do {} while (0)
#define __io_rbw()      do {} while (0)
#define __io_raw()      do {} while (0)

#define readb_relaxed(c)    ({ rt_uint8_t  __v; __io_rbr(); __v = __raw_readb(c); __io_rar(); __v; })
#define readw_relaxed(c)    ({ rt_uint16_t __v; __io_rbr(); __v = __raw_readw(c); __io_rar(); __v; })
#define readl_relaxed(c)    ({ rt_uint32_t __v; __io_rbr(); __v = __raw_readl(c); __io_rar(); __v; })

#define writeb_relaxed(v,c) ({ __io_rbw(); __raw_writeb((v),(c)); __io_raw(); })
#define writew_relaxed(v,c) ({ __io_rbw(); __raw_writew((v),(c)); __io_raw(); })
#define writel_relaxed(v,c) ({ __io_rbw(); __raw_writel((v),(c)); __io_raw(); })

#if __riscv_xlen != 32
#define readq_relaxed(c)    ({ rt_uint64_t __v; __io_rbr(); __v = __raw_readq(c); __io_rar(); __v; })
#define writeq_relaxed(v,c) ({ __io_rbw(); __raw_writeq((v),(c)); __io_raw(); })
#endif

#define __io_br()   do {} while (0)
#define __io_ar()   __asm__ __volatile__ ("fence i,r" : : : "memory");
#define __io_bw()   __asm__ __volatile__ ("fence w,o" : : : "memory");
#define __io_aw()   do {} while (0)

#define readb(c)    ({ rt_uint8_t  __v; __io_br(); __v = __raw_readb(c); __io_ar(); __v; })
#define readw(c)    ({ rt_uint16_t __v; __io_br(); __v = __raw_readw(c); __io_ar(); __v; })
#define readl(c)    ({ rt_uint32_t __v; __io_br(); __v = __raw_readl(c); __io_ar(); __v; })

#define writeb(v,c) ({ __io_bw(); __raw_writeb((v),(c)); __io_aw(); })
#define writew(v,c) ({ __io_bw(); __raw_writew((v),(c)); __io_aw(); })
#define writel(v,c) ({ __io_bw(); __raw_writel((v),(c)); __io_aw(); })

#if __riscv_xlen != 32
#define readq(c)    ({ rt_uint64_t __v; __io_br(); __v = __raw_readq(c); __io_ar(); __v; })
#define writeq(v,c) ({ __io_bw(); __raw_writeq((v),(c)); __io_aw(); })
#endif

#endif
