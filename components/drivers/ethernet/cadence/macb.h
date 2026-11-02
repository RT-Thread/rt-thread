/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#ifndef __MACB_H__
#define __MACB_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "../ethernet_dm.h"

/* Queue 0 (legacy offsets) */
#define GEM_NCR                                 0x0000
#define GEM_NCFGR                               0x0004
#define GEM_NSR                                 0x0008
#define GEM_USRIO                               0x000c
#define GEM_DMACFG                              0x0010
#define GEM_TSR                                 0x0014
#define GEM_TSR_TGO                             RT_BIT(3)
#define GEM_TSR_COMP                            RT_BIT(5)
#define GEM_RSR                                 0x0020
#define GEM_ISR                                 0x0024
#define GEM_IER                                 0x0028
#define GEM_IDR                                 0x002c
#define GEM_IMR                                 0x0030
#define GEM_ISR0                                0x0400  /* GEM queue 0 ISR */
#define GEM_IER0                                0x0600  /* GEM queue 0 IER */
#define GEM_IDR0                                0x0620  /* GEM queue 0 IDR */
#define GEM_IMR0                                0x0640  /* GEM queue 0 IMR */
#define GEM_MAN                                 0x0034  /* PHY maintenance (was wrongly 0x340) */
/*
 * GEM queue 0 uses legacy MACB ring/IRQ registers; GEM_*Q1+ live at 0x440/0x480.
 * Linux: queue0 -> MACB_TBQP/RBQP/ISR/IER; queue1+ -> GEM_TBQP(n)/GEM_RBQP(n).
 */
#define GEM_RBQP                                0x0018
#define GEM_TBQP                                0x001c
#define GEM_RBQP1                               0x0480
#define GEM_TBQP1                               0x0440
#define MACB_MAX_QUEUES                         8
#define GEM_QUEUE_TBQP(q)                       (0x0440 + ((q) << 2))
#define GEM_QUEUE_RBQP(q)                       (0x0480 + ((q) << 2))

#define GEM_JML                                 0x0048
#define GEM_PBUFRXCUT                           0x0044
#define GEM_INTMOD                              0x005c
#define GEM_INTMOD_TX_MOD_SHIFT                 16
#define GEM_INTMOD_RX_MOD_SHIFT                 0

#define GEM_SA1B                                0x0088
#define GEM_SA1T                                0x008c

#define GEM_DCFG1                               0x0280
#define GEM_DCFG1_IRQCOR_SHIFT                  23
#define GEM_DCFG5                               0x0290
#define GEM_DCFG6                               0x0294
#define GEM_DCFG6_DAW64_SHIFT                   23

#define GEM_RBQPH                               0x04d4
#define GEM_TBQPH                               0x04c8

#define GEM_AMP                                 0x0054
#define GEM_AMP_AR2R_MAX_PIPE_SHIFT             0
#define GEM_AMP_AW2W_MAX_PIPE_SHIFT             8
#define GEM_AMP_AW2B_FILL_SHIFT                 16

#define GEM_USRIO_RGMII                         RT_BIT(0)

/* TSU / 1588 */
#define GEM_TISUBN                              0x01bc
#define GEM_TSH                                 0x01c0
#define GEM_TSL                                 0x01d0
#define GEM_TN                                  0x01d4
#define GEM_TA                                  0x01d8
#define GEM_TI                                  0x01dc

/* NCR */
#define GEM_NCR_LLB                             RT_BIT(1)
#define GEM_NCR_RE                              RT_BIT(2)
#define GEM_NCR_TE                              RT_BIT(3)
#define GEM_NCR_MPE                             RT_BIT(4)
#define GEM_NCR_CLRSTAT                         RT_BIT(5)
#define GEM_NCR_TSTART                          RT_BIT(9)

/*
 * NCFGR: GEM uses same SPD/FD as MACB (bit0/1); gigabit is GEM_GBE @ bit10,
 * not bit31.
 */
#define GEM_NCFGR_SPD                           RT_BIT(0)   /* 100 Mbps */
#define GEM_NCFGR_FD                            RT_BIT(1)   /* Full duplex */
#define GEM_NCFGR_GBE                           RT_BIT(10)  /* 1000 Mbps (GEM) */
#define GEM_NCFGR_BIG                           RT_BIT(8)   /* Receive 1536-byte frames */
#define GEM_NCFGR_DRFCS                         RT_BIT(17)  /* Discard RX FCS */

/* DBW in NCFGR bits [22:21] */
#define GEM_NCFGR_DBW_SHIFT                     21

/* MDC clock divider in NCFGR bits [20:18] */
#define GEM_NCFGR_CLK_SHIFT                     18

/* NSR */
#define GEM_NSR_IDLE                            RT_BIT(2)

/* RSR */
#define GEM_RSR_BNA                             RT_BIT(0)
#define GEM_RSR_REC                             RT_BIT(1)
#define GEM_RSR_OVR                             RT_BIT(2)

/* ISR / IER / IDR / IMR: queue 0 @ 0x24..0x30; extra GEM queues @ 0x400/0x600 */
#define GEM_INT_MFD                             RT_BIT(0)
#define GEM_INT_HRESP                           RT_BIT(11)
#define GEM_INT_RCOMP                           RT_BIT(1)
#define GEM_INT_RXUBR                           RT_BIT(2)
#define GEM_INT_TXUBR                           RT_BIT(3)
#define GEM_INT_TUND                            RT_BIT(4)
#define GEM_INT_RLE                             RT_BIT(5)
#define GEM_INT_TXERR                           RT_BIT(6)
#define GEM_INT_TCOMP                           RT_BIT(7)
#define GEM_INT_LINK                            RT_BIT(9)
#define GEM_INT_ROVR                            RT_BIT(10)

#define GEM_INT_RX_BITS                         (GEM_INT_RCOMP | GEM_INT_RXUBR | GEM_INT_ROVR)
#define GEM_INT_TX_BITS                         (GEM_INT_TCOMP | GEM_INT_TUND | GEM_INT_RLE | GEM_INT_TXERR)

/* MAN (MDIO clause 22) */
#define GEM_MAN_SOF                             1
#define GEM_MAN_WRITE                           1
#define GEM_MAN_READ                            2
#define GEM_MAN_CODE                            2

#define GEM_MAN_DATA_OFF                        0
#define GEM_MAN_DATA_SZ                         16
#define GEM_MAN_CODE_OFF                        16
#define GEM_MAN_CODE_SZ                         2
#define GEM_MAN_REGA_OFF                        18
#define GEM_MAN_REGA_SZ                         5
#define GEM_MAN_PHYA_OFF                        23
#define GEM_MAN_PHYA_SZ                         5
#define GEM_MAN_RW_OFF                          28
#define GEM_MAN_RW_SZ                           2
#define GEM_MAN_SOF_OFF                         30
#define GEM_MAN_SOF_SZ                          2
#define GEM_MAN_BF(name, val)                   (((val) & ((1 << GEM_MAN_##name##_SZ) - 1)) << GEM_MAN_##name##_OFF)

/*
 * RX descriptor word @addr: OWNERSHIP uses bit0 (RX_USED); WRAP is bit1.
 * Word @ctrl: frame length in bits [11:0], SOF/EOF for single-buffer frames.
 */
#define GEM_RX_USED                             RT_BIT(0)   /* In addr */
#define GEM_RX_WRAP                             RT_BIT(1)   /* In addr */
#define GEM_RX_LEN_MASK                         0x0fff      /* FRMLEN in ctrl */
#define GEM_RX_SOF                              RT_BIT(14)
#define GEM_RX_EOF                              RT_BIT(15)

/* TX descriptor @ctrl (GEM length bits [13:0]) */
#define GEM_TX_LAST                             RT_BIT(15)
#define GEM_TX_NOCRC                            RT_BIT(16)
#define GEM_TX_WRAP                             RT_BIT(30)
#define GEM_TX_USED                             RT_BIT(31)
#define GEM_TX_LEN_MASK                         0x3fff

/* DMACFG */
#define GEM_DMACFG_FBLDO_SHIFT                  0
#define GEM_DMACFG_ENDIA_DESC_SHIFT             6
#define GEM_DMACFG_ENDIA_PKT_SHIFT              7
#define GEM_DMACFG_RXBMS_SHIFT                  8
#define GEM_DMACFG_TXPBMS_SHIFT                 10
#define GEM_DMACFG_RXBS_SHIFT                   16
#define GEM_DMACFG_DDRP_SHIFT                   24
#define GEM_DMACFG_RXEXT_SHIFT                  28
#define GEM_DMACFG_TXEXT_SHIFT                  29
#define GEM_DMACFG_ADDR64_SHIFT                 30

#define GEM_DMACFG_RXBS_MASK                    0xff

#define GEM_CLK_DIV8                            0
#define GEM_CLK_DIV16                           1
#define GEM_CLK_DIV32                           2
#define GEM_CLK_DIV48                           3
#define GEM_CLK_DIV64                           4
#define GEM_CLK_DIV96                           5
#define GEM_CLK_DIV128                          6
#define GEM_CLK_DIV224                          7

/* DCFG5: TSU present */
#define GEM_DCFG5_TSU_SHIFT                     8

#define GEM_DBW32                               0
#define GEM_DBW64                               1
#define GEM_DBW128                              2

#define MACB_CAP_USRIO_HAS_CLKEN                RT_BIT(1)
#define MACB_CAP_USRIO_DEFAULT_MII_GMII         RT_BIT(2)
#define MACB_CAP_NO_GIGABIT_HALF                RT_BIT(3)
#define MACB_CAP_USRIO_DISABLED                 RT_BIT(4)
#define MACB_CAP_JUMBO                          RT_BIT(5)
#define MACB_CAP_GEM_HAS_PTP                    RT_BIT(6)
#define MACB_CAP_BD_RD_PREFETCH                 RT_BIT(7)
#define MACB_CAP_NEEDS_RSTONUBR                 RT_BIT(8)
#define MACB_CAP_MIIONRGMII                     RT_BIT(9)
#define MACB_CAP_NEED_TSUCLK                    RT_BIT(10)
#define MACB_CAP_QUEUE_DISABLE                  RT_BIT(11)
#define MACB_CAP_QBV                            RT_BIT(12)
#define MACB_CAP_CLK_HW_CHG                     RT_BIT(15)
#define MACB_CAP_MACB_IS_EMAC                   RT_BIT(16)
#define MACB_CAP_GIGABIT_MODE_AVAILABLE         RT_BIT(18)
#define MACB_CAP_SG_DISABLED                    RT_BIT(19)
#define MACB_CAP_NO_LSO                         RT_BIT(24)

struct macb_eth;

struct macb_config
{
    rt_uint32_t caps;
    rt_uint8_t dma_burst_length;
    rt_uint16_t jumbo_max_len;
    rt_uint16_t max_tx_len;
};

struct macb_dma_desc
{
    rt_uint32_t addr;
    rt_uint32_t ctrl;
};

struct macb_dma_desc_64
{
    rt_uint32_t addrh;
    rt_uint32_t resvd;
};

#define MACB_RX_RING_SIZE                       32
#define MACB_TX_RING_SIZE                       16
#define MACB_RX_BUFFER_SIZE                     1536

/* RXBS encoding: buffer_bytes / 64 */
#define MACB_RX_BUFFER_SIZE_DIV64               (MACB_RX_BUFFER_SIZE / 64)

struct macb_eth
{
    struct eth_device parent;
#ifdef RT_ETHERNET_CADENCE_PTP
    struct rt_ptp_clock ptp_parent;
#endif
    struct rt_device *dev;

    struct rt_phy_device *phy;
    struct mii_bus *mii;

    int irq;
    void *regs;

    struct rt_clk *pclk;
    struct rt_clk *hclk;
    struct rt_clk *tsu_clk;
    struct rt_clk *tx_clk;

    rt_uint8_t mac[6];
    rt_bool_t is_gem;
    rt_bool_t dma_64bit;
    rt_bool_t native_io;
    rt_bool_t isr_clear_on_write;
    rt_uint32_t ncr_shadow;
    rt_uint32_t ncfgr_shadow;

    const struct macb_config *config;
    rt_uint16_t max_tx_len;

    int phy_interface;
    rt_ssize_t phy_reset_pin;
    rt_uint8_t phy_reset_active;
    rt_uint16_t phy_reset_ms;
    rt_uint8_t aw2w_max_pipe;
    rt_uint8_t ar2r_max_pipe;
    rt_bool_t use_aw2b_fill;

    struct macb_dma_desc *rx_ring;
    struct macb_dma_desc *tx_ring;
    rt_uint8_t *rx_buffer;
    rt_uint8_t *tx_buffer;
    rt_size_t dma_blob_size;
    rt_ubase_t dma_blob_handle;
    rt_ubase_t rx_ring_dma;
    rt_ubase_t tx_ring_dma;
    rt_ubase_t rx_buffer_dma;
    rt_ubase_t tx_buffer_dma;

    struct macb_dma_desc *dummy_desc;
    rt_ubase_t dummy_desc_dma;
    rt_size_t dummy_desc_size;

    rt_uint32_t rx_tail;
    rt_uint32_t tx_head;
    rt_uint32_t tx_tail;

    rt_bool_t net_registered;
    rt_bool_t irq_installed;
    rt_bool_t hw_ready;
    rt_bool_t mac_started;
    rt_bool_t phy_configured;

#ifdef RT_USING_SYSTEM_WORKQUEUE
    struct rt_work phy_retry_work;
    int phy_retry_count;
#endif

    struct rt_mutex mdio_lock;
    struct rt_semaphore tx_sem;
};

#define raw_to_macb_eth(raw) \
    rt_container_of(rt_container_of(raw, struct eth_device, parent), struct macb_eth, parent)
#define raw_to_macb_ptp(raw) \
    rt_container_of(raw, struct macb_eth, ptp_parent)

rt_inline rt_uint32_t macb_readl(struct macb_eth *eth, rt_uint32_t off)
{
    if (eth->native_io)
    {
        return *(volatile rt_uint32_t *)((rt_uint8_t *)eth->regs + off);
    }

    return HWREG32(eth->regs + off);
}

rt_inline void macb_writel(struct macb_eth *eth, rt_uint32_t off, rt_uint32_t val)
{
    if (eth->native_io)
    {
        *(volatile rt_uint32_t *)((rt_uint8_t *)eth->regs + off) = val;
    }
    else
    {
        HWREG32(eth->regs + off) = val;
    }
}

rt_err_t macb_eth_hw_init(struct macb_eth *eth);
void macb_eth_hw_stop(struct macb_eth *eth);

rt_err_t macb_eth_common_probe(struct macb_eth *eth);
rt_err_t macb_eth_common_remove(struct macb_eth *eth);

#ifdef RT_ETHERNET_CADENCE_PTP
rt_err_t macb_ptp_register(struct macb_eth *eth);
void macb_ptp_unregister(struct macb_eth *eth);
#endif

#endif /* __MACB_H__ */
