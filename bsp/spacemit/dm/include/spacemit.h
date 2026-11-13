/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SPACEMIT_H__
#define __SPACEMIT_H__

#include <rthw.h>

#define is_aligned(x, a) (((x) & ((typeof(x))(a) - 1)) == 0)

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

rt_inline rt_uint32_t fls(rt_uint32_t val)
{
    rt_uint32_t  bit = 32;

    if (!val)
        return 0;
    if (!(val & 0xffff0000u))
    {
        val <<= 16;
        bit -= 16;
    }
    if (!(val & 0xff000000u))
    {
        val <<= 8;
        bit -= 8;
    }
    if (!(val & 0xf0000000u))
    {
        val <<= 4;
        bit -= 4;
    }
    if (!(val & 0xc0000000u))
    {
        val <<= 2;
        bit -= 2;
    }
    if (!(val & 0x80000000u))
    {
        bit -= 1;
    }

    return bit;
}

#ifdef ARCH_RISCV
#include <csr.h>

/* TCM enable register */
#define CSR_TCMCFG  0x5db
#define TCM_EN      _UL(0x00000001) /* TCM Access Enable */

rt_inline rt_uint32_t tcm_override_readl(const volatile void *addr)
{
    rt_uint32_t val;
    rt_ubase_t level, tcm_csr;

    level = rt_hw_local_irq_disable();
    tcm_csr = csr_read_clear(CSR_TCMCFG, TCM_EN);
    val = HWREG32(addr);
    csr_set(CSR_TCMCFG, tcm_csr);
    rt_hw_local_irq_enable(level);

    return val;
}

/* i/o write on the tcm override area */
rt_inline void tcm_override_writel(volatile void *addr, rt_uint32_t val)
{
    rt_ubase_t level, tcm_csr;

    level = rt_hw_local_irq_disable();
    tcm_csr = csr_read_clear(CSR_TCMCFG, TCM_EN);
    HWREG32(addr) = val;
    csr_set(CSR_TCMCFG, tcm_csr);
    rt_hw_local_irq_enable(level);
}
#endif /* ARCH_RISCV */

#endif /* __SPACEMIT_H__ */
