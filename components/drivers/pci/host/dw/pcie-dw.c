/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#define DBG_TAG "pcie.dw"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pcie-dw.h"

static rt_uint8_t __dw_pcie_find_next_cap(struct dw_pcie *pci,
        rt_uint8_t cap_ptr, rt_uint8_t cap)
{
    rt_uint16_t reg;
    rt_uint8_t cap_id, next_cap_ptr;

    if (!cap_ptr)
    {
        return 0;
    }

    reg = dw_pcie_readw_dbi(pci, cap_ptr);
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
    return __dw_pcie_find_next_cap(pci, next_cap_ptr, cap);
}

rt_uint8_t dw_pcie_find_capability(struct dw_pcie *pci, rt_uint8_t cap)
{
    rt_uint16_t reg;
    rt_uint8_t next_cap_ptr;

    reg = dw_pcie_readw_dbi(pci, PCIR_CAP_PTR);
    next_cap_ptr = (reg & 0x00ff);

    return __dw_pcie_find_next_cap(pci, next_cap_ptr, cap);
}

static rt_uint16_t dw_pcie_find_next_ext_capability(struct dw_pcie *pci,
        rt_uint16_t start, rt_uint8_t cap)
{
    rt_uint32_t header;
    int ttl, pos = PCI_REGMAX + 1;

    /* minimum 8 bytes per capability */
    ttl = ((PCIE_REGMAX + 1) - (PCI_REGMAX + 1)) / 8;

    if (start)
    {
        pos = start;
    }

    header = dw_pcie_readl_dbi(pci, pos);
    /*
     * If we have no capabilities, this is indicated by cap ID,
     * cap version and next pointer all being 0.
     */
    if (header == 0)
    {
        return 0;
    }

    while (ttl-- > 0)
    {
        if (PCI_EXTCAP_ID(header) == cap && pos != start)
        {
            return pos;
        }

        pos = PCI_EXTCAP_NEXTPTR(header);

        if (pos < PCI_REGMAX + 1)
        {
            break;
        }

        header = dw_pcie_readl_dbi(pci, pos);
    }

    return 0;
}

rt_uint16_t dw_pcie_find_ext_capability(struct dw_pcie *pci, rt_uint8_t cap)
{
    return dw_pcie_find_next_ext_capability(pci, 0, cap);
}

rt_err_t dw_pcie_read(void *addr, rt_size_t size, rt_uint32_t *out_val)
{
    /* Check aligned */
    if ((rt_ubase_t)addr & ((rt_ubase_t)size - 1))
    {
        *out_val = 0;
        return -RT_EINVAL;
    }

    if (size == 4)
    {
        *out_val = HWREG32(addr);
    }
    else if (size == 2)
    {
        *out_val = HWREG16(addr);
    }
    else if (size == 1)
    {
        *out_val = HWREG8(addr);
    }
    else
    {
        *out_val = 0;
        return -RT_EINVAL;
    }

    return RT_EOK;
}

rt_err_t dw_pcie_write(void *addr, rt_size_t size, rt_uint32_t val)
{
    /* Check aligned */
    if ((rt_ubase_t)addr & ((rt_ubase_t)size - 1))
    {
        return -RT_EINVAL;
    }

    if (size == 4)
    {
        HWREG32(addr) = val;
    }
    else if (size == 2)
    {
        HWREG16(addr) = val;
    }
    else if (size == 1)
    {
        HWREG8(addr) = val;
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

rt_uint32_t dw_pcie_read_dbi(struct dw_pcie *pci, rt_uint32_t reg, rt_size_t size)
{
    rt_err_t err;
    rt_uint32_t val = 0;

    if (pci->ops->read_dbi)
    {
        return pci->ops->read_dbi(pci, pci->dbi_base, reg, size);
    }

    if ((err = dw_pcie_read(pci->dbi_base + reg, size, &val)))
    {
        LOG_E("Read DBI address error = %s", rt_strerror(err));
    }

    return val;
}

void dw_pcie_write_dbi(struct dw_pcie *pci, rt_uint32_t reg, rt_size_t size, rt_uint32_t val)
{
    rt_err_t err;

    if (pci->ops->write_dbi)
    {
        pci->ops->write_dbi(pci, pci->dbi_base, reg, size, val);
        return;
    }

    if ((err = dw_pcie_write(pci->dbi_base + reg, size, val)))
    {
        LOG_E("Write DBI address error = %s", rt_strerror(err));
    }
}

void dw_pcie_write_dbi2(struct dw_pcie *pci, rt_uint32_t reg, rt_size_t size, rt_uint32_t val)
{
    rt_err_t err;

    if (pci->ops && pci->ops->write_dbi2)
    {
        pci->ops->write_dbi2(pci, pci->dbi_base2, reg, size, val);
        return;
    }

    if ((err = dw_pcie_write(pci->dbi_base2 + reg, size, val)))
    {
        LOG_E("Write DBI2 address error = %s", rt_strerror(err));
    }
}

rt_uint32_t dw_pcie_readl_atu(struct dw_pcie *pci, rt_uint32_t reg)
{
    rt_err_t err;
    rt_uint32_t val = 0;

    if (pci->ops->read_dbi)
    {
        return pci->ops->read_dbi(pci, pci->atu_base, reg, 4);
    }

    if ((err = dw_pcie_read(pci->atu_base + reg, 4, &val)))
    {
        LOG_E("Read ATU address error = %s", rt_strerror(err));
    }

    return val;
}

void dw_pcie_writel_atu(struct dw_pcie *pci, rt_uint32_t reg, rt_uint32_t val)
{
    rt_err_t err;

    if (pci->ops->write_dbi)
    {
        pci->ops->write_dbi(pci, pci->atu_base, reg, 4, val);
        return;
    }

    if ((err = dw_pcie_write(pci->atu_base + reg, 4, val)))
    {
        LOG_E("Write ATU address error = %s", rt_strerror(err));
    }
}

static void dw_pcie_prog_outbound_atu_unroll(struct dw_pcie *pci, rt_uint8_t func_no,
        int index, int type, rt_uint64_t cpu_addr, rt_uint64_t pci_addr, rt_size_t size)
{
    rt_uint64_t limit_addr = cpu_addr + size - 1;

    dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_BASE,
            rt_lower_32_bits(cpu_addr));
    dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_BASE,
            rt_upper_32_bits(cpu_addr));
    dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_LIMIT,
            rt_lower_32_bits(limit_addr));
    dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_LIMIT,
            rt_upper_32_bits(limit_addr));
    dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_LOWER_TARGET,
            rt_lower_32_bits(pci_addr));
    dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_UPPER_TARGET,
            rt_upper_32_bits(pci_addr));
    dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL1,
            type | PCIE_ATU_FUNC_NUM(func_no));
    dw_pcie_writel_ob_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL2,
            PCIE_ATU_ENABLE);

    /*
     * Make sure ATU enable takes effect before any subsequent config
     * and I/O accesses.
     */
    for (int retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; ++retries)
    {
        if (dw_pcie_readl_ob_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL2) & PCIE_ATU_ENABLE)
        {
            return;
        }

        rt_thread_mdelay(LINK_WAIT_IATU);
    }

    LOG_E("Outbound iATU is not being enabled");
}

static void __dw_pcie_prog_outbound_atu(struct dw_pcie *pci, rt_uint8_t func_no,
        int index, int type, rt_uint64_t cpu_addr, rt_uint64_t pci_addr, rt_size_t size)
{
    if (pci->ops->cpu_addr_fixup)
    {
        cpu_addr = pci->ops->cpu_addr_fixup(pci, cpu_addr);
    }

    if (pci->iatu_unroll_enabled & DWC_IATU_UNROLL_EN)
    {
        dw_pcie_prog_outbound_atu_unroll(pci, func_no,
                index, type, cpu_addr, pci_addr, size);

        return;
    }

    dw_pcie_writel_dbi(pci, PCIE_ATU_VIEWPORT, PCIE_ATU_REGION_OUTBOUND | index);
    dw_pcie_writel_dbi(pci, PCIE_ATU_LOWER_BASE, rt_lower_32_bits(cpu_addr));
    dw_pcie_writel_dbi(pci, PCIE_ATU_UPPER_BASE, rt_upper_32_bits(cpu_addr));
    dw_pcie_writel_dbi(pci, PCIE_ATU_LIMIT, rt_lower_32_bits(cpu_addr + size - 1));
    dw_pcie_writel_dbi(pci, PCIE_ATU_LOWER_TARGET, rt_lower_32_bits(pci_addr));
    dw_pcie_writel_dbi(pci, PCIE_ATU_UPPER_TARGET, rt_upper_32_bits(pci_addr));
    dw_pcie_writel_dbi(pci, PCIE_ATU_CR1, type | PCIE_ATU_FUNC_NUM(func_no));
    dw_pcie_writel_dbi(pci, PCIE_ATU_CR2, PCIE_ATU_ENABLE);

    /*
     * Make sure ATU enable takes effect before any subsequent config
     * and I/O accesses.
     */
    for (int retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; ++retries)
    {
        if (dw_pcie_readl_dbi(pci, PCIE_ATU_CR2) & PCIE_ATU_ENABLE)
        {
            return;
        }

        rt_thread_mdelay(LINK_WAIT_IATU);
    }

    LOG_E("Outbound iATU is not being enabled");
}

void dw_pcie_prog_outbound_atu(struct dw_pcie *pci,
        int index, int type, rt_uint64_t cpu_addr, rt_uint64_t pci_addr, rt_size_t size)
{
    __dw_pcie_prog_outbound_atu(pci, 0, index, type, cpu_addr, pci_addr, size);
}

void dw_pcie_prog_ep_outbound_atu(struct dw_pcie *pci, rt_uint8_t func_no,
        int index, int type, rt_uint64_t cpu_addr, rt_uint64_t pci_addr, rt_size_t size)
{
    __dw_pcie_prog_outbound_atu(pci, func_no, index, type, cpu_addr, pci_addr, size);
}

static rt_err_t dw_pcie_prog_inbound_atu_unroll(struct dw_pcie *pci,
        rt_uint8_t func_no, int index, int bar, rt_uint64_t cpu_addr,
        enum dw_pcie_aspace_type aspace_type)
{
    int type;

    dw_pcie_writel_ib_unroll(pci, index, PCIE_ATU_UNR_LOWER_TARGET,
            rt_lower_32_bits(cpu_addr));
    dw_pcie_writel_ib_unroll(pci, index, PCIE_ATU_UNR_UPPER_TARGET,
            rt_upper_32_bits(cpu_addr));

    switch (aspace_type)
    {
    case DW_PCIE_ASPACE_MEM:
        type = PCIE_ATU_TYPE_MEM;
        break;

    case DW_PCIE_ASPACE_IO:
        type = PCIE_ATU_TYPE_IO;
        break;

    default:
        return -RT_EINVAL;
    }

    dw_pcie_writel_ib_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL1,
            type | PCIE_ATU_FUNC_NUM(func_no));
    dw_pcie_writel_ib_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL2,
            PCIE_ATU_FUNC_NUM_MATCH_EN | PCIE_ATU_ENABLE |
            PCIE_ATU_BAR_MODE_ENABLE | (bar << 8));

    /*
     * Make sure ATU enable takes effect before any subsequent config
     * and I/O accesses.
     */
    for (int retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; ++retries)
    {
        if (dw_pcie_readl_ib_unroll(pci, index, PCIE_ATU_UNR_REGION_CTRL2) & PCIE_ATU_ENABLE)
        {
            return RT_EOK;
        }

        rt_thread_mdelay(LINK_WAIT_IATU);
    }

    LOG_E("Inbound iATU is not being enabled");

    return -RT_EBUSY;
}

rt_err_t dw_pcie_prog_inbound_atu(struct dw_pcie *pci,
        rt_uint8_t func_no, int index, int bar, rt_uint64_t cpu_addr,
        enum dw_pcie_aspace_type aspace_type)
{
    int type;

    if (pci->iatu_unroll_enabled & DWC_IATU_UNROLL_EN)
    {
        return dw_pcie_prog_inbound_atu_unroll(pci, func_no,
                index, bar, cpu_addr, aspace_type);
    }

    dw_pcie_writel_dbi(pci, PCIE_ATU_VIEWPORT, PCIE_ATU_REGION_INBOUND | index);
    dw_pcie_writel_dbi(pci, PCIE_ATU_LOWER_TARGET, rt_lower_32_bits(cpu_addr));
    dw_pcie_writel_dbi(pci, PCIE_ATU_UPPER_TARGET, rt_upper_32_bits(cpu_addr));

    switch (aspace_type)
    {
    case DW_PCIE_ASPACE_MEM:
        type = PCIE_ATU_TYPE_MEM;
        break;

    case DW_PCIE_ASPACE_IO:
        type = PCIE_ATU_TYPE_IO;
        break;

    default:
        return -RT_EINVAL;
    }

    dw_pcie_writel_dbi(pci, PCIE_ATU_CR1, type | PCIE_ATU_FUNC_NUM(func_no));
    dw_pcie_writel_dbi(pci, PCIE_ATU_CR2, PCIE_ATU_ENABLE |
            PCIE_ATU_FUNC_NUM_MATCH_EN | PCIE_ATU_BAR_MODE_ENABLE | (bar << 8));

    /*
     * Make sure ATU enable takes effect before any subsequent config
     * and I/O accesses.
     */
    for (int retries = 0; retries < LINK_WAIT_MAX_IATU_RETRIES; ++retries)
    {
        if (dw_pcie_readl_dbi(pci, PCIE_ATU_CR2) & PCIE_ATU_ENABLE)
        {
            return RT_EOK;
        }

        rt_thread_mdelay(LINK_WAIT_IATU);
    }

    LOG_E("Inbound iATU is not being enabled");

    return -RT_EBUSY;
}

void dw_pcie_disable_atu(struct dw_pcie *pci, int index, enum dw_pcie_region_type type)
{
    rt_uint32_t region;

    switch (type)
    {
    case DW_PCIE_REGION_INBOUND:
        region = PCIE_ATU_REGION_INBOUND;
        break;

    case DW_PCIE_REGION_OUTBOUND:
        region = PCIE_ATU_REGION_OUTBOUND;
        break;

    default:
        return;
    }

    if (pci->iatu_unroll_enabled)
    {
        if (region == PCIE_ATU_REGION_INBOUND)
        {
            dw_pcie_writel_ib_unroll(pci, index,
                    PCIE_ATU_UNR_REGION_CTRL2, ~(rt_uint32_t)PCIE_ATU_ENABLE);
        }
        else
        {
            dw_pcie_writel_ob_unroll(pci, index,
                    PCIE_ATU_UNR_REGION_CTRL2, ~(rt_uint32_t)PCIE_ATU_ENABLE);
        }
    }
    else
    {
        dw_pcie_writel_dbi(pci, PCIE_ATU_VIEWPORT, region | index);
        dw_pcie_writel_dbi(pci, PCIE_ATU_CR2, ~(rt_uint32_t)PCIE_ATU_ENABLE);
    }
}

rt_err_t dw_pcie_wait_for_link(struct dw_pcie *pci)
{
    /* Check if the link is up or not */
    for (int retries = 0; retries < LINK_WAIT_MAX_RETRIES; ++retries)
    {
        if (dw_pcie_link_up(pci))
        {
            LOG_I("%s: Link up", rt_dm_dev_get_name(pci->dev));

            return RT_EOK;
        }

        rt_hw_us_delay((LINK_WAIT_USLEEP_MIN + LINK_WAIT_USLEEP_MAX) >> 1);
    }

    LOG_I("PHY link never came up");

    return -RT_ETIMEOUT;
}

rt_bool_t dw_pcie_link_up(struct dw_pcie *pci)
{
    rt_uint32_t val;

    if (pci->ops->link_up)
    {
        return pci->ops->link_up(pci);
    }

    val = HWREG32(pci->dbi_base + PCIE_PORT_DEBUG1);

    return (val & PCIE_PORT_DEBUG1_LINK_UP) && (!(val & PCIE_PORT_DEBUG1_LINK_IN_TRAINING));
}

void dw_pcie_upconfig_setup(struct dw_pcie *pci)
{
    rt_uint32_t val;

    val = dw_pcie_readl_dbi(pci, PCIE_PORT_MULTI_LANE_CTRL);
    val |= PORT_MLTI_UPCFG_SUPPORT;
    dw_pcie_writel_dbi(pci, PCIE_PORT_MULTI_LANE_CTRL, val);
}

static void dw_pcie_link_set_max_speed(struct dw_pcie *pci, rt_uint32_t link_gen)
{
    rt_uint32_t cap, ctrl2, link_speed;
    rt_uint8_t offset = dw_pcie_find_capability(pci, PCIY_EXPRESS);

    cap = dw_pcie_readl_dbi(pci, offset + PCIER_LINK_CAP);
    ctrl2 = dw_pcie_readl_dbi(pci, offset + PCIER_LINK_CTL2);
    ctrl2 &= ~PCIEM_LNKCTL2_TLS;

    switch (link_gen)
    {
    case 1: link_speed = PCIEM_LNKCTL2_TLS_2_5GT; break;
    case 2: link_speed = PCIEM_LNKCTL2_TLS_5_0GT; break;
    case 3: link_speed = PCIEM_LNKCTL2_TLS_8_0GT; break;
    case 4: link_speed = PCIEM_LNKCTL2_TLS_16_0GT; break;
    default:
        /* Use hardware capability */
        link_speed = RT_FIELD_GET(PCIEM_LINK_CAP_MAX_SPEED, cap);
        ctrl2 &= ~PCIEM_LNKCTL2_HASD;
        break;
    }

    dw_pcie_writel_dbi(pci, offset + PCIER_LINK_CTL2, ctrl2 | link_speed);

    cap &= ~((rt_uint32_t)PCIEM_LINK_CAP_MAX_SPEED);
    dw_pcie_writel_dbi(pci, offset + PCIER_LINK_CAP, cap | link_speed);
}

void dw_pcie_setup(struct dw_pcie *pci)
{
    rt_uint32_t val;
    struct rt_device *dev = pci->dev;

    if (pci->version >= 0x480a || (!pci->version && dw_pcie_iatu_unroll_enabled(pci)))
    {
        pci->iatu_unroll_enabled |= DWC_IATU_UNROLL_EN;

        if (!pci->atu_base)
        {
            pci->atu_base = rt_dm_dev_iomap_by_name(dev, "atu");
        }

        if (!pci->atu_base)
        {
            pci->atu_base = pci->dbi_base + DEFAULT_DBI_ATU_OFFSET;
        }
    }

    LOG_D("iATU unroll is %sabled", pci->iatu_unroll_enabled & DWC_IATU_UNROLL_EN ? "en" : "dis");

    if (pci->link_gen > 0)
    {
        dw_pcie_link_set_max_speed(pci, pci->link_gen);
    }

    /* Configure Gen1 N_FTS */
    if (pci->fts_number[0])
    {
        val = dw_pcie_readl_dbi(pci, PCIE_PORT_AFR);
        val &= ~(PORT_AFR_N_FTS_MASK | PORT_AFR_CC_N_FTS_MASK);
        val |= PORT_AFR_N_FTS(pci->fts_number[0]);
        val |= PORT_AFR_CC_N_FTS(pci->fts_number[0]);
        dw_pcie_writel_dbi(pci, PCIE_PORT_AFR, val);
    }

    /* Configure Gen2+ N_FTS */
    if (pci->fts_number[1])
    {
        val = dw_pcie_readl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
        val &= ~PORT_LOGIC_N_FTS_MASK;
        val |= pci->fts_number[1];
        dw_pcie_writel_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);
    }

    val = dw_pcie_readl_dbi(pci, PCIE_PORT_LINK_CONTROL);
    val &= ~PORT_LINK_FAST_LINK_MODE;
    val |= PORT_LINK_DLL_LINK_EN;
    dw_pcie_writel_dbi(pci, PCIE_PORT_LINK_CONTROL, val);

    if (rt_dm_dev_prop_read_bool(dev, "snps,enable-cdm-check"))
    {
        val = dw_pcie_readl_dbi(pci, PCIE_PL_CHK_REG_CONTROL_STATUS);
        val |= PCIE_PL_CHK_REG_CHK_REG_CONTINUOUS | PCIE_PL_CHK_REG_CHK_REG_START;
        dw_pcie_writel_dbi(pci, PCIE_PL_CHK_REG_CONTROL_STATUS, val);
    }

    rt_dm_dev_prop_read_u32(dev, "num-lanes", &pci->num_lanes);

    if (!pci->num_lanes)
    {
        LOG_D("Using h/w default number of lanes");
        return;
    }

    /* Set the number of lanes */
    val &= ~PORT_LINK_FAST_LINK_MODE;
    val &= ~PORT_LINK_MODE_MASK;
    switch (pci->num_lanes)
    {
    case 1: val |= PORT_LINK_MODE_1_LANES; break;
    case 2: val |= PORT_LINK_MODE_2_LANES; break;
    case 4: val |= PORT_LINK_MODE_4_LANES; break;
    case 8: val |= PORT_LINK_MODE_8_LANES; break;
    default:
        LOG_E("Invail num-lanes = %d", pci->num_lanes);
        return;
    }
    dw_pcie_writel_dbi(pci, PCIE_PORT_LINK_CONTROL, val);

    /* Set link width speed control register */
    val = dw_pcie_readl_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL);
    val &= ~PORT_LOGIC_LINK_WIDTH_MASK;
    switch (pci->num_lanes)
    {
    case 1: val |= PORT_LOGIC_LINK_WIDTH_1_LANES; break;
    case 2: val |= PORT_LOGIC_LINK_WIDTH_2_LANES; break;
    case 4: val |= PORT_LOGIC_LINK_WIDTH_4_LANES; break;
    case 8: val |= PORT_LOGIC_LINK_WIDTH_8_LANES; break;
    }
    val |= pci->user_speed;
    dw_pcie_writel_dbi(pci, PCIE_LINK_WIDTH_SPEED_CONTROL, val);
}
