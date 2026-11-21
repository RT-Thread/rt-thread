/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Bring up C907 from E907. CCU sequence from SyterKit c907_boot ret-v4;
 * PMC power-on for hart0/hart1 from board_smp / e907-dual.
 */

#include <stdint.h>

#include "board_c907_release.h"

#define CCU_BASE        0x02001000U
#define CCU_CPU_CLK     (CCU_BASE + 0x500U)
#define CCU_RESET_CFG   (CCU_BASE + 0x504U)
#define CCU_PIC_CLK     (CCU_BASE + 0x508U)
#define CCU_CFG_BUS     (CCU_BASE + 0x50cU)

#define RISCV_CFG_BASE  0x08008000U
#define RESET_ENTRY_LO(n) (RISCV_CFG_BASE + 0x100U + 0x80U * (n))
#define RESET_ENTRY_HI(n) (RISCV_CFG_BASE + 0x104U + 0x80U * (n))
#define CORE_CFG(n)       (RISCV_CFG_BASE + 0x108U + 0x80U * (n))

#define PMC_BASE(n)            (0x08000000U + 0x1000U * (n))
#define PMC_SW_MODE_CTRL(n, m) (PMC_BASE(n) + 0x100U + 0x4U * (m))
#define PMC_MODE_MANUAL_ON     (0x3U << 3)
#define PMC_POWER_ON           0x11U

static uint32_t mmio_read(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}

static void mmio_write(uint32_t addr, uint32_t value)
{
    *(volatile uint32_t *)addr = value;
}

static void fence_io(void)
{
    __asm__ volatile("fence ow, ow" ::: "memory");
}

static void pmc_power_on(unsigned int hartid)
{
    mmio_write(PMC_SW_MODE_CTRL(hartid, 0), PMC_MODE_MANUAL_ON);
    mmio_write(PMC_SW_MODE_CTRL(hartid, 1), PMC_POWER_ON);
    fence_io();
}

static void set_reset_entry(unsigned int hartid, unsigned long entry_addr)
{
    uint32_t cfg;

    cfg = mmio_read(CORE_CFG(hartid)) & ~0x300U;
    cfg |= 0x100U; /* 32-bit mode */
    mmio_write(CORE_CFG(hartid), cfg);
    mmio_write(RESET_ENTRY_LO(hartid), (uint32_t)entry_addr);
    mmio_write(RESET_ENTRY_HI(hartid), 0);
    fence_io();
}

int rt_hw_c907_release(unsigned long entry_addr)
{
    uint32_t v, cfg, rst;

    mmio_write(CCU_BASE + 0x20U, 0xf8216310U);

    v = mmio_read(CCU_PIC_CLK);
    mmio_write(CCU_PIC_CLK, (v & 0x7effffffU) | 0x80000000U);

    cfg = mmio_read(CCU_CFG_BUS);
    rst = mmio_read(CCU_RESET_CFG);
    mmio_write(CCU_CFG_BUS, cfg | 0x00010001U);
    mmio_write(CCU_RESET_CFG, rst | 0x16aa100cU);
    fence_io();

    /* Enable RISCV_CFG bus gate (same bit board_smp uses). */
    mmio_write(CCU_CFG_BUS, mmio_read(CCU_CFG_BUS) | 0x00010001U);

    set_reset_entry(0, entry_addr);
    set_reset_entry(1, entry_addr); /* hart1 parks in SMP secondary wait */

    pmc_power_on(0);
    pmc_power_on(1);

    __asm__ volatile("fence rw, rw" ::: "memory");
    __asm__ volatile("fence.i" ::: "memory");

    mmio_write(CCU_CPU_CLK, mmio_read(CCU_CPU_CLK) & 0xfffcffffU);
    mmio_write(CCU_RESET_CFG, mmio_read(CCU_RESET_CFG) | 0x16aa0103U);
    fence_io();
    mmio_write(CCU_RESET_CFG, mmio_read(CCU_RESET_CFG) | 0x16aa0010U);
    fence_io();
    mmio_write(CCU_RESET_CFG, mmio_read(CCU_RESET_CFG) | 0x16aa0020U);
    fence_io();

    return 0;
}
