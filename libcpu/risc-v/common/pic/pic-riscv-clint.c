/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-01-30     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#ifndef PIC_DISABLE_DM
#include <rtdevice.h>
#endif

#include <cpu.h>
#include <csr.h>
#include <riscv_timer.h>

#include "pic-riscv-clint.h"

#define CLINT_IPI_OFF           0
#define CLINT_TIMER_CMP_OFF     0x4000
#define CLINT_TIMER_VAL_OFF     0xbff8

#define CLINT_QUIRK_IPI_FORCE   0
#define CLINT_QUIRK_IPI_CSR_CLEAR 1

static rt_uint32_t *riscv_clint_ipi_base;
rt_uint32_t *riscv_aclint_ipi_base;
static rt_bool_t riscv_clint_ipi_csr_clear;

void clint_send_ipi(int cpu)
{
    if (!riscv_cpu_id_available(cpu))
    {
        return;
    }

    if (riscv_clint_ipi_base)
    {
        HWREG32(riscv_clint_ipi_base + riscv_cpu_id_to_hartid(cpu)) = 1;
    }
}

void clint_clear_ipi(void)
{
    if (riscv_clint_ipi_base)
    {
        if (riscv_clint_ipi_csr_clear)
        {
            csr_clear(CSR_IP, IE_SIE);
        }
        else
        {
            rt_ubase_t hartid = riscv_cpu_id_to_hartid(rt_hw_cpu_id());

            HWREG32(riscv_clint_ipi_base + hartid) = 0;
        }
    }
}

static rt_err_t riscv_clint_common_init(rt_ubase_t *mmio_ranges, unsigned mmio_count)
{
    void *clint_timer_val, *clint_timer_cmp;

    if (mmio_count == 1)
    {
        void *base = rt_ioremap((void *)mmio_ranges[0], mmio_ranges[1]);

        if (!base)
        {
            return -RT_EIO;
        }

        riscv_clint_ipi_base = base + CLINT_IPI_OFF;
        clint_timer_cmp = base + CLINT_TIMER_CMP_OFF;
        clint_timer_val = base + CLINT_TIMER_VAL_OFF;
    }
    else
    {
        riscv_clint_ipi_base = RT_NULL;

        clint_timer_val = rt_ioremap((void *)mmio_ranges[0], mmio_ranges[1]);

        if (!clint_timer_val)
        {
            return -RT_EIO;
        }

        clint_timer_cmp = rt_ioremap((void *)mmio_ranges[2], mmio_ranges[3]);

        if (!clint_timer_cmp)
        {
            rt_iounmap(clint_timer_val);
            return -RT_EIO;
        }
    }

    riscv_timer_probe(clint_timer_cmp, clint_timer_val);

    return RT_EOK;
}

#ifndef PIC_DISABLE_DM
#ifdef ARCH_RISCV_M_MODE
static rt_ubase_t aclint_quirks = RT_BIT(CLINT_QUIRK_IPI_FORCE);
#else
static rt_ubase_t aclint_quirks = RT_BIT(CLINT_QUIRK_IPI_FORCE) |
        RT_BIT(CLINT_QUIRK_IPI_CSR_CLEAR);
#endif

static const struct rt_ofw_node_id riscv_clint_ofw_ids[] =
{
    { .compatible = "riscv,clint0", },
    { .compatible = "sifive,clint0", },
#ifdef ARCH_RISCV_M_MODE
    { .compatible = "riscv,aclint-mtimer", },
    { .compatible = "riscv,aclint-mswi", .data = &aclint_quirks },
#else
    { .compatible = "riscv,aclint-sswi", .data = &aclint_quirks },
#endif
    { /* sentinel */ }
};

rt_err_t riscv_clint_ofw_init(void)
{
    rt_err_t err;
    rt_ubase_t quirks;
    unsigned mmio_count;
    rt_uint64_t addr, size;
    rt_ubase_t mmio_ranges[4];
    struct rt_ofw_node *np;
    const struct rt_ofw_node_id *id;

    if (!(np = rt_ofw_find_node_by_ids_r(RT_NULL, riscv_clint_ofw_ids, &id)))
    {
        return -RT_ENOSYS;
    }
    quirks = id->data ? *(rt_ubase_t *)id->data : 0;

    if ((err = rt_ofw_get_address(np, 0, &addr, &size)))
    {
        goto _out;
    }

    mmio_ranges[0] = addr;
    mmio_ranges[1] = size;
    mmio_count = 1;

    if (!rt_ofw_get_address(np, 1, &addr, &size))
    {
        mmio_ranges[2] = addr;
        mmio_ranges[3] = size;
        mmio_count = 2;
    }

    rt_ofw_node_set_flag(np, RT_OFW_F_READLY);

    if (quirks & RT_BIT(CLINT_QUIRK_IPI_FORCE))
    {
        riscv_clint_ipi_base = rt_ioremap((void *)mmio_ranges[0], mmio_ranges[1]);

        if (!riscv_clint_ipi_base)
        {
            err = -RT_EIO;
            goto _out;
        }

        riscv_aclint_ipi_base = riscv_clint_ipi_base;
        riscv_clint_ipi_csr_clear = !!(quirks & RT_BIT(CLINT_QUIRK_IPI_CSR_CLEAR));
        err = RT_EOK;
    }
    else
    {
        err = riscv_clint_common_init(mmio_ranges, mmio_count);
    }

_out:
    rt_ofw_node_put(np);

    return err;
}
#endif /* !PIC_DISABLE_DM */
