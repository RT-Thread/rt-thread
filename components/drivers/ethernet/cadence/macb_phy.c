/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#define GEM_MDIO_IDLE_RETRIES           100000
#define GEM_MDIO_POLL_US                10
#define GEM_MDIO_FIXED_TURNAROUND_US    100

static rt_bool_t gem_mdio_wait_idle(struct macb_eth *eth, int retries)
{
    while (retries-- > 0)
    {
        rt_uint32_t nsr = macb_readl(eth, GEM_NSR);

        /*
         * GEM queue-0 may not expose a readable NSR @ 0x8 (reads 0xffffffff).
         * Linux/U-Boot treat the idle bit as set; use a fixed turnaround.
         */
        if (nsr == 0xffffffff)
        {
            rt_hw_us_delay(GEM_MDIO_FIXED_TURNAROUND_US);
            return RT_TRUE;
        }

        if (nsr & GEM_NSR_IDLE)
        {
            return RT_TRUE;
        }

        rt_hw_us_delay(GEM_MDIO_POLL_US);
    }

    return RT_FALSE;
}

static rt_err_t gem_mdio_frame(struct macb_eth *eth, rt_uint32_t frame)
{
    if (!gem_mdio_wait_idle(eth, GEM_MDIO_IDLE_RETRIES))
    {
        return -RT_ETIMEOUT;
    }

    macb_writel(eth, GEM_MAN, frame);
    if (!eth->native_io)
    {
        macb_mmio_posted_barrier(eth);
    }

    if (!gem_mdio_wait_idle(eth, GEM_MDIO_IDLE_RETRIES))
    {
        if (!eth->native_io)
        {
            rt_hw_us_delay(GEM_MDIO_FIXED_TURNAROUND_US);
            return RT_EOK;
        }

        return -RT_ETIMEOUT;
    }

    return RT_EOK;
}

static rt_bool_t gem_mdio_data_invalid(struct macb_eth *eth, rt_uint32_t data)
{
    return data == 0xffff && !eth->native_io;
}

static rt_uint32_t gem_ncfgr_mdc_div(rt_ubase_t pclk_hz)
{
    if (pclk_hz <= 20000000)
    {
        return GEM_CLK_DIV8 << GEM_NCFGR_CLK_SHIFT;
    }
    else if (pclk_hz <= 40000000)
    {
        return GEM_CLK_DIV16 << GEM_NCFGR_CLK_SHIFT;
    }
    else if (pclk_hz <= 80000000)
    {
        return GEM_CLK_DIV32 << GEM_NCFGR_CLK_SHIFT;
    }
    else if (pclk_hz <= 120000000)
    {
        return GEM_CLK_DIV48 << GEM_NCFGR_CLK_SHIFT;
    }
    else if (pclk_hz <= 160000000)
    {
        return GEM_CLK_DIV64 << GEM_NCFGR_CLK_SHIFT;
    }
    else if (pclk_hz <= 240000000)
    {
        return GEM_CLK_DIV96 << GEM_NCFGR_CLK_SHIFT;
    }
    else if (pclk_hz <= 320000000)
    {
        return GEM_CLK_DIV128 << GEM_NCFGR_CLK_SHIFT;
    }

    return GEM_CLK_DIV224 << GEM_NCFGR_CLK_SHIFT;
}

static rt_uint32_t macb_gem_dbw(struct macb_eth *eth)
{
    rt_uint32_t dcfg1, dbw;

    dcfg1 = macb_readl(eth, GEM_DCFG1);
    dbw = (dcfg1 >> 25) & 0x7U;

    switch (dbw)
    {
    case 4:
        return GEM_DBW128 << GEM_NCFGR_DBW_SHIFT;
    case 2:
        return GEM_DBW64 << GEM_NCFGR_DBW_SHIFT;
    default:
        return GEM_DBW32 << GEM_NCFGR_DBW_SHIFT;
    }
}

static int gem_mdio_read(struct mii_bus *bus, int addr, int devad, int reg)
{
    rt_err_t err;
    rt_uint32_t data, frame;
    struct macb_eth *eth = bus->priv;

    rt_mutex_take(&eth->mdio_lock, RT_WAITING_FOREVER);

    frame = GEM_MAN_BF(SOF, GEM_MAN_SOF) | GEM_MAN_BF(RW, GEM_MAN_READ) |
            GEM_MAN_BF(PHYA, addr) | GEM_MAN_BF(REGA, reg) |
            GEM_MAN_BF(CODE, GEM_MAN_CODE);

    err = gem_mdio_frame(eth, frame);
    if (err)
    {
        LOG_W("MDIO read timeout addr=%d reg=%d nsr=0x%x ncr=0x%x",
                addr, reg, macb_readl(eth, GEM_NSR), macb_readl(eth, GEM_NCR));
        rt_mutex_release(&eth->mdio_lock);
        return -RT_EIO;
    }

    data = macb_readl(eth, GEM_MAN) & 0xffff;
    if (gem_mdio_data_invalid(eth, data))
    {
        LOG_W("MDIO read invalid data addr=%d reg=%d man=0x%x",
                addr, reg, macb_readl(eth, GEM_MAN));
        rt_mutex_release(&eth->mdio_lock);
        return -RT_EIO;
    }

    rt_mutex_release(&eth->mdio_lock);
    return (int)data;
}

static int gem_mdio_write(struct mii_bus *bus, int addr, int devad, int reg, rt_uint16_t val)
{
    rt_err_t err;
    rt_uint32_t frame;
    struct macb_eth *eth = bus->priv;

    rt_mutex_take(&eth->mdio_lock, RT_WAITING_FOREVER);

    frame = GEM_MAN_BF(SOF, GEM_MAN_SOF) | GEM_MAN_BF(RW, GEM_MAN_WRITE) |
            GEM_MAN_BF(PHYA, addr) | GEM_MAN_BF(REGA, reg) |
            GEM_MAN_BF(CODE, GEM_MAN_CODE) | GEM_MAN_BF(DATA, val);

    err = gem_mdio_frame(eth, frame);

    rt_mutex_release(&eth->mdio_lock);
    return err ? -RT_EIO : 0;
}

static rt_err_t macb_adjust_link(struct macb_eth *eth)
{
    rt_uint32_t ncfgr;
    struct rt_phy_device *phy = eth->phy;

    if (!phy || !phy->link)
    {
        return -RT_ERROR;
    }

    /* Some platforms return unreadable NCFGR; keep a software shadow. */
    ncfgr = eth->ncfgr_shadow;
    ncfgr &= ~(GEM_NCFGR_SPD | GEM_NCFGR_FD | GEM_NCFGR_GBE |
            (3u << GEM_NCFGR_DBW_SHIFT));
    ncfgr |= macb_gem_dbw(eth);

    if (phy->duplex == DUPLEX_FULL)
    {
        ncfgr |= GEM_NCFGR_FD;
    }

    if (phy->speed == SPEED_1000)
    {
        ncfgr |= GEM_NCFGR_GBE;
    }
    else if (phy->speed == SPEED_100)
    {
        ncfgr |= GEM_NCFGR_SPD;
    }

    eth->ncfgr_shadow = ncfgr;
    macb_writel(eth, GEM_NCFGR, ncfgr);
    if (!eth->native_io)
    {
        macb_mmio_posted_barrier(eth);
    }
    macb_set_tx_clk(eth, phy->speed);

    if (eth->mac_started)
    {
        macb_gem_write_traffic_ier(eth);
    }

    return RT_EOK;
}

static int macb_mdio_bus_reset(struct mii_bus *bus)
{
    struct macb_eth *eth = bus->priv;

    macb_phy_reset(eth);
    return 0;
}

static rt_err_t macb_mii_register(struct macb_eth *eth)
{
    rt_err_t err;

    eth->mii = rt_mdio_alloc();
    if (!eth->mii)
    {
        return -RT_ENOMEM;
    }

    /* Enable MDIO management port (Linux macb_mii_init) */
    eth->ncr_shadow |= GEM_NCR_MPE;
    if (!eth->native_io)
    {
        macb_ncr_posted_write(eth, eth->ncr_shadow);
    }
    else
    {
        macb_writel(eth, GEM_NCR, eth->ncr_shadow);
    }

    eth->mii->priv = eth;
    eth->mii->read = gem_mdio_read;
    eth->mii->write = gem_mdio_write;
    eth->mii->reset = macb_mdio_bus_reset;
    rt_snprintf(eth->mii->name, RT_NAME_MAX, "mii%p", eth);

    if ((err = rt_mdio_register(eth->mii)))
    {
        rt_free(eth->mii);
        eth->mii = RT_NULL;
        return err;
    }

    if (eth->mii->reset)
    {
        eth->mii->reset(eth->mii);
    }

    return RT_EOK;
}

static void macb_mii_unregister(struct macb_eth *eth)
{
    if (eth->mii)
    {
        rt_mdio_unregister(eth->mii);
        rt_free(eth->mii);
        eth->mii = RT_NULL;
    }
}
