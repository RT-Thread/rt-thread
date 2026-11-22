/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "clint.h"

static uint32_t mmio_r32(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}

static void mmio_w32(uint32_t addr, uint32_t value)
{
    *(volatile uint32_t *)addr = value;
}

void v861_clint_ipi_send(unsigned int hartid)
{
    if (hartid < 2)
    {
        mmio_w32(V861_CLINT_MSIP(hartid), 1);
    }
}

void v861_clint_ipi_clear(unsigned int hartid)
{
    if (hartid < 2)
    {
        mmio_w32(V861_CLINT_MSIP(hartid), 0);
    }
}

uint64_t v861_clint_mtime(void)
{
    uint32_t hi, lo;

    do
    {
        hi = mmio_r32(V861_CLINT_MTIME + 4U);
        lo = mmio_r32(V861_CLINT_MTIME);
    } while (hi != mmio_r32(V861_CLINT_MTIME + 4U));

    return ((uint64_t)hi << 32) | lo;
}

void v861_clint_set_mtimecmp(unsigned int hartid, uint64_t value)
{
    uint32_t base;

    if (hartid >= 2)
    {
        return;
    }

    base = V861_CLINT_MTIMECMP(hartid);
    mmio_w32(base, 0xffffffffU);
    mmio_w32(base + 4U, (uint32_t)(value >> 32));
    mmio_w32(base, (uint32_t)value);
}
