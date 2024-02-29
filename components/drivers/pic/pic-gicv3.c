/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 * 2014-04-03     Grissiom     many enhancements
 * 2018-11-22     Jesven       add rt_hw_ipi_send()
 *                             add rt_hw_ipi_handler_install()
 * 2022-08-24     GuEe-GUI     add pic support
 * 2022-11-07     GuEe-GUI     add v2m support
 * 2023-01-30     GuEe-GUI     add its and espi, eppi, lpi support
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "pic.gicv3"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpu.h>

#include <ioremap.h>
#include <hashmap.h>

#include "pic-gicv3.h"
#include "pic-gic-common.h"

#define FLAGS_WORKAROUND_GICR_WAKER_MSM8996 (1ULL << 0)

static int _init_cpu_id;
static struct gicv3 _gic;
static rt_bool_t _gicv3_eoi_mode_ns = RT_FALSE;
static rt_bool_t _gicv3_arm64_2941627_erratum = RT_FALSE;

enum
{
    SGI_TYPE,
    PPI_TYPE,
    SPI_TYPE,
    EPPI_TYPE,
    ESPI_TYPE,
    LPI_TYPE,

    UNKNOW_TYPE,
};

rt_inline void *gicv3_percpu_redist_base(void)
{
    return _gic.redist_percpu_base[rt_hw_cpu_id()];
}

rt_inline void *gicv3_percpu_redist_sgi_base(void)
{
    return gicv3_percpu_redist_base() + GICR_SGI_OFFSET;
}

static rt_uint16_t *gicv3_dist_espi_reg(rt_uint32_t offset)
{
#define __reg_map_bits 5
#define __reg_map_size (1 << __reg_map_bits)
    static rt_uint16_t reg_map[__reg_map_size] = {};

    int idx = rt_hashmap_32(offset, __reg_map_bits);

    LOG_D("%s ESPI Map<0x%04x> = %2d", "Distributor", offset, idx);

    return &reg_map[idx];
#undef __reg_map_bits
#undef __reg_map_size
}

static void gicv3_wait_for_rwp(void *base, rt_uint32_t rwp_bit)
{
    rt_uint32_t count = 1000000;

    while ((HWREG32(base + GICD_CTLR) & rwp_bit))
    {
        count--;
        if (!count)
        {
            LOG_W("RWP timeout");
            break;
        }

        rt_hw_cpu_relax();
    }
}

rt_inline void gicv3_dist_wait_for_rwp(void)
{
    gicv3_wait_for_rwp(_gic.dist_base, GICD_CTLR_RWP);
}

rt_inline void gicv3_redist_wait_for_rwp(void)
{
    gicv3_wait_for_rwp(_gic.redist_percpu_base[rt_hw_cpu_id()], GICR_CTLR_RWP);
}

static typeof(UNKNOW_TYPE) gicv3_hwirq_type(int hwirq)
{
    typeof(UNKNOW_TYPE) ret;

    switch (hwirq)
    {
    case 0 ... 15:
        ret = SGI_TYPE;
        break;
    case 16 ... 31:
        ret = PPI_TYPE;
        break;
    case 32 ... 1019:
        ret = SPI_TYPE;
        break;
    case GIC_EPPI_BASE_INTID ... (GIC_EPPI_BASE_INTID + 63):
        ret = EPPI_TYPE;
        break;
    case GIC_ESPI_BASE_INTID ... (GIC_ESPI_BASE_INTID + 1023):
        ret = ESPI_TYPE;
        break;
    case 8192 ... RT_GENMASK(23, 0):
        ret = LPI_TYPE;
        break;
    default:
        ret = UNKNOW_TYPE;
        break;
    }

    return ret;
}

static rt_uint32_t gicv3_hwirq_convert_offset_index(int hwirq, rt_uint32_t offset, rt_uint32_t *index)
{
    switch (gicv3_hwirq_type(hwirq))
    {
    case SGI_TYPE:
    case PPI_TYPE:
    case SPI_TYPE:
        *index = hwirq;
        break;
    case EPPI_TYPE:
        /* EPPI range (GICR_IPRIORITYR<n>E) is contiguousto the PPI (GICR_IPRIORITYR<n>) range in the registers */
        *index = hwirq - GIC_EPPI_BASE_INTID + 32;
        break;
    case ESPI_TYPE:
        *index = hwirq - GIC_ESPI_BASE_INTID;
        offset = *gicv3_dist_espi_reg(offset);
        break;
    default:
        *index = hwirq;
        break;
    }

    return offset;
}

rt_inline rt_bool_t gicv3_hwirq_in_redist(int hwirq)
{
    switch (gicv3_hwirq_type(hwirq))
    {
    case SGI_TYPE:
    case PPI_TYPE:
    case EPPI_TYPE:
        return RT_TRUE;
    default:
        return RT_FALSE;
    }
}

static void *gicv3_hwirq_reg_base(int hwirq, rt_uint32_t offset, rt_uint32_t *index)
{
    void *base;

    if (gicv3_hwirq_in_redist(hwirq))
    {
        base = gicv3_percpu_redist_sgi_base();
    }
    else
    {
        base = _gic.dist_base;
    }

    return base + gicv3_hwirq_convert_offset_index(hwirq, offset, index);
}

static void gicv3_hwirq_poke(int hwirq, rt_uint32_t offset)
{
    rt_uint32_t index;
    void *base = gicv3_hwirq_reg_base(hwirq, offset, &index);

    HWREG32(base + (index / 32) * 4) = 1 << (index % 32);
}

static void gicv3_dist_init(void)
{
    rt_uint32_t i;
    rt_uint64_t affinity;
    void *base = _gic.dist_base;
    rt_ubase_t mpidr = rt_cpu_mpidr_table[_init_cpu_id = rt_hw_cpu_id()];

    _gic.line_nr = rt_min(GICD_TYPER_SPIS(_gic.gicd_typer), 1020U);
    _gic.espi_nr = GICD_TYPER_ESPIS(_gic.gicd_typer);

    LOG_D("%d SPIs implemented", _gic.line_nr - 32);
    LOG_D("%d Extended SPIs implemented", _gic.espi_nr);

    /* Disable the distributor */
    HWREG32(base + GICD_CTLR) = 0;
    gicv3_dist_wait_for_rwp();

    /* Non-secure Group-1 */
    for (i = 32; i < _gic.line_nr; i += 32)
    {
        HWREG32(base + GICD_IGROUPR + i / 8) = RT_UINT32_MAX;
    }

    /* Disable, clear, group */
    for (i = 0; i < _gic.espi_nr; i += 4)
    {
        HWREG32(base + GICD_IPRIORITYRnE + i) = GICD_INT_DEF_PRI_X4;

        if (!(i % 16))
        {
            HWREG32(base + GICD_ICFGRnE + i / 4) = 0;

            if (!(i % 32))
            {
                HWREG32(base + GICD_ICENABLERnE + i / 8) = RT_UINT32_MAX;
                HWREG32(base + GICD_ICACTIVERnE + i / 8) = RT_UINT32_MAX;
                HWREG32(base + GICD_IGROUPRnE + i / 8) = RT_UINT32_MAX;
            }
        }
    }

    gic_common_dist_config(base, _gic.line_nr, RT_NULL, RT_NULL);

    /* Enable the distributor */
    HWREG32(base + GICD_CTLR) = GICD_CTLR_ARE_NS | GICD_CTLR_ENABLE_G1A | GICD_CTLR_ENABLE_G1;
    gicv3_dist_wait_for_rwp();

    affinity = ((rt_uint64_t)MPIDR_AFFINITY_LEVEL(mpidr, 3) << 32 |
                            MPIDR_AFFINITY_LEVEL(mpidr, 2) << 16 |
                            MPIDR_AFFINITY_LEVEL(mpidr, 1) << 8  |
                            MPIDR_AFFINITY_LEVEL(mpidr, 0));

    /* Set all global interrupts to this CPU only. */
    for (i = 32; i < _gic.line_nr; ++i)
    {
        HWREG64(base + GICD_IROUTER + i * 8) = affinity;
    }

    for (i = 0; i < _gic.espi_nr; ++i)
    {
        HWREG64(base + GICD_IROUTERnE + i * 8) = affinity;
    }

    if (GICD_TYPER_NUM_LPIS(_gic.gicd_typer))
    {
        /* Max LPI = 8192 + Math.pow(2, num_LPIs + 1) - 1 */
        rt_size_t num_lpis = (1 << (GICD_TYPER_NUM_LPIS(_gic.gicd_typer) + 1)) + 1;

        _gic.lpi_nr = rt_min_t(int, num_lpis, 1 << GICD_TYPER_ID_BITS(_gic.gicd_typer));
    }
    else
    {
        _gic.lpi_nr = 1 << GICD_TYPER_ID_BITS(_gic.gicd_typer);
    }

    /* SPI + eSPI + LPIs */
    _gic.irq_nr = _gic.line_nr - 32 + _gic.espi_nr + _gic.lpi_nr;
}

static void gicv3_redist_enable(rt_bool_t enable)
{
    void *base;
    rt_uint32_t count = 1000000, waker;

    do {
        if (_gic.flags & FLAGS_WORKAROUND_GICR_WAKER_MSM8996)
        {
            break;
        }

        base = gicv3_percpu_redist_base();

        waker = HWREG32(base + GICR_WAKER);
        if (enable)
        {
            waker &= ~GICR_WAKER_ProcessorSleep;
        }
        else
        {
            waker |= GICR_WAKER_ProcessorSleep;
        }
        HWREG32(base + GICR_WAKER) = waker;

        if (!enable && !(HWREG32(base + GICR_WAKER) & GICR_WAKER_ProcessorSleep))
        {
            break;
        }

        while ((HWREG32(base + GICR_WAKER) & GICR_WAKER_ChildrenAsleep) != 0)
        {
            if (count-- == 0)
            {
                LOG_E("%s failed to %s", "Redistributor", enable ? "wakeup" : "sleep");
                break;
            }
        }
    } while (0);
}

static void gicv3_redist_init(void)
{
    void *base;
    rt_uint32_t affinity;
    int cpu_id = rt_hw_cpu_id();
    rt_bool_t find_ok = RT_TRUE;
    rt_uint64_t mpidr = rt_cpu_mpidr_table[cpu_id], gicr_typer;

    affinity = (MPIDR_AFFINITY_LEVEL(mpidr, 3) << 24 |
                MPIDR_AFFINITY_LEVEL(mpidr, 2) << 16 |
                MPIDR_AFFINITY_LEVEL(mpidr, 1) << 8 |
                MPIDR_AFFINITY_LEVEL(mpidr, 0));

    for (int i = 0; i < _gic.redist_regions_nr; ++i)
    {
        base = _gic.redist_regions[i].base;

        do {
            gicr_typer = HWREG64(base + GICR_TYPER);

            if ((gicr_typer >> 32) == affinity)
            {
                rt_size_t ppi_nr = _gic.percpu_ppi_nr[cpu_id];
                rt_size_t typer_nr_ppis = GICR_TYPER_NR_PPIS(gicr_typer);

                _gic.percpu_ppi_nr[cpu_id] = rt_min(typer_nr_ppis, ppi_nr);
                _gic.redist_percpu_base[cpu_id] = base;

                find_ok = RT_TRUE;
                break;
            }

            if (_gic.redist_stride)
            {
                base += _gic.redist_stride;
            }
            else
            {
                base += GICR_RD_BASE_SIZE + GICR_SGI_BASE_SIZE;

                if (gicr_typer & GICR_TYPER_VLPIS)
                {
                    base += GICR_VLPI_BASE_SIZE + GICR_RESERVED_SIZE;
                }
            }
        } while (!(gicr_typer & GICR_TYPER_LAST));

        if (find_ok)
        {
            break;
        }
    }

    if (find_ok)
    {
        gicv3_redist_enable(RT_TRUE);
    }
}

static void gicv3_cpu_init(void)
{
    void *base;
    rt_size_t ppi_nr;
    rt_uint64_t value;
    int cpu_id = rt_hw_cpu_id();
#ifdef ARCH_SUPPORT_HYP
    _gicv3_eoi_mode_ns = RT_TRUE;
#endif

    base = gicv3_percpu_redist_sgi_base();
    ppi_nr = _gic.percpu_ppi_nr[cpu_id] + 16;

    for (rt_uint32_t i = 0; i < ppi_nr; i += 32)
    {
        HWREG32(base + GICR_IGROUPR0 + i / 8) = RT_UINT32_MAX;
    }

    gic_common_cpu_config(base, ppi_nr, (void *)gicv3_redist_wait_for_rwp, &_gic.parent);

    read_gicreg(ICC_SRE_SYS, value);
    value |= (1 << 0);
    write_gicreg(ICC_SRE_SYS, value);
    rt_hw_isb();

    write_gicreg(ICC_PMR_SYS, 0xff);

    /* Enable group1 interrupt */
    write_gicreg(ICC_IGRPEN1_SYS, 1);

    write_gicreg(ICC_BPR1_SYS, 0);

    /*
     * ICC_BPR0_EL1 determines the preemption group for both Group 0 and Group 1
     * interrupts.
     * Targeted SGIs with affinity level 0 values of 0 - 255 are supported.
     */
    value = ICC_CTLR_EL1_RSS | ICC_CTLR_EL1_CBPR_MASK;
    if (_gicv3_eoi_mode_ns)
    {
        value |= ICC_CTLR_EL1_EOImode_drop;
    }
    write_gicreg(ICC_CTLR_SYS, value);
}

static rt_err_t gicv3_irq_init(struct rt_pic *pic)
{
    gicv3_redist_init();
    gicv3_cpu_init();

    return RT_EOK;
}

static void gicv3_irq_ack(struct rt_pic_irq *pirq)
{
    if (!_gicv3_eoi_mode_ns)
    {
        write_gicreg(ICC_EOIR1_SYS, pirq->hwirq);
        rt_hw_isb();
    }
}

static void gicv3_irq_mask(struct rt_pic_irq *pirq)
{
    int hwirq = pirq->hwirq;

    gicv3_hwirq_poke(hwirq, GICD_ICENABLER);

    if (gicv3_hwirq_in_redist(hwirq))
    {
        gicv3_redist_wait_for_rwp();
    }
    else
    {
        gicv3_dist_wait_for_rwp();
    }
}

static void gicv3_irq_unmask(struct rt_pic_irq *pirq)
{
    int hwirq = pirq->hwirq;

    gicv3_hwirq_poke(hwirq, GICD_ISENABLER);
}

static void gicv3_irq_eoi(struct rt_pic_irq *pirq)
{
    if (_gicv3_eoi_mode_ns)
    {
        int hwirq = pirq->hwirq;

        if (hwirq < 8192)
        {
            write_gicreg(ICC_EOIR1_SYS, hwirq);
            rt_hw_isb();

            if (!_gicv3_arm64_2941627_erratum)
            {
                write_gicreg(ICC_DIR_SYS, hwirq);
                rt_hw_isb();
            }
        }
    }
}

static rt_err_t gicv3_irq_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority)
{
    void *base;
    int hwirq = pirq->hwirq;
    rt_uint32_t index, offset;

    if (gicv3_hwirq_in_redist(hwirq))
    {
        base = gicv3_percpu_redist_sgi_base();
    }
    else
    {
        base = _gic.dist_base;
    }

    offset = gicv3_hwirq_convert_offset_index(hwirq, GICD_IPRIORITYR, &index);
    HWREG8(base + offset + index) = priority;

    return RT_EOK;
}

static rt_err_t gicv3_irq_set_affinity(struct rt_pic_irq *pirq, rt_bitmap_t *affinity)
{
    rt_err_t ret = RT_EOK;
    rt_uint64_t val;
    rt_ubase_t mpidr;
    rt_uint32_t offset, index;
    int hwirq = pirq->hwirq, cpu_id = rt_bitmap_next_set_bit(affinity, 0, RT_CPUS_NR);

    mpidr = rt_cpu_mpidr_table[cpu_id];

    offset = gicv3_hwirq_convert_offset_index(hwirq, GICD_IROUTER, &index);
    val = ((rt_uint64_t)MPIDR_AFFINITY_LEVEL(mpidr, 3) << 32 |
                       MPIDR_AFFINITY_LEVEL(mpidr, 2) << 16 |
                       MPIDR_AFFINITY_LEVEL(mpidr, 1) << 8  |
                       MPIDR_AFFINITY_LEVEL(mpidr, 0));

    HWREG64(_gic.dist_base + offset + (index * 8)) = val;

    return ret;
}

static rt_err_t gicv3_irq_set_triger_mode(struct rt_pic_irq *pirq, rt_uint32_t mode)
{
    void *base;
    rt_err_t ret = RT_EOK;
    int hwirq = pirq->hwirq;
    rt_uint32_t index, offset;

    if (hwirq > 15)
    {
        if (gicv3_hwirq_in_redist(hwirq))
        {
            base = gicv3_percpu_redist_sgi_base();
        }
        else
        {
            base = _gic.dist_base;
        }

        offset = gicv3_hwirq_convert_offset_index(hwirq, GICD_ICFGR, &index);

        ret = gic_common_configure_irq(base + offset, hwirq, mode, RT_NULL, RT_NULL);
    }
    else
    {
        ret = -RT_ENOSYS;
    }

    return ret;
}

static void gicv3_irq_send_ipi(struct rt_pic_irq *pirq, rt_bitmap_t *cpumask)
{
#define __mpidr_to_sgi_affinity(cluster_id, level)  \
    (MPIDR_AFFINITY_LEVEL(cluster_id, level) << ICC_SGI1R_AFFINITY_##level##_SHIFT)
    int cpu_id, last_cpu_id, limit;
    rt_uint64_t initid, range_sel, target_list, cluster_id;

    range_sel = 0;
    initid = ((pirq->hwirq) << ICC_SGI1R_SGI_ID_SHIFT);

    rt_bitmap_for_each_set_bit(cpumask, cpu_id, RT_CPUS_NR)
    {
        rt_uint64_t mpidr = rt_cpu_mpidr_table[cpu_id];

        cluster_id = mpidr & (~MPIDR_LEVEL_MASK);
        target_list = 1 << ((mpidr & MPIDR_LEVEL_MASK) % ICC_SGI1R_TARGET_LIST_MAX);
        limit = rt_min(cpu_id + ICC_SGI1R_TARGET_LIST_MAX, RT_CPUS_NR);

        last_cpu_id = cpu_id;
        rt_bitmap_for_each_set_bit_from(cpumask, cpu_id, cpu_id, limit)
        {
            rt_uint64_t mpidr = rt_cpu_mpidr_table[cpu_id];

            if (cluster_id != (mpidr & (~MPIDR_LEVEL_MASK)))
            {
                range_sel = 0;
                /* Don't break next cpuid */
                cpu_id = last_cpu_id;
                break;
            }

            last_cpu_id = cpu_id;
            target_list |= 1 << ((mpidr & MPIDR_LEVEL_MASK) % ICC_SGI1R_TARGET_LIST_MAX);
        }

        rt_hw_dsb();
        write_gicreg(ICC_SGI1R_SYS,
                __mpidr_to_sgi_affinity(cluster_id, 3) |
                (range_sel << ICC_SGI1R_RS_SHIFT) |
                __mpidr_to_sgi_affinity(cluster_id, 2) |
                initid |
                __mpidr_to_sgi_affinity(cluster_id, 1) |
                target_list);
        rt_hw_isb();

        ++range_sel;
    }
#undef __mpidr_to_sgi_affinity
}

static int gicv3_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    struct rt_pic_irq *pirq;
    int irq, hwirq_type, irq_index;

    hwirq_type = gicv3_hwirq_type(hwirq);
    if (hwirq_type != LPI_TYPE)
    {
        irq_index = hwirq - GIC_SGI_NR;
    }
    else
    {
        irq_index = _gic.irq_nr - _gic.lpi_nr + hwirq - 8192;
    }
    pirq = rt_pic_find_irq(pic, irq_index);

    if (pirq && hwirq >= GIC_SGI_NR)
    {
        pirq->mode = mode;

        switch (gicv3_hwirq_type(hwirq))
        {
        case SPI_TYPE:
        case ESPI_TYPE:
            pirq->priority = GICD_INT_DEF_PRI;
            rt_bitmap_set_bit(pirq->affinity, _init_cpu_id);
        default:
            break;
        }

        irq = rt_pic_config_irq(pic, irq_index, hwirq);

        if (irq >= 0 && mode != RT_IRQ_MODE_LEVEL_HIGH)
        {
            gicv3_irq_set_triger_mode(pirq, mode);
        }
    }
    else
    {
        irq = -1;
    }

    return irq;
}

static rt_err_t gicv3_irq_parse(struct rt_pic *pic, struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    rt_err_t err = RT_EOK;

    if (args->args_count == 3)
    {
        out_pirq->mode = args->args[2] & RT_IRQ_MODE_MASK;

        switch (args->args[0])
        {
        case 0:
            /* SPI */
            out_pirq->hwirq = args->args[1] + 32;
        break;
        case 1:
            /* PPI */
            out_pirq->hwirq = args->args[1] + 16;
        break;
        case 2:
            /* ESPI */
            out_pirq->hwirq = args->args[1] + GIC_ESPI_BASE_INTID;
            break;
        case 3:
            /* EPPI */
            out_pirq->hwirq = args->args[1] + GIC_EPPI_BASE_INTID;
            break;
        case GIC_IRQ_TYPE_LPI:
            /* LPI */
            out_pirq->hwirq = args->args[1];
            break;
        case GIC_IRQ_TYPE_PARTITION:

            out_pirq->hwirq = args->args[1];

            if (args->args[1] >= 16)
            {
                out_pirq->hwirq += GIC_EPPI_BASE_INTID - 16;
            }
            else
            {
                out_pirq->hwirq += 16;
            }
            break;
        default:
            err = -RT_ENOSYS;
        break;
        }
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static struct rt_pic_ops gicv3_ops =
{
    .name = "GICv3",
    .irq_init = gicv3_irq_init,
    .irq_ack = gicv3_irq_ack,
    .irq_mask = gicv3_irq_mask,
    .irq_unmask = gicv3_irq_unmask,
    .irq_eoi = gicv3_irq_eoi,
    .irq_set_priority = gicv3_irq_set_priority,
    .irq_set_affinity = gicv3_irq_set_affinity,
    .irq_set_triger_mode = gicv3_irq_set_triger_mode,
    .irq_send_ipi = gicv3_irq_send_ipi,
    .irq_map = gicv3_irq_map,
    .irq_parse = gicv3_irq_parse,
};

static rt_bool_t gicv3_handler(void *data)
{
    rt_bool_t res = RT_FALSE;
    int hwirq;
    struct gicv3 *gic = data;

    read_gicreg(ICC_IAR1_SYS, hwirq);

    if (!(hwirq >= 1020 && hwirq <= 1023))
    {
        struct rt_pic_irq *pirq;

        if (hwirq < GIC_SGI_NR)
        {
            rt_hw_rmb();

            pirq = rt_pic_find_ipi(&gic->parent, hwirq);
        }
        else
        {
            pirq = rt_pic_find_irq(&gic->parent, hwirq - GIC_SGI_NR);
        }

        gicv3_irq_ack(pirq);

        rt_pic_handle_isr(pirq);

        gicv3_irq_eoi(pirq);

        res = RT_TRUE;
    }

    return res;
}

static rt_err_t gicv3_enable_quirk_msm8996(void *data)
{
    struct gicv3 *gic = data;

    gic->flags |= FLAGS_WORKAROUND_GICR_WAKER_MSM8996;

    return RT_EOK;
}

static rt_err_t gicv3_enable_quirk_arm64_2941627(void *data)
{
    _gicv3_arm64_2941627_erratum = RT_TRUE;
    return RT_EOK;
}

static const struct gic_quirk _gicv3_quirks[] =
{
    {
        .desc       = "GICv3: Qualcomm MSM8996 broken firmware",
        .compatible = "qcom,msm8996-gic-v3",
        .init       = gicv3_enable_quirk_msm8996,
    },
    {
        /* GIC-700: 2941627 workaround - IP variant [0,1] */
        .desc       = "GICv3: ARM64 erratum 2941627",
        .iidr       = 0x0400043b,
        .iidr_mask  = 0xff0e0fff,
        .init       = gicv3_enable_quirk_arm64_2941627,
    },
    {
        /* GIC-700: 2941627 workaround - IP variant [2] */
        .desc       = "GICv3: ARM64 erratum 2941627",
        .iidr       = 0x0402043b,
        .iidr_mask  = 0xff0f0fff,
        .init       = gicv3_enable_quirk_arm64_2941627,
    },
    { /* sentinel */ }
};

static rt_err_t gicv3_iomap_init(rt_uint64_t *regs)
{
    rt_err_t ret = RT_EOK;
    int idx;
    char *name;

    do {
        /* GICD->GICR */
        _gic.dist_size = regs[1];
        _gic.dist_base = rt_ioremap((void *)regs[0], _gic.dist_size);
        if (!_gic.dist_base)
        {
            name = "Distributor";
            idx = 0;
            ret = -RT_ERROR;
            break;
        }

        name = "Redistributor";

        _gic.redist_regions = rt_malloc(sizeof(_gic.redist_regions[0]) * _gic.redist_regions_nr);
        if (!_gic.redist_regions)
        {
            idx = -1;
            ret = -RT_ENOMEM;
            LOG_E("No memory to save %s", name);
            break;
        }

        for (int i = 0, off = 2; i < _gic.redist_regions_nr; ++i)
        {
            void *base = (void *)regs[off++];
            rt_size_t size = regs[off++];
            _gic.redist_regions[i].size = size;
            _gic.redist_regions[i].base = rt_ioremap(base, size);
            _gic.redist_regions[i].base_phy = base;

            if (!base)
            {
                idx = 1;
                ret = -RT_ERROR;
                break;
            }
        }

        if (ret)
        {
            break;
        }

        /* ArchRev[4:7] */
        _gic.version = HWREG32(_gic.dist_base + GICD_PIDR2) >> 4;
    } while (0);

    if (ret && idx >= 0)
    {
        RT_UNUSED(name);
        LOG_E("%s IO[%p, %p] map fail", name[idx], regs[idx * 2], regs[idx * 2 + 1]);
    }

    return ret;
}

static void gicv3_init(void)
{
#define __dist_espi_regs_do(func, expr, ...) \
    __VA_ARGS__(*func(GICD_IGROUPR)    expr GICD_IGROUPRnE);    \
    __VA_ARGS__(*func(GICD_ISENABLER)  expr GICD_ISENABLERnE);  \
    __VA_ARGS__(*func(GICD_ICENABLER)  expr GICD_ICENABLERnE);  \
    __VA_ARGS__(*func(GICD_ISPENDR)    expr GICD_ISPENDRnE);    \
    __VA_ARGS__(*func(GICD_ICPENDR)    expr GICD_ICPENDRnE);    \
    __VA_ARGS__(*func(GICD_ISACTIVER)  expr GICD_ISACTIVERnE);  \
    __VA_ARGS__(*func(GICD_ICACTIVER)  expr GICD_ICACTIVERnE);  \
    __VA_ARGS__(*func(GICD_IPRIORITYR) expr GICD_IPRIORITYRnE); \
    __VA_ARGS__(*func(GICD_ICFGR)      expr GICD_ICFGRnE);      \
    __VA_ARGS__(*func(GICD_IROUTER)    expr GICD_IROUTERnE);

    /* Map registers for ESPI */
    __dist_espi_regs_do(gicv3_dist_espi_reg, =);
    __dist_espi_regs_do(gicv3_dist_espi_reg, ==, RT_ASSERT);
#undef __dist_espi_regs_do

    _gic.gicd_typer = HWREG32(_gic.dist_base + GICD_TYPER);

    gic_common_init_quirk_hw(HWREG32(_gic.dist_base + GICD_IIDR), _gicv3_quirks, &_gic.parent);
    gicv3_dist_init();

    _gic.parent.priv_data = &_gic;
    _gic.parent.ops = &gicv3_ops;

    rt_pic_linear_irq(&_gic.parent, _gic.irq_nr - GIC_SGI_NR);
    gic_common_sgi_config(_gic.dist_base, &_gic.parent, 0);

    rt_pic_add_traps(gicv3_handler, &_gic);

    rt_pic_user_extends(&_gic.parent);
}

static void gicv3_init_fail(void)
{
    if (_gic.dist_base)
    {
        rt_iounmap(_gic.dist_base);
    }
    if (_gic.redist_regions)
    {
        for (int i = 0; i < _gic.redist_regions_nr; ++i)
        {
            if (_gic.redist_regions[i].base)
            {
                rt_iounmap(_gic.redist_regions[i].base);
            }
        }

        rt_free(_gic.redist_regions);
    }

    rt_memset(&_gic, 0, sizeof(_gic));
}

static rt_err_t gicv3_ofw_init(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err = RT_EOK;

    do {
        rt_size_t reg_nr_max;
        rt_err_t msi_init = -RT_ENOSYS;
        rt_uint32_t redist_regions_nr;
        rt_uint64_t *regs, redist_stride;

        if (rt_ofw_prop_read_u32(np, "#redistributor-regions", &redist_regions_nr))
        {
            redist_regions_nr = 1;
        }

        /* GICD + n * GICR */
        reg_nr_max = 2 + (2 * redist_regions_nr);
        regs = rt_calloc(1, sizeof(rt_uint64_t) * reg_nr_max);

        if (!regs)
        {
            err = -RT_ENOMEM;
            break;
        }

        rt_ofw_get_address_array(np, reg_nr_max, regs);
        _gic.redist_regions_nr = redist_regions_nr;

        err = gicv3_iomap_init(regs);
        rt_free(regs);

        if (err)
        {
            break;
        }

        if (_gic.version != 3 && _gic.version != 4)
        {
            LOG_E("Version = %d is not support", _gic.version);
            err = -RT_EINVAL;
            break;
        }

        if (rt_ofw_prop_read_u64(np, "redistributor-stride", &redist_stride))
        {
            redist_stride = 0;
        }
        _gic.redist_stride = redist_stride;

        gic_common_init_quirk_ofw(np, _gicv3_quirks, &_gic.parent);
        gicv3_init();

        rt_ofw_data(np) = &_gic.parent;

    #ifdef RT_PIC_ARM_GIC_V3_ITS
        msi_init = gicv3_its_ofw_probe(np, id);
    #endif

        /* V2M or ITS only */
        if (msi_init)
        {
        #ifdef RT_PIC_ARM_GIC_V2M
            gicv2m_ofw_probe(np, id);
        #endif
        }
    } while (0);

    if (err)
    {
        gicv3_init_fail();
    }

    return err;
}

static const struct rt_ofw_node_id gicv3_ofw_ids[] =
{
    { .compatible = "arm,gic-v3" },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(gicv3, gicv3_ofw_ids, gicv3_ofw_init);
