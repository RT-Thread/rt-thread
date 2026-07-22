/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include "dwmac.h"
#ifdef RT_ETHERNET_DWMAC_PTP
#include "dwmac_ptp.h"
#endif

#define DBG_TAG "eth.dwmac"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define NEXT_TX(i)                      (((i) + 1) & (DWMAC_TX_RING_SIZE - 1))
#define NEXT_RX(i)                      (((i) + 1) & (DWMAC_RX_RING_SIZE - 1))
#define ETH_ZLEN                        60
#define DWMAC_PHY_RETRY_INTERVAL_MS     2000
#define DWMAC_DMA_ALLOC_FLAGS           (RT_DMA_F_LINEAR | RT_DMA_F_32BITS)
#define DWMAC_DMA_ADDR_MAX              0xffffffffULL

static rt_err_t dwmac_poll_bit(struct dwmac_eth *eth, rt_uint32_t reg,
        rt_uint32_t mask, rt_bool_t wait_clear)
{
    rt_uint32_t val;
    rt_tick_t start = rt_tick_get();
    rt_tick_t timeout = rt_tick_from_millisecond(100);

    while (rt_tick_get() - start < timeout)
    {
        val = dwmac_readl(eth, reg);
        if (wait_clear ? !(val & mask) : (val & mask))
        {
            return RT_EOK;
        }
        rt_hw_us_delay(10);
    }

    return -RT_ETIMEOUT;
}

static rt_err_t dwmac_dma_reset(struct dwmac_eth *eth)
{
    rt_uint32_t val = dwmac_readl(eth, DMA_BUS_MODE);

    dwmac_writel(eth, DMA_BUS_MODE, val | DMA_BUS_MODE_SFT_RESET);

    return dwmac_poll_bit(eth, DMA_BUS_MODE, DMA_BUS_MODE_SFT_RESET, RT_TRUE);
}

static rt_uint32_t dwmac_mdio_format_addr(int pa, int gr)
{
    return ((pa << MII_GMAC4_ADDR_SHIFT) & MII_GMAC4_ADDR_MASK) |
           ((gr << MII_GMAC4_REG_SHIFT) & MII_GMAC4_REG_MASK) |
           MII_GMAC4_CSR_100_150M |
           MII_ADDR_GBUSY;
}

static rt_err_t dwmac_mdio_wait(struct dwmac_eth *eth)
{
    return dwmac_poll_bit(eth, GMAC_MDIO_ADDR, MII_ADDR_GBUSY, RT_TRUE);
}

static int dwmac_mdio_read(struct mii_bus *bus, int addr, int devad, int reg)
{
    struct dwmac_eth *eth = bus->priv;
    rt_uint32_t maddr;
    rt_err_t err;

    RT_UNUSED(devad);

    err = dwmac_mdio_wait(eth);
    if (err)
    {
        return err;
    }

    maddr = dwmac_mdio_format_addr(addr, reg) | MII_GMAC4_READ;
    dwmac_writel(eth, GMAC_MDIO_DATA, 0);
    dwmac_writel(eth, GMAC_MDIO_ADDR, maddr);

    err = dwmac_mdio_wait(eth);
    if (err)
    {
        return err;
    }

    return dwmac_readl(eth, GMAC_MDIO_DATA) & MII_DATA_GD_MASK;
}

static int dwmac_mdio_write(struct mii_bus *bus, int addr, int devad, int reg, rt_uint16_t val)
{
    struct dwmac_eth *eth = bus->priv;
    rt_uint32_t maddr;
    rt_err_t err;

    RT_UNUSED(devad);

    err = dwmac_mdio_wait(eth);
    if (err)
    {
        return err;
    }

    maddr = dwmac_mdio_format_addr(addr, reg) | MII_GMAC4_WRITE;
    dwmac_writel(eth, GMAC_MDIO_DATA, val);
    dwmac_writel(eth, GMAC_MDIO_ADDR, maddr);

    return dwmac_mdio_wait(eth);
}

static void dwmac_phy_reset_gpio(struct dwmac_eth *eth)
{
    if (eth->phy_reset_pin < 0)
    {
        return;
    }

    rt_pin_mode(eth->phy_reset_pin, PIN_MODE_OUTPUT);
    if (eth->phy_reset_delays[0])
    {
        rt_hw_us_delay(eth->phy_reset_delays[0]);
    }
    rt_pin_write(eth->phy_reset_pin, eth->phy_reset_active);
    if (eth->phy_reset_delays[1])
    {
        rt_hw_us_delay(eth->phy_reset_delays[1]);
    }
    rt_pin_write(eth->phy_reset_pin, !eth->phy_reset_active);
    if (eth->phy_reset_delays[2])
    {
        rt_hw_us_delay(eth->phy_reset_delays[2]);
    }
}

#define DWMAC_AXI_BLEN_MAX              7

static rt_uint32_t dwmac_axi_blen_to_mask(rt_uint32_t size)
{
    switch (size)
    {
    case 256:
        return DMA_AXI_BLEN256;
    case 128:
        return DMA_AXI_BLEN128;
    case 64:
        return DMA_AXI_BLEN64;
    case 32:
        return DMA_AXI_BLEN32;
    case 16:
        return DMA_AXI_BLEN16;
    case 8:
        return DMA_AXI_BLEN8;
    case 4:
        return DMA_AXI_BLEN4;
    default:
        return 0;
    }
}

#ifdef RT_USING_OFW
static void dwmac_parse_axi_config(struct dwmac_eth *eth, struct rt_ofw_node *np)
{
    rt_uint32_t blen[DWMAC_AXI_BLEN_MAX];
    int count, i;

    if (rt_ofw_prop_read_u32(np, "snps,wr_osr_lmt", &eth->axi.wr_osr_lmt))
    {
        eth->axi.wr_osr_lmt = 4;
    }

    if (rt_ofw_prop_read_u32(np, "snps,rd_osr_lmt", &eth->axi.rd_osr_lmt))
    {
        eth->axi.rd_osr_lmt = 8;
    }

    eth->axi.fixed_burst = rt_ofw_prop_read_bool(np, "snps,fb");
    eth->axi.mixed_burst = rt_ofw_prop_read_bool(np, "snps,mb");
    eth->axi.aal = rt_ofw_prop_read_bool(np, "snps,aal");

    count = rt_ofw_prop_read_u32_array_index(np, "snps,blen", 0,
            DWMAC_AXI_BLEN_MAX, blen);
    for (i = 0; i < count; ++i)
    {
        eth->axi.blen_mask |= dwmac_axi_blen_to_mask(blen[i]);
    }
}

static void dwmac_parse_mtl_config(struct dwmac_eth *eth, struct rt_ofw_node *np)
{
    struct rt_ofw_node *rx_np;
    struct rt_ofw_node *tx_np;

    eth->mtl.rx_queues = 1;
    eth->mtl.tx_queues = 1;

    rx_np = rt_ofw_parse_phandle(np, "snps,mtl-rx-config", 0);
    if (rx_np)
    {
        rt_ofw_prop_read_u32(rx_np, "snps,rx-queues-to-use", &eth->mtl.rx_queues);
        rt_ofw_node_put(rx_np);
    }

    tx_np = rt_ofw_parse_phandle(np, "snps,mtl-tx-config", 0);
    if (tx_np)
    {
        rt_ofw_prop_read_u32(tx_np, "snps,tx-queues-to-use", &eth->mtl.tx_queues);
        rt_ofw_node_put(tx_np);
    }
}
#endif /* RT_USING_OFW */

static void dwmac_parse_dt_props(struct dwmac_eth *eth)
{
    const struct dwmac_config *cfg = eth->config;

    eth->dma_pbl = cfg && cfg->dma_pbl ? cfg->dma_pbl : DWMAC_DMA_PBL;
    eth->dma_txpbl = eth->dma_pbl;
    eth->dma_rxpbl = eth->dma_pbl;
    eth->axi.wr_osr_lmt = 4;
    eth->axi.rd_osr_lmt = 8;
    eth->axi.blen_mask = DMA_AXI_BLEN16 | DMA_AXI_BLEN8 | DMA_AXI_BLEN4;
    eth->mtl.rx_queues = 1;
    eth->mtl.tx_queues = 1;

#ifdef RT_USING_OFW
    struct rt_device *dev = eth->dev;
    struct rt_ofw_node *np = dev->ofw_node;
    struct rt_ofw_node *axi_np;

    if (rt_ofw_get_interface(dev->ofw_node, (rt_phy_interface *)&eth->phy_interface))
    {
        eth->phy_interface = RT_PHY_INTERFACE_MODE_RGMII;
    }

    eth->tso_en = rt_ofw_prop_read_bool(np, "snps,tso") ||
            (cfg && (cfg->caps & DWMAC_CAP_TSO));
    eth->axi.mixed_burst = rt_ofw_prop_read_bool(np, "snps,mixed-burst");

    if (!rt_ofw_prop_read_u32(np, "snps,pbl", (rt_uint32_t *)&eth->dma_pbl))
    {
        eth->dma_txpbl = eth->dma_pbl;
        eth->dma_rxpbl = eth->dma_pbl;
    }

    rt_ofw_prop_read_u32(np, "snps,txpbl", (rt_uint32_t *)&eth->dma_txpbl);
    rt_ofw_prop_read_u32(np, "snps,rxpbl", (rt_uint32_t *)&eth->dma_rxpbl);
    eth->axi.aal = rt_ofw_prop_read_bool(np, "snps,aal");
    eth->axi.fixed_burst = rt_ofw_prop_read_bool(np, "snps,fixed-burst");

    axi_np = rt_ofw_parse_phandle(np, "snps,axi-config", 0);
    if (axi_np)
    {
        dwmac_parse_axi_config(eth, axi_np);
        rt_ofw_node_put(axi_np);
    }

    dwmac_parse_mtl_config(eth, np);

#ifdef RT_USING_PIN
    eth->phy_reset_pin = rt_pin_get_named_pin(dev, "snps,reset", 0,
            RT_NULL, &eth->phy_reset_active);
    if (eth->phy_reset_pin < 0)
    {
        LOG_W("PHY reset gpio not found: %d", eth->phy_reset_pin);
        eth->phy_reset_pin = -1;
    }

    rt_ofw_prop_read_u32_array_index(dev->ofw_node, "snps,reset-delays-us",
            0, 3, eth->phy_reset_delays);
#endif /* RT_USING_PIN */
#else
    eth->phy_interface = RT_PHY_INTERFACE_MODE_RGMII;
#endif /* RT_USING_OFW */
}

static void dwmac_clocks_get(struct dwmac_eth *eth, struct rt_device *dev)
{
    eth->stmmac_clk = rt_clk_get_by_name(dev, "stmmaceth");
    eth->mac_clk_speed = rt_clk_get_by_name(dev, "clk_mac_speed");
    eth->mac_clk_rx = rt_clk_get_by_name(dev, "mac_clk_rx");
    eth->mac_clk_tx = rt_clk_get_by_name(dev, "mac_clk_tx");
    eth->clk_mac_refout = rt_clk_get_by_name(dev, "clk_mac_refout");
    eth->ptp_clk = rt_clk_get_by_name(dev, "ptp_ref");
    eth->aclk = rt_clk_get_by_name(dev, "aclk_mac");
    eth->pclk = rt_clk_get_by_name(dev, "pclk_mac");
}

static rt_err_t dwmac_clk_prepare_enable(struct rt_clk *clk)
{
    if (rt_is_err_or_null(clk))
    {
        return RT_EOK;
    }

    return rt_clk_prepare_enable(clk);
}

static void dwmac_clk_disable_unprepare(struct rt_clk *clk)
{
    if (!rt_is_err_or_null(clk))
    {
        rt_clk_disable_unprepare(clk);
    }
}

static rt_err_t dwmac_clocks_enable(struct dwmac_eth *eth)
{
    rt_err_t err;

    if ((err = dwmac_clk_prepare_enable(eth->aclk)))
    {
        return err;
    }

    if ((err = dwmac_clk_prepare_enable(eth->pclk)))
    {
        goto _fail_aclk;
    }

    if ((err = dwmac_clk_prepare_enable(eth->stmmac_clk)))
    {
        goto _fail_pclk;
    }

    if ((err = dwmac_clk_prepare_enable(eth->mac_clk_speed)))
    {
        goto _fail_stmmac;
    }

    if ((err = dwmac_clk_prepare_enable(eth->mac_clk_rx)))
    {
        goto _fail_mac_speed;
    }

    if ((err = dwmac_clk_prepare_enable(eth->mac_clk_tx)))
    {
        goto _fail_mac_rx;
    }

    if ((err = dwmac_clk_prepare_enable(eth->clk_mac_refout)))
    {
        goto _fail_mac_tx;
    }

    if ((err = dwmac_clk_prepare_enable(eth->ptp_clk)))
    {
        goto _fail_refout;
    }

    return RT_EOK;

_fail_refout:
    dwmac_clk_disable_unprepare(eth->clk_mac_refout);
_fail_mac_tx:
    dwmac_clk_disable_unprepare(eth->mac_clk_tx);
_fail_mac_rx:
    dwmac_clk_disable_unprepare(eth->mac_clk_rx);
_fail_mac_speed:
    dwmac_clk_disable_unprepare(eth->mac_clk_speed);
_fail_stmmac:
    dwmac_clk_disable_unprepare(eth->stmmac_clk);
_fail_pclk:
    dwmac_clk_disable_unprepare(eth->pclk);
_fail_aclk:
    return err;
}

static void dwmac_clocks_disable(struct dwmac_eth *eth)
{
    dwmac_clk_disable_unprepare(eth->ptp_clk);
    dwmac_clk_disable_unprepare(eth->clk_mac_refout);
    dwmac_clk_disable_unprepare(eth->mac_clk_tx);
    dwmac_clk_disable_unprepare(eth->mac_clk_rx);
    dwmac_clk_disable_unprepare(eth->mac_clk_speed);
    dwmac_clk_disable_unprepare(eth->stmmac_clk);
    dwmac_clk_disable_unprepare(eth->pclk);
    dwmac_clk_disable_unprepare(eth->aclk);
}

#ifdef RT_USING_REGULATOR
static rt_err_t dwmac_phy_supply_enable(struct dwmac_eth *eth)
{
    rt_err_t err;
#ifdef RT_USING_OFW
    rt_phandle supply_phandle = 0;
    const char *supply_name = RT_NULL;
#endif

#ifdef RT_USING_OFW
    if (eth->dev && eth->dev->ofw_node)
    {
        if (rt_ofw_prop_read_u32(eth->dev->ofw_node, "phy-supply",
                    &supply_phandle))
        {
            LOG_D("No phy-supply property");
            return RT_EOK;
        }

        LOG_D("PHY supply phandle=0x%08x", supply_phandle);
    }
#endif /* RT_USING_OFW */

    eth->phy_supply = rt_regulator_get(eth->dev, "phy");
    if (rt_is_err(eth->phy_supply))
    {
        err = rt_ptr_err(eth->phy_supply);
        LOG_W("PHY supply get failed: %s", rt_strerror(err));
        eth->phy_supply = RT_NULL;
        return err;
    }
    if (!eth->phy_supply)
    {
#ifdef RT_USING_OFW
        if (supply_phandle)
        {
            struct rt_ofw_node *supply_np;

            supply_np = rt_ofw_find_node_by_phandle(supply_phandle);
            if (supply_np)
            {
                rt_ofw_prop_read_string(supply_np, "regulator-name",
                        &supply_name);
                rt_ofw_node_put(supply_np);
            }

            if (supply_name)
            {
                eth->phy_supply = rt_regulator_get(RT_NULL, supply_name);
                if (rt_is_err(eth->phy_supply))
                {
                    err = rt_ptr_err(eth->phy_supply);
                    LOG_W("PHY supply %s get failed: %s", supply_name,
                            rt_strerror(err));
                    eth->phy_supply = RT_NULL;
                    return err;
                }
            }
        }
#endif /* RT_USING_OFW */

        if (eth->phy_supply)
        {
            goto _enable;
        }

        LOG_W("PHY supply not available");
        return RT_EOK;
    }

_enable:
    err = rt_regulator_enable(eth->phy_supply);
    if (err)
    {
        rt_regulator_put(eth->phy_supply);
        eth->phy_supply = RT_NULL;
        return err;
    }

    LOG_D("PHY supply enabled, voltage=%d uV",
            rt_regulator_get_voltage(eth->phy_supply));

    return RT_EOK;
}

static void dwmac_phy_supply_disable(struct dwmac_eth *eth)
{
    if (!eth->phy_supply)
    {
        return;
    }

    rt_regulator_disable(eth->phy_supply);
    rt_regulator_put(eth->phy_supply);
    eth->phy_supply = RT_NULL;
}
#else
static rt_err_t dwmac_phy_supply_enable(struct dwmac_eth *eth)
{
    RT_UNUSED(eth);

    return RT_EOK;
}

static void dwmac_phy_supply_disable(struct dwmac_eth *eth)
{
    RT_UNUSED(eth);
}
#endif /* RT_USING_REGULATOR */

static void dwmac_set_mac_addr(struct dwmac_eth *eth)
{
    rt_uint32_t lo = eth->mac[0] | (eth->mac[1] << 8) |
                     (eth->mac[2] << 16) | (eth->mac[3] << 24);
    rt_uint16_t hi = eth->mac[4] | (eth->mac[5] << 8);

    dwmac_writel(eth, GMAC_ADDR_LOW(0), lo);
    dwmac_writel(eth, GMAC_ADDR_HIGH(0), hi | RT_BIT(31));
}

static rt_err_t dwmac_mii_register(struct dwmac_eth *eth)
{
    rt_err_t err;

    eth->mii = rt_mdio_alloc();
    if (!eth->mii)
    {
        return -RT_ENOMEM;
    }

    eth->mii->priv = eth;
    eth->mii->read = dwmac_mdio_read;
    eth->mii->write = dwmac_mdio_write;
    rt_snprintf(eth->mii->name, RT_NAME_MAX, "mii%p", eth);

    if ((err = rt_mdio_register(eth->mii)))
    {
        rt_free(eth->mii);
        eth->mii = RT_NULL;
        return err;
    }

    return RT_EOK;
}

static void dwmac_mii_unregister(struct dwmac_eth *eth)
{
    if (eth->mii)
    {
        rt_mdio_unregister(eth->mii);
        rt_free(eth->mii);
        eth->mii = RT_NULL;
    }
}

static int dwmac_find_phy_addr(struct dwmac_eth *eth)
{
#ifdef RT_USING_OFW
    struct rt_ofw_node *phy_np;

    if (eth->dev && eth->dev->ofw_node &&
        (phy_np = rt_ofw_parse_phandle(eth->dev->ofw_node, "phy-handle", 0)))
    {
        rt_uint32_t reg;

        if (!rt_ofw_prop_read_u32(phy_np, "reg", &reg))
        {
            rt_ofw_node_put(phy_np);
            return (int)reg;
        }

        rt_ofw_node_put(phy_np);
    }
#endif /* RT_USING_OFW */

    for (int addr = 0; addr < 32; ++addr)
    {
        int id = dwmac_mdio_read(eth->mii, addr, 0, RT_MII_PHYSID1);

        if (id > 0 && id != 0xffff)
        {
            return addr;
        }
    }

    return -1;
}

static rt_err_t dwmac_dma_alloc_rings(struct dwmac_eth *eth)
{
    rt_size_t desc_bytes, rx_buf_bytes, tx_buf_bytes, total;
    rt_ubase_t handle;
    rt_uint64_t dma_end;
    void *blob;

    desc_bytes = sizeof(struct dwmac_desc) * (DWMAC_RX_RING_SIZE + DWMAC_TX_RING_SIZE);
    rx_buf_bytes = DWMAC_RX_BUFFER_SIZE * DWMAC_RX_RING_SIZE;
    tx_buf_bytes = DWMAC_RX_BUFFER_SIZE * DWMAC_TX_RING_SIZE;
    total = desc_bytes + rx_buf_bytes + tx_buf_bytes;

    blob = rt_dma_alloc(eth->dev, total, &handle, DWMAC_DMA_ALLOC_FLAGS);
    if (!blob)
    {
        return -RT_ENOMEM;
    }

    dma_end = (rt_uint64_t)handle + total - 1;
    if ((rt_uint64_t)handle > DWMAC_DMA_ADDR_MAX ||
        dma_end > DWMAC_DMA_ADDR_MAX)
    {
        LOG_E("DMA address 0x%llx-0x%llx exceeds 32-bit range",
                (unsigned long long)handle, (unsigned long long)dma_end);
        rt_dma_free(eth->dev, total, blob, handle, DWMAC_DMA_ALLOC_FLAGS);
        return -RT_EINVAL;
    }

    eth->rx_ring = blob;
    eth->tx_ring = (struct dwmac_desc *)((rt_uint8_t *)blob +
            sizeof(struct dwmac_desc) * DWMAC_RX_RING_SIZE);
    eth->rx_buffers = (rt_uint8_t *)blob + desc_bytes;
    eth->tx_buffers = eth->rx_buffers + rx_buf_bytes;

    eth->rx_ring_dma = handle;
    eth->tx_ring_dma = handle + sizeof(struct dwmac_desc) * DWMAC_RX_RING_SIZE;
    eth->rx_buffers_dma = handle + desc_bytes;
    eth->tx_buffers_dma = eth->rx_buffers_dma + rx_buf_bytes;

    eth->dma_blob_size = total;
    eth->dma_blob_handle = handle;

    rt_memset(blob, 0, total);

    return RT_EOK;
}

static void dwmac_init_rx_desc(struct dwmac_eth *eth, int idx)
{
    struct dwmac_desc *desc = &eth->rx_ring[idx];
    rt_ubase_t buf_dma = eth->rx_buffers_dma + idx * DWMAC_RX_BUFFER_SIZE;

    desc->des0 = (rt_uint32_t)buf_dma;
    desc->des1 = 0;
    desc->des2 = 0;
    desc->des3 = RDES3_OWN | RDES3_BUFFER1_VALID_ADDR |
            RDES3_INT_ON_COMPLETION_EN;
}

static void dwmac_dma_init(struct dwmac_eth *eth)
{
    rt_uint32_t val;
    int c = DWMAC_CHAN;
    rt_size_t ring_bytes = sizeof(struct dwmac_desc) *
            (DWMAC_RX_RING_SIZE + DWMAC_TX_RING_SIZE);

    for (int i = 0; i < DWMAC_RX_RING_SIZE; ++i)
    {
        dwmac_init_rx_desc(eth, i);
    }
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, eth->rx_ring, ring_bytes);

    val = 0;
    if (eth->axi.fixed_burst)
    {
        val |= DMA_SYS_BUS_FB;
    }
    if (eth->axi.mixed_burst)
    {
        val |= DMA_SYS_BUS_MB;
    }
    if (eth->axi.aal)
    {
        val |= DMA_SYS_BUS_AAL;
    }
    val |= eth->axi.blen_mask;
    val |= (eth->axi.wr_osr_lmt << DMA_AXI_WR_OSR_LMT_SHIFT);
    val |= (eth->axi.rd_osr_lmt << DMA_AXI_RD_OSR_LMT_SHIFT);
    dwmac_writel(eth, DMA_SYS_BUS_MODE, val);

    /* MTL: store-and-forward, enable TX queue 0 */
    val = dwmac_readl(eth, MTL_CHAN_TX_OP_MODE(c));
    val |= MTL_OP_MODE_TSF | MTL_OP_MODE_TXQEN;
    dwmac_writel(eth, MTL_CHAN_TX_OP_MODE(c), val);

    val = dwmac_readl(eth, MTL_CHAN_RX_OP_MODE(c));
    val |= MTL_OP_MODE_RSF;
    dwmac_writel(eth, MTL_CHAN_RX_OP_MODE(c), val);

    dwmac_writel(eth, GMAC_RXQ_CTRL0, GMAC_RX_DCB_QUEUE_ENABLE(0));

    val = dwmac_readl(eth, GMAC_RXQ_CTRL1);
    val &= ~GMAC_RXQCTRL_MCBCQ_MASK;
    val |= (0 << GMAC_RXQCTRL_MCBCQ_SHIFT) & GMAC_RXQCTRL_MCBCQ_MASK;
    val |= GMAC_RXQCTRL_MCBCQEN;
    dwmac_writel(eth, GMAC_RXQ_CTRL1, val);

    val = dwmac_readl(eth, MTL_RXQ_DMA_MAP0);
    val &= ~MTL_RXQ_DMA_QXMDMACH_MASK(0);
    val |= MTL_RXQ_DMA_QXMDMACH(DWMAC_CHAN, 0);
    dwmac_writel(eth, MTL_RXQ_DMA_MAP0, val);

    /* DMA channel */
    val = eth->dma_txpbl << DMA_BUS_MODE_PBL_SHIFT;
    if (eth->tso_en)
    {
        val |= DMA_CONTROL_TSE;
    }
    dwmac_writel(eth, DMA_CHAN_TX_CONTROL(c), val | DMA_CONTROL_OSP);

    val = eth->dma_rxpbl << DMA_BUS_MODE_RPBL_SHIFT;
    val |= ((DWMAC_RX_BUFFER_SIZE << DMA_RBSZ_SHIFT) & DMA_RBSZ_MASK);
    dwmac_writel(eth, DMA_CHAN_RX_CONTROL(c), val);

    dwmac_writel(eth, DMA_CHAN_TX_BASE_ADDR(c), (rt_uint32_t)eth->tx_ring_dma);
    dwmac_writel(eth, DMA_CHAN_RX_BASE_ADDR(c), (rt_uint32_t)eth->rx_ring_dma);
    dwmac_writel(eth, DMA_CHAN_TX_RING_LEN(c), DWMAC_TX_RING_SIZE - 1);
    dwmac_writel(eth, DMA_CHAN_RX_RING_LEN(c), DWMAC_RX_RING_SIZE - 1);

    dwmac_writel(eth, DMA_CHAN_RX_END_ADDR(c),
            (rt_uint32_t)(eth->rx_ring_dma +
            (DWMAC_RX_RING_SIZE - 1) * sizeof(struct dwmac_desc)));

    dwmac_writel(eth, GMAC_PACKET_FILTER, GMAC_PF_PM);
}

static rt_err_t dwmac_adjust_link(struct dwmac_eth *eth)
{
    rt_uint32_t cfg;
    const struct dwmac_plat_ops *plat = dwmac_plat(eth);

    if (!eth->phy || !eth->phy->link)
    {
        return -RT_ERROR;
    }

    cfg = dwmac_readl(eth, GMAC_CONFIG);
    cfg &= ~(GMAC_CONFIG_PS | GMAC_CONFIG_FES | GMAC_CONFIG_DM);

    if (eth->phy->duplex == DUPLEX_FULL)
    {
        cfg |= GMAC_CONFIG_DM;
    }

    switch (eth->phy->speed)
    {
    case SPEED_1000:
        break;
    case SPEED_100:
        cfg |= GMAC_CONFIG_PS | GMAC_CONFIG_FES;
        break;
    case SPEED_10:
        cfg |= GMAC_CONFIG_PS;
        break;
    default:
        return -RT_EINVAL;
    }

    if (plat && plat->fix_link_speed)
    {
        rt_err_t err = plat->fix_link_speed(eth, eth->phy->speed);

        if (err)
        {
            return err;
        }
    }

    cfg |= GMAC_CONFIG_TE | GMAC_CONFIG_RE | GMAC_CONFIG_IPC;
    dwmac_writel(eth, GMAC_CONFIG, cfg);

    /* Start DMA engines */
    cfg = dwmac_readl(eth, DMA_CHAN_TX_CONTROL(DWMAC_CHAN));
    dwmac_writel(eth, DMA_CHAN_TX_CONTROL(DWMAC_CHAN), cfg | DMA_CONTROL_ST);

    cfg = dwmac_readl(eth, DMA_CHAN_RX_CONTROL(DWMAC_CHAN));
    dwmac_writel(eth, DMA_CHAN_RX_CONTROL(DWMAC_CHAN), cfg | DMA_CONTROL_SR);

    dwmac_writel(eth, DMA_CHAN_STATUS(DWMAC_CHAN), 0xffffffff);
    dwmac_writel(eth, DMA_CHAN_INTR_ENA(DWMAC_CHAN),
            DMA_CHAN_INTR_DEFAULT_MASK_4_10);

    eth->mac_started = RT_TRUE;

    return RT_EOK;
}

static rt_err_t dwmac_start(struct dwmac_eth *eth)
{
    rt_err_t err;

    if (!eth->phy)
    {
        return -RT_ERROR;
    }

    if (!eth->phy_configured)
    {
        if ((err = rt_phy_config(eth->phy)) < 0)
        {
            return err;
        }
        eth->phy_configured = RT_TRUE;
    }

    if ((err = rt_phy_startup(eth->phy)) < 0)
    {
        return err;
    }

    return dwmac_adjust_link(eth);
}

#ifdef RT_USING_SYSTEM_WORKQUEUE
static void dwmac_phy_retry_work(struct rt_work *work, void *work_data)
{
    struct dwmac_eth *eth = work_data;
    rt_err_t err;

    RT_UNUSED(work);

    if (!eth || !eth->net_registered || !eth->phy)
    {
        return;
    }

    err = dwmac_start(eth);
    if (err == RT_EOK && eth->phy->link)
    {
        eth_device_linkchange(&eth->parent, RT_TRUE);
        return;
    }

    eth_device_linkchange(&eth->parent, RT_FALSE);
    rt_work_submit(&eth->phy_retry_work,
            rt_tick_from_millisecond(DWMAC_PHY_RETRY_INTERVAL_MS));
}
#endif /* RT_USING_SYSTEM_WORKQUEUE */

static rt_err_t dwmac_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct dwmac_eth *eth = rt_container_of(dev, struct dwmac_eth, parent.parent);
    struct dwmac_desc *desc;
    rt_uint32_t idx = eth->tx_idx;
    rt_uint8_t *payload;
    rt_size_t len = p->tot_len;
    rt_uint32_t tdes3;

    if (!eth->mac_started || !eth->phy || !eth->phy->link)
    {
        return -RT_ERROR;
    }

    desc = &eth->tx_ring[idx];
    if (desc->des3 & TDES3_OWN)
    {
        return -RT_EBUSY;
    }

    payload = eth->tx_buffers + idx * DWMAC_RX_BUFFER_SIZE;

    pbuf_copy_partial(p, payload, len, 0);
    if (len < ETH_ZLEN)
    {
        rt_memset(payload + len, 0, ETH_ZLEN - len);
        len = ETH_ZLEN;
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, payload, len);

    desc->des0 = (rt_uint32_t)(eth->tx_buffers_dma + idx * DWMAC_RX_BUFFER_SIZE);
    desc->des1 = 0;
    desc->des2 = len & TDES2_BUFFER1_SIZE_MASK;
    tdes3 = (len & TDES3_PACKET_SIZE_MASK) |
            TDES3_FIRST_DESCRIPTOR | TDES3_LAST_DESCRIPTOR | TDES3_OWN;
#ifdef RT_LWIP_USING_HW_CHECKSUM
    tdes3 |= TDES3_CHECKSUM_INSERTION_FULL;
#endif
    rt_hw_wmb();
    desc->des3 = tdes3;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, desc, sizeof(*desc));

    eth->tx_idx = NEXT_TX(idx);
    rt_hw_wmb();
    dwmac_writel(eth, DMA_CHAN_TX_END_ADDR(DWMAC_CHAN),
            (rt_uint32_t)(eth->tx_ring_dma +
            eth->tx_idx * sizeof(struct dwmac_desc)));
    rt_hw_dsb();

    return RT_EOK;
}

static struct pbuf *dwmac_eth_rx(rt_device_t dev)
{
    struct dwmac_eth *eth = rt_container_of(dev, struct dwmac_eth, parent.parent);
    struct dwmac_desc *desc;
    struct pbuf *p = RT_NULL;
    rt_uint32_t idx = eth->rx_idx;
    rt_uint32_t len;
    rt_uint8_t *payload;

    desc = &eth->rx_ring[idx];
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, desc, sizeof(*desc));

    if (desc->des3 & RDES3_OWN)
    {
        return RT_NULL;
    }

    len = desc->des3 & RDES3_PACKET_SIZE_MASK;
    if (len == 0 || len > DWMAC_RX_BUFFER_SIZE)
    {
        goto refill;
    }

    payload = eth->rx_buffers + idx * DWMAC_RX_BUFFER_SIZE;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, payload, len);

    p = pbuf_alloc(PBUF_RAW, len, PBUF_RAM);
    if (p)
    {
        pbuf_take(p, payload, len);
    }

refill:
    dwmac_init_rx_desc(eth, idx);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, desc, sizeof(*desc));
    dwmac_writel(eth, DMA_CHAN_RX_END_ADDR(DWMAC_CHAN),
            (rt_uint32_t)(eth->rx_ring_dma + idx * sizeof(struct dwmac_desc)));
    eth->rx_idx = NEXT_RX(idx);

    return p;
}

static rt_err_t dwmac_eth_control(rt_device_t dev, int cmd, void *args)
{
    struct dwmac_eth *eth = rt_container_of(dev, struct dwmac_eth, parent.parent);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (!args)
        {
            return -RT_EINVAL;
        }
        rt_memcpy(args, eth->mac, sizeof(eth->mac));
        return RT_EOK;

    default:
        return -RT_EINVAL;
    }
}

static void dwmac_eth_isr(int irq, void *param)
{
    rt_uint32_t status;
    struct dwmac_eth *eth = param;

    RT_UNUSED(irq);

    status = dwmac_readl(eth, DMA_CHAN_STATUS(DWMAC_CHAN));
    if (!status)
    {
        return;
    }

    dwmac_writel(eth, DMA_CHAN_STATUS(DWMAC_CHAN), status);

    if (status & (DMA_CHAN_STATUS_RI | DMA_CHAN_STATUS_TI | DMA_CHAN_STATUS_NIS))
    {
        eth_device_ready(&eth->parent);
    }
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops dwmac_eth_ops =
{
    .control = dwmac_eth_control,
};
#endif

rt_err_t dwmac_eth_common_probe(struct dwmac_eth *eth)
{
    rt_err_t err;

#ifdef RT_USING_DEVICE_OPS
    eth->parent.parent.ops = &dwmac_eth_ops;
#else
    eth->parent.parent.control = dwmac_eth_control;
#endif
    eth->parent.eth_tx = dwmac_eth_tx;
    eth->parent.eth_rx = dwmac_eth_rx;

    if ((err = rt_dm_dev_set_name_auto(&eth->parent.parent, "e")) < 0)
    {
        return err;
    }

    if (eth->irq >= 0)
    {
        rt_hw_interrupt_install(eth->irq, dwmac_eth_isr, eth, "dwmac");
        rt_hw_interrupt_umask(eth->irq);
        eth->irq_installed = RT_TRUE;
    }

    if ((err = eth_device_init(&eth->parent, rt_dm_dev_get_name(&eth->parent.parent))))
    {
        return err;
    }

    eth->net_registered = RT_TRUE;

#ifdef RT_ETHERNET_DWMAC_PTP
    if (eth->config && (eth->config->caps & DWMAC_CAP_PTP))
    {
        if ((err = dwmac_ptp_register(eth)))
        {
            LOG_W("PTP register failed: %s", rt_strerror(err));
        }
    }
#endif /* RT_ETHERNET_DWMAC_PTP */

#ifdef RT_USING_SYSTEM_WORKQUEUE
    if (eth->phy && !eth->phy->link)
    {
        rt_work_init(&eth->phy_retry_work, dwmac_phy_retry_work, eth);
        eth->phy_work_inited = RT_TRUE;
        eth_device_linkchange(&eth->parent, RT_FALSE);
        rt_work_submit(&eth->phy_retry_work,
                rt_tick_from_millisecond(DWMAC_PHY_RETRY_INTERVAL_MS));
    }
    else if (eth->phy && eth->phy->link)
    {
        eth_device_linkchange(&eth->parent, RT_TRUE);
    }
    else
    {
        eth_device_linkchange(&eth->parent, RT_FALSE);
    }
#else
    if (dwmac_start(eth) == RT_EOK && eth->phy && eth->phy->link)
    {
        eth_device_linkchange(&eth->parent, RT_TRUE);
    }
    else
    {
        eth_device_linkchange(&eth->parent, RT_FALSE);
    }
#endif

    return RT_EOK;
}

rt_err_t dwmac_eth_common_remove(struct dwmac_eth *eth)
{
#ifdef RT_ETHERNET_DWMAC_PTP
    dwmac_ptp_unregister(eth);
#endif

#ifdef RT_USING_SYSTEM_WORKQUEUE
    if (eth->phy_work_inited)
    {
        rt_work_cancel(&eth->phy_retry_work);
        eth->phy_work_inited = RT_FALSE;
    }
#endif

    if (eth->irq_installed)
    {
        rt_hw_interrupt_mask(eth->irq);
        rt_pic_detach_irq(eth->irq, eth);
        eth->irq_installed = RT_FALSE;
    }

    if (eth->net_registered)
    {
        eth_device_linkchange(&eth->parent, RT_FALSE);
        eth_device_deinit(&eth->parent);
        eth->net_registered = RT_FALSE;
    }

    if (eth->phy)
    {
        rt_phy_shutdown(eth->phy);
        eth->phy = RT_NULL;
    }

    dwmac_mii_unregister(eth);

    return RT_EOK;
}

rt_err_t dwmac_probe(struct dwmac_eth *eth)
{
    rt_err_t err;
    const struct dwmac_plat_ops *plat = dwmac_plat(eth);
    int phy_addr;

    dwmac_parse_dt_props(eth);
    dwmac_clocks_get(eth, eth->dev);

    if (plat && plat->parse_ofw)
    {
        err = plat->parse_ofw(eth);
        if (err)
        {
            return err;
        }
    }

    eth->rst = rt_reset_control_get_by_name(eth->dev, "stmmaceth");
    if (!rt_is_err_or_null(eth->rst))
    {
        rt_reset_control_assert(eth->rst);
        rt_hw_us_delay(20);
        rt_reset_control_deassert(eth->rst);
    }

    if ((err = dwmac_clocks_enable(eth)))
    {
        goto _fail_clk;
    }

    if (plat && plat->init)
    {
        err = plat->init(eth);
        if (err)
        {
            goto _fail_plat;
        }
    }

    if ((err = dwmac_phy_supply_enable(eth)))
    {
        LOG_E("PHY supply enable failed: %s", rt_strerror(err));
        goto _fail_plat;
    }

    dwmac_phy_reset_gpio(eth);

    if ((err = dwmac_dma_reset(eth)))
    {
        LOG_E("DMA reset failed");
        goto _fail_phy_supply;
    }

    if ((err = dwmac_dma_alloc_rings(eth)))
    {
        goto _fail_phy_supply;
    }

    dwmac_dma_init(eth);
    dwmac_set_mac_addr(eth);

    if ((err = dwmac_mii_register(eth)))
    {
        goto _fail_blob;
    }

    phy_addr = dwmac_find_phy_addr(eth);
    if (phy_addr < 0)
    {
        LOG_E("No PHY on MDIO");
        err = -RT_EINVAL;
        goto _fail_mii;
    }

    eth->phy = rt_phy_get_device(eth->mii, eth->dev->ofw_node, phy_addr,
            (rt_phy_interface)eth->phy_interface);
    if (!eth->phy)
    {
        LOG_E("PHY attach failed");
        err = -RT_ERROR;
        goto _fail_mii;
    }

    eth->hw_ready = RT_TRUE;

    if ((err = dwmac_eth_common_probe(eth)))
    {
        dwmac_eth_common_remove(eth);
        goto _fail_mii;
    }

    return RT_EOK;

_fail_mii:
    dwmac_mii_unregister(eth);

_fail_blob:
    if (eth->rx_ring)
    {
        rt_dma_free(eth->dev, eth->dma_blob_size, eth->rx_ring,
                eth->dma_blob_handle, DWMAC_DMA_ALLOC_FLAGS);
        eth->rx_ring = RT_NULL;
    }

_fail_phy_supply:
    dwmac_phy_supply_disable(eth);

_fail_plat:
    if (plat && plat->exit)
    {
        plat->exit(eth);
    }
    dwmac_clocks_disable(eth);

_fail_clk:
    if (!rt_is_err_or_null(eth->rst))
    {
        rt_reset_control_put(eth->rst);
    }

    return err;
}

rt_err_t dwmac_remove(struct dwmac_eth *eth)
{
    const struct dwmac_plat_ops *plat = dwmac_plat(eth);

    dwmac_eth_common_remove(eth);

    if (eth->rx_ring)
    {
        rt_dma_free(eth->dev, eth->dma_blob_size, eth->rx_ring,
                eth->dma_blob_handle, DWMAC_DMA_ALLOC_FLAGS);
        eth->rx_ring = RT_NULL;
    }

    dwmac_phy_supply_disable(eth);

    if (plat && plat->exit)
    {
        plat->exit(eth);
    }

    dwmac_clocks_disable(eth);

    if (!rt_is_err_or_null(eth->rst))
    {
        rt_reset_control_put(eth->rst);
    }

    return RT_EOK;
}
