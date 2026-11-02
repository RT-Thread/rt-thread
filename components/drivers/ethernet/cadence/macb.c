/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include "macb.h"

#define DBG_TAG "eth.macb"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#define NEXT_TX(i) (((i) + 1) & (MACB_TX_RING_SIZE - 1))
#define NEXT_RX(i) (((i) + 1) & (MACB_RX_RING_SIZE - 1))

#define MACB_PHY_RETRY_INTERVAL_MS      2000
#define MACB_PHY_RETRY_MAX              15

static const struct macb_config macb_cfg_emac, macb_cfg_default_gem;

static rt_size_t macb_desc_stride(struct macb_eth *eth);
static void macb_dma_flush(struct macb_eth *eth, void *ptr, rt_size_t size);
static void macb_dma_inval(struct macb_eth *eth, void *ptr, rt_size_t size);
static rt_err_t macb_mac_enable(struct macb_eth *eth);

rt_weak void macb_plat_mac_enable_prepare(void)
{
}

static void macb_mmio_posted_barrier(struct macb_eth *eth)
{
    (void)macb_readl(eth, GEM_NCR);
    if (!eth->native_io)
    {
        rt_hw_dmb();
    }
}

static void macb_dma_read_barrier(struct macb_eth *eth)
{
    if (!eth->native_io)
    {
        rt_hw_dmb();
        (void)macb_readl(eth, GEM_NCR);
    }
}

#ifdef RT_USING_OFW
static struct rt_clk *macb_find_provider_clk(struct rt_ofw_node *dev_np,
        const char *output_name)
{
    struct rt_ofw_node *bus, *child;

    if (!dev_np || !output_name)
    {
        return RT_NULL;
    }

    for (bus = dev_np->parent; bus; bus = bus->parent)
    {
        rt_ofw_foreach_child_node(bus, child)
        {
            rt_ssize_t n, i;
            const char *oname;

            if (!rt_ofw_get_prop(child, "#clock-cells", RT_NULL))
            {
                continue;
            }

            n = rt_ofw_count_of_clk(child);
            for (i = 0; i < n; ++i)
            {
                if (rt_ofw_prop_read_string_index(child, "clock-output-names",
                        i, &oname))
                {
                    continue;
                }

                if (rt_strcmp(oname, output_name))
                {
                    continue;
                }

                return rt_ofw_get_clk(child, (int)i);
            }
        }
    }

    return RT_NULL;
}
#endif

static void macb_set_tx_clk(struct macb_eth *eth, int speed)
{
    rt_base_t rate, rounded;
    rt_err_t err;

    if (!eth->tx_clk)
    {
        return;
    }

    if (eth->config && (eth->config->caps & MACB_CAP_CLK_HW_CHG))
    {
        return;
    }

#ifdef RT_USING_PHY_V2
    if (eth->phy_interface == RT_PHY_INTERFACE_MODE_MII)
    {
        return;
    }
#endif

    switch (speed)
    {
    case SPEED_10:
        rate = 2500000;
        break;
    case SPEED_100:
        rate = 25000000;
        break;
    case SPEED_1000:
        rate = 125000000;
        break;
    default:
        return;
    }

    err = rt_clk_prepare_enable(eth->tx_clk);
    if (err)
    {
        LOG_W("tx_clk enable failed: %s", rt_strerror(err));
        return;
    }

    rounded = rt_clk_round_rate(eth->tx_clk, rate);
    if (rounded > 0)
    {
        rate = rounded;
    }

    err = rt_clk_set_rate(eth->tx_clk, rate);
    if (err)
    {
        LOG_W("tx_clk set_rate %ld Hz failed: %s", (long)rate, rt_strerror(err));
    }
}

static rt_size_t macb_desc_sync_size(struct macb_eth *eth)
{
    return eth->dma_64bit ?
            macb_desc_stride(eth) : sizeof(struct macb_dma_desc);
}

static void macb_desc_ring_sync(struct macb_eth *eth, rt_bool_t rx, rt_bool_t flush)
{
    rt_size_t bytes;
    void *ptr;

    if (rx)
    {
        bytes = macb_desc_stride(eth) * MACB_RX_RING_SIZE;
        ptr = eth->rx_ring;
    }
    else
    {
        bytes = macb_desc_stride(eth) * MACB_TX_RING_SIZE;
        ptr = eth->tx_ring;
    }

    if (flush)
    {
        macb_dma_flush(eth, ptr, bytes);
    }
    else
    {
        macb_dma_inval(eth, ptr, bytes);
    }
}

static rt_ubase_t macb_dma_flags(struct macb_eth *eth)
{
    /*
     * Bus DMA above 4G (dma-ranges): use uncached CPU mappings so
     * descriptor/buffer writes reach the GEM engine without flush alone.
     */
    if (eth->dma_64bit)
    {
        return RT_DMA_F_LINEAR | RT_DMA_F_NOCACHE;
    }

    return RT_DMA_F_LINEAR;
}

static rt_bool_t macb_hw_supports_dma64(struct macb_eth *eth)
{
    rt_uint32_t dcfg6 = macb_readl(eth, GEM_DCFG6);

    if (dcfg6 == 0xffffffff)
    {
        return RT_FALSE;
    }

    return !!((dcfg6 >> GEM_DCFG6_DAW64_SHIFT) & 1u);
}

static void macb_update_dma64(struct macb_eth *eth, rt_bool_t wide_bus_addr)
{
    if (wide_bus_addr || macb_hw_supports_dma64(eth))
    {
        eth->dma_64bit = RT_TRUE;
    }
}

static void macb_gem_program_dmacfg(struct macb_eth *eth);
static void macb_gem_init_axi(struct macb_eth *eth);
static void macb_gem_init_intmod(struct macb_eth *eth);
static void macb_gem_init_usrio(struct macb_eth *eth);

static void macb_gem_setup_dma_hw(struct macb_eth *eth)
{
    macb_gem_program_dmacfg(eth);
    macb_gem_init_axi(eth);
    macb_gem_init_intmod(eth);
    macb_gem_init_usrio(eth);
}

static void macb_clear_gem_irq(struct macb_eth *eth, rt_uint32_t status);
static void macb_gem_commit_irq_enable(struct macb_eth *eth);
static void macb_gem_write_traffic_ier(struct macb_eth *eth);
static void macb_service_traffic(struct macb_eth *eth);
static rt_bool_t macb_gem_irq_use_q0_bank(struct macb_eth *eth);
static void macb_clocks_get(struct macb_eth *eth, struct rt_device *dev)
{
    eth->pclk = rt_clk_get_by_name(dev, "pclk");
    eth->hclk = rt_clk_get_by_name(dev, "hclk");
    eth->tsu_clk = rt_clk_get_by_name(dev, "tsu_clk");
    eth->tx_clk = rt_clk_get_by_name(dev, "tx_clk");

    if (!eth->tx_clk)
    {
        eth->tx_clk = rt_clk_get_by_index(dev, 3);
    }

    if (!eth->tx_clk)
    {
        eth->tx_clk = rt_clk_get_by_name(dev, "clk_eth");
    }

#ifdef RT_USING_OFW
    if (!eth->tx_clk && dev->ofw_node)
    {
        eth->tx_clk = macb_find_provider_clk(dev->ofw_node, "clk_eth");
    }
#endif

    if (!eth->tx_clk)
    {
        LOG_W("tx_clk missing (RGMII TX clock required for transmit)");
    }
}

static void macb_dma_flush(struct macb_eth *eth, void *ptr, rt_size_t size)
{
    if (ptr && size)
    {
        rt_dma_sync_out_data(eth->dev, ptr, size, RT_NULL, macb_dma_flags(eth));
    }
}

static void macb_dma_inval(struct macb_eth *eth, void *ptr, rt_size_t size)
{
    if (ptr && size)
    {
        rt_dma_sync_in_data(eth->dev, ptr, size, 0, macb_dma_flags(eth));
    }
}

static rt_size_t macb_desc_stride(struct macb_eth *eth)
{
    return eth->dma_64bit ?
            sizeof(struct macb_dma_desc) + sizeof(struct macb_dma_desc_64) :
            sizeof(struct macb_dma_desc);
}

static struct macb_dma_desc *macb_ring_desc(struct macb_dma_desc *ring,
        struct macb_eth *eth, rt_uint32_t idx)
{
    return (struct macb_dma_desc *)((rt_uint8_t *)ring + idx * macb_desc_stride(eth));
}

static struct macb_dma_desc *macb_tx_desc_at(struct macb_eth *eth, rt_uint32_t idx)
{
    return macb_ring_desc(eth->tx_ring, eth, idx);
}

static struct macb_dma_desc *macb_rx_desc_at(struct macb_eth *eth, rt_uint32_t idx)
{
    return macb_ring_desc(eth->rx_ring, eth, idx);
}

static void macb_set_desc_addr(struct macb_eth *eth, struct macb_dma_desc *desc,
        rt_uint64_t addr)
{
    if (eth->dma_64bit)
    {
        struct macb_dma_desc_64 *desc64 = (struct macb_dma_desc_64 *)
                ((rt_uint8_t *)desc + sizeof(*desc));

        desc64->addrh = (rt_uint32_t)(addr >> 32);
        rt_hw_wmb();
    }

    desc->addr = (rt_uint32_t)addr;
}

static void macb_ncr_write(struct macb_eth *eth, rt_uint32_t val)
{
    eth->ncr_shadow = val;
    macb_writel(eth, GEM_NCR, val);
}

static void macb_ncr_posted_write(struct macb_eth *eth, rt_uint32_t val)
{
    macb_ncr_write(eth, val);
    macb_mmio_posted_barrier(eth);
}

static rt_bool_t macb_hw_is_native_io(struct macb_eth *eth)
{
    rt_uint32_t val = GEM_NCR_LLB;

    macb_ncr_write(eth, val);
    val = macb_readl(eth, GEM_NCR);
    macb_ncr_write(eth, 0);

    return val == GEM_NCR_LLB;
}

static void macb_gem_kick_tx(struct macb_eth *eth)
{
    rt_uint32_t ncr;

    /*
     * Linux macb_tx_restart(): merge TSTART with live NCR, then read
     * back to flush posted MMIO writes so the kick reaches GEM.
     */
    macb_mmio_posted_barrier(eth);
    ncr = macb_readl(eth, GEM_NCR) | GEM_NCR_TSTART;
    macb_ncr_write(eth, ncr);
    macb_mmio_posted_barrier(eth);
    eth->ncr_shadow = macb_readl(eth, GEM_NCR);
    eth->ncr_shadow &= ~GEM_NCR_TSTART;
}

static void macb_gem_tx_restart(struct macb_eth *eth)
{
    rt_uint64_t tbqp;
    rt_uint32_t head_idx;
    rt_size_t stride = macb_desc_stride(eth);

    if (eth->tx_head == eth->tx_tail || !stride)
    {
        return;
    }

    tbqp = macb_readl(eth, GEM_TBQP);
    if (eth->dma_64bit)
    {
        tbqp |= (rt_uint64_t)macb_readl(eth, GEM_TBQPH) << 32;
    }

    head_idx = eth->tx_head;
    tbqp = (tbqp - eth->tx_ring_dma) / stride;
    tbqp &= MACB_TX_RING_SIZE - 1;
    head_idx &= MACB_TX_RING_SIZE - 1;

    if (tbqp == head_idx)
    {
        return;
    }

    macb_gem_kick_tx(eth);
}

static rt_bool_t macb_gem_irq_use_q0_bank(struct macb_eth *eth)
{
    rt_uint32_t dcfg1 = macb_readl(eth, GEM_DCFG1);
    if (dcfg1 == 0xffffffff)
    {
        return RT_FALSE;
    }

    /* Linux: GEM DCFG1.IRQCOR selects queue-0 bank @ 0x400/0x600. */
    return !!((dcfg1 >> GEM_DCFG1_IRQCOR_SHIFT) & 1u);
}

static rt_uint32_t macb_gem_isr(struct macb_eth *eth)
{
    rt_uint32_t isr, isr0 = 0;
    rt_bool_t use_q0 = macb_gem_irq_use_q0_bank(eth);

    if (use_q0)
    {
        isr0 = macb_readl(eth, GEM_ISR0);
        if (isr0 && isr0 != 0xffffffff)
        {
            return isr0;
        }
    }

    isr = macb_readl(eth, GEM_ISR);
    if (isr && isr != 0xffffffff)
    {
        return isr;
    }

    /*
     * Legacy ISR @ 0x24 may read 0 when pending; try queue-0 bank
     * @ 0x400 when DCFG1.IRQCOR is clear or ISR0 was not tried yet.
     */
    if (!use_q0 && (eth->native_io || !isr0))
    {
        isr0 = macb_readl(eth, GEM_ISR0);
        if (isr0 && isr0 != 0xffffffff)
        {
            return isr0;
        }
    }

    return 0;
}

static void macb_init_ring_bases(struct macb_eth *eth)
{
    if (eth->dma_64bit)
    {
        macb_writel(eth, GEM_RBQPH, (rt_uint32_t)(eth->rx_ring_dma >> 32));
        macb_writel(eth, GEM_TBQPH, (rt_uint32_t)(eth->tx_ring_dma >> 32));
        macb_writel(eth, GEM_RBQP, (rt_uint32_t)eth->rx_ring_dma);
        macb_writel(eth, GEM_TBQP, (rt_uint32_t)eth->tx_ring_dma);
    }
    else
    {
        macb_writel(eth, GEM_RBQP, (rt_uint32_t)eth->rx_ring_dma);
        macb_writel(eth, GEM_TBQP, (rt_uint32_t)eth->tx_ring_dma);
    }

    if (!eth->native_io)
    {
        macb_mmio_posted_barrier(eth);
    }
    else if (!eth->mac_started)
    {
        (void)macb_readl(eth, GEM_TBQP);
        if (eth->dma_64bit)
        {
            (void)macb_readl(eth, GEM_TBQPH);
        }
    }
    else
    {
        rt_hw_dsb();
    }
}

static rt_uint32_t macb_gem_build_dmacfg(struct macb_eth *eth)
{
    rt_uint32_t dmacfg = 0;

    dmacfg |= (MACB_RX_BUFFER_SIZE_DIV64 & GEM_DMACFG_RXBS_MASK) << GEM_DMACFG_RXBS_SHIFT;
    dmacfg |= RT_BIT(GEM_DMACFG_TXPBMS_SHIFT);
    dmacfg |= (3u << GEM_DMACFG_RXBMS_SHIFT);
    if (!eth->native_io)
    {
        dmacfg |= RT_BIT(GEM_DMACFG_ENDIA_DESC_SHIFT);
    }
    if (eth->dma_64bit)
    {
        dmacfg |= RT_BIT(GEM_DMACFG_ADDR64_SHIFT);
    }
    if (eth->config && eth->config->dma_burst_length)
    {
        dmacfg |= (eth->config->dma_burst_length & 0x1f) << GEM_DMACFG_FBLDO_SHIFT;
    }

    return dmacfg;
}

static void macb_detect_caps(struct macb_eth *eth)
{
    rt_uint32_t dcfg1 = macb_readl(eth, GEM_DCFG1);

    eth->isr_clear_on_write = RT_FALSE;

    if (dcfg1 != 0xffffffff &&
            !((dcfg1 >> GEM_DCFG1_IRQCOR_SHIFT) & 1u))
    {
        eth->isr_clear_on_write = RT_TRUE;
    }
}

static void macb_gem_program_dmacfg(struct macb_eth *eth)
{
    rt_uint32_t dmacfg = macb_gem_build_dmacfg(eth);

    macb_writel(eth, GEM_DMACFG, dmacfg);
    if (!eth->native_io)
    {
        macb_mmio_posted_barrier(eth);
    }
    else
    {
        (void)macb_readl(eth, GEM_DMACFG);
    }
}

/*
 * U-Boot gmac_init_multi_queues(): point unused queue 1+ rings at a
 * dummy TX_USED descriptor so the GEM DMA engine stays idle on them.
 */
static rt_err_t macb_gem_init_multi_queues(struct macb_eth *eth)
{
    rt_uint32_t queue_mask;
    int i, num_queues = 1;

    if (!eth->is_gem || !eth->dummy_desc)
    {
        return RT_EOK;
    }

    eth->dummy_desc->ctrl = GEM_TX_USED;
    eth->dummy_desc->addr = 0;
    if (eth->dma_64bit)
    {
        struct macb_dma_desc_64 *d64 = (struct macb_dma_desc_64 *)
                ((rt_uint8_t *)eth->dummy_desc + sizeof(*eth->dummy_desc));

        d64->addrh = 0;
    }
    macb_dma_flush(eth, eth->dummy_desc, eth->dummy_desc_size);

    queue_mask = macb_readl(eth, GEM_DCFG6) & 0xff;
    if (queue_mask == 0xffffffff)
    {
        queue_mask = 0x1;
    }
    queue_mask |= 0x1;

    for (i = 1; i < MACB_MAX_QUEUES; ++i)
    {
        if (queue_mask & RT_BIT(i))
        {
            ++num_queues;
        }
    }

    for (i = 1; i < num_queues; ++i)
    {
        /*
         * Queue 1+ low pointers only; TBQPH/RBQPH are shared for queue 0
         * (see Linux macb_init_buffers()).
         */
        macb_writel(eth, GEM_QUEUE_TBQP(i - 1), (rt_uint32_t)eth->dummy_desc_dma);
        macb_writel(eth, GEM_QUEUE_RBQP(i - 1), (rt_uint32_t)eth->dummy_desc_dma);
    }

    if (!eth->native_io)
    {
        macb_mmio_posted_barrier(eth);
    }
    else
    {
        (void)macb_readl(eth, GEM_TBQP);
    }
    return RT_EOK;
}

static rt_bool_t macb_phy_interface_is_rgmii(int mode)
{
#ifdef RT_USING_PHY_V2
    return mode == RT_PHY_INTERFACE_MODE_RGMII ||
           mode == RT_PHY_INTERFACE_MODE_RGMII_ID ||
           mode == RT_PHY_INTERFACE_MODE_RGMII_RXID ||
           mode == RT_PHY_INTERFACE_MODE_RGMII_TXID;
#else
    RT_UNUSED(mode);
    return RT_FALSE;
#endif
}

static void macb_parse_dt_props(struct macb_eth *eth)
{
    struct rt_device *dev = eth->dev;
    rt_uint32_t val;

#ifdef RT_USING_OFW
    if (!dev || !dev->ofw_node)
    {
        return;
    }

#ifdef RT_USING_PHY_V2
    if (rt_ofw_get_interface(dev->ofw_node, (rt_phy_interface *)&eth->phy_interface))
    {
        eth->phy_interface = RT_PHY_INTERFACE_MODE_NA;
    }
#endif

    eth->phy_reset_pin = rt_pin_get_named_pin(dev, "phy-reset", 0,
            RT_NULL, &eth->phy_reset_active);
    if (eth->phy_reset_pin < 0)
    {
        eth->phy_reset_pin = -1;
    }

    eth->phy_reset_ms = 10;
    rt_dm_dev_prop_read_u32(dev, "phy-reset-duration", &val);
    if (val > 0 && val <= 1000)
    {
        eth->phy_reset_ms = val;
    }

    if (!rt_dm_dev_prop_read_u32(dev, "cdns,aw2w-max-pipe", &val))
    {
        eth->aw2w_max_pipe = val;
    }
    if (!rt_dm_dev_prop_read_u32(dev, "cdns,ar2r-max-pipe", &val))
    {
        eth->ar2r_max_pipe = val;
    }
    eth->use_aw2b_fill = rt_dm_dev_prop_read_bool(dev, "cdns,use-aw2b-fill");
#endif
}

static void macb_phy_reset(struct macb_eth *eth)
{
    rt_uint32_t ms;

    if (eth->phy_reset_pin < 0)
    {
        return;
    }

    ms = eth->phy_reset_ms ? eth->phy_reset_ms : 10;

    rt_pin_mode(eth->phy_reset_pin, PIN_MODE_OUTPUT);
    rt_pin_write(eth->phy_reset_pin, eth->phy_reset_active);
    rt_hw_us_delay(ms * 1000);
    rt_pin_write(eth->phy_reset_pin, !eth->phy_reset_active);
    rt_hw_us_delay(100000);
}

static void macb_gem_init_usrio(struct macb_eth *eth)
{
    rt_uint32_t usrio = 0;
    rt_uint32_t ncr_save = eth->ncr_shadow;
    int mode = eth->phy_interface;

    if (eth->config && (eth->config->caps & MACB_CAP_USRIO_DISABLED))
    {
        return;
    }

#ifdef RT_USING_PHY_V2
    if (mode == RT_PHY_INTERFACE_MODE_NA && eth->phy)
    {
        mode = eth->phy->interface;
    }
#endif

    if (macb_phy_interface_is_rgmii(mode))
    {
        usrio = GEM_USRIO_RGMII;
    }

    /* Program USRIO with MAC TX/RX off so the mode latch takes effect. */
    macb_ncr_write(eth, ncr_save & ~(GEM_NCR_TE | GEM_NCR_RE));
    macb_writel(eth, GEM_USRIO, usrio);
    rt_hw_dsb();
    macb_ncr_write(eth, ncr_save);
}

static void macb_gem_init_intmod(struct macb_eth *eth)
{
    rt_uint32_t throttle = (1000 * 50) / 800;
    rt_uint32_t intmod = 0;

    intmod |= (throttle & 0xffu) << GEM_INTMOD_TX_MOD_SHIFT;
    intmod |= (throttle & 0xffu) << GEM_INTMOD_RX_MOD_SHIFT;
    macb_writel(eth, GEM_INTMOD, intmod);
}

static void macb_gem_init_axi(struct macb_eth *eth)
{
    rt_uint32_t amp;
    rt_uint8_t aw2w = eth->aw2w_max_pipe;
    rt_uint8_t ar2r = eth->ar2r_max_pipe;

    if (!aw2w && !ar2r && !eth->use_aw2b_fill)
    {
        return;
    }

    /* Preserve reset defaults; zeroing AMP can break remote GEM DMA. */
    amp = macb_readl(eth, GEM_AMP);
    if (eth->use_aw2b_fill)
    {
        amp |= RT_BIT(GEM_AMP_AW2B_FILL_SHIFT);
    }
    if (aw2w)
    {
        amp &= ~((rt_uint32_t)0xffu << GEM_AMP_AW2W_MAX_PIPE_SHIFT);
        amp |= (aw2w & 0xffu) << GEM_AMP_AW2W_MAX_PIPE_SHIFT;
    }
    if (ar2r)
    {
        amp &= ~((rt_uint32_t)0xffu << GEM_AMP_AR2R_MAX_PIPE_SHIFT);
        amp |= (ar2r & 0xffu) << GEM_AMP_AR2R_MAX_PIPE_SHIFT;
    }

    macb_writel(eth, GEM_AMP, amp);
    if (!eth->native_io)
    {
        macb_mmio_posted_barrier(eth);
    }
}

static void macb_rx_refill(struct macb_eth *eth, rt_uint32_t idx)
{
    struct macb_dma_desc *d = macb_rx_desc_at(eth, idx);
    rt_uint64_t p = eth->rx_buffer_dma + idx * MACB_RX_BUFFER_SIZE;
    rt_size_t dsz = macb_desc_sync_size(eth);

    d->ctrl = 0;
    if (eth->dma_64bit)
    {
        macb_set_desc_addr(eth, d, p);
    }
    else
    {
        d->addr = (rt_uint32_t)p;
    }
    d->addr &= ~GEM_RX_USED;
    if (idx == MACB_RX_RING_SIZE - 1)
    {
        d->addr |= GEM_RX_WRAP;
    }

    macb_dma_flush(eth, d, dsz);
}

static void macb_tx_cleanup(struct macb_eth *eth)
{
    rt_uint32_t tail = eth->tx_tail;

    while (tail != eth->tx_head)
    {
        struct macb_dma_desc *d = macb_tx_desc_at(eth, tail);
        rt_size_t dsz = macb_desc_sync_size(eth);

        macb_dma_inval(eth, d, dsz);
        if (!eth->native_io)
        {
            macb_dma_read_barrier(eth);
        }
        else
        {
            rt_hw_dmb();
        }
        if (!(d->ctrl & GEM_TX_USED))
        {
            break;
        }

        d->ctrl = GEM_TX_USED;
        if (tail == MACB_TX_RING_SIZE - 1)
        {
            d->ctrl |= GEM_TX_WRAP;
        }
        rt_hw_dmb();
        macb_dma_flush(eth, d, dsz);

        rt_sem_release(&eth->tx_sem);
        tail = NEXT_TX(tail);
    }

    eth->tx_tail = tail;
}

/*
 * Poll TX/RX completion without clearing GEM ISR/TSR/IDR. Used when a
 * hardware IRQ is installed (level-triggered MSI/MSIX must stay asserted).
 */
static void macb_poll_completions(struct macb_eth *eth)
{
    struct macb_dma_desc *d;

    macb_tx_cleanup(eth);

    d = macb_rx_desc_at(eth, eth->rx_tail);
    macb_dma_inval(eth, d, macb_desc_sync_size(eth));
    rt_hw_dmb();
    if (d->addr & GEM_RX_USED)
    {
        eth_device_ready(&eth->parent);
    }
}

static rt_err_t macb_eth_tx(rt_device_t dev, struct pbuf *p)
{
    struct macb_eth *eth = raw_to_macb_eth(dev);
    struct macb_dma_desc *d;
    rt_uint32_t ctrl;
    rt_uint8_t *buf;

    if (!eth->hw_ready || !eth->mac_started)
    {
        return -RT_EBUSY;
    }

    if (!eth->phy || !eth->phy->link)
    {
        return -RT_EBUSY;
    }

    if (p->tot_len > eth->max_tx_len || p->tot_len > MACB_RX_BUFFER_SIZE)
    {
        return -RT_EINVAL;
    }

    if (rt_sem_take(&eth->tx_sem, RT_WAITING_FOREVER) != RT_EOK)
    {
        return -RT_EBUSY;
    }

    {
        rt_uint32_t slot = eth->tx_head;
        rt_uint64_t buf_dma = eth->tx_buffer_dma + slot * MACB_RX_BUFFER_SIZE;

        d = macb_tx_desc_at(eth, slot);
        buf = eth->tx_buffer + slot * MACB_RX_BUFFER_SIZE;

        pbuf_copy_partial(p, buf, p->tot_len, 0);
        rt_hw_dmb();
        macb_dma_flush(eth, buf, p->tot_len);

        ctrl = (p->tot_len & GEM_TX_LEN_MASK) | GEM_TX_LAST;
        if (slot == MACB_TX_RING_SIZE - 1)
        {
            ctrl |= GEM_TX_WRAP;
        }

        macb_set_desc_addr(eth, d, buf_dma);
        rt_hw_wmb();
        d->ctrl = ctrl;
        rt_hw_wmb();
        macb_desc_ring_sync(eth, RT_FALSE, RT_TRUE);

        eth->tx_head = NEXT_TX(eth->tx_head);
        macb_gem_kick_tx(eth);
        macb_gem_tx_restart(eth);
        /*
         * With irq_installed: poll completions only. service_traffic()
         * clears ISR and can drop level-triggered MSI/MSIX lines.
         */
        if (eth->irq_installed)
        {
            macb_poll_completions(eth);
        }
        else
        {
            macb_service_traffic(eth);
        }
    }

    eth_device_ready(&eth->parent);

    return RT_EOK;
}

static struct pbuf *macb_eth_rx(rt_device_t dev)
{
    struct macb_eth *eth = raw_to_macb_eth(dev);
    struct macb_dma_desc *d;
    rt_uint32_t ctrl;
    rt_uint32_t addr;
    rt_uint16_t len;
    struct pbuf *p = RT_NULL;

    if (eth->irq_installed)
    {
        macb_poll_completions(eth);
    }
    else
    {
        macb_service_traffic(eth);
    }

    d = macb_rx_desc_at(eth, eth->rx_tail);
    macb_dma_inval(eth, d, macb_desc_sync_size(eth));
    rt_hw_dmb();
    addr = d->addr;

    /* Ownership: HW sets RX_USED in addr when a frame is in the buffer */
    if (!(addr & GEM_RX_USED))
    {
        return RT_NULL;
    }

    ctrl = d->ctrl;

    if (!((ctrl & GEM_RX_SOF) && (ctrl & GEM_RX_EOF)))
    {
        macb_rx_refill(eth, eth->rx_tail);
        eth->rx_tail = NEXT_RX(eth->rx_tail);
        return RT_NULL;
    }

    len = (rt_uint16_t)(ctrl & GEM_RX_LEN_MASK);
    if (len == 0 || len > MACB_RX_BUFFER_SIZE)
    {
        macb_rx_refill(eth, eth->rx_tail);
        eth->rx_tail = NEXT_RX(eth->rx_tail);
        return RT_NULL;
    }

    {
        rt_uint8_t *buf = eth->rx_buffer + eth->rx_tail * MACB_RX_BUFFER_SIZE;

        macb_dma_inval(eth, buf, len);
        rt_hw_dmb();

        p = pbuf_alloc(PBUF_RAW, len, PBUF_RAM);
        if (p)
        {
            rt_memcpy(p->payload, buf, len);
        }
    }

    macb_rx_refill(eth, eth->rx_tail);
    eth->rx_tail = NEXT_RX(eth->rx_tail);

    return p;
}

static rt_err_t macb_eth_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err = RT_EOK;
    struct macb_eth *eth = raw_to_macb_eth(dev);

    switch (cmd)
    {
    case NIOCTL_GADDR:
        if (args)
        {
            rt_memcpy(args, eth->mac, sizeof(eth->mac));
        }
        else
        {
            err = -RT_EINVAL;
        }
        break;

    default:
        err = -RT_EINVAL;
        break;
    }

    return err;
}

#ifdef RT_USING_DEVICE_OPS
const static struct rt_device_ops macb_eth_ops =
{
    .control = macb_eth_control,
};
#endif

static void macb_clear_gem_irq(struct macb_eth *eth, rt_uint32_t status)
{
    if (!status || status == 0xffffffff)
    {
        return;
    }

    if (status & GEM_INT_RX_BITS)
    {
        macb_writel(eth, GEM_RSR, macb_readl(eth, GEM_RSR));
    }

    if (status & GEM_INT_TX_BITS)
    {
        macb_writel(eth, GEM_TSR, macb_readl(eth, GEM_TSR));
    }

    if (macb_gem_irq_use_q0_bank(eth))
    {
        macb_writel(eth, GEM_ISR0, status);
    }
    macb_writel(eth, GEM_ISR, status);
    macb_mmio_posted_barrier(eth);
}

static void macb_gem_commit_irq_enable(struct macb_eth *eth)
{
    rt_uint32_t mask = GEM_INT_RX_BITS | GEM_INT_TX_BITS | GEM_INT_HRESP;
    rt_uint32_t imr, pending;
    rt_bool_t use_q0 = macb_gem_irq_use_q0_bank(eth);

    if (use_q0)
    {
        pending = macb_readl(eth, GEM_ISR0);
        if (pending == 0xffffffff)
        {
            pending = 0;
        }
    }
    else
    {
        pending = macb_readl(eth, GEM_ISR);
    }
    if (pending != 0xffffffff && pending)
    {
        macb_clear_gem_irq(eth, pending);
    }

    if (use_q0)
    {
        macb_writel(eth, GEM_IDR0, 0xffffffff);
        macb_writel(eth, GEM_ISR0, 0xffffffff);
    }
    macb_writel(eth, GEM_IDR, 0xffffffff);
    if (eth->isr_clear_on_write)
    {
        macb_writel(eth, GEM_ISR, 0xffffffff);
    }

    macb_writel(eth, GEM_IER, mask);
    if (use_q0)
    {
        macb_writel(eth, GEM_IER0, mask);
    }
    macb_mmio_posted_barrier(eth);

    imr = use_q0 ? macb_readl(eth, GEM_IMR0) : macb_readl(eth, GEM_IMR);
    if (imr == 0xffffffff)
    {
        imr = macb_readl(eth, GEM_IMR);
    }
    if (!(imr & GEM_INT_RCOMP))
    {
        if (use_q0)
        {
            macb_writel(eth, GEM_IER0, GEM_INT_RCOMP);
        }
        else
        {
            macb_writel(eth, GEM_IER, GEM_INT_RCOMP);
        }
        macb_mmio_posted_barrier(eth);
        if (use_q0)
        {
            macb_writel(eth, GEM_IER0, mask);
        }
        else
        {
            macb_writel(eth, GEM_IER, mask);
        }
        macb_mmio_posted_barrier(eth);
        imr = use_q0 ? macb_readl(eth, GEM_IMR0) : macb_readl(eth, GEM_IMR);
    }
}

static void macb_gem_write_traffic_ier(struct macb_eth *eth)
{
    rt_uint32_t mask = GEM_INT_RX_BITS | GEM_INT_TX_BITS | GEM_INT_HRESP;

    macb_writel(eth, GEM_IER, mask);
    if (macb_gem_irq_use_q0_bank(eth))
    {
        macb_writel(eth, GEM_IER0, mask);
    }
    macb_mmio_posted_barrier(eth);
}

static void macb_service_traffic(struct macb_eth *eth)
{
    rt_uint32_t status = macb_gem_isr(eth);

    if (!status)
    {
        rt_uint32_t rsr = macb_readl(eth, GEM_RSR);
        rt_uint32_t tsr = macb_readl(eth, GEM_TSR);

        if (rsr & (GEM_RSR_REC | GEM_RSR_BNA | GEM_RSR_OVR))
        {
            status |= GEM_INT_RCOMP;
        }
        if (tsr & (GEM_TSR_TGO | GEM_TSR_COMP))
        {
            status |= GEM_INT_TCOMP;
        }
    }

    while (status)
    {
        if (status & GEM_INT_RX_BITS)
        {
            rt_uint32_t rsr = macb_readl(eth, GEM_RSR);

            macb_writel(eth, GEM_IDR, GEM_INT_RX_BITS);
            macb_writel(eth, GEM_RSR, rsr);
            eth_device_ready(&eth->parent);
            macb_gem_write_traffic_ier(eth);
        }

        if (status & GEM_INT_TX_BITS)
        {
            rt_uint32_t tsr = macb_readl(eth, GEM_TSR);

            macb_writel(eth, GEM_IDR, GEM_INT_TCOMP);
            macb_writel(eth, GEM_TSR, tsr);
            macb_tx_cleanup(eth);
            macb_writel(eth, GEM_IER, GEM_INT_TCOMP);
            macb_mmio_posted_barrier(eth);
        }

        if (status & GEM_INT_HRESP)
        {
            LOG_E("GEM HRESP bus error");
        }

        macb_clear_gem_irq(eth, status);
        status = macb_gem_isr(eth);
        if (!eth->native_io && status == 0xffffffff)
        {
            break;
        }
    }

    macb_tx_cleanup(eth);
}

static void macb_eth_isr(int irq, void *param)
{
    struct macb_eth *eth = param;

    RT_UNUSED(irq);

    macb_service_traffic(eth);
}

#include "macb_phy.c"

static int macb_find_phy_addr(struct macb_eth *eth)
{
    int addr;

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
#endif

    for (addr = 0; addr < 32; ++addr)
    {
        int id = gem_mdio_read(eth->mii, addr, 0, RT_MII_PHYSID1);

        if (id > 0 && id != 0xffff)
        {
            return addr;
        }
    }

    return -1;
}

static void macb_set_mac_addr(struct macb_eth *eth)
{
    rt_uint32_t lo;
    rt_uint16_t hi;

    lo = eth->mac[0] | (eth->mac[1] << 8) | (eth->mac[2] << 16) | (eth->mac[3] << 24);
    hi = eth->mac[4] | (eth->mac[5] << 8);
    macb_writel(eth, GEM_SA1B, lo);
    macb_writel(eth, GEM_SA1T, hi);
}

static rt_bool_t macb_phy_poll_link(struct macb_eth *eth)
{
    rt_uint32_t bmsr;

    if (!eth->phy)
    {
        return RT_FALSE;
    }

    bmsr = rt_phy_read(eth->phy, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);
    if (bmsr < 0 || bmsr == 0xffff)
    {
        eth->phy->link = 0;
        return RT_FALSE;
    }

    if (!(bmsr & RT_BMSR_LSTATUS))
    {
        bmsr = rt_phy_read(eth->phy, RT_MDIO_DEVAD_NONE, RT_MII_BMSR);
    }
    if (bmsr < 0 || bmsr == 0xffff || !(bmsr & RT_BMSR_LSTATUS))
    {
        eth->phy->link = 0;
        return RT_FALSE;
    }

    eth->phy->link = 1;
    if (rt_genphy_parse_link(eth->phy))
    {
        eth->phy->link = 0;
        return RT_FALSE;
    }

    return RT_TRUE;
}

static rt_err_t macb_start(struct macb_eth *eth)
{
    rt_err_t err;

    if (eth->mac_started)
    {
        return RT_EOK;
    }

    if (!eth->phy)
    {
        return -RT_ERROR;
    }

    if (!eth->phy_configured)
    {
        err = rt_phy_config(eth->phy);
        if (err < 0)
        {
            LOG_W("PHY config failed: %s", rt_strerror(err));
            return err;
        }

        eth->phy_configured = RT_TRUE;
    }

    err = rt_phy_startup(eth->phy);
    if (err)
    {
        LOG_W("PHY startup failed: %s", rt_strerror(err));
        return err;
    }

    if (!eth->phy->link)
    {
        return RT_EOK;
    }

    return macb_mac_enable(eth);
}

static void macb_phy_link_up(struct macb_eth *eth)
{
    if (!eth->mac_started)
    {
        if (macb_mac_enable(eth) != RT_EOK)
        {
            LOG_W("MAC enable on link up failed");
            return;
        }
    }
    else if (macb_adjust_link(eth))
    {
        LOG_W("Adjust PHY link failed");
        return;
    }
    eth_device_linkchange(&eth->parent, RT_TRUE);
}

static void macb_phy_link_down(struct macb_eth *eth)
{
    if (eth->phy)
    {
        eth->phy->link = 0;
    }

    eth_device_linkchange(&eth->parent, RT_FALSE);
}

static void macb_prepare_rings(struct macb_eth *eth)
{
    for (int i = 0; i < MACB_RX_RING_SIZE; ++i)
    {
        macb_rx_refill(eth, i);
    }

    eth->rx_tail = 0;
    eth->tx_head = 0;
    eth->tx_tail = 0;
    rt_hw_dmb();
    macb_init_ring_bases(eth);
    macb_gem_init_multi_queues(eth);
    /* U-Boot gmac_init_multi_queues() touches TBQPH/RBQPH — restore queue 0. */
    macb_init_ring_bases(eth);
}

static rt_err_t macb_mac_enable(struct macb_eth *eth)
{
    rt_err_t err;

    if (eth->mac_started)
    {
        return RT_EOK;
    }

    if (!eth->phy || !eth->phy->link)
    {
        return -RT_ERROR;
    }

    if ((err = macb_adjust_link(eth)))
    {
        LOG_W("Adjust link failed: %s", rt_strerror(err));
        return err;
    }

    macb_plat_mac_enable_prepare();
    macb_prepare_rings(eth);
    macb_gem_program_dmacfg(eth);
    macb_gem_init_usrio(eth);
    if (eth->dma_64bit)
    {
        macb_gem_init_axi(eth);
        macb_gem_init_intmod(eth);
    }
    (void)macb_gem_isr(eth);
    if (macb_gem_irq_use_q0_bank(eth))
    {
        macb_writel(eth, GEM_IDR0, 0xffffffff);
    }
    macb_writel(eth, GEM_IDR, 0xffffffff);
    if (eth->isr_clear_on_write)
    {
        if (macb_gem_irq_use_q0_bank(eth))
        {
            macb_writel(eth, GEM_ISR0, 0xffffffff);
        }
        macb_writel(eth, GEM_ISR, 0xffffffff);
    }
    macb_mmio_posted_barrier(eth);

    /* Linux mac_link_up(): enable IER before asserting TE|RE. */
    macb_gem_commit_irq_enable(eth);

    macb_ncr_posted_write(eth, GEM_NCR_TE | GEM_NCR_RE | GEM_NCR_MPE);
    eth->ncr_shadow = GEM_NCR_TE | GEM_NCR_RE | GEM_NCR_MPE;
    macb_init_ring_bases(eth);

    if (eth->dma_64bit)
    {
        rt_uint32_t dmacfg = macb_readl(eth, GEM_DMACFG);

        if (!(dmacfg & RT_BIT(GEM_DMACFG_ADDR64_SHIFT)))
        {
            LOG_E("DMACFG missing ADDR64 bit");
        }
    }

    eth_device_ready(&eth->parent);

    eth->mac_started = RT_TRUE;

    return RT_EOK;
}

#ifdef RT_USING_SYSTEM_WORKQUEUE
static void macb_phy_retry_work(struct rt_work *work, void *work_data)
{
    struct macb_eth *eth = work_data;

    RT_UNUSED(work);

    if (!eth->mac_started)
    {
        if (macb_start(eth) == RT_EOK)
        {
            eth->phy_retry_count = 0;
            if (eth->phy->link)
            {
                macb_phy_link_up(eth);
            }
            else
            {
                macb_phy_link_down(eth);
                rt_work_submit(&eth->phy_retry_work,
                        rt_tick_from_millisecond(MACB_PHY_RETRY_INTERVAL_MS));
            }
        }
        else
        {
            eth->phy_retry_count++;
            if (eth->phy_retry_count < MACB_PHY_RETRY_MAX)
            {
                rt_work_submit(&eth->phy_retry_work,
                        rt_tick_from_millisecond(MACB_PHY_RETRY_INTERVAL_MS));
            }
            else
            {
                LOG_W("MAC start retry stopped");
                eth->phy_retry_count = 0;
            }
        }
        return;
    }

    if (eth->phy->link)
    {
        eth->phy_retry_count = 0;
        if (!eth->mac_started)
        {
            macb_phy_link_up(eth);
        }
        return;
    }

    if (macb_phy_poll_link(eth))
    {
        eth->phy_retry_count = 0;
        macb_phy_link_up(eth);
        return;
    }

    eth->phy_retry_count++;
    if (eth->phy_retry_count < MACB_PHY_RETRY_MAX)
    {
        rt_work_submit(&eth->phy_retry_work,
                rt_tick_from_millisecond(MACB_PHY_RETRY_INTERVAL_MS));
    }
    else
    {
        LOG_W("PHY link retry stopped, wait for link IRQ");
        eth->phy_retry_count = 0;
    }
}
#endif

rt_err_t macb_eth_hw_init(struct macb_eth *eth)
{
    rt_err_t err;
    int phy_addr;
    void *blob;
    rt_size_t blob_sz, rx_ring_bytes, tx_ring_bytes;
    rt_ubase_t dma_handle;
    rt_ubase_t pclk_hz = 0;
    rt_uint32_t ncfgr;

    if (!eth->config)
    {
        eth->config = &macb_cfg_default_gem;
    }

    eth->max_tx_len = eth->config->max_tx_len ? eth->config->max_tx_len : 0x3fc0; /* GEM_MAX_TX_LEN */

    if (eth->pclk)
    {
        rt_clk_prepare_enable(eth->pclk);
        pclk_hz = rt_clk_get_rate(eth->pclk);
    }
    if (eth->hclk)
    {
        rt_clk_prepare_enable(eth->hclk);
    }
    if (eth->tsu_clk)
    {
        rt_clk_prepare_enable(eth->tsu_clk);
    }
    rt_mutex_init(&eth->mdio_lock, "macb_mdio", RT_IPC_FLAG_PRIO);
    rt_sem_init(&eth->tx_sem, "macb_tx", MACB_TX_RING_SIZE, RT_IPC_FLAG_FIFO);

    eth->is_gem = RT_TRUE;
    eth->dma_64bit = RT_FALSE;
    eth->native_io = RT_FALSE;
    eth->mac_started = RT_FALSE;
    eth->hw_ready = RT_FALSE;
    eth->ncr_shadow = 0;
    eth->ncfgr_shadow = 0;

    macb_writel(eth, GEM_NCR, 0);
    rt_hw_us_delay(20);
    macb_writel(eth, GEM_IDR, 0xffffffff);
    macb_writel(eth, GEM_ISR, 0xffffffff);

    eth->native_io = macb_hw_is_native_io(eth);
    macb_update_dma64(eth, RT_FALSE);
    macb_detect_caps(eth);

    macb_writel(eth, GEM_JML, eth->config->jumbo_max_len ? eth->config->jumbo_max_len : 0x2400);

    /* NCFGR: MDC divider, DBW, standard GEM flags */
    pclk_hz = pclk_hz ? : 150000000;

    ncfgr = gem_ncfgr_mdc_div(pclk_hz);
    ncfgr |= GEM_NCFGR_BIG | GEM_NCFGR_DRFCS;
    ncfgr |= macb_gem_dbw(eth);
    eth->ncfgr_shadow = ncfgr;
    macb_writel(eth, GEM_NCFGR, ncfgr);
    if (!eth->native_io)
    {
        macb_mmio_posted_barrier(eth);
    }

    rx_ring_bytes = macb_desc_stride(eth) * MACB_RX_RING_SIZE;
    tx_ring_bytes = macb_desc_stride(eth) * MACB_TX_RING_SIZE;
    blob_sz = rx_ring_bytes + tx_ring_bytes +
              MACB_RX_RING_SIZE * MACB_RX_BUFFER_SIZE +
              MACB_TX_RING_SIZE * MACB_RX_BUFFER_SIZE;

    {
        rt_ubase_t dma_flags = macb_dma_flags(eth);

        blob = rt_dma_alloc(eth->dev, blob_sz, &dma_handle, dma_flags);
    }

    if (!blob)
    {
        err = -RT_ENOMEM;
        goto _fail_sem;
    }

    eth->rx_ring = (struct macb_dma_desc *)blob;
    eth->tx_ring = (struct macb_dma_desc *)((rt_uint8_t *)blob + rx_ring_bytes);
    eth->rx_buffer = (rt_uint8_t *)((rt_uint8_t *)eth->tx_ring + tx_ring_bytes);
    eth->tx_buffer = eth->rx_buffer + MACB_RX_RING_SIZE * MACB_RX_BUFFER_SIZE;
    eth->dma_blob_size = blob_sz;
    eth->dma_blob_handle = dma_handle;

    eth->rx_ring_dma = dma_handle;
    eth->tx_ring_dma = dma_handle + rx_ring_bytes;
    eth->rx_buffer_dma = dma_handle + rx_ring_bytes + tx_ring_bytes;
    eth->tx_buffer_dma = eth->rx_buffer_dma + MACB_RX_RING_SIZE * MACB_RX_BUFFER_SIZE;

    if (eth->rx_ring_dma > 0xffffffffULL)
    {
        macb_update_dma64(eth, RT_TRUE);
    }

    if (eth->rx_ring_dma > 0xffffffffULL && !eth->dma_64bit)
    {
        LOG_E("DMA bus addr %#llx exceeds 32-bit; enable GEM ADDR64",
                (unsigned long long)eth->rx_ring_dma);
        err = -RT_EINVAL;
        goto _fail_blob;
    }

    if (eth->dma_64bit)
    {
        macb_gem_setup_dma_hw(eth);
    }
    else
    {
        rt_uint32_t dmacfg;

        dmacfg = macb_readl(eth, GEM_DMACFG);
        dmacfg &= ~(GEM_DMACFG_RXBS_MASK << GEM_DMACFG_RXBS_SHIFT);
        dmacfg |= (MACB_RX_BUFFER_SIZE_DIV64 & GEM_DMACFG_RXBS_MASK) << GEM_DMACFG_RXBS_SHIFT;
        dmacfg |= RT_BIT(GEM_DMACFG_TXPBMS_SHIFT);
        dmacfg |= (3u << GEM_DMACFG_RXBMS_SHIFT);
        dmacfg &= ~RT_BIT(GEM_DMACFG_ENDIA_PKT_SHIFT);
        dmacfg &= ~RT_BIT(GEM_DMACFG_ENDIA_DESC_SHIFT);
        dmacfg &= ~RT_BIT(GEM_DMACFG_ADDR64_SHIFT);
        if (eth->config->dma_burst_length)
        {
            dmacfg &= ~(0x1f << GEM_DMACFG_FBLDO_SHIFT);
            dmacfg |= (eth->config->dma_burst_length & 0x1f) << GEM_DMACFG_FBLDO_SHIFT;
        }
        macb_writel(eth, GEM_DMACFG, dmacfg);
        macb_writel(eth, GEM_USRIO, 0);
    }

    eth->dummy_desc_size = macb_desc_stride(eth);
    if (eth->dma_64bit)
    {
        if (!(eth->dummy_desc = rt_dma_alloc(eth->dev, eth->dummy_desc_size,
                &eth->dummy_desc_dma, macb_dma_flags(eth))))
        {
            err = -RT_ENOMEM;
            goto _fail_blob;
        }
    }

    rt_memset(eth->rx_ring, 0, rx_ring_bytes + tx_ring_bytes);

    for (int i = 0; i < MACB_RX_RING_SIZE; ++i)
    {
        macb_rx_refill(eth, i);
    }

    for (int i = 0; i < MACB_TX_RING_SIZE; ++i)
    {
        struct macb_dma_desc *d = macb_tx_desc_at(eth, i);
        rt_uint64_t p = eth->tx_buffer_dma + i * MACB_RX_BUFFER_SIZE;
        rt_size_t dsz = macb_desc_sync_size(eth);

        if (eth->dma_64bit)
        {
            macb_set_desc_addr(eth, d, p);
        }
        else
        {
            d->addr = (rt_uint32_t)p;
        }
        d->ctrl = GEM_TX_USED;
        if (i == MACB_TX_RING_SIZE - 1)
        {
            d->ctrl |= GEM_TX_WRAP;
        }
        macb_dma_flush(eth, d, dsz);
    }

    eth->rx_tail = 0;
    eth->tx_head = 0;
    eth->tx_tail = 0;

    rt_hw_dmb();

    /* Ring bases are programmed in macb_mac_enable(), like Linux mac_link_up. */
    macb_set_mac_addr(eth);

    if ((err = macb_mii_register(eth)))
    {
        goto _fail_blob;
    }

    phy_addr = macb_find_phy_addr(eth);
    if (phy_addr < 0)
    {
        LOG_E("No PHY found on MDIO");
        err = -RT_EINVAL;
        goto _fail_mii;
    }

#ifdef RT_USING_PHY_V2
    eth->phy = rt_phy_get_device(eth->mii, eth->dev->ofw_node, phy_addr,
            (rt_phy_interface)eth->phy_interface);
#else
    eth->phy = rt_phy_device_create(eth->mii, phy_addr, 0xffffffff, RT_FALSE);
#endif
    if (!eth->phy)
    {
        LOG_E("PHY not found on MDIO");
        err = -RT_ERROR;
        goto _fail_mii;
    }

    if ((err = rt_phy_config(eth->phy)) < 0)
    {
        LOG_E("PHY config failed: %s", rt_strerror(err));
        goto _fail_phy;
    }

    eth->phy_configured = RT_TRUE;

    if ((err = rt_phy_startup(eth->phy)))
    {
        LOG_E("PHY startup failed: %s", rt_strerror(err));
        goto _fail_phy;
    }

    if (!eth->phy->link)
    {
        return RT_EOK;
    }

    if ((err = macb_mac_enable(eth)))
    {
        LOG_W("MAC enable failed: %s", rt_strerror(err));
    }

    return RT_EOK;

_fail_phy:
    if (eth->phy)
    {
        rt_phy_shutdown(eth->phy);
        eth->phy = RT_NULL;
    }

_fail_mii:
    macb_mii_unregister(eth);

_fail_blob:
    if (eth->dummy_desc)
    {
        rt_dma_free(eth->dev, eth->dummy_desc_size, eth->dummy_desc,
                eth->dummy_desc_dma, RT_DMA_F_LINEAR);
        eth->dummy_desc = RT_NULL;
        eth->dummy_desc_size = 0;
    }
    if (eth->rx_ring)
    {
        rt_dma_free(eth->dev, eth->dma_blob_size, eth->rx_ring, eth->dma_blob_handle,
                RT_DMA_F_LINEAR);
        eth->rx_ring = RT_NULL;
        eth->dma_blob_size = 0;
    }

_fail_sem:
    rt_sem_detach(&eth->tx_sem);
    rt_mutex_detach(&eth->mdio_lock);
    return err;
}

void macb_eth_hw_stop(struct macb_eth *eth)
{
    if (!eth || !eth->regs)
    {
        return;
    }

    eth->mac_started = RT_FALSE;
    eth->hw_ready = RT_FALSE;
    macb_writel(eth, GEM_IDR, 0xffffffff);
    macb_ncr_write(eth, 0);
}

rt_err_t macb_eth_common_probe(struct macb_eth *eth)
{
    rt_err_t err;

#ifdef RT_USING_DEVICE_OPS
    eth->parent.parent.ops = &macb_eth_ops;
#else
    eth->parent.parent.control = macb_eth_control;
#endif
    eth->parent.eth_tx = macb_eth_tx;
    eth->parent.eth_rx = macb_eth_rx;

    if ((err = rt_dm_dev_set_name_auto(&eth->parent.parent, "e")) < 0)
    {
        return err;
    }

    if (eth->irq >= 0)
    {
        rt_hw_interrupt_install(eth->irq, macb_eth_isr, eth, "macb");
        rt_hw_interrupt_umask(eth->irq);
        eth->irq_installed = RT_TRUE;
    }

    if ((err = eth_device_init(&eth->parent, rt_dm_dev_get_name(&eth->parent.parent))))
    {
        return err;
    }

    eth->net_registered = RT_TRUE;

#ifdef RT_ETHERNET_CADENCE_PTP
    if ((err = macb_ptp_register(eth)))
    {
        LOG_W("PTP register failed: %s", rt_strerror(err));
    }
#endif

#ifdef RT_USING_SYSTEM_WORKQUEUE
    if (eth->phy && !eth->mac_started)
    {
        rt_work_init(&eth->phy_retry_work, macb_phy_retry_work, eth);
        rt_work_submit(&eth->phy_retry_work,
                rt_tick_from_millisecond(MACB_PHY_RETRY_INTERVAL_MS));
        eth_device_linkchange(&eth->parent, RT_FALSE);
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
    if (macb_start(eth) == RT_EOK && eth->phy && eth->phy->link)
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

rt_err_t macb_eth_common_remove(struct macb_eth *eth)
{
#ifdef RT_ETHERNET_CADENCE_PTP
    macb_ptp_unregister(eth);
#endif

#ifdef RT_USING_SYSTEM_WORKQUEUE
    rt_work_cancel(&eth->phy_retry_work);
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

    macb_eth_hw_stop(eth);

    if (eth->phy)
    {
        rt_phy_shutdown(eth->phy);
        eth->phy = RT_NULL;
    }

    macb_mii_unregister(eth);

    if (eth->dummy_desc)
    {
        rt_dma_free(eth->dev, eth->dummy_desc_size, eth->dummy_desc,
                eth->dummy_desc_dma, RT_DMA_F_LINEAR);
        eth->dummy_desc = RT_NULL;
        eth->dummy_desc_size = 0;
    }

    if (eth->rx_ring)
    {
        rt_dma_free(eth->dev, eth->dma_blob_size, eth->rx_ring, eth->dma_blob_handle,
                RT_DMA_F_LINEAR);
        eth->rx_ring = RT_NULL;
        eth->dma_blob_size = 0;
    }

    rt_sem_detach(&eth->tx_sem);
    rt_mutex_detach(&eth->mdio_lock);

    return RT_EOK;
}

static void macb_regs_iounmap(struct macb_eth *eth)
{
    if (eth->regs)
    {
        rt_iounmap(eth->regs);
    }
}

static rt_err_t macb_platform_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct macb_eth *eth = rt_calloc(1, sizeof(*eth));

    if (!eth)
    {
        return -RT_ENOMEM;
    }

    eth->dev = dev;
    eth->config = &macb_cfg_default_gem;
    if (pdev->id && pdev->id->data)
    {
        eth->config = (const struct macb_config *)pdev->id->data;
    }
    macb_parse_dt_props(eth);

    if (eth->config == &macb_cfg_emac)
    {
        LOG_W("AT91 EMAC (cdns,emac / cdns,at91rm9200-emac): driver uses GEM path; verify on hardware");
    }

    eth->irq = rt_dm_dev_get_irq(dev, 0);
    eth->regs = rt_dm_dev_iomap(dev, 0);

    if (!eth->regs)
    {
        rt_free(eth);
        return -RT_EIO;
    }

    macb_clocks_get(eth, dev);

#ifdef RT_USING_OFW
    if (rt_ofw_get_mac_addr(dev->ofw_node, eth->mac))
#endif
    {
        ethernet_random_addr(&eth->parent, eth->mac);
    }

    dev->user_data = eth;

    if ((err = macb_eth_hw_init(eth)))
    {
        LOG_E("hw init failed: %s", rt_strerror(err));
        goto _unmap;
    }

    eth->hw_ready = RT_TRUE;

    if ((err = macb_eth_common_probe(eth)))
    {
        macb_eth_common_remove(eth);
        goto _unmap;
    }

    return RT_EOK;

_unmap:
    dev->user_data = RT_NULL;
    macb_regs_iounmap(eth);
    rt_free(eth);
    return err;
}

static rt_err_t macb_platform_remove(struct rt_platform_device *pdev)
{
    struct macb_eth *eth = pdev->parent.user_data;

    macb_eth_common_remove(eth);
    macb_regs_iounmap(eth);
    rt_free(eth);

    return RT_EOK;
}

static const struct macb_config macb_cfg_default_gem =
{
    .caps = MACB_CAP_GIGABIT_MODE_AVAILABLE | MACB_CAP_JUMBO | MACB_CAP_GEM_HAS_PTP,
    .dma_burst_length = 16,
    .jumbo_max_len = 10240,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_at91sam9260 =
{
    .caps = MACB_CAP_USRIO_HAS_CLKEN | MACB_CAP_USRIO_DEFAULT_MII_GMII,
    .dma_burst_length = 0,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_pc302gem =
{
    .caps = MACB_CAP_SG_DISABLED | MACB_CAP_GIGABIT_MODE_AVAILABLE,
    .dma_burst_length = 16,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_sama5d2 =
{
    .caps = MACB_CAP_USRIO_DEFAULT_MII_GMII | MACB_CAP_JUMBO,
    .dma_burst_length = 16,
    .jumbo_max_len = 10240,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_sama5d29 =
{
    .caps = MACB_CAP_USRIO_DEFAULT_MII_GMII | MACB_CAP_GEM_HAS_PTP,
    .dma_burst_length = 16,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_sama5d3 =
{
    .caps = MACB_CAP_SG_DISABLED | MACB_CAP_GIGABIT_MODE_AVAILABLE |
            MACB_CAP_USRIO_DEFAULT_MII_GMII | MACB_CAP_JUMBO,
    .dma_burst_length = 16,
    .jumbo_max_len = 10240,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_sama5d3_macb =
{
    .caps = MACB_CAP_SG_DISABLED | MACB_CAP_USRIO_HAS_CLKEN | MACB_CAP_USRIO_DEFAULT_MII_GMII,
    .dma_burst_length = 0,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_sama5d4 =
{
    .caps = MACB_CAP_USRIO_DEFAULT_MII_GMII,
    .dma_burst_length = 4,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_emac =
{
    .caps = MACB_CAP_NEEDS_RSTONUBR | MACB_CAP_MACB_IS_EMAC,
    .dma_burst_length = 0,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_np4 =
{
    .caps = MACB_CAP_USRIO_DISABLED,
    .dma_burst_length = 0,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_zynqmp =
{
    .caps = MACB_CAP_GIGABIT_MODE_AVAILABLE | MACB_CAP_JUMBO | MACB_CAP_GEM_HAS_PTP |
            MACB_CAP_BD_RD_PREFETCH,
    .dma_burst_length = 16,
    .jumbo_max_len = 10240,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_zynq =
{
    .caps = MACB_CAP_GIGABIT_MODE_AVAILABLE | MACB_CAP_NO_GIGABIT_HALF | MACB_CAP_NEEDS_RSTONUBR,
    .dma_burst_length = 16,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_mpfs =
{
    .caps = MACB_CAP_GIGABIT_MODE_AVAILABLE | MACB_CAP_JUMBO | MACB_CAP_GEM_HAS_PTP,
    .dma_burst_length = 16,
    .jumbo_max_len = 4040,
    .max_tx_len = 4040,
};

static const struct macb_config macb_cfg_sama7g5_gem =
{
    .caps = MACB_CAP_GIGABIT_MODE_AVAILABLE | MACB_CAP_CLK_HW_CHG |
            MACB_CAP_USRIO_DEFAULT_MII_GMII | MACB_CAP_MIIONRGMII | MACB_CAP_GEM_HAS_PTP,
    .dma_burst_length = 16,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_sama7g5_emac =
{
    .caps = MACB_CAP_USRIO_DEFAULT_MII_GMII | MACB_CAP_USRIO_HAS_CLKEN | MACB_CAP_MIIONRGMII |
            MACB_CAP_GEM_HAS_PTP,
    .dma_burst_length = 16,
    .jumbo_max_len = 0,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_versal =
{
    .caps = MACB_CAP_GIGABIT_MODE_AVAILABLE | MACB_CAP_JUMBO | MACB_CAP_GEM_HAS_PTP |
            MACB_CAP_BD_RD_PREFETCH | MACB_CAP_NEED_TSUCLK | MACB_CAP_QUEUE_DISABLE |
            MACB_CAP_QBV,
    .dma_burst_length = 16,
    .jumbo_max_len = 10240,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_eyeq5 =
{
    .caps = MACB_CAP_GIGABIT_MODE_AVAILABLE | MACB_CAP_JUMBO | MACB_CAP_GEM_HAS_PTP |
            MACB_CAP_QUEUE_DISABLE | MACB_CAP_NO_LSO,
    .dma_burst_length = 16,
    .jumbo_max_len = 10240,
    .max_tx_len = 0,
};

static const struct macb_config macb_cfg_fu540 =
{
    .caps = MACB_CAP_GIGABIT_MODE_AVAILABLE | MACB_CAP_JUMBO | MACB_CAP_GEM_HAS_PTP,
    .dma_burst_length = 16,
    .jumbo_max_len = 10240,
    .max_tx_len = 0,
};

static const struct rt_ofw_node_id macb_eth_ofw_ids[] =
{
    { .compatible = "cdns,at91sam9260-macb", .data = &macb_cfg_at91sam9260 },
    { .compatible = "cdns,macb", .data = &macb_cfg_default_gem },
    { .compatible = "cdns,np4-macb", .data = &macb_cfg_np4 },
    { .compatible = "cdns,pc302-gem", .data = &macb_cfg_pc302gem },
    { .compatible = "cdns,gem", .data = &macb_cfg_pc302gem },
    { .compatible = "cdns,sam9x60-macb", .data = &macb_cfg_at91sam9260 },
    { .compatible = "atmel,sama5d2-gem", .data = &macb_cfg_sama5d2 },
    { .compatible = "atmel,sama5d29-gem", .data = &macb_cfg_sama5d29 },
    { .compatible = "atmel,sama5d3-gem", .data = &macb_cfg_sama5d3 },
    { .compatible = "atmel,sama5d3-macb", .data = &macb_cfg_sama5d3_macb },
    { .compatible = "atmel,sama5d4-gem", .data = &macb_cfg_sama5d4 },
    { .compatible = "cdns,at91rm9200-emac", .data = &macb_cfg_emac },
    { .compatible = "cdns,emac", .data = &macb_cfg_emac },
    { .compatible = "cdns,zynqmp-gem", .data = &macb_cfg_zynqmp },
    { .compatible = "cdns,zynq-gem", .data = &macb_cfg_zynq },
    { .compatible = "sifive,fu540-c000-gem", .data = &macb_cfg_fu540 },
    { .compatible = "microchip,mpfs-macb", .data = &macb_cfg_mpfs },
    { .compatible = "microchip,sama7g5-gem", .data = &macb_cfg_sama7g5_gem },
    { .compatible = "microchip,sama7g5-emac", .data = &macb_cfg_sama7g5_emac },
    { .compatible = "mobileye,eyeq5-gem", .data = &macb_cfg_eyeq5 },
    { .compatible = "xlnx,zynqmp-gem", .data = &macb_cfg_zynqmp },
    { .compatible = "xlnx,zynq-gem", .data = &macb_cfg_zynq },
    { .compatible = "xlnx,versal-gem", .data = &macb_cfg_versal },
    { /* sentinel */ }
};

static struct rt_platform_driver macb_eth_driver =
{
    .name = "eth-macb",
    .ids = macb_eth_ofw_ids,

    .probe = macb_platform_probe,
    .remove = macb_platform_remove,
};
RT_PLATFORM_DRIVER_EXPORT(macb_eth_driver);
