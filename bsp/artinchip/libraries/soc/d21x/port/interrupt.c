/*
 * Copyright (c) 2022-2026, ArtInChip Technology Co., Ltd
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * PLIC setup adapted from Luban-Lite bsp/artinchip/sys/d21x/system.c.
 */

#include "aic_soc.h"

void aic_interrupt_init(void)
{
    /* Mask loader-owned sources before the common PLIC driver starts.
     * Pending bits are read-only. Never complete an unclaimed source. */
    for (int i = 0; i < 32; i++)
    {
        aic_write32(AIC_PLIC_BASE + 0x2000 + i * 4, 0);
        aic_write32(AIC_PLIC_BASE + 0x2080 + i * 4, 0);
    }
    /* C906 PLIC priority enable, not part of the standard PLIC block. */
    aic_write32(AIC_PLIC_BASE + 0x1ffffc, 1);
}

rt_ubase_t platform_get_plic_base(void)
{
    return AIC_PLIC_BASE;
}

rt_size_t platform_get_plic_size(void)
{
    return 0x210000;
}
