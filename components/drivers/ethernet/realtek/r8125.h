/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#ifndef __R8125_H__
#define __R8125_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "../ethernet_dm.h"

#ifdef RT_REALTEK_PTP
#include <drivers/ptp.h>
#endif

/* --- Ring sizing --- */
#define R8125_RX_RING_SIZE      32
#define R8125_TX_RING_SIZE      16
#define R8125_RX_BUFFER_SIZE    1536
#define R8125_DESC_ALIGN        256
#ifdef RT_REALTEK_PTP
#define R8125_REGS_SIZE         0x6812
#else
#define R8125_REGS_SIZE         0x4802
#endif
#define R8125_PCI_MMIO_BAR      2
#define R8125_TX_TIMEOUT_TICK   (RT_TICK_PER_SECOND * 2)

#define R8125_NEXT_TX(i)        (((i) + 1) & (R8125_TX_RING_SIZE - 1))
#define R8125_NEXT_RX(i)        (((i) + 1) & (R8125_RX_RING_SIZE - 1))

/*
 * Chip variants — enum values match official r8125.h mcfg (9.016.01).
 */
enum r8125_mcfg
{
    R8125_CFG_8125A_2       = 2,
    R8125_CFG_8125A_3       = 3,
    R8125_CFG_8125B_4       = 4,
    R8125_CFG_8125B_5       = 5,
    R8125_CFG_8168KB_6      = 6,
    R8125_CFG_8168KB_7      = 7,
    R8125_CFG_8125BP_8      = 8,
    R8125_CFG_8125BP_9      = 9,
    R8125_CFG_8125D_10      = 10,
    R8125_CFG_8125D_11      = 11,
    R8125_CFG_8125CP_12     = 12,
    R8125_CFG_8168KD_13     = 13,
    R8125_CFG_DEFAULT       = 14,
};

/* --- MMIO registers (from official rtl8125_registers) --- */
enum r8125_reg
{
    R8125_MAC0               = 0x00,
    R8125_MAR0               = 0x08,
    R8125_TX_DESC_LO         = 0x20,
    R8125_TX_DESC_HI         = 0x24,
    R8125_INT_CFG0           = 0x34,
    R8125_CHIP_CMD           = 0x37,
    R8125_INTR_MASK          = 0x38,
    R8125_INTR_STATUS        = 0x3C,
    R8125_TX_CFG             = 0x40,
    R8125_RX_CFG             = 0x44,
    R8125_CFG9346            = 0x50,
    R8125_PHYAR              = 0x60,
    R8125_PHY_STATUS         = 0x6C,
    R8125_RX_MAX_SIZE        = 0xDA,
    R8125_CPLUS_CMD          = 0xE0,
    R8125_RX_DESC_LO         = 0xE4,
    R8125_RX_DESC_HI         = 0xE8,
    R8125_MACOCP             = 0xB0,
    R8125_PHYOCP             = 0xB8,
    R8125_TPPOLL_8125        = 0x90,
    R8125_RSS_CTRL           = 0x4500,
    R8125_Q_NUM_CTRL         = 0x4800,

    R8125_PTP_CTRL           = 0x6800,
    R8125_PTP_ISR            = 0x6804,
    R8125_PTP_TIME_CMD       = 0x6806,
    R8125_PTP_SOFT_NS        = 0x6808,
    R8125_PTP_SOFT_SEC       = 0x680C,
};

enum r8125_bits
{
    R8125_CMD_RESET          = 0x10,
    R8125_CMD_RX_EN          = 0x08,
    R8125_CMD_TX_EN          = 0x04,
    R8125_INT_CFG0_ENABLE    = 0x01,

    R8125_INTR_SYSE          = 0x8000,
    R8125_INTR_PCSTIMEOUT    = 0x4000,
    R8125_INTR_SWINT         = 0x0100,
    R8125_INTR_TXDU          = 0x0080,
    R8125_INTR_RXFIFO        = 0x0040,
    R8125_INTR_LINKCHG       = 0x0020,
    R8125_INTR_RXDU          = 0x0010,
    R8125_INTR_TXERR         = 0x0008,
    R8125_INTR_TXOK          = 0x0004,
    R8125_INTR_RXERR         = 0x0002,
    R8125_INTR_RXOK          = 0x0001,
    R8125_INTR_DEFAULT       = R8125_INTR_LINKCHG | R8125_INTR_RXDU |
                               R8125_INTR_TXOK | R8125_INTR_RXOK |
                               R8125_INTR_RXERR | R8125_INTR_TXERR,

    R8125_DESC_OWN           = (1 << 31),
    R8125_DESC_RING_END      = (1 << 30),
    R8125_DESC_FIRST_FRAG    = (1 << 29),
    R8125_DESC_LAST_FRAG     = (1 << 28),

    R8125_RX_RES             = (1 << 21),
    R8125_RX_CLOSE_MULTI     = (1 << 21),
    R8125_RX_RWT             = (1 << 22),
    R8125_RX_RUNT            = (1 << 20),
    R8125_RX_CRC             = (1 << 19),

    R8125_RX_ACCEPT_ERR      = 0x20,
    R8125_RX_ACCEPT_RUNT     = 0x10,
    R8125_RX_ACCEPT_BCAST    = 0x08,
    R8125_RX_ACCEPT_MCAST    = 0x04,
    R8125_RX_ACCEPT_MY_PHYS  = 0x02,
    R8125_RX_ACCEPT_ALL_PHYS = 0x01,

    R8125_PHY_LINK           = 0x02,
    R8125_PHY_FULL_DUP       = 0x01,
    R8125_PHY_2500_F         = 0x400,
    R8125_PHY_1000_F         = 0x10,
    R8125_PHY_100_BPS        = 0x08,
    R8125_PHY_10_BPS         = 0x04,

    R8125_CFG9346_UNLOCK     = 0xC0,
    R8125_CFG9346_LOCK       = 0x00,

    R8125_PHYAR_FLAG         = 0x80000000,
    R8125_PHYAR_WRITE        = 0x80000000,

    R8125_OCP_WRITE          = 0x80000000,
    R8125_OCP_ADDR_SHIFT     = 16,

    R8125_RX_DMA_SHIFT       = 8,
    R8125_RX_DMA_256         = 4,
    R8125_RX_FETCH_8         = (1 << 30),
    R8125_RX_PAUSE_SLOT      = (1 << 11),
    R8125_RX_INNER_VLAN      = (1 << 22),
    R8125_RX_OUTER_VLAN      = (1 << 23),

    R8125_TX_DMA_SHIFT       = 8,
    R8125_TX_DMA_UNLIMITED   = 7,
    R8125_TX_IFG_SHIFT       = 24,
    R8125_TX_IFG_DEFAULT     = 0x03,

    R8125_CPLUS_RX_CSUM      = (1 << 5),
    R8125_CPLUS_NORMAL       = (1 << 13),

    R8125_PTP_EXEC_CMD       = (1 << 7),
    R8125_PTP_CMD_SET_TIME   = 0,
    R8125_PTP_CMD_ADJ_TIME   = 1,
    R8125_PTP_CMD_LATCH_TIME = 2,
    R8125_PTP_NS_NEGATIVE    = (1 << 30),
};

/* MII (clause 22) */
#define R8125_MII_BMCR           0x00
#define R8125_MII_BMSR           0x01
#define R8125_MII_ADVERTISE      0x04
#define R8125_MII_CTRL1000       0x09
#define R8125_MII_PAGE           0x1f

#define R8125_BMCR_RESET         0x8000
#define R8125_BMCR_ANENABLE      0x1000
#define R8125_BMCR_ANRESTART     0x0200
#define R8125_BMSR_ANCOMP        0x0020
#define R8125_ADVERTISE_ALL      0x05e1
#define R8125_ADVERTISE_1000FULL 0x0200

/* 2.5G advertise (OCP PHY) -- RTK_ADVERTISE_2500FULL from official driver. */
#define R8125_OCP_ADVERT_2500    0x0080

enum r8125_ptp_version
{
    R8125_PTP_NONE = 0,
    R8125_PTP_MAC  = 1,
    R8125_PTP_PHY  = 3,
};

struct r8125_tx_desc
{
    rt_uint32_t opts1;
    rt_uint32_t opts2;
    rt_uint64_t addr;
    rt_uint32_t reserved0;
    rt_uint32_t reserved1;
    rt_uint32_t reserved2;
    rt_uint32_t reserved3;
};

struct r8125_rx_desc
{
    rt_uint32_t opts1;
    rt_uint32_t opts2;
    rt_uint64_t addr;
};

struct r8125_eth
{
    struct eth_device parent;

    struct rt_pci_device *pdev;
    void *regs;
    int irq;

    rt_uint8_t mac[6];
    rt_uint8_t mcfg;
    const char *chip_name;
    rt_uint32_t rx_config;
    rt_bool_t ic_ver_unknown;

    struct r8125_tx_desc *tx_ring;
    struct r8125_rx_desc *rx_ring;
    rt_uint8_t *tx_bufs;
    rt_uint8_t *rx_bufs;

    rt_size_t dma_blob_size;
    rt_ubase_t dma_blob_handle;
    rt_ubase_t tx_ring_dma;
    rt_ubase_t rx_ring_dma;
    rt_ubase_t tx_bufs_dma;
    rt_ubase_t rx_bufs_dma;

    rt_uint32_t tx_head;
    rt_uint32_t tx_tail;
    rt_uint32_t tx_queued;
    rt_uint32_t rx_tail;

    rt_uint16_t cur_page;
    rt_bool_t link_up;
    rt_bool_t net_registered;
    rt_bool_t irq_installed;
    rt_uint32_t intr_mask;

    struct rt_semaphore tx_sem;
    struct rt_semaphore tx_free;
    struct rt_spinlock tx_lock;

#ifdef RT_REALTEK_PTP
    struct rt_ptp_clock ptp_parent;
    struct rt_mutex ptp_lock;
    rt_uint8_t ptp_ver;
    rt_bool_t ptp_registered;
#endif
};

typedef struct r8125_eth rtl8125_private;

#define raw_to_r8125_eth(raw) \
    rt_container_of(rt_container_of(raw, struct eth_device, parent), struct r8125_eth, parent)

#define RTL_REG(eth, reg)       ((rt_ubase_t)(eth)->regs + (reg))
#define RTL_R8(eth, reg)        HWREG8(RTL_REG(eth, reg))
#define RTL_W8(eth, reg, val)   (HWREG8(RTL_REG(eth, reg)) = (val))
#define RTL_R16(eth, reg)       HWREG16(RTL_REG(eth, reg))
#define RTL_W16(eth, reg, val)  (HWREG16(RTL_REG(eth, reg)) = (val))
#define RTL_R32(eth, reg)       HWREG32(RTL_REG(eth, reg))
#define RTL_W32(eth, reg, val)  (HWREG32(RTL_REG(eth, reg)) = (val))

rt_err_t r8125_eth_hw_init(struct r8125_eth *eth);
void r8125_eth_hw_stop(struct r8125_eth *eth);
rt_err_t r8125_eth_common_probe(struct r8125_eth *eth);
rt_err_t r8125_eth_common_remove(struct r8125_eth *eth);

#ifdef RT_REALTEK_PTP
#define raw_to_r8125_ptp(raw) rt_container_of(raw, struct r8125_eth, ptp_parent)

void r8125_mac_ocp_write(struct r8125_eth *eth, rt_uint16_t reg, rt_uint16_t val);
rt_uint16_t r8125_mac_ocp_read(struct r8125_eth *eth, rt_uint16_t reg);
void r8125_phy_ocp_write(struct r8125_eth *eth, rt_uint16_t reg, rt_uint16_t val);
rt_uint16_t r8125_phy_ocp_read(struct r8125_eth *eth, rt_uint16_t reg);
void r8125_phy_ocp_set_bits(struct r8125_eth *eth, rt_uint16_t reg, rt_uint16_t mask);
void r8125_phy_ocp_clear_bits(struct r8125_eth *eth, rt_uint16_t reg, rt_uint16_t mask);
void r8125_phy_ocp_update_bits(struct r8125_eth *eth, rt_uint16_t reg,
        rt_uint16_t clear, rt_uint16_t set);

rt_err_t rtl8125_ptp_register(struct r8125_eth *eth);
void rtl8125_ptp_unregister(struct r8125_eth *eth);
void rtl8125_ptp_reset(struct r8125_eth *eth);
void rtl8125_ptp_suspend(struct r8125_eth *eth);
#endif

#endif /* __R8125_H__ */
