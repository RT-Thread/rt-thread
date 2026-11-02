/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-25     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <drivers/byteorder.h>

#define DBG_TAG "dma.axi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define DMAC_MAX_CHANNELS 32
#define DMAC_MAX_MASTERS  2
#define DMAC_MAX_BLK_SIZE 0x200000
#define DMAC_MAX_LLIS     64
#define LLI_ALIGN         64

#define COMMON_REG_LEN     0x100
#define CHAN_REG_LEN       0x100
#define DMA_REG_MAP_CH_REF 8

#define DMAC_CFG       0x010
#define DMAC_CHEN      0x018
#define DMAC_INTSTATUS 0x030
#define DMAC_RESET     0x058

#define CH_SAR           0x000
#define CH_DAR           0x008
#define CH_BLOCK_TS      0x010
#define CH_CTL           0x018
#define CH_CTL_L         0x018
#define CH_CTL_H         0x01C
#define CH_CFG           0x020
#define CH_CFG_L         0x020
#define CH_CFG_H         0x024
#define CH_LLP           0x028
#define CH_INTSTATUS_ENA 0x080
#define CH_INTSTATUS     0x088
#define CH_INTSIGNAL_ENA 0x090
#define CH_INTCLEAR      0x098

#define DMAC_EN_MASK RT_BIT(0)
#define INT_EN_MASK  RT_BIT(1)

#define DMAC_CHAN_EN_SHIFT     0
#define DMAC_CHAN_EN_WE_SHIFT  8
#define DMAC_CHAN_EN2_WE_SHIFT 16

#define CH_CTL_H_ARLEN_EN  RT_BIT(6)
#define CH_CTL_H_ARLEN_POS 7
#define CH_CTL_H_AWLEN_EN  RT_BIT(15)
#define CH_CTL_H_AWLEN_POS 16
#define CH_CTL_H_LLI_LAST  RT_BIT(30)
#define CH_CTL_H_LLI_VALID RT_BIT(31)

#define CH_CTL_L_DST_MSIZE_POS 18
#define CH_CTL_L_SRC_MSIZE_POS 14
#define CH_CTL_L_DST_WIDTH_POS 11
#define CH_CTL_L_SRC_WIDTH_POS 8
#define CH_CTL_L_DST_INC_POS   6
#define CH_CTL_L_SRC_INC_POS   4
#define CH_CTL_L_DST_MAST      RT_BIT(2)
#define CH_CTL_L_SRC_MAST      RT_BIT(0)

#define CH_CFG_H_PRIORITY_POS   17
#define CH_CFG_H_DST_PER_POS    12
#define CH_CFG_H_SRC_PER_POS    7
#define CH_CFG_H_HS_SEL_DST_POS 4
#define CH_CFG_H_HS_SEL_SRC_POS 3
#define CH_CFG_H_TT_FC_POS      0

#define CH_CFG2_L_SRC_PER_POS    4
#define CH_CFG2_L_DST_PER_POS    11
#define CH_CFG2_H_TT_FC_POS      0
#define CH_CFG2_H_HS_SEL_SRC_POS 3
#define CH_CFG2_H_HS_SEL_DST_POS 4
#define CH_CFG2_H_PRIORITY_POS   20

#define CH_CFG_L_DST_MULTBLK_TYPE_POS 2
#define CH_CFG_L_SRC_MULTBLK_TYPE_POS 0

#define DWAXIDMAC_ARWLEN_MIN 0
#define DWAXIDMAC_ARWLEN_MAX 255

#define DWAXIDMAC_BURST_TRANS_LEN_1  0
#define DWAXIDMAC_BURST_TRANS_LEN_4  1
#define DWAXIDMAC_BURST_TRANS_LEN_8  2
#define DWAXIDMAC_BURST_TRANS_LEN_16 3

#define DWAXIDMAC_CH_CTL_L_INC   0
#define DWAXIDMAC_CH_CTL_L_NOINC 1

#define DWAXIDMAC_HS_SEL_HW 0
#define DWAXIDMAC_HS_SEL_SW 1

#define DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC 0
#define DWAXIDMAC_TT_FC_MEM_TO_PER_DMAC 1
#define DWAXIDMAC_TT_FC_PER_TO_MEM_DMAC 2
#define DWAXIDMAC_TT_FC_MEM_TO_PER_DST  5
#define DWAXIDMAC_TT_FC_PER_TO_MEM_SRC  4

#define DWAXIDMAC_MBLK_TYPE_LL 3

#define DWAXIDMAC_IRQ_DMA_TRF RT_BIT(1)
#define DWAXIDMAC_IRQ_ALL_ERR (RT_GENMASK(21, 16) | RT_GENMASK(14, 5))
#define DWAXIDMAC_IRQ_ALL     RT_GENMASK(31, 0)
#define DWAXIDMAC_IRQ_NONE    0

#define DWAXIDMAC_TRANS_WIDTH_MAX 7

rt_packed(struct axi_dma_lli {
    rt_uint64_t sar;
    rt_uint64_t dar;
    rt_uint32_t block_ts_lo;
    rt_uint32_t block_ts_hi;
    rt_uint64_t llp;
    rt_uint32_t ctl_lo;
    rt_uint32_t ctl_hi;
    rt_uint32_t sstat;
    rt_uint32_t dstat;
    rt_uint32_t status_lo;
    rt_uint32_t status_hi;
    rt_uint32_t reserved_lo;
    rt_uint32_t reserved_hi;
});

struct dw_axi_dma_hcfg
{
    rt_uint32_t nr_channels;
    rt_uint32_t nr_masters;
    rt_uint32_t m_data_width;
    rt_uint32_t block_size[DMAC_MAX_CHANNELS];
    rt_uint32_t priority[DMAC_MAX_CHANNELS];
    rt_uint32_t axi_rw_burst_len[DMAC_MAX_CHANNELS];
    rt_bool_t reg_map_8_channels;
    rt_bool_t restrict_axi_burst_len;
    rt_bool_t use_cfg2;
};

struct axi_dma_chan;

struct axi_dma_chip
{
    struct rt_dma_controller parent;
    struct dw_axi_dma_hcfg hdata;

    struct rt_clk *core_clk;
    struct rt_clk *cfgr_clk;

    void *regs;
    int irq;

    struct axi_dma_chan *chans;
};

struct axi_dma_chan
{
    struct rt_dma_chan parent;

    struct axi_dma_chip *chip;
    void *chan_regs;
    rt_uint8_t id;
    rt_uint8_t hw_handshake;
    rt_bool_t enabled;
    rt_bool_t cyclic;

    enum rt_dma_transfer_direction direction;
    rt_size_t transfer_size;
    rt_size_t period_len;
    rt_uint32_t cyclic_pos;

    struct axi_dma_lli *lli;
    void *lli_raw;
    rt_ubase_t lli_dma;
    rt_ubase_t lli_bus;
    rt_uint32_t nr_llis;
    rt_size_t lli_bytes;
};

#define raw_to_axi_dma_chip(raw) rt_container_of(raw, struct axi_dma_chip, parent)
#define raw_to_axi_dma_chan(raw) rt_container_of(raw, struct axi_dma_chan, parent)

rt_inline void axi_dma_writel(struct axi_dma_chip *chip, rt_uint32_t reg, rt_uint32_t val)
{
    HWREG32(chip->regs + reg) = val;
}

rt_inline rt_uint32_t axi_dma_readl(struct axi_dma_chip *chip, rt_uint32_t reg)
{
    return HWREG32(chip->regs + reg);
}

rt_inline void axi_chan_writel(struct axi_dma_chan *chan, rt_uint32_t reg, rt_uint32_t val)
{
    HWREG32(chan->chan_regs + reg) = val;
}

rt_inline rt_uint32_t axi_chan_readl(struct axi_dma_chan *chan, rt_uint32_t reg)
{
    return HWREG32(chan->chan_regs + reg);
}

rt_inline void axi_chan_writeq(struct axi_dma_chan *chan, rt_uint32_t reg, rt_uint64_t val)
{
    axi_chan_writel(chan, reg, rt_lower_32_bits(val));
    axi_chan_writel(chan, reg + 4, rt_upper_32_bits(val));
}

rt_inline void axi_dma_disable(struct axi_dma_chip *chip)
{
    rt_uint32_t val = axi_dma_readl(chip, DMAC_CFG);

    val &= ~DMAC_EN_MASK;
    axi_dma_writel(chip, DMAC_CFG, val);
}

rt_inline void axi_dma_enable(struct axi_dma_chip *chip)
{
    rt_uint32_t val = axi_dma_readl(chip, DMAC_CFG);

    val |= DMAC_EN_MASK;
    axi_dma_writel(chip, DMAC_CFG, val);
}

rt_inline void axi_dma_irq_disable(struct axi_dma_chip *chip)
{
    rt_uint32_t val = axi_dma_readl(chip, DMAC_CFG);

    val &= ~INT_EN_MASK;
    axi_dma_writel(chip, DMAC_CFG, val);
}

rt_inline void axi_dma_irq_enable(struct axi_dma_chip *chip)
{
    rt_uint32_t val = axi_dma_readl(chip, DMAC_CFG);

    val |= INT_EN_MASK;
    axi_dma_writel(chip, DMAC_CFG, val);
}

rt_inline void axi_chan_irq_disable(struct axi_dma_chan *chan)
{
    axi_chan_writel(chan, CH_INTSTATUS_ENA, DWAXIDMAC_IRQ_NONE);
}

rt_inline void axi_chan_irq_set(struct axi_dma_chan *chan, rt_uint32_t irq_mask)
{
    axi_chan_writel(chan, CH_INTSTATUS_ENA, irq_mask);
}

rt_inline void axi_chan_irq_sig_set(struct axi_dma_chan *chan, rt_uint32_t irq_mask)
{
    axi_chan_writel(chan, CH_INTSIGNAL_ENA, irq_mask);
}

rt_inline void axi_chan_irq_clear(struct axi_dma_chan *chan, rt_uint32_t irq_mask)
{
    axi_chan_writel(chan, CH_INTCLEAR, irq_mask);
}

rt_inline rt_uint32_t axi_chan_irq_read(struct axi_dma_chan *chan)
{
    return axi_chan_readl(chan, CH_INTSTATUS);
}

rt_inline void axi_chan_disable(struct axi_dma_chan *chan)
{
    rt_uint32_t val = axi_dma_readl(chan->chip, DMAC_CHEN);

    val &= ~(RT_BIT(chan->id) << DMAC_CHAN_EN_SHIFT);
    if (chan->chip->hdata.reg_map_8_channels)
    {
        val |= RT_BIT(chan->id) << DMAC_CHAN_EN_WE_SHIFT;
    }
    else
    {
        val |= RT_BIT(chan->id) << DMAC_CHAN_EN2_WE_SHIFT;
    }
    axi_dma_writel(chan->chip, DMAC_CHEN, val);
}

rt_inline void axi_chan_enable(struct axi_dma_chan *chan)
{
    rt_uint32_t val = axi_dma_readl(chan->chip, DMAC_CHEN);

    if (chan->chip->hdata.reg_map_8_channels)
    {
        val |= RT_BIT(chan->id) << DMAC_CHAN_EN_SHIFT |
               RT_BIT(chan->id) << DMAC_CHAN_EN_WE_SHIFT;
    }
    else
    {
        val |= RT_BIT(chan->id) << DMAC_CHAN_EN_SHIFT |
               RT_BIT(chan->id) << DMAC_CHAN_EN2_WE_SHIFT;
    }
    axi_dma_writel(chan->chip, DMAC_CHEN, val);
}

rt_inline rt_bool_t axi_chan_is_hw_enable(struct axi_dma_chan *chan)
{
    rt_uint32_t val = axi_dma_readl(chan->chip, DMAC_CHEN);

    return !!(val & (RT_BIT(chan->id) << DMAC_CHAN_EN_SHIFT));
}

static rt_uint32_t axi_dma_encode_msize(rt_uint32_t max_burst)
{
    if (max_burst <= 1)
    {
        return DWAXIDMAC_BURST_TRANS_LEN_1;
    }
    if (max_burst > 1024)
    {
        return 10;
    }

    return __rt_fls(max_burst) - 2;
}

static rt_uint32_t axi_chan_get_xfer_width(struct axi_dma_chan *chan,
                                           rt_ubase_t src, rt_ubase_t dst, rt_size_t len)
{
    rt_uint32_t max_width = chan->chip->hdata.m_data_width;

    return __rt_ffs(src | dst | len | RT_BIT(max_width)) - 1;
}

static void axi_dma_hw_init(struct axi_dma_chip *chip)
{
    rt_uint32_t retries = 1000;

    axi_dma_writel(chip, DMAC_RESET, 1);
    while (axi_dma_readl(chip, DMAC_RESET))
    {
        if (!--retries)
        {
            LOG_E("DMAC reset timeout");
            return;
        }
        rt_hw_cpu_relax();
    }

    for (rt_uint32_t i = 0; i < chip->hdata.nr_channels; ++i)
    {
        axi_chan_irq_disable(&chip->chans[i]);
        axi_chan_disable(&chip->chans[i]);
    }

    /* DMAC reset clears the global DMA and interrupt enable bits. */
    axi_dma_enable(chip);
    axi_dma_irq_enable(chip);
}

static rt_err_t axi_dma_resume(struct axi_dma_chip *chip)
{
    rt_err_t err;

    if ((err = rt_clk_prepare_enable(chip->cfgr_clk)))
    {
        return err;
    }

    if ((err = rt_clk_prepare_enable(chip->core_clk)))
    {
        rt_clk_disable_unprepare(chip->cfgr_clk);
        return err;
    }

    axi_dma_enable(chip);
    axi_dma_irq_enable(chip);

    return RT_EOK;
}

static void axi_dma_suspend(struct axi_dma_chip *chip)
{
    axi_dma_irq_disable(chip);
    axi_dma_disable(chip);
    rt_clk_disable_unprepare(chip->core_clk);
    rt_clk_disable_unprepare(chip->cfgr_clk);
}

static void axi_dma_free_llis(struct axi_dma_chan *chan)
{
    struct rt_device *dev = chan->chip->parent.dev;

    if (chan->lli_raw)
    {
        rt_dma_free_coherent(dev, chan->lli_bytes, chan->lli_raw, chan->lli_bus);
        chan->lli_raw = RT_NULL;
        chan->lli = RT_NULL;
        chan->lli_dma = 0;
        chan->lli_bus = 0;
        chan->nr_llis = 0;
        chan->lli_bytes = 0;
    }
}

static struct axi_dma_lli *axi_dma_alloc_llis(struct axi_dma_chan *chan, rt_uint32_t count)
{
    struct rt_device *dev = chan->chip->parent.dev;
    rt_size_t size = RT_ALIGN(count * sizeof(struct axi_dma_lli), LLI_ALIGN);
    rt_ubase_t dma;
    void *cpu;
    rt_ubase_t aligned_dma;
    struct axi_dma_lli *lli;

    axi_dma_free_llis(chan);

    cpu = rt_dma_alloc_coherent(dev, size + LLI_ALIGN, &dma);
    if (!cpu)
    {
        return RT_NULL;
    }

    aligned_dma = RT_ALIGN(dma, LLI_ALIGN);
    lli = (struct axi_dma_lli *)((rt_uint8_t *)cpu + (aligned_dma - dma));

    chan->lli_raw = cpu;
    chan->lli = lli;
    chan->lli_bus = dma;
    chan->lli_dma = aligned_dma;
    chan->nr_llis = count;
    chan->lli_bytes = size + LLI_ALIGN;

    rt_memset(lli, 0, count * sizeof(*lli));

    return lli;
}

static void axi_chan_config_write(struct axi_dma_chan *chan, rt_uint8_t tt_fc,
                                  rt_uint8_t src_per, rt_uint8_t dst_per)
{
    rt_uint32_t cfg_lo, cfg_hi;
    struct dw_axi_dma_hcfg *hdata = &chan->chip->hdata;

    cfg_lo = (DWAXIDMAC_MBLK_TYPE_LL << CH_CFG_L_DST_MULTBLK_TYPE_POS |
              DWAXIDMAC_MBLK_TYPE_LL << CH_CFG_L_SRC_MULTBLK_TYPE_POS);

    if (hdata->reg_map_8_channels && !hdata->use_cfg2)
    {
        cfg_hi = tt_fc << CH_CFG_H_TT_FC_POS |
                 DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_SRC_POS |
                 DWAXIDMAC_HS_SEL_HW << CH_CFG_H_HS_SEL_DST_POS |
                 src_per << CH_CFG_H_SRC_PER_POS |
                 dst_per << CH_CFG_H_DST_PER_POS |
                 hdata->priority[chan->id] << CH_CFG_H_PRIORITY_POS;
    }
    else
    {
        cfg_lo |= src_per << CH_CFG2_L_SRC_PER_POS |
                  dst_per << CH_CFG2_L_DST_PER_POS;
        cfg_hi = tt_fc << CH_CFG2_H_TT_FC_POS |
                 DWAXIDMAC_HS_SEL_HW << CH_CFG2_H_HS_SEL_SRC_POS |
                 DWAXIDMAC_HS_SEL_HW << CH_CFG2_H_HS_SEL_DST_POS |
                 hdata->priority[chan->id] << CH_CFG2_H_PRIORITY_POS;
    }

    axi_chan_writel(chan, CH_CFG_L, cfg_lo);
    axi_chan_writel(chan, CH_CFG_H, cfg_hi);
}

static void axi_dma_fill_lli_ctl(struct axi_dma_chan *chan, struct axi_dma_lli *lli,
                                 rt_uint32_t ctl_lo, rt_uint32_t block_ts, rt_bool_t last)
{
    rt_uint32_t ctl_hi = CH_CTL_H_LLI_VALID;

    if (chan->chip->hdata.restrict_axi_burst_len)
    {
        rt_uint32_t burst_len = chan->chip->hdata.axi_rw_burst_len[chan->id];

        ctl_hi |= CH_CTL_H_ARLEN_EN | CH_CTL_H_AWLEN_EN |
                  burst_len << CH_CTL_H_ARLEN_POS |
                  burst_len << CH_CTL_H_AWLEN_POS;
    }

    if (last)
    {
        ctl_hi |= CH_CTL_H_LLI_LAST;
    }

    lli->block_ts_lo = rt_cpu_to_le32(block_ts - 1);
    lli->ctl_lo = rt_cpu_to_le32(ctl_lo);
    lli->ctl_hi = rt_cpu_to_le32(ctl_hi);
}

static rt_uint32_t axi_dma_calc_memcpy_llis(struct axi_dma_chan *chan,
                                            rt_ubase_t src, rt_ubase_t dst, rt_size_t len)
{
    rt_size_t max_block_ts = chan->chip->hdata.block_size[chan->id];
    rt_uint32_t nr_llis = 0;
    rt_size_t remain = len;

    while (remain)
    {
        rt_uint32_t width = axi_chan_get_xfer_width(chan, src, dst, remain);
        rt_size_t xfer_len = remain;
        rt_uint32_t block_ts = xfer_len >> width;

        if (block_ts > max_block_ts)
        {
            block_ts = max_block_ts;
            xfer_len = max_block_ts << width;
        }

        nr_llis++;
        if (nr_llis > DMAC_MAX_LLIS)
        {
            return 0;
        }

        src += xfer_len;
        dst += xfer_len;
        remain -= xfer_len;
    }

    return nr_llis;
}

static rt_err_t axi_dma_build_memcpy_llis(struct axi_dma_chan *chan,
                                          rt_ubase_t src, rt_ubase_t dst, rt_size_t len)
{
    rt_size_t max_block_ts = chan->chip->hdata.block_size[chan->id];
    rt_uint32_t nr_llis;
    rt_size_t remain = len;
    struct axi_dma_lli *lli;

    nr_llis = axi_dma_calc_memcpy_llis(chan, src, dst, len);
    if (!nr_llis)
    {
        return -RT_EINVAL;
    }

    lli = axi_dma_alloc_llis(chan, nr_llis);
    if (!lli)
    {
        return -RT_ENOMEM;
    }

    remain = len;
    for (rt_uint32_t i = 0; i < nr_llis; ++i)
    {
        rt_uint32_t width = axi_chan_get_xfer_width(chan, src, dst, remain);
        rt_size_t xfer_len = remain;
        rt_uint32_t block_ts = xfer_len >> width;

        if (block_ts > max_block_ts)
        {
            block_ts = max_block_ts;
            xfer_len = max_block_ts << width;
        }

        lli[i].sar = rt_cpu_to_le64(src);
        lli[i].dar = rt_cpu_to_le64(dst);

        axi_dma_fill_lli_ctl(chan, &lli[i],
                             (DWAXIDMAC_BURST_TRANS_LEN_4 << CH_CTL_L_DST_MSIZE_POS |
                              DWAXIDMAC_BURST_TRANS_LEN_4 << CH_CTL_L_SRC_MSIZE_POS |
                              width << CH_CTL_L_DST_WIDTH_POS |
                              width << CH_CTL_L_SRC_WIDTH_POS |
                              DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_DST_INC_POS |
                              DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_SRC_INC_POS),
                             block_ts, i == nr_llis - 1);

        if (i < nr_llis - 1)
        {
            rt_ubase_t next = chan->lli_dma + (i + 1) * sizeof(struct axi_dma_lli);

            lli[i].llp = rt_cpu_to_le64(next);
        }

        src += xfer_len;
        dst += xfer_len;
        remain -= xfer_len;
    }

    chan->direction = RT_DMA_MEM_TO_MEM;
    chan->transfer_size = len;
    chan->cyclic = RT_FALSE;

    return RT_EOK;
}

static rt_err_t axi_dma_build_slave_llis(struct axi_dma_chan *chan,
                                         rt_ubase_t mem_addr, rt_size_t len, enum rt_dma_transfer_direction dir,
                                         rt_bool_t cyclic, rt_size_t period_len)
{
    rt_uint32_t data_width = RT_BIT(chan->chip->hdata.m_data_width);
    rt_uint32_t mem_width, reg_width, block_ts;
    rt_size_t axi_block_ts = chan->chip->hdata.block_size[chan->id];
    rt_uint32_t ctl_lo;
    rt_ubase_t dev_addr;
    struct axi_dma_lli *lli;

    if (dir == RT_DMA_MEM_TO_DEV)
    {
        reg_width = __rt_ffs(chan->parent.conf.dst_addr_width) - 1;
        mem_width = __rt_ffs(data_width | mem_addr | len) - 1;
        dev_addr = chan->parent.conf.dst_addr;
        ctl_lo = reg_width << CH_CTL_L_DST_WIDTH_POS |
                 mem_width << CH_CTL_L_SRC_WIDTH_POS |
                 axi_dma_encode_msize(chan->parent.conf.dst_maxburst) << CH_CTL_L_DST_MSIZE_POS |
                 axi_dma_encode_msize(16) << CH_CTL_L_SRC_MSIZE_POS |
                 DWAXIDMAC_CH_CTL_L_NOINC << CH_CTL_L_DST_INC_POS |
                 DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_SRC_INC_POS;
        block_ts = len >> mem_width;
    }
    else if (dir == RT_DMA_DEV_TO_MEM)
    {
        reg_width = __rt_ffs(chan->parent.conf.src_addr_width) - 1;
        mem_width = __rt_ffs(data_width | mem_addr | len) - 1;
        if (chan->parent.conf.dst_addr_width &&
            chan->parent.conf.dst_addr_width < (1U << mem_width))
        {
            mem_width = __rt_ffs(chan->parent.conf.dst_addr_width) - 1;
        }
        dev_addr = chan->parent.conf.src_addr;
        ctl_lo = reg_width << CH_CTL_L_SRC_WIDTH_POS |
                 mem_width << CH_CTL_L_DST_WIDTH_POS |
                 axi_dma_encode_msize(16) << CH_CTL_L_DST_MSIZE_POS |
                 axi_dma_encode_msize(chan->parent.conf.src_maxburst) << CH_CTL_L_SRC_MSIZE_POS |
                 DWAXIDMAC_CH_CTL_L_INC << CH_CTL_L_DST_INC_POS |
                 DWAXIDMAC_CH_CTL_L_NOINC << CH_CTL_L_SRC_INC_POS;
        block_ts = len >> reg_width;
    }
    else
    {
        return -RT_EINVAL;
    }

    if (len % (1U << reg_width))
    {
        return -RT_EINVAL;
    }

    if (block_ts > axi_block_ts)
    {
        return -RT_EINVAL;
    }

    lli = axi_dma_alloc_llis(chan, 1);
    if (!lli)
    {
        return -RT_ENOMEM;
    }

    if (dir == RT_DMA_MEM_TO_DEV)
    {
        lli->sar = rt_cpu_to_le64(mem_addr);
        lli->dar = rt_cpu_to_le64(dev_addr);
    }
    else
    {
        lli->sar = rt_cpu_to_le64(dev_addr);
        lli->dar = rt_cpu_to_le64(mem_addr);
    }

    axi_dma_fill_lli_ctl(chan, lli, ctl_lo, block_ts, RT_TRUE);

    if (cyclic)
    {
        lli->llp = rt_cpu_to_le64(chan->lli_dma);
    }

    chan->direction = dir;
    chan->transfer_size = len;
    chan->period_len = period_len;
    chan->cyclic = cyclic;
    chan->cyclic_pos = 0;

    return RT_EOK;
}

static rt_err_t axi_dma_chan_start_locked(struct axi_dma_chan *chan)
{
    rt_uint8_t tt_fc = DWAXIDMAC_TT_FC_MEM_TO_MEM_DMAC;
    rt_uint8_t src_per = 0, dst_per = 0;
    rt_uint32_t irq_mask;

    if (axi_chan_is_hw_enable(chan))
    {
        return -RT_EBUSY;
    }

    switch (chan->direction)
    {
    case RT_DMA_MEM_TO_DEV:
        tt_fc = DWAXIDMAC_TT_FC_MEM_TO_PER_DMAC;
        dst_per = chan->hw_handshake;
        break;
    case RT_DMA_DEV_TO_MEM:
        tt_fc = DWAXIDMAC_TT_FC_PER_TO_MEM_DMAC;
        src_per = chan->hw_handshake;
        break;
    default:
        break;
    }

    axi_chan_config_write(chan, tt_fc, src_per, dst_per);
    axi_chan_writeq(chan, CH_LLP, chan->lli_dma);

    irq_mask = DWAXIDMAC_IRQ_DMA_TRF | DWAXIDMAC_IRQ_ALL_ERR;
    axi_chan_irq_sig_set(chan, irq_mask);
    axi_chan_irq_set(chan, irq_mask | RT_BIT(29));

    axi_chan_enable(chan);

    return RT_EOK;
}

static struct rt_dma_chan *axi_dma_request_chan(struct rt_dma_controller *ctrl,
                                                struct rt_device *slave, void *fw_data)
{
    struct axi_dma_chip *chip = raw_to_axi_dma_chip(ctrl);
    struct rt_ofw_cell_args *args = fw_data;
    struct axi_dma_chan *chan = RT_NULL;

    for (rt_uint32_t i = 0; i < chip->hdata.nr_channels; ++i)
    {
        if (!chip->chans[i].enabled)
        {
            chan = &chip->chans[i];
            break;
        }
    }

    if (!chan)
    {
        return rt_err_ptr(-RT_EBUSY);
    }

    chan->hw_handshake = args ? (rt_uint8_t)args->args[0] : 0;
    chan->enabled = RT_TRUE;
    chan->parent.slave = slave;
    chan->cyclic = RT_FALSE;
    chan->cyclic_pos = 0;

    return &chan->parent;
}

static rt_err_t axi_dma_stop(struct rt_dma_chan *chan)
{
    struct axi_dma_chan *axi_chan = raw_to_axi_dma_chan(chan);
    rt_uint32_t timeout = 1000;
    rt_uint32_t active = RT_BIT(axi_chan->id) << DMAC_CHAN_EN_SHIFT;

    axi_chan_disable(axi_chan);

    while ((axi_dma_readl(axi_chan->chip, DMAC_CHEN) & active) && --timeout)
    {
        rt_hw_cpu_relax();
    }

    axi_chan_irq_clear(axi_chan, DWAXIDMAC_IRQ_ALL);
    axi_chan->cyclic = RT_FALSE;

    return RT_EOK;
}

static rt_err_t axi_dma_release_chan(struct rt_dma_chan *chan)
{
    struct axi_dma_chan *axi_chan = raw_to_axi_dma_chan(chan);

    axi_dma_stop(chan);
    axi_dma_free_llis(axi_chan);
    axi_chan->enabled = RT_FALSE;

    return RT_EOK;
}

static rt_err_t axi_dma_start(struct rt_dma_chan *chan)
{
    struct axi_dma_chan *axi_chan = raw_to_axi_dma_chan(chan);

    if (!axi_chan->lli)
    {
        return -RT_EINVAL;
    }

    return axi_dma_chan_start_locked(axi_chan);
}

static rt_err_t axi_dma_config(struct rt_dma_chan *chan, struct rt_dma_slave_config *conf)
{
    rt_memcpy(&chan->conf, conf, sizeof(*conf));

    return RT_EOK;
}

static rt_err_t axi_dma_prep_memcpy(struct rt_dma_chan *chan,
                                    rt_ubase_t dma_addr_src, rt_ubase_t dma_addr_dst, rt_size_t len)
{
    struct axi_dma_chan *axi_chan = raw_to_axi_dma_chan(chan);

    return axi_dma_build_memcpy_llis(axi_chan, dma_addr_src, dma_addr_dst, len);
}

static rt_err_t axi_dma_prep_cyclic(struct rt_dma_chan *chan,
                                    rt_ubase_t dma_buf_addr, rt_size_t buf_len, rt_size_t period_len,
                                    enum rt_dma_transfer_direction dir)
{
    struct axi_dma_chan *axi_chan = raw_to_axi_dma_chan(chan);

    if (!period_len || buf_len % period_len)
    {
        return -RT_EINVAL;
    }

    return axi_dma_build_slave_llis(axi_chan, dma_buf_addr, period_len, dir, RT_TRUE, period_len);
}

static rt_err_t axi_dma_prep_single(struct rt_dma_chan *chan,
                                    rt_ubase_t dma_buf_addr, rt_size_t buf_len,
                                    enum rt_dma_transfer_direction dir)
{
    struct axi_dma_chan *axi_chan = raw_to_axi_dma_chan(chan);

    return axi_dma_build_slave_llis(axi_chan, dma_buf_addr, buf_len, dir, RT_FALSE, 0);
}

static const struct rt_dma_controller_ops axi_dma_ops = {
    .request_chan = axi_dma_request_chan,
    .release_chan = axi_dma_release_chan,
    .start = axi_dma_start,
    .stop = axi_dma_stop,
    .config = axi_dma_config,
    .prep_memcpy = axi_dma_prep_memcpy,
    .prep_cyclic = axi_dma_prep_cyclic,
    .prep_single = axi_dma_prep_single,
};

static void axi_dma_handle_complete(struct axi_dma_chan *chan)
{
    if (chan->cyclic)
    {
        chan->cyclic_pos += chan->period_len;
        if (chan->cyclic_pos >= chan->transfer_size)
        {
            chan->cyclic_pos = 0;
        }

        axi_chan_irq_clear(chan, DWAXIDMAC_IRQ_DMA_TRF);
        if (chan->lli)
        {
            chan->lli->ctl_hi = rt_cpu_to_le32(rt_le32_to_cpu(chan->lli->ctl_hi) | CH_CTL_H_LLI_VALID);
        }
        axi_chan_enable(chan);
        rt_dma_chan_done(&chan->parent, chan->period_len);
    }
    else
    {
        axi_chan_disable(chan);
        rt_dma_chan_done(&chan->parent, chan->transfer_size);
    }
}

static void axi_dma_isr(int irq, void *param)
{
    struct axi_dma_chip *chip = param;
    rt_uint32_t status;

    axi_dma_irq_disable(chip);

    for (rt_uint32_t i = 0; i < chip->hdata.nr_channels; ++i)
    {
        struct axi_dma_chan *chan = &chip->chans[i];

        if (!chan->enabled)
        {
            continue;
        }

        status = axi_chan_irq_read(chan);
        if (!status)
        {
            continue;
        }

        axi_chan_irq_clear(chan, status);

        if (status & DWAXIDMAC_IRQ_ALL_ERR)
        {
            LOG_E("chan%u error irq 0x%08x", chan->id, status);
            axi_dma_stop(&chan->parent);
            rt_dma_chan_done(&chan->parent, 0);
        }
        else if (status & DWAXIDMAC_IRQ_DMA_TRF)
        {
            axi_dma_handle_complete(chan);
        }
    }

    axi_dma_irq_enable(chip);
}

static rt_err_t axi_dma_parse_props(struct rt_device *dev, struct dw_axi_dma_hcfg *hdata)
{
    int count;
    rt_uint32_t tmp, carr[DMAC_MAX_CHANNELS];
    rt_err_t err;

    if ((err = rt_dm_dev_prop_read_u32(dev, "dma-channels", &tmp)))
    {
        return err;
    }
    if (!tmp || tmp > DMAC_MAX_CHANNELS)
    {
        return -RT_EINVAL;
    }

    hdata->nr_channels = tmp;
    if (tmp <= DMA_REG_MAP_CH_REF)
    {
        hdata->reg_map_8_channels = RT_TRUE;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "snps,dma-masters", &tmp)))
    {
        return err;
    }
    if (!tmp || tmp > DMAC_MAX_MASTERS)
    {
        return -RT_EINVAL;
    }
    hdata->nr_masters = tmp;

    if (rt_dm_dev_prop_read_u32(dev, "snps,dma-targets", &tmp) == RT_EOK && tmp > 16)
    {
        hdata->use_cfg2 = RT_TRUE;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "snps,data-width", &tmp)))
    {
        return err;
    }
    if (tmp > DWAXIDMAC_TRANS_WIDTH_MAX)
    {
        return -RT_EINVAL;
    }
    hdata->m_data_width = tmp;

    if (rt_dm_dev_prop_read_u32_array_index(dev, "snps,block-size", 0,
                                            hdata->nr_channels, carr) != hdata->nr_channels)
    {
        return -RT_EINVAL;
    }
    for (tmp = 0; tmp < hdata->nr_channels; ++tmp)
    {
        if (!carr[tmp] || carr[tmp] > DMAC_MAX_BLK_SIZE)
        {
            return -RT_EINVAL;
        }
        hdata->block_size[tmp] = carr[tmp];
    }

    if (rt_dm_dev_prop_read_u32_array_index(dev, "snps,priority", 0,
                                            hdata->nr_channels, carr) != hdata->nr_channels)
    {
        return -RT_EINVAL;
    }
    for (tmp = 0; tmp < hdata->nr_channels; ++tmp)
    {
        if (carr[tmp] >= hdata->nr_channels)
        {
            return -RT_EINVAL;
        }
        hdata->priority[tmp] = carr[tmp];
    }

    count = rt_dm_dev_prop_count_of_u32(dev, "snps,axi-max-burst-len");
    if (count > 0 && count <= hdata->nr_channels &&
        rt_dm_dev_prop_read_u32_array_index(dev, "snps,axi-max-burst-len", 0,
                                            count, carr) == count)
    {
        hdata->restrict_axi_burst_len = RT_TRUE;
        for (tmp = 0; tmp < hdata->nr_channels; ++tmp)
        {
            rt_uint32_t burst_len = carr[rt_min(tmp, (rt_uint32_t)count - 1)];

            if (burst_len < DWAXIDMAC_ARWLEN_MIN + 1 ||
                burst_len > DWAXIDMAC_ARWLEN_MAX + 1)
            {
                return -RT_EINVAL;
            }
            hdata->axi_rw_burst_len[tmp] = burst_len;
        }
    }

    return RT_EOK;
}

static rt_err_t axi_dma_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_bool_t resumed = RT_FALSE;
    struct rt_device *dev = &pdev->parent;
    struct axi_dma_chip *chip = rt_calloc(1, sizeof(*chip));

    if (!chip)
    {
        return -RT_ENOMEM;
    }

    chip->regs = rt_dm_dev_iomap(dev, 0);
    if (!chip->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    chip->irq = rt_dm_dev_get_irq(dev, 0);
    if (chip->irq < 0)
    {
        err = chip->irq;
        goto _fail;
    }

    chip->core_clk = rt_clk_get_by_name(dev, "core-clk");
    if (rt_is_err(chip->core_clk))
    {
        err = rt_ptr_err(chip->core_clk);
        goto _fail;
    }

    chip->cfgr_clk = rt_clk_get_by_name(dev, "cfgr-clk");
    if (rt_is_err(chip->cfgr_clk))
    {
        err = rt_ptr_err(chip->cfgr_clk);
        goto _fail;
    }

    if ((err = axi_dma_parse_props(dev, &chip->hdata)))
    {
        goto _fail;
    }

    chip->chans = rt_calloc(chip->hdata.nr_channels, sizeof(chip->chans[0]));
    if (!chip->chans)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    for (rt_uint32_t i = 0; i < chip->hdata.nr_channels; ++i)
    {
        struct axi_dma_chan *chan = &chip->chans[i];

        chan->chip = chip;
        chan->id = i;
        chan->chan_regs = chip->regs + COMMON_REG_LEN + i * CHAN_REG_LEN;
    }

    if ((err = axi_dma_resume(chip)))
    {
        goto _fail;
    }
    resumed = RT_TRUE;

    axi_dma_hw_init(chip);

    chip->parent.dev = dev;
    chip->parent.ops = &axi_dma_ops;
    rt_dma_controller_add_direction(&chip->parent, RT_DMA_MEM_TO_MEM);
    rt_dma_controller_add_direction(&chip->parent, RT_DMA_MEM_TO_DEV);
    rt_dma_controller_add_direction(&chip->parent, RT_DMA_DEV_TO_MEM);
    rt_dma_controller_set_addr_mask(&chip->parent, RT_DMA_ADDR_MASK(64));

    if ((err = rt_dma_controller_register(&chip->parent)))
    {
        goto _fail;
    }

    rt_hw_interrupt_install(chip->irq, axi_dma_isr, chip, "axi-dma");
    rt_hw_interrupt_umask(chip->irq);

    dev->user_data = chip;

    LOG_I("DesignWare AXI DMA, %u channels", chip->hdata.nr_channels);

    return RT_EOK;

_fail:
    if (chip->chans)
    {
        rt_free(chip->chans);
    }
    if (resumed)
    {
        axi_dma_suspend(chip);
    }
    if (chip->regs)
    {
        rt_iounmap(chip->regs);
    }
    if (!rt_is_err_or_null(chip->core_clk))
    {
        rt_clk_put(chip->core_clk);
    }
    if (!rt_is_err_or_null(chip->cfgr_clk))
    {
        rt_clk_put(chip->cfgr_clk);
    }
    rt_free(chip);

    return err;
}

static rt_err_t axi_dma_remove(struct rt_platform_device *pdev)
{
    struct axi_dma_chip *chip = pdev->parent.user_data;

    rt_hw_interrupt_mask(chip->irq);
    rt_pic_detach_irq(chip->irq, chip);

    rt_dma_controller_unregister(&chip->parent);

    for (rt_uint32_t i = 0; i < chip->hdata.nr_channels; ++i)
    {
        axi_dma_free_llis(&chip->chans[i]);
    }

    axi_dma_suspend(chip);
    rt_iounmap(chip->regs);
    rt_clk_put(chip->core_clk);
    rt_clk_put(chip->cfgr_clk);
    rt_free(chip->chans);
    rt_free(chip);

    return RT_EOK;
}

static const struct rt_ofw_node_id axi_dma_ofw_ids[] = {
    { .compatible = "snps,axi-dma-1.01a" },
    { /* sentinel */ }
};

static struct rt_platform_driver axi_dma_driver = {
    .name = "dma-dw-axi",
    .ids = axi_dma_ofw_ids,
    .probe = axi_dma_probe,
    .remove = axi_dma_remove,
};

static int axi_dma_drv_register(void)
{
    rt_platform_driver_register(&axi_dma_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(axi_dma_drv_register);
