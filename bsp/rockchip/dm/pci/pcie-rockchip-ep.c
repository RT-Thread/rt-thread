/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#define DBG_TAG "pcie.rk-ep"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pcie-rockchip.h"

struct rockchip_pcie_ep
{
    struct rockchip_pcie rk_pcie;
    struct rt_pci_ep epc;

    rt_ubase_t *ob_addr;
    rt_uint32_t max_regions;
    rt_bitmap_t ob_region_map;
    rt_slab_t addr_slab;

    void *irq_cpu_addr;
    rt_ubase_t irq_phys_addr;
    rt_uint64_t irq_pci_addr;
    rt_uint8_t irq_pci_fn;
    rt_uint8_t irq_pending;
};

rt_inline int __fls64(rt_uint64_t x)
{
    const rt_uint64_t bits_per_u64 = (sizeof(x) * 8);
    int num = bits_per_u64 - 1;

    if (x == 0)
    {
        return 0;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 32))))
    {
        num -= 32;
        x <<= 32;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 16))))
    {
        num -= 16;
        x <<= 16;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 8))))
    {
        num -= 8;
        x <<= 8;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 4))))
    {
        num -= 4;
        x <<= 4;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 2))))
    {
        num -= 2;
        x <<= 2;
    }

    if (!(x & (~0ULL << (bits_per_u64 - 1))))
    {
        num -= 1;
    }

    return num + 1;
}

static void rockchip_pcie_clear_ep_ob_atu(struct rockchip_pcie *rk_pcie,
        rt_uint32_t region)
{
    rockchip_pcie_write(rk_pcie, 0, RK_PCIE_AT_OB_REGION_PCI_ADDR0(region));
    rockchip_pcie_write(rk_pcie, 0, RK_PCIE_AT_OB_REGION_PCI_ADDR1(region));
    rockchip_pcie_write(rk_pcie, 0, RK_PCIE_AT_OB_REGION_DESC0(region));
    rockchip_pcie_write(rk_pcie, 0, RK_PCIE_AT_OB_REGION_DESC1(region));
    rockchip_pcie_write(rk_pcie, 0, RK_PCIE_AT_OB_REGION_CPU_ADDR0(region));
    rockchip_pcie_write(rk_pcie, 0, RK_PCIE_AT_OB_REGION_CPU_ADDR1(region));
}

static void rockchip_pcie_prog_ep_ob_atu(struct rockchip_pcie *rk_pcie,
        rt_uint8_t func_no, rt_uint32_t r, rt_uint32_t type,
        rt_uint64_t cpu_addr, rt_uint64_t pci_addr, rt_size_t size)
{
    rt_uint64_t sz = 1ULL << __fls64(size - 1);
    int num_pass_bits = rt_ilog2(sz);
    rt_uint32_t addr0, addr1, desc0, desc1;
    rt_bool_t is_nor_msg = (type == AXI_WRAPPER_NOR_MSG);

    /* The minimal region size is 1MB */
    if (num_pass_bits < 8)
    {
        num_pass_bits = 8;
    }

    cpu_addr -= rk_pcie->mem_base_addr;
    addr0 = ((is_nor_msg ? 0x10 : (num_pass_bits - 1)) &
            PCIE_CORE_OB_REGION_ADDR0_NUM_BITS) |
            (rt_lower_32_bits(cpu_addr) & PCIE_CORE_OB_REGION_ADDR0_LO_ADDR);
    addr1 = rt_upper_32_bits(is_nor_msg ? cpu_addr : pci_addr);
    desc0 = RK_PCIE_AT_OB_REGION_DESC0_DEVFN(func_no) | type;
    desc1 = 0;

    if (is_nor_msg)
    {
        rockchip_pcie_write(rk_pcie, 0, RK_PCIE_AT_OB_REGION_PCI_ADDR0(r));
        rockchip_pcie_write(rk_pcie, 0, RK_PCIE_AT_OB_REGION_PCI_ADDR1(r));
        rockchip_pcie_write(rk_pcie, desc0, RK_PCIE_AT_OB_REGION_DESC0(r));
        rockchip_pcie_write(rk_pcie, desc1, RK_PCIE_AT_OB_REGION_DESC1(r));
    }
    else
    {
        /* PCI bus address region */
        rockchip_pcie_write(rk_pcie, addr0, RK_PCIE_AT_OB_REGION_PCI_ADDR0(r));
        rockchip_pcie_write(rk_pcie, addr1, RK_PCIE_AT_OB_REGION_PCI_ADDR1(r));
        rockchip_pcie_write(rk_pcie, desc0, RK_PCIE_AT_OB_REGION_DESC0(r));
        rockchip_pcie_write(rk_pcie, desc1, RK_PCIE_AT_OB_REGION_DESC1(r));

        addr0 = ((num_pass_bits - 1) & PCIE_CORE_OB_REGION_ADDR0_NUM_BITS) |
                (rt_lower_32_bits(cpu_addr) & PCIE_CORE_OB_REGION_ADDR0_LO_ADDR);
        addr1 = rt_upper_32_bits(cpu_addr);
    }

    /* CPU bus address region */
    rockchip_pcie_write(rk_pcie, addr0, RK_PCIE_AT_OB_REGION_CPU_ADDR0(r));
    rockchip_pcie_write(rk_pcie, addr1, RK_PCIE_AT_OB_REGION_CPU_ADDR1(r));
}

static rt_err_t rockchip_pcie_ep_write_header(struct rt_pci_ep *epc, rt_uint8_t func_no,
        struct rt_pci_ep_header *hdr)
{
    rt_uint32_t reg;
    struct rockchip_pcie_ep *ep = epc->priv;
    struct rockchip_pcie *rk_pcie = &ep->rk_pcie;

    /* All functions share the same vendor ID with function 0 */
    if (func_no == 0)
    {
        rt_uint32_t vid_regs = (hdr->vendor & RT_GENMASK(15, 0)) |
                (hdr->subsystem_vendor & RT_GENMASK(31, 16)) << 16;

        rockchip_pcie_write(rk_pcie, vid_regs, PCIE_CORE_CONFIG_VENDOR);
    }

    reg = rockchip_pcie_read(rk_pcie, PCIE_EP_CONFIG_DID_VID);
    reg = (reg & 0xffff) | (hdr->device << 16);
    rockchip_pcie_write(rk_pcie, reg, PCIE_EP_CONFIG_DID_VID);

    rockchip_pcie_write(rk_pcie,
            hdr->revision | hdr->progif << 8 |
            hdr->subclass << 16 | hdr->class_code << 24,
            RK_PCIE_EP_FUNC_BASE(func_no) + PCIR_REVID);
    rockchip_pcie_write(rk_pcie, hdr->cache_line_size,
            RK_PCIE_EP_FUNC_BASE(func_no) + PCIR_CACHELNSZ);
    rockchip_pcie_write(rk_pcie, hdr->subsystem_device << 16,
            RK_PCIE_EP_FUNC_BASE(func_no) + PCIR_SUBVEND_0);
    rockchip_pcie_write(rk_pcie, hdr->intx << 8,
            RK_PCIE_EP_FUNC_BASE(func_no) + PCIR_INTPIN);

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_set_bar(struct rt_pci_ep *epc, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx)
{
    rt_uint64_t sz;
    rt_ubase_t bar_phys, flags = bar->bus.flags;
    rt_uint32_t addr0, addr1, reg, cfg, b, aperture, ctrl;
    struct rockchip_pcie_ep *ep = epc->priv;
    struct rockchip_pcie *rk_pcie = &ep->rk_pcie;

    bar_phys = bar->bus.base;
    sz = rt_max_t(rt_size_t, bar->bus.size, MIN_EP_APERTURE);
    sz = 1ULL << __fls64(sz - 1);
    aperture = rt_ilog2(sz) - 7;

    if ((flags & PCIM_BAR_SPACE) == PCIM_BAR_SPACE_IO)
    {
        ctrl = RK_PCIE_CORE_BAR_CFG_CTRL_IO_32BITS;
    }
    else
    {
        rt_bool_t is_prefetch = !!(flags & PCIM_BAR_MEM_PREFETCH);
        rt_bool_t is_64bits = sz > (2UL * SIZE_GB);

        if (is_64bits && (bar_idx & 1))
        {
            return -RT_EINVAL;
        }

        if (is_64bits && is_prefetch)
        {
            ctrl = RK_PCIE_CORE_BAR_CFG_CTRL_PREFETCH_MEM_64BITS;
        }
        else if (is_prefetch)
        {
            ctrl = RK_PCIE_CORE_BAR_CFG_CTRL_PREFETCH_MEM_32BITS;
        }
        else if (is_64bits)
        {
            ctrl = RK_PCIE_CORE_BAR_CFG_CTRL_MEM_64BITS;
        }
        else
        {
            ctrl = RK_PCIE_CORE_BAR_CFG_CTRL_MEM_32BITS;
        }
    }

    if (bar_idx < 4)
    {
        reg = RK_PCIE_CORE_EP_FUNC_BAR_CFG0(func_no);
        b = bar_idx;
    }
    else
    {
        reg = RK_PCIE_CORE_EP_FUNC_BAR_CFG1(func_no);
        b = bar_idx - 4;
    }

    addr0 = rt_lower_32_bits(bar_phys);
    addr1 = rt_upper_32_bits(bar_phys);

    cfg = rockchip_pcie_read(rk_pcie, reg);
    cfg &= ~(RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
            RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
    cfg |= (RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE(b, aperture) |
            RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl));

    rockchip_pcie_write(rk_pcie, cfg, reg);
    rockchip_pcie_write(rk_pcie, addr0, RK_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(func_no, bar_idx));
    rockchip_pcie_write(rk_pcie, addr1, RK_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(func_no, bar_idx));

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_clear_bar(struct rt_pci_ep *epc, rt_uint8_t func_no,
        struct rt_pci_ep_bar *bar, int bar_idx)
{
    rt_uint32_t reg, cfg, b, ctrl;
    struct rockchip_pcie_ep *ep = epc->priv;
    struct rockchip_pcie *rk_pcie = &ep->rk_pcie;

    if (bar_idx < 4)
    {
        reg = RK_PCIE_CORE_EP_FUNC_BAR_CFG0(func_no);
        b = bar_idx;
    }
    else
    {
        reg = RK_PCIE_CORE_EP_FUNC_BAR_CFG1(func_no);
        b = bar_idx - 4;
    }

    ctrl = RK_PCIE_CORE_BAR_CFG_CTRL_DISABLED;
    cfg = rockchip_pcie_read(rk_pcie, reg);
    cfg &= ~(RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_APERTURE_MASK(b) |
            RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL_MASK(b));
    cfg |= RK_PCIE_CORE_EP_FUNC_BAR_CFG_BAR_CTRL(b, ctrl);

    rockchip_pcie_write(rk_pcie, cfg, reg);
    rockchip_pcie_write(rk_pcie, 0x0, RK_PCIE_AT_IB_EP_FUNC_BAR_ADDR0(func_no, bar_idx));
    rockchip_pcie_write(rk_pcie, 0x0, RK_PCIE_AT_IB_EP_FUNC_BAR_ADDR1(func_no, bar_idx));

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_map_addr(struct rt_pci_ep *epc, rt_uint8_t func_no,
        rt_ubase_t addr, rt_uint64_t pci_addr, rt_size_t size)
{
    struct rockchip_pcie_ep *ep = epc->priv;
    struct rockchip_pcie *pcie = &ep->rk_pcie;
    rt_uint32_t r;

    r = rt_bitmap_next_clear_bit(&ep->ob_region_map, 0, RT_BITS_PER_LONG);
    /*
     * Region 0 is reserved for configuration space and shouldn't
     * be used elsewhere per TRM, so leave it out.
     */
    if (r >= ep->max_regions - 1)
    {
        return -RT_EINVAL;
    }

    rockchip_pcie_prog_ep_ob_atu(pcie, func_no, r, AXI_WRAPPER_MEM_WRITE,
            addr, pci_addr, size);

    rt_bitmap_set_bit(&ep->ob_region_map, r);
    ep->ob_addr[r] = addr;

    return 0;
}

static rt_err_t rockchip_pcie_ep_unmap_addr(struct rt_pci_ep *epc, rt_uint8_t func_no,
        rt_ubase_t addr)
{
    rt_uint32_t r;
    struct rockchip_pcie_ep *ep = epc->priv;
    struct rockchip_pcie *rk_pcie = &ep->rk_pcie;

    for (r = 0; r < ep->max_regions - 1; ++r)
    {
        if (ep->ob_addr[r] == addr)
        {
            break;
        }
    }

    /*
     * Region 0 is reserved for configuration space and shouldn't
     * be used elsewhere per TRM, so leave it out.
     */
    if (r == ep->max_regions - 1)
    {
        return RT_EOK;
    }

    rockchip_pcie_clear_ep_ob_atu(rk_pcie, r);

    ep->ob_addr[r] = 0;
    rt_bitmap_clear_bit(&ep->ob_region_map, r);

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_set_msi(struct rt_pci_ep *epc, rt_uint8_t func_no,
        unsigned irq_nr)
{
    rt_uint32_t flags;
    struct rockchip_pcie_ep *ep = epc->priv;
    struct rockchip_pcie *rk_pcie = &ep->rk_pcie;

    flags = rockchip_pcie_read(rk_pcie, RK_PCIE_EP_FUNC_BASE(func_no) +
            RK_PCIE_EP_MSI_CTRL_REG);
    flags &= ~RK_PCIE_EP_MSI_CTRL_MMC_MASK;
    flags |= (irq_nr << RK_PCIE_EP_MSI_CTRL_MMC_OFFSET) |
            (PCIM_MSICTRL_64BIT << RK_PCIE_EP_MSI_FLAGS_OFFSET);
    flags &= ~RK_PCIE_EP_MSI_CTRL_MASK_MSI_CAP;
    rockchip_pcie_write(rk_pcie, flags, RK_PCIE_EP_FUNC_BASE(func_no) +
            RK_PCIE_EP_MSI_CTRL_REG);

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_get_msi(struct rt_pci_ep *epc, rt_uint8_t func_no,
        unsigned *out_irq_nr)
{
    rt_uint32_t flags;
    struct rockchip_pcie_ep *ep = epc->priv;
    struct rockchip_pcie *rk_pcie = &ep->rk_pcie;

    flags = rockchip_pcie_read(rk_pcie, RK_PCIE_EP_FUNC_BASE(func_no) +
            RK_PCIE_EP_MSI_CTRL_REG);

    if (!(flags & RK_PCIE_EP_MSI_CTRL_ME))
    {
        return -RT_EINVAL;
    }

    *out_irq_nr = ((flags & RK_PCIE_EP_MSI_CTRL_MME_MASK) >> RK_PCIE_EP_MSI_CTRL_MME_OFFSET);
    return RT_EOK;
}

static void rockchip_pcie_ep_assert_intx(struct rockchip_pcie_ep *ep,
        rt_uint8_t func_no, rt_uint8_t intx, rt_bool_t do_assert)
{
    struct rockchip_pcie *rk_pcie = &ep->rk_pcie;

    intx &= 3;

    if (do_assert)
    {
        ep->irq_pending |= RT_BIT(intx);
        rockchip_pcie_write(rk_pcie, PCIE_CLIENT_INT_IN_ASSERT |
                PCIE_CLIENT_INT_PEND_ST_PEND, PCIE_CLIENT_LEGACY_INT_CTRL);
    }
    else
    {
        ep->irq_pending &= ~RT_BIT(intx);
        rockchip_pcie_write(rk_pcie, PCIE_CLIENT_INT_IN_DEASSERT |
                PCIE_CLIENT_INT_PEND_ST_NORMAL, PCIE_CLIENT_LEGACY_INT_CTRL);
    }
}

static rt_err_t rockchip_pcie_ep_send_legacy_irq(struct rockchip_pcie_ep *ep,
        rt_uint8_t func_no, rt_uint8_t intx)
{
    rt_uint16_t cmd;

    cmd = rockchip_pcie_read(&ep->rk_pcie, RK_PCIE_EP_FUNC_BASE(func_no) +
            RK_PCIE_EP_CMD_STATUS);

    if (cmd & PCIM_CMD_INTxDIS)
    {
        return -RT_EINVAL;
    }

    /*
     * Should add some delay between toggling INTx per TRM vaguely saying
     * it depends on some cycles of the AHB bus clock to function it. So
     * add sufficient 1ms here.
     */
    rockchip_pcie_ep_assert_intx(ep, func_no, intx, RT_TRUE);
    rt_thread_mdelay(1);
    rockchip_pcie_ep_assert_intx(ep, func_no, intx, RT_FALSE);

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_send_msi_irq(struct rockchip_pcie_ep *ep,
        rt_uint8_t func_no, unsigned irq_nr)
{
    rt_uint8_t msi_count;
    rt_uint32_t flags, mme, data, data_mask;
    rt_uint64_t pci_addr, pci_addr_mask = 0xff;
    struct rockchip_pcie *rk_pcie = &ep->rk_pcie;

    /* Check MSI enable bit */
    flags = rockchip_pcie_read(&ep->rk_pcie, RK_PCIE_EP_FUNC_BASE(func_no) +
            RK_PCIE_EP_MSI_CTRL_REG);

    if (!(flags & RK_PCIE_EP_MSI_CTRL_ME))
    {
        return -RT_EINVAL;
    }

    /* Get MSI numbers from MME */
    mme = ((flags & RK_PCIE_EP_MSI_CTRL_MME_MASK) >> RK_PCIE_EP_MSI_CTRL_MME_OFFSET);
    msi_count = 1 << mme;
    if (!irq_nr || irq_nr > msi_count)
    {
        return -RT_EINVAL;
    }

    /* Set MSI private data */
    data_mask = msi_count - 1;
    data = rockchip_pcie_read(rk_pcie, RK_PCIE_EP_FUNC_BASE(func_no) +
            RK_PCIE_EP_MSI_CTRL_REG + PCIR_MSI_DATA_64BIT);
    data = (data & ~data_mask) | ((irq_nr - 1) & data_mask);

    /* Get MSI PCI address */
    pci_addr = rockchip_pcie_read(rk_pcie, RK_PCIE_EP_FUNC_BASE(func_no) +
            RK_PCIE_EP_MSI_CTRL_REG + PCIR_MSI_ADDR_HIGH);
    pci_addr <<= 32;
    pci_addr |= rockchip_pcie_read(rk_pcie, RK_PCIE_EP_FUNC_BASE(func_no) +
            RK_PCIE_EP_MSI_CTRL_REG + PCIR_MSI_ADDR);
    pci_addr &= RT_GENMASK_ULL(63, 2);

    /* Set the outbound region if needed. */
    if (ep->irq_pci_addr != (pci_addr & ~pci_addr_mask) || ep->irq_pci_fn != func_no)
    {
        rockchip_pcie_prog_ep_ob_atu(rk_pcie, func_no, ep->max_regions - 1,
                AXI_WRAPPER_MEM_WRITE, ep->irq_phys_addr,
                pci_addr & ~pci_addr_mask, pci_addr_mask + 1);

        ep->irq_pci_addr = (pci_addr & ~pci_addr_mask);
        ep->irq_pci_fn = func_no;
    }

    HWREG16(ep->irq_cpu_addr + (pci_addr & pci_addr_mask)) = data;

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_raise_irq(struct rt_pci_ep *epc, rt_uint8_t func_no,
        enum rt_pci_ep_irq type, unsigned irq)
{
    struct rockchip_pcie_ep *ep = epc->priv;

    switch (type)
    {
    case RT_PCI_EP_IRQ_LEGACY:
        return rockchip_pcie_ep_send_legacy_irq(ep, func_no, 0);

    case RT_PCI_EP_IRQ_MSI:
        return rockchip_pcie_ep_send_msi_irq(ep, func_no, irq);

    default:
        return -RT_EINVAL;
    }
}

static rt_err_t rockchip_pcie_ep_start(struct rt_pci_ep *epc)
{
    rt_uint32_t cfg = RT_BIT(0);
    struct rt_pci_epf *epf;
    struct rockchip_pcie_ep *ep = epc->priv;
    struct rockchip_pcie *rk_pcie = &ep->rk_pcie;

    rt_list_for_each_entry(epf, &epc->epf_nodes, list)
    {
        cfg |= RT_BIT(epf->func_no);
    }

    rockchip_pcie_write(rk_pcie, cfg, PCIE_CORE_PHY_FUNC_CFG);

    return RT_EOK;
}

static const struct rt_pci_ep_ops rockchip_pcie_ep_ops =
{
    .write_header   = rockchip_pcie_ep_write_header,
    .set_bar        = rockchip_pcie_ep_set_bar,
    .clear_bar      = rockchip_pcie_ep_clear_bar,
    .map_addr       = rockchip_pcie_ep_map_addr,
    .unmap_addr     = rockchip_pcie_ep_unmap_addr,
    .set_msi        = rockchip_pcie_ep_set_msi,
    .get_msi        = rockchip_pcie_ep_get_msi,
    .raise_irq      = rockchip_pcie_ep_raise_irq,
    .start          = rockchip_pcie_ep_start,
};

static rt_err_t rockchip_pcie_ep_ofw_parse(struct rockchip_pcie *rk_pcie,
        struct rockchip_pcie_ep *ep)
{
    rt_err_t err;
    struct rt_device *dev = rk_pcie->dev;

    if ((err = rockchip_pcie_ofw_parse(rk_pcie)))
    {
        return err;
    }

    if ((err = rockchip_pcie_get_phys(rk_pcie)))
    {
        return err;
    }

    if (rt_dm_dev_prop_read_u32(dev, "rk_pcie,max-outbound-regions", &ep->max_regions) ||
        ep->max_regions > MAX_REGION_LIMIT)
    {
        ep->max_regions = MAX_REGION_LIMIT;
    }

    if (rt_dm_dev_prop_read_u8(dev, "max-functions", &ep->epc.max_functions))
    {
        ep->epc.max_functions = 1;
    }

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_size_t max_regions;
    struct rockchip_pcie_ep *ep;
    struct rockchip_pcie *rk_pcie;
    struct rt_pci_ep *epc = RT_NULL;
    struct rt_device *dev = &pdev->parent;

    if (!(ep = rt_calloc(1, sizeof(*ep))))
    {
        return -RT_ENOMEM;
    }

    rk_pcie = &ep->rk_pcie;
    rk_pcie->is_rc = RT_FALSE;
    rk_pcie->dev = dev;

    epc = &ep->epc;
    epc->name = rt_dm_dev_get_name(dev);
    epc->rc_dev = dev;
    epc->ops = &rockchip_pcie_ep_ops;
    epc->priv = ep;

    if ((err = rt_pci_ep_register(epc)))
    {
        goto _fail;
    }

    if ((err = rockchip_pcie_ep_ofw_parse(rk_pcie, ep)))
    {
        return err;
    }

    if ((err = rockchip_pcie_enable_clocks(rk_pcie)))
    {
        return err;
    }

    if ((err = rockchip_pcie_init_port(rk_pcie)))
    {
        goto _err_disable_clocks;
    }

    /* Establish the link automatically */
    rockchip_pcie_write(rk_pcie, PCIE_CLIENT_LINK_TRAIN_ENABLE, PCIE_CLIENT_CONFIG);

    max_regions = ep->max_regions;
    ep->ob_addr = rt_calloc(max_regions, sizeof(*ep->ob_addr));

    if (!ep->ob_addr)
    {
        err = -RT_ENOMEM;
        goto _err_uninit_port;
    }

    /* Only enable function 0 by default */
    rockchip_pcie_write(rk_pcie, RT_BIT(0), PCIE_CORE_PHY_FUNC_CFG);

    if ((err = rt_pci_ep_mem_init(epc,
            rk_pcie->mem_base_addr, rk_pcie->mem_base_size, ARCH_PAGE_SIZE)))
    {
        goto _fail;
    }

    ep->irq_cpu_addr = rt_pci_ep_mem_alloc(epc, &ep->irq_phys_addr, 128 * SIZE_KB);

    if (!ep->irq_cpu_addr)
    {
        err = -RT_ENOMEM;
        goto _err_epc_mem_exit;
    }

    ep->irq_pci_addr = RK_PCIE_EP_DUMMY_IRQ_ADDR;
    rockchip_pcie_write(rk_pcie, PCIE_CLIENT_CONF_ENABLE, PCIE_CLIENT_CONFIG);

    return RT_EOK;

_err_epc_mem_exit:
    if (ep->irq_phys_addr)
    {
        if (ep->irq_cpu_addr)
        {
            rt_iounmap(ep->irq_cpu_addr);
        }

        rt_slab_free(ep->addr_slab, (void *)ep->irq_phys_addr);
    }

    rt_slab_detach(ep->addr_slab);

_err_uninit_port:
    rockchip_pcie_deinit_phys(rk_pcie);

_err_disable_clocks:
    rockchip_pcie_disable_clocks(rk_pcie);
    rockchip_pcie_common_free(rk_pcie);

_fail:
    if (ep)
    {
        rt_free(ep->ob_addr);
        rt_free(ep);
    }

    return err;
}

static const struct rt_ofw_node_id rockchip_pcie_ep_ofw_ids[] =
{
    { .compatible = "rockchip,rk3399-pcie-ep", },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_pcie_ep_driver =
{
    .name = "rk_pcie-pcie-ep",
    .ids = rockchip_pcie_ep_ofw_ids,

    .probe = rockchip_pcie_ep_probe,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_pcie_ep_driver);

