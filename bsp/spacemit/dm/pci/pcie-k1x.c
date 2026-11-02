/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#define DBG_TAG "pci.dw.k1x"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "pcie-dw.h"

#define PCIE_VENDORID_MASK              0xffff
#define PCIE_DEVICEID_SHIFT             16
#define K1X_PCIE_VENDOR_ID              0x201f
#define k1X_PCIE_DEVICE_ID              0x0001

/* PCIe controller wrapper k1x configuration registers */

#define K1X_PHY_AHB_IRQ_EN              0x0000
#define IRQ_EN                          RT_BIT(0)
#define PME_TURN_OFF                    RT_BIT(5)

#define K1X_PHY_AHB_IRQSTATUS_INTX      0x0008
#define INTA                            RT_BIT(6)
#define INTB                            RT_BIT(7)
#define INTC                            RT_BIT(8)
#define INTD                            RT_BIT(9)
#define LEG_EP_INTERRUPTS               (INTA | INTB | INTC | INTD)
#define INTX_MASK                       RT_GENMASK(9, 6)
#define INTX_SHIFT                      6

#define K1X_PHY_AHB_IRQENABLE_SET_INTX  0x000c

#define K1X_PHY_AHB_IRQSTATUS_MSI       0x0010
#define MSI                             RT_BIT(11)
#define PCIE_REMOTE_INTERRUPT           RT_BIT(31)
/* DMA write channel 0~7 irq*/
#define EDMA_INT0                       RT_BIT(0)
#define EDMA_INT1                       RT_BIT(1)
#define EDMA_INT2                       RT_BIT(2)
#define EDMA_INT3                       RT_BIT(3)
#define EDMA_INT4                       RT_BIT(4)
#define EDMA_INT5                       RT_BIT(5)
#define EDMA_INT6                       RT_BIT(6)
#define EDMA_INT7                       RT_BIT(7)
/* DMA read channel 0~7 irq*/
#define EDMA_INT8                       RT_BIT(8)
#define EDMA_INT9                       RT_BIT(9)
#define EDMA_INT10                      RT_BIT(10)
#define EDMA_INT11                      RT_BIT(11)
#define EDMA_INT12                      RT_BIT(12)
#define EDMA_INT13                      RT_BIT(13)
#define EDMA_INT14                      RT_BIT(14)
#define EDMA_INT15                      RT_BIT(15)
#define DMA_READ_INT                    RT_GENMASK(11, 8)

#define K1X_PHY_AHB_IRQENABLE_SET_MSI   0x0014

#define PCIECTRL_K1X_CONF_DEVICE_CMD    0x0000
#define LTSSM_EN                        RT_BIT(6)
/* Perst input value in ep mode */
#define PCIE_PERST_IN                   RT_BIT(7)
#define PCIE_AUX_PWR_DET                RT_BIT(9)
/* Perst GPIO en in RC mode 1: perst# low, 0: perst# high */
#define PCIE_RC_PERST                   RT_BIT(12)
/* Wake# GPIO in EP mode 1: Wake# low, 0: Wake# high */
#define PCIE_EP_WAKE                    RT_BIT(13)
#define APP_HOLD_PHY_RST                RT_BIT(30)
/* BIT31 0: EP, 1: RC*/
#define DEVICE_TYPE_RC                  RT_BIT(31)

#define PCIE_CTRL_LOGIC                 0x0004
#define PCIE_IGNORE_PERSTN              RT_BIT(2)

#define K1X_PHY_AHB_LINK_STS            0x0004
#define SMLH_LINK_UP                    RT_BIT(1)
#define RDLH_LINK_UP                    RT_BIT(12)
#define   PCIE_CLIENT_DEBUG_LTSSM_MASK  RT_GENMASK(11, 6)
#define   PCIE_CLIENT_DEBUG_LTSSM_L1    (RT_BIT(10) | RT_BIT(8))
#define   PCIE_CLIENT_DEBUG_LTSSM_L2    (RT_BIT(10) | RT_BIT(8) | RT_BIT(6))

#define ADDR_INTR_STATUS1               0x0018
#define ADDR_INTR_ENABLE1               0x001c
#define MSI_INT                         RT_BIT(0)
#define MSIX_INT                        RT_GENMASK(8, 1)

#define ADDR_MSI_RECV_CTRL              0x0080
#define MSI_MON_EN                      RT_BIT(0)
#define MSIX_MON_EN                     RT_GENMASK(8, 1)
#define MSIX_AFIFO_FULL                 RT_BIT(30)
#define MSIX_AFIFO_EMPTY                RT_BIT(29)
#define ADDR_MSI_RECV_ADDR0             0x0084
#define ADDR_MSIX_MON_MASK              0x0088
#define ADDR_MSIX_MON_BASE0             0x008c

#define ADDR_MON_FIFO_DATA0             0x00b0
#define ADDR_MON_FIFO_DATA1             0x00b4
#define FIFO_EMPTY                      0xffffffff
#define FIFO_LEN                        32
#define INT_VEC_MASK                    RT_GENMASK(7, 0)

#define EXP_CAP_ID_OFFSET               0x70

#define PCIECTRL_K1X_CONF_INTX_ASSERT   0x0124
#define PCIECTRL_K1X_CONF_INTX_DEASSERT 0x0128

/*RC write config  0xD28 offset register which equal with ELBI offset 0x028 addr*/
#define PCIE_ELBI_EP_DMA_IRQ_STATUS     0x028
#define PC_TO_EP_INT                    0x3fffffff

#define PCIE_ELBI_EP_DMA_IRQ_MASK       0x02c
#define PC_TO_EP_INT_MASK               0x3fffffff

#define PCIE_ELBI_EP_MSI_REASON         0x018

#define PCIE_LINK_IS_L2(x)              (((x) & PCIE_CLIENT_DEBUG_LTSSM_MASK) == PCIE_CLIENT_DEBUG_LTSSM_L2)

struct k1x_pcie_soc_data
{
    enum dw_pcie_device_mode mode;
};

struct k1x_pcie
{
    struct dw_pcie pci;

    int irq;
    void *base;
    void *elbi_base;
    void *dma_base;
    void *phy_ahb;
    void *phy_addr;
    void *conf0_addr;
    void *phy0_addr;

    enum dw_pcie_device_mode mode;

    struct rt_clk *clk_master;
    struct rt_reset_control *rstc;

    rt_base_t pwr_on_pin;
    rt_uint8_t pwr_on_active_val;

    rt_uint32_t pcie_rcal;
    rt_uint32_t port_id;
    rt_uint32_t num_lanes;
    rt_uint32_t link_gen;

    fdt32_t msi_phandle_cell;

    void *msix_data;
    rt_ubase_t msix_data_phy;

    struct rt_ofw_node *pic_np;
    struct rt_pic pic;
};

#define to_k1x_pcie(dw_pcie) rt_container_of(dw_pcie, struct k1x_pcie, pci)

static rt_bool_t porta_init_done = RT_FALSE;

rt_inline rt_uint32_t k1x_pcie_readl_dma(struct k1x_pcie *k1x, int offset)
{
    return HWREG32(k1x->dma_base + offset);
}

rt_inline void k1x_pcie_writel_dma(struct k1x_pcie *k1x, int offset, rt_uint32_t val)
{
    HWREG32(k1x->dma_base + offset) = val;
}

rt_inline rt_uint32_t k1x_pcie_readw_dma(struct k1x_pcie *k1x, int offset)
{
    return (rt_uint32_t)HWREG16(k1x->dma_base + offset);
}

rt_inline void k1x_pcie_writew_dma(struct k1x_pcie *k1x, int offset, rt_uint32_t val)
{
    HWREG16(k1x->dma_base + offset) = (rt_uint16_t)val;
}

rt_inline rt_uint32_t k1x_pcie_readl(struct k1x_pcie *k1x, int offset)
{
    return HWREG32(k1x->base + offset);
}

rt_inline void k1x_pcie_writel(struct k1x_pcie *k1x, int offset, rt_uint32_t val)
{
    HWREG32(k1x->base + offset) = val;
}

rt_inline rt_uint32_t k1x_pcie_readl_elbi(struct k1x_pcie *k1x, int offset)
{
    return HWREG32(k1x->elbi_base + offset);
}

rt_inline void k1x_pcie_writel_elbi(struct k1x_pcie *k1x, int offset, rt_uint32_t val)
{
    HWREG32(k1x->elbi_base + offset) = val;
}

rt_inline rt_uint32_t k1x_pcie_phy_ahb_readl(struct k1x_pcie *k1x, int offset)
{
    return HWREG32(k1x->phy_ahb + offset);
}

rt_inline void k1x_pcie_phy_ahb_writel(struct k1x_pcie *k1x, int offset, rt_uint32_t val)
{
    HWREG32(k1x->phy_ahb + offset) = val;
}

rt_inline rt_uint32_t k1x_pcie_phy_reg_readl(struct k1x_pcie *k1x, int offset)
{
    return HWREG32(k1x->phy_addr + offset);
}

rt_inline void k1x_pcie_phy_reg_writel(struct k1x_pcie *k1x, int offset, rt_uint32_t val)
{
    HWREG32(k1x->phy_addr + offset) = val;
}

rt_inline rt_uint32_t k1x_pcie_conf0_reg_readl(struct k1x_pcie *k1x, int offset)
{
    return HWREG32(k1x->conf0_addr + offset);
}

rt_inline void k1x_pcie_conf0_reg_writel(struct k1x_pcie *k1x, int offset, rt_uint32_t val)
{
    HWREG32(k1x->conf0_addr + offset) = val;
}

rt_inline rt_uint32_t k1x_pcie_phy0_reg_readl(struct k1x_pcie *k1x, int offset)
{
    return HWREG32(k1x->phy0_addr + offset);
}

rt_inline void k1x_pcie_phy0_reg_writel(struct k1x_pcie *k1x, int offset, rt_uint32_t val)
{
    HWREG32(k1x->phy0_addr + offset) = val;
}

static rt_err_t k1x_pcie_ep_init(struct dw_pcie_ep *ep)
{
    rt_uint32_t reg;
    struct dw_pcie *pci = to_dw_pcie_from_endpoint(ep);
    struct k1x_pcie *k1x = to_k1x_pcie(pci);

    /* Enable wrapper interrupts */
    reg = k1x_pcie_phy_ahb_readl(k1x, K1X_PHY_AHB_IRQENABLE_SET_MSI);
    reg |= PCIE_REMOTE_INTERRUPT | DMA_READ_INT;
    k1x_pcie_phy_ahb_writel(k1x, K1X_PHY_AHB_IRQENABLE_SET_MSI, reg);

    reg = k1x_pcie_phy_ahb_readl(k1x, K1X_PHY_AHB_IRQ_EN);
    reg |= IRQ_EN;
    k1x_pcie_phy_ahb_writel(k1x, K1X_PHY_AHB_IRQ_EN, reg);

    reg = k1x_pcie_readl_elbi(k1x, PCIE_ELBI_EP_DMA_IRQ_MASK);
    reg |= PC_TO_EP_INT_MASK;
    k1x_pcie_writel_elbi(k1x, PCIE_ELBI_EP_DMA_IRQ_MASK, reg);

    return RT_EOK;
}

static rt_err_t k1x_pcie_raise_irq(struct dw_pcie_ep *ep, rt_uint8_t func_no,
        enum rt_pci_ep_irq type, unsigned irq)
{
    switch (type)
    {
    case RT_PCI_EP_IRQ_LEGACY:
        LOG_E("Unsupported INTx");
        return -RT_EINVAL;

    case RT_PCI_EP_IRQ_MSI:
        dw_pcie_ep_raise_msi_irq(ep, func_no, irq);
        break;

    case RT_PCI_EP_IRQ_MSIX:
        dw_pcie_ep_raise_msix_irq(ep, func_no, irq);
        break;

    default:
        LOG_E("Unknown IRQ type = %d", type);
    }

    return RT_EOK;
}

static struct dw_pcie_ep_ops pcie_ep_ops =
{
    .ep_init = k1x_pcie_ep_init,
    .raise_irq = k1x_pcie_raise_irq,
};

static rt_err_t k1x_add_pcie_ep(struct k1x_pcie *k1x, struct rt_device *dev)
{
    rt_err_t err;
    struct dw_pcie *pci = &k1x->pci;
    struct dw_pcie_ep *ep = &pci->endpoint;

    ep->ops = &pcie_ep_ops;

    if (!(k1x->elbi_base = rt_dm_dev_iomap_by_name(dev, "elbi")))
    {
        return -RT_EIO;
    }

    if (!(k1x->dma_base = rt_dm_dev_iomap_by_name(dev, "dma")))
    {
        return -RT_EIO;
    }

    if ((err = dw_pcie_ep_init(ep)))
    {
        LOG_E("Failed to initialize endpoint");
        return err;
    }

    return RT_EOK;
}

static rt_err_t k1x_pcie_host_init(struct dw_pcie_port *port)
{
    rt_err_t err;
    rt_uint32_t reg;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);
    struct k1x_pcie *k1x = to_k1x_pcie(pci);

    rt_thread_mdelay(100);

    /* Set Perst# gpio high state */
    reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);
    reg &= ~PCIE_RC_PERST;
    k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, reg);

    /* Enable MSI interrupts */
    reg = k1x_pcie_phy_ahb_readl(k1x, K1X_PHY_AHB_IRQENABLE_SET_MSI);
    reg |= MSI;
    k1x_pcie_phy_ahb_writel(k1x, K1X_PHY_AHB_IRQENABLE_SET_MSI, reg);

    reg = k1x_pcie_phy_ahb_readl(k1x, K1X_PHY_AHB_IRQENABLE_SET_INTX);
    reg |= LEG_EP_INTERRUPTS;
    k1x_pcie_phy_ahb_writel(k1x, K1X_PHY_AHB_IRQENABLE_SET_INTX, reg);

    reg = k1x_pcie_phy_ahb_readl(k1x, K1X_PHY_AHB_IRQ_EN);
    reg |= IRQ_EN;
    k1x_pcie_phy_ahb_writel(k1x, K1X_PHY_AHB_IRQ_EN, reg);

    reg = k1x_pcie_phy_ahb_readl(k1x, ADDR_INTR_ENABLE1);
    reg |= (MSI_INT | MSIX_INT);
    k1x_pcie_phy_ahb_writel(k1x, ADDR_INTR_ENABLE1, reg);

    /* Configure the root complex before starting link training. */
    dw_pcie_setup_rc(port);

    if (!dw_pcie_link_up(pci) && pci->ops->start_link)
    {
        if ((err = pci->ops->start_link(pci)))
        {
            LOG_E("Failed to start PCIe%d link: %s", k1x->port_id,
                    rt_strerror(err));
            return err;
        }
    }

    /* Keep the host registered even when an endpoint trains later. */
    if ((err = dw_pcie_wait_for_link(pci)))
    {
        reg = k1x_pcie_phy_ahb_readl(k1x, K1X_PHY_AHB_LINK_STS);
        LOG_W("PCIe%d link down, status=0x%08x", k1x->port_id, reg);
    }
    else
    {
        reg = dw_pcie_readw_dbi(pci, EXP_CAP_ID_OFFSET + PCIER_LINK_STA);
        LOG_I("PCIe%d Link up, Gen%i", k1x->port_id,
                reg & PCIEM_LINK_STA_SPEED);
    }

    return RT_EOK;
}

static rt_err_t k1x_pcie_msi_host_init(struct dw_pcie_port *port)
{
    rt_uint32_t reg;
    rt_uint64_t msi_target;
    struct dw_pcie *pci = to_dw_pcie_from_port(port);
    struct k1x_pcie *k1x = to_k1x_pcie(pci);

    /* MSI Start */
    port->msi_data = rt_dma_alloc_coherent(pci->dev, sizeof(rt_uint64_t),
            &port->msi_data_phy);
    if (!port->msi_data)
    {
        goto _msix_init;
    }
    msi_target = (rt_uint64_t)port->msi_data_phy;

    /* Program the msi_data */
    dw_pcie_writel_dbi(pci, PCIE_MSI_ADDR_LO, rt_lower_32_bits(msi_target));
    dw_pcie_writel_dbi(pci, PCIE_MSI_ADDR_HI, rt_upper_32_bits(msi_target));

    reg = k1x_pcie_phy_ahb_readl(k1x, ADDR_MSI_RECV_CTRL);
    reg |= MSI_MON_EN;
    k1x_pcie_phy_ahb_writel(k1x, ADDR_MSI_RECV_CTRL, reg);
    k1x_pcie_phy_ahb_writel(k1x, ADDR_MSI_RECV_ADDR0, (rt_lower_32_bits(msi_target) >> 2));
    /* MSI End */

_msix_init:
    /* MSI-X Start */
    k1x->msix_data = rt_dma_alloc_coherent(pci->dev, sizeof(rt_uint64_t),
            &k1x->msix_data_phy);
    if (!k1x->msix_data)
    {
        goto _end;
    }
    msi_target = (rt_uint64_t)k1x->msix_data_phy;

    reg = k1x_pcie_phy_ahb_readl(k1x, ADDR_MSI_RECV_CTRL);
    reg |= MSIX_MON_EN;
    k1x_pcie_phy_ahb_writel(k1x, ADDR_MSI_RECV_CTRL, reg);
    k1x_pcie_phy_ahb_writel(k1x, ADDR_MSIX_MON_BASE0, (rt_lower_32_bits(msi_target) >> 2));
    /* MSI-X End */

_end:
    return RT_EOK;
}

static const struct dw_pcie_host_ops k1x_pcie_host_ops =
{
    .host_init = k1x_pcie_host_init,
    .msi_host_init = k1x_pcie_msi_host_init,
};

static rt_bool_t k1x_pcie_link_up(struct dw_pcie *pci)
{
    struct k1x_pcie *k1x = to_k1x_pcie(pci);
    rt_uint32_t reg = k1x_pcie_phy_ahb_readl(k1x, K1X_PHY_AHB_LINK_STS);

    return (reg & RDLH_LINK_UP) && (reg & SMLH_LINK_UP);
}

static rt_err_t k1x_pcie_establish_link(struct dw_pcie *pci)
{
    rt_uint32_t reg;
    struct k1x_pcie *k1x = to_k1x_pcie(pci);

    if (k1x->mode == DW_PCIE_EP_TYPE)
    {
        rt_uint32_t cnt = 0;
        do {
            reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);

            if ((reg & RT_BIT(7)) == RT_BIT(7))
            {
                break;
            }

            rt_hw_us_delay(10);
            cnt += 1;
        } while (cnt < 300000);
    }

    if (dw_pcie_link_up(pci))
    {
        LOG_E("Link is already up");
        return RT_EOK;
    }

    reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);
    reg |= LTSSM_EN;
    reg &= ~APP_HOLD_PHY_RST;
    k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, reg);

    LOG_D("LTSSM Enable");

    return RT_EOK;
}

static void k1x_pcie_stop_link(struct dw_pcie *pci)
{
    rt_uint32_t reg;
    struct k1x_pcie *k1x = to_k1x_pcie(pci);

    reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);
    reg &= ~LTSSM_EN;
    k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, reg);
}

static const struct dw_pcie_ops dw_pcie_ops =
{
    .link_up = k1x_pcie_link_up,
    .start_link = k1x_pcie_establish_link,
    .stop_link = k1x_pcie_stop_link,
};

static void k1x_pci_irq_mask(struct rt_pic_irq *pirq)
{
    if (pirq->msi_desc)
    {
        rt_pci_msi_mask_irq(pirq);
    }
}

static void k1x_pci_irq_unmask(struct rt_pic_irq *pirq)
{
    if (pirq->msi_desc)
    {
        rt_pci_msi_unmask_irq(pirq);
    }
}

static void k1x_pcie_irq_compose_msi_msg(struct rt_pic_irq *pirq, struct rt_pci_msi_msg *msg)
{
    rt_uint64_t msi_target;
    struct k1x_pcie *k1x = pirq->pic->priv_data;
    struct dw_pcie_port *port = &k1x->pci.port;

    msi_target = (rt_uint64_t)port->msi_data_phy;

    msg->address_lo = rt_lower_32_bits(msi_target);
    msg->address_hi = rt_upper_32_bits(msi_target);
    msg->data = pirq->hwirq;
}

static int k1x_pcie_irq_alloc_msi(struct rt_pic *pic, struct rt_pci_msi_desc *msi_desc)
{
    rt_ubase_t level;
    int irq, virq, hwirq;
    struct rt_pic_irq *pirq;
    struct k1x_pcie *k1x = pic->priv_data;
    struct dw_pcie_port *port = &k1x->pci.port;

    level = rt_spin_lock_irqsave(&port->lock);
    hwirq = rt_bitmap_next_clear_bit(port->msi_map, 0, MAX_MSI_IRQS);
    virq = hwirq + RT_PCI_INTX_PIN_MAX;

    if (hwirq >= MAX_MSI_IRQS || virq >= pic->irq_nr)
    {
        irq = -RT_EEMPTY;
        goto _out_lock;
    }

    pirq = rt_pic_find_irq(pic, virq);

    irq = rt_pic_config_irq(pic, virq, hwirq);
    pirq->mode = RT_IRQ_MODE_EDGE_RISING;

    rt_bitmap_set_bit(port->msi_map, hwirq);

_out_lock:
    rt_spin_unlock_irqrestore(&port->lock, level);

    return irq;
}

static void k1x_pcie_irq_free_msi(struct rt_pic *pic, int irq)
{
    rt_ubase_t level;
    struct rt_pic_irq *pirq;
    struct k1x_pcie *k1x = pic->priv_data;
    struct dw_pcie_port *port = &k1x->pci.port;

    pirq = rt_pic_find_pirq(pic, irq);

    if (!pirq)
    {
        return;
    }

    level = rt_spin_lock_irqsave(&port->lock);
    rt_bitmap_clear_bit(port->msi_map, pirq->hwirq);
    rt_spin_unlock_irqrestore(&port->lock, level);
}

static int k1x_pcie_irq_map(struct rt_pic *pic, int hwirq, rt_uint32_t mode)
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

static rt_err_t k1x_pcie_irq_parse(struct rt_pic *pic,
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

const static struct rt_pic_ops k1x_pcie_pic_ops =
{
    .name = "K1X-PCIe",
    .irq_mask = k1x_pci_irq_mask,
    .irq_unmask = k1x_pci_irq_unmask,
    .irq_compose_msi_msg = k1x_pcie_irq_compose_msi_msg,
    .irq_alloc_msi = k1x_pcie_irq_alloc_msi,
    .irq_free_msi = k1x_pcie_irq_free_msi,
    .irq_map = k1x_pcie_irq_map,
    .irq_parse = k1x_pcie_irq_parse,
};

static void k1x_pcie_pic_isr(int irqno, void *param)
{
    rt_uint32_t reg, hwirq;
    struct rt_pic_irq *pirq;
    struct k1x_pcie *k1x = param;

    reg = k1x_pcie_phy_ahb_readl(k1x, ADDR_INTR_STATUS1);
    k1x_pcie_phy_ahb_writel(k1x, ADDR_INTR_STATUS1, reg);

    /* MSI int handler */
    if ((reg & MSI_INT) | (reg & MSIX_INT))
    {
        rt_uint32_t val;

        if (k1x_pcie_phy_ahb_readl(k1x, ADDR_MSI_RECV_CTRL) & MSIX_AFIFO_FULL)
        {
            LOG_W("AXI monitor FIFO FULL");
        }

        for (int i = 0; i < FIFO_LEN; ++i)
        {
            if (k1x_pcie_phy_ahb_readl(k1x, ADDR_MON_FIFO_DATA0) == FIFO_EMPTY)
            {
                break;
            }
            val = k1x_pcie_phy_ahb_readl(k1x, ADDR_MON_FIFO_DATA1);
            /* In fact, val is the hwirq which equals with msi_data + msi vector */
            val &= INT_VEC_MASK;

            if ((pirq = rt_pic_find_irq(&k1x->pic, val + RT_PCI_INTX_PIN_MAX)))
            {
                rt_pic_handle_isr(pirq);
            }
        }
    }

    /* Legacy INTx */
    reg = k1x_pcie_phy_ahb_readl(k1x, K1X_PHY_AHB_IRQSTATUS_INTX);
    k1x_pcie_phy_ahb_writel(k1x, K1X_PHY_AHB_IRQSTATUS_INTX, reg);
    reg = (reg & INTX_MASK) >> INTX_SHIFT;

    if (reg)
    {
        LOG_D("Legacy INTx interrupt received");
    }

    while (reg)
    {
        hwirq = __rt_ffs(reg) - 1;
        reg &= ~RT_BIT(hwirq);

        pirq = rt_pic_find_irq(&k1x->pic, hwirq);

        if (pirq)
        {
            rt_pic_handle_isr(pirq);
        }
        else
        {
            LOG_E("Unexpected IRQ INTx #%c", 'A' + hwirq);
        }
    }
}

static rt_err_t k1x_add_pcie_port(struct k1x_pcie *k1x, struct rt_device *dev)
{
    rt_err_t err;
    rt_uint32_t reg;
    struct dw_pcie *pci = &k1x->pci;
    struct dw_pcie_port *port = &pci->port;
    struct rt_ofw_node *np = dev->ofw_node, *msi_np;

    /* Set Perst# (fundamental rstc) gpio low state */
    reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);
    reg |= PCIE_RC_PERST;
    k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, reg);

    port->sys_irq = rt_dm_dev_get_irq(dev, 0);
    if (port->sys_irq < 0)
    {
        LOG_E("Missing IRQ resource");
        return port->sys_irq;
    }

    if (!(pci->dbi_base = rt_dm_dev_iomap_by_name(dev, "dbi")))
    {
        return -RT_EIO;
    }

    if (!(pci->atu_base = rt_dm_dev_iomap_by_name(dev, "atu")))
    {
        return -RT_EIO;
    }

    if (!(msi_np = rt_ofw_append_child(np, "msi-controller")))
    {
        return -RT_ENOMEM;
    }

    k1x->msi_phandle_cell = cpu_to_fdt32(msi_np->phandle);

    if ((err = rt_ofw_append_prop(np, "msi-parent", sizeof(fdt32_t), &k1x->msi_phandle_cell)))
    {
        return err;
    }

    if (!(k1x->pic_np = rt_ofw_get_child_by_tag(np, "interrupt-controller")))
    {
        LOG_E("INTx ofw node not found");
        return -RT_EIO;
    }

    port->ops = &k1x_pcie_host_ops;
    port->irq_count = RT_PCI_INTX_PIN_MAX + MAX_MSI_IRQS;

    k1x->pic.priv_data = k1x;
    k1x->pic.ops = &k1x_pcie_pic_ops;
    rt_pic_linear_irq(&k1x->pic, port->irq_count);
    rt_pic_user_extends(&k1x->pic);
    rt_ofw_data(k1x->pic_np) = &k1x->pic;
    rt_ofw_node_put(k1x->pic_np);

    /* For MSI */
    rt_ofw_data(msi_np) = &k1x->pic;

    rt_hw_interrupt_install(port->sys_irq, k1x_pcie_pic_isr, k1x, "k1x-pcie");
    rt_hw_interrupt_umask(port->sys_irq);

    /* Init ID */
    dw_pcie_dbi_ro_writable_enable(pci, RT_TRUE);
    dw_pcie_writew_dbi(pci, PCIR_VENDOR, K1X_PCIE_VENDOR_ID);
    dw_pcie_writew_dbi(pci, PCIR_DEVICE, k1X_PCIE_DEVICE_ID);
    dw_pcie_dbi_ro_writable_enable(pci, RT_FALSE);

    if ((err = dw_pcie_host_init(port)))
    {
        LOG_E("Failed to initialize host");
        return err;
    }

    return RT_EOK;
}

/* Local cpu interrupt, vendor specific */
static void k1x_pcie_isr(int irqno, void *param)
{
    rt_uint32_t reg, reg_ahb;
    struct k1x_pcie *k1x = param;

    reg = k1x_pcie_readl_elbi(k1x, PCIE_ELBI_EP_DMA_IRQ_STATUS);
    /* Write 0 to clear the irq*/
    k1x_pcie_writel_elbi(k1x, PCIE_ELBI_EP_DMA_IRQ_STATUS, 0);
    reg_ahb = k1x_pcie_phy_ahb_readl(k1x, K1X_PHY_AHB_IRQSTATUS_MSI);

_repeat:
    if (reg & PC_TO_EP_INT)
    {
        LOG_I("EP ISR");
    }
    if (reg_ahb & DMA_READ_INT)
    {
        LOG_I("DMA ISR");
    }

    reg = k1x_pcie_readl_elbi(k1x, PCIE_ELBI_EP_DMA_IRQ_STATUS);
    if (reg & PC_TO_EP_INT)
    {
        k1x_pcie_writel_elbi(k1x, PCIE_ELBI_EP_DMA_IRQ_STATUS, 0);
        goto _repeat;
    }
}

/* Wait porta rterm done */
static void porta_rterm(struct k1x_pcie *k1x)
{
    rt_uint32_t val;
    int rd_data, count = 0;

    k1x_pcie_conf0_reg_writel(k1x, 0, 0x4000003f);

    val = k1x_pcie_conf0_reg_readl(k1x, 0);
    val &= 0xbfffffff;
    k1x_pcie_conf0_reg_writel(k1x, 0, val);

    /* Set refclk model */
    val = k1x_pcie_phy0_reg_readl(k1x, 0x17 << 2);
    val |= 0x1 << 10;
    k1x_pcie_phy0_reg_writel(k1x, 0x17 << 2, val);

    val = k1x_pcie_phy0_reg_readl(k1x, 0x17 << 2);
    val &= ~(0x3 << 8);
    k1x_pcie_phy0_reg_writel(k1x, 0x17 << 2, val);

    /* Driver mode */
    val = k1x_pcie_phy0_reg_readl(k1x, 0x17 << 2);
    val |= 0x1 << 8;
    k1x_pcie_phy0_reg_writel(k1x, 0x17 << 2, val);

    val = k1x_pcie_phy0_reg_readl(k1x, 0x12 << 2);
    val &= 0xffff0fff;
    k1x_pcie_phy0_reg_writel(k1x, 0x12 << 2, val);

    val = k1x_pcie_phy0_reg_readl(k1x, 0x12 << 2);
    val |= 0x00002000;
    k1x_pcie_phy0_reg_writel(k1x, 0x12 << 2, val);

    val = k1x_pcie_phy0_reg_readl(k1x, 0x13 << 2);
    val |= 0x1 << 4;
    k1x_pcie_phy0_reg_writel(k1x, 0x13 << 2, val);

    val = k1x_pcie_phy0_reg_readl(k1x, 0x12 << 2);
    val &= 0xfff0ffff;
    k1x_pcie_phy0_reg_writel(k1x, 0x12 << 2, val);

    k1x_pcie_phy0_reg_writel(k1x, 0x02 << 2, 0x00000b78);

    k1x_pcie_phy0_reg_writel(k1x, 0x06 << 2, 0x00000400);

    /* Wait pm0 rterm done */
    do {
        rd_data = k1x_pcie_phy0_reg_readl(k1x, 0x21 * 4);

        if (count++ > 5000)
        {
            LOG_E("Read PCIe%d phy rd_data time out", 0);
            break;
        }
    } while (((rd_data >> 10) & 0x1) == 0); /* Waiting PCIe portA readonly_reg2[2] r_tune_done==1 */
}

/* Force rterm value to porta/b/c */
static void rterm_force(struct k1x_pcie *k1x, rt_uint32_t pcie_rcal)
{
    rt_uint32_t val = 0;
    int lane = k1x->num_lanes;

    /* 2. Write pma0 rterm value LSB[3:0](read0nly1[3:0]) to lane0/1 rx_reg1 */
    for (int i = 0; i < lane; ++i)
    {
        val = k1x_pcie_phy_reg_readl(k1x, ((0x14 << 2) + 0x400 * i));
        val &= ~(0xf << 8);
        val |= (pcie_rcal & 0xf) << 8;
        k1x_pcie_phy_reg_writel(k1x, ((0x14 << 2) + 0x400 * i), val);
    }
    /* 3. Set lane0/1 rx_reg4 bit5=0 */
    for (int i = 0; i < lane; ++i)
    {
        val = k1x_pcie_phy_reg_readl(k1x, ((0x15 << 2) + 0x400 * i));
        val &= ~(1 << 5);
        k1x_pcie_phy_reg_writel(k1x, ((0x15 << 2) + 0x400 * i), val);
    }

    /* 4. Write pma0 rterm value MSB[7:4](readonly1[7:4]) to lane0/1 tx_reg1[7:4] */
    for (int i = 0; i < lane; ++i)
    {
        val = k1x_pcie_phy_reg_readl(k1x, ((0x19 << 2) + 0x400 * i));
        val &= ~(0xf << 12);
        val |= ((pcie_rcal >> 4) & 0xf) << 12;
        k1x_pcie_phy_reg_writel(k1x, ((0x19 << 2) + 0x400 * i), val);
    }

    /* 5. Set lane0/1 tx_reg3 bit1=1 */
    for (int i = 0; i < lane; ++i)
    {
        val = k1x_pcie_phy_reg_readl(k1x, ((0x19 << 2) + 0x400 * i));
        val |= 1 << 25;
        k1x_pcie_phy_reg_writel(k1x, ((0x19 << 2) + 0x400 * i), val);
    }

    /* 6. Adjust rc calrefclk freq */
    val = k1x_pcie_phy_reg_readl(k1x, 0x8 << 2);
    val &= ~(0x7 << 29);
    val |= 0x3 << 29;
    k1x_pcie_phy_reg_writel(k1x, 0x8 << 2, val);

    /* 7. Set lane0/1 rc_cal_reg1[6]=1 */
    for (int i = 0; i < lane; ++i)
    {
        val = k1x_pcie_phy_reg_readl(k1x, ((0x8 << 2) + 0x400 * i));
        val &= ~(1 << 22);
        k1x_pcie_phy_reg_writel(k1x, ((0x8 << 2) + 0x400 * i), val);
    }
    for (int i = 0; i < lane; ++i)
    {
        val = k1x_pcie_phy_reg_readl(k1x, ((0x8 << 2) + 0x400 * i));
        val |= 1 << 22;
        k1x_pcie_phy_reg_writel(k1x, ((0x8 << 2) + 0x400 * i), val);
    }
}

static rt_err_t init_phy(struct k1x_pcie *k1x)
{
    int count = 0;
    rt_uint32_t reg, rd_data, pcie_rcal, val = 0;

    if (k1x->port_id != 0)
    {
        if (!porta_init_done)
        {
            porta_rterm(k1x);
            pcie_rcal = k1x_pcie_phy0_reg_readl(k1x, 0x21 << 2);

            val = k1x_pcie_conf0_reg_readl(k1x, 0);
            val &= ~0x4000003f;
            k1x_pcie_conf0_reg_writel(k1x, 0, val);
        }
        else
        {
            pcie_rcal = k1x_pcie_phy0_reg_readl(k1x, 0x21 << 2);
        }
    }
    else
    {
        count = 0;
        do {
            rd_data = k1x_pcie_phy0_reg_readl(k1x, 0x21 * 4);

            if (count++ > 5000)
            {
                LOG_E("Read PCIe%d phy rd_data time out", 0);
                break;
            }
        } while (((rd_data >> 10) & 0x1) == 0);
        pcie_rcal = k1x_pcie_phy0_reg_readl(k1x, 0x21 << 2);
    }

    k1x->pcie_rcal = pcie_rcal;

    /* Disable ltssm and phy */
    reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);
    reg &= ~0x7f;
    k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, reg);

    /* Soft rstc */
    reg = k1x_pcie_readl(k1x, PCIE_CTRL_LOGIC);
    reg |= 1 << 0;
    k1x_pcie_writel(k1x, PCIE_CTRL_LOGIC, reg);

    rt_thread_mdelay(2);

    /* Soft no rstc */
    reg = k1x_pcie_readl(k1x, PCIE_CTRL_LOGIC);
    reg &= ~(1 << 0);
    k1x_pcie_writel(k1x, PCIE_CTRL_LOGIC, reg);

    reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);
    reg |= 0x3f;
    k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, reg);

    rterm_force(k1x, pcie_rcal);

    val = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);
    val &= 0xbfffffff;
    k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, val);

    /* Set refclk model */
    val = k1x_pcie_phy_reg_readl(k1x, 0x17 << 2);
    val |= 0x1 << 10;
    k1x_pcie_phy_reg_writel(k1x, 0x17 << 2, val);

    val = k1x_pcie_phy_reg_readl(k1x, 0x17 << 2);
    val &= ~(0x3 << 8);
    k1x_pcie_phy_reg_writel(k1x, 0x17 << 2, val);

    val = k1x_pcie_phy_reg_readl(k1x, 0x400 + (0x17 << 2));
    val |= 0x1 << 10;
    k1x_pcie_phy_reg_writel(k1x, 0x400 + (0x17 << 2), val);

    val = k1x_pcie_phy_reg_readl(k1x, 0x400 + (0x17 << 2));
    val &= ~(0x3 << 8);
    k1x_pcie_phy_reg_writel(k1x, 0x400 + (0x17 << 2), val);

    /* Driver mode */
    val = k1x_pcie_phy_reg_readl(k1x, 0x17 << 2);
    val |= 0x1 << 8;
    k1x_pcie_phy_reg_writel(k1x, 0x17 << 2, val);

    val = k1x_pcie_phy_reg_readl(k1x, 0x400 + (0x17 << 2));
    val |= 0x1 << 8;
    k1x_pcie_phy_reg_writel(k1x, 0x400 + (0x17 << 2), val);

    val = k1x_pcie_phy_reg_readl(k1x, 0x12 << 2);
    val &= 0xffff0fff;
    k1x_pcie_phy_reg_writel(k1x, 0x12 << 2, val);

    val = k1x_pcie_phy_reg_readl(k1x, 0x12 << 2);
    val |= 0x00002000;
    k1x_pcie_phy_reg_writel(k1x, 0x12 << 2, val);

    val = k1x_pcie_phy_reg_readl(k1x, 0x13 << 2);
    val |= 0x1 << 4;
    k1x_pcie_phy_reg_writel(k1x, 0x13 << 2, val);

    if (k1x->port_id == 0)
    {
        val = k1x_pcie_phy0_reg_readl(k1x, 0x14 << 2);
        val |= 0x1 << 3;
        k1x_pcie_phy0_reg_writel(k1x, 0x14 << 2, val);
    }

    /* pll_reg1 of lane0, disable ssc pll_reg4[3:0]=4'h0 */
    val = k1x_pcie_phy_reg_readl(k1x, 0x12 << 2);
    val &= 0xfff0ffff;
    k1x_pcie_phy_reg_writel(k1x, 0x12 << 2, val);

    /* PU_ADDR_CLK_CFG of lane0 */
    k1x_pcie_phy_reg_writel(k1x, 0x02 << 2, 0x00000b78);

    /* PU_ADDR_CLK_CFG of lane1 */
    k1x_pcie_phy_reg_writel(k1x, 0x400 + (0x02 << 2), 0x00000b78);

    /* Force rcv done */
    k1x_pcie_phy_reg_writel(k1x, 0x06 << 2, 0x00000400);

    /* Waiting pll lock */
    do {
        rd_data = k1x_pcie_phy_reg_readl(k1x, 0x8);

        if (count++ > 5000)
        {
            LOG_E("Read PCIe%d phy rd_data time out", k1x->port_id);
            break;
        }
    } while ((rd_data & 0x1) == 0);

    if (k1x->port_id == 0)
    {
        porta_init_done = RT_TRUE;
    }

    return RT_EOK;
}

static void k1x_pcie_hold_phy_rst(struct k1x_pcie *k1x)
{
    rt_uint32_t reg;

    reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);

    if (reg & APP_HOLD_PHY_RST)
    {
        LOG_D("Phy reset already held");
        return;
    }

    reg |= APP_HOLD_PHY_RST;
    k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, reg);
}

#ifdef RT_USING_PM
static rt_err_t k1x_pcie_dw_pcie_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    rt_uint32_t val;
    struct k1x_pcie *k1x = device->user_data;
    struct dw_pcie *pci = &k1x->pci;

    if (k1x->mode != DW_PCIE_RC_TYPE)
    {
        return RT_EOK;
    }

    /* Clear MSE */
    val = dw_pcie_readl_dbi(pci, PCIR_COMMAND);
    val &= ~PCIM_CMD_MEMEN;
    dw_pcie_writel_dbi(pci, PCIR_COMMAND, val);

    return RT_EOK;
}

static void k1x_pcie_dw_pcie_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    rt_uint32_t val;
    struct k1x_pcie *k1x = device->user_data;
    struct dw_pcie *pci = &k1x->pci;

    if (k1x->mode != DW_PCIE_RC_TYPE)
    {
        return;
    }

    /* Set MSE */
    val = dw_pcie_readl_dbi(pci, PCIR_COMMAND);
    val |= PCIM_CMD_MEMEN;
    dw_pcie_writel_dbi(pci, PCIR_COMMAND, val);
}

static const struct rt_device_pm_ops k1x_pcie_dw_pcie_pm_ops =
{
    .suspend = k1x_pcie_dw_pcie_pm_suspend,
    .resume = k1x_pcie_dw_pcie_pm_resume,
};
#endif /* RT_USING_PM */

static rt_err_t k1x_pcie_dw_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t reg;
    struct dw_pcie *pci;
    struct rt_device *dev = &pdev->parent;
    struct k1x_pcie *k1x = rt_calloc(1, sizeof(*k1x));
    const struct k1x_pcie_soc_data *data = pdev->id->data;

    if (!k1x)
    {
        return -RT_ENOMEM;
    }
    k1x->mode = data->mode;

    pci = &k1x->pci;
    pci->dev = dev;
    pci->ops = &dw_pcie_ops;
    pci->priv = k1x;

    if (!(k1x->base = rt_dm_dev_iomap_by_name(dev, "k1x_conf")))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (!(k1x->phy_ahb = rt_dm_dev_iomap_by_name(dev, "phy_ahb")))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (!(k1x->phy_addr = rt_dm_dev_iomap_by_name(dev, "phy_addr")))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (!(k1x->conf0_addr = rt_dm_dev_iomap_by_name(dev, "conf0_addr")))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (!(k1x->phy0_addr = rt_dm_dev_iomap_by_name(dev, "phy0_addr")))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if ((k1x->irq = rt_dm_dev_get_irq(dev, 1)) < 0)
    {
        err = k1x->irq;
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "k1x,pcie-port", &k1x->port_id)))
    {
        LOG_E("Failed to get pcie's port id");
        goto _fail;
    }

    if (rt_dm_dev_prop_read_u32(dev, "num-lanes", &k1x->num_lanes))
    {
        LOG_W("Failed to get pcie's port num-lanes");
        k1x->num_lanes = 1;
    }

    if (k1x->num_lanes < 1 || k1x->num_lanes > 2)
    {
        LOG_W("Configuration of num-lanes is invalid");
        k1x->num_lanes = 1;
    }

    k1x->pwr_on_pin = rt_pin_get_named_pin(dev, "k1x,pwr_on", 0,
            RT_NULL, &k1x->pwr_on_active_val);

    k1x->clk_master = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(k1x->clk_master))
    {
        err = rt_ptr_err(k1x->clk_master);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(k1x->clk_master)))
    {
        goto _fail;
    }

    /* PCIE0 and usb use combo phy and rstc */
    k1x->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(k1x->rstc))
    {
        err = rt_ptr_err(k1x->rstc);
        goto _fail;
    }

    k1x_pcie_hold_phy_rst(k1x);

    rt_reset_control_deassert(k1x->rstc);

    if ((err = init_phy(k1x)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "max-link-speed", &k1x->link_gen)))
    {
        goto _fail;
    }
    if (k1x->link_gen < 0 || k1x->link_gen > 3)
    {
        k1x->link_gen = 3;
    }

    rt_hw_interrupt_install(k1x->irq, k1x_pcie_isr, k1x, "k1x-pcie-vs");
    rt_hw_interrupt_umask(k1x->irq);

    switch (k1x->mode)
    {
    case DW_PCIE_RC_TYPE:
        reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);
        reg |= DEVICE_TYPE_RC | PCIE_AUX_PWR_DET;
        k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, reg);

        reg = k1x_pcie_readl(k1x, PCIE_CTRL_LOGIC);
        reg |= PCIE_IGNORE_PERSTN;
        k1x_pcie_writel(k1x, PCIE_CTRL_LOGIC, reg);

        /* Power on the interface */
        if (k1x->pwr_on_pin >= 0)
        {
            rt_pin_write(k1x->pwr_on_pin, k1x->pwr_on_active_val);
            rt_pin_mode(k1x->pwr_on_pin, PIN_MODE_OUTPUT);
        }

        err = k1x_add_pcie_port(k1x, dev);
        break;

    case DW_PCIE_EP_TYPE:
        reg = k1x_pcie_readl(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD);
        reg &= ~DEVICE_TYPE_RC;
        k1x_pcie_writel(k1x, PCIECTRL_K1X_CONF_DEVICE_CMD, reg);

        err = k1x_add_pcie_ep(k1x, dev);
        break;

    default:
        /* It's impossible */
        RT_ASSERT(0);
        break;
    }

    if (err)
    {
        goto _free_irq;
    }

#ifdef RT_USING_PM
    rt_pm_device_register(dev, &k1x_pcie_dw_pcie_pm_ops);
#endif

    dev->user_data = k1x;

    return RT_EOK;

_free_irq:
    rt_hw_interrupt_mask(k1x->irq);
    rt_pic_detach_irq(k1x->irq, k1x);

    rt_clk_disable_unprepare(k1x->clk_master);

_fail:
    if (k1x->base)
    {
        rt_iounmap(k1x->base);
    }
    if (k1x->phy_ahb)
    {
        rt_iounmap(k1x->phy_ahb);
    }
    if (k1x->phy_addr)
    {
        rt_iounmap(k1x->phy_addr);
    }
    if (k1x->conf0_addr)
    {
        rt_iounmap(k1x->conf0_addr);
    }
    if (k1x->phy0_addr)
    {
        rt_iounmap(k1x->phy0_addr);
    }
    if (!rt_is_err_or_null(k1x->clk_master))
    {
        rt_clk_put(k1x->clk_master);
    }
    if (!rt_is_err_or_null(k1x->rstc))
    {
        rt_reset_control_put(k1x->rstc);
    }
    if (k1x->pci.port.msi_data)
    {
        rt_dma_free_coherent(dev, sizeof(rt_uint64_t), k1x->pci.port.msi_data, k1x->pci.port.msi_data_phy);
    }
    if (k1x->msix_data)
    {
        rt_dma_free_coherent(dev, sizeof(rt_uint64_t), k1x->msix_data, k1x->msix_data_phy);
    }

    rt_free(k1x);

    return err;
}

static const struct k1x_pcie_soc_data k1x_pcie_rc_soc_data =
{
    .mode = DW_PCIE_RC_TYPE,
};

static const struct k1x_pcie_soc_data k1x_pcie_ep_soc_data =
{
    .mode = DW_PCIE_EP_TYPE,
};

static const struct rt_ofw_node_id k1x_pcie_dw_ofw_ids[] =
{
    { .compatible = "k1x,dwc-pcie",     .data = &k1x_pcie_rc_soc_data, },
    { .compatible = "k1x,dwc-pcie-ep",  .data = &k1x_pcie_ep_soc_data, },
    { /* sentinel */ }
};

static struct rt_platform_driver k1x_pcie_dw_driver =
{
    .name = "dw-pcie-k1x",
    .ids = k1x_pcie_dw_ofw_ids,

    .probe = k1x_pcie_dw_probe,
};
RT_PLATFORM_DRIVER_EXPORT(k1x_pcie_dw_driver);
