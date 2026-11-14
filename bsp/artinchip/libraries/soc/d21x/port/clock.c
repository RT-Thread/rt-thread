/*
 * Copyright (c) 2022-2026, ArtInChip Technology Co., Ltd
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Gate/reset sequencing adapted from Luban-Lite bsp/artinchip/hal/cmu.
 * DDR, PLLs and the bus clock tree belong to the loader.
 */

#include <rthw.h>
#include "aic_soc.h"

#define CMU_BUS_GATE    (1U << 12)
#define CMU_RESET_N     (1U << 13)
#define CMU_MODULE_GATE (1U << 8)

static void aic_clock_enable(rt_ubase_t reg, rt_uint32_t gates)
{
    aic_write32(reg, aic_read32(reg) | gates);
    rt_hw_us_delay(30);
    aic_write32(reg, aic_read32(reg) | CMU_RESET_N);
    rt_hw_us_delay(30);
}

void aic_clock_init(void)
{
#ifdef BSP_USING_UART0
    aic_clock_enable(AIC_CMU_UART0, CMU_BUS_GATE | CMU_MODULE_GATE);
#endif
    aic_clock_enable(AIC_CMU_BASE + 0x83c, CMU_BUS_GATE); /* GPIO */
}
