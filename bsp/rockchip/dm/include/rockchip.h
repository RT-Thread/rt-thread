/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-3-08      GuEe-GUI     the first version
 */

#ifndef __ROCKCHIP_H__
#define __ROCKCHIP_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <dt-bindings/size.h>

#define rk_clrsetreg(addr, clr, set)    HWREG32(addr) = (((clr) | (set)) << 16 | (set))
#define rk_clrreg(addr, clr)            HWREG32(addr) = ((clr) << 16)
#define rk_setreg(addr, set)            HWREG32(addr) = ((set) << 16 | (set))

#define HIWORD_UPDATE(val, mask, shift) ((val) << (shift) | (mask) << ((shift) + 16))

#define readx_poll_timeout(OP, ADDR, VAL, COND, DELAY_US, TIMEOUT_US) \
({                                                      \
    rt_uint64_t timeout_us = (TIMEOUT_US);              \
    rt_int64_t left_ns = timeout_us * 1000L;            \
    rt_ubase_t delay_us = (DELAY_US);                   \
    rt_uint64_t delay_ns = delay_us * 1000L;            \
    for (;;)                                            \
    {                                                   \
        (VAL) = OP(ADDR);                               \
        if (COND)                                       \
        {                                               \
            break;                                      \
        }                                               \
        if (timeout_us && left_ns < 0)                  \
        {                                               \
            (VAL) = OP(ADDR);                           \
            break;                                      \
        }                                               \
        if (delay_us)                                   \
        {                                               \
            rt_hw_us_delay(delay_us);                   \
            if (timeout_us)                             \
            {                                           \
                left_ns -= delay_ns;                    \
            }                                           \
        }                                               \
        rt_hw_cpu_relax();                              \
        if (timeout_us)                                 \
        {                                               \
            --left_ns;                                  \
        }                                               \
    }                                                   \
    (COND) ? RT_EOK : -RT_ETIMEOUT;                     \
})

#define readl_poll_timeout(ADDR, VAL, COND, DELAY_US, TIMEOUT_US) \
        readx_poll_timeout(HWREG32, ADDR, VAL, COND, DELAY_US, TIMEOUT_US)

#define is_aligned(x, a)    (((x) & ((typeof(x))(a) - 1)) == 0)

rt_inline int fls(int x)
{
    return x ? sizeof(x) * 8 - __builtin_clz(x) : 0;
}

rt_inline int fls_long(unsigned long x)
{
    return x ? sizeof(x) * 8 - __builtin_clzl(x) : 0;
}

rt_inline int __roundup_pow_of_two(rt_uint32_t x)
{
    return 1UL << fls(x - 1);
}

rt_inline int __rounddown_pow_of_two(rt_uint32_t x)
{
    return (1UL << fls(x - 1)) / 2;
}

#endif /* __ROCKCHIP_H__ */