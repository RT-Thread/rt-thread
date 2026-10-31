/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "r8125.h"

#define DBG_TAG "eth.r8125"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define ETH_ZLEN                60
#define ETH_FCS_LEN             4

struct r8125_chip_info
{
    const char *name;
    rt_uint8_t mcfg;
    rt_uint32_t rx_config;
};

static const struct r8125_chip_info r8125_chips[] =
{
    { "RTL8125A",  R8125_CFG_8125A_2,  R8125_RX_FETCH_8 | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8125A",  R8125_CFG_8125A_3,  R8125_RX_FETCH_8 | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8125B",  R8125_CFG_8125B_4,  R8125_RX_FETCH_8 | R8125_RX_PAUSE_SLOT | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8125B",  R8125_CFG_8125B_5,  R8125_RX_FETCH_8 | R8125_RX_PAUSE_SLOT | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8168KB", R8125_CFG_8168KB_6, R8125_RX_FETCH_8 | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8168KB", R8125_CFG_8168KB_7, R8125_RX_FETCH_8 | R8125_RX_PAUSE_SLOT | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8125BP", R8125_CFG_8125BP_8, R8125_RX_FETCH_8 | R8125_RX_CLOSE_MULTI | R8125_RX_PAUSE_SLOT | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8125BP", R8125_CFG_8125BP_9, R8125_RX_FETCH_8 | R8125_RX_CLOSE_MULTI | R8125_RX_PAUSE_SLOT | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8125D",  R8125_CFG_8125D_10, R8125_RX_FETCH_8 | R8125_RX_CLOSE_MULTI | R8125_RX_PAUSE_SLOT | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8125D",  R8125_CFG_8125D_11, R8125_RX_FETCH_8 | R8125_RX_CLOSE_MULTI | R8125_RX_PAUSE_SLOT | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8125CP", R8125_CFG_8125CP_12, R8125_RX_FETCH_8 | R8125_RX_CLOSE_MULTI | R8125_RX_PAUSE_SLOT | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "RTL8168KD", R8125_CFG_8168KD_13, R8125_RX_FETCH_8 | R8125_RX_CLOSE_MULTI | R8125_RX_PAUSE_SLOT | R8125_RX_INNER_VLAN | R8125_RX_OUTER_VLAN | (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
    { "Unknown",   R8125_CFG_DEFAULT,  (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT) },
};

/* --- MMIO helpers --- */

void r8125_mac_ocp_write(struct r8125_eth *eth, rt_uint16_t reg, rt_uint16_t val)
{
    rt_uint32_t data;

    data = (reg / 2) << R8125_OCP_ADDR_SHIFT;
    data |= val;
    data |= R8125_OCP_WRITE;
    RTL_W32(eth, R8125_MACOCP, data);

    for (int i = 0; i < 1000; ++i)
    {
        rt_hw_us_delay(10);
        if (!(RTL_R32(eth, R8125_MACOCP) & R8125_OCP_WRITE))
        {
            break;
        }
    }
}

rt_uint16_t r8125_mac_ocp_read(struct r8125_eth *eth, rt_uint16_t reg)
{
    rt_uint32_t data;

    data = (reg / 2) << R8125_OCP_ADDR_SHIFT;
    RTL_W32(eth, R8125_MACOCP, data);

    for (int i = 0; i < 1000; ++i)
    {
        rt_hw_us_delay(10);
        if (RTL_R32(eth, R8125_MACOCP) & R8125_OCP_WRITE)
        {
            break;
        }
    }

    return (rt_uint16_t)RTL_R32(eth, R8125_MACOCP);
}

void r8125_phy_ocp_write(struct r8125_eth *eth, rt_uint16_t reg, rt_uint16_t val)
{
    rt_uint32_t data;

    data = (reg / 2) << R8125_OCP_ADDR_SHIFT;
    data |= R8125_OCP_WRITE | val;

    RTL_W32(eth, R8125_PHYOCP, data);
    for (int i = 0; i < 1000; i++)
    {
        rt_hw_us_delay(10);
        if (!(RTL_R32(eth, R8125_PHYOCP) & R8125_OCP_WRITE))
        {
            break;
        }
    }
}

rt_uint16_t r8125_phy_ocp_read(struct r8125_eth *eth, rt_uint16_t reg)
{
    rt_uint32_t data;

    data = (reg / 2) << R8125_OCP_ADDR_SHIFT;

    RTL_W32(eth, R8125_PHYOCP, data);
    for (int i = 0; i < 1000; ++i)
    {
        rt_hw_us_delay(10);
        if (RTL_R32(eth, R8125_PHYOCP) & R8125_OCP_WRITE)
        {
            break;
        }
    }

    return (rt_uint16_t)(RTL_R32(eth, R8125_PHYOCP) & 0xffff);
}

void r8125_phy_ocp_update_bits(struct r8125_eth *eth, rt_uint16_t reg,
        rt_uint16_t clear, rt_uint16_t set)
{
    rt_uint16_t val;

    val = r8125_phy_ocp_read(eth, reg);
    val &= ~clear;
    val |= set;
    r8125_phy_ocp_write(eth, reg, val);
}

void r8125_phy_ocp_set_bits(struct r8125_eth *eth, rt_uint16_t reg, rt_uint16_t mask)
{
    r8125_phy_ocp_update_bits(eth, reg, 0, mask);
}

void r8125_phy_ocp_clear_bits(struct r8125_eth *eth, rt_uint16_t reg, rt_uint16_t mask)
{
    r8125_phy_ocp_update_bits(eth, reg, mask, 0);
}

static void r8125_cfg9346_unlock(struct r8125_eth *eth)
{
    RTL_W8(eth, R8125_CFG9346, R8125_CFG9346_UNLOCK);
}

static void r8125_cfg9346_lock(struct r8125_eth *eth)
{
    RTL_W8(eth, R8125_CFG9346, R8125_CFG9346_LOCK);
}

static void r8125_intr_mask(struct r8125_eth *eth)
{
    RTL_W32(eth, R8125_INTR_MASK, 0);
}

static void r8125_select_legacy_interrupt(struct r8125_eth *eth)
{
    if (eth->mcfg >= R8125_CFG_8125B_4)
    {
        /*
         * Use the RTL8125 v1 IMR0/ISR0 interface for the single INTx vector.
         * These remain 32-bit registers, unlike the RTL8168 interface.
         */
        RTL_W8(eth, R8125_INT_CFG0,
               RTL_R8(eth, R8125_INT_CFG0) & ~R8125_INT_CFG0_ENABLE);
    }
}

static void r8125_intr_unmask(struct r8125_eth *eth)
{
    RTL_W32(eth, R8125_INTR_MASK, eth->intr_mask);
}

static void r8125_intr_ack_all(struct r8125_eth *eth)
{
    RTL_W32(eth, R8125_INTR_STATUS, 0xffffffff);
}

static void r8125_mdio_write(struct r8125_eth *eth, rt_uint16_t reg, rt_uint16_t val)
{
    if (reg == R8125_MII_PAGE)
    {
        eth->cur_page = val;
        return;
    }

    RTL_W32(eth, R8125_PHYAR, R8125_PHYAR_WRITE | ((reg & 0x1f) << 16) | val);
    for (int i = 0; i < 1000; ++i)
    {
        rt_hw_us_delay(10);
        if (RTL_R32(eth, R8125_PHYAR) & R8125_PHYAR_FLAG)
        {
            continue;
        }
        break;
    }
}

static rt_uint16_t r8125_mdio_read(struct r8125_eth *eth, rt_uint16_t reg)
{
    RTL_W32(eth, R8125_PHYAR, (reg & 0x1f) << 16);
    for (int i = 0; i < 1000; ++i)
    {
        rt_hw_us_delay(10);
        if (!(RTL_R32(eth, R8125_PHYAR) & R8125_PHYAR_FLAG))
        {
            break;
        }
    }

    return (rt_uint16_t)(RTL_R32(eth, R8125_PHYAR) & 0xffff);
}

/* --- Chip detect --- */
static void r8125_detect_chip(struct r8125_eth *eth)
{
    rt_uint32_t txcfg = RTL_R32(eth, R8125_TX_CFG);
    rt_uint32_t reg = txcfg & 0x7c800000;
    rt_uint32_t ic = txcfg & 0x00700000;
    rt_uint16_t devid;

    eth->ic_ver_unknown = RT_FALSE;

    switch (reg)
    {
    case 0x60800000:
        eth->mcfg = (ic == 0) ? R8125_CFG_8125A_2 : R8125_CFG_8125A_3;
        if (ic != 0 && ic != 0x100000)
        {
            eth->ic_ver_unknown = RT_TRUE;
        }
        break;
    case 0x64000000:
        eth->mcfg = (ic == 0) ? R8125_CFG_8125B_4 : R8125_CFG_8125B_5;
        if (ic != 0 && ic != 0x100000)
        {
            eth->ic_ver_unknown = RT_TRUE;
        }
        break;
    case 0x68000000:
        eth->mcfg = (ic == 0) ? R8125_CFG_8125BP_8 : R8125_CFG_8125BP_9;
        if (ic != 0 && ic != 0x100000)
        {
            eth->ic_ver_unknown = RT_TRUE;
        }
        break;
    case 0x68800000:
        eth->mcfg = (ic == 0) ? R8125_CFG_8125D_10 : R8125_CFG_8125D_11;
        if (ic != 0 && ic != 0x100000)
        {
            eth->ic_ver_unknown = RT_TRUE;
        }
        break;
    case 0x70800000:
        eth->mcfg = R8125_CFG_8125CP_12;
        if (ic != 0)
        {
            eth->ic_ver_unknown = RT_TRUE;
        }
        break;
    default:
        eth->mcfg = R8125_CFG_DEFAULT;
        eth->ic_ver_unknown = RT_TRUE;
        LOG_W("Unknown TxConfig chip version 0x%08x", reg);
        break;
    }

    rt_pci_read_config_u16(eth->pdev, 0x02, &devid);
    if (devid == 0x8162)
    {
        if (eth->mcfg == R8125_CFG_8125A_3)
        {
            eth->mcfg = R8125_CFG_8168KB_6;
        }
        else if (eth->mcfg == R8125_CFG_8125B_5)
        {
            eth->mcfg = R8125_CFG_8168KB_7;
        }
        else if (eth->mcfg == R8125_CFG_8125D_11)
        {
            eth->mcfg = R8125_CFG_8168KD_13;
        }
    }

    eth->chip_name = r8125_chips[RT_ARRAY_SIZE(r8125_chips) - 1].name;
    eth->rx_config = r8125_chips[RT_ARRAY_SIZE(r8125_chips) - 1].rx_config;

    for (int i = 0; i < (int)RT_ARRAY_SIZE(r8125_chips); ++i)
    {
        if (r8125_chips[i].mcfg == eth->mcfg)
        {
            eth->chip_name = r8125_chips[i].name;
            eth->rx_config = r8125_chips[i].rx_config;
            break;
        }
    }

#ifdef RT_REALTEK_PTP
    eth->ptp_ver = R8125_PTP_NONE;
    switch (eth->mcfg)
    {
    case R8125_CFG_8125B_4:
    case R8125_CFG_8125B_5:
    case R8125_CFG_8168KB_7:
        eth->ptp_ver = R8125_PTP_MAC;
        break;
    case R8125_CFG_8125D_10:
    case R8125_CFG_8125D_11:
    case R8125_CFG_8125CP_12:
    case R8125_CFG_8168KD_13:
        eth->ptp_ver = R8125_PTP_PHY;
        break;
    default:
        break;
    }
#endif /* RT_REALTEK_PTP */

    LOG_D("%s mcfg=%u%s", eth->chip_name, eth->mcfg, eth->ic_ver_unknown ? " (IC ver unknown)" : "");
}

/* --- Reset / MAC --- */
static void r8125_soft_reset(struct r8125_eth *eth)
{
    RTL_W8(eth, R8125_CHIP_CMD, R8125_CMD_RESET);
    for (int i = 100; i > 0; --i)
    {
        rt_hw_us_delay(100);
        if ((RTL_R8(eth, R8125_CHIP_CMD) & R8125_CMD_RESET) == 0)
        {
            break;
        }
    }

    RTL_W32(eth, R8125_RX_CFG, (R8125_RX_DMA_256 << R8125_RX_DMA_SHIFT));
}

static void r8125_read_mac(struct r8125_eth *eth)
{
    for (int i = 0; i < 6; ++i)
    {
        eth->mac[i] = RTL_R8(eth, R8125_MAC0 + i);
    }

    if ((eth->mac[0] & 0x01) ||
        (eth->mac[0] == 0xff && eth->mac[1] == 0xff && eth->mac[2] == 0xff) ||
        (eth->mac[0] == 0x00 && eth->mac[1] == 0x00 && eth->mac[2] == 0x00 &&
         eth->mac[3] == 0x00 && eth->mac[4] == 0x00 && eth->mac[5] == 0x00))
    {
        ethernet_random_addr(&eth->parent, eth->mac);
    }
}

static void r8125_set_mac(struct r8125_eth *eth)
{
    rt_uint32_t low = (rt_uint32_t)eth->mac[0] |
                     ((rt_uint32_t)eth->mac[1] << 8) |
                     ((rt_uint32_t)eth->mac[2] << 16) |
                     ((rt_uint32_t)eth->mac[3] << 24);
    rt_uint32_t high = (rt_uint32_t)eth->mac[4] |
                      ((rt_uint32_t)eth->mac[5] << 8);

    r8125_cfg9346_unlock(eth);
    RTL_W32(eth, R8125_MAC0, low);
    RTL_W32(eth, R8125_MAC0 + 4, high);
    r8125_cfg9346_lock(eth);
}

static void r8125_set_rx_filter(struct r8125_eth *eth)
{
    rt_uint32_t rx_mode = R8125_RX_ACCEPT_BCAST | R8125_RX_ACCEPT_MY_PHYS;
    rt_uint32_t tmp;

    tmp = eth->rx_config | rx_mode;
    RTL_W32(eth, R8125_RX_CFG, tmp);
    RTL_W32(eth, R8125_MAR0, 0xffffffff);
    RTL_W32(eth, R8125_MAR0 + 4, 0xffffffff);
}

static rt_bool_t r8125_rx_pending(struct r8125_eth *eth)
{
    struct r8125_rx_desc *d = &eth->rx_ring[eth->rx_tail];

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, d, sizeof(*d));

    return (rt_le32_to_cpu(d->opts1) & R8125_DESC_OWN) ? RT_FALSE : RT_TRUE;
}

/* --- Minimal 8125B-class hardware setup --- */
static void r8125_hw_setup_modern(struct r8125_eth *eth)
{
    rt_uint16_t val;

    /* Only queue zero has a descriptor ring in this driver. */
    RTL_W32(eth, R8125_RSS_CTRL, 0);
    RTL_W16(eth, R8125_Q_NUM_CTRL,
            RTL_R16(eth, R8125_Q_NUM_CTRL) & ~(0x07 << 2));

    if (eth->mcfg < R8125_CFG_8125B_4)
    {
        return;
    }

    /* Enable MAC MCU (firmware may already be in chip ROM) */
    r8125_mac_ocp_write(eth, 0xC0B4, r8125_mac_ocp_read(eth, 0xC0B4) & ~0x01);
    r8125_mac_ocp_write(eth, 0xC0B4, r8125_mac_ocp_read(eth, 0xC0B4) | 0x01);

    val = r8125_mac_ocp_read(eth, 0xEB58);
    r8125_mac_ocp_write(eth, 0xEB58, val | 0x01);

    val = r8125_mac_ocp_read(eth, 0xE614);
    val = (val & ~(0x07 << 8)) | (2 << 8);
    r8125_mac_ocp_write(eth, 0xE614, val);

    val = r8125_mac_ocp_read(eth, 0xE63E);
    val = (val & ~(0x03 << 10)) | (0 << 10);
    r8125_mac_ocp_write(eth, 0xE63E, val);

    val = r8125_mac_ocp_read(eth, 0xE63E);
    val = (val & ~(0x03 << 4)) | (0x02 << 4);
    r8125_mac_ocp_write(eth, 0xE63E, val);

    r8125_mac_ocp_write(eth, 0xE0C0, 0x4000);
}

static void r8125_phy_autoneg(struct r8125_eth *eth)
{
    rt_uint16_t adv2500;

    eth->cur_page = 0;
    r8125_mdio_write(eth, R8125_MII_BMCR, R8125_BMCR_RESET | R8125_BMCR_ANENABLE);

    for (int i = 0; i < 100; ++i)
    {
        if (!(r8125_mdio_read(eth, R8125_MII_BMCR) & R8125_BMCR_RESET))
        {
            break;
        }
        rt_hw_us_delay(100);
    }

    r8125_mdio_write(eth, R8125_MII_ADVERTISE, R8125_ADVERTISE_ALL);
    r8125_mdio_write(eth, R8125_MII_CTRL1000, R8125_ADVERTISE_1000FULL);

    adv2500 = r8125_phy_ocp_read(eth, 0xA5D4);
    adv2500 |= R8125_OCP_ADVERT_2500;
    r8125_phy_ocp_write(eth, 0xA5D4, adv2500);

    r8125_mdio_write(eth, R8125_MII_BMCR, R8125_BMCR_ANENABLE | R8125_BMCR_ANRESTART);
}

static rt_bool_t r8125_update_link(struct r8125_eth *eth)
{
    rt_bool_t up;
    rt_uint32_t status = RTL_R32(eth, R8125_PHY_STATUS);

    if (status == 0xffffffff)
    {
        return eth->link_up;
    }

    up = (status & R8125_PHY_LINK) ? RT_TRUE : RT_FALSE;
    if (up != eth->link_up)
    {
        eth->link_up = up;
        /* eth_device_init() creates parent.netif after MAC setup. */
        if (eth->net_registered)
        {
            eth_device_linkchange(&eth->parent, up);
        }
    }

    return up;
}

/* --- Descriptor rings --- */

static rt_size_t r8125_ring_bytes(void)
{
    rt_size_t tx_ring = RT_ALIGN(sizeof(struct r8125_tx_desc) * R8125_TX_RING_SIZE, R8125_DESC_ALIGN);
    rt_size_t rx_ring = RT_ALIGN(sizeof(struct r8125_rx_desc) * R8125_RX_RING_SIZE, R8125_DESC_ALIGN);
    rt_size_t tx_buf = R8125_TX_RING_SIZE * R8125_RX_BUFFER_SIZE;
    rt_size_t rx_buf = R8125_RX_RING_SIZE * R8125_RX_BUFFER_SIZE;

    return tx_ring + rx_ring + tx_buf + rx_buf;
}

static void r8125_rx_refill(struct r8125_eth *eth, rt_uint32_t idx)
{
    struct r8125_rx_desc *d = &eth->rx_ring[idx];
    rt_uint32_t opts1 = R8125_DESC_OWN | R8125_RX_BUFFER_SIZE;

    if (idx == R8125_RX_RING_SIZE - 1)
    {
        opts1 |= R8125_DESC_RING_END;
    }

    d->opts2 = 0;
    d->addr = rt_cpu_to_le64((rt_uint64_t)(eth->rx_bufs_dma + idx * R8125_RX_BUFFER_SIZE));
    rt_hw_wmb();
    d->opts1 = rt_cpu_to_le32(opts1);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, d, sizeof(*d));
}

static rt_err_t r8125_alloc_rings(struct r8125_eth *eth)
{
    rt_size_t tx_ring_sz = RT_ALIGN(sizeof(struct r8125_tx_desc) * R8125_TX_RING_SIZE, R8125_DESC_ALIGN);
    rt_size_t rx_ring_sz = RT_ALIGN(sizeof(struct r8125_rx_desc) * R8125_RX_RING_SIZE, R8125_DESC_ALIGN);
    rt_size_t tx_buf_sz = R8125_TX_RING_SIZE * R8125_RX_BUFFER_SIZE;
    rt_uint8_t *blob;
    rt_ubase_t dma;

    eth->dma_blob_size = r8125_ring_bytes();
    eth->dma_blob_handle = 0;

    blob = rt_dma_alloc_coherent(&eth->pdev->parent, eth->dma_blob_size, &dma);
    if (!blob)
    {
        return -RT_ENOMEM;
    }

    eth->dma_blob_handle = dma;
    eth->tx_ring = (struct r8125_tx_desc *)blob;
    eth->tx_ring_dma = dma;
    blob += tx_ring_sz;
    dma += tx_ring_sz;

    eth->rx_ring = (struct r8125_rx_desc *)blob;
    eth->rx_ring_dma = dma;
    blob += rx_ring_sz;
    dma += rx_ring_sz;

    eth->tx_bufs = blob;
    eth->tx_bufs_dma = dma;
    blob += tx_buf_sz;
    dma += tx_buf_sz;

    eth->rx_bufs = blob;
    eth->rx_bufs_dma = dma;

    rt_memset(eth->tx_ring, 0, tx_ring_sz);
    rt_memset(eth->rx_ring, 0, rx_ring_sz);

    eth->tx_ring[R8125_TX_RING_SIZE - 1].opts1 = rt_cpu_to_le32(R8125_DESC_RING_END);
    eth->tx_head = 0;
    eth->tx_tail = 0;
    eth->tx_queued = 0;
    eth->rx_tail = 0;

    for (int i = 0; i < R8125_RX_RING_SIZE; ++i)
    {
        r8125_rx_refill(eth, i);
    }

    return RT_EOK;
}

static void r8125_free_rings(struct r8125_eth *eth)
{
    if (eth->tx_ring)
    {
        rt_dma_free_coherent(&eth->pdev->parent, eth->dma_blob_size,
                             eth->tx_ring, eth->dma_blob_handle);
        eth->tx_ring = RT_NULL;
        eth->rx_ring = RT_NULL;
        eth->tx_bufs = RT_NULL;
        eth->rx_bufs = RT_NULL;
        eth->dma_blob_size = 0;
        eth->dma_blob_handle = 0;
        eth->tx_ring_dma = 0;
        eth->rx_ring_dma = 0;
        eth->tx_bufs_dma = 0;
        eth->rx_bufs_dma = 0;
        eth->tx_head = 0;
        eth->tx_tail = 0;
        eth->tx_queued = 0;
        eth->rx_tail = 0;
    }
}

static void r8125_tx_cleanup(struct r8125_eth *eth)
{
    rt_uint32_t reclaimed = 0;
    rt_ubase_t level = rt_spin_lock_irqsave(&eth->tx_lock);

    while (eth->tx_queued)
    {
        rt_uint32_t opts1;
        struct r8125_tx_desc *d = &eth->tx_ring[eth->tx_tail];

        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, d, sizeof(*d));
        opts1 = rt_le32_to_cpu(d->opts1);
        if (opts1 & R8125_DESC_OWN)
        {
            break;
        }

        d->opts1 = rt_cpu_to_le32((eth->tx_tail == R8125_TX_RING_SIZE - 1) ?
                                  R8125_DESC_RING_END : 0);
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, d, sizeof(*d));

        eth->tx_tail = R8125_NEXT_TX(eth->tx_tail);
        eth->tx_queued--;
        reclaimed++;
    }
    rt_spin_unlock_irqrestore(&eth->tx_lock, level);

    while (reclaimed)
    {
        rt_sem_release(&eth->tx_free);
        reclaimed--;
    }
}

static rt_err_t r8125_tx_wait_free(struct r8125_eth *eth)
{
    rt_tick_t deadline = rt_tick_get() + R8125_TX_TIMEOUT_TICK;

    while (rt_tick_get() < deadline)
    {
        r8125_tx_cleanup(eth);
        if (rt_sem_take(&eth->tx_free, 1) == RT_EOK)
        {
            return RT_EOK;
        }
    }

    r8125_tx_cleanup(eth);

    return rt_sem_take(&eth->tx_free, 0);
}

static void r8125_program_desc_addr(struct r8125_eth *eth)
{
    RTL_W32(eth, R8125_TX_DESC_LO, (rt_uint32_t)eth->tx_ring_dma);
    RTL_W32(eth, R8125_TX_DESC_HI, (rt_uint32_t)(eth->tx_ring_dma >> 32));
    RTL_W32(eth, R8125_RX_DESC_LO, (rt_uint32_t)eth->rx_ring_dma);
    RTL_W32(eth, R8125_RX_DESC_HI, (rt_uint32_t)(eth->rx_ring_dma >> 32));
}

/* --- Hardware init / stop --- */

rt_err_t r8125_eth_hw_init(struct r8125_eth *eth)
{
    rt_err_t err;
    rt_uint32_t txcfg;

    eth->intr_mask = R8125_INTR_DEFAULT;

    r8125_soft_reset(eth);
    r8125_detect_chip(eth);
    r8125_read_mac(eth);

    err = r8125_alloc_rings(eth);
    if (err)
    {
        return err;
    }

    r8125_cfg9346_unlock(eth);

    r8125_hw_setup_modern(eth);
    r8125_select_legacy_interrupt(eth);

    txcfg = (R8125_TX_DMA_UNLIMITED << R8125_TX_DMA_SHIFT) |
            (R8125_TX_IFG_DEFAULT << R8125_TX_IFG_SHIFT);
    RTL_W32(eth, R8125_TX_CFG, txcfg);

    RTL_W16(eth, R8125_RX_MAX_SIZE, R8125_RX_BUFFER_SIZE);
    RTL_W16(eth, R8125_CPLUS_CMD, R8125_CPLUS_NORMAL | R8125_CPLUS_RX_CSUM);

    r8125_program_desc_addr(eth);
    r8125_set_mac(eth);
    r8125_set_rx_filter(eth);

    r8125_phy_autoneg(eth);
    r8125_update_link(eth);

    r8125_intr_mask(eth);
    r8125_intr_ack_all(eth);

    RTL_W8(eth, R8125_CHIP_CMD, R8125_CMD_TX_EN | R8125_CMD_RX_EN);

    r8125_cfg9346_lock(eth);

    LOG_D("%s %02x:%02x:%02x:%02x:%02x:%02x",
          eth->chip_name,
          eth->mac[0], eth->mac[1], eth->mac[2],
          eth->mac[3], eth->mac[4], eth->mac[5]);

    return RT_EOK;
}

void r8125_eth_hw_stop(struct r8125_eth *eth)
{
    r8125_intr_mask(eth);
    r8125_intr_ack_all(eth);
    RTL_W8(eth, R8125_CHIP_CMD, 0);
    r8125_free_rings(eth);
}

/* --- TX / RX --- */
static rt_err_t r8125_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct r8125_eth *eth = raw_to_r8125_eth(dev);
    struct r8125_tx_desc *d;
    rt_uint32_t idx, len, opts1;
    rt_ubase_t level;
    rt_uint8_t *buf;

    if (!p || p->tot_len > R8125_RX_BUFFER_SIZE)
    {
        return -RT_EINVAL;
    }

    if (!eth->link_up)
    {
        return -RT_ERROR;
    }

    r8125_tx_cleanup(eth);

    if (r8125_tx_wait_free(eth) != RT_EOK)
    {
        return -RT_ETIMEOUT;
    }

    if (rt_sem_take(&eth->tx_sem, RT_WAITING_FOREVER) != RT_EOK)
    {
        rt_sem_release(&eth->tx_free);
        return -RT_EBUSY;
    }

    idx = eth->tx_head;
    d = &eth->tx_ring[idx];
    buf = eth->tx_bufs + idx * R8125_RX_BUFFER_SIZE;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, d, sizeof(*d));
    if (rt_le32_to_cpu(d->opts1) & R8125_DESC_OWN)
    {
        rt_sem_release(&eth->tx_sem);
        rt_sem_release(&eth->tx_free);
        return -RT_EBUSY;
    }

    len = p->tot_len;
    pbuf_copy_partial(p, buf, len, 0);
    if (len < ETH_ZLEN)
    {
        rt_memset(buf + len, 0, ETH_ZLEN - len);
    }
    len = len < ETH_ZLEN ? ETH_ZLEN : len;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, buf, len);

    opts1 = R8125_DESC_OWN | R8125_DESC_FIRST_FRAG | R8125_DESC_LAST_FRAG | len;
    if (idx == R8125_TX_RING_SIZE - 1)
    {
        opts1 |= R8125_DESC_RING_END;
    }

    /* Publish descriptor ownership and queue state atomically against reclaim. */
    level = rt_spin_lock_irqsave(&eth->tx_lock);
    d->opts2 = 0;
    d->addr = rt_cpu_to_le64((rt_uint64_t)(eth->tx_bufs_dma + idx * R8125_RX_BUFFER_SIZE));
    rt_hw_wmb();
    d->opts1 = rt_cpu_to_le32(opts1);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, d, sizeof(*d));

    eth->tx_head = R8125_NEXT_TX(idx);
    eth->tx_queued++;
    RTL_W16(eth, R8125_TPPOLL_8125, 0x0001);
    rt_spin_unlock_irqrestore(&eth->tx_lock, level);

    rt_sem_release(&eth->tx_sem);

    return RT_EOK;
}

static struct pbuf *r8125_eth_rx(rt_device_t dev)
{
    rt_uint8_t *buf;
    rt_uint32_t status, len;
    struct pbuf *p = RT_NULL;
    struct r8125_rx_desc *d;
    struct r8125_eth *eth = raw_to_r8125_eth(dev);

    r8125_tx_cleanup(eth);
    r8125_update_link(eth);

    d = &eth->rx_ring[eth->rx_tail];
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, d, sizeof(*d));
    status = rt_le32_to_cpu(d->opts1);

    if (status & R8125_DESC_OWN)
    {
        return RT_NULL;
    }

    if (status & (R8125_RX_RES | R8125_RX_RWT | R8125_RX_RUNT | R8125_RX_CRC))
    {
        r8125_rx_refill(eth, eth->rx_tail);
        eth->rx_tail = R8125_NEXT_RX(eth->rx_tail);
        return RT_NULL;
    }

    len = status & 0x3fff;
    if (len < ETH_FCS_LEN || len > R8125_RX_BUFFER_SIZE)
    {
        goto _done;
    }

    len -= ETH_FCS_LEN;

    p = pbuf_alloc(PBUF_RAW, (rt_uint16_t)len, PBUF_RAM);
    if (p)
    {
        buf = eth->rx_bufs + eth->rx_tail * R8125_RX_BUFFER_SIZE;
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, buf, len);
        pbuf_take(p, buf, len);
    }

_done:
    r8125_rx_refill(eth, eth->rx_tail);
    eth->rx_tail = R8125_NEXT_RX(eth->rx_tail);
    return p;
}

static rt_err_t r8125_eth_control(rt_device_t dev, int cmd, void *args)
{
    struct r8125_eth *eth = raw_to_r8125_eth(dev);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args)
        {
            rt_memcpy(args, eth->mac, 6);
            return RT_EOK;
        }
        return -RT_EINVAL;
    default:
        return -RT_EINVAL;
    }
}

static void r8125_eth_isr(int irq, void *param)
{
    rt_uint32_t status;
    struct r8125_eth *eth = param;

    status = RTL_R32(eth, R8125_INTR_STATUS);
    if (!status || status == 0xffffffff)
    {
        return;
    }

    RTL_W32(eth, R8125_INTR_STATUS, status);

    if (status & R8125_INTR_LINKCHG)
    {
        r8125_update_link(eth);
    }

    if (status & (R8125_INTR_TXOK | R8125_INTR_TXERR))
    {
        r8125_tx_cleanup(eth);
    }

    if (status & (R8125_INTR_RXOK | R8125_INTR_RXDU | R8125_INTR_RXERR))
    {
        if (r8125_rx_pending(eth))
        {
            eth_device_ready(&eth->parent);
        }
    }
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops r8125_eth_ops =
{
    .control = r8125_eth_control,
};
#endif

rt_err_t r8125_eth_common_probe(struct r8125_eth *eth)
{
    rt_err_t err;

#ifdef RT_USING_DEVICE_OPS
    eth->parent.parent.ops = &r8125_eth_ops;
#else
    eth->parent.parent.control = r8125_eth_control;
#endif
    eth->parent.eth_tx = r8125_eth_tx;
    eth->parent.eth_rx = r8125_eth_rx;

    if ((err = rt_dm_dev_set_name_auto(&eth->parent.parent, "e")) < 0)
    {
        return err;
    }

    if ((err = eth_device_init(&eth->parent, rt_dm_dev_get_name(&eth->parent.parent))))
    {
        return err;
    }

    eth->net_registered = RT_TRUE;

    if (eth->irq >= 0)
    {
        rt_hw_interrupt_install(eth->irq, r8125_eth_isr, eth, "r8125");
        r8125_intr_ack_all(eth);
        rt_hw_interrupt_umask(eth->irq);
        eth->irq_installed = RT_TRUE;
        r8125_intr_unmask(eth);
    }

    eth_device_linkchange(&eth->parent, eth->link_up);

#ifdef RT_REALTEK_PTP
    if ((err = rtl8125_ptp_register(eth)))
    {
        LOG_W("PTP register failed: %s", rt_strerror(err));
    }
#endif

    return RT_EOK;
}

rt_err_t r8125_eth_common_remove(struct r8125_eth *eth)
{
#ifdef RT_REALTEK_PTP
    rtl8125_ptp_unregister(eth);
#endif

    if (eth->net_registered)
    {
        eth_device_linkchange(&eth->parent, RT_FALSE);
        eth_device_deinit(&eth->parent);
        eth->net_registered = RT_FALSE;
    }

    if (eth->irq_installed)
    {
        r8125_intr_mask(eth);
        rt_hw_interrupt_mask(eth->irq);
        eth->irq_installed = RT_FALSE;
    }
    r8125_eth_hw_stop(eth);
    rt_sem_detach(&eth->tx_sem);
    rt_sem_detach(&eth->tx_free);

    return RT_EOK;
}

static const struct rt_pci_device_id r8125_pci_ids[] =
{
    { RT_PCI_DEVICE_ID(0x10ec, 0x8125), },
    { RT_PCI_DEVICE_ID(0x10ec, 0x8162), },
    { RT_PCI_DEVICE_ID(0x10ec, 0x3000), },
    { /* sentinel */ }
};

static rt_err_t r8125_pci_probe(struct rt_pci_device *pdev)
{
    rt_err_t err;
    struct r8125_eth *eth;

    if (pdev->resource[R8125_PCI_MMIO_BAR].size < R8125_REGS_SIZE)
    {
        return -RT_ERROR;
    }

    eth = rt_calloc(1, sizeof(*eth));
    if (!eth)
    {
        return -RT_ENOMEM;
    }

    eth->pdev = pdev;
    eth->irq = pdev->irq;
    rt_spin_lock_init(&eth->tx_lock);
    rt_sem_init(&eth->tx_sem, "r8125tx", 1, RT_IPC_FLAG_PRIO);
    rt_sem_init(&eth->tx_free, "r8125tf", R8125_TX_RING_SIZE, RT_IPC_FLAG_PRIO);
#ifdef RT_REALTEK_PTP
    rt_mutex_init(&eth->ptp_lock, "r8125ptp", RT_IPC_FLAG_PRIO);
#endif

    rt_pci_set_master(pdev);
    rt_pci_irq_unmask(pdev);
    LOG_D("using legacy INTx irq=%d", eth->irq);

    eth->regs = rt_pci_iomap(pdev, R8125_PCI_MMIO_BAR);
    if (!eth->regs)
    {
        err = -RT_EIO;
        goto _err_free;
    }

    LOG_D("MMIO mapped at %p", eth->regs);

    if ((err = r8125_eth_hw_init(eth)))
    {
        goto _err_unmap;
    }

    pdev->parent.user_data = eth;

    if ((err = r8125_eth_common_probe(eth)))
    {
        r8125_eth_hw_stop(eth);
        goto _err_unmap;
    }

    return RT_EOK;

_err_unmap:
    pdev->parent.user_data = RT_NULL;
    rt_iounmap(eth->regs);

_err_free:
#ifdef RT_REALTEK_PTP
    rt_mutex_detach(&eth->ptp_lock);
#endif
    rt_sem_detach(&eth->tx_sem);
    rt_sem_detach(&eth->tx_free);
    rt_free(eth);
    rt_pci_irq_mask(pdev);
    return err;
}

static rt_err_t r8125_pci_remove(struct rt_pci_device *pdev)
{
    struct r8125_eth *eth = pdev->parent.user_data;

    if (!eth)
    {
        return RT_EOK;
    }

    r8125_eth_common_remove(eth);
    rt_iounmap(eth->regs);
#ifdef RT_REALTEK_PTP
    rt_mutex_detach(&eth->ptp_lock);
#endif

    pdev->parent.user_data = RT_NULL;
    rt_pci_irq_mask(pdev);
    rt_pci_clear_master(pdev);
    rt_free(eth);

    return RT_EOK;
}

static struct rt_pci_driver r8125_pci_driver =
{
    .name = "r8125",
    .ids = r8125_pci_ids,
    .probe = r8125_pci_probe,
    .remove = r8125_pci_remove,
};
RT_PCI_DRIVER_EXPORT(r8125_pci_driver);
