/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#define DBG_TAG "pcie.dw-ep"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pcie-dw.h"

struct dw_pcie_ep_func *dw_pcie_ep_get_func_from_ep(struct dw_pcie_ep *ep, rt_uint8_t func_no)
{
    struct dw_pcie_ep_func *ep_func;

    rt_list_for_each_entry(ep_func, &ep->func_nodes, list)
    {
        if (ep_func->func_no == func_no)
        {
            return ep_func;
        }
    }

    return RT_NULL;
}

static rt_uint8_t dw_pcie_ep_func_select(struct dw_pcie_ep *ep, rt_uint8_t func_no)
{
    rt_uint8_t func_offset = 0;

    if (ep->ops->func_select)
    {
        func_offset = ep->ops->func_select(ep, func_no);
    }

    return func_offset;
}

static void __dw_pcie_ep_reset_bar(struct dw_pcie *pci, rt_uint8_t func_no,
        int bar_idx, int flags)
{
    rt_uint32_t reg;
    rt_uint8_t func_offset = 0;
    struct dw_pcie_ep *ep = &pci->endpoint;

    func_offset = dw_pcie_ep_func_select(ep, func_no);
    reg = func_offset + PCIR_BAR(bar_idx);

    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);

    dw_pcie_writel_dbi2(pci, reg, 0x0);
    dw_pcie_writel_dbi(pci, reg, 0x0);

    if (flags & PCIM_BAR_MEM_TYPE_64)
    {
        dw_pcie_writel_dbi2(pci, reg + 4, 0x0);
        dw_pcie_writel_dbi(pci, reg + 4, 0x0);
    }

    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);
}

void dw_pcie_ep_reset_bar(struct dw_pcie *pci, int bar_idx)
{
    rt_uint8_t func_no, funcs = pci->endpoint.epc->max_functions;

    for (func_no = 0; func_no < funcs; ++func_no)
    {
        __dw_pcie_ep_reset_bar(pci, func_no, bar_idx, 0);
    }
}

static rt_uint8_t __dw_pcie_ep_find_next_cap(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        rt_uint8_t cap_ptr, rt_uint8_t cap)
{
    rt_uint16_t reg;
    rt_uint8_t func_offset = 0, cap_id, next_cap_ptr;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    if (!cap_ptr)
    {
        return 0;
    }

    func_offset = dw_pcie_ep_func_select(ep, func_no);
    reg = dw_pcie_readw_dbi(pci, func_offset + cap_ptr);
    cap_id = (reg & 0x00ff);

    if (cap_id > PCIY_MAX)
    {
        return 0;
    }

    if (cap_id == cap)
    {
        return cap_ptr;
    }

    next_cap_ptr = (reg & 0xff00) >> 8;
    return __dw_pcie_ep_find_next_cap(ep, func_no, next_cap_ptr, cap);
}

static rt_uint8_t dw_pcie_ep_find_capability(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        rt_uint8_t cap)
{
    rt_uint16_t reg;
    rt_uint8_t func_offset = 0, next_cap_ptr;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    func_offset = dw_pcie_ep_func_select(ep, func_no);
    reg = dw_pcie_readw_dbi(pci, func_offset + PCIR_CAP_PTR);
    next_cap_ptr = reg & 0x00ff;

    return __dw_pcie_ep_find_next_cap(ep, func_no, next_cap_ptr, cap);
}

rt_err_t dw_pcie_ep_inbound_atu(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        int bar_idx, rt_ubase_t cpu_addr, enum dw_pcie_aspace_type aspace_type)
{
    rt_err_t err;
    rt_uint32_t free_win;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    free_win = rt_bitmap_next_clear_bit(ep->ib_window_map, 0, ep->num_ib_windows);
    if (free_win >= ep->num_ib_windows)
    {
        LOG_E("No free inbound window");
        return -RT_EEMPTY;
    }

    err = dw_pcie_prog_inbound_atu(pci, func_no, free_win, bar_idx, cpu_addr, aspace_type);
    if (err)
    {
        LOG_E("Failed to program IB window error = %s", rt_strerror(err));
        return err;
    }

    ep->bar_to_atu[bar_idx] = free_win;
    rt_bitmap_set_bit(ep->ib_window_map, free_win);

    return RT_EOK;
}

rt_err_t dw_pcie_ep_outbound_atu(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        rt_ubase_t phys_addr, rt_uint64_t pci_addr, rt_size_t size)
{
    rt_uint32_t free_win;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    free_win = rt_bitmap_next_clear_bit(ep->ob_window_map, 0, ep->num_ob_windows);
    if (free_win >= ep->num_ob_windows)
    {
        LOG_E("No free outbound window");
        return -RT_EEMPTY;
    }

    dw_pcie_prog_ep_outbound_atu(pci, func_no, free_win, PCIE_ATU_TYPE_MEM,
            phys_addr, pci_addr, size);

    ep->outbound_addr[free_win] = phys_addr;
    rt_bitmap_set_bit(ep->ob_window_map, free_win);

    return RT_EOK;
}

static rt_err_t dw_pcie_ep_write_header(struct rt_pci_ep *epc, rt_uint8_t func_no,
        struct rt_pci_ep_header *hdr)
{
    rt_uint8_t func_offset = 0;
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    func_offset = dw_pcie_ep_func_select(ep, func_no);

    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);

    dw_pcie_writew_dbi(pci, func_offset + PCIR_VENDOR, hdr->vendor);
    dw_pcie_writew_dbi(pci, func_offset + PCIR_DEVICE, hdr->device);
    dw_pcie_writeb_dbi(pci, func_offset + PCIR_REVID, hdr->revision);
    dw_pcie_writeb_dbi(pci, func_offset + PCIR_PROGIF, hdr->progif);
    dw_pcie_writew_dbi(pci, func_offset + PCIR_SUBCLASS, hdr->subclass | hdr->class_code << 8);
    dw_pcie_writeb_dbi(pci, func_offset + PCIR_CACHELNSZ, hdr->cache_line_size);
    dw_pcie_writew_dbi(pci, func_offset + PCIR_SUBVEND_0, hdr->subsystem_vendor);
    dw_pcie_writew_dbi(pci, func_offset + PCIR_SUBDEV_0, hdr->subsystem_device);
    dw_pcie_writeb_dbi(pci, func_offset + PCIR_INTPIN, hdr->intx);

    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);

    return 0;
}

static rt_err_t dw_pcie_ep_clear_bar(struct rt_pci_ep *epc, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx)
{
    rt_uint32_t atu_index;
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    atu_index = ep->bar_to_atu[bar_idx];
    __dw_pcie_ep_reset_bar(pci, func_no, bar_idx, ep->epc_bar[bar_idx]->bus.flags);

    dw_pcie_disable_atu(pci, atu_index, DW_PCIE_REGION_INBOUND);
    rt_bitmap_clear_bit(ep->ib_window_map, atu_index);
    ep->epc_bar[bar_idx] = RT_NULL;

    return RT_EOK;
}

static rt_err_t dw_pcie_ep_set_bar(struct rt_pci_ep *epc, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx)
{
    rt_err_t err;
    rt_uint32_t reg;
    rt_uint8_t func_offset = 0;
    rt_size_t size = bar->bus.size;
    rt_ubase_t flags = bar->bus.flags;
    enum dw_pcie_aspace_type aspace_type;
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    func_offset = dw_pcie_ep_func_select(ep, func_no);
    reg = PCIR_BAR(bar_idx) + func_offset;

    if (!(flags & PCIM_BAR_SPACE))
    {
        aspace_type = DW_PCIE_ASPACE_MEM;
    }
    else
    {
        aspace_type = DW_PCIE_ASPACE_IO;
    }

    err = dw_pcie_ep_inbound_atu(ep, func_no, bar_idx, bar->bus.base, aspace_type);
    if (err)
    {
        return err;
    }

    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);

    dw_pcie_writel_dbi2(pci, reg, rt_lower_32_bits(size - 1));
    dw_pcie_writel_dbi(pci, reg, flags);

    if (flags & PCIM_BAR_MEM_TYPE_64)
    {
        dw_pcie_writel_dbi2(pci, reg + 4, rt_upper_32_bits(size - 1));
        dw_pcie_writel_dbi(pci, reg + 4, 0);
    }

    ep->epc_bar[bar_idx] = bar;
    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);

    return 0;
}

static rt_err_t dw_pcie_find_index(struct dw_pcie_ep *ep,
        rt_ubase_t addr, rt_uint32_t *atu_index)
{
    for (rt_uint32_t index = 0; index < ep->num_ob_windows; ++index)
    {
        if (ep->outbound_addr[index] != addr)
        {
            continue;
        }

        *atu_index = index;

        return RT_EOK;
    }

    return -RT_EINVAL;
}

static rt_err_t dw_pcie_ep_unmap_addr(struct rt_pci_ep *epc, rt_uint8_t func_no,
        rt_ubase_t addr)
{
    rt_err_t err;
    rt_uint32_t atu_index;
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    if ((err = dw_pcie_find_index(ep, addr, &atu_index)))
    {
        return err;
    }

    dw_pcie_disable_atu(pci, atu_index, DW_PCIE_REGION_OUTBOUND);
    rt_bitmap_clear_bit(ep->ob_window_map, atu_index);

    return RT_EOK;
}

static rt_err_t dw_pcie_ep_map_addr(struct rt_pci_ep *epc, rt_uint8_t func_no,
        rt_ubase_t addr, rt_uint64_t pci_addr, rt_size_t size)
{
    rt_err_t err;
    struct dw_pcie_ep *ep = epc->priv;

    err = dw_pcie_ep_outbound_atu(ep, func_no, addr, pci_addr, size);
    if (err)
    {
        LOG_E("Failed to enable address error = %s", rt_strerror(err));
        return err;
    }

    return RT_EOK;
}

static rt_err_t dw_pcie_ep_set_msi(struct rt_pci_ep *epc, rt_uint8_t func_no,
        unsigned irq_nr)
{
    rt_uint32_t val, reg;
    rt_uint8_t func_offset = 0;
    struct dw_pcie_ep_func *ep_func;
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
    if (!ep_func || !ep_func->msi_cap)
    {
        return -RT_EINVAL;
    }

    func_offset = dw_pcie_ep_func_select(ep, func_no);
    reg = ep_func->msi_cap + func_offset + PCIR_MSI_CTRL;

    val = dw_pcie_readw_dbi(pci, reg);
    val &= ~PCIM_MSICTRL_MMC_MASK;
    val |= (irq_nr << 1) & PCIM_MSICTRL_MMC_MASK;

    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);
    dw_pcie_writew_dbi(pci, reg, val);
    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);

    return RT_EOK;
}

static rt_err_t dw_pcie_ep_get_msi(struct rt_pci_ep *epc, rt_uint8_t func_no,
        unsigned *out_irq_nr)
{
    rt_uint32_t val, reg;
    rt_uint8_t func_offset = 0;
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie_ep_func *ep_func;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
    if (!ep_func || !ep_func->msi_cap)
    {
        return -RT_EINVAL;
    }

    func_offset = dw_pcie_ep_func_select(ep, func_no);
    reg = ep_func->msi_cap + func_offset + PCIR_MSI_CTRL;

    val = dw_pcie_readw_dbi(pci, reg);
    if (!(val & PCIM_MSICTRL_MSI_ENABLE))
    {
        return -RT_EINVAL;
    }

    *out_irq_nr = (val & PCIM_MSICTRL_MME_MASK) >> 4;

    return RT_EOK;
}

static rt_err_t dw_pcie_ep_set_msix(struct rt_pci_ep *epc, rt_uint8_t func_no,
        unsigned irq_nr, int bar_idx, rt_off_t offset)
{
    rt_uint32_t val, reg;
    rt_uint8_t func_offset = 0;
    struct dw_pcie_ep_func *ep_func;
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
    if (!ep_func || !ep_func->msix_cap)
    {
        return -RT_EINVAL;
    }

    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);

    func_offset = dw_pcie_ep_func_select(ep, func_no);
    reg = ep_func->msix_cap + func_offset + PCIR_MSIX_CTRL;

    val = dw_pcie_readw_dbi(pci, reg);
    val &= ~PCIM_MSIXCTRL_TABLE_SIZE;
    val |= irq_nr;
    dw_pcie_writew_dbi(pci, reg, val);

    reg = ep_func->msix_cap + func_offset + PCIR_MSIX_TABLE;
    val = offset | bar_idx;
    dw_pcie_writel_dbi(pci, reg, val);

    reg = ep_func->msix_cap + func_offset + PCIR_MSIX_PBA;
    val = (offset + (irq_nr * PCIM_MSIX_ENTRY_SIZE)) | bar_idx;
    dw_pcie_writel_dbi(pci, reg, val);

    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);

    return RT_EOK;
}

static rt_err_t dw_pcie_ep_get_msix(struct rt_pci_ep *epc, rt_uint8_t func_no,
        unsigned *out_irq_nr)
{
    rt_uint32_t val, reg;
    rt_uint8_t func_offset = 0;
    struct dw_pcie_ep_func *ep_func;
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
    if (!ep_func || !ep_func->msix_cap)
    {
        return -RT_EINVAL;
    }

    func_offset = dw_pcie_ep_func_select(ep, func_no);
    reg = ep_func->msix_cap + func_offset + PCIR_MSIX_CTRL;

    val = dw_pcie_readw_dbi(pci, reg);
    if (!(val & PCIM_MSIXCTRL_MSIX_ENABLE))
    {
        return -RT_EINVAL;
    }

    *out_irq_nr = val & PCIM_MSIXCTRL_TABLE_SIZE;

    return RT_EOK;
}

static rt_err_t dw_pcie_ep_raise_irq(struct rt_pci_ep *epc, rt_uint8_t func_no,
        enum rt_pci_ep_irq type, unsigned irq)
{
    struct dw_pcie_ep *ep = epc->priv;

    if (!ep->ops->raise_irq)
    {
        return -RT_ENOSYS;
    }

    return ep->ops->raise_irq(ep, func_no, type, irq);
}

static rt_err_t dw_pcie_ep_stop(struct rt_pci_ep *epc)
{
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    if (pci->ops->stop_link)
    {
        pci->ops->stop_link(pci);
    }

    return RT_EOK;
}

static rt_err_t dw_pcie_ep_start(struct rt_pci_ep *epc)
{
    struct dw_pcie_ep *ep = epc->priv;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    if (pci->ops->start_link)
    {
        return pci->ops->start_link(pci);
    }

    return RT_EOK;
}

static const struct rt_pci_ep_ops dw_pcie_ep_ops =
{
    .write_header   = dw_pcie_ep_write_header,
    .set_bar        = dw_pcie_ep_set_bar,
    .clear_bar      = dw_pcie_ep_clear_bar,
    .map_addr       = dw_pcie_ep_map_addr,
    .unmap_addr     = dw_pcie_ep_unmap_addr,
    .set_msi        = dw_pcie_ep_set_msi,
    .get_msi        = dw_pcie_ep_get_msi,
    .set_msix       = dw_pcie_ep_set_msix,
    .get_msix       = dw_pcie_ep_get_msix,
    .raise_irq      = dw_pcie_ep_raise_irq,
    .start          = dw_pcie_ep_start,
    .stop           = dw_pcie_ep_stop,
};

rt_err_t dw_pcie_ep_raise_legacy_irq(struct dw_pcie_ep *ep, rt_uint8_t func_no)
{
    LOG_E("EP cannot trigger legacy IRQs");

    return -RT_EINVAL;
}

rt_err_t dw_pcie_ep_raise_msi_irq(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        unsigned irq)
{
    rt_err_t err;
    rt_off_t aligned_offset;
    rt_uint8_t func_offset = 0;
    rt_uint64_t msg_addr;
    rt_uint16_t msg_ctrl, msg_data;
    rt_uint32_t msg_addr_lower, msg_addr_upper, reg;
    struct rt_pci_ep *epc = ep->epc;
    struct dw_pcie_ep_func *ep_func;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
    if (!ep_func || !ep_func->msi_cap)
    {
        return -RT_EINVAL;
    }

    func_offset = dw_pcie_ep_func_select(ep, func_no);

    /* Raise MSI per the PCI Local Bus Specification Revision 3.0, 6.8.1. */
    reg = ep_func->msi_cap + func_offset + PCIR_MSI_CTRL;
    msg_ctrl = dw_pcie_readw_dbi(pci, reg);
    reg = ep_func->msi_cap + func_offset + PCIR_MSI_ADDR;
    msg_addr_lower = dw_pcie_readl_dbi(pci, reg);

    if (!!(msg_ctrl & PCIM_MSICTRL_64BIT))
    {
        reg = ep_func->msi_cap + func_offset + PCIR_MSI_ADDR_HIGH;
        msg_addr_upper = dw_pcie_readl_dbi(pci, reg);
        reg = ep_func->msi_cap + func_offset + PCIR_MSI_DATA_64BIT;
        msg_data = dw_pcie_readw_dbi(pci, reg);
    }
    else
    {
        msg_addr_upper = 0;
        reg = ep_func->msi_cap + func_offset + PCIR_MSI_DATA;
        msg_data = dw_pcie_readw_dbi(pci, reg);
    }

    aligned_offset = msg_addr_lower & (ep->page_size - 1);
    msg_addr = ((rt_uint64_t)msg_addr_upper << 32) | (msg_addr_lower & ~aligned_offset);

    if ((err = dw_pcie_ep_map_addr(epc, func_no, ep->msi_mem_phy, msg_addr, ep->page_size)))
    {
        return err;
    }

    HWREG32(ep->msi_mem + aligned_offset) = msg_data | (irq - 1);
    dw_pcie_ep_unmap_addr(epc, func_no, ep->msi_mem_phy);

    return RT_EOK;
}

rt_err_t dw_pcie_ep_raise_msix_irq_doorbell(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        unsigned irq)
{
    rt_uint32_t msg_data;
    struct dw_pcie_ep_func *ep_func;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
    if (!ep_func || !ep_func->msix_cap)
    {
        return -RT_EINVAL;
    }

    msg_data = (func_no << PCIE_MSIX_DOORBELL_PF_SHIFT) | (irq - 1);
    dw_pcie_writel_dbi(pci, PCIE_MSIX_DOORBELL, msg_data);

    return RT_EOK;
}

rt_err_t dw_pcie_ep_raise_msix_irq(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        unsigned irq)
{
    rt_err_t err;
    int bar_idx;
    rt_uint64_t msg_addr;
    rt_uint32_t tbl_offset;
    rt_off_t aligned_offset;
    rt_uint8_t func_offset = 0;
    rt_uint32_t reg, msg_data, vec_ctrl;
    struct rt_pci_ep *epc = ep->epc;
    struct rt_pci_ep_msix_tbl *msix_tbl;
    struct dw_pcie_ep_func *ep_func;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    ep_func = dw_pcie_ep_get_func_from_ep(ep, func_no);
    if (!ep_func || !ep_func->msix_cap)
    {
        return -RT_EINVAL;
    }

    func_offset = dw_pcie_ep_func_select(ep, func_no);
    reg = ep_func->msix_cap + func_offset + PCIR_MSIX_TABLE;

    tbl_offset = dw_pcie_readl_dbi(pci, reg);
    bar_idx = (tbl_offset & PCIM_MSIX_BIR_MASK);
    tbl_offset &= PCIM_MSIX_TABLE_OFFSET;

    msix_tbl = (void *)ep->epc_bar[bar_idx]->cpu_addr + tbl_offset;
    msg_addr = msix_tbl[(irq - 1)].msg_addr;
    msg_data = msix_tbl[(irq - 1)].msg_data;
    vec_ctrl = msix_tbl[(irq - 1)].vector_ctrl;

    if (vec_ctrl & PCIM_MSIX_ENTRYVECTOR_CTRL_MASK)
    {
        return -RT_EINVAL;
    }

    aligned_offset = msg_addr & (ep->page_size - 1);

    if ((err = dw_pcie_ep_map_addr(epc, func_no, ep->msi_mem_phy, msg_addr, ep->page_size)))
    {
        return err;
    }

    HWREG32(ep->msi_mem + aligned_offset) = msg_data;
    dw_pcie_ep_unmap_addr(epc, func_no, ep->msi_mem_phy);

    return RT_EOK;
}

void dw_pcie_ep_exit(struct dw_pcie_ep *ep)
{
    struct rt_pci_ep *epc = ep->epc;

    if (ep->msi_mem)
    {
        rt_pci_ep_mem_free(epc, ep->msi_mem, ep->msi_mem_phy, ep->page_size);
    }

    if (!rt_list_isempty(&ep->func_nodes))
    {
        struct dw_pcie_ep_func *ep_func, *ep_func_next;

        rt_list_for_each_entry_safe(ep_func, ep_func_next, &ep->func_nodes, list)
        {
            rt_list_remove(&ep_func->list);
            rt_free(ep_func);
        }
    }

    if (ep->ib_window_map)
    {
        rt_free(ep->ib_window_map);
    }

    if (ep->ob_window_map)
    {
        rt_free(ep->ob_window_map);
    }

    if (ep->outbound_addr)
    {
        rt_free(ep->outbound_addr);
    }

    if (epc)
    {
        rt_free(epc);
    }
}

static rt_uint32_t dw_pcie_ep_find_ext_capability(struct dw_pcie *pci, int cap)
{
    rt_uint32_t header;
    int pos = (PCI_REGMAX + 1);

    while (pos)
    {
        header = dw_pcie_readl_dbi(pci, pos);

        if (PCI_EXTCAP_ID(header) == cap)
        {
            return pos;
        }

        if (!(pos = PCI_EXTCAP_NEXTPTR(header)))
        {
            break;
        }
    }

    return 0;
}

rt_err_t dw_pcie_ep_init_complete(struct dw_pcie_ep *ep)
{
    rt_off_t offset;
    rt_size_t bar_nr;
    rt_uint32_t reg;
    rt_uint8_t hdr_type;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);

    hdr_type = dw_pcie_readb_dbi(pci, PCIR_HDRTYPE) & PCIM_HDRTYPE;
    if (hdr_type != PCIM_HDRTYPE_NORMAL)
    {
        LOG_E("PCIe controller is not set to EP mode hdr_type = %x", hdr_type);
        return -RT_EIO;
    }

    offset = dw_pcie_ep_find_ext_capability(pci, PCIZ_RESIZE_BAR);

    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);

    if (offset)
    {
        reg = dw_pcie_readl_dbi(pci, offset + PCIM_REBAR_CTRL);
        bar_nr = (reg & PCIM_REBAR_CTRL_NBAR_MASK) >> PCIM_REBAR_CTRL_NBAR_SHIFT;

        for (int i = 0; i < bar_nr; ++i, offset += PCIM_REBAR_CTRL)
        {
            dw_pcie_writel_dbi(pci, offset + PCIM_REBAR_CAP, 0x0);
        }
    }

    dw_pcie_setup(pci);
    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);

    return RT_EOK;
}

rt_err_t dw_pcie_ep_init(struct dw_pcie_ep *ep)
{
    rt_err_t err;
    struct rt_pci_ep *epc = RT_NULL;
    struct dw_pcie_ep_func *ep_func;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);
    struct rt_device *dev = pci->dev;

    rt_list_init(&ep->func_nodes);

    if (!pci->dbi_base || !pci->dbi_base2)
    {
        LOG_E("dbi_base/dbi_base2 is not populated");
        return -RT_EINVAL;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "num-ib-windows", &ep->num_ib_windows)))
    {
        LOG_E("Unable to read 'num-ib-windows' property");
        return err;
    }

    if (ep->num_ib_windows > MAX_IATU_IN)
    {
        LOG_E("Invalid 'num-ib-windows'");
        return -RT_EINVAL;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "num-ob-windows", &ep->num_ob_windows)))
    {
        LOG_E("Unable to read 'num-ob-windows' property");
        return err;
    }

    if (ep->num_ob_windows > MAX_IATU_OUT)
    {
        LOG_E("Invalid 'num-ob-windows'");
        return -RT_EINVAL;
    }

    ep->ib_window_map = rt_calloc(RT_BITMAP_LEN(ep->num_ib_windows), sizeof(rt_bitmap_t));
    if (!ep->ib_window_map)
    {
        return -RT_ENOMEM;
    }

    ep->ob_window_map = rt_calloc(RT_BITMAP_LEN(ep->num_ob_windows), sizeof(rt_bitmap_t));
    if (!ep->ob_window_map)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    ep->outbound_addr = rt_calloc(ep->num_ob_windows, sizeof(rt_ubase_t));
    if (!ep->outbound_addr)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    if (pci->link_gen < 1)
    {
        pci->link_gen = -1;
        rt_dm_dev_prop_read_u32(dev, "max-link-speed", &pci->link_gen);
    }

    epc = rt_calloc(1, sizeof(*epc));
    if (!epc)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    epc->name = rt_dm_dev_get_name(dev);
    epc->rc_dev = dev;
    epc->ops = &dw_pcie_ep_ops;
    epc->priv = ep;

    if ((err = rt_pci_ep_register(epc)))
    {
        goto _fail;
    }
    ep->epc = epc;

    if (rt_dm_dev_prop_read_u8(dev, "max-functions", &epc->max_functions))
    {
        epc->max_functions = 1;
    }

    for (rt_uint8_t func_no = 0; func_no < epc->max_functions; ++func_no)
    {
        ep_func = rt_calloc(1, sizeof(*ep_func));

        if (!ep_func)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }

        ep_func->func_no = func_no;
        ep_func->msi_cap = dw_pcie_ep_find_capability(ep, func_no, PCIY_MSI);
        ep_func->msix_cap = dw_pcie_ep_find_capability(ep, func_no, PCIY_MSIX);

        rt_list_init(&ep_func->list);
        rt_list_insert_after(&ep->func_nodes, &ep_func->list);
    }

    if (ep->ops->ep_init)
    {
        ep->ops->ep_init(ep);
    }

    if ((err = rt_pci_ep_mem_init(epc, ep->aspace, ep->aspace_size, ep->page_size)))
    {
        goto _fail;
    }

    ep->msi_mem = rt_pci_ep_mem_alloc(epc, &ep->msi_mem_phy, ep->page_size);

    if (!ep->msi_mem)
    {
        LOG_E("Failed to reserve memory for MSI/MSI-X");
        err = -RT_ENOMEM;
        goto _fail;
    }

    if ((err = dw_pcie_ep_init_complete(ep)))
    {
        goto _fail;
    }

    return RT_EOK;

_fail:
    dw_pcie_ep_exit(ep);

    return err;
}
