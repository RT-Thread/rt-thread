/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/misc.h>

#define DBG_TAG "cache.sifive_ccache"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>

#define SIFIVE_CCACHE_DIRECCFIX_LOW             0x100
#define SIFIVE_CCACHE_DIRECCFIX_HIGH            0x104
#define SIFIVE_CCACHE_DIRECCFIX_COUNT           0x108

#define SIFIVE_CCACHE_DIRECCFAIL_LOW            0x120
#define SIFIVE_CCACHE_DIRECCFAIL_HIGH           0x124
#define SIFIVE_CCACHE_DIRECCFAIL_COUNT          0x128

#define SIFIVE_CCACHE_DATECCFIX_LOW             0x140
#define SIFIVE_CCACHE_DATECCFIX_HIGH            0x144
#define SIFIVE_CCACHE_DATECCFIX_COUNT           0x148

#define SIFIVE_CCACHE_DATECCFAIL_LOW            0x160
#define SIFIVE_CCACHE_DATECCFAIL_HIGH           0x164
#define SIFIVE_CCACHE_DATECCFAIL_COUNT          0x168

#define SIFIVE_CCACHE_CONFIG                    0x00
#define SIFIVE_CCACHE_CONFIG_BANK_MASK          RT_GENMASK_ULL(7, 0)
#define SIFIVE_CCACHE_CONFIG_WAYS_MASK          RT_GENMASK_ULL(15, 8)
#define SIFIVE_CCACHE_CONFIG_SETS_MASK          RT_GENMASK_ULL(23, 16)
#define SIFIVE_CCACHE_CONFIG_BLKS_MASK          RT_GENMASK_ULL(31, 24)

#define SIFIVE_CCACHE_FLUSH64                   0x200
#define SIFIVE_CCACHE_FLUSH32                   0x240

#define SIFIVE_CCACHE_WAYENABLE                 0x08
#define SIFIVE_CCACHE_ECCINJECTERR              0x40

#define SIFIVE_CCACHE_MAX_ECCINTR               4
#define SIFIVE_CCACHE_LINE_SIZE                 64

#define SIFIVE_CCACHE_TRUNKCLOCKGATE            0x1000
#define SIFIVE_CCACHE_TRUNKCLOCKGATE_DISABLE    RT_BIT(0)
#define SIFIVE_CCACHE_REGIONCLOCKGATE_DISABLE   RT_BIT(1)

enum
{
    DIR_CORR = 0,
    DATA_CORR,
    DATA_UNCORR,
    DIR_UNCORR,
};

enum
{
    QUIRK_BROKEN_DATA_UNCORR    = RT_BIT(0),
    QUIRK_HAS_CG                = RT_BIT(1),
};

static void *ccache_base;
static rt_ubase_t ccache_quirk;
static rt_uint32_t ccache_level;
static int ccache_irq[SIFIVE_CCACHE_MAX_ECCINTR];
static struct rt_ofw_node *ccache_np;

static void ccache_enable(void)
{
    rt_uint32_t config, ways;

    /* Enable all ways of composable cache */
    config = HWREG32(ccache_base + SIFIVE_CCACHE_CONFIG);
    ways = RT_FIELD_GET(SIFIVE_CCACHE_CONFIG_WAYS_MASK, config);

    HWREG32(ccache_base + SIFIVE_CCACHE_WAYENABLE) = ways - 1;

    if (ccache_quirk & QUIRK_HAS_CG)
    {
        /* Enable clock gating bits */
        config = HWREG32(ccache_base + SIFIVE_CCACHE_TRUNKCLOCKGATE);
        config &= ~(SIFIVE_CCACHE_TRUNKCLOCKGATE_DISABLE | SIFIVE_CCACHE_REGIONCLOCKGATE_DISABLE);
        HWREG32(ccache_base + SIFIVE_CCACHE_TRUNKCLOCKGATE) = config;
    }
}

static void ccache_disable(void)
{
    rt_uint32_t config;

    HWREG32(ccache_base + SIFIVE_CCACHE_WAYENABLE) = 0;

    if (ccache_quirk & QUIRK_HAS_CG)
    {
        /* Disable clock gating bits */
        config = HWREG32(ccache_base + SIFIVE_CCACHE_TRUNKCLOCKGATE);
        config |= SIFIVE_CCACHE_TRUNKCLOCKGATE_DISABLE | SIFIVE_CCACHE_REGIONCLOCKGATE_DISABLE;
        HWREG32(ccache_base + SIFIVE_CCACHE_TRUNKCLOCKGATE) = config;
    }
}

static void ccache_flush_range(void *vaddr, rt_size_t size)
{
    rt_ubase_t start = (rt_ubase_t)rt_kmem_v2p(vaddr);
    rt_ubase_t end = start + size;

    if (!size)
    {
        return;
    }

    rt_hw_barrier();

    for (rt_ubase_t line = RT_ALIGN_DOWN(start, SIFIVE_CCACHE_LINE_SIZE);
        line < end;
        line += SIFIVE_CCACHE_LINE_SIZE)
    {
    #ifdef ARCH_CPU_64BIT
        HWREG64(ccache_base + SIFIVE_CCACHE_FLUSH64) = line;
    #else
        HWREG32(ccache_base + SIFIVE_CCACHE_FLUSH32) = line >> 4;
    #endif
        rt_hw_barrier();
    }
}

static struct rt_hwcache_ops ccache_mgmt =
{
    .name = "ccache",
    .enable = ccache_enable,
    .disable = ccache_disable,
    .flush = ccache_flush_range,
    .invalidate = ccache_flush_range,
};

static void sifive_ccache_isr(int irq, void *param)
{
    rt_uint32_t add_h, add_l;

    if (irq == ccache_irq[DIR_CORR])
    {
        add_h = HWREG32(ccache_base + SIFIVE_CCACHE_DIRECCFIX_HIGH);
        add_l = HWREG32(ccache_base + SIFIVE_CCACHE_DIRECCFIX_LOW);
        LOG_E("Dir error: 0x%08x%08x", add_h, add_l);

        /* Reading this register clears the DirError interrupt sig */
        HWREG32(ccache_base + SIFIVE_CCACHE_DIRECCFIX_COUNT);
    }
    else if (irq == ccache_irq[DIR_UNCORR])
    {
        add_h = HWREG32(ccache_base + SIFIVE_CCACHE_DIRECCFAIL_HIGH);
        add_l = HWREG32(ccache_base + SIFIVE_CCACHE_DIRECCFAIL_LOW);

        /* Reading this register clears the DirFail interrupt sig */
        HWREG32(ccache_base + SIFIVE_CCACHE_DIRECCFAIL_COUNT);
        LOG_E("Dir fail: 0x%08x%08x", add_h, add_l);
        RT_ASSERT(0);
    }
    else if (irq == ccache_irq[DATA_CORR])
    {
        add_h = HWREG32(ccache_base + SIFIVE_CCACHE_DATECCFIX_HIGH);
        add_l = HWREG32(ccache_base + SIFIVE_CCACHE_DATECCFIX_LOW);
        LOG_E("Data error: 0x%08x.%08x", add_h, add_l);

        /* Reading this register clears the DataError interrupt sig */
        HWREG32(ccache_base + SIFIVE_CCACHE_DATECCFIX_COUNT);
    }
    else if (irq == ccache_irq[DATA_UNCORR])
    {
        add_h = HWREG32(ccache_base + SIFIVE_CCACHE_DATECCFAIL_HIGH);
        add_l = HWREG32(ccache_base + SIFIVE_CCACHE_DATECCFAIL_LOW);
        LOG_E("Data fail: 0x%08x%08x", add_h, add_l);

        /* Reading this register clears the DataFail interrupt sig */
        HWREG32(ccache_base + SIFIVE_CCACHE_DATECCFAIL_COUNT);
    }
}

static void ccache_irq_init(void)
{
    if (!ccache_np)
    {
        return;
    }

    for (int i = 0; i < RT_ARRAY_SIZE(ccache_irq); ++i)
    {
        int irq;

        if (i == DATA_UNCORR && (ccache_quirk & QUIRK_BROKEN_DATA_UNCORR))
        {
            continue;
        }

        irq = rt_ofw_get_irq(ccache_np, i);

        if (irq >= 0)
        {
            rt_hw_interrupt_install(irq, sifive_ccache_isr, ccache_np, "ccache");
            rt_hw_interrupt_umask(irq);

            ccache_irq[i] = irq;
        }
    }
}
INIT_SUBSYS_EXPORT(ccache_irq_init);

static rt_err_t sifive_ccache_ofw_init(struct rt_ofw_node *np,
        const struct rt_ofw_node_id *id)
{
    ccache_quirk = *(rt_ubase_t *)id->data;

    ccache_base = rt_ofw_iomap(np, 0);

    if (!ccache_base)
    {
        return -RT_EIO;
    }

    ccache_np = np;

    if (!rt_dm_cpu_dcache_ops)
    {
        rt_dm_cpu_dcache_ops = &ccache_mgmt;
    }

    return RT_EOK;
}

static rt_ubase_t ccache0_quirk = QUIRK_HAS_CG;
static rt_ubase_t jh7100_quirk = QUIRK_BROKEN_DATA_UNCORR;

static const struct rt_ofw_node_id sifive_ccache_ofw_ids[] =
{
    { .compatible = "sifive,fu540-c000-ccache" },
    { .compatible = "sifive,fu740-c000-ccache" },
    { .compatible = "starfive,jh7100-ccache", .data = &jh7100_quirk },
    { .compatible = "sifive,ccache0", .data = &ccache0_quirk },
    { /* sentinel */ }
};
RT_HWCACHE_OFW_DECLARE(sifive_ccache, sifive_ccache_ofw_ids, sifive_ccache_ofw_init);
