/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <dt-bindings/size.h>

#define DBG_TAG "dma.mmp-pdma"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mmu.h>

#define DDADRH(n)               (0x0300 + ((n) << 4))
#define DSADRH(n)               (0x0304 + ((n) << 4))
#define DTADRH(n)               (0x0308 + ((n) << 4))
#define DCSR_LPAEEN             RT_BIT(21)  /* Long Physical Address Extension enable */
#define DRCMR_INVALID           100         /* Max DMA request number + 1 */
#define DCMD_BURST64            (4 << 16)   /* 64 byte burst */

#define DCSR                    0x0000
#define DALGN                   0x00a0
#define DINT                    0x00f0
#define DDADR                   0x0200
#define DSADR(n)                (0x0204 + ((n) << 4))
#define DTADR(n)                (0x0208 + ((n) << 4))
#define DCMD                    0x020c

#define DCSR_RUN                RT_BIT(31)  /* Run Bit (read / write) */
#define DCSR_NODESC             RT_BIT(30)  /* No-Descriptor Fetch (read / write) */
#define DCSR_STOPIRQEN          RT_BIT(29)  /* Stop Interrupt Enable (read / write) */
#define DCSR_REQPEND            RT_BIT(8)   /* Request Pending (read-only) */
#define DCSR_STOPSTATE          RT_BIT(3)   /* Stop State (read-only) */
#define DCSR_ENDINTR            RT_BIT(2)   /* End Interrupt (read / write) */
#define DCSR_STARTINTR          RT_BIT(1)   /* Start Interrupt (read / write) */
#define DCSR_BUSERR             RT_BIT(0)   /* Bus Error Interrupt (read / write) */

#define DCSR_EORIRQEN           RT_BIT(28)  /* End of Receive Interrupt Enable (R/W) */
#define DCSR_EORJMPEN           RT_BIT(27)  /* Jump to next descriptor on EOR */
#define DCSR_EORSTOPEN          RT_BIT(26)  /* STOP on an EOR */
#define DCSR_SETCMPST           RT_BIT(25)  /* Set Descriptor Compare Status */
#define DCSR_CLRCMPST           RT_BIT(24)  /* Clear Descriptor Compare Status */
#define DCSR_CMPST              RT_BIT(10)  /* The Descriptor Compare Status */
#define DCSR_EORINTR            RT_BIT(9)   /* The end of Receive */

#define DRCMR(n)                ((((n) < 64) ? 0x0100 : 0x1100) + (((n) & 0x3f) << 2))
#define DRCMR_MAPVLD            RT_BIT(7)   /* Map Valid (read / write) */
#define DRCMR_CHLNUM            0x1f        /* mask for Channel Number (read / write) */

#define DDADR_DESCADDR          0xfffffff0  /* Address of next descriptor (mask) */
#define DDADR_STOP              RT_BIT(0)   /* Stop (read / write) */

#define DCMD_INCSRCADDR         RT_BIT(31)  /* Source Address Increment Setting. */
#define DCMD_INCTRGADDR         RT_BIT(30)  /* Target Address Increment Setting. */
#define DCMD_FLOWSRC            RT_BIT(29)  /* Flow Control by the source. */
#define DCMD_FLOWTRG            RT_BIT(28)  /* Flow Control by the target. */
#define DCMD_STARTIRQEN         RT_BIT(22)  /* Start Interrupt Enable */
#define DCMD_ENDIRQEN           RT_BIT(21)  /* End Interrupt Enable */
#define DCMD_ENDIAN             RT_BIT(18)  /* Device Endian-ness. */
#define DCMD_BURST8             (1 << 16)   /* 8 byte burst */
#define DCMD_BURST16            (2 << 16)   /* 16 byte burst */
#define DCMD_BURST32            (3 << 16)   /* 32 byte burst */
#define DCMD_WIDTH1             (1 << 14)   /* 1 byte width */
#define DCMD_WIDTH2             (2 << 14)   /* 2 byte width (HalfWord) */
#define DCMD_WIDTH4             (3 << 14)   /* 4 byte width (Word) */
#define DCMD_LENGTH             0x01fff     /* length mask (max = 8K - 1) */

#define DEFAULT_MAX_BURST_SIZE  32
#define INVALID_BURST_SETTING   -1

#define PDMA_MAX_DESC_BYTES     DCMD_LENGTH

#ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
struct mmp_pdma_desc_hw
{
    rt_uint32_t ddadr;  /* Points to the next descriptor + flags */
    rt_uint32_t dsadr;  /* DSADR value for the current transfer */
    rt_uint32_t dtadr;  /* DTADR value for the current transfer */
    rt_uint32_t dcmd;   /* DCMD value for the current transfer */
    rt_uint32_t ddadrh; /* Points to the next descriptor + flags */
    rt_uint32_t dsadrh; /* DSADR value for the current transfer */
    rt_uint32_t dtadrh; /* DTADR value for the current transfer */
    rt_uint32_t rsvd;   /* DCMD value for the current transfer */
} rt_align(64);
#else
struct mmp_pdma_desc_hw
{
    rt_uint32_t ddadr;  /* Points to the next descriptor + flags */
    rt_uint32_t dsadr;  /* DSADR value for the current transfer */
    rt_uint32_t dtadr;  /* DTADR value for the current transfer */
    rt_uint32_t dcmd;   /* DCMD value for the current transfer */
} rt_align(32);
#endif

struct mmp_pdma_chan
{
    struct rt_dma_chan parent;

    rt_size_t desc_nr;
    rt_ubase_t desc_dma;
    struct mmp_pdma_desc_hw *desc;

    rt_uint32_t dcmd;
    rt_uint32_t drcmr;
    rt_uint32_t dev_addr;

    rt_size_t size;
    rt_uint32_t bytes_residue;
    rt_bool_t byte_align;
    rt_bool_t pausing;
    enum rt_dma_transfer_direction dir;
};

struct reserved_chan
{
    rt_uint32_t chan_id;
    rt_uint32_t drcmr;
};

struct mmp_pdma_device
{
    struct rt_dma_controller parent;

    struct rt_clk *clk;
    struct rt_reset_control *rstc;

    int irq;
    void *base;

    rt_uint32_t max_burst_size;

    rt_uint32_t dma_channels;
    struct mmp_pdma_chan *chan;

    rt_uint32_t reserved_channels_nr;
    struct reserved_chan *reserved_channels;

    struct mmp_pdma_phy *phy;
};
#define raw_to_mmp_pdma_device(raw)         rt_container_of(raw, struct mmp_pdma_device, parent)
#define raw_to_mmp_pdma_device_chan(raw)    rt_container_of(raw, struct mmp_pdma_chan, parent)

static int get_max_burst_setting(rt_uint32_t max_burst_size)
{
    switch (max_burst_size)
    {
    case 8:
        return DCMD_BURST8;
    case 16:
        return DCMD_BURST16;
    case 32:
        return DCMD_BURST32;
    case 64:
        return DCMD_BURST64;
    default:
        return INVALID_BURST_SETTING;
    }
}

static void enable_chan(struct mmp_pdma_chan *chan)
{
    int idx;
    rt_uint32_t reg, dalgn, dcsr;
    struct mmp_pdma_device *pdma = raw_to_mmp_pdma_device(chan->parent.ctrl);

    idx = chan - pdma->chan;

    if (chan->drcmr >= 0)
    {
        reg = DRCMR(chan->drcmr);
        HWREG32(pdma->base + reg) = DRCMR_MAPVLD | idx;
    }

    dalgn = HWREG32(pdma->base + DALGN);
    if (chan->byte_align)
    {
        dalgn |= 1 << idx;
    }
    else
    {
        dalgn &= ~(1 << idx);
    }
    HWREG32(pdma->base + DALGN) = dalgn;

    reg = (idx << 2) + DCSR;

    dcsr = HWREG32(pdma->base + reg);
    dcsr |= DCSR_RUN | DCSR_EORIRQEN | DCSR_EORSTOPEN;
#ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
    /* Use long descriptor mode: set DCSR_LPAEEN bit */
    dcsr |= DCSR_LPAEEN;
#endif
    HWREG32(pdma->base + reg) = dcsr;
}

static void disable_chan(struct mmp_pdma_chan *chan)
{
    int idx;
    rt_uint32_t reg, dcsr, cnt = 1000;
    struct mmp_pdma_device *pdma = raw_to_mmp_pdma_device(chan->parent.ctrl);

    idx = chan - pdma->chan;

    reg = (idx << 2) + DCSR;

    dcsr = HWREG32(pdma->base + reg);
    dcsr &= ~(DCSR_RUN | DCSR_EORIRQEN | DCSR_EORSTOPEN);
#ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
    /* Use long descriptor mode: set DCSR_LPAEEN bit */
    dcsr &= ~DCSR_LPAEEN;
#endif
    HWREG32(pdma->base + reg) = dcsr;

    /* Ensure dma is stopped. */
    dcsr = HWREG32(pdma->base + reg);
    while (!(dcsr & (0x1 << 3)) && --cnt)
    {
        rt_hw_us_delay(10);
        dcsr = HWREG32(pdma->base + reg);
    }
}

static void mmp_pdma_config_write(struct mmp_pdma_chan *chan,
        struct rt_dma_slave_config *cfg,
        enum rt_dma_transfer_direction direction)
{
    rt_uint32_t maxburst = 0, addr = 0;
    enum rt_dma_slave_buswidth width = RT_DMA_SLAVE_BUSWIDTH_UNDEFINED;

    if (direction == RT_DMA_DEV_TO_MEM)
    {
        chan->dcmd = DCMD_INCTRGADDR | DCMD_FLOWSRC;
        maxburst = cfg->src_maxburst;
        width = cfg->src_addr_width;
        addr = cfg->src_addr;
    }
    else if (direction == RT_DMA_MEM_TO_DEV)
    {
        chan->dcmd = DCMD_INCSRCADDR | DCMD_FLOWTRG;
        maxburst = cfg->dst_maxburst;
        width = cfg->dst_addr_width;
        addr = cfg->dst_addr;
    }

    if (width == RT_DMA_SLAVE_BUSWIDTH_1_BYTE)
    {
        chan->dcmd |= DCMD_WIDTH1;
    }
    else if (width == RT_DMA_SLAVE_BUSWIDTH_2_BYTES)
    {
        chan->dcmd |= DCMD_WIDTH2;
    }
    else if (width == RT_DMA_SLAVE_BUSWIDTH_4_BYTES)
    {
        chan->dcmd |= DCMD_WIDTH4;
    }

    if (maxburst == 8)
    {
        chan->dcmd |= DCMD_BURST8;
    }
    else if (maxburst == 16)
    {
        chan->dcmd |= DCMD_BURST16;
    }
    else if (maxburst == 32)
    {
        chan->dcmd |= DCMD_BURST32;
    }

    chan->dir = direction;
    chan->dev_addr = addr;
}

static struct rt_dma_chan *mmp_pdma_request_chan(struct rt_dma_controller *ctrl,
        struct rt_device *slave, void *fw_data)
{
    int drcmr;
    struct mmp_pdma_chan *chan = RT_NULL;
    struct mmp_pdma_device *pdma = raw_to_mmp_pdma_device(ctrl);
    struct rt_ofw_cell_args *args = fw_data;

    drcmr = args ? args->args[0] : -1;

    for (int i = 0; i < pdma->dma_channels; ++i)
    {
        if (!pdma->chan[i].desc)
        {
            for (int j = 0; j < pdma->reserved_channels_nr; ++j)
            {
                if (pdma->reserved_channels[i].chan_id == i &&
                    (pdma->reserved_channels[i].drcmr != drcmr || drcmr >= 0))
                {
                    goto _find_next;
                }
            }

            chan = &pdma->chan[i];
            break;
        }
    _find_next:
        ;
    }

    if (!chan)
    {
        return rt_err_ptr(-RT_EBUSY);
    }

    chan->drcmr = drcmr;
    chan->pausing = RT_FALSE;
    chan->desc_nr = ARCH_PAGE_SIZE / sizeof(*chan->desc);
    chan->desc = rt_dma_alloc_coherent(slave, ARCH_PAGE_SIZE, &chan->desc_dma);

    if (!chan->desc)
    {
        return rt_err_ptr(-RT_ENOMEM);
    }

    return &chan->parent;
}

static rt_err_t mmp_pdma_release_chan(struct rt_dma_chan *raw_chan)
{
    struct mmp_pdma_chan *chan = raw_to_mmp_pdma_device_chan(raw_chan);

    rt_dma_free_coherent(raw_chan->slave, ARCH_PAGE_SIZE, chan->desc, chan->desc_dma);
    chan->desc = RT_NULL;

    return RT_EOK;
}

static rt_err_t mmp_pdma_start(struct rt_dma_chan *raw_chan)
{
    struct mmp_pdma_chan *chan = raw_to_mmp_pdma_device_chan(raw_chan);

    if (!chan->pausing)
    {
        int idx;
        rt_uint32_t reg;
        struct mmp_pdma_device *pdma = raw_to_mmp_pdma_device(chan->parent.ctrl);

        idx = chan - pdma->chan;
        reg = (idx << 4) + DDADR;

        HWREG32(pdma->base + reg) = chan->desc_dma & 0xffffffff;
    #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
        /* Config higher bits for desc address */
        HWREG32(pdma->base + DDADRH(idx)) = (rt_uint32_t)(chan->desc_dma >> 32);
    #endif
    }

    enable_chan(chan);
    chan->bytes_residue = 0;
    chan->pausing = RT_FALSE;

    return RT_EOK;
}

static rt_err_t mmp_pdma_pause(struct rt_dma_chan *raw_chan)
{
    struct mmp_pdma_chan *chan = raw_to_mmp_pdma_device_chan(raw_chan);

    disable_chan(chan);
    chan->pausing = RT_TRUE;

    return RT_EOK;
}

static rt_err_t mmp_pdma_stop(struct rt_dma_chan *raw_chan)
{
    rt_uint32_t reg;
    struct mmp_pdma_chan *chan = raw_to_mmp_pdma_device_chan(raw_chan);
    struct mmp_pdma_device *pdma = raw_to_mmp_pdma_device(raw_chan->ctrl);

    disable_chan(chan);

    if (chan->drcmr >= 0)
    {
        /* Clear the channel mapping in DRCMR */
        reg = DRCMR(chan->drcmr);
        HWREG32(pdma->base + reg) = 0;
    }

    chan->bytes_residue = 0;
    chan->pausing = RT_FALSE;

    return RT_EOK;
}

static rt_err_t mmp_pdma_config(struct rt_dma_chan *raw_chan,
        struct rt_dma_slave_config *conf)
{
    if (conf->src_addr_width == RT_DMA_SLAVE_BUSWIDTH_UNDEFINED)
    {
        conf->src_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    }
    if (conf->dst_addr_width == RT_DMA_SLAVE_BUSWIDTH_UNDEFINED)
    {
        conf->dst_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
    }

    return RT_EOK;
}

static rt_err_t mmp_pdma_prep_memcpy(struct rt_dma_chan *raw_chan,
        rt_ubase_t dma_addr_src, rt_ubase_t dma_addr_dst, rt_size_t len)
{
    int idx;
    rt_size_t copy = 0;
    rt_ubase_t desc_dma;
    struct mmp_pdma_desc_hw *desc, *prev_desc;
    struct mmp_pdma_chan *chan = raw_to_mmp_pdma_device_chan(raw_chan);
    struct mmp_pdma_device *pdma = raw_to_mmp_pdma_device(raw_chan->ctrl);

    if (len > chan->desc_nr * PDMA_MAX_DESC_BYTES)
    {
        return -RT_EEMPTY;
    }

    chan->byte_align = RT_FALSE;

    if (!chan->dir)
    {
        chan->dir = RT_DMA_MEM_TO_MEM;
        chan->dcmd = DCMD_INCTRGADDR | DCMD_INCSRCADDR | get_max_burst_setting(pdma->max_burst_size);
    }

    chan->size = len;

    for (idx = 0, desc_dma = chan->desc_dma; len; ++idx, desc_dma += sizeof(*desc))
    {
        copy = rt_min_t(rt_size_t, len, PDMA_MAX_DESC_BYTES);

        if ((dma_addr_src & 0x7) || (dma_addr_dst & 0x7))
        {
            chan->byte_align = RT_TRUE;
        }

        desc = &chan->desc[idx];
        desc->dcmd = chan->dcmd | (DCMD_LENGTH & copy);

        /*
         * Check whether descriptor/source-addr/target-addr is in
         * region higher than 4G. If so, set related higher bits to 1.
         */
        if (chan->dir == RT_DMA_MEM_TO_DEV)
        {
            desc->dsadr = dma_addr_src & 0xffffffff;
            desc->dtadr = dma_addr_dst;
        #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
            desc->dsadrh = dma_addr_src >> 32;
            desc->dtadrh = 0;
        #endif
        }
        else if (chan->dir == RT_DMA_DEV_TO_MEM)
        {
            desc->dsadr = dma_addr_src;
            desc->dtadr = dma_addr_dst & 0xffffffff;
        #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
            desc->dsadrh = 0;
            desc->dtadrh = dma_addr_dst >> 32;
        #endif
        }
        else if (chan->dir == RT_DMA_MEM_TO_MEM)
        {
            desc->dsadr = dma_addr_src & 0xffffffff;
            desc->dtadr = dma_addr_dst & 0xffffffff;
        #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
            desc->dsadrh = dma_addr_src >> 32;
            desc->dtadrh = dma_addr_dst >> 32;
        #endif
        }

        len -= copy;

        if (chan->dir == RT_DMA_MEM_TO_DEV)
        {
            dma_addr_src += copy;
        }
        else if (chan->dir == RT_DMA_DEV_TO_MEM)
        {
            dma_addr_dst += copy;
        }
        else if (chan->dir == RT_DMA_MEM_TO_MEM)
        {
            dma_addr_src += copy;
            dma_addr_dst += copy;
        }

        if (idx)
        {
            prev_desc = &chan->desc[idx - 1];

            prev_desc->ddadr = desc_dma;
        #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
            prev_desc->ddadrh = desc_dma >> 32;
        #endif
        }
    }

    prev_desc = &chan->desc[idx - 1];

    prev_desc->ddadr = DDADR_STOP;
    prev_desc->dcmd |= DCMD_ENDIRQEN;

    return RT_EOK;
}

static rt_err_t mmp_pdma_prep_cyclic(struct rt_dma_chan *raw_chan,
        rt_ubase_t dma_buf_addr, rt_size_t buf_len, rt_size_t period_len,
        enum rt_dma_transfer_direction dir)
{
    int idx;
    rt_ubase_t desc_dma;
    rt_ubase_t dma_addr_src, dma_addr_dst;
#ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
    rt_ubase_t dma_addr_srch, dma_addr_dsth;
#endif
    struct mmp_pdma_desc_hw *desc, *prev_desc;
    struct mmp_pdma_chan *chan = raw_to_mmp_pdma_device_chan(raw_chan);

    if (buf_len % period_len != 0)
    {
        return -RT_EINVAL;
    }

    if (period_len > PDMA_MAX_DESC_BYTES)
    {
        return -RT_EINVAL;
    }

    if (buf_len > chan->desc_nr * PDMA_MAX_DESC_BYTES)
    {
        return -RT_EEMPTY;
    }

    mmp_pdma_config_write(chan, &raw_chan->conf, dir);

    switch (dir)
    {
    case RT_DMA_MEM_TO_DEV:
        dma_addr_src = dma_buf_addr & 0xffffffff;
        dma_addr_dst = chan->dev_addr;
    #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
        dma_addr_srch = dma_buf_addr >> 32;
        dma_addr_dsth = 0;
    #endif
        break;

    case RT_DMA_DEV_TO_MEM:
        dma_addr_dst = dma_buf_addr & 0xffffffff;
        dma_addr_src = chan->dev_addr;
    #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
        dma_addr_dsth = dma_buf_addr >> 32;
        dma_addr_srch = 0;
    #endif
        break;

    default:
        LOG_E("Unsupported direction for cyclic DMA");
        return -RT_EINVAL;
    }

    chan->dir = dir;
    chan->size = buf_len;

    for (idx = 0, desc_dma = chan->desc_dma; buf_len; ++idx, desc_dma += sizeof(*desc))
    {
        desc = &chan->desc[idx];

        desc->dcmd = chan->dcmd | DCMD_ENDIRQEN | (DCMD_LENGTH & period_len);
        desc->dsadr = dma_addr_src;
        desc->dtadr = dma_addr_dst;
    #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
        desc->dsadrh = dma_addr_dsth;
        desc->dtadrh = dma_addr_srch;
    #endif

        buf_len -= period_len;

        if (chan->dir == RT_DMA_MEM_TO_DEV)
        {
            dma_addr_src += period_len;
        }
        else
        {
            dma_addr_dst += period_len;
        }

        if (idx)
        {
            prev_desc = &chan->desc[idx - 1];

            prev_desc->ddadr = desc_dma;
        #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
            prev_desc->ddadrh = desc_dma >> 32;
        #endif
        }
    };

    prev_desc = &chan->desc[idx - 1];

    /* Make the cyclic link */
    prev_desc->ddadr = chan->desc_dma;

    return RT_EOK;
}

static rt_err_t mmp_pdma_prep_single(struct rt_dma_chan *raw_chan,
        rt_ubase_t dma_buf_addr, rt_size_t buf_len,
        enum rt_dma_transfer_direction dir)
{
    int idx;
    rt_size_t copy = 0;
    rt_ubase_t desc_dma;
    struct mmp_pdma_desc_hw *desc, *prev_desc;
    struct mmp_pdma_chan *chan = raw_to_mmp_pdma_device_chan(raw_chan);

    if (buf_len > chan->desc_nr * PDMA_MAX_DESC_BYTES)
    {
        return -RT_EEMPTY;
    }

    chan->byte_align = RT_TRUE;

    mmp_pdma_config_write(chan, &raw_chan->conf, dir);

    chan->dir = dir;
    chan->size = buf_len;

    for (idx = 0, desc_dma = chan->desc_dma; buf_len; ++idx, desc_dma += sizeof(*desc))
    {
        copy = rt_min_t(rt_size_t, buf_len, PDMA_MAX_DESC_BYTES);

        if (dma_buf_addr & 0x7)
        {
            chan->byte_align = RT_TRUE;
        }

        desc = &chan->desc[idx];
        desc->dcmd = chan->dcmd | (DCMD_LENGTH & copy);

        /*
         * Check whether descriptor/source-addr/target-addr is in
         * region higher than 4G. If so, set related higher bits to 1.
         */
        if (dir == RT_DMA_MEM_TO_DEV)
        {
            desc->dsadr = dma_buf_addr & 0xffffffff;
            desc->dtadr = chan->dev_addr;
        #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
            desc->dsadrh = dma_buf_addr >> 32;
            desc->dtadrh = 0;
        #endif
        }
        else if (dir == RT_DMA_DEV_TO_MEM)
        {
            desc->dsadr = chan->dev_addr;
            desc->dtadr = dma_buf_addr & 0xffffffff;
        #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
            desc->dsadrh = 0;
            desc->dtadrh = dma_buf_addr >> 32;
        #endif
        }
        else
        {
            return -RT_EINVAL;
        }

        dma_buf_addr += copy;
        buf_len -= copy;

        if (idx)
        {
            prev_desc = &chan->desc[idx - 1];

            prev_desc->ddadr = desc_dma;
        #ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
            prev_desc->ddadrh = desc_dma >> 32;
        #endif
        }
    }

    prev_desc = &chan->desc[idx - 1];

    prev_desc->ddadr = DDADR_STOP;
    prev_desc->dcmd |= DCMD_ENDIRQEN;

    return RT_EOK;
}

static const struct rt_dma_controller_ops mmp_pdma_ops =
{
    .request_chan = mmp_pdma_request_chan,
    .release_chan = mmp_pdma_release_chan,
    .start = mmp_pdma_start,
    .pause = mmp_pdma_pause,
    .stop = mmp_pdma_stop,
    .config = mmp_pdma_config,
    .prep_memcpy = mmp_pdma_prep_memcpy,
    .prep_cyclic = mmp_pdma_prep_cyclic,
    .prep_single = mmp_pdma_prep_single,
};

static void mmp_pdma_isr(int irq, void *param)
{
    rt_uint32_t i, dint, dcsr;
    struct mmp_pdma_chan *chan;
    struct mmp_pdma_device *pdma = param;

    dint = HWREG32(pdma->base + DINT);

    while (dint)
    {
        if ((i = __rt_ffs(dint) - 1) >= pdma->dma_channels)
        {
            break;
        }

        chan = &pdma->chan[i];

        /* Clear IRQ */
        dcsr = HWREG32(pdma->base + (i << 2) + DCSR);
        HWREG32(pdma->base + (i << 2) + DCSR) = dcsr;

        rt_dma_chan_done(&chan->parent, chan->size);

        dint &= (dint - 1);
    }
}

#ifdef RT_USING_PM
static rt_err_t mmp_pdma_pm_suspend(const struct rt_device *device, rt_uint8_t mode)
{
    struct mmp_pdma_device *pdma = device->user_data;

    rt_clk_disable_unprepare(pdma->clk);

    return RT_EOK;
}

static void mmp_pdma_pm_resume(const struct rt_device *device, rt_uint8_t mode)
{
    struct mmp_pdma_device *pdma = device->user_data;

    rt_clk_prepare_enable(pdma->clk);
}

static const struct rt_device_pm_ops mmp_pdma_pm_ops =
{
    .suspend = mmp_pdma_pm_suspend,
    .resume = mmp_pdma_pm_resume,
};
#endif /* RT_USING_PM */

static void mmp_pdma_free(struct mmp_pdma_device *pdma, struct rt_device *dev)
{
    if (pdma->base)
    {
        rt_iounmap(pdma->base);
    }

    if (!rt_is_err_or_null(pdma->clk))
    {
        rt_clk_disable_unprepare(pdma->clk);
        rt_clk_put(pdma->clk);
    }

    if (!rt_is_err_or_null(pdma->rstc))
    {
        rt_reset_control_put(pdma->rstc);
    }

    if (pdma->reserved_channels)
    {
        rt_free(pdma->reserved_channels);
    }

    if (pdma->chan)
    {
        rt_free(pdma->chan);
    }

    rt_free(pdma);
}

static rt_err_t mmp_pdma_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct mmp_pdma_device *pdma = rt_calloc(1, sizeof(*pdma));

    if (!pdma)
    {
        return -RT_ENOMEM;
    }

    if (!(pdma->base = rt_dm_dev_iomap(dev, 0)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if ((pdma->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = pdma->irq;
        goto _fail;
    }

    pdma->clk = rt_clk_get_by_index(dev, 0);
    if (rt_is_err(pdma->clk))
    {
        err = rt_ptr_err(pdma->clk);
        goto _fail;
    }

    if ((err = rt_clk_prepare_enable(pdma->clk)))
    {
        goto _fail;
    }

    pdma->rstc = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(pdma->rstc))
    {
        err = rt_ptr_err(pdma->rstc);
        goto _fail;
    }

    if ((err = rt_reset_control_deassert(pdma->rstc)))
    {
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "#dma-channels", &pdma->dma_channels)))
    {
        goto _fail;
    }

    if (rt_dm_dev_prop_read_u32(dev, "max-burst-size", &pdma->max_burst_size) ||
        get_max_burst_setting(pdma->max_burst_size) == INVALID_BURST_SETTING)
    {
        pdma->max_burst_size = DEFAULT_MAX_BURST_SIZE;
    }

    pdma->reserved_channels_nr = rt_dm_dev_prop_count_of_size(dev,
            "reserved-channels", sizeof(rt_uint32_t) * 2);

    if (pdma->reserved_channels_nr > 0)
    {
        pdma->reserved_channels = rt_calloc(pdma->reserved_channels_nr, sizeof(struct reserved_chan));

        if (!pdma->reserved_channels)
        {
            err = -RT_ENOMEM;
            goto _fail;
        }

        for (int i = 0; i < pdma->reserved_channels_nr; ++i)
        {
            rt_dm_dev_prop_read_u32_index(dev, "reserved-channels", i * 2,
                    &pdma->reserved_channels[i].chan_id);
            rt_dm_dev_prop_read_u32_index(dev, "reserved-channels", i * 2 + 1,
                    &pdma->reserved_channels[i].drcmr);
        }
    }

    if (!(pdma->chan = rt_calloc(pdma->dma_channels, sizeof(*pdma->chan))))
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    pdma->parent.dev = dev;
    pdma->parent.ops = &mmp_pdma_ops;
    rt_dma_controller_add_direction(&pdma->parent, RT_DMA_MEM_TO_MEM);
    rt_dma_controller_add_direction(&pdma->parent, RT_DMA_MEM_TO_DEV);
    rt_dma_controller_add_direction(&pdma->parent, RT_DMA_DEV_TO_MEM);
#ifdef RT_DMA_MMP_PDMA_SUPPORT_64BIT
    rt_dma_controller_set_addr_mask(&pdma->parent, RT_DMA_ADDR_MASK(64));
#else
    rt_dma_controller_set_addr_mask(&pdma->parent, RT_DMA_ADDR_MASK(32));
#endif

    if ((err = rt_dma_controller_register(&pdma->parent)))
    {
        goto _fail;
    }

    rt_hw_interrupt_install(pdma->irq, mmp_pdma_isr, pdma, "pdma");
    rt_hw_interrupt_umask(pdma->irq);

    dev->user_data = pdma;

#ifdef RT_USING_PM
    rt_pm_device_register(dev, &mmp_pdma_pm_ops);
#endif

    return RT_EOK;

_fail:
    mmp_pdma_free(pdma, dev);

    return err;
}

static rt_err_t mmp_pdma_remove(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct mmp_pdma_device *pdma = dev->user_data;

#ifdef RT_USING_PM
    rt_pm_device_unregister(dev);
#endif

    rt_dma_controller_unregister(&pdma->parent);

    rt_hw_interrupt_mask(pdma->irq);
    rt_pic_detach_irq(pdma->irq, pdma);

    rt_reset_control_assert(pdma->rstc);

    mmp_pdma_free(pdma, dev);

    return RT_EOK;
}

static const struct rt_ofw_node_id mmp_pdma_ofw_ids[] =
{
    { .compatible = "spacemit,pdma-1.0" },
    { /* sentinel */ }
};

static struct rt_platform_driver mmp_pdma_driver =
{
    .name = "dma-mmp-pdma",
    .ids = mmp_pdma_ofw_ids,

    .probe = mmp_pdma_probe,
    .remove = mmp_pdma_remove,
};

static int mmp_pdma_drv_register(void)
{
    rt_platform_driver_register(&mmp_pdma_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(mmp_pdma_drv_register);
