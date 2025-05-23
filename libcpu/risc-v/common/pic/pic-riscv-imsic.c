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

#define DBG_TAG "pic.imsic"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpu.h>
#include <csr.h>
#include "pic-riscv-imsic.h"

#define IMSIC_ID_START              1
#define IMSIC_IPI_ID                IMSIC_ID_START

#define IMSIC_ENABLE_EIDELIVERY     1
#define IMSIC_DISABLE_EIDELIVERY    0
#define IMSIC_ENABLE_EITHRESHOLD    0
#define IMSIC_DISABLE_EITHRESHOLD   1

struct riscv_imsic_mmio
{
    rt_uint64_t addr;
    rt_uint64_t size;

    void *mapped;
};

struct riscv_imsic
{
    struct rt_pic parent;
    struct rt_pic *parent_ic;

    struct rt_ofw_node *np;

    int parent_irq;
    int msi_id_start;
    int init_cpu_id;

    struct imsic_global_config global;

    rt_bitmap_t *vectors;
    struct rt_spinlock lock;
};

extern rt_uint32_t *riscv_aclint_ipi_base;

rt_inline unsigned int __fls(unsigned long word)
{
    unsigned int num = RT_BITS_PER_LONG - 1;

#if RT_BITS_PER_LONG == 64
    if (!(word & (~0UL << 32)))
    {
        num -= 32;
        word <<= 32;
    }
#endif
    if (!(word & (~0UL << (RT_BITS_PER_LONG - 16))))
    {
        num -= 16;
        word <<= 16;
    }
    if (!(word & (~0UL << (RT_BITS_PER_LONG - 8))))
    {
        num -= 8;
        word <<= 8;
    }
    if (!(word & (~0UL << (RT_BITS_PER_LONG - 4))))
    {
        num -= 4;
        word <<= 4;
    }
    if (!(word & (~0UL << (RT_BITS_PER_LONG - 2))))
    {
        num -= 2;
        word <<= 2;
    }
    if (!(word & (~0UL << (RT_BITS_PER_LONG - 1))))
    {
        num -= 1;
    }
    return num;
}

rt_inline void imsic_csr_write(rt_ubase_t reg, rt_ubase_t val)
{
    csr_write(CSR_ISELECT, reg);
    csr_write(CSR_IREG, val);
}

rt_inline rt_ubase_t imsic_csr_read(rt_ubase_t reg)
{
    csr_write(CSR_ISELECT, reg);
    return csr_read(CSR_IREG);
}

rt_inline rt_ubase_t imsic_csr_read_clear(rt_ubase_t reg, rt_ubase_t val)
{
    csr_write(CSR_ISELECT, reg);
    return csr_read_clear(CSR_IREG, val);
}

rt_inline void imsic_csr_set(rt_ubase_t reg, rt_ubase_t val)
{
    csr_write(CSR_ISELECT, reg);
    csr_set(CSR_IREG, val);
}

rt_inline void imsic_csr_clear(rt_ubase_t reg, rt_ubase_t val)
{
    csr_write(CSR_ISELECT, reg);
    csr_clear(CSR_IREG, val);
}

static void imsic_eix_update(rt_ubase_t base_id, rt_ubase_t num_id, rt_bool_t pend, rt_bool_t val)
{
    rt_ubase_t id = base_id, last_id = base_id + num_id, isel, ireg;

    while (id < last_id)
    {
        isel = id / RT_BITS_PER_LONG;
        isel *= RT_BITS_PER_LONG / IMSIC_EIPx_BITS;
        isel += pend ? IMSIC_EIP0 : IMSIC_EIE0;

        /*
         * Prepare the ID mask to be programmed in the
         * IMSIC EIEx and EIPx registers. These registers
         * are XLEN-wide and we must not touch IDs which
         * are < base_id and >= (base_id + num_id).
         */
        ireg = 0;
        for (rt_ubase_t i = id & (__riscv_xlen - 1); id < last_id && i < __riscv_xlen; ++i)
        {
            ireg |= RT_BIT(i);
            id++;
        }

        /*
         * The IMSIC EIEx and EIPx registers are indirectly
         * accessed via using ISELECT and IREG CSRs so we
         * need to access these CSRs without getting preempted.
         *
         * All existing users of this function call this
         * function with local IRQs disabled so we don't
         * need to do anything special here.
         */
        if (val)
        {
            imsic_csr_set(isel, ireg);
        }
        else
        {
            imsic_csr_clear(isel, ireg);
        }
    }
}

rt_inline void imsic_id_clear_enable(rt_ubase_t id)
{
    imsic_eix_update(id, 1, RT_FALSE, RT_FALSE);
}

rt_inline void imsic_id_set_enable(rt_ubase_t id)
{
    imsic_eix_update(id, 1, RT_FALSE, RT_TRUE);
}

rt_inline void imsic_local_delivery(rt_bool_t enable)
{
    if (enable)
    {
        imsic_csr_write(IMSIC_EITHRESHOLD, IMSIC_ENABLE_EITHRESHOLD);
        imsic_csr_write(IMSIC_EIDELIVERY, IMSIC_ENABLE_EIDELIVERY);
    }
    else
    {
        imsic_csr_write(IMSIC_EIDELIVERY, IMSIC_DISABLE_EIDELIVERY);
        imsic_csr_write(IMSIC_EITHRESHOLD, IMSIC_DISABLE_EITHRESHOLD);
    }
}

static void imsic_handler(int hwirq, void *data);

static rt_err_t riscv_imsic_irq_init(struct rt_pic *pic)
{
    struct riscv_imsic *imsic = pic->priv_data;

    imsic_local_delivery(RT_TRUE);

    for (int hwirq = IMSIC_ID_START; hwirq < imsic->global.nr_ids; ++hwirq)
    {
        /*
         * Enable all ID in current CPU
         * that will not sync by IPI in mask/umask.
         */
        imsic_id_set_enable(hwirq);
    }

    if (imsic->parent_irq < 0)
    {
        struct rt_ofw_cell_args irq_args;

        if (rt_ofw_parse_irq_cells(imsic->np, 0, &irq_args))
        {
            LOG_E("%s: Parent IRQ is not available", rt_ofw_node_full_name(imsic->np));
            return RT_EOK;
        }

        /* Create mapping */
        irq_args.args[0] = RV_IRQ_EXT;

        imsic->parent_irq = rt_ofw_map_irq(&irq_args);

        rt_hw_interrupt_install(imsic->parent_irq, imsic_handler, imsic, "IMSIC");
    }

    rt_pic_irq_unmask(imsic->parent_irq);

    return RT_EOK;
}

static void riscv_imsic_irq_mask(struct rt_pic_irq *pirq)
{
    if (pirq->msi_desc)
    {
        rt_pci_msi_mask_irq(pirq);
    }

#if defined(RT_USING_SMP) && defined(ARCH_RISCV_M_MODE)
    if (pirq->irq < RT_MAX_IPI)
    {
        imsic_id_clear_enable(pirq->hwirq);
    }
#endif
}

static void riscv_imsic_irq_unmask(struct rt_pic_irq *pirq)
{
    if (pirq->msi_desc)
    {
        rt_pci_msi_unmask_irq(pirq);
    }

#if defined(RT_USING_SMP) && defined(ARCH_RISCV_M_MODE)
    if (pirq->irq < RT_MAX_IPI)
    {
        imsic_id_set_enable(pirq->hwirq);
    }
#endif
}

static rt_err_t riscv_imsic_irq_set_affinity(struct rt_pic_irq *pirq, rt_bitmap_t *affinity)
{
    struct rt_pci_msi_desc *desc = pirq->msi_desc;

    if (desc)
    {
        int old_cpu, cpu;

        cpu = rt_bitmap_next_set_bit(affinity, 0, RT_CPUS_NR);

        /* IMSIC supports only one HART affinity */
        if (rt_bitmap_next_set_bit(affinity, cpu, RT_CPUS_NR) != RT_CPUS_NR)
        {
            return -RT_ENOSYS;
        }

        old_cpu = rt_bitmap_next_set_bit(pirq->affinity, 0, RT_CPUS_NR);

        if (cpu == old_cpu)
        {
            return RT_EOK;
        }

        RT_IRQ_AFFINITY_CLEAR(pirq->affinity, old_cpu);
        RT_IRQ_AFFINITY_SET(pirq->affinity, cpu);

        /* Update MSI info */
        pirq->pic->ops->irq_compose_msi_msg(pirq, &desc->msg);

        /* Update for PCI device */
        rt_pci_msi_write_msg(desc, &desc->msg);

        return RT_EOK;
    }

    return -RT_EINVAL;
}

#ifdef ARCH_RISCV_M_MODE
static void riscv_imsic_irq_send_ipi(struct rt_pic_irq *pirq, rt_bitmap_t *cpumask)
{
    int cpu_id;
    struct imsic_local_config *local;
    struct riscv_imsic *imsic = pirq->pic->priv_data;

    rt_bitmap_for_each_set_bit(cpumask, cpu_id, RT_CPUS_NR)
    {
        local = &imsic->global.local[cpu_id];

        HWREG32(local->msi) = pirq->hwirq;
    }
}
#endif /* ARCH_RISCV_M_MODE */

static void riscv_imsic_irq_compose_msi_msg(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg)
{
    struct imsic_local_config *local;
    struct imsic_global_config *global;
    struct riscv_imsic *imsic = pirq->pic->priv_data;

    global = &imsic->global;

    if (RT_BIT(global->guest_index_bits) <= 0)
    {
        LOG_W("Global guest disabled");
        return;
    }

    local = &global->local[rt_bitmap_next_set_bit(pirq->affinity, 0, RT_CPUS_NR)];

    msg->address_hi = rt_upper_32_bits(local->msi_phy);
    msg->address_lo = rt_lower_32_bits(local->msi_phy);
    msg->data = pirq->hwirq;
}

static void riscv_imsic_irq_write_msi_msg(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg)
{
    struct rt_pic_irq virtual_pirq;
    struct riscv_imsic *imsic = pirq->pic->priv_data;

    virtual_pirq.pic = imsic->parent_ic;
    virtual_pirq.hwirq = pirq->hwirq;

    imsic->parent_ic->ops->irq_write_msi_msg(&virtual_pirq, msg);
}

static int riscv_imsic_irq_alloc_msi(struct rt_pic *pic, struct rt_pci_msi_desc *msi_desc)
{
    rt_ubase_t level;
    int irq, hwirq_index;
    struct rt_pic_irq *pirq;
    struct imsic_global_config *global;
    struct riscv_imsic *imsic = pic->priv_data;

    global = &imsic->global;

    level = rt_spin_lock_irqsave(&imsic->lock);
    hwirq_index = rt_bitmap_next_clear_bit(imsic->vectors, 0, global->nr_ids);

    if (hwirq_index >= global->nr_ids)
    {
        irq = -RT_EEMPTY;
        goto _out_lock;
    }

    irq = rt_pic_config_irq(pic, hwirq_index, hwirq_index + IMSIC_ID_START);
    if (irq < 0)
    {
        goto _out_lock;
    }
    pirq = rt_pic_find_irq(pic, hwirq_index);
    pirq->mode = RT_IRQ_MODE_EDGE_RISING;
    RT_IRQ_AFFINITY_SET(pirq->affinity, imsic->init_cpu_id);

    rt_bitmap_set_bit(imsic->vectors, hwirq_index);

_out_lock:
    rt_spin_unlock_irqrestore(&imsic->lock, level);

    return irq;
}

static void riscv_imsic_irq_free_msi(struct rt_pic *pic, int irq)
{
    rt_ubase_t level;
    struct rt_pic_irq *pirq;
    struct riscv_imsic *imsic;

    pirq = rt_pic_find_pirq(pic, irq);

    if (!pirq)
    {
        return;
    }

    imsic = pirq->pic->priv_data;

    level = rt_spin_lock_irqsave(&imsic->lock);
    rt_bitmap_clear_bit(imsic->vectors, pirq->hwirq - IMSIC_ID_START);
    rt_spin_unlock_irqrestore(&imsic->lock, level);
}

const static struct rt_pic_ops riscv_imsic_ops =
{
    .name = "IMSIC",
    .irq_init = riscv_imsic_irq_init,
    .irq_mask = riscv_imsic_irq_mask,
    .irq_unmask = riscv_imsic_irq_unmask,
    .irq_set_affinity = riscv_imsic_irq_set_affinity,
#ifdef ARCH_RISCV_M_MODE
    .irq_send_ipi = riscv_imsic_irq_send_ipi,
#endif
    .irq_compose_msi_msg = riscv_imsic_irq_compose_msi_msg,
    .irq_write_msi_msg = riscv_imsic_irq_write_msi_msg,
    .irq_alloc_msi = riscv_imsic_irq_alloc_msi,
    .irq_free_msi = riscv_imsic_irq_free_msi,
};

static void imsic_handler(int hwirq, void *data)
{
    rt_ubase_t local_id;
    struct rt_pic_irq *pirq;
    struct riscv_imsic *imsic = data;

    while ((local_id = csr_swap(CSR_TOPEI, 0)))
    {
        local_id >>= TOPEI_ID_SHIFT;

        if (local_id >= imsic->msi_id_start)
        {
            pirq = rt_pic_find_irq(&imsic->parent, local_id - IMSIC_ID_START);
        }
        else
        {
        #if defined(RT_USING_SMP) && defined(ARCH_RISCV_M_MODE)
            pirq = rt_pic_find_ipi(&imsic->parent, local_id - IMSIC_IPI_ID);
        #else
            LOG_E("It's is impossible");
            RT_ASSERT(0);
        #endif
        }

        rt_pic_handle_isr(pirq);
    }
}

const struct imsic_global_config *imsic_global_config_read(struct rt_ofw_node *np)
{
    struct riscv_imsic *imsic = rt_container_of(rt_ofw_data(np), struct riscv_imsic, parent);

    return imsic ? &imsic->global : RT_NULL;
}

static const struct rt_ofw_node_id riscv_imsic_ofw_ids[] =
{
    { .compatible = "riscv,imsics" },
    { /* sentinel */ }
};

rt_err_t imsic_ofw_probe(struct rt_ofw_node *np,
        struct rt_ofw_node *ic_np, const struct rt_ofw_node_id *ic_id)
{
    rt_err_t err;
    int irq_count, mmio_count, i;
    struct rt_ofw_node_id *id;
    struct riscv_imsic *imsic;
    struct imsic_global_config *global;
    struct riscv_imsic_mmio *mmio = RT_NULL;

    if (!(id = rt_ofw_node_match(np, riscv_imsic_ofw_ids)))
    {
        return -RT_EINVAL;
    }

    if (!(imsic = rt_calloc(1, sizeof(*imsic))))
    {
        return -RT_ENOMEM;
    }
    global = &imsic->global;

    irq_count = rt_ofw_get_irq_count(np);

    rt_ofw_prop_read_u32(np, "riscv,guest-index-bits", &global->guest_index_bits);

    if (rt_ofw_prop_read_u32(np, "riscv,hart-index-bits", &global->hart_index_bits))
    {
        global->hart_index_bits = __fls(irq_count);

        if (RT_BIT(global->hart_index_bits) < irq_count)
        {
            ++global->hart_index_bits;
        }
    }

    rt_ofw_prop_read_u32(np, "riscv,group-index-bits", &global->guest_index_bits);

    if (rt_ofw_prop_read_u32(np, "riscv,group-index-shift", &global->group_index_shift))
    {
        global->group_index_shift = IMSIC_MMIO_PAGE_SHIFT * 2;
    }

    if ((err = rt_ofw_prop_read_u32(np, "riscv,num-ids", &global->nr_ids)))
    {
        LOG_E("%s: Number of IRQ is unknown", rt_ofw_node_full_name(np));
        goto _fail;
    }

    if (rt_ofw_prop_read_u32(np, "riscv,num-guest-ids", &global->nr_guest_ids))
    {
        global->nr_guest_ids = global->nr_ids;
    }

    /* Sanity check guest index bits */
    i = RT_BITS_PER_LONG - IMSIC_MMIO_PAGE_SHIFT;
    if (i < global->guest_index_bits)
    {
        LOG_E("%s: %s index %s too big", "Guest", "bits", rt_ofw_node_full_name(np));

        err = -RT_EINVAL;
        goto _fail;
    }

    /* Sanity check HART index bits */
    i = RT_BITS_PER_LONG - IMSIC_MMIO_PAGE_SHIFT - global->guest_index_bits;
    if (i < global->hart_index_bits)
    {
        LOG_E("%s: %s index %s too big", "HART", "bits", rt_ofw_node_full_name(np));

        err = -RT_EINVAL;
        goto _fail;
    }

    /* Sanity check group index bits */
    i = RT_BITS_PER_LONG - IMSIC_MMIO_PAGE_SHIFT - global->guest_index_bits - global->hart_index_bits;
    if (i < global->group_index_bits)
    {
        LOG_E("%s: %s index %s too big", "Group", "bits", rt_ofw_node_full_name(np));

        err = -RT_EINVAL;
        goto _fail;
    }

    /* Sanity check group index shift */
    i = global->group_index_bits + global->group_index_shift - 1;
    if (i >= RT_BITS_PER_LONG)
    {
        LOG_E("%s: %s index %s too big", "Group", "shift", rt_ofw_node_full_name(np));

        err = -RT_EINVAL;
        goto _fail;
    }

    /* Sanity check number of interrupt identities */
    if (global->nr_ids < IMSIC_MIN_ID ||
        global->nr_ids >= IMSIC_MAX_ID ||
        (global->nr_ids & IMSIC_MIN_ID) != IMSIC_MIN_ID)
    {
        LOG_E("%s: Invalid number of %sinterrupt identities", "", rt_ofw_node_full_name(np));

        err = -RT_EINVAL;
        goto _fail;
    }

    /* Sanity check number of guest interrupt identities */
    if (global->nr_guest_ids < IMSIC_MIN_ID ||
        global->nr_guest_ids >= IMSIC_MAX_ID ||
        (global->nr_guest_ids & IMSIC_MIN_ID) != IMSIC_MIN_ID)
    {
        LOG_E("%s: Invalid number of %sinterrupt identities", "guest ", rt_ofw_node_full_name(np));

        err = -RT_EINVAL;
        goto _fail;
    }

    mmio_count = rt_ofw_get_address_count(np);
    mmio = rt_calloc(mmio_count, sizeof(*mmio));

    if (!mmio)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    for (int i = 0; i < mmio_count; ++i)
    {
        rt_ubase_t base_addr;

        if ((err = rt_ofw_get_address(np, 0, &mmio[i].addr, &mmio[i].size)))
        {
            goto _fail;
        }

        if (i == 0)
        {
            global->base_addr = mmio[i].addr;
            global->base_addr &= ~(RT_BIT(global->guest_index_bits +
                    global->hart_index_bits + IMSIC_MMIO_PAGE_SHIFT) - 1);
            global->base_addr &= ~((RT_BIT(global->group_index_bits) - 1) <<
                    global->group_index_shift);
        }

        base_addr = mmio[i].addr;
        base_addr &= ~(RT_BIT(global->guest_index_bits +
                global->hart_index_bits + IMSIC_MMIO_PAGE_SHIFT) - 1);
        base_addr &= ~((RT_BIT(global->group_index_bits) - 1) <<
                global->group_index_shift);

        if (base_addr != global->base_addr)
        {
            err = -RT_EINVAL;
            goto _fail;
        }

        mmio[i].mapped = rt_ioremap((void *)mmio[i].addr, mmio[i].size);

        if (!mmio[i].mapped)
        {
            err = -RT_EIO;
            goto _fail;
        }
    }

    for (int i = 0; i < irq_count; ++i)
    {
        int cpu_id;
        int index, reloff;
        rt_ubase_t hartid;
        struct rt_ofw_node *cpu_np;
        struct rt_ofw_cell_args arg;
        struct imsic_local_config *local;

        if (rt_ofw_parse_irq_cells(np, i, &arg))
        {
            continue;
        }

        cpu_np = rt_ofw_get_parent(arg.data);
        hartid = rt_ofw_get_cpu_hwid(cpu_np, 0);
        rt_ofw_node_put(cpu_np);

        cpu_id = riscv_hartid_to_cpu_id(hartid);

        if (cpu_id >= RT_CPUS_NR)
        {
            continue;
        }

        /* Find MMIO location of MSI page */
        index = mmio_count;
        reloff = i * RT_BIT(global->guest_index_bits) * IMSIC_MMIO_PAGE_SZ;
        for (int j = 0; mmio_count; ++j)
        {
            if (reloff < mmio[j].size)
            {
                index = j;
                break;
            }

            /*
             * MMIO region size may not be aligned to
             * RT_BIT(global->guest_index_bits) * IMSIC_MMIO_PAGE_SZ
             * if holes are present.
             */
            reloff -= RT_ALIGN(mmio[j].size, RT_BIT(global->guest_index_bits) * IMSIC_MMIO_PAGE_SZ);
        }

        if (index >= mmio_count)
        {
            LOG_E("%s: MMIO not found for parent IRQ[%d]", rt_ofw_node_full_name(np), i);
            continue;
        }

        local = &global->local[cpu_id];
        local->msi_phy = mmio[index].addr + reloff;
        local->msi = mmio[index].mapped + reloff;
    }
    rt_free(mmio);

    if (!(imsic->vectors = rt_calloc(1, RT_BITMAP_LEN(global->nr_ids) * sizeof(rt_bitmap_t))))
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    rt_spin_lock_init(&imsic->lock);

    imsic->np = np;
    imsic->parent_irq = -1;
    imsic->init_cpu_id = rt_hw_cpu_id();

    imsic->parent.priv_data = imsic;
    imsic->parent.ops = &riscv_imsic_ops;

    imsic->parent_ic = rt_ofw_data(ic_np);

    rt_ofw_data(np) = &imsic->parent;
    rt_ofw_node_set_flag(np, RT_OFW_F_READLY);

    rt_pic_linear_irq(&imsic->parent, global->nr_ids);

    imsic->msi_id_start = IMSIC_ID_START;

#if defined(RT_USING_SMP) && defined(ARCH_RISCV_M_MODE)
    if (!riscv_aclint_ipi_base)
    {
        for (int ipi = 0; ipi < RT_MAX_IPI; ++ipi)
        {
            int hwirq = IMSIC_IPI_ID + ipi;

            rt_bitmap_set_bit(imsic->vectors, hwirq);
            rt_pic_config_ipi(&imsic->parent, ipi, hwirq);
        }

        imsic->msi_id_start += RT_MAX_IPI;
    }
#endif /* RT_USING_SMP && ARCH_RISCV_M_MODE */

    rt_pic_user_extends(&imsic->parent);

    return RT_EOK;

_fail:
    if (mmio)
    {
        for (int i = 0; mmio[i].mapped && i < mmio_count; ++i)
        {
            rt_iounmap(mmio[i].mapped);
        }

        rt_free(mmio);
    }

    rt_free(imsic);

    return err;
}
