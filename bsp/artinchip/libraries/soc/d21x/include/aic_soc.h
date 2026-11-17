/*
 * Copyright (c) 2022, ArtInChip Technology Co., Ltd
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * D213 register addresses from Luban-Lite bsp/artinchip/sys/d21x.
 */

#ifndef __AIC_SOC_H__
#define __AIC_SOC_H__

#include <rtthread.h>

#define AIC_CMU_BASE   0x18020000UL
#define AIC_GPIO_BASE  0x18700000UL
#define AIC_UART0_BASE 0x18710000UL
#define AIC_PLIC_BASE  0x20000000UL
#define AIC_CLINT_BASE 0x24000000UL
#define AIC_UART0_IRQ  76
#define AIC_CMU_UART0  (AIC_CMU_BASE + 0x840)

/* Order device accesses. The loader must leave MMIO non-cacheable. */
rt_inline rt_uint32_t aic_read32(rt_ubase_t addr)
{
    rt_uint32_t value;

    __asm__ volatile("fence iorw, iorw" ::: "memory");
    value = *(volatile rt_uint32_t *)addr;
    __asm__ volatile("fence iorw, iorw" ::: "memory");
    return value;
}

rt_inline void aic_write32(rt_ubase_t addr, rt_uint32_t value)
{
    __asm__ volatile("fence iorw, iorw" ::: "memory");
    *(volatile rt_uint32_t *)addr = value;
    __asm__ volatile("fence iorw, iorw" ::: "memory");
}

void aic_soc_init(void);
void aic_clock_init(void);
void aic_interrupt_init(void);

#endif /* __AIC_SOC_H__ */
