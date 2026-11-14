/*
 * Copyright (c) 2022-2026, ArtInChip Technology Co., Ltd
 * Copyright (c) 2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * C906 setup adapted from Luban-Lite bsp/artinchip/sys/d21x/system.c.
 */

#include <rthw.h>
#include "aic_soc.h"

void aic_soc_init(void)
{
    rt_ubase_t value;

    /* C906 THEADISAEE and misaligned access, as in vendor SystemInit. */
    __asm__ volatile("csrr %0, 0x7c0" : "=r"(value));
    value |= (1UL << 22) | (1UL << 15);
    __asm__ volatile("csrw 0x7c0, %0" ::"r"(value) : "memory");

    __asm__ volatile("csrr %0, mstatus" : "=r"(value));
    value = (value & ~(3UL << 13)) | (1UL << 13);
    __asm__ volatile("csrw mstatus, %0" ::"r"(value) : "memory");
}
