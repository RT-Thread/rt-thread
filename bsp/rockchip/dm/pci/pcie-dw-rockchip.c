/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#define DBG_TAG "pci.dw.rockchip"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pcie-dw.h"
#include "rockchip.h"

#define PCIE_DMA_OFFSET                     0x380000

#define PCIE_DMA_CTRL_OFF                   0x8
#define PCIE_DMA_WR_ENB                     0xc
#define PCIE_DMA_WR_CTRL_LO                 0x200
#define PCIE_DMA_WR_CTRL_HI                 0x204
#define PCIE_DMA_WR_XFERSIZE                0x208
#define PCIE_DMA_WR_SAR_PTR_LO              0x20c
#define PCIE_DMA_WR_SAR_PTR_HI              0x210
#define PCIE_DMA_WR_DAR_PTR_LO              0x214
#define PCIE_DMA_WR_DAR_PTR_HI              0x218
#define PCIE_DMA_WR_WEILO                   0x18
#define PCIE_DMA_WR_WEIHI                   0x1c
#define PCIE_DMA_WR_DOORBELL                0x10
#define PCIE_DMA_WR_INT_STATUS              0x4c
#define PCIE_DMA_WR_INT_MASK                0x54
#define PCIE_DMA_WR_INT_CLEAR               0x58

#define PCIE_DMA_RD_ENB                     0x2c
#define PCIE_DMA_RD_CTRL_LO                 0x300
#define PCIE_DMA_RD_CTRL_HI                 0x304
#define PCIE_DMA_RD_XFERSIZE                0x308
#define PCIE_DMA_RD_SAR_PTR_LO              0x30c
#define PCIE_DMA_RD_SAR_PTR_HI              0x310
#define PCIE_DMA_RD_DAR_PTR_LO              0x314
#define PCIE_DMA_RD_DAR_PTR_HI              0x318
#define PCIE_DMA_RD_WEILO                   0x38
#define PCIE_DMA_RD_WEIHI                   0x3c
#define PCIE_DMA_RD_DOORBELL                0x30
#define PCIE_DMA_RD_INT_STATUS              0xa0
#define PCIE_DMA_RD_INT_MASK                0xa8
#define PCIE_DMA_RD_INT_CLEAR               0xac

#define PCIE_DMA_CHANEL_MAX_NUM             2

/* Parameters for the waiting for iATU enabled routine */
#define LINK_WAIT_IATU_MIN                  9000
#define LINK_WAIT_IATU_MAX                  10000

#define PCIE_DIRECT_SPEED_CHANGE            (0x1 << 17)

#define PCIE_TYPE0_STATUS_COMMAND_REG       0x4
#define PCIE_TYPE0_BAR0_REG                 0x10

#define PCIE_CAP_LINK_CONTROL2_LINK_STATUS  0xa0

#define PCIE_CLIENT_INTR_STATUS_MSG_RX      0x04
#define PME_TO_ACK                          (RT_BIT(9) | RT_BIT(25))
#define PCIE_CLIENT_INTR_STATUS_LEGACY      0x08
#define PCIE_CLIENT_INTR_STATUS_MISC        0x10
#define PCIE_CLIENT_INTR_MASK_LEGACY        0x1c
#define UNMASK_ALL_LEGACY_INT               0xffff0000
#define MASK_LEGACY_INT(x)                  (0x00110011 << (x))
#define UNMASK_LEGACY_INT(x)                (0x00110000 << (x))
#define PCIE_CLIENT_INTR_MASK               0x24
#define PCIE_CLIENT_POWER                   0x2c
#define READY_ENTER_L23                     RT_BIT(3)
#define PCIE_CLIENT_MSG_GEN                 0x34
#define PME_TURN_OFF                        (RT_BIT(4) | RT_BIT(20))
#define PCIE_CLIENT_GENERAL_DEBUG           0x104
#define PCIE_CLIENT_HOT_RESET_CTRL          0x180
#define PCIE_LTSSM_APP_DLY1_EN              RT_BIT(0)
#define PCIE_LTSSM_APP_DLY2_EN              RT_BIT(1)
#define PCIE_LTSSM_APP_DLY1_DONE            RT_BIT(2)
#define PCIE_LTSSM_APP_DLY2_DONE            RT_BIT(3)
#define PCIE_LTSSM_ENABLE_ENHANCE           RT_BIT(4)
#define PCIE_CLIENT_LTSSM_STATUS            0x300
#define SMLH_LINKUP                         RT_BIT(16)
#define RDLH_LINKUP                         RT_BIT(17)
#define PCIE_CLIENT_CDM_RASDES_TBA_INFO_CMN 0x154
#define PCIE_CLIENT_DBG_FIFO_MODE_CON       0x310
#define PCIE_CLIENT_DBG_FIFO_PTN_HIT_D0     0x320
#define PCIE_CLIENT_DBG_FIFO_PTN_HIT_D1     0x324
#define PCIE_CLIENT_DBG_FIFO_TRN_HIT_D0     0x328
#define PCIE_CLIENT_DBG_FIFO_TRN_HIT_D1     0x32c
#define PCIE_CLIENT_DBG_FIFO_STATUS         0x350
#define PCIE_CLIENT_DBG_TRANSITION_DATA     0xffff0000
#define PCIE_CLIENT_DBF_EN                  0xffff0007

#define PCIE_PHY_LINKUP                     RT_BIT(0)
#define PCIE_DATA_LINKUP                    RT_BIT(1)

#define PCIE_TYPE0_HDR_DBI2_OFFSET          0x100000
#define PCIE_SB_BAR0_MASK_REG               0x100010

#define PCIE_PL_ORDER_RULE_CTRL_OFF         0x8b4
#define RK_PCIE_L2_TMOUT_US                 5000
#define RK_PCIE_HOTRESET_TMOUT_US           10000
#define RK_PCIE_ENUM_HW_RETRYIES            2

enum rockchip_pcie_ltssm_code
{
    S_L0        = 0x11,
    S_L0S       = 0x12,
    S_L1_IDLE   = 0x14,
    S_L2_IDLE   = 0x15,
    S_MAX       = 0x1f,
};

enum rockchip_pcie_soc_type
{
    SOC_TYPE_ALL = 0,
    SOC_TYPE_RK1808,
};

struct rockchip_pcie_soc_data
{
    enum rockchip_pcie_soc_type type;
    enum dw_pcie_device_mode mode;
    rt_uint32_t msi_vector_num;
};

struct rockchip_pcie
{
    struct dw_pcie pci;

    void *apb_base;

    enum rt_phye_mode phy_mode;
    enum rt_phye_mode phy_submode;

    struct rt_phye *phy;
    struct rt_clk_array *clk_arr;
    struct rt_reset_control *rstc;
    struct rt_regulator *vpcie3v3;

    struct rt_syscon *usb_pcie_grf;
    struct rt_syscon *pmu_grf;

    rt_base_t rst_pin;
    rt_uint8_t rst_active_val;

    rt_base_t prsnt_pin;
    rt_uint8_t prsnt_active_val;
    rt_uint32_t perst_inactive_ms;

    rt_uint64_t mem_start;
    rt_uint64_t mem_size;

    rt_uint32_t msi_vector_num;
    rt_uint32_t comp_prst[2];

    rt_bool_t in_suspend;
    rt_bool_t skip_scan_in_resume;
    rt_bool_t is_signal_test;
    rt_bool_t bifurcation;
    rt_bool_t supports_clkreq;
    struct rt_work hot_rst_work;

    int intx_irq;
    rt_uint32_t intx;
    struct rt_ofw_node *intx_np;
    struct rt_pic intx_pic;

    const struct rockchip_pcie_soc_data *soc_data;
};

#define to_rockchip_pcie(dw_pcie) rt_container_of(dw_pcie, struct rockchip_pcie, pci)

rt_inline rt_uint32_t rockchip_pcie_readl_apb(struct rockchip_pcie *rk_pcie,
        int offset)
{
    return HWREG32(rk_pcie->apb_base + offset);
}

rt_inline void rockchip_pcie_writel_apb(struct rockchip_pcie *rk_pcie,
        int offset, rt_uint32_t val)
{
    HWREG32(rk_pcie->apb_base + offset) = val;
}

rt_inline void rockchip_pcie_link_status_clear(struct rockchip_pcie *rk_pcie)
{
    rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_GENERAL_DEBUG, 0x0);
}

rt_inline void rockchip_pcie_disable_ltssm(struct rockchip_pcie *rk_pcie)
{
    rockchip_pcie_writel_apb(rk_pcie, 0x0, 0xc0008);
}

rt_inline void rockchip_pcie_enable_ltssm(struct rockchip_pcie *rk_pcie)
{
    rockchip_pcie_writel_apb(rk_pcie, 0x0, 0xc000c);
}

rt_inline rt_bool_t rockchip_pcie_udma_enabled(struct rockchip_pcie *rk_pcie)
{
    return dw_pcie_readl_dbi(&rk_pcie->pci, PCIE_DMA_OFFSET + PCIE_DMA_CTRL_OFF);
}

static void rockchip_pcie_intx_irq_mask(struct rt_pic_irq *pirq)
{
    struct rockchip_pcie *rk_pcie = pirq->pic->priv_data;

    rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_INTR_MASK_LEGACY,
            MASK_LEGACY_INT(pirq->hwirq));
}

static void rockchip_pcie_intx_irq_unmask(struct rt_pic_irq *pirq)
{
    struct rockchip_pcie *rk_pcie = pirq->pic->priv_data;

    rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_INTR_MASK_LEGACY,
            UNMASK_LEGACY_INT(pirq->hwirq));
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
            rt_pic_irq_set_triger_mode(irq, RT_IRQ_MODE_LEVEL_HIGH);
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

const static struct rt_pic_ops rockchip_intx_ops =
{
    .name = "DWPCI-RK-INTx",
    .irq_mask = rockchip_pcie_intx_irq_mask,
    .irq_unmask = rockchip_pcie_intx_irq_unmask,
    .irq_map = rockchip_pcie_intx_irq_map,
    .irq_parse = rockchip_pcie_intx_irq_parse,
};

static void rockchip_pcie_sys_isr(int irqno, void *param)
{
    rt_uint32_t reg;
    struct rockchip_pcie *rk_pcie = param;

    /* DMA ISR */
    LOG_D("%s: DMA %s status = %x", rt_dm_dev_get_name(rk_pcie->dev), "WR",
            dw_pcie_readl_dbi(&rk_pcie->pci, PCIE_DMA_OFFSET + PCIE_DMA_WR_INT_STATUS));

    LOG_D("%s: DMA %s status = %x", rt_dm_dev_get_name(rk_pcie->dev), "RD",
            dw_pcie_readl_dbi(&rk_pcie->pci, PCIE_DMA_OFFSET + PCIE_DMA_WR_INT_STATUS));

    /* MISC ISR */
    reg = rockchip_pcie_readl_apb(rk_pcie, PCIE_CLIENT_INTR_STATUS_MISC);

    if (reg & RT_BIT(2))
    {
        rt_work_submit(&rk_pcie->hot_rst_work, 0);
    }

    rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_INTR_STATUS_MISC, reg);
}

static void rockchip_pcie_legacy_isr(int irqno, void *param)
{
    rt_uint32_t ints;
    struct rt_pic_irq *pirq;
    struct rockchip_pcie *rk_pcie = param;

    ints = rockchip_pcie_readl_apb(rk_pcie, PCIE_CLIENT_INTR_STATUS_LEGACY);

    for (int pin = 0; ints && pin < RT_PCI_INTX_PIN_MAX; ++pin, ints >>= 1)
    {
        if ((ints & 1))
        {
            pirq = rt_pic_find_irq(&rk_pcie->intx_pic, pin);

            rt_pic_handle_isr(pirq);
        }
    }
}

static void rockchip_pcie_hot_rst_work(struct rt_work *work, void *work_data)
{
    rt_err_t err;
    rt_uint32_t val, status;
    struct rockchip_pcie *rk_pcie = work_data;

    val = dw_pcie_readl_dbi(&rk_pcie->pci, PCIR_COMMAND);
    val &= 0xffff0000;
    val |= PCIM_CMD_PORTEN | PCIM_CMD_MEMEN | PCIM_CMD_BUSMASTEREN | PCIM_CMD_SERRESPEN;
    dw_pcie_writel_dbi(&rk_pcie->pci, PCIR_COMMAND, val);

    if (rockchip_pcie_readl_apb(rk_pcie, PCIE_CLIENT_HOT_RESET_CTRL) & PCIE_LTSSM_APP_DLY2_EN)
    {
        err = readl_poll_timeout(rk_pcie->apb_base + PCIE_CLIENT_LTSSM_STATUS,
                status, ((status & 0x3f) == 0), 100, RK_PCIE_HOTRESET_TMOUT_US);
        if (err)
        {
            LOG_E("Wait for detect quiet timeout");
        }

        rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_HOT_RESET_CTRL,
                (PCIE_LTSSM_APP_DLY2_DONE) | ((PCIE_LTSSM_APP_DLY2_DONE) << 16));
    }
}

rt_inline rt_err_t rockchip_pcie_enable_power(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err = RT_EOK;

    if (rk_pcie->vpcie3v3)
    {
        err = rt_regulator_set_voltage(rk_pcie->vpcie3v3, 3300000, 3300000);
        err |= rt_regulator_enable(rk_pcie->vpcie3v3);
    }

    return err;
}

rt_inline rt_err_t rockchip_pcie_disable_power(struct rockchip_pcie *rk_pcie)
{
    if (rk_pcie->vpcie3v3)
    {
        return rt_regulator_disable(rk_pcie->vpcie3v3);
    }

    return RT_EOK;
}

static void rockchip_pcie_fast_link_setup(struct rockchip_pcie *rk_pcie)
{
    rt_uint32_t val;

    /* LTSSM EN ctrl mode */
    val = rockchip_pcie_readl_apb(rk_pcie, PCIE_CLIENT_HOT_RESET_CTRL);
    val |= (PCIE_LTSSM_ENABLE_ENHANCE | PCIE_LTSSM_APP_DLY2_EN) |
            ((PCIE_LTSSM_APP_DLY2_EN | PCIE_LTSSM_ENABLE_ENHANCE) << 16);
    rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_HOT_RESET_CTRL, val);
}

static rt_err_t rockchip_pcie_establish_link_raw(struct rockchip_pcie *rk_pcie)
{
    rt_uint32_t ltssm;
    rt_bool_t std_rc = rk_pcie->soc_data->mode == DW_PCIE_RC_TYPE;
    struct dw_pcie *pci = &rk_pcie->pci;

    /*
     * For standard RC, even if the link has been setup by firmware,
     * we still need to reset link as we need to remove all resource info
     * from devices, for instance BAR, as it wasn't assigned by kernel.
     */
    if (dw_pcie_link_up(pci) && !std_rc)
    {
        LOG_E("Link is already up");
        return RT_EOK;
    }

    for (int hw_retries = 0; hw_retries < RK_PCIE_ENUM_HW_RETRYIES; ++hw_retries)
    {
        /* Rest the device */
        rt_pin_write(rk_pcie->rst_pin, !rk_pcie->rst_active_val);

        rockchip_pcie_disable_ltssm(rk_pcie);
        rockchip_pcie_link_status_clear(rk_pcie);

        if (rk_pcie->soc_data->type != SOC_TYPE_RK1808)
        {
            rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_PTN_HIT_D0,
                    PCIE_CLIENT_DBG_TRANSITION_DATA);
            rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_PTN_HIT_D1,
                    PCIE_CLIENT_DBG_TRANSITION_DATA);
            rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_TRN_HIT_D0,
                    PCIE_CLIENT_DBG_TRANSITION_DATA);
            rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_TRN_HIT_D1,
                    PCIE_CLIENT_DBG_TRANSITION_DATA);
            rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_DBG_FIFO_MODE_CON,
                    PCIE_CLIENT_DBF_EN);
        }

        /* Enable client reset or link down interrupt */
        rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_INTR_MASK, 0x40000);

        /* Enable LTSSM */
        rockchip_pcie_enable_ltssm(rk_pcie);

        /*
         * In resume routine, function devices' resume function must be late
         * after controllers'. Some devices, such as Wi-Fi,
         * need special IO setting before finishing training.
         * So there must be timeout here. These kinds of devices need rescan
         * devices by its driver when used. So no need to waste time waiting
         * for training pass.
         */
        if (rk_pcie->in_suspend && rk_pcie->skip_scan_in_resume)
        {
            /*
             * Check WiFi power status here.
             * If down, active the RST pin and return.
             */
        }

        /*
         * PCIe requires the refclk to be stable for 100µs prior to releasing
         * PERST and T_PVPERL (Power stable to PERST# inactive) should be a
         * minimum of 100ms.  See table 2-4 in section 2.6.2 AC, the PCI Express
         * Card Electromechanical Specification 3.0.
         * So 100ms in total is the min requuirement here.
         * We add a 200ms by default for sake of hoping everthings work fine.
         * If it doesn't, Add more in DT node by add rockchip,perst-inactive-ms.
         */
        rt_thread_mdelay(rk_pcie->perst_inactive_ms);
        rt_pin_write(rk_pcie->rst_pin, rk_pcie->rst_active_val);

        /* Link is always up stably after 1ms. */
        rt_thread_mdelay(2);

        for (int retries = 0; retries < 100; ++retries)
        {
            if (dw_pcie_link_up(pci))
            {
                /*
                 * We may be here in case of L0 in Gen1. But if EP is capable
                 * of Gen2 or Gen3, Gen switch may happen just in this time, but
                 * we keep on accessing devices in unstable link status. Given
                 * that LTSSM max timeout is 24ms per period, we can wait a bit
                 * more for Gen switch.
                 */
                rt_thread_mdelay(50);

                /* In case link drop after linkup, double check it */
                if (dw_pcie_link_up(pci))
                {
                    LOG_I("PCIe Link up, LTSSM is 0x%x",
                            rockchip_pcie_readl_apb(rk_pcie, PCIE_CLIENT_LTSSM_STATUS));

                    return RT_EOK;
                }
            }

            if (!(retries % 20))
            {
                LOG_I("PCIe Linking... LTSSM is 0x%x",
                        rockchip_pcie_readl_apb(rk_pcie, PCIE_CLIENT_LTSSM_STATUS));
            }
            rt_thread_mdelay(20);
        }

        /*
         * In response to the situation where PCIe peripherals cannot be
         * enumerated due tosignal abnormalities, reset PERST# and reset
         * the peripheral power supply, then restart the enumeration.
         */
        ltssm = rockchip_pcie_readl_apb(rk_pcie, PCIE_CLIENT_LTSSM_STATUS);
        LOG_E("PCIe Link Fail, LTSSM is 0x%x", ltssm);

        if (ltssm >= 3 && !rk_pcie->is_signal_test)
        {
            rockchip_pcie_disable_power(rk_pcie);
            rt_thread_mdelay(1000);
            rockchip_pcie_enable_power(rk_pcie);
        }
        else
        {
            break;
        }
    }

    return rk_pcie->is_signal_test == RT_TRUE ? 0 : -RT_EINVAL;
}

rt_inline void rockchip_pcie_set_mode(struct rockchip_pcie *rk_pcie)
{
    switch (rk_pcie->soc_data->mode)
    {
    case DW_PCIE_EP_TYPE:
        rockchip_pcie_writel_apb(rk_pcie, 0x0, 0xf00000);

        break;

    case DW_PCIE_RC_TYPE:
        if (rk_pcie->supports_clkreq)
        {
            /* Application is ready to have reference clock removed */
            rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_POWER, 0x00010001);
        }
        else
        {
            /* Pull down CLKREQ# to assert the connecting CLOCK_GEN OE */
            rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_POWER, 0x30011000);
            /* Disable ASPM L1SS here */
        }

        rockchip_pcie_writel_apb(rk_pcie, 0x0, 0xf00040);

        /*
         * Disable order rule for CPL can't pass halted P queue.
         * Need to check producer-consumer model. Just for RK1808 platform.
         */
        if (rk_pcie->soc_data->type == SOC_TYPE_RK1808)
        {
            dw_pcie_writel_dbi(&rk_pcie->pci, PCIE_PL_ORDER_RULE_CTRL_OFF, 0xff00);
        }
        break;

    default:
        break;
    }
}

static rt_err_t rockchip_pcie_reset_grant_ctrl(struct rockchip_pcie *rk_pcie,
        rt_bool_t enable)
{
    rt_uint32_t val = (0x1 << 18);

    if (enable)
    {
        val |= (0x1 << 2);
    }

    return rt_syscon_write(rk_pcie->usb_pcie_grf, 0x0, val);
}

static void rockchip_pcie_ep_reset_bar(struct rockchip_pcie *rk_pcie,
        int bar_idx, rt_ubase_t flags)
{
    rt_uint32_t reg = PCIR_BAR(bar_idx);

    dw_pcie_writel_dbi(&rk_pcie->pci, reg, 0x0);

    if (flags & PCIM_BAR_MEM_TYPE_64)
    {
        dw_pcie_writel_dbi(&rk_pcie->pci, reg + 4, 0x0);
    }
}

static rt_err_t rockchip_pcie_ep_inbound_atu(struct rockchip_pcie *rk_pcie,
        int bar_idx, rt_ubase_t cpu_addr, enum dw_pcie_aspace_type aspace_type)
{
    rt_err_t err;
    rt_uint32_t free_win;
    rt_uint8_t func_no = 0x0;
    struct dw_pcie_ep *ep = &rk_pcie->pci.endpoint;

    if (rk_pcie->in_suspend)
    {
        free_win = ep->bar_to_atu[bar_idx];
    }
    else
    {
        free_win = rt_bitmap_next_clear_bit(ep->ib_window_map, 0, ep->num_ib_windows);

        if (free_win >= ep->num_ib_windows)
        {
            LOG_E("No free inbound window");
            return -RT_EINVAL;
        }
    }

    if ((err = dw_pcie_prog_inbound_atu(&rk_pcie->pci, func_no, free_win,
            bar_idx, cpu_addr, aspace_type)))
    {
        LOG_E("Failed to program IB window");
        return err;
    }

    if (rk_pcie->in_suspend)
    {
        return RT_EOK;
    }

    ep->bar_to_atu[bar_idx] = free_win;
    rt_bitmap_set_bit(ep->ib_window_map, free_win);

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_outbound_atu(struct rockchip_pcie *rk_pcie,
        rt_ubase_t phys_addr, rt_uint64_t pci_addr, rt_size_t size)
{
    rt_uint32_t free_win;
    struct dw_pcie_ep *ep = &rk_pcie->pci.endpoint;

    if (rk_pcie->in_suspend)
    {
        free_win = rt_bitmap_next_set_bit(ep->ob_window_map, 0, ep->num_ob_windows);
    }
    else
    {
        free_win = rt_bitmap_next_clear_bit(ep->ob_window_map, 0, ep->num_ob_windows);

        if (free_win >= ep->num_ob_windows)
        {
            LOG_E("No free outbound window");
            return -RT_EINVAL;
        }
    }

    dw_pcie_prog_outbound_atu(&rk_pcie->pci, free_win, PCIE_ATU_TYPE_MEM,
            phys_addr, pci_addr, size);

    if (rk_pcie->in_suspend)
    {
        return RT_EOK;
    }

    ep->outbound_addr[free_win] = phys_addr;
    rt_bitmap_set_bit(ep->ob_window_map, free_win);

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_atu_init(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;

    for (int bar = 0; bar < PCI_STD_NUM_BARS; ++bar)
    {
        rockchip_pcie_ep_reset_bar(rk_pcie, bar, 0);
    }

    if ((err = rockchip_pcie_ep_inbound_atu(rk_pcie, 0, rk_pcie->mem_start,
            DW_PCIE_ASPACE_MEM)))
    {
        return err;
    }

    if ((err = rockchip_pcie_ep_outbound_atu(rk_pcie, 0x0, 0x0, 2UL * SIZE_GB)))
    {
        return err;
    }

    return RT_EOK;
}

static rt_err_t rockchip_pcie_establish_link(struct dw_pcie *pci)
{
    struct rockchip_pcie *rk_pcie = rt_container_of(pci, struct rockchip_pcie, pci);

    return rockchip_pcie_establish_link_raw(rk_pcie);
}

static const struct dw_pcie_ops dw_pcie_ops =
{
    .start_link = rockchip_pcie_establish_link,
};

static rt_err_t rockchip_pcie_host_init(struct dw_pcie_port *port)
{
    rt_err_t err;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);
    struct rockchip_pcie *rk_pcie = rt_container_of(pci, struct rockchip_pcie, pci);

    dw_pcie_setup_rc(port);

    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);

    /* Disable BAR0 BAR1 */
    dw_pcie_writel_dbi2(pci, PCIR_BAR(0), 0);
    dw_pcie_writel_dbi2(pci, PCIR_BAR(1), 0);

    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);

    err = rockchip_pcie_establish_link_raw(rk_pcie);

    if (port->msi_irq > 0)
    {
        dw_pcie_msi_init(port);
    }

    return err;
}

static rt_err_t rockchip_pcie_msi_host_init(struct dw_pcie_port *port)
{
    return RT_EOK;
}

static void rockchip_pcie_set_irq_count(struct dw_pcie_port *port)
{
    struct dw_pcie *pci = to_dw_pcie_from_port(port);
    struct rockchip_pcie *rk_pcie = rt_container_of(pci, struct rockchip_pcie, pci);

    port->irq_count = rk_pcie->msi_vector_num;
}

static struct dw_pcie_host_ops rockchip_pcie_port_ops[] =
{
    [0] =   /* Normal */
    {
        .host_init = rockchip_pcie_host_init,
    },
    [1] =   /* MSI */
    {
        .host_init = rockchip_pcie_host_init,
        .msi_host_init = rockchip_pcie_msi_host_init,
    },
    [2] =   /* No MSI */
    {
        .host_init = rockchip_pcie_host_init,
        .set_irq_count = rockchip_pcie_set_irq_count,
    },
};

static rt_err_t rockchip_pcie_add_port(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;
    struct dw_pcie *pci = &rk_pcie->pci;
    struct dw_pcie_port *port = &pci->port;

    port->ops = &rockchip_pcie_port_ops[0];
#ifdef RT_USING_MSI
    if ((port->msi_irq = rt_dm_dev_get_irq_by_name(dev, "msi")) < 0)
    {
        port->ops = &rockchip_pcie_port_ops[1];
    }
    else
    {
        port->ops = &rockchip_pcie_port_ops[2];
    }
#endif

    if ((err = dw_pcie_host_init(port)))
    {
        LOG_E("Init HOST error = %s", rt_strerror(err));
        return err;
    }

    return RT_EOK;
}

static rt_err_t rockchip_pcie_ep_raise_irq(struct dw_pcie_ep *ep,
        rt_uint8_t func_no, enum rt_pci_ep_irq type, unsigned irq)
{
    switch (type)
    {
    case RT_PCI_EP_IRQ_LEGACY:
        return dw_pcie_ep_raise_legacy_irq(ep, func_no);

    case RT_PCI_EP_IRQ_MSI:
        return dw_pcie_ep_raise_msi_irq(ep, func_no, irq);

    case RT_PCI_EP_IRQ_MSIX:
        return dw_pcie_ep_raise_msix_irq(ep, func_no, irq);

    default:
        LOG_E("Unknown IRQ type = %d", type);
    }

    return RT_EOK;
}

static struct dw_pcie_ep_ops rockchip_pcie_ep_ops =
{
    .raise_irq = rockchip_pcie_ep_raise_irq,
};

static rt_err_t rockchip_pcie_ep_set_bar_flag(struct rockchip_pcie *rk_pcie,
        int bar_idx, rt_ubase_t flags)
{
    rt_uint32_t reg = PCIR_BAR(bar_idx);
    struct dw_pcie *pci = &rk_pcie->pci;

    /* Disabled the upper 32bits BAR to make a 64bits bar pair */
    if (flags & PCIM_BAR_MEM_TYPE_64)
    {
        dw_pcie_writel_dbi2(pci, reg + 4, 0);
    }

    dw_pcie_writel_dbi(pci, reg, flags);

    if (flags & PCIM_BAR_MEM_TYPE_64)
    {
        dw_pcie_writel_dbi(pci, reg + 4, 0);
    }

    return 0;
}

static void rockchip_pcie_ep_setup_top(struct rockchip_pcie *rk_pcie)
{
    struct dw_pcie *pci = &rk_pcie->pci;

    /* Enable client write and read interrupt */
    rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_INTR_MASK, 0xc000000);
    /* Enable core write interrupt */
    dw_pcie_writel_dbi(pci, PCIE_DMA_OFFSET + PCIE_DMA_WR_INT_MASK, 0x0);
    /* Enable core read interrupt */
    dw_pcie_writel_dbi(pci, PCIE_DMA_OFFSET + PCIE_DMA_RD_INT_MASK, 0x0);
}

static void rockchip_pcie_ep_setup_bottom(struct rockchip_pcie *rk_pcie)
{
    int resbar_base;
    struct dw_pcie *pci = &rk_pcie->pci;

    /* Enable bus master and memory space */
    dw_pcie_writel_dbi(pci, PCIE_TYPE0_STATUS_COMMAND_REG, 0x6);

    resbar_base = dw_pcie_find_ext_capability(pci, PCIZ_RESIZE_BAR);
    if (!resbar_base)
    {
        LOG_W("Resbar CAP not found");
    }
    else
    {
        /*
         * Resize:
         * BAR0 to support 512GB
         * BAR1 to support 8M
         * BAR2~5 to support 64M
         */
        dw_pcie_writel_dbi(pci, resbar_base + 0x4, 0xfffff0);
        dw_pcie_writel_dbi(pci, resbar_base + 0x8, 0x13c0);
        dw_pcie_writel_dbi(pci, resbar_base + 0xc, 0xfffff0);
        dw_pcie_writel_dbi(pci, resbar_base + 0x10, 0x3c0);

        for (int bar = 2; bar < PCI_STD_NUM_BARS; ++bar)
        {
            dw_pcie_writel_dbi(pci, resbar_base + 0x4 + bar * 0x8, 0xfffff0);
            dw_pcie_writel_dbi(pci, resbar_base + 0x8 + bar * 0x8, 0x6c0);
        }

        /* Set flags */
        rockchip_pcie_ep_set_bar_flag(rk_pcie, 0, PCIM_BAR_MEM_TYPE_32);
        rockchip_pcie_ep_set_bar_flag(rk_pcie, 1, PCIM_BAR_MEM_TYPE_32);
        rockchip_pcie_ep_set_bar_flag(rk_pcie, 2, PCIM_BAR_MEM_PREFETCH | PCIM_BAR_MEM_TYPE_64);
        rockchip_pcie_ep_set_bar_flag(rk_pcie, 3, PCIM_BAR_MEM_PREFETCH | PCIM_BAR_MEM_TYPE_64);
    }

    /* Device id and class id needed for request bar address */
    dw_pcie_writew_dbi(pci, PCIR_DEVICE, 0x356a);
    dw_pcie_writew_dbi(pci, PCIR_SUBCLASS, 0x0580);

    /* Set shadow BAR0 */
    if (rk_pcie->soc_data->type == SOC_TYPE_RK1808)
    {
        dw_pcie_writel_dbi(pci, PCIE_SB_BAR0_MASK_REG, rk_pcie->mem_size - 1);
    }
}

static rt_err_t rockchip_pcie_add_endpoint(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;
    struct dw_pcie *pci = &rk_pcie->pci;
    struct rt_ofw_node *np = rk_pcie->pci.dev->ofw_node, *mem_np;

    if (!(mem_np = rt_ofw_parse_phandle(np, "memory-region", 0)))
    {
        LOG_E("%s: Missing '%s'", rt_ofw_node_full_name(np), "memory-region");
        return -RT_EINVAL;
    }

    if ((err = rt_ofw_get_address(mem_np, 0, &rk_pcie->mem_start, &rk_pcie->mem_size)))
    {
        LOG_E("%s: Missing '%s'", rt_ofw_node_full_name(mem_np), "reg");
        return -RT_EINVAL;
    }

    pci->atu_base = pci->dbi_base + DEFAULT_DBI_ATU_OFFSET;
    pci->user_speed = PCIE_DIRECT_SPEED_CHANGE;
    pci->endpoint.ops = &rockchip_pcie_ep_ops;

    rockchip_pcie_ep_setup_top(rk_pcie);

    if ((err = dw_pcie_ep_init(&pci->endpoint)))
    {
        LOG_E("Init EP error = %s", rt_strerror(err));
        return err;
    }

    rockchip_pcie_ep_setup_bottom(rk_pcie);

    if ((err = rockchip_pcie_ep_atu_init(rk_pcie)))
    {
        LOG_E("Init EP ATU error = %s", rt_strerror(err));
        return err;
    }

    if ((err = rockchip_pcie_establish_link_raw(rk_pcie)))
    {
        LOG_E("Establish pcie link error = %s", rt_strerror(err));
        return err;
    }

    if (!rockchip_pcie_udma_enabled(rk_pcie))
    {
        goto _end;
    }

    /* Init uDMA here */

_end:
    return RT_EOK;
}

#ifdef RT_USING_PM
static int rockchip_dw_pcie_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    rt_err_t err;
    rt_uint32_t status;
    struct rockchip_pcie *rk_pcie = device->user_data;
    struct dw_pcie *pci = &rk_pcie->pci;

    /*
     * This is as per PCI Express Base r5.0 r1.0 May 22-2019,
     * 5.2 Link State Power Management (Page #440).
     *
     * L2/L3 Ready entry negotiations happen while in the L0 state.
     * L2/L3 Ready are entered only after the negotiation completes.
     *
     * The following example sequence illustrates the multi-step Link state
     * transition process leading up to entering a system sleep state:
     * 1. System software directs all Functions of
     *    a Downstream component to D3Hot.
     * 2. The Downstream component then initiates the transition of the
     *    Link to L1 as required.
     * 3. System software then causes the Root Complex to broadcast the
     *    PME_TURN_OFF Message in preparation for removing the main power source.
     * 4. This Message causes the subject Link to transition back to L0
     *    in order to send it and to enable the Downstream component to
     *    respond with PME_TO_Ack.
     * 5. After sending the PME_TO_Ack, the Downstream component initiates the
     *    L2/L3 Ready transition protocol.
     */

    /* 1. All sub-devices are in D3hot by PCIe stack */
    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);

    rockchip_pcie_link_status_clear(rk_pcie);

    /*
     * Wlan devices will be shutdown from function driver now, so doing L2 here
     * must fail. Skip L2 routine.
     */
    if (rk_pcie->skip_scan_in_resume)
    {
        /* Check WiFi power state here. If down, goto the label "_no_l2" */
    }

    /* 2. Broadcast PME_Turn_Off Message */
    rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_MSG_GEN, PME_TURN_OFF);
    err = readl_poll_timeout(rk_pcie->apb_base + PCIE_CLIENT_MSG_GEN,
            status, !(status & RT_BIT(4)), 20, RK_PCIE_L2_TMOUT_US);
    if (err)
    {
        LOG_E("Failed to send PME_TURN_OFF");
        goto _no_l2;
    }

    /* 3. Wait for PME_TO_Ack */
    err = readl_poll_timeout(rk_pcie->apb_base + PCIE_CLIENT_INTR_STATUS_MSG_RX,
            status, status & RT_BIT(9), 20, RK_PCIE_L2_TMOUT_US);
    if (err)
    {
        LOG_E("Failed to receive PME_TO_ACK");
        goto _no_l2;
    }

    /* 4. Clear PME_TO_Ack and Wait for ready to enter L23 message */
    rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_INTR_STATUS_MSG_RX, PME_TO_ACK);
    err = readl_poll_timeout(rk_pcie->apb_base + PCIE_CLIENT_POWER,
            status, status & READY_ENTER_L23, 20, RK_PCIE_L2_TMOUT_US);
    if (err)
    {
        LOG_E("Failed to ready to enter L23");
        goto _no_l2;
    }

    /* 5. Check we are in L2 */
    err = readl_poll_timeout(rk_pcie->apb_base + PCIE_CLIENT_LTSSM_STATUS,
            status, ((status & S_MAX) == S_L2_IDLE), 20, RK_PCIE_L2_TMOUT_US);
    if (err)
    {
        LOG_E("Link isn't in L2 idle");
    }

_no_l2:
    rockchip_pcie_disable_ltssm(rk_pcie);

    /* make sure assert phy success */
    rt_hw_us_delay(250);

    rt_phye_power_off(rk_pcie->phy);
    rt_phye_exit(rk_pcie->phy);

    rk_pcie->intx = rockchip_pcie_readl_apb(rk_pcie, PCIE_CLIENT_INTR_MASK_LEGACY);

    rt_clk_array_disable_unprepare(rk_pcie->clk_arr);

    rk_pcie->in_suspend = RT_TRUE;

    rt_pin_write(rk_pcie->rst_pin, !rk_pcie->rst_active_val);

    return rockchip_pcie_disable_power(rk_pcie);
}

static void rockchip_dw_pcie_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    rt_err_t err;
    rt_bool_t std_rc;
    struct rockchip_pcie *rk_pcie = device->user_data;
    struct dw_pcie *pci = &rk_pcie->pci;

    std_rc = rk_pcie->soc_data->mode == DW_PCIE_RC_TYPE;

    rt_reset_control_assert(rk_pcie->rstc);
    rt_hw_us_delay(10);
    rt_reset_control_deassert(rk_pcie->rstc);

    if ((err = rockchip_pcie_enable_power(rk_pcie)))
    {
        LOG_E("Enable PCIe power error = %s", rt_strerror(err));
        return;
    }

    if ((err = rt_clk_array_prepare_enable(rk_pcie->clk_arr)))
    {
        LOG_E("Prepare enable PCIe clks error = %s", rt_strerror(err));
        return;
    }

    if ((err = rt_phye_set_mode(rk_pcie->phy, rk_pcie->phy_mode, rk_pcie->phy_submode)))
    {
        LOG_E("Set PHY to mode %s error = %s",
                (rk_pcie->phy_submode == RT_PHYE_MODE_PCIE_RC) ? "RC" : "EP",
                rt_strerror(err));
        return;
    }

    if ((err = rt_phye_init(rk_pcie->phy)))
    {
        LOG_E("Init PHY error = %s", rt_strerror(err));
        return;
    }

    rt_phye_power_on(rk_pcie->phy);

    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);

    if (rk_pcie->soc_data->type == SOC_TYPE_RK1808)
    {
        /* Release link reset grant */
        if (rockchip_pcie_reset_grant_ctrl(rk_pcie, RT_TRUE))
        {
            return;
        }
    }
    else
    {
        rockchip_pcie_fast_link_setup(rk_pcie);
    }

    /* Set PCIe mode */
    rockchip_pcie_set_mode(rk_pcie);

    if (std_rc)
    {
        dw_pcie_setup_rc(&pci->port);
    }

    rockchip_pcie_writel_apb(rk_pcie, PCIE_CLIENT_INTR_MASK_LEGACY,
            rk_pcie->intx | 0xffff0000);

    if ((err = rockchip_pcie_establish_link_raw(rk_pcie)))
    {
        LOG_E("Establish PCIe link error = %s", rt_strerror(err));
        goto _err;
    }

    if (std_rc)
    {
        goto _std_rc_done;
    }

    if ((err = rockchip_pcie_ep_atu_init(rk_pcie)))
    {
        LOG_E("Init EP device error = %s", rt_strerror(err));
        goto _err;
    }

    rockchip_pcie_ep_setup_top(rk_pcie);
    dw_pcie_setup(pci);
    rockchip_pcie_ep_setup_bottom(rk_pcie);

    rk_pcie->in_suspend = RT_FALSE;

_std_rc_done:
    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);
    /* hold link reset grant after link-up */
    if (rk_pcie->soc_data->type == SOC_TYPE_RK1808)
    {
        if ((err = rockchip_pcie_reset_grant_ctrl(rk_pcie, RT_FALSE)))
        {
            goto _err;
        }
    }

    if (pci->port.msi_irq > 0)
    {
        dw_pcie_msi_init(&pci->port);
    }

    return;

_err:
    rockchip_pcie_disable_power(rk_pcie);
}

static const struct rt_device_pm_ops rockchip_dw_pcie_pm_ops =
{
    .suspend = rockchip_dw_pcie_pm_suspend,
    .resume = rockchip_dw_pcie_pm_resume,
};
#endif /* RT_USING_PM */

static rt_err_t rockchip_pcie_phy_init(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;
    struct rt_device *dev = rk_pcie->pci.dev;

    rk_pcie->phy = rt_phye_get_by_name(dev, "pcie-phy");
    if (rt_is_err(rk_pcie->phy))
    {
        LOG_E("Missing PHY");
        return rt_ptr_err(rk_pcie->phy);
    }

    switch (rk_pcie->soc_data->mode)
    {
    case DW_PCIE_RC_TYPE:
        rk_pcie->phy_mode = RT_PHYE_MODE_PCIE;
        rk_pcie->phy_submode = RT_PHYE_MODE_PCIE_RC;
        break;

    case DW_PCIE_EP_TYPE:
        rk_pcie->phy_mode = RT_PHYE_MODE_PCIE;
        rk_pcie->phy_submode = RT_PHYE_MODE_PCIE_EP;
        break;

    default:
        break;
    }

    if ((err = rt_phye_set_mode(rk_pcie->phy, rk_pcie->phy_mode, rk_pcie->phy_submode)))
    {
        LOG_E("Fail to set PHY to mode %s",
                (rk_pcie->phy_submode == RT_PHYE_MODE_PCIE_RC) ? "RC" : "EP");

        rk_pcie->phy = RT_NULL;
        return err;
    }

    if (rk_pcie->bifurcation)
    {
        rt_phye_set_mode(rk_pcie->phy, rk_pcie->phy_mode, RT_PHYE_MODE_PCIE_BIFURCATION);
    }

    if ((err = rt_phye_init(rk_pcie->phy)))
    {
        LOG_E("Init PHY fail");

        rk_pcie->phy = RT_NULL;
        return err;
    }

    rt_phye_power_on(rk_pcie->phy);

    return RT_EOK;
}

static rt_err_t rockchip_pcie_fixup_rk1808(struct rockchip_pcie *rk_pcie)
{
    rt_err_t err;
    struct rt_ofw_node *np = rk_pcie->pci.dev->ofw_node;

    rk_pcie->usb_pcie_grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,usbpciegrf");
    if (!rk_pcie->usb_pcie_grf)
    {
        LOG_E("Failed to find %s regmap", "usb_pcie_grf");
        return -RT_EIO;
    }

    rk_pcie->pmu_grf = rt_syscon_find_by_ofw_phandle(np, "rockchip,pmugrf");
    if (!rk_pcie->pmu_grf)
    {
        LOG_E("Failed to find %s regmap", "pmugrf");
        return -RT_EIO;
    }

    /* Workaround for pcie, switch to PCIe_PRSTNm0 */
    if ((err = rt_syscon_write(rk_pcie->pmu_grf, 0x100, 0x01000100)))
    {
        return err;
    }

    if ((err = rt_syscon_write(rk_pcie->pmu_grf, 0x0, 0x0c000000)))
    {
        return err;
    }

    /* Release link reset grant */
    return rockchip_pcie_reset_grant_ctrl(rk_pcie, RT_TRUE);
}

static void rockchip_pcie_free(struct rockchip_pcie *rk_pcie)
{
    if (rk_pcie->pci.dbi_base)
    {
        rt_iounmap(rk_pcie->pci.dbi_base);
    }

    if (rk_pcie->apb_base)
    {
        rt_iounmap(rk_pcie->apb_base);
    }

    if (!rt_is_err_or_null(rk_pcie->clk_arr))
    {
        rt_clk_array_disable_unprepare(rk_pcie->clk_arr);
        rt_clk_array_put(rk_pcie->clk_arr);
    }

    if (!rt_is_err_or_null(rk_pcie->rstc))
    {
        rt_reset_control_assert(rk_pcie->rstc);
        rt_reset_control_put(rk_pcie->rstc);
    }

    if (!rt_is_err_or_null(rk_pcie->phy))
    {
        rt_phye_power_off(rk_pcie->phy);
        rt_phye_exit(rk_pcie->phy);
        rt_phye_put(rk_pcie->phy);
    }

    if (!rt_is_err_or_null(rk_pcie->vpcie3v3))
    {
        rt_regulator_disable(rk_pcie->vpcie3v3);
    }

    rt_free(rk_pcie);
}

static void rockchip_pcie_free_irq(struct rockchip_pcie *rk_pcie)
{
    if (rk_pcie->intx_np)
    {
        rt_ofw_data(rk_pcie->intx_np) = RT_NULL;

        rt_pic_cancel_irq(&rk_pcie->intx_pic);

        rt_hw_interrupt_mask(rk_pcie->intx_irq);
        rt_pic_detach_irq(rk_pcie->intx_irq, rk_pcie);
    }

    rt_hw_interrupt_mask(rk_pcie->pci.port.sys_irq);
    rt_pic_detach_irq(rk_pcie->pci.port.sys_irq, rk_pcie);
}

static rt_err_t rockchip_pcie_dw_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t val;
    rt_uint8_t pmode;
    struct dw_pcie *pci;
    struct dw_pcie_port *port;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node, *intx_np;
    struct rockchip_pcie *rk_pcie = rt_calloc(1, sizeof(*rk_pcie));

    if (!rk_pcie)
    {
        return -RT_EINVAL;
    }

    rk_pcie->soc_data = pdev->id->data;
    rk_pcie->intx_irq = -RT_EEMPTY;

    pci = &rk_pcie->pci;
    pci->dev = dev;
    pci->ops = &dw_pcie_ops;
    pci->priv = rk_pcie;

    port = &pci->port;
    port->irq_count = rk_pcie->soc_data->msi_vector_num;

    rk_pcie->bifurcation = rt_dm_dev_prop_read_bool(dev, "rockchip,bifurcation");

    pci->dbi_base = rt_dm_dev_iomap_by_name(dev, "pcie-dbi");
    if (!pci->dbi_base)
    {
        err = -RT_EIO;
        goto _fail;
    }
    pci->dbi_base2 = pci->dbi_base + PCIE_TYPE0_HDR_DBI2_OFFSET;

    rk_pcie->apb_base = rt_dm_dev_iomap_by_name(dev, "pcie-apb");
    if (!rk_pcie->apb_base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    rk_pcie->rst_pin = rt_pin_get_named_pin(dev, "reset", 0,
            RT_NULL, &rk_pcie->rst_active_val);
    if (rk_pcie->rst_pin < 0 && rk_pcie->rst_pin != PIN_NONE)
    {
        err = (rt_err_t)rk_pcie->rst_pin;
        goto _fail;
    }

    rk_pcie->prsnt_pin = rt_pin_get_named_pin(dev, "prsnt", 0,
            &pmode, &rk_pcie->prsnt_active_val);
    if (rk_pcie->prsnt_pin >= 0)
    {
        rt_pin_mode(rk_pcie->prsnt_pin, pmode);

        if (rt_pin_read(rk_pcie->prsnt_pin) != rk_pcie->prsnt_active_val)
        {
            /* No device */
            err = -RT_EINVAL;
            goto _fail;
        }
    }
    else if (rk_pcie->prsnt_pin != PIN_NONE)
    {
        LOG_I("Invalid prsnt-gpios");
    }

    rt_pin_write(rk_pcie->rst_pin, !rk_pcie->rst_active_val);
    rt_pin_mode(rk_pcie->rst_pin, PIN_MODE_OUTPUT);

    if (rt_dm_dev_prop_read_u32(dev, "rockchip,perst-inactive-ms",
            &rk_pcie->perst_inactive_ms))
    {
        rk_pcie->perst_inactive_ms = 200;
    }

    rk_pcie->supports_clkreq = rt_dm_dev_prop_read_bool(dev, "supports-clkreq");

    rk_pcie->vpcie3v3 = rt_regulator_get(dev, "vpcie3v3");

    if (rt_is_err(rk_pcie->vpcie3v3))
    {
        err = rt_ptr_err(rk_pcie->vpcie3v3);
        goto _fail;
    }

    if ((err = rockchip_pcie_enable_power(rk_pcie)))
    {
        goto _fail;
    }

    if ((err = rockchip_pcie_phy_init(rk_pcie)))
    {
        goto _fail;
    }

    rk_pcie->rstc = rt_reset_control_get_array(dev);

    if (rt_is_err(rk_pcie->rstc))
    {
        err = rt_ptr_err(rk_pcie->rstc);
        goto _fail;
    }
    rt_reset_control_deassert(rk_pcie->rstc);

    rk_pcie->clk_arr = rt_clk_get_array(dev);

    if (rt_is_err(rk_pcie->clk_arr))
    {
        err = rt_ptr_err(rk_pcie->clk_arr);
        goto _fail;
    }

    if ((err = rt_clk_array_prepare_enable(rk_pcie->clk_arr)))
    {
        goto _fail;
    }

    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);

    if (rk_pcie->soc_data->type == SOC_TYPE_RK1808)
    {
        if ((err = rockchip_pcie_fixup_rk1808(rk_pcie)))
        {
            goto _fail;
        }
    }
    else
    {
        rockchip_pcie_fast_link_setup(rk_pcie);
    }

    rockchip_pcie_set_mode(rk_pcie);

    /* Force into loopback master mode */
    if (rt_dm_dev_prop_read_bool(dev, "rockchip,lpbk-master"))
    {
        val = dw_pcie_readl_dbi(pci, PCIE_PORT_LINK_CONTROL);
        val |= PORT_LINK_LPBK_ENABLE;
        dw_pcie_writel_dbi(pci, PCIE_PORT_LINK_CONTROL, val);
        rk_pcie->is_signal_test = RT_TRUE;
    }

    /*
     * Force into compliance mode
     * comp_prst is a two dimensional array of which the first element
     * stands for speed mode, and the second one is preset value encoding:
     *  [0] 0->SMA tool control the signal switch,
     *      1/2/3 is for manual Gen setting
     *  [1] transmitter setting for manual Gen setting,
     *      valid only if [0] isn't zero.
     */
    if (rt_dm_dev_prop_read_u32_array_index(dev, "rockchip,compliance-mode",
            0, 2, rk_pcie->comp_prst) > 0)
    {
        if (!rk_pcie->comp_prst[0])
        {
            LOG_I("Auto compliance mode for SMA tool");
        }
        else
        {
            LOG_I("Compliance mode for soldered board Gen%d, P%d",
                    rk_pcie->comp_prst[0], rk_pcie->comp_prst[1]);

            val = dw_pcie_readl_dbi(pci, PCIE_CAP_LINK_CONTROL2_LINK_STATUS);
            val |= RT_BIT(4) | rk_pcie->comp_prst[0] | (rk_pcie->comp_prst[1] << 12);
            dw_pcie_writel_dbi(pci, PCIE_CAP_LINK_CONTROL2_LINK_STATUS, val);
        }
        rk_pcie->is_signal_test = RT_TRUE;
    }

    /* Skip waiting for training to pass in system PM routine */
    if (rt_dm_dev_prop_read_bool(dev, "rockchip,skip-scan-in-resume"))
    {
        rk_pcie->skip_scan_in_resume = RT_TRUE;
    }

    port->sys_irq = rt_dm_dev_get_irq_by_name(dev, "sys");

    if (port->sys_irq < 0)
    {
        err = port->sys_irq;
        goto _fail;
    }

    rk_pcie->intx_irq = rt_dm_dev_get_irq_by_name(dev, "legacy");

    if (rk_pcie->intx_irq >= 0)
    {
        /* Legacy (INTx) init */
        if (!(intx_np = rt_ofw_get_child_by_tag(np, "legacy-interrupt-controller")))
        {
            LOG_E("INTx ofw node not found");

            err = -RT_EIO;
            goto _fail;
        }

        rk_pcie->intx_np = intx_np;
        rk_pcie->intx_pic.priv_data = rk_pcie;
        rk_pcie->intx_pic.ops = &rockchip_intx_ops;
        rt_pic_linear_irq(&rk_pcie->intx_pic, RT_PCI_INTX_PIN_MAX);
        rt_pic_user_extends(&rk_pcie->intx_pic);
        rt_ofw_data(intx_np) = &rk_pcie->intx_pic;
        rt_ofw_node_put(intx_np);

        rt_hw_interrupt_install(rk_pcie->intx_irq, rockchip_pcie_legacy_isr, rk_pcie, "rk-pcie-legacy");
        rt_hw_interrupt_umask(rk_pcie->intx_irq);
    }
    else
    {
        LOG_D("Missing legacy IRQ");
    }

    rt_hw_interrupt_install(port->sys_irq, rockchip_pcie_sys_isr, rk_pcie, "rk-pcie-sys");
    rt_hw_interrupt_umask(port->sys_irq);

    rt_work_init(&rk_pcie->hot_rst_work, rockchip_pcie_hot_rst_work, rk_pcie);

    switch (rk_pcie->soc_data->mode)
    {
    case DW_PCIE_RC_TYPE:
        err = rockchip_pcie_add_port(rk_pcie);
        break;

    case DW_PCIE_EP_TYPE:
        err = rockchip_pcie_add_endpoint(rk_pcie);
        break;

    default:
        /* It's impossible */
        RT_ASSERT(0);
        break;
    }

    if (rk_pcie->is_signal_test)
    {
        goto _end;
    }

    if (err)
    {
        goto _free_irq;
    }

    if (rk_pcie->soc_data->type == SOC_TYPE_RK1808)
    {
        /* Hold link reset grant after link-up */
        if ((err = rockchip_pcie_reset_grant_ctrl(rk_pcie, RT_FALSE)))
        {
            goto _free_irq;
        }
    }

_end:
    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);

#ifdef RT_USING_PM
    rt_pm_device_register(dev, &rockchip_dw_pcie_pm_ops);
#endif

    dev->user_data = rk_pcie;

    return RT_EOK;

_free_irq:
    rockchip_pcie_free_irq(rk_pcie);

_fail:
    rockchip_pcie_free(rk_pcie);

    return err;
}

static rt_err_t rockchip_pcie_dw_remove(struct rt_platform_device *pdev)
{
    struct rockchip_pcie *rk_pcie = pdev->parent.user_data;

#ifdef RT_USING_PM
    rt_pm_device_unregister(&pdev->parent);
#endif

    if (rk_pcie->pci.port.bridge)
    {
        rt_pci_host_bridge_remove(rk_pcie->pci.port.bridge);
    }
    dw_pcie_host_free(&rk_pcie->pci.port);

    rockchip_pcie_free_irq(rk_pcie);

    rockchip_pcie_free(rk_pcie);

    return RT_EOK;
}

static const struct rockchip_pcie_soc_data rk_pcie_rc_soc_data =
{
    .mode = DW_PCIE_RC_TYPE,
};

static const struct rockchip_pcie_soc_data rk_pcie_ep_soc_data =
{
    .mode = DW_PCIE_EP_TYPE,
};

static const struct rockchip_pcie_soc_data rk1808_pcie_rc_soc_data =
{
    .type = SOC_TYPE_RK1808,
    .mode = DW_PCIE_RC_TYPE,
};

static const struct rockchip_pcie_soc_data rk1808_pcie_ep_soc_data =
{
    .type = SOC_TYPE_RK1808,
    .mode = DW_PCIE_EP_TYPE,
};

static const struct rockchip_pcie_soc_data rk3528_pcie_rc_soc_data =
{
    .mode = DW_PCIE_RC_TYPE,
    .msi_vector_num = 8,
};

static const struct rt_ofw_node_id rockchip_pcie_dw_ofw_ids[] =
{
    { .compatible = "rockchip,rk1808-pcie",     .data = &rk1808_pcie_rc_soc_data, },
    { .compatible = "rockchip,rk1808-pcie-ep",  .data = &rk1808_pcie_ep_soc_data, },
    { .compatible = "rockchip,rk3528-pcie",     .data = &rk3528_pcie_rc_soc_data, },
    { .compatible = "rockchip,rk3562-pcie",     .data = &rk3528_pcie_rc_soc_data, },
    { .compatible = "rockchip,rk3568-pcie",     .data = &rk_pcie_rc_soc_data, },
    { .compatible = "rockchip,rk3568-pcie-ep",  .data = &rk_pcie_ep_soc_data, },
    { .compatible = "rockchip,rk3576-pcie",     .data = &rk3528_pcie_rc_soc_data, },
    { .compatible = "rockchip,rk3588-pcie",     .data = &rk_pcie_rc_soc_data, },
    { .compatible = "rockchip,rk3588-pcie-ep",  .data = &rk_pcie_ep_soc_data, },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_pcie_dw_driver =
{
    .name = "dw-pcie-rockchip",
    .ids = rockchip_pcie_dw_ofw_ids,

    .probe = rockchip_pcie_dw_probe,
    .remove = rockchip_pcie_dw_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_pcie_dw_driver);
