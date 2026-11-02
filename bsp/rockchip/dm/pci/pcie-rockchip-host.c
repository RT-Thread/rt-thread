/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#define DBG_TAG "pcie.rk-host"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pcie-rockchip.h"

rt_inline rt_uint8_t __bitrev8(rt_uint8_t x)
{
    x = (x & 0x55) << 1 | (x & 0xaa) >> 1;
    x = (x & 0x33) << 2 | (x & 0xcc) >> 2;
    x = (x & 0x0f) << 4 | (x & 0xf0) >> 4;

    return x;
}

static void rockchip_pcie_enable_bw_int(struct rockchip_pcie *rk_pcie)
{
    rt_uint32_t status;

    status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_LCS);
    status |= (PCIEM_LINK_CTL_LBMIE | PCIEM_LINK_CTL_LABIE);
    rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_LCS);
}

static void rockchip_pcie_clr_bw_int(struct rockchip_pcie *rk_pcie)
{
    rt_uint32_t status;

    status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_LCS);
    status |= (PCIEM_LINK_STA_LINK_BW_MGMT | PCIEM_LINK_STA_LINK_AUTO_BW) << 16;
    rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_LCS);
}

static void rockchip_pcie_update_txcredit_mui(struct rockchip_pcie *rk_pcie)
{
    rt_uint32_t val;

    /* Update Tx credit maximum update interval */
    val = rockchip_pcie_read(rk_pcie, PCIE_CORE_TXCREDIT_CFG1);
    val &= ~PCIE_CORE_TXCREDIT_CFG1_MUI_MASK;
    /* NS */
    val |= PCIE_CORE_TXCREDIT_CFG1_MUI_ENCODE(24000);
    rockchip_pcie_write(rk_pcie, val, PCIE_CORE_TXCREDIT_CFG1);
}

static rt_bool_t rockchip_pcie_valid_device(struct rockchip_pcie *rk_pcie,
        struct rt_pci_bus *bus, int dev)
{
    if (rt_pci_is_root_bus(bus) ||
        (bus->parent && rt_pci_is_root_bus(bus->parent)))
    {
        return dev == 0;
    }

    return RT_TRUE;
}

static void rockchip_pcie_set_power_limit(struct rockchip_pcie *rk_pcie)
{
    int curr;
    rt_uint32_t status, scale, power;

    if (rt_is_err(rk_pcie->vpcie3v3))
    {
        return;
    }

    /*
     * Set RC's captured slot power limit and scale if vpcie3v3 available.
     * The default values are both zero which means the software
     * should set these two according to the actual power supply.
     */
    curr = rt_regulator_get_voltage(rk_pcie->vpcie3v3);
    if (curr <= 0)
    {
        return;
    }

    scale = 3; /* 0.001x */
    curr = curr / 1000; /* convert to mA */
    power = (curr * 3300) / 1000; /* milliwatt */
    while (power > PCIE_RC_CONFIG_DCR_CSPL_LIMIT)
    {
        if (!scale)
        {
            LOG_W("Invalid power supply");
            return;
        }

        --scale;
        power /= 10;
    }

    status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_DCR);
    status |= (power << PCIE_RC_CONFIG_DCR_CSPL_SHIFT) |
            (scale << PCIE_RC_CONFIG_DCR_CPLS_SHIFT);
    rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_DCR);
}

static rt_uint8_t rockchip_pcie_lane_map(struct rockchip_pcie *rk_pcie)
{
    rt_uint8_t map;
    rt_uint32_t val;

    if (rk_pcie->legacy_phy)
    {
        return RT_GENMASK(MAX_LANE_NUM - 1, 0);
    }

    val = rockchip_pcie_read(rk_pcie, PCIE_CORE_LANE_MAP);
    map = val & PCIE_CORE_LANE_MAP_MASK;

    /* The link may be using a reverse-indexed mapping. */
    if (val & PCIE_CORE_LANE_MAP_REVERSE)
    {
        map = __bitrev8(map) >> 4;
    }

    return map;
}

static void rockchip_pcie_enable_interrupts(struct rockchip_pcie *rk_pcie)
{
    rockchip_pcie_write(rk_pcie, (PCIE_CLIENT_INT_CLI << 16) &
            (~PCIE_CLIENT_INT_CLI), PCIE_CLIENT_INT_MASK);
    rockchip_pcie_write(rk_pcie, (rt_uint32_t)(~PCIE_CORE_INT),
            PCIE_CORE_INT_MASK);

    rockchip_pcie_enable_bw_int(rk_pcie);
    rockchip_pcie_write(rk_pcie, PCIE_UDMA_INT_ENABLE_MASK,
            PCIE_APB_CORE_UDMA_BASE + PCIE_UDMA_INT_ENABLE_REG);
}

static rt_err_t rockchip_pcie_bus_read_own_conf(struct rockchip_pcie *rk_pcie,
        int reg, int width, rt_uint32_t *value)
{
    void *addr = rk_pcie->apb_base + PCIE_RC_CONFIG_NORMAL_BASE + reg;

    if (!is_aligned((rt_ubase_t)addr, width))
    {
        *value = 0;
        return -RT_EINVAL;
    }

    if (width == 4)
    {
        *value = HWREG32(addr);
    }
    else if (width == 2)
    {
        *value = HWREG16(addr);
    }
    else if (width == 1)
    {
        *value = HWREG8(addr);
    }
    else
    {
        *value = 0;
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t rockchip_pcie_bus_write_own_conf(struct rockchip_pcie *rk_pcie,
        int reg, int width, rt_uint32_t value)
{
    void *addr;
    rt_uint32_t mask, tmp, offset;

    offset = reg & ~0x3;
    addr = rk_pcie->apb_base + PCIE_RC_CONFIG_NORMAL_BASE + offset;

    if (width == 4)
    {
        HWREG32(addr) = value;
        return RT_EOK;
    }

    mask = ~(((1 << (width * 8)) - 1) << ((reg & 0x3) * 8));

    /*
     * N.B. This read/modify/write isn't safe in general because it can
     * corrupt RW1C bits in adjacent registers.  But the hardware
     * doesn't support smaller writes.
     */
    tmp = HWREG32(addr) & mask;
    tmp |= value << ((reg & 0x3) * 8);
    HWREG32(addr) = tmp;

    return RT_EOK;
}

static rt_err_t rockchip_pcie_bus_read_other_conf(struct rockchip_pcie *rk_pcie,
        struct rt_pci_bus *bus, rt_uint32_t devfn, int reg, int width, rt_uint32_t *value)
{
    rt_uint32_t busdev;

    if (rk_pcie->in_remove)
    {
        return RT_EOK;
    }

    busdev = PCIE_ECAM_ADDR(bus->number, RT_PCI_SLOT(devfn), RT_PCI_FUNC(devfn), reg);

    if (!is_aligned(busdev, width))
    {
        *value = 0;
        return -RT_EINVAL;
    }

    if (rt_pci_is_root_bus(bus->parent))
    {
        rockchip_pcie_cfg_configuration_accesses(rk_pcie, AXI_WRAPPER_TYPE0_CFG);
    }
    else
    {
        rockchip_pcie_cfg_configuration_accesses(rk_pcie, AXI_WRAPPER_TYPE1_CFG);
    }

    if (width == 4)
    {
        *value = HWREG32(rk_pcie->axi_base + busdev);
    }
    else if (width == 2)
    {
        *value = HWREG16(rk_pcie->axi_base + busdev);
    }
    else if (width == 1)
    {
        *value = HWREG8(rk_pcie->axi_base + busdev);
    }
    else
    {
        *value = 0;
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t rockchip_pcie_bus_write_other_conf(struct rockchip_pcie *rk_pcie,
        struct rt_pci_bus *bus, rt_uint32_t devfn, int reg, int width, rt_uint32_t value)
{
    rt_uint32_t busdev;

    if (rk_pcie->in_remove)
    {
        return RT_EOK;
    }

    busdev = PCIE_ECAM_ADDR(bus->number, RT_PCI_SLOT(devfn), RT_PCI_FUNC(devfn), reg);
    if (!is_aligned(busdev, width))
    {
        return -RT_EINVAL;
    }

    if (rt_pci_is_root_bus(bus->parent))
    {
        rockchip_pcie_cfg_configuration_accesses(rk_pcie, AXI_WRAPPER_TYPE0_CFG);
    }
    else
    {
        rockchip_pcie_cfg_configuration_accesses(rk_pcie, AXI_WRAPPER_TYPE1_CFG);
    }

    if (width == 4)
    {
        HWREG32(rk_pcie->axi_base + busdev) = value;
    }
    else if (width == 2)
    {
        HWREG16(rk_pcie->axi_base + busdev) = value;
    }
    else if (width == 1)
    {
        HWREG8(rk_pcie->axi_base + busdev) = value;
    }
    else
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t rockchip_pcie_bus_read(struct rt_pci_bus *bus,
            rt_uint32_t devfn, int reg, int width, rt_uint32_t *value)
{
    struct rockchip_pcie *rk_pcie = bus->sysdata;

    if (!rockchip_pcie_valid_device(rk_pcie, bus, RT_PCI_SLOT(devfn)))
    {
        *value = 0xffffffff;
        return -RT_EINVAL;
    }

    if (rt_pci_is_root_bus(bus))
    {
        return rockchip_pcie_bus_read_own_conf(rk_pcie, reg, width, value);
    }

    return rockchip_pcie_bus_read_other_conf(rk_pcie, bus, devfn, reg, width, value);
}

static rt_err_t rockchip_pcie_bus_write(struct rt_pci_bus *bus,
            rt_uint32_t devfn, int reg, int width, rt_uint32_t value)
{
    struct rockchip_pcie *rk_pcie = bus->sysdata;

    if (!rockchip_pcie_valid_device(rk_pcie, bus, RT_PCI_SLOT(devfn)))
    {
        return -RT_EINVAL;
    }

    if (rt_pci_is_root_bus(bus))
    {
        return rockchip_pcie_bus_write_own_conf(rk_pcie, reg, width, value);
    }

    return rockchip_pcie_bus_write_other_conf(rk_pcie, bus, devfn, reg, width, value);
}

static const struct rt_pci_ops rockchip_pcie_ops =
{
    .read = rockchip_pcie_bus_read,
    .write = rockchip_pcie_bus_write,
};

static void rockchip_pcie_intx_irq_mask(struct rt_pic_irq *pirq)
{
    struct rockchip_pcie *rk_pcie = pirq->pic->priv_data;

    rt_hw_interrupt_mask(rk_pcie->legacy_irq);
}

static void rockchip_pcie_intx_irq_unmask(struct rt_pic_irq *pirq)
{
    struct rockchip_pcie *rk_pcie = pirq->pic->priv_data;

    rt_hw_interrupt_umask(rk_pcie->legacy_irq);
}

static int rockchip_pcie_intx_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
{
    int irq;
    struct rt_pic_irq *pirq = rt_pic_find_irq(pic, hwirq);

    if (pirq)
    {
        if (pirq->irq >= 0)
        {
            irq = pirq->irq;
        }
        else
        {
            irq = rt_pic_config_irq(pic, hwirq, hwirq);
        }
    }
    else
    {
        irq = -1;
    }

    return irq;
}

static rt_err_t rockchip_pcie_intx_irq_parse(struct rt_pic *pic,
        struct rt_ofw_cell_args *args, struct rt_pic_irq *out_pirq)
{
    rt_err_t err = RT_EOK;

    if (args->args_count == 1)
    {
        out_pirq->hwirq = args->args[0];
        out_pirq->mode = RT_IRQ_MODE_LEVEL_HIGH;
    }
    else
    {
        err = -RT_EINVAL;
    }

    return err;
}

static const struct rt_pic_ops pcie_intx_ops =
{
    .name = "RK-INTx",
    .irq_mask = rockchip_pcie_intx_irq_mask,
    .irq_unmask = rockchip_pcie_intx_irq_unmask,
    .irq_map = rockchip_pcie_intx_irq_map,
    .irq_parse = rockchip_pcie_intx_irq_parse,
};

static void rockchip_pcie_subsys_isr(int irqno, void *param)
{
    rt_uint32_t reg, sub_reg;
    struct rockchip_pcie *rk_pcie = param;
    struct rt_device *dev = rk_pcie->dev;

    RT_UNUSED(dev);
    reg = rockchip_pcie_read(rk_pcie, PCIE_CLIENT_INT_STATUS);
    sub_reg = rockchip_pcie_read(rk_pcie, PCIE_CORE_INT_STATUS);

    if (reg & PCIE_CLIENT_INT_LOCAL)
    {
        LOG_D("%s: Local interrupt received", rt_dm_dev_get_name(dev));

        if (sub_reg & PCIE_CORE_INT_PRFPE)
        {
            LOG_D("%s: Parity error detected while reading from the PNP receive FIFO RAM",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_CRFPE)
        {
            LOG_D("%s: Parity error detected while reading from the Completion Receive FIFO RAM",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_RRPE)
        {
            LOG_D("%s: Parity error detected while reading from replay buffer RAM",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_PRFO)
        {
            LOG_D("%s: Overflow occurred in the PNP receive FIFO",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_CRFO)
        {
            LOG_D("%s: Overflow occurred in the completion receive FIFO",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_RT)
        {
            LOG_D("%s: Replay timer timed out", rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_RTR)
        {
            LOG_D("%s: Replay timer rolled over after 4 transmissions of the same TLP",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_PE)
        {
            LOG_D("%s: Phy error detected on receive side",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_MTR)
        {
            LOG_D("%s: Malformed TLP received from the link",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_UCR)
        {
            LOG_D("%s: Malformed TLP received from the link",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_FCE)
        {
            LOG_D("%s: An error was observed in the flow control advertisements from the other side",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_CT)
        {
            LOG_D("%s: A request timed out waiting for completion",
                    rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_UTC)
        {
            LOG_D("%s: Unmapped TC error", rt_dm_dev_get_name(dev));
        }

        if (sub_reg & PCIE_CORE_INT_MMVC)
        {
            LOG_D("%s: MSI mask register changes", rt_dm_dev_get_name(dev));
        }

        rockchip_pcie_write(rk_pcie, sub_reg, PCIE_CORE_INT_STATUS);
    }
    else if (reg & PCIE_CLIENT_INT_PHY)
    {
        LOG_D("%s: PHY link changes", rt_dm_dev_get_name(dev));
        rockchip_pcie_update_txcredit_mui(rk_pcie);
        rockchip_pcie_clr_bw_int(rk_pcie);
    }

    if (reg & PCIE_CLIENT_INT_UDMA)
    {
        rockchip_pcie_write(rk_pcie, sub_reg, PCIE_CLIENT_INT_STATUS);
        rockchip_pcie_write(rk_pcie, reg, PCIE_CLIENT_INT_STATUS);
    }

    rockchip_pcie_write(rk_pcie, reg & PCIE_CLIENT_INT_LOCAL, PCIE_CLIENT_INT_STATUS);
}

static void rockchip_pcie_legacy_intx_isr(int irqno, void *param)
{
    rt_uint32_t reg, hwirq;
    struct rt_pic_irq *pirq;
    struct rockchip_pcie *rk_pcie = param;

    reg = rockchip_pcie_read(rk_pcie, PCIE_CLIENT_INT_STATUS);
    reg = (reg & PCIE_CLIENT_INTR_MASK) >> PCIE_CLIENT_INTR_SHIFT;

    while (reg)
    {
        hwirq = __rt_ffs(reg) - 1;
        reg &= ~RT_BIT(hwirq);

        pirq = rt_pic_find_irq(&rk_pcie->intx_pic, hwirq);

        rt_pic_handle_isr(pirq);
    }
}

static void rockchip_pcie_client_isr(int irqno, void *param)
{
    rt_uint32_t reg;
    struct rockchip_pcie *rk_pcie = param;
    struct rt_device *dev = rk_pcie->dev;

    RT_UNUSED(dev);
    reg = rockchip_pcie_read(rk_pcie, PCIE_CLIENT_INT_STATUS);

    if (reg & PCIE_CLIENT_INT_LEGACY_DONE)
    {
        LOG_D("%s: Legacy done interrupt received", rt_dm_dev_get_name(dev));
    }

    if (reg & PCIE_CLIENT_INT_MSG)
    {
        LOG_D("%s: Message done interrupt received", rt_dm_dev_get_name(dev));
    }

    if (reg & PCIE_CLIENT_INT_HOT_RST)
    {
        LOG_D("%s: Hot reset interrupt received", rt_dm_dev_get_name(dev));
    }

    if (reg & PCIE_CLIENT_INT_DPA)
    {
        LOG_D("%s: DPA interrupt received", rt_dm_dev_get_name(dev));
    }

    if (reg & PCIE_CLIENT_INT_FATAL_ERR)
    {
        LOG_D("%s: Fatal error interrupt received", rt_dm_dev_get_name(dev));
    }

    if (reg & PCIE_CLIENT_INT_NFATAL_ERR)
    {
        LOG_D("%s: No fatal error interrupt received", rt_dm_dev_get_name(dev));
    }

    if (reg & PCIE_CLIENT_INT_CORR_ERR)
    {
        LOG_D("%s: Correctable error interrupt received", rt_dm_dev_get_name(dev));
    }

    if (reg & PCIE_CLIENT_INT_PHY)
    {
        LOG_D("%s: PHY interrupt received", rt_dm_dev_get_name(dev));
    }

    rockchip_pcie_write(rk_pcie, reg & (PCIE_CLIENT_INT_LEGACY_DONE |
            PCIE_CLIENT_INT_MSG | PCIE_CLIENT_INT_HOT_RST |
            PCIE_CLIENT_INT_DPA | PCIE_CLIENT_INT_FATAL_ERR |
            PCIE_CLIENT_INT_NFATAL_ERR |
            PCIE_CLIENT_INT_CORR_ERR |
            PCIE_CLIENT_INT_PHY), PCIE_CLIENT_INT_STATUS);
}

static rt_err_t rockchip_pcie_host_ofw_parse(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;
    struct rt_device *dev = rk_pcie->dev;

    if ((err = rockchip_pcie_ofw_parse(rk_pcie)))
    {
        return err;
    }

    rk_pcie->vpcie12v = rt_regulator_get(dev, "vpcie12v");
    if (rt_is_err(rk_pcie->vpcie12v))
    {
        return rt_ptr_err(rk_pcie->vpcie12v);
    }

    rk_pcie->vpcie3v3 = rt_regulator_get(dev, "vpcie3v3");
    if (rt_is_err(rk_pcie->vpcie3v3))
    {
        return rt_ptr_err(rk_pcie->vpcie3v3);
    }

    rk_pcie->vpcie1v8 = rt_regulator_get(dev, "vpcie1v8");
    if (rt_is_err(rk_pcie->vpcie1v8))
    {
        return rt_ptr_err(rk_pcie->vpcie1v8);
    }

    rk_pcie->vpcie0v9 = rt_regulator_get(dev, "vpcie0v9");
    if (rt_is_err(rk_pcie->vpcie0v9))
    {
        return rt_ptr_err(rk_pcie->vpcie0v9);
    }

    return RT_EOK;
}

static rt_err_t rockchip_pcie_set_vpcie(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;

    if (rk_pcie->vpcie12v && (err = rt_regulator_enable(rk_pcie->vpcie12v)))
    {
        return err;
    }

    if (rk_pcie->vpcie3v3 && (err = rt_regulator_enable(rk_pcie->vpcie3v3)))
    {
        goto _err_disable_12v;
    }

    if ((err = rt_regulator_enable(rk_pcie->vpcie1v8)))
    {
        goto _err_disable_3v3;
    }

    if ((err = rt_regulator_enable(rk_pcie->vpcie0v9)))
    {
        goto _err_disable_1v8;
    }

    return RT_EOK;

_err_disable_1v8:
    rt_regulator_disable(rk_pcie->vpcie1v8);

_err_disable_3v3:
    if (!rt_is_err(rk_pcie->vpcie3v3))
    {
        rt_regulator_disable(rk_pcie->vpcie3v3);
    }

_err_disable_12v:
    if (!rt_is_err(rk_pcie->vpcie12v))
    {
        rt_regulator_disable(rk_pcie->vpcie12v);
    }

    return err;
}

static rt_err_t rockchip_pcie_host_init_port(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;
    rt_uint32_t status, timeouts = 500;
    struct rt_device *dev = rk_pcie->dev;

    rt_pin_write(rk_pcie->ep_pin, !rk_pcie->active_val);

    if ((err = rockchip_pcie_init_port(rk_pcie)))
    {
        return err;
    }

    /* Fix the transmitted FTS count desired to exit from L0s. */
    status = rockchip_pcie_read(rk_pcie, PCIE_CORE_CTRL_PLC1);
    status = (status & ~PCIE_CORE_CTRL_PLC1_FTS_MASK) |
            (PCIE_CORE_CTRL_PLC1_FTS_CNT << PCIE_CORE_CTRL_PLC1_FTS_SHIFT);
    rockchip_pcie_write(rk_pcie, status, PCIE_CORE_CTRL_PLC1);

    rockchip_pcie_set_power_limit(rk_pcie);

    /* Set RC's clock architecture as common clock */
    status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_LCS);
    status |= PCIEM_LINK_STA_SLOT_CLOCK << 16;
    rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_LCS);

    /* Set RC's RCB to 128 */
    status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_LCS);
    status |= PCIEM_LINK_CTL_RCB;
    rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_LCS);

    /* Enable Gen1 training */
    rockchip_pcie_write(rk_pcie, PCIE_CLIENT_LINK_TRAIN_ENABLE,
            PCIE_CLIENT_CONFIG);

    rt_pin_write(rk_pcie->ep_pin, rk_pcie->active_val);

    if (rk_pcie->wait_ep)
    {
        timeouts = 10000;
    }

    /* 500ms timeout value should be enough for Gen1/2 training */
    err = readl_poll_timeout(rk_pcie->apb_base + PCIE_CLIENT_BASIC_STATUS1,
            status, PCIE_LINK_UP(status), 20, timeouts * 1000L);
    if (err)
    {
        LOG_E("PCIe link training gen1 timeout");
        goto _err_power_off_phy;
    }

    err = readl_poll_timeout(rk_pcie->apb_base + PCIE_CLIENT_DEBUG_OUT_0,
            status, PCIE_LINK_IS_L0(status), 20, timeouts * 1000L);
    if (err)
    {
        LOG_E("LTSSM is not L0");
        return -ETIMEDOUT;
    }

    if (rk_pcie->link_gen == 2)
    {
        /*
         * Enable retrain for gen2. This should be configured only after
         * gen1 finished.
         */
        status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_LCS);
        status |= PCIEM_LINK_CTL_RETRAIN_LINK;
        rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_LCS);

        err = readl_poll_timeout(rk_pcie->apb_base + PCIE_CORE_CTRL,
                status, PCIE_LINK_IS_GEN2(status), 20, 500 * 1000L);

        if (err)
        {
            LOG_D("PCIe link training gen2 timeout, fall back to gen1");
        }
    }

    /* Check the final link width from negotiated lane counter from MGMT */
    status = rockchip_pcie_read(rk_pcie, PCIE_CORE_CTRL);
    status = 0x1 << ((status & PCIE_CORE_PL_CONF_LANE_MASK) >>
            PCIE_CORE_PL_CONF_LANE_SHIFT);

    /* Power off unused lane(s) */
    rk_pcie->lanes_map = rockchip_pcie_lane_map(rk_pcie);
    for (int i = 0; i < MAX_LANE_NUM; ++i)
    {
        if (!(rk_pcie->lanes_map & RT_BIT(i)))
        {
            rt_phye_power_off(rk_pcie->phys[i]);
        }
    }

    rockchip_pcie_write(rk_pcie, RK_VENDOR_ID, PCIE_CORE_CONFIG_VENDOR);
    rockchip_pcie_write(rk_pcie, PCIS_BRIDGE_PCI << PCIE_RC_CONFIG_SCC_SHIFT,
            PCIE_RC_CONFIG_RID_CCR);

    /* Clear THP cap's next cap pointer to remove L1 substate cap */
    status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_THP_CAP);
    status &= ~PCIE_RC_CONFIG_THP_CAP_NEXT_MASK;
    rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_THP_CAP);

    /* Clear L0s from RC's link cap */
    if (rt_dm_dev_prop_read_bool(dev, "aspm-no-l0s"))
    {
        status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_LINK_CAP);
        status &= ~PCIE_RC_CONFIG_LINK_CAP_L0S;
        rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_LINK_CAP);
    }

    status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_DCSR);
    status &= ~PCIE_RC_CONFIG_DCSR_MPS_MASK;
    status |= PCIE_RC_CONFIG_DCSR_MPS_256;
    rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_DCSR);

    return RT_EOK;

_err_power_off_phy:
    for (int i = 0; i < MAX_LANE_NUM; ++i)
    {
        rt_phye_power_off(rk_pcie->phys[i]);
    }

    for (int i = 0; i < MAX_LANE_NUM; ++i)
    {
        rt_phye_exit(rk_pcie->phys[i]);
    }

    return err;
}

static rt_err_t rockchip_pcie_setup_irq(struct rockchip_pcie *rk_pcie)
{
    struct rt_device *dev = rk_pcie->dev;
    struct rt_ofw_node *np = dev->ofw_node, *intx_np;

    rk_pcie->sys_irq = rt_dm_dev_get_irq_by_name(dev, "sys");
    if (rk_pcie->sys_irq < 0)
    {
        return rk_pcie->sys_irq;
    }

    rk_pcie->legacy_irq = rt_dm_dev_get_irq_by_name(dev, "legacy");
    if (rk_pcie->legacy_irq < 0)
    {
        return rk_pcie->legacy_irq;
    }

    rk_pcie->client_irq = rt_dm_dev_get_irq_by_name(dev, "client");
    if (rk_pcie->client_irq < 0)
    {
        return rk_pcie->client_irq;
    }

    intx_np = rt_ofw_get_next_child(np, RT_NULL);

    if (!intx_np)
    {
        LOG_E("Missing child interrupt-controller node");
        return -RT_EINVAL;
    }

    rk_pcie->intx_np = intx_np;
    rk_pcie->intx_pic.priv_data = rk_pcie;
    rk_pcie->intx_pic.ops = &pcie_intx_ops;
    rt_pic_linear_irq(&rk_pcie->intx_pic, RT_PCI_INTX_PIN_MAX);
    rt_pic_user_extends(&rk_pcie->intx_pic);
    rt_ofw_data(intx_np) = &rk_pcie->intx_pic;

    rt_ofw_node_put(intx_np);

    rt_hw_interrupt_install(rk_pcie->sys_irq, rockchip_pcie_subsys_isr,
            rk_pcie, "rk-pcie-sys");
    rt_hw_interrupt_install(rk_pcie->legacy_irq, rockchip_pcie_legacy_intx_isr,
            rk_pcie, "rk-pcie-legacy");
    rt_hw_interrupt_install(rk_pcie->client_irq, rockchip_pcie_client_isr,
            rk_pcie, "rk-pcie-client");

    return RT_EOK;
}

static rt_err_t rockchip_pcie_prog_ob_atu(struct rockchip_pcie *rk_pcie,
        int region_no, int type, rt_uint8_t num_pass_bits,
        rt_uint32_t lower_addr, rt_uint32_t upper_addr)
{
    rt_uint32_t ob_addr_0, ob_addr_1, ob_desc_0, aw_offset;

    if (region_no >= MAX_AXI_WRAPPER_REGION_NUM)
    {
        return -RT_EINVAL;
    }

    if (num_pass_bits + 1 < 8)
    {
        return -RT_EINVAL;
    }

    if (num_pass_bits > 63)
    {
        return -RT_EINVAL;
    }

    if (region_no == 0)
    {
        if (AXI_REGION_0_SIZE < (2ULL << num_pass_bits))
        {
            return -RT_EINVAL;
        }
    }
    if (region_no != 0)
    {
        if (AXI_REGION_SIZE < (2ULL << num_pass_bits))
        {
            return -RT_EINVAL;
        }
    }

    aw_offset = (region_no << OB_REG_SIZE_SHIFT);

    ob_addr_0 = num_pass_bits & PCIE_CORE_OB_REGION_ADDR0_NUM_BITS;
    ob_addr_0 |= lower_addr & PCIE_CORE_OB_REGION_ADDR0_LO_ADDR;
    ob_addr_1 = upper_addr;
    ob_desc_0 = (1 << 23 | type);

    rockchip_pcie_write(rk_pcie, ob_addr_0, PCIE_CORE_OB_REGION_ADDR0 + aw_offset);
    rockchip_pcie_write(rk_pcie, ob_addr_1, PCIE_CORE_OB_REGION_ADDR1 + aw_offset);
    rockchip_pcie_write(rk_pcie, ob_desc_0, PCIE_CORE_OB_REGION_DESC0 + aw_offset);
    rockchip_pcie_write(rk_pcie, 0, PCIE_CORE_OB_REGION_DESC1 + aw_offset);

    return RT_EOK;
}

static rt_err_t rockchip_pcie_prog_ib_atu(struct rockchip_pcie *rk_pcie,
        int region_no, rt_uint8_t num_pass_bits,
        rt_uint32_t lower_addr, rt_uint32_t upper_addr)
{
    rt_uint32_t ib_addr_0, ib_addr_1, aw_offset;

    if (region_no > MAX_AXI_IB_ROOTPORT_REGION_NUM)
    {
        return -RT_EINVAL;
    }

    if (num_pass_bits + 1 < MIN_AXI_ADDR_BITS_PASSED)
    {
        return -RT_EINVAL;
    }

    if (num_pass_bits > 63)
    {
        return -RT_EINVAL;
    }

    aw_offset = (region_no << IB_ROOT_PORT_REG_SIZE_SHIFT);

    ib_addr_0 = num_pass_bits & PCIE_CORE_IB_REGION_ADDR0_NUM_BITS;
    ib_addr_0 |= (lower_addr << 8) & PCIE_CORE_IB_REGION_ADDR0_LO_ADDR;
    ib_addr_1 = upper_addr;

    rockchip_pcie_write(rk_pcie, ib_addr_0, PCIE_RP_IB_ADDR0 + aw_offset);
    rockchip_pcie_write(rk_pcie, ib_addr_1, PCIE_RP_IB_ADDR1 + aw_offset);

    return RT_EOK;
}

static rt_err_t rockchip_pcie_cfg_atu(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;
    int reg_no;
    rt_off_t offset;
    rt_uint64_t pci_addr, size;
    struct rt_pci_bus_region *region = RT_NULL;
    struct rt_pci_host_bridge *bridge = rk_pcie->bridge;

    rockchip_pcie_cfg_configuration_accesses(rk_pcie, AXI_WRAPPER_TYPE0_CFG);

    for (int i = 0; i < bridge->bus_regions_nr; ++i)
    {
        if (bridge->bus_regions[i].flags == PCI_BUS_REGION_F_MEM)
        {
            region = &bridge->bus_regions[i];
            break;
        }
    }

    if (!region)
    {
        return -RT_ENOSYS;
    }

    size = region->size;
    pci_addr = region->phy_addr;
    rk_pcie->msg_bus_addr = pci_addr;

    for (reg_no = 0; reg_no < (size >> 20); ++reg_no)
    {
        err = rockchip_pcie_prog_ob_atu(rk_pcie, reg_no + 1,
                AXI_WRAPPER_MEM_WRITE, 20 - 1, pci_addr + (reg_no << 20), 0);

        if (err)
        {
            LOG_E("Program RC mem outbound ATU error = %s", rt_strerror(err));
            return err;
        }
    }

    if ((err = rockchip_pcie_prog_ib_atu(rk_pcie, 2, 32 - 1, 0x0, 0)))
    {
        LOG_E("Program RC mem inbound ATU error = %s", rt_strerror(err));
        return err;
    }

    /* Store the register number offset to program RC io outbound ATU */
    offset = size >> 20;

    region = RT_NULL;
    for (int i = 0; i < bridge->bus_regions_nr; ++i)
    {
        if (bridge->bus_regions[i].flags == PCI_BUS_REGION_F_IO)
        {
            region = &bridge->bus_regions[i];
            break;
        }
    }

    size = region->size;
    pci_addr = region->phy_addr;

    for (reg_no = 0; reg_no < (size >> 20); ++reg_no)
    {
        err = rockchip_pcie_prog_ob_atu(rk_pcie, reg_no + 1 + offset,
                AXI_WRAPPER_IO_WRITE, 20 - 1, pci_addr + (reg_no << 20), 0);

        if (err)
        {
            LOG_E("Program RC io outbound ATU error = %s", rt_strerror(err));
            return err;
        }
    }

    /* Assign message regions */
    rockchip_pcie_prog_ob_atu(rk_pcie, reg_no + 1 + offset,
            AXI_WRAPPER_NOR_MSG, 20 - 1, 0, 0);

    rk_pcie->msg_bus_addr += (reg_no + offset) << 20;
    rk_pcie->msg_region = rt_ioremap((void *)rk_pcie->msg_bus_addr, SIZE_MB);
    if (!rk_pcie->msg_region)
    {
        err = -RT_ENOMEM;
    }

    return err;
}

#ifdef RT_USING_PM
static int rockchip_pcie_pm_suspend(const struct rt_device *dev, rt_uint8_t mode)
{
    struct rockchip_pcie *rk_pcie = dev->user_data;

    rockchip_pcie_disable_clocks(rk_pcie);
    rt_regulator_disable(rk_pcie->vpcie0v9);

    return RT_EOK;
}

static void rockchip_pcie_pm_resume(const struct rt_device *dev, rt_uint8_t mode)
{
    struct rockchip_pcie *rk_pcie = dev->user_data;

    if (rt_regulator_enable(rk_pcie->vpcie0v9))
    {
        LOG_E("Fail to enable vpcie0v9 regulator");
        return;
    }

    if (rockchip_pcie_enable_clocks(rk_pcie))
    {
        rt_regulator_disable(rk_pcie->vpcie0v9);
    }
}

static const struct rt_device_pm_ops rockchip_pcie_pm_ops =
{
    .suspend = rockchip_pcie_pm_suspend,
    .resume = rockchip_pcie_pm_resume,
};
#endif /* RT_USING_PM */

static void rockchip_pcie_free(struct rockchip_pcie *rk_pcie)
{
    rockchip_pcie_common_free(rk_pcie);

    if (rk_pcie->sys_irq > 0)
    {
        rt_hw_interrupt_mask(rk_pcie->sys_irq);
        rt_pic_detach_irq(rk_pcie->sys_irq, rk_pcie);
    }

    if (rk_pcie->legacy_irq > 0)
    {
        rt_hw_interrupt_mask(rk_pcie->legacy_irq);
        rt_pic_detach_irq(rk_pcie->legacy_irq, rk_pcie);
    }

    if (rk_pcie->client_irq > 0)
    {
        rt_hw_interrupt_mask(rk_pcie->client_irq);
        rt_pic_detach_irq(rk_pcie->client_irq, rk_pcie);
    }

    rt_pci_host_bridge_free(rk_pcie->bridge);
    rt_free(rk_pcie);
}

static rt_err_t rockchip_pcie_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rockchip_pcie *rk_pcie;
    struct rt_pci_host_bridge *bridge;
    struct rt_device *dev = &pdev->parent;

    if (!(bridge = rt_pci_host_bridge_alloc(sizeof(*rk_pcie))))
    {
        return -RT_ENOMEM;
    }

    rk_pcie = (void *)bridge->priv;
    rk_pcie->bridge = bridge;
    rk_pcie->dev = dev;
    rk_pcie->is_rc = RT_TRUE;

    if ((err = rockchip_pcie_host_ofw_parse(rk_pcie)))
    {
        return err;
    }

    if ((err = rockchip_pcie_enable_clocks(rk_pcie)))
    {
        return err;
    }

    if ((err = rockchip_pcie_set_vpcie(rk_pcie)))
    {
        goto _err_set_vpcie;
    }

    if ((err = rockchip_pcie_host_init_port(rk_pcie)))
    {
        goto _err_deinit_port;
    }

    if ((err = rockchip_pcie_setup_irq(rk_pcie)))
    {
        goto _err_deinit_port;
    }

    rockchip_pcie_enable_interrupts(rk_pcie);

    if ((err = rockchip_pcie_cfg_atu(rk_pcie)))
    {
        goto _err_deinit_port;
    }

    rk_pcie->bridge->parent.ofw_node = dev->ofw_node;
    rk_pcie->bridge->sysdata = rk_pcie;
    rk_pcie->bridge->ops = &rockchip_pcie_ops;
    dev->user_data = rk_pcie;

    if ((err = rt_pci_host_bridge_probe(rk_pcie->bridge)))
    {
        goto _err_deinit_port;
    }

#ifdef RT_USING_PM
    rt_pm_device_register(dev, &rockchip_pcie_pm_ops);
#endif

    return RT_EOK;

_err_deinit_port:
    if (rk_pcie->intx_np)
    {
        rt_pic_cancel_irq(&rk_pcie->intx_pic);
    }

    rockchip_pcie_deinit_phys(rk_pcie);

    if (!rt_is_err_or_null(rk_pcie->vpcie12v))
    {
        rt_regulator_disable(rk_pcie->vpcie12v);
        rt_regulator_put(rk_pcie->vpcie12v);
    }
    if (!rt_is_err_or_null(rk_pcie->vpcie3v3))
    {
        rt_regulator_disable(rk_pcie->vpcie3v3);
        rt_regulator_put(rk_pcie->vpcie3v3);
    }
    rt_regulator_disable(rk_pcie->vpcie1v8);
    rt_regulator_put(rk_pcie->vpcie1v8);
    rt_regulator_disable(rk_pcie->vpcie0v9);
    rt_regulator_put(rk_pcie->vpcie0v9);

_err_set_vpcie:
    rockchip_pcie_disable_clocks(rk_pcie);
    rockchip_pcie_free(rk_pcie);

    return err;
}

static rt_err_t rockchip_pcie_remove(struct rt_platform_device *pdev)
{
    rt_uint32_t status, status1, status2;
    struct rockchip_pcie *rk_pcie = pdev->parent.user_data;

    rt_pci_host_bridge_remove(rk_pcie->bridge);

    rt_ofw_data(rk_pcie->intx_np) = RT_NULL;

    rt_hw_interrupt_mask(rk_pcie->sys_irq);
    rt_pic_detach_irq(rk_pcie->sys_irq, rk_pcie);
    rt_hw_interrupt_mask(rk_pcie->legacy_irq);
    rt_pic_detach_irq(rk_pcie->legacy_irq, rk_pcie);
    rt_hw_interrupt_mask(rk_pcie->client_irq);
    rt_pic_detach_irq(rk_pcie->client_irq, rk_pcie);

#ifdef RT_USING_PM
    rt_pm_device_unregister(&pdev->parent);
#endif

    status1 = rockchip_pcie_read(rk_pcie, PCIE_CLIENT_BASIC_STATUS1);
    status2 = rockchip_pcie_read(rk_pcie, PCIE_CLIENT_DEBUG_OUT_0);

    if (!PCIE_LINK_UP(status1) || !PCIE_LINK_IS_L0(status2))
    {
        rk_pcie->in_remove = RT_TRUE;
    }

    /* Disable link state */
    status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_LCS);
    status |= RT_BIT(4);
    rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_LCS);

    rt_thread_mdelay(1);

    status = rockchip_pcie_read(rk_pcie, PCIE_RC_CONFIG_LCS);
    status &= ~RT_BIT(4);
    rockchip_pcie_write(rk_pcie, status, PCIE_RC_CONFIG_LCS);

    rockchip_pcie_deinit_phys(rk_pcie);

    rockchip_pcie_disable_clocks(rk_pcie);

    if (!rt_is_err_or_null(rk_pcie->vpcie12v))
    {
        rt_regulator_disable(rk_pcie->vpcie12v);
    }
    if (!rt_is_err_or_null(rk_pcie->vpcie3v3))
    {
        rt_regulator_disable(rk_pcie->vpcie3v3);
    }
    rt_regulator_disable(rk_pcie->vpcie1v8);
    rt_regulator_disable(rk_pcie->vpcie0v9);

    rockchip_pcie_free(rk_pcie);

    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_pcie_ofw_ids[] =
{
    { .compatible = "rockchip,rk3399-pcie", },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_pcie_driver =
{
    .name = "rk_pcie-pcie-host",
    .ids = rockchip_pcie_ofw_ids,

    .probe = rockchip_pcie_probe,
    .remove = rockchip_pcie_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_pcie_driver);
