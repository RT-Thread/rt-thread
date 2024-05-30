/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-07     GuEe-GUI     first version
 */

#include <drivers/pci_msi.h>
#include <drivers/core/numa.h>

#define DBG_TAG "pci.msi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* PCI has 2048 max IRQs in MSI-X */
static RT_IRQ_AFFINITY_DECLARE(msi_affinity_default[2048]) rt_section(".bss.noclean.pci.msi");

rt_inline void spin_lock(struct rt_spinlock *lock)
{
    rt_hw_spin_lock(&lock->lock);
}

rt_inline void spin_unlock(struct rt_spinlock *lock)
{
    rt_hw_spin_unlock(&lock->lock);
}

rt_inline void *msix_table_base(struct rt_pci_msix_conf *msix)
{
    return msix->table_base + msix->index * PCIM_MSIX_ENTRY_SIZE;
}

rt_inline void *msix_vector_ctrl_base(struct rt_pci_msix_conf *msix)
{
    return msix_table_base(msix) + PCIM_MSIX_ENTRY_VECTOR_CTRL;
}

rt_inline void msix_write_vector_ctrl(struct rt_pci_msix_conf *msix,
        rt_uint32_t ctrl)
{
    void *vc_addr = msix_vector_ctrl_base(msix);

    HWREG32(vc_addr) = ctrl;
}

rt_inline void msix_mask(struct rt_pci_msix_conf *msix)
{
    msix->msg_ctrl |= PCIM_MSIX_ENTRYVECTOR_CTRL_MASK;
    msix_write_vector_ctrl(msix, msix->msg_ctrl);

    /* Flush write to device */
    HWREG32(msix->table_base);
}

static void msix_update_ctrl(struct rt_pci_device *pdev,
        rt_uint16_t clear, rt_uint16_t set)
{
    rt_uint16_t msgctl;

    rt_pci_read_config_u16(pdev, pdev->msix_cap + PCIR_MSIX_CTRL, &msgctl);
    msgctl &= ~clear;
    msgctl |= set;
    rt_pci_write_config_u16(pdev, pdev->msix_cap + PCIR_MSIX_CTRL, msgctl);
}

rt_inline void msix_unmask(struct rt_pci_msix_conf *msix)
{
    msix->msg_ctrl &= ~PCIM_MSIX_ENTRYVECTOR_CTRL_MASK;
    msix_write_vector_ctrl(msix, msix->msg_ctrl);
}

rt_inline rt_uint32_t msi_multi_mask(struct rt_pci_msi_conf *msi)
{
    if (msi->cap.multi_msg_max >= 5)
    {
        return 0xffffffff;
    }

    return (1 << (1 << msi->cap.multi_msg_max)) - 1;
}

static void msi_write_mask(struct rt_pci_msi_conf *msi,
        rt_uint32_t clear, rt_uint32_t set, struct rt_pci_device *pdev)
{
    if (msi->cap.is_masking)
    {
        rt_ubase_t level = rt_spin_lock_irqsave(&pdev->msi_lock);

        msi->mask &= ~clear;
        msi->mask |= set;
        rt_pci_write_config_u32(pdev, msi->mask_pos, msi->mask);

        rt_spin_unlock_irqrestore(&pdev->msi_lock, level);
    }
}

rt_inline void msi_mask(struct rt_pci_msi_conf *msi,
        rt_uint32_t mask, struct rt_pci_device *pdev)
{
    msi_write_mask(msi, 0, mask, pdev);
}

rt_inline void msi_unmask(struct rt_pci_msi_conf *msi,
        rt_uint32_t mask, struct rt_pci_device *pdev)
{
    msi_write_mask(msi, mask, 0, pdev);
}

static void msi_write_enable(struct rt_pci_device *pdev, rt_bool_t enable)
{
    rt_uint16_t msgctl;

    rt_pci_read_config_u16(pdev, pdev->msi_cap + PCIR_MSI_CTRL, &msgctl);

    msgctl &= ~PCIM_MSICTRL_MSI_ENABLE;

    if (enable)
    {
        msgctl |= PCIM_MSICTRL_MSI_ENABLE;
    }

    rt_pci_write_config_u16(pdev, pdev->msi_cap + PCIR_MSI_CTRL, msgctl);
}

static void msi_affinity_init(struct rt_pci_msi_desc *desc, int msi_index,
        rt_bitmap_t *cpumasks)
{
    int irq;
    struct rt_pic_irq *pirq;
    struct rt_pci_device *pdev = desc->pdev;
    struct rt_pic *msi_pic = pdev->msi_pic;

    irq = desc->irq + desc->is_msix ? 0 : msi_index;
    pirq = rt_pic_find_pirq(msi_pic, irq);

    /* Save affinity */
    if (desc->is_msix)
    {
        desc->affinity = pirq->affinity;
    }
    else
    {
        desc->affinities[msi_index] = pirq->affinity;
    }

    if ((void *)cpumasks > (void *)msi_affinity_default &&
        (void *)cpumasks < (void *)msi_affinity_default + sizeof(msi_affinity_default))
    {
        rt_uint64_t data_address;

        /* Get MSI/MSI-X write data adddress */
        data_address = desc->msg.address_hi;
        data_address <<= 32;
        data_address |= desc->msg.address_lo;

        /* Prepare affinity */
        cpumasks = pirq->affinity;

        rt_numa_memory_affinity(data_address, cpumasks);
    }
    else if (rt_bitmap_next_set_bit(cpumasks, 0, RT_CPUS_NR) >= RT_CPUS_NR)
    {
        /* No affinity info found, give up */
        return;
    }

    if (!rt_pic_irq_set_affinity(irq, cpumasks))
    {
        if (msi_pic->ops->irq_write_msi_msg)
        {
            msi_pic->ops->irq_write_msi_msg(pirq, &desc->msg);
        }
    }
}

void rt_pci_msi_shutdown(struct rt_pci_device *pdev)
{
    struct rt_pci_msi_desc *desc;

    if (!pdev)
    {
        return;
    }

    msi_write_enable(pdev, RT_FALSE);
    rt_pci_intx(pdev, RT_TRUE);

    if ((desc = rt_pci_msi_first_desc(pdev)))
    {
        msi_unmask(&desc->msi, msi_multi_mask(&desc->msi), pdev);
    }

    /* Restore pdev->irq to its default pin-assertion IRQ */
    pdev->irq = desc->msi.default_irq;
    pdev->msi_enabled = RT_FALSE;
}

void rt_pci_msix_shutdown(struct rt_pci_device *pdev)
{
    struct rt_pci_msi_desc *desc;

    if (!pdev)
    {
        return;
    }

    rt_pci_msi_for_each_desc(pdev, desc)
    {
        msix_mask(&desc->msix);
    }

    msix_update_ctrl(pdev, PCIM_MSIXCTRL_MSIX_ENABLE, 0);

    rt_pci_intx(pdev, RT_TRUE);
    pdev->msix_enabled = RT_FALSE;
}

void rt_pci_msi_free_irqs(struct rt_pci_device *pdev)
{
    struct rt_pci_msi_desc *desc, *last_desc = RT_NULL;

    if (!pdev)
    {
        return;
    }

    if (pdev->msix_base)
    {
        rt_iounmap(pdev->msix_base);
        pdev->msix_base = RT_NULL;
    }

    rt_pci_msi_for_each_desc(pdev, desc)
    {
        /* To safety */
        if (last_desc)
        {
            rt_list_remove(&last_desc->list);
            rt_free(last_desc);
        }
        last_desc = desc;
    }

    /* The last one */
    if (last_desc)
    {
        rt_list_remove(&last_desc->list);
        rt_free(last_desc);
    }
}

void rt_pci_msi_write_msg(struct rt_pci_msi_desc *desc, struct rt_pci_msi_msg *msg)
{
    struct rt_pci_device *pdev = desc->pdev;

    if (desc->is_msix)
    {
        void *msix_entry;
        rt_bool_t unmasked;
        rt_uint32_t msgctl;
        struct rt_pci_msix_conf *msix = &desc->msix;

        msgctl = msix->msg_ctrl;
        unmasked = !(msgctl & PCIM_MSIX_ENTRYVECTOR_CTRL_MASK);
        msix_entry = msix_table_base(msix);

        if (unmasked)
        {
            msix_write_vector_ctrl(msix, msgctl | PCIM_MSIX_ENTRYVECTOR_CTRL_MASK);
        }

        HWREG32(msix_entry + PCIM_MSIX_ENTRY_LOWER_ADDR) = msg->address_lo;
        HWREG32(msix_entry + PCIM_MSIX_ENTRY_UPPER_ADDR) = msg->address_hi;
        HWREG32(msix_entry + PCIM_MSIX_ENTRY_DATA) = msg->data;

        if (unmasked)
        {
            msix_write_vector_ctrl(msix, msgctl);
        }

        /* Ensure that the writes are visible in the device */
        HWREG32(msix_entry + PCIM_MSIX_ENTRY_DATA);
    }
    else
    {
        rt_uint16_t msgctl;
        int pos = pdev->msi_cap;
        struct rt_pci_msi_conf *msi = &desc->msi;

        rt_pci_read_config_u16(pdev, pos + PCIR_MSI_CTRL, &msgctl);
        msgctl &= ~PCIM_MSICTRL_MME_MASK;
        msgctl |= msi->cap.multi_msg_use << PCIM_MSICTRL_MME_SHIFT;
        rt_pci_write_config_u16(pdev, pos + PCIR_MSI_CTRL, msgctl);

        rt_pci_write_config_u32(pdev, pos + PCIR_MSI_ADDR, msg->address_lo);

        /*
         * The value stored in this field is related to the processor system,
         * the processor will initialize this field
         * when the PCIe device is initialized, and the rules for filling
         * in this field are not the same for different processors.
         * If the Multiple Message Enable field is not 0b000 (multiple IRQs),
         * the PCIe device can send different interrupt requests
         * by changing the low data in the Message Data field
         */
        if (msi->cap.is_64bit)
        {
            rt_pci_write_config_u32(pdev, pos + PCIR_MSI_ADDR_HIGH, msg->address_hi);
            rt_pci_write_config_u16(pdev, pos + PCIR_MSI_DATA_64BIT, msg->data);
        }
        else
        {
            rt_pci_write_config_u16(pdev, pos + PCIR_MSI_DATA, msg->data);
        }

        /* Ensure that the writes are visible in the device */
        rt_pci_read_config_u16(pdev, pos + PCIR_MSI_CTRL, &msgctl);
    }

    desc->msg = *msg;

    if (desc->write_msi_msg)
    {
        desc->write_msi_msg(desc, desc->write_msi_msg_data);
    }
}

void rt_pci_msi_mask_irq(struct rt_pic_irq *pirq)
{
    struct rt_pci_msi_desc *desc;

    if (pirq && (desc = pirq->msi_desc))
    {
        if (desc->is_msix)
        {
            msix_mask(&desc->msix);
        }
        else
        {
            msi_mask(&desc->msi, RT_BIT(pirq->irq - desc->irq), desc->pdev);
        }
    }
}

void rt_pci_msi_unmask_irq(struct rt_pic_irq *pirq)
{
    struct rt_pci_msi_desc *desc;

    if (pirq && (desc = pirq->msi_desc))
    {
        if (desc->is_msix)
        {
            msix_unmask(&desc->msix);
        }
        else
        {
            msi_unmask(&desc->msi, RT_BIT(pirq->irq - desc->irq), desc->pdev);
        }
    }
}

rt_ssize_t rt_pci_alloc_vector(struct rt_pci_device *pdev, int min, int max,
        rt_uint32_t flags, RT_IRQ_AFFINITY_DECLARE((*affinities)))
{
    rt_ssize_t res = -RT_ENOSYS;

    if (!pdev || min > max)
    {
        return -RT_EINVAL;
    }

    if (flags & RT_PCI_IRQ_F_AFFINITY)
    {
        if (!affinities)
        {
            affinities = msi_affinity_default;
        }
    }
    else
    {
        affinities = RT_NULL;
    }

    if (flags & RT_PCI_IRQ_F_MSIX)
    {
        res = rt_pci_msix_enable_range_affinity(pdev, RT_NULL, min, max, affinities);

        if (res > 0)
        {
            return res;
        }
    }

    if (flags & RT_PCI_IRQ_F_MSI)
    {
        res = rt_pci_msi_enable_range_affinity(pdev, min, max, affinities);

        if (res > 0)
        {
            return res;
        }
    }

    if (flags & RT_PCI_IRQ_F_LEGACY)
    {
        if (min == 1 && pdev->irq >= 0)
        {
            if (affinities)
            {
                int cpuid;
                RT_IRQ_AFFINITY_DECLARE(old_affinity);

                /* INTx is shared, we should update it */
                rt_pic_irq_get_affinity(pdev->irq, old_affinity);

                rt_bitmap_for_each_set_bit(affinities[0], cpuid, RT_CPUS_NR)
                {
                    RT_IRQ_AFFINITY_SET(old_affinity, cpuid);
                }

                rt_pic_irq_set_affinity(pdev->irq, old_affinity);
            }

            rt_pci_intx(pdev, RT_TRUE);

            return min;
        }
    }

    return res;
}

void rt_pci_free_vector(struct rt_pci_device *pdev)
{
    if (!pdev)
    {
        return;
    }

    rt_pci_msi_disable(pdev);
    rt_pci_msix_disable(pdev);
    rt_pci_irq_mask(pdev);
}

static rt_err_t msi_verify_entries(struct rt_pci_device *pdev)
{
    if (pdev->no_64bit_msi)
    {
        struct rt_pci_msi_desc *desc;

        rt_pci_msi_for_each_desc(pdev, desc)
        {
            if (desc->msg.address_hi)
            {
                LOG_D("%s: Arch assigned 64-bit MSI address %08x%08x"
                        "but device only supports 32 bits",
                        rt_dm_dev_get_name(&pdev->parent),
                        desc->msg.address_hi, desc->msg.address_lo);

                return -RT_EIO;
            }
        }
    }

    return RT_EOK;
}

static rt_err_t msi_insert_desc(struct rt_pci_device *pdev,
        struct rt_pci_msi_desc *init_desc)
{
    rt_size_t msi_affinity_ptr_size = 0;
    struct rt_pci_msi_desc *msi_desc;

    if (!init_desc->is_msix)
    {
        msi_affinity_ptr_size += sizeof(msi_desc->affinities[0]) * 32;
    }

    msi_desc = rt_calloc(1, sizeof(*msi_desc) + msi_affinity_ptr_size);

    if (!msi_desc)
    {
        return -RT_ENOMEM;
    }

    rt_memcpy(msi_desc, init_desc, sizeof(*msi_desc));

    if (!init_desc->is_msix)
    {
        msi_desc->affinities = (void *)msi_desc + sizeof(*msi_desc);
    }

    msi_desc->pdev = pdev;
    rt_list_init(&msi_desc->list);
    rt_list_insert_before(&pdev->msi_desc_nodes, &msi_desc->list);

    return RT_EOK;
}

rt_ssize_t rt_pci_msi_vector_count(struct rt_pci_device *pdev)
{
    rt_uint16_t msgctl;

    if (!pdev)
    {
        return -RT_EINVAL;
    }

    if (!pdev->msi_cap)
    {
        return -RT_EINVAL;
    }

    rt_pci_read_config_u16(pdev, pdev->msi_cap + PCIR_MSI_CTRL, &msgctl);

    return 1 << ((msgctl & PCIM_MSICTRL_MMC_MASK) >> 1);
}

rt_err_t rt_pci_msi_disable(struct rt_pci_device *pdev)
{
    if (!pdev)
    {
        return -RT_EINVAL;
    }

    if (!pdev->msi_enabled)
    {
        return -RT_EINVAL;
    }

    spin_lock(&pdev->msi_lock);

    rt_pci_msi_shutdown(pdev);
    rt_pci_msi_free_irqs(pdev);

    spin_unlock(&pdev->msi_lock);

    return RT_EOK;
}

static rt_err_t msi_setup_msi_desc(struct rt_pci_device *pdev, int nvec)
{
    rt_uint16_t msgctl;
    struct rt_pci_msi_desc desc;

    rt_memset(&desc, 0, sizeof(desc));

    desc.vector_used = nvec;
    desc.vector_count = rt_pci_msi_vector_count(pdev);
    desc.is_msix = RT_FALSE;

    rt_pci_read_config_u16(pdev, pdev->msi_cap + PCIR_MSI_CTRL, &msgctl);

    desc.msi.cap.is_64bit = !!(msgctl & PCIM_MSICTRL_64BIT);
    desc.msi.cap.is_masking = !!(msgctl & PCIM_MSICTRL_VECTOR);
    desc.msi.cap.multi_msg_max = (msgctl & PCIM_MSICTRL_MMC_MASK) >> 1;

    for (int log2 = 0; log2 < 5; ++log2)
    {
        if (nvec <= (1 << log2))
        {
            desc.msi.cap.multi_msg_use = log2;
            break;
        }
    }

    if (desc.msi.cap.is_64bit)
    {
        desc.msi.mask_pos = pdev->msi_cap + PCIR_MSI_MASK_64BIT;
    }
    else
    {
        desc.msi.mask_pos = pdev->msi_cap + PCIR_MSI_MASK;
    }

    /* Save pdev->irq for its default pin-assertion IRQ */
    desc.msi.default_irq = pdev->irq;

    if (desc.msi.cap.is_masking)
    {
        /* Get the old mask status */
        rt_pci_read_config_u32(pdev, desc.msi.mask_pos, &desc.msi.mask);
    }

    return msi_insert_desc(pdev, &desc);
}

static rt_ssize_t msi_capability_init(struct rt_pci_device *pdev,
        int nvec, RT_IRQ_AFFINITY_DECLARE((*affinities)))
{
    rt_err_t err;
    struct rt_pci_msi_desc *desc;

    msi_write_enable(pdev, RT_FALSE);

    spin_lock(&pdev->msi_lock);

    if (!(err = msi_setup_msi_desc(pdev, nvec)))
    {
        /* All MSIs are unmasked by default; mask them all */
        desc = rt_pci_msi_first_desc(pdev);
        msi_mask(&desc->msi, msi_multi_mask(&desc->msi), pdev);

        if (!(err = rt_pci_msi_setup_irqs(pdev, nvec, PCIY_MSI)))
        {
            err = msi_verify_entries(pdev);
        }

        if (err)
        {
            msi_unmask(&desc->msi, msi_multi_mask(&desc->msi), pdev);
        }
    }

    spin_unlock(&pdev->msi_lock);

    if (err)
    {
        rt_pci_msi_free_irqs(pdev);

        LOG_E("%s: Setup %s interrupts(%d) error = %s",
                rt_dm_dev_get_name(&pdev->parent), "MSI", nvec, rt_strerror(err));

        return err;
    }

    if (affinities)
    {
        for (int idx = 0; idx < nvec; ++idx)
        {
            msi_affinity_init(desc, idx, affinities[idx]);
        }
    }

    /* Disable INTX */
    rt_pci_intx(pdev, RT_FALSE);

    /* Set MSI enabled bits */
    msi_write_enable(pdev, RT_TRUE);

    pdev->irq = desc->irq;

    pdev->msi_enabled = RT_TRUE;

    return nvec;
}

rt_ssize_t rt_pci_msi_enable_range_affinity(struct rt_pci_device *pdev,
        int min, int max, RT_IRQ_AFFINITY_DECLARE((*affinities)))
{
    int nvec = max;
    rt_size_t entries_nr;

    if (!pdev || min > max)
    {
        return -RT_EINVAL;
    }

    if (pdev->no_msi)
    {
        return -RT_ENOSYS;
    }

    if (!pdev->msi_pic)
    {
        return -RT_ENOSYS;
    }

    if (pdev->msi_enabled)
    {
        LOG_W("%s: MSI is enabled", rt_dm_dev_get_name(&pdev->parent));

        return -RT_EINVAL;
    }

    entries_nr = rt_pci_msi_vector_count(pdev);

    if (entries_nr < 0)
    {
        return entries_nr;
    }

    if (nvec > entries_nr)
    {
        return -RT_EEMPTY;
    }

    return msi_capability_init(pdev, nvec, affinities);
}

rt_ssize_t rt_pci_msix_vector_count(struct rt_pci_device *pdev)
{
    rt_uint16_t msgctl;

    if (!pdev)
    {
        return -RT_EINVAL;
    }

    if (!pdev->msix_cap)
    {
        return -RT_EINVAL;
    }

    rt_pci_read_config_u16(pdev, pdev->msix_cap + PCIR_MSIX_CTRL, &msgctl);

    return rt_pci_msix_table_size(msgctl);
}

rt_err_t rt_pci_msix_disable(struct rt_pci_device *pdev)
{
    if (!pdev)
    {
        return -RT_EINVAL;
    }

    if (!pdev->msix_enabled)
    {
        return -RT_EINVAL;
    }

    spin_lock(&pdev->msi_lock);

    rt_pci_msix_shutdown(pdev);
    rt_pci_msi_free_irqs(pdev);

    spin_unlock(&pdev->msi_lock);

    return RT_EOK;
}

static void *msix_table_remap(struct rt_pci_device *pdev, rt_size_t entries_nr)
{
    rt_uint8_t bir;
    rt_uint32_t table_offset;
    rt_ubase_t table_base_phys;

    rt_pci_read_config_u32(pdev, pdev->msix_cap + PCIR_MSIX_TABLE, &table_offset);
    bir = (rt_uint8_t)(table_offset & PCIM_MSIX_BIR_MASK);

    if (pdev->resource[bir].flags & PCI_BUS_REGION_F_NONE)
    {
        LOG_E("%s: BAR[bir = %d] is invalid", rt_dm_dev_get_name(&pdev->parent), bir);

        return RT_NULL;
    }

    table_base_phys = pdev->resource[bir].base + (table_offset & ~PCIM_MSIX_BIR_MASK);

    return rt_ioremap((void *)table_base_phys, entries_nr * PCIM_MSIX_ENTRY_SIZE);
}

static rt_err_t msix_setup_msi_descs(struct rt_pci_device *pdev,
        void *table_base, struct rt_pci_msix_entry *entries, int nvec)
{
    rt_err_t err;
    struct rt_pci_msi_desc desc;

    rt_memset(&desc, 0, sizeof(desc));

    desc.vector_used = 1;
    desc.vector_count = rt_pci_msix_vector_count(pdev);

    desc.is_msix = RT_TRUE;
    desc.msix.table_base = table_base;

    for (int i = 0; i < nvec; ++i)
    {
        void *table_entry;
        int index = entries ? entries[i].index : i;

        desc.msix.index = index;
        table_entry = msix_table_base(&desc.msix);

        desc.msix.msg_ctrl = HWREG32(table_entry + PCIM_MSIX_ENTRY_VECTOR_CTRL);

        if ((err = msi_insert_desc(pdev, &desc)))
        {
            break;
        }
    }

    return err;
}

static rt_ssize_t msix_capability_init(struct rt_pci_device *pdev,
        struct rt_pci_msix_entry *entries, int nvec,
        RT_IRQ_AFFINITY_DECLARE((*affinities)))
{
    rt_err_t err;
    rt_uint16_t msgctl;
    rt_size_t table_size;
    void *table_base, *table_entry;
    struct rt_pci_msi_desc *desc;
    struct rt_pci_msix_entry *entry;

    /*
     * Some devices require MSI-X to be enabled before the MSI-X
     * registers can be accessed.
     * Mask all the vectors to prevent interrupts coming in before
     * they're fully set up.
     */
    msix_update_ctrl(pdev, 0, PCIM_MSIXCTRL_FUNCTION_MASK | PCIM_MSIXCTRL_MSIX_ENABLE);

    rt_pci_read_config_u16(pdev, pdev->msix_cap + PCIR_MSIX_CTRL, &msgctl);
    /* Request & Map MSI-X table region */
    table_size = rt_pci_msix_table_size(msgctl);
    table_base = msix_table_remap(pdev, table_size);

    if (!table_base)
    {
        LOG_E("%s: Remap MSI-X table fail", rt_dm_dev_get_name(&pdev->parent));

        err = -RT_ENOMEM;
        goto _out_disbale_msix;
    }

    pdev->msix_base = table_base;

    spin_lock(&pdev->msi_lock);

    if (!(err = msix_setup_msi_descs(pdev, table_base, entries, nvec)))
    {
        if (!(err = rt_pci_msi_setup_irqs(pdev, nvec, PCIY_MSIX)))
        {
            /* Check if all MSI entries honor device restrictions */
            err = msi_verify_entries(pdev);
        }
    }

    spin_unlock(&pdev->msi_lock);

    if (err)
    {
        rt_pci_msi_free_irqs(pdev);

        LOG_E("%s: Setup %s interrupts(%d) error = %s",
                rt_dm_dev_get_name(&pdev->parent), "MSI-X", nvec, rt_strerror(err));

        goto _out_disbale_msix;
    }

    entry = entries;
    rt_pci_msi_for_each_desc(pdev, desc)
    {
        if (affinities)
        {
            msi_affinity_init(desc, desc->msix.index, affinities[entry->index]);
        }

        entry->irq = desc->irq;
        ++entry;
    }

    /* Disable INTX */
    rt_pci_intx(pdev, RT_FALSE);

    /* Maske all table entries */
    table_entry = table_base;
    for (int i = 0; i < table_size; ++i, table_entry += PCIM_MSIX_ENTRY_SIZE)
    {
        HWREG32(table_entry + PCIM_MSIX_ENTRY_VECTOR_CTRL) = PCIM_MSIX_ENTRYVECTOR_CTRL_MASK;
    }
    msix_update_ctrl(pdev, PCIM_MSIXCTRL_FUNCTION_MASK, 0);

    pdev->msix_enabled = RT_TRUE;

    return nvec;

_out_disbale_msix:
    msix_update_ctrl(pdev, PCIM_MSIXCTRL_FUNCTION_MASK | PCIM_MSIXCTRL_MSIX_ENABLE, 0);

    return err;
}

rt_ssize_t rt_pci_msix_enable_range_affinity(struct rt_pci_device *pdev,
        struct rt_pci_msix_entry *entries, int min, int max,
        RT_IRQ_AFFINITY_DECLARE((*affinities)))
{
    int nvec = max;
    rt_size_t entries_nr;

    if (!pdev || min > max)
    {
        return -RT_EINVAL;
    }

    if (pdev->no_msi)
    {
        return -RT_ENOSYS;
    }

    if (!pdev->msi_pic)
    {
        return -RT_ENOSYS;
    }

    if (pdev->msix_enabled)
    {
        LOG_W("%s: MSI-X is enabled", rt_dm_dev_get_name(&pdev->parent));

        return -RT_EINVAL;
    }

    entries_nr = rt_pci_msix_vector_count(pdev);

    if (entries_nr < 0)
    {
        return entries_nr;
    }

    if (nvec > entries_nr)
    {
        return -RT_EEMPTY;
    }

    if (!entries)
    {
        return 0;
    }

    /* Check if entries is valid */
    for (int i = 0; i < nvec; ++i)
    {
        struct rt_pci_msix_entry *target = &entries[i];

        if (target->index >= entries_nr)
        {
            return -RT_EINVAL;
        }

        for (int j = i + 1; j < nvec; ++j)
        {
            /* Check duplicate */
            if (target->index == entries[j].index)
            {
                LOG_E("%s: msix entry[%d].index = entry[%d].index",
                        rt_dm_dev_get_name(&pdev->parent), i, j);

                return -RT_EINVAL;
            }
        }
    }

    return msix_capability_init(pdev, entries, nvec, affinities);
}
