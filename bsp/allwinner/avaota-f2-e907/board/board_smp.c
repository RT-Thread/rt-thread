/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Power on the second C907 via RISCV_CFG + PMC (proven on this board).
 */

#include <rthw.h>
#include <rtthread.h>
#include <stdint.h>

#include "board_smp.h"

#define CCU_BASE             0x02001000U
#define CCU_RISCV_CFG_BGR    (CCU_BASE + 0x50cU)
#define CCU_RISCV_CFG_BGR_EN ((1U << 16) | (1U << 0))

#define RISCV_CFG_BASE      0x08008000U
#define RESET_ENTRY_LO(n)   (RISCV_CFG_BASE + 0x100U + 0x80U * (n))
#define RESET_ENTRY_HI(n)   (RISCV_CFG_BASE + 0x104U + 0x80U * (n))
#define CORE_CFG(n)         (RISCV_CFG_BASE + 0x108U + 0x80U * (n))
#define CORE_CFG_MODE_MASK  (0x3U << 8)
#define CORE_CFG_MODE_32BIT (0x1U << 8)

#define PMC_BASE(n)            (0x08000000U + 0x1000U * (n))
#define PMC_SW_MODE_CTRL(n, m) (PMC_BASE(n) + 0x100U + 0x4U * (m))
#define PMC_MODE_MANUAL_ON     (0x3U << 3)
#define PMC_POWER_ON           0x11U

static rt_uint32_t mmio_read(rt_ubase_t addr)
{
    return *(volatile rt_uint32_t *)addr;
}

static void mmio_write(rt_ubase_t addr, rt_uint32_t value)
{
    *(volatile rt_uint32_t *)addr = value;
}

int rt_hw_hart_power_on(unsigned int hartid, unsigned long entry_addr)
{
    rt_uint32_t cfg;

    if (hartid != 1)
    {
        return -1;
    }

    mmio_write(CCU_RISCV_CFG_BGR, mmio_read(CCU_RISCV_CFG_BGR) | CCU_RISCV_CFG_BGR_EN);

    cfg = mmio_read(CORE_CFG(hartid)) & ~CORE_CFG_MODE_MASK;
    cfg |= CORE_CFG_MODE_32BIT;
    mmio_write(CORE_CFG(hartid), cfg);
    mmio_write(RESET_ENTRY_LO(hartid), (rt_uint32_t)entry_addr);
    mmio_write(RESET_ENTRY_HI(hartid), 0);
    __asm__ volatile("fence iorw, iorw" ::: "memory");

    mmio_write(PMC_SW_MODE_CTRL(hartid, 0), PMC_MODE_MANUAL_ON);
    mmio_write(PMC_SW_MODE_CTRL(hartid, 1), PMC_POWER_ON);
    return 0;
}
