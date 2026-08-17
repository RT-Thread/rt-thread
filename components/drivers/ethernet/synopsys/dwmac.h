/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __DWMAC_H__
#define __DWMAC_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <drivers/misc.h>
#include "../ethernet_dm.h"

/* GMAC4 MAC registers (offset from mac_base) */
#define GMAC_CONFIG                     0x0000
#define GMAC_PACKET_FILTER              0x0008
#define GMAC_MDIO_ADDR                  0x0200
#define GMAC_MDIO_DATA                  0x0204
#define GMAC_ADDR_HIGH(reg)             (0x0300 + (reg) * 8)
#define GMAC_ADDR_LOW(reg)              (0x0304 + (reg) * 8)
#define GMAC_RXQ_CTRL0                  0x00a0
#define GMAC_RXQ_CTRL1                  0x00a4

#define GMAC_CONFIG_RE                  RT_BIT(0)
#define GMAC_CONFIG_TE                  RT_BIT(1)
#define GMAC_CONFIG_DM                  RT_BIT(13)
#define GMAC_CONFIG_FES                 RT_BIT(14)
#define GMAC_CONFIG_PS                  RT_BIT(15)
#define GMAC_CONFIG_IPC                 RT_BIT(27)

#define GMAC_PF_PM                      RT_BIT(4)

#define GMAC_RX_DCB_QUEUE_ENABLE(q)     RT_BIT(((q) * 2) + 1)
#define GMAC_RXQCTRL_MCBCQEN            RT_BIT(20)
#define GMAC_RXQCTRL_MCBCQ_MASK         RT_GENMASK(18, 16)
#define GMAC_RXQCTRL_MCBCQ_SHIFT        16

/* DMA top-level (offset from mac_base) */
#define DMA_BUS_MODE                    0x1000
#define DMA_SYS_BUS_MODE                0x1004
#define DMA_BUS_MODE_SFT_RESET          RT_BIT(0)
#define DMA_SYS_BUS_FB                  RT_BIT(0)
#define DMA_SYS_BUS_MB                  RT_BIT(14)
#define DMA_SYS_BUS_AAL                 RT_BIT(12)
#define DMA_AXI_BLEN16                  RT_BIT(3)
#define DMA_AXI_BLEN8                   RT_BIT(2)
#define DMA_AXI_BLEN4                   RT_BIT(1)
#define DMA_AXI_BLEN32                  RT_BIT(4)
#define DMA_AXI_BLEN64                  RT_BIT(5)
#define DMA_AXI_BLEN128                 RT_BIT(6)
#define DMA_AXI_BLEN256                 RT_BIT(7)
#define DMA_AXI_WR_OSR_LMT_SHIFT        24
#define DMA_AXI_RD_OSR_LMT_SHIFT        16

#define DMA_CHAN_BASE                   0x1100
#define DMA_CHAN_OFFSET                 0x80
#define DMA_CHAN_CONTROL(c)             (DMA_CHAN_BASE + (c) * DMA_CHAN_OFFSET)
#define DMA_CHAN_TX_CONTROL(c)          (DMA_CHAN_CONTROL(c) + 0x04)
#define DMA_CHAN_RX_CONTROL(c)          (DMA_CHAN_CONTROL(c) + 0x08)
#define DMA_CHAN_TX_BASE_ADDR(c)        (DMA_CHAN_CONTROL(c) + 0x14)
#define DMA_CHAN_RX_BASE_ADDR(c)        (DMA_CHAN_CONTROL(c) + 0x1c)
#define DMA_CHAN_TX_END_ADDR(c)         (DMA_CHAN_CONTROL(c) + 0x20)
#define DMA_CHAN_RX_END_ADDR(c)         (DMA_CHAN_CONTROL(c) + 0x28)
#define DMA_CHAN_TX_RING_LEN(c)         (DMA_CHAN_CONTROL(c) + 0x2c)
#define DMA_CHAN_RX_RING_LEN(c)         (DMA_CHAN_CONTROL(c) + 0x30)
#define DMA_CHAN_INTR_ENA(c)            (DMA_CHAN_CONTROL(c) + 0x34)
#define DMA_CHAN_STATUS(c)              (DMA_CHAN_CONTROL(c) + 0x60)

#define DMA_CONTROL_ST                  RT_BIT(0)
#define DMA_CONTROL_SR                  RT_BIT(0)
#define DMA_CONTROL_OSP                 RT_BIT(4)
#define DMA_CONTROL_TSE                 RT_BIT(12)
#define DMA_BUS_MODE_PBL_SHIFT          16
#define DMA_BUS_MODE_RPBL_SHIFT         16
#define DMA_RBSZ_SHIFT                  1
#define DMA_RBSZ_MASK                   RT_GENMASK(14, 1)

#define DMA_CHAN_STATUS_TI              RT_BIT(0)
#define DMA_CHAN_STATUS_RI              RT_BIT(6)
#define DMA_CHAN_STATUS_NIS             RT_BIT(15)

#define DMA_CHAN_INTR_ENA_RIE           RT_BIT(6)
#define DMA_CHAN_INTR_ENA_TIE           RT_BIT(0)
#define DMA_CHAN_INTR_ENA_NIE           RT_BIT(16)
#define DMA_CHAN_INTR_ENA_AIE           RT_BIT(15)
#define DMA_CHAN_INTR_ENA_NIE_4_10      RT_BIT(15)
#define DMA_CHAN_INTR_ENA_AIE_4_10      RT_BIT(14)
#define DMA_CHAN_INTR_ENA_FBE           RT_BIT(12)
#define DMA_CHAN_INTR_DEFAULT_MASK      (DMA_CHAN_INTR_ENA_NIE | \
                                         DMA_CHAN_INTR_ENA_AIE | \
                                         DMA_CHAN_INTR_ENA_FBE | \
                                         DMA_CHAN_INTR_ENA_RIE | \
                                         DMA_CHAN_INTR_ENA_TIE)
#define DMA_CHAN_INTR_DEFAULT_MASK_4_10 (DMA_CHAN_INTR_ENA_NIE_4_10 | \
                                         DMA_CHAN_INTR_ENA_AIE_4_10 | \
                                         DMA_CHAN_INTR_ENA_FBE | \
                                         DMA_CHAN_INTR_ENA_RIE | \
                                         DMA_CHAN_INTR_ENA_TIE)

#define MTL_OPERATION_MODE              0x0c00
#define MTL_RXQ_DMA_MAP0                0x0c30
#define MTL_RXQ_DMA_QXMDMACH_MASK(q)    (0xf << (8 * (q)))
#define MTL_RXQ_DMA_QXMDMACH(chan, q)   ((chan) << (8 * (q)))
#define MTL_CHAN_BASE                   0x0d00
#define MTL_CHAN_OFFSET                 0x40
#define MTL_CHAN_TX_OP_MODE(c)          (MTL_CHAN_BASE + (c) * MTL_CHAN_OFFSET)
#define MTL_CHAN_RX_OP_MODE(c)          (MTL_CHAN_BASE + (c) * MTL_CHAN_OFFSET + 0x30)
#define MTL_OP_MODE_RSF                 RT_BIT(5)
#define MTL_OP_MODE_TSF                 RT_BIT(1)
#define MTL_OP_MODE_TXQEN               RT_BIT(3)

/* Enhanced descriptors (DWMAC4) */
#define TDES2_BUFFER1_SIZE_MASK         RT_GENMASK(13, 0)
#define TDES3_PACKET_SIZE_MASK          RT_GENMASK(14, 0)
#define TDES3_CHECKSUM_INSERTION_SHIFT  16
#define TDES3_CHECKSUM_INSERTION_FULL   (3 << TDES3_CHECKSUM_INSERTION_SHIFT)
#define TDES3_FIRST_DESCRIPTOR          RT_BIT(29)
#define TDES3_LAST_DESCRIPTOR           RT_BIT(28)
#define TDES3_OWN                       RT_BIT(31)
#define RDES3_OWN                       RT_BIT(31)
#define RDES3_INT_ON_COMPLETION_EN      RT_BIT(30)
#define RDES3_BUFFER1_VALID_ADDR        RT_BIT(24)
#define RDES3_PACKET_SIZE_MASK          RT_GENMASK(14, 0)

#define MII_ADDR_GBUSY                  RT_BIT(0)
#define MII_DATA_GD_MASK                RT_GENMASK(15, 0)
#define MII_GMAC4_GOC_SHIFT             2
#define MII_GMAC4_WRITE                 (1 << MII_GMAC4_GOC_SHIFT)
#define MII_GMAC4_READ                  (3 << MII_GMAC4_GOC_SHIFT)
#define MII_GMAC4_ADDR_SHIFT            21
#define MII_GMAC4_ADDR_MASK             RT_GENMASK(25, 21)
#define MII_GMAC4_REG_SHIFT             16
#define MII_GMAC4_REG_MASK              RT_GENMASK(20, 16)
#define MII_GMAC4_CSR_SHIFT             8
#define MII_GMAC4_CSR_100_150M          (0x4 << MII_GMAC4_CSR_SHIFT)

#define DWMAC_RX_RING_SIZE              32
#define DWMAC_TX_RING_SIZE              16
#define DWMAC_RX_BUFFER_SIZE            1536
#define DWMAC_CHAN                      0
#define DWMAC_DMA_PBL                   8
#define DWMAC_MDIO_TIMEOUT_US           10000

enum dwmac_core_type
{
    DWMAC_CORE_GMAC4,
};

struct dwmac_desc
{
    rt_uint32_t des0;
    rt_uint32_t des1;
    rt_uint32_t des2;
    rt_uint32_t des3;
};

#define DWMAC_CAP_TSO                   RT_BIT(0)
#define DWMAC_CAP_PTP                   RT_BIT(1)

struct dwmac_axi_cfg
{
    rt_uint32_t wr_osr_lmt;
    rt_uint32_t rd_osr_lmt;
    rt_bool_t fixed_burst;
    rt_bool_t mixed_burst;
    rt_bool_t aal;
    rt_uint32_t blen_mask;
};

struct dwmac_mtl_cfg
{
    rt_uint32_t rx_queues;
    rt_uint32_t tx_queues;
};

struct dwmac_eth;

struct dwmac_plat_ops
{
    rt_uint32_t flags;

    rt_err_t (*parse_ofw)(struct dwmac_eth *eth);
    rt_err_t (*init)(struct dwmac_eth *eth);
    void     (*exit)(struct dwmac_eth *eth);
    rt_err_t (*fix_link_speed)(struct dwmac_eth *eth, int speed);
};

struct dwmac_config
{
    enum dwmac_core_type core_type;
    rt_uint32_t caps;
    rt_uint8_t dma_pbl;
    const struct dwmac_plat_ops *plat;
};

struct dwmac_eth
{
    struct eth_device parent;
    struct rt_device *dev;

    void *mac_base;
    int irq;

    struct rt_phy_device *phy;
    struct mii_bus *mii;

    rt_uint8_t mac[6];
    int phy_interface;

    struct rt_clk *stmmac_clk;
    struct rt_clk *mac_clk_speed;
    struct rt_clk *mac_clk_rx;
    struct rt_clk *mac_clk_tx;
    struct rt_clk *clk_mac_refout;
    struct rt_clk *ptp_clk;
    struct rt_clk *aclk;
    struct rt_clk *pclk;
    struct rt_reset_control *rst;
#ifdef RT_USING_REGULATOR
    struct rt_regulator *phy_supply;
#endif

    rt_ssize_t phy_reset_pin;
    rt_uint8_t phy_reset_active;
    rt_uint32_t phy_reset_delays[3];

    struct dwmac_desc *rx_ring;
    struct dwmac_desc *tx_ring;
    rt_ubase_t rx_ring_dma;
    rt_ubase_t tx_ring_dma;
    rt_uint8_t *rx_buffers;
    rt_ubase_t rx_buffers_dma;
    rt_uint8_t *tx_buffers;
    rt_ubase_t tx_buffers_dma;
    rt_size_t dma_blob_size;
    rt_ubase_t dma_blob_handle;

    rt_uint32_t tx_idx;
    rt_uint32_t rx_idx;

    rt_uint8_t dma_pbl;
    rt_uint8_t dma_txpbl;
    rt_uint8_t dma_rxpbl;
    rt_bool_t tso_en;
    struct dwmac_axi_cfg axi;
    struct dwmac_mtl_cfg mtl;

    rt_bool_t hw_ready;
    rt_bool_t mac_started;
    rt_bool_t net_registered;
    rt_bool_t irq_installed;
    rt_bool_t phy_configured;

#ifdef RT_USING_SYSTEM_WORKQUEUE
    struct rt_work phy_retry_work;
    rt_bool_t phy_work_inited;
#endif

    const struct dwmac_config *config;
    void *plat_priv;

#ifdef RT_ETHERNET_DWMAC_PTP
    struct rt_ptp_clock ptp_parent;
    rt_uint32_t ptp_clk_rate;
    rt_uint32_t default_addend;
    rt_uint32_t sub_second_inc;
    rt_uint32_t systime_flags;
    rt_uint8_t pps_out_num;
    rt_uint8_t aux_snapshot_num;
#endif /* RT_ETHERNET_DWMAC_PTP */
};

#define dwmac_readl(eth, reg)           HWREG32((rt_uint8_t *)(eth)->mac_base + (reg))
#define dwmac_writel(eth, reg, val)     HWREG32((rt_uint8_t *)(eth)->mac_base + (reg)) = (val)

rt_inline const struct dwmac_plat_ops *dwmac_plat(const struct dwmac_eth *eth)
{
    if (eth && eth->config && eth->config->plat)
    {
        return eth->config->plat;
    }

    return RT_NULL;
}

rt_err_t dwmac_probe(struct dwmac_eth *eth);
rt_err_t dwmac_remove(struct dwmac_eth *eth);
rt_err_t dwmac_eth_common_probe(struct dwmac_eth *eth);
rt_err_t dwmac_eth_common_remove(struct dwmac_eth *eth);

#ifdef RT_ETHERNET_DWMAC_PTP
rt_err_t dwmac_ptp_register(struct dwmac_eth *eth);
void dwmac_ptp_unregister(struct dwmac_eth *eth);
#endif /* RT_ETHERNET_DWMAC_PTP */

#endif /* __DWMAC_H__ */
