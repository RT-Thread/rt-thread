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

#include <cpu.h>
#include <riscv_timer.h>

#define CLINT_IPI_OFF           0
#define CLINT_TIMER_CMP_OFF     0x4000
#define CLINT_TIMER_VAL_OFF     0xbff8

#define CLINT_QUICKS_IPI_FORCE  0

rt_uint32_t *riscv_clint_ipi_base, *riscv_aclint_ipi_base;

rt_inline void clint_send_ipi(int cpu)
{
    if (riscv_clint_ipi_base)
    {
        HWREG32(riscv_clint_ipi_base + riscv_cpu_id_to_hartid(cpu)) = 1;
    }
}

rt_inline void clint_clear_ipi(void)
{
    if (riscv_clint_ipi_base)
    {
        HWREG32(riscv_clint_ipi_base + csr_read(CSR_MHARTID)) = 0;
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
static rt_ubase_t aclint_quicks = RT_BIT(CLINT_QUICKS_IPI_FORCE);

static const struct rt_ofw_node_id riscv_clint_ofw_ids[] =
{
    { .compatible = "riscv,clint0", },
    { .compatible = "sifive,clint0", },
#ifdef ARCH_RISCV_M_MODE
    { .compatible = "riscv,aclint-mtimer", },
    { .compatible = "riscv,aclint-mswi", .data = &aclint_quicks },
#else
    { .compatible = "riscv,aclint-sswi", .data = &aclint_quicks },
#endif
    { /* sentinel */ }
};

static rt_err_t riscv_clint_ofw_init(void)
{
    rt_err_t err;
    rt_ubase_t quicks;
    unsigned mmio_count;
    rt_uint64_t addr, size;
    rt_ubase_t mmio_ranges[4];
    struct rt_ofw_node *np;
    const struct rt_ofw_node_id *id;

    if (!(np = rt_ofw_find_node_by_ids_r(RT_NULL, riscv_clint_ofw_ids, &id)))
    {
        return -RT_ENOSYS;
    }
    quicks = id->data ? *(rt_ubase_t *)id->data : 0;

    if ((err = rt_ofw_get_address(np, 0, &addr, &size)))
    {
        return err;
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

    if (!(err = riscv_clint_common_init(mmio_ranges, mmio_count)))
    {
        if (quicks & CLINT_QUICKS_IPI_FORCE)
        {
            riscv_aclint_ipi_base = riscv_clint_ipi_base;
        }
    }

    return err;
}
#endif /* !PIC_DISABLE_DM */
