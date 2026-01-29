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
#include <rtdevice.h>

#define DBG_TAG "pic.aplic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <csr.h>
#include <cpu.h>
#include "pic-riscv-imsic.h"

#define APLIC_MAX_IDC                   RT_BIT(14)
#define APLIC_MAX_SOURCE                1024

#define APLIC_DOMAINCFG                 0x0000
#define APLIC_DOMAINCFG_RDONLY          0x80000000
#define APLIC_DOMAINCFG_IE              RT_BIT(8)
#define APLIC_DOMAINCFG_DM              RT_BIT(2)
#define APLIC_DOMAINCFG_BE              RT_BIT(0)

#define APLIC_SOURCECFG_BASE            0x0004
#define APLIC_SOURCECFG_D               RT_BIT(10)
#define APLIC_SOURCECFG_CHILDIDX_MASK   0x000003ff
#define APLIC_SOURCECFG_SM_MASK         0x00000007
#define APLIC_SOURCECFG_SM_INACTIVE     0x0
#define APLIC_SOURCECFG_SM_DETACH       0x1
#define APLIC_SOURCECFG_SM_EDGE_RISE    0x4
#define APLIC_SOURCECFG_SM_EDGE_FALL    0x5
#define APLIC_SOURCECFG_SM_LEVEL_HIGH   0x6
#define APLIC_SOURCECFG_SM_LEVEL_LOW    0x7

#define APLIC_MMSICFGADDR               0x1bc0
#define APLIC_MMSICFGADDRH              0x1bc4
#define APLIC_SMSICFGADDR               0x1bc8
#define APLIC_SMSICFGADDRH              0x1bcc

#ifdef ARCH_RISCV_M_MODE
#define APLIC_xMSICFGADDR               APLIC_MMSICFGADDR
#define APLIC_xMSICFGADDRH              APLIC_MMSICFGADDRH
#else
#define APLIC_xMSICFGADDR               APLIC_SMSICFGADDR
#define APLIC_xMSICFGADDRH              APLIC_SMSICFGADDRH
#endif

#define APLIC_xMSICFGADDRH_L            RT_BIT(31)
#define APLIC_xMSICFGADDRH_HHXS_MASK    0x1f
#define APLIC_xMSICFGADDRH_HHXS_SHIFT   24
#define APLIC_xMSICFGADDRH_HHXS         (APLIC_xMSICFGADDRH_HHXS_MASK << APLIC_xMSICFGADDRH_HHXS_SHIFT)
#define APLIC_xMSICFGADDRH_LHXS_MASK    0x7
#define APLIC_xMSICFGADDRH_LHXS_SHIFT   20
#define APLIC_xMSICFGADDRH_LHXS         (APLIC_xMSICFGADDRH_LHXS_MASK << APLIC_xMSICFGADDRH_LHXS_SHIFT)
#define APLIC_xMSICFGADDRH_HHXW_MASK    0x7
#define APLIC_xMSICFGADDRH_HHXW_SHIFT   16
#define APLIC_xMSICFGADDRH_HHXW         (APLIC_xMSICFGADDRH_HHXW_MASK << APLIC_xMSICFGADDRH_HHXW_SHIFT)
#define APLIC_xMSICFGADDRH_LHXW_MASK    0xf
#define APLIC_xMSICFGADDRH_LHXW_SHIFT   12
#define APLIC_xMSICFGADDRH_LHXW         (APLIC_xMSICFGADDRH_LHXW_MASK << APLIC_xMSICFGADDRH_LHXW_SHIFT)
#define APLIC_xMSICFGADDRH_BAPPN_MASK   0xfff
#define APLIC_xMSICFGADDRH_BAPPN_SHIFT  0
#define APLIC_xMSICFGADDRH_BAPPN        (APLIC_xMSICFGADDRH_BAPPN_MASK << APLIC_xMSICFGADDRH_BAPPN_SHIFT)

#define APLIC_xMSICFGADDR_PPN_SHIFT     12

#define APLIC_xMSICFGADDR_PPN_HART(__lhxs)  \
        (RT_BIT(__lhxs) - 1)

#define APLIC_xMSICFGADDR_PPN_LHX_MASK(__lhxw)  \
        (RT_BIT(__lhxw) - 1)
#define APLIC_xMSICFGADDR_PPN_LHX_SHIFT(__lhxs) \
        ((__lhxs))
#define APLIC_xMSICFGADDR_PPN_LHX(__lhxw, __lhxs) \
        (APLIC_xMSICFGADDR_PPN_LHX_MASK(__lhxw) << APLIC_xMSICFGADDR_PPN_LHX_SHIFT(__lhxs))

#define APLIC_xMSICFGADDR_PPN_HHX_MASK(__hhxw) \
        (RT_BIT(__hhxw) - 1)
#define APLIC_xMSICFGADDR_PPN_HHX_SHIFT(__hhxs) \
        ((__hhxs) + APLIC_xMSICFGADDR_PPN_SHIFT)
#define APLIC_xMSICFGADDR_PPN_HHX(__hhxw, __hhxs) \
        (APLIC_xMSICFGADDR_PPN_HHX_MASK(__hhxw) << APLIC_xMSICFGADDR_PPN_HHX_SHIFT(__hhxs))

#define APLIC_IRQBITS_PER_REG           32

#define APLIC_SETIP_BASE                0x1c00
#define APLIC_SETIPNUM                  0x1cdc

#define APLIC_CLRIP_BASE                0x1d00
#define APLIC_CLRIPNUM                  0x1ddc

#define APLIC_SETIE_BASE                0x1e00
#define APLIC_SETIENUM                  0x1edc

#define APLIC_CLRIE_BASE                0x1f00
#define APLIC_CLRIENUM                  0x1fdc

#define APLIC_SETIPNUM_LE               0x2000
#define APLIC_SETIPNUM_BE               0x2004

#define APLIC_GENMSI                    0x3000

#define APLIC_TARGET_BASE               0x3004
#define APLIC_TARGET_HART_IDX_SHIFT     18
#define APLIC_TARGET_HART_IDX_MASK      0x3fff
#define APLIC_TARGET_HART_IDX           (APLIC_TARGET_HART_IDX_MASK << APLIC_TARGET_HART_IDX_SHIFT)
#define APLIC_TARGET_GUEST_IDX_SHIFT    12
#define APLIC_TARGET_GUEST_IDX_MASK     0x3f
#define APLIC_TARGET_GUEST_IDX          (APLIC_TARGET_GUEST_IDX_MASK << APLIC_TARGET_GUEST_IDX_SHIFT)
#define APLIC_TARGET_IPRIO_SHIFT        0
#define APLIC_TARGET_IPRIO_MASK         0xff
#define APLIC_TARGET_IPRIO              (APLIC_TARGET_IPRIO_MASK << APLIC_TARGET_IPRIO_SHIFT)
#define APLIC_TARGET_EIID_SHIFT         0
#define APLIC_TARGET_EIID_MASK          0x7ff
#define APLIC_TARGET_EIID               (APLIC_TARGET_EIID_MASK << APLIC_TARGET_EIID_SHIFT)

#define APLIC_IDC_BASE                  0x4000
#define APLIC_IDC_SIZE                  32

#define APLIC_IDC_IDELIVERY             0x00

#define APLIC_IDC_IFORCE                0x04

#define APLIC_IDC_ITHRESHOLD            0x08

#define APLIC_IDC_TOPI                  0x18
#define APLIC_IDC_TOPI_ID_SHIFT         16
#define APLIC_IDC_TOPI_ID_MASK          0x3ff
#define APLIC_IDC_TOPI_ID               (APLIC_IDC_TOPI_ID_MASK << APLIC_IDC_TOPI_ID_SHIFT)
#define APLIC_IDC_TOPI_PRIO_SHIFT       0
#define APLIC_IDC_TOPI_PRIO_MASK        0xff
#define APLIC_IDC_TOPI_PRIO             (APLIC_IDC_TOPI_PRIO_MASK << APLIC_IDC_TOPI_PRIO_SHIFT)

#define APLIC_IDC_CLAIMI                0x1c

#define APLIC_ENABLE_IDELIVERY          1
#define APLIC_ENABLE_ITHRESHOLD         0

#define APLIC_DEFAULT_PRIORITY          1

struct riscv_aplic_idc
{
    void *regs;
};

struct riscv_aplic_msicfg
{
    rt_ubase_t base_ppn;
    rt_uint32_t hhxs;
    rt_uint32_t hhxw;
    rt_uint32_t lhxs;
    rt_uint32_t lhxw;
};

struct riscv_aplic
{
    struct rt_pic parent;
    struct rt_pic *msi_ic;

    struct rt_ofw_node *np;

    void *regs;
    int parent_irq;
    int init_cpu_id;

    rt_uint32_t gsi_base;
    rt_uint32_t nr_irqs;
    rt_uint32_t nr_idcs;

    struct riscv_aplic_msicfg msicfg;
    struct riscv_aplic_idc idc[RT_CPUS_NR];
};

rt_always_inline rt_uint32_t irq_cfg_offset(int hwirq)
{
    return (hwirq - 1) * sizeof(rt_uint32_t);
}

static void aplic_handler(int hwirq, void *data);

static rt_err_t aplic_irq_init(struct rt_pic *pic)
{
    struct riscv_aplic *aplic = pic->priv_data;

    if (!aplic->msi_ic)
    {
        if (aplic->parent_irq < 0)
        {
            struct rt_ofw_cell_args irq_args;

            if (rt_ofw_parse_irq_cells(aplic->np, 0, &irq_args))
            {
                LOG_E("%s: Parent IRQ is not available", rt_ofw_node_full_name(aplic->np));
                return RT_EOK;
            }

            /* Create mapping */
            irq_args.args[0] = RV_IRQ_EXT;

            aplic->parent_irq = rt_ofw_map_irq(&irq_args);

            rt_hw_interrupt_install(aplic->parent_irq, aplic_handler, aplic, "APLIC");
        }

        rt_pic_irq_unmask(aplic->parent_irq);
    }

    return RT_EOK;
}

static void aplic_irq_unmask(struct rt_pic_irq *pirq)
{
    struct riscv_aplic *aplic = pirq->pic->priv_data;

    HWREG32(aplic->regs + APLIC_SETIENUM) = pirq->hwirq;
}

static void aplic_irq_mask(struct rt_pic_irq *pirq)
{
    struct riscv_aplic *aplic = pirq->pic->priv_data;

    HWREG32(aplic->regs + APLIC_CLRIENUM) = pirq->hwirq;
}

static void aplic_msi_irq_eoi(struct rt_pic_irq *pirq)
{
    struct riscv_aplic *aplic = pirq->pic->priv_data;

    switch (pirq->mode)
    {
    case RT_IRQ_MODE_LEVEL_HIGH:
    case RT_IRQ_MODE_LEVEL_LOW:
        HWREG32(aplic->regs + APLIC_SETIPNUM_LE) = pirq->hwirq;
        break;

    default:
        break;
    }
}

static rt_err_t aplic_direct_irq_set_priority(struct rt_pic_irq *pirq, rt_uint32_t priority)
{
    rt_uint32_t value;
    struct riscv_aplic *aplic = pirq->pic->priv_data;

    /* Start with 1 not 0 */
    priority += 1;
    priority = rt_min_t(rt_uint32_t, priority, APLIC_TARGET_IPRIO_MASK);

    value = HWREG32(aplic->regs + APLIC_TARGET_BASE + irq_cfg_offset(pirq->hwirq));
    value &= ~APLIC_TARGET_IPRIO;
    value |= priority << APLIC_TARGET_IPRIO_SHIFT;

    HWREG32(aplic->regs + APLIC_TARGET_BASE + irq_cfg_offset(pirq->hwirq)) = value;

    return RT_EOK;
}

static rt_err_t aplic_direct_irq_set_affinity(struct rt_pic_irq *pirq, rt_bitmap_t *affinity)
{
    rt_uint32_t value;
    struct riscv_aplic *aplic = pirq->pic->priv_data;

    value = RT_FIELD_PREP(APLIC_TARGET_HART_IDX, rt_bitmap_next_set_bit(affinity, 0, RT_CPUS_NR));
    value |= RT_FIELD_PREP(APLIC_TARGET_IPRIO, pirq->priority);

    HWREG32(aplic->regs + APLIC_TARGET_BASE + irq_cfg_offset(pirq->hwirq)) = value;

    return RT_EOK;
}

static rt_err_t aplic_msi_irq_set_affinity(struct rt_pic_irq *pirq, rt_bitmap_t *affinity)
{
    int cpu_id;
    rt_uint32_t value;
    struct riscv_aplic *aplic = pirq->pic->priv_data;

    cpu_id = rt_bitmap_next_set_bit(affinity, 0, RT_CPUS_NR);
    value = RT_FIELD_PREP(APLIC_TARGET_HART_IDX, cpu_id);
    value |= RT_FIELD_PREP(APLIC_TARGET_EIID, pirq->parent->hwirq);

    HWREG32(aplic->regs + APLIC_TARGET_BASE + irq_cfg_offset(pirq->hwirq)) = value;

    return RT_EOK;
}

static rt_err_t aplic_irq_set_triger_mode(struct rt_pic_irq *pirq, rt_uint32_t mode)
{
    struct riscv_aplic *aplic = pirq->pic->priv_data;

    switch (mode)
    {
    case RT_IRQ_MODE_NONE:
        mode = APLIC_SOURCECFG_SM_INACTIVE;
        break;
    case RT_IRQ_MODE_LEVEL_LOW:
        mode = APLIC_SOURCECFG_SM_LEVEL_LOW;
        break;
    case RT_IRQ_MODE_LEVEL_HIGH:
        mode = APLIC_SOURCECFG_SM_LEVEL_HIGH;
        break;
    case RT_IRQ_MODE_EDGE_FALLING:
        mode = APLIC_SOURCECFG_SM_EDGE_FALL;
        break;
    case RT_IRQ_MODE_EDGE_RISING:
        mode = APLIC_SOURCECFG_SM_EDGE_RISE;
        break;
    default:
        return -RT_EINVAL;
    }

    HWREG32(aplic->regs + APLIC_SOURCECFG_BASE + irq_cfg_offset(pirq->hwirq)) = mode;

    return RT_EOK;
}

static void aplic_msi_irq_write_msg(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg)
{
    rt_ubase_t tppn, tbppn, msg_addr;
    rt_uint32_t group_index, hart_index, guest_index, val;
    struct riscv_aplic *aplic = pirq->pic->priv_data;
    struct riscv_aplic_msicfg *msicfg = &aplic->msicfg;

    /* For zeroed MSI, simply write zero into the target register */
    if (!msg->address_hi && !msg->address_lo && !msg->data)
    {
        HWREG32(aplic->regs + APLIC_TARGET_BASE + irq_cfg_offset(pirq->hwirq)) = 0;
        return;
    }

    /* Sanity check on message data */
    if (msg->data > APLIC_TARGET_EIID_MASK)
    {
        LOG_W("MSI msg out of EIID mask");
    }

    /* Compute target MSI address */
    msg_addr = (((rt_uint64_t)msg->address_hi) << 32) | msg->address_lo;
    tppn = msg_addr >> APLIC_xMSICFGADDR_PPN_SHIFT;

    /* Compute target HART Base PPN */
    tbppn = tppn;
    tbppn &= ~APLIC_xMSICFGADDR_PPN_HART(msicfg->lhxs);
    tbppn &= ~APLIC_xMSICFGADDR_PPN_LHX(msicfg->lhxw, msicfg->lhxs);
    tbppn &= ~APLIC_xMSICFGADDR_PPN_HHX(msicfg->hhxw, msicfg->hhxs);

    /* Compute target group and hart indexes */
    group_index = (tppn >> APLIC_xMSICFGADDR_PPN_HHX_SHIFT(msicfg->hhxs)) &
            APLIC_xMSICFGADDR_PPN_HHX_MASK(msicfg->hhxw);
    hart_index = (tppn >> APLIC_xMSICFGADDR_PPN_LHX_SHIFT(msicfg->lhxs)) &
            APLIC_xMSICFGADDR_PPN_LHX_MASK(msicfg->lhxw);
    hart_index |= (group_index << msicfg->lhxw);

    if (hart_index > APLIC_TARGET_HART_IDX_MASK)
    {
        LOG_W("HART index out of IDX mask");
    }

    /* Compute target guest index */
    guest_index = tppn & APLIC_xMSICFGADDR_PPN_HART(msicfg->lhxs);

    if (guest_index > APLIC_TARGET_GUEST_IDX_MASK)
    {
        LOG_W("Guest index out of IDX mask");
    }

    /* Update IRQ TARGET register */
    val = RT_FIELD_PREP(APLIC_TARGET_HART_IDX, hart_index);
    val |= RT_FIELD_PREP(APLIC_TARGET_GUEST_IDX, guest_index);
    val |= RT_FIELD_PREP(APLIC_TARGET_EIID, msg->data);

    HWREG32(aplic->regs + APLIC_TARGET_BASE + irq_cfg_offset(pirq->hwirq)) = val;
}

static int aplic_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq;
    struct riscv_aplic *aplic = pic->priv_data;
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq);

    if (aplic->msi_ic)
    {
        int msi_irq = aplic->msi_ic->ops->irq_alloc_msi(aplic->msi_ic, RT_NULL);

        if (msi_irq < 0)
        {
            return msi_irq;
        }

        irq = rt_pic_config_irq(pic, hwirq, hwirq);

        rt_pic_cascade(pirq, msi_irq);
    }
    else
    {
        irq = rt_pic_config_irq(pic, hwirq, hwirq);
    }

    rt_memset(pirq->affinity, 0, sizeof(pirq->affinity));

    RT_IRQ_AFFINITY_SET(pirq->affinity, aplic->init_cpu_id);
    pic->ops->irq_set_affinity(pirq, pirq->affinity);

    pirq->mode = mode;
    pic->ops->irq_set_triger_mode(pirq, mode);

    return irq;
}

static rt_err_t aplic_irq_parse(struct rt_pic *pic, struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    struct riscv_aplic *aplic = pic->priv_data;

    if (args->args_count < 2 || !args->args[0])
    {
        return -RT_EINVAL;
    }

    out_pirq->hwirq = args->args[0] - aplic->gsi_base;
    out_pirq->mode = args->args[1] & RT_IRQ_MODE_MASK;

    return RT_EOK;
}

const static struct rt_pic_ops aplic_direct_ops =
{
    .name = "APLIC-DIRECT",
    .irq_init = aplic_irq_init,
    .irq_mask = aplic_irq_mask,
    .irq_unmask = aplic_irq_unmask,
    .irq_set_priority = aplic_direct_irq_set_priority,
    .irq_set_affinity = aplic_direct_irq_set_affinity,
    .irq_set_triger_mode = aplic_irq_set_triger_mode,
    .irq_map = aplic_irq_map,
    .irq_parse = aplic_irq_parse,
};

const static struct rt_pic_ops aplic_msi_ops =
{
    .name = "APLIC-MSI",
    .irq_init = aplic_irq_init,
    .irq_mask = aplic_irq_mask,
    .irq_unmask = aplic_irq_unmask,
    .irq_eoi = aplic_msi_irq_eoi,
    .irq_set_affinity = aplic_msi_irq_set_affinity,
    .irq_set_triger_mode = aplic_irq_set_triger_mode,
    .irq_write_msi_msg = aplic_msi_irq_write_msg,
    .irq_map = aplic_irq_map,
    .irq_parse = aplic_irq_parse,
    .flags = RT_PIC_F_IRQ_ROUTING,
};

static void aplic_handler(int hwirq, void *data)
{
    struct rt_pic_irq *pirq;
    struct riscv_aplic *aplic = data;
    struct riscv_aplic_idc *idc = &aplic->idc[rt_hw_cpu_id()];

    while ((hwirq = HWREG32(idc->regs + APLIC_IDC_CLAIMI)))
    {
        hwirq >>= APLIC_IDC_TOPI_ID_SHIFT;

        pirq = rt_pic_find_irq(&aplic->parent, hwirq);

        rt_pic_handle_isr(pirq);
    }
}

static rt_err_t aplic_ofw_init(struct rt_ofw_node *np, const struct rt_ofw_node_id *id)
{
    rt_err_t err;
    rt_uint32_t val;
    struct rt_ofw_node *msi_np;
    struct riscv_aplic *aplic = rt_calloc(1, sizeof(*aplic));

    aplic->regs = rt_ofw_iomap(np, 0);

    if (!aplic->regs)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    if ((err = rt_ofw_prop_read_u32(np, "riscv,num-sources", &aplic->nr_irqs)))
    {
        goto _fail;
    }

    msi_np = rt_ofw_parse_phandle(np, "msi-parent", 0);

    /* Disable all interrupts */
    for (int i = 0; i <= aplic->nr_irqs; i += 32)
    {
        HWREG32(aplic->regs + APLIC_CLRIE_BASE + (i / 32) * sizeof(rt_uint32_t)) = RT_UINT32_MAX;
    }

    /* Clear APLIC domaincfg */
    HWREG32(aplic->regs + APLIC_DOMAINCFG) = 0;

    aplic->np = np;
    aplic->init_cpu_id = rt_hw_cpu_id();
    rt_ofw_data(np) = &aplic->parent;

    if (msi_np)
    {
        const struct imsic_global_config *imsic_global;
        struct riscv_aplic_msicfg *msicfg = &aplic->msicfg;

        if ((err = imsic_ofw_probe(msi_np, np, id)))
        {
            goto _fail;
        }

        if (!(imsic_global = imsic_global_config_read(msi_np)))
        {
            LOG_E("%s: IMSIC global config not found", rt_ofw_node_full_name(np));
            err = -RT_EINVAL;
            goto _fail;
        }

        /* Find number of guest index bits (LHXS) */
        msicfg->lhxs = imsic_global->guest_index_bits;
        if (APLIC_xMSICFGADDRH_LHXS_MASK < msicfg->lhxs)
        {
            LOG_E("%s: IMSIC guest index bits big for APLIC LHXS", rt_ofw_node_full_name(np));
            err = -RT_EINVAL;
            goto _fail;
        }

        /* Find number of HART index bits (LHXW) */
        msicfg->lhxw = imsic_global->hart_index_bits;
        if (APLIC_xMSICFGADDRH_LHXW_MASK < msicfg->lhxw)
        {
            LOG_E("%s: IMSIC hart index bits big for APLIC LHXW", rt_ofw_node_full_name(np));
            err = -RT_EINVAL;
            goto _fail;
        }

        /* Find number of group index bits (HHXW) */
        msicfg->hhxw = imsic_global->group_index_bits;
        if (APLIC_xMSICFGADDRH_HHXW_MASK < msicfg->hhxw)
        {
            LOG_E("%s: IMSIC group index bits big for APLIC HHXW", rt_ofw_node_full_name(np));
            err = -RT_EINVAL;
            goto _fail;
        }

        /* Find first bit position of group index (HHXS) */
        msicfg->hhxs = imsic_global->group_index_shift;
        if (msicfg->hhxs < (2 * APLIC_xMSICFGADDR_PPN_SHIFT))
        {
            LOG_E("%s: IMSIC group index shift should be >= %d",
                    rt_ofw_node_full_name(np), (2 * APLIC_xMSICFGADDR_PPN_SHIFT));
            err = -RT_EINVAL;
            goto _fail;
        }
        msicfg->hhxs -= (2 * APLIC_xMSICFGADDR_PPN_SHIFT);
        if (APLIC_xMSICFGADDRH_HHXS_MASK < msicfg->hhxs)
        {
            LOG_E("%s: IMSIC group index shift big for APLIC HHXS", rt_ofw_node_full_name(np));
            err = -RT_EINVAL;
            goto _fail;
        }

        /* Compute PPN base */
        msicfg->base_ppn = imsic_global->base_addr >> APLIC_xMSICFGADDR_PPN_SHIFT;
        msicfg->base_ppn &= ~APLIC_xMSICFGADDR_PPN_HART(msicfg->lhxs);
        msicfg->base_ppn &= ~APLIC_xMSICFGADDR_PPN_LHX(msicfg->lhxw, msicfg->lhxs);
        msicfg->base_ppn &= ~APLIC_xMSICFGADDR_PPN_HHX(msicfg->hhxw, msicfg->hhxs);
    }
    else
    {
        int hwirq, cpu_id;
        rt_ubase_t hartid;
        struct riscv_aplic_idc *idc;
        struct rt_ofw_cell_args idcs;
        struct rt_ofw_node *cpu_np;

        while (!rt_ofw_parse_irq_cells(np, aplic->nr_idcs, &idcs))
        {
            cpu_np = rt_ofw_get_parent(idcs.data);

            hwirq = idcs.args[0];
            hartid = rt_ofw_get_cpu_hwid(cpu_np, 0);

            rt_ofw_node_put(cpu_np);

            if (hwirq != RV_IRQ_EXT)
            {
                continue;
            }

            cpu_id = riscv_hartid_to_cpu_id(hartid);

            if (cpu_id >= RT_CPUS_NR)
            {
                continue;
            }

            idc = &aplic->idc[cpu_id];
            idc->regs = aplic->regs + APLIC_IDC_BASE + aplic->nr_idcs * APLIC_IDC_SIZE;

            /* Priority must be less than threshold for interrupt triggering */
            HWREG32(idc->regs + APLIC_IDC_ITHRESHOLD) = APLIC_ENABLE_ITHRESHOLD;

            /* Delivery must be set to 1 for interrupt triggering */
            HWREG32(idc->regs + APLIC_IDC_IDELIVERY) = APLIC_ENABLE_IDELIVERY;

            ++aplic->nr_idcs;
        }
    }

    /* Setup global config and interrupt delivery */
#ifdef ARCH_RISCV_M_MODE
    if (msi_np)
    {
        rt_uint32_t valh;

        val = rt_lower_32_bits(aplic->msicfg.base_ppn);
        valh = RT_FIELD_PREP(APLIC_xMSICFGADDRH_BAPPN, rt_upper_32_bits(aplic->msicfg.base_ppn));
        valh |= RT_FIELD_PREP(APLIC_xMSICFGADDRH_LHXW, aplic->msicfg.lhxw);
        valh |= RT_FIELD_PREP(APLIC_xMSICFGADDRH_HHXW, aplic->msicfg.hhxw);
        valh |= RT_FIELD_PREP(APLIC_xMSICFGADDRH_LHXS, aplic->msicfg.lhxs);
        valh |= RT_FIELD_PREP(APLIC_xMSICFGADDRH_HHXS, aplic->msicfg.hhxs);

        HWREG32(aplic->regs + APLIC_xMSICFGADDR) = val;
        HWREG32(aplic->regs + APLIC_xMSICFGADDRH) = valh;
    }
#endif /* ARCH_RISCV_M_MODE */

    /* Setup APLIC domaincfg register */
    val = HWREG32(aplic->regs + APLIC_DOMAINCFG);
    val |= APLIC_DOMAINCFG_IE;

    if (msi_np)
    {
        val |= APLIC_DOMAINCFG_DM;
    }

    HWREG32(aplic->regs + APLIC_DOMAINCFG) = val;

    if (HWREG32(aplic->regs + APLIC_DOMAINCFG) != val)
    {
        LOG_W("Unable to write 0x%x in domaincfg", val);
    }

    aplic->parent_irq = -1;

    aplic->parent.priv_data = aplic;

    if (msi_np)
    {
        aplic->parent.ops = &aplic_msi_ops;
        aplic->msi_ic = rt_ofw_data(msi_np);
    }
    else
    {
        aplic->parent.ops = &aplic_direct_ops;
    }

    rt_pic_linear_irq(&aplic->parent, aplic->nr_irqs);

    rt_pic_user_extends(&aplic->parent);

    return RT_EOK;

_fail:
    if (aplic->regs)
    {
        rt_iounmap(aplic->regs);
    }

    rt_free(aplic);

    return err;
}

static const struct rt_ofw_node_id aplic_ofw_ids[] =
{
    { .compatible = "riscv,aplic" },
    { /* sentinel */ }
};
RT_PIC_OFW_DECLARE(aplic, aplic_ofw_ids, aplic_ofw_init);
