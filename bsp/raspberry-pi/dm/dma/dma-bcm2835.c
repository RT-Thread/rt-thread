/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-26     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <dt-bindings/size.h>

#define DBG_TAG "dma.bcm2835"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define BCM2835_DMA_CS                      0x00
#define BCM2835_DMA_ADDR                    0x04
#define BCM2835_DMA_TI                      0x08
#define BCM2835_DMA_SOURCE_AD               0x0c
#define BCM2835_DMA_DEST_AD                 0x10
#define BCM2835_DMA_LEN                     0x14
#define BCM2835_DMA_STRIDE                  0x18
#define BCM2835_DMA_NEXTCB                  0x1c
#define BCM2835_DMA_DEBUG                   0x20

/* DMA CS Control and Status bits */
#define BCM2835_DMA_ACTIVE                  RT_BIT(0) /* Activate the DMA */
#define BCM2835_DMA_END                     RT_BIT(1) /* Current CB has ended */
#define BCM2835_DMA_INT                     RT_BIT(2) /* Interrupt status */
#define BCM2835_DMA_DREQ                    RT_BIT(3) /* DREQ state */
#define BCM2835_DMA_ISPAUSED                RT_BIT(4) /* Pause requested or not active */
#define BCM2835_DMA_ISHELD                  RT_BIT(5) /* Is held by DREQ flow control */
#define BCM2835_DMA_WAITING_FOR_WRITES      RT_BIT(6) /* Waiting for last AXI-write to ack */
#define BCM2835_DMA_ERR                     RT_BIT(8)
#define BCM2835_DMA_PRIORITY(x)             ((x & 15) << 16) /* AXI priority */
#define BCM2835_DMA_PANIC_PRIORITY(x)       ((x & 15) << 20) /* Panic priority */
#define BCM2835_DMA_WAIT_FOR_WRITES         RT_BIT(28)
#define BCM2835_DMA_DIS_DEBUG               RT_BIT(29) /* Disable debug pause signal */
#define BCM2835_DMA_ABORT                   RT_BIT(30) /* Stop current CB, go to next, WO */
#define BCM2835_DMA_RESET                   RT_BIT(31) /* WO, self clearing */

#define BCM2835_DMA_DEBUG_LITE              RT_BIT(28)

#define BCM2835_DMA_INT_EN                  RT_BIT(0)
#define BCM2835_DMA_TDMODE                  RT_BIT(1) /* 2D-Mode */
#define BCM2835_DMA_WAIT_RESP               RT_BIT(3) /* wait for AXI-write to be acked */
#define BCM2835_DMA_D_INC                   RT_BIT(4)
#define BCM2835_DMA_D_WIDTH                 RT_BIT(5) /* 128bit writes if set */
#define BCM2835_DMA_D_DREQ                  RT_BIT(6) /* Enable DREQ for destination */
#define BCM2835_DMA_D_IGNORE                RT_BIT(7) /* Ignore destination writes */
#define BCM2835_DMA_S_INC                   RT_BIT(8)
#define BCM2835_DMA_S_WIDTH                 RT_BIT(9) /* 128bit writes if set */
#define BCM2835_DMA_S_DREQ                  RT_BIT(10) /* Enable SREQ for source */
#define BCM2835_DMA_S_IGNORE                RT_BIT(11) /* Ignore source reads - read 0 */
#define BCM2835_DMA_BURST_LENGTH(x)         (((x) & 15) << 12)
#define BCM2835_DMA_GET_BURST_LENGTH(x)     (((x) >> 12) & 15)
#define BCM2835_DMA_CS_FLAGS(x)             (x & (BCM2835_DMA_PRIORITY(15) | BCM2835_DMA_PANIC_PRIORITY(15) | \
                                            BCM2835_DMA_WAIT_FOR_WRITES | BCM2835_DMA_DIS_DEBUG))

#define BCM2835_DMA_PER_MAP(x)              ((x & 31) << 16) /* REQ source */
#define BCM2835_DMA_WAIT(x)                 ((x & 31) << 21) /* Add DMA-wait cycles */
#define BCM2835_DMA_NO_WIDE_BURSTS          RT_BIT(26) /* No 2 beat write bursts */

/* A fake bit to request that the driver doesn't set the WAIT_RESP bit. */
#define BCM2835_DMA_NO_WAIT_RESP            RT_BIT(27)
#define WAIT_RESP(x)                        ((x & BCM2835_DMA_NO_WAIT_RESP) ? 0 : BCM2835_DMA_WAIT_RESP)

/* A fake bit to request that the driver requires wide reads */
#define BCM2835_DMA_WIDE_SOURCE             RT_BIT(24)
#define WIDE_SOURCE(x)                      ((x & BCM2835_DMA_WIDE_SOURCE) ? BCM2835_DMA_S_WIDTH : 0)

/* A fake bit to request that the driver requires wide writes */
#define BCM2835_DMA_WIDE_DEST               RT_BIT(25)
#define WIDE_DEST(x)                        ((x & BCM2835_DMA_WIDE_DEST) ? BCM2835_DMA_D_WIDTH : 0)

/* A fake bit to request that the driver requires multi-beat burst */
#define BCM2835_DMA_BURST                   RT_BIT(30)
#define BURST_LENGTH(x)                     ((x & BCM2835_DMA_BURST) ? BCM2835_DMA_BURST_LENGTH(3) : 0)

/* Valid only for channels 0 - 14, 15 has its own base address */
#define BCM2835_DMA_CHAN_SIZE               0x100
#define BCM2835_DMA_CHAN(n)                 ((n) * BCM2835_DMA_CHAN_SIZE) /* Base address */
#define BCM2835_DMA_CHANIO(base, n)         ((base) + BCM2835_DMA_CHAN(n))

/* 40-bit DMA support */
#define BCM2711_DMA40_CS                    0x00
#define BCM2711_DMA40_CB                    0x04
#define BCM2711_DMA40_DEBUG                 0x0c
#define BCM2711_DMA40_TI                    0x10
#define BCM2711_DMA40_SRC                   0x14
#define BCM2711_DMA40_SRCI                  0x18
#define BCM2711_DMA40_DEST                  0x1c
#define BCM2711_DMA40_DESTI                 0x20
#define BCM2711_DMA40_LEN                   0x24
#define BCM2711_DMA40_NEXT_CB               0x28
#define BCM2711_DMA40_DEBUG2                0x2c

#define BCM2711_DMA40_DEBUG_RESET           RT_BIT(23)

#define BCM2711_DMA40_ACTIVE                RT_BIT(0)
#define BCM2711_DMA40_END                   RT_BIT(1)
#define BCM2711_DMA40_INT                   RT_BIT(2)
#define BCM2711_DMA40_DREQ                  RT_BIT(3)  /* DREQ state */
#define BCM2711_DMA40_RD_PAUSED             RT_BIT(4)  /* Reading is paused */
#define BCM2711_DMA40_WR_PAUSED             RT_BIT(5)  /* Writing is paused */
#define BCM2711_DMA40_DREQ_PAUSED           RT_BIT(6)  /* Is paused by DREQ flow control */
#define BCM2711_DMA40_WAITING_FOR_WRITES    RT_BIT(7)  /* Waiting for last write */
#define BCM2711_DMA40_PROT                  (RT_BIT(8) | RT_BIT(9))
#define BCM2711_DMA40_ERR                   RT_BIT(10)
#define BCM2711_DMA40_QOS(x)                (((x) & 0x1f) << 16)
#define BCM2711_DMA40_PANIC_QOS(x)          (((x) & 0x1f) << 20)
#define BCM2711_DMA40_TRANSACTIONS          RT_BIT(25)
#define BCM2711_DMA40_WAIT_FOR_WRITES       RT_BIT(28)
#define BCM2711_DMA40_DISDEBUG              RT_BIT(29)
#define BCM2711_DMA40_ABORT                 RT_BIT(30)
#define BCM2711_DMA40_HALT                  RT_BIT(31)

#define BCM2711_DMA40_CS_FLAGS(x)           (x & (BCM2711_DMA40_QOS(15) | BCM2711_DMA40_PANIC_QOS(15) | \
                                            BCM2711_DMA40_WAIT_FOR_WRITES | BCM2711_DMA40_DISDEBUG))

#define BCM2711_DMA40_INTEN                 RT_BIT(0)
#define BCM2711_DMA40_TDMODE                RT_BIT(1) /* 2D-Mode */
#define BCM2711_DMA40_WAIT_RESP             RT_BIT(2) /* Wait for AXI write to be acked */
#define BCM2711_DMA40_WAIT_RD_RESP          RT_BIT(3) /* Wait for AXI read to complete */
#define BCM2711_DMA40_PER_MAP(x)            ((x & 31) << 9) /* REQ source */
#define BCM2711_DMA40_S_DREQ                RT_BIT(14) /* Enable SREQ for source */
#define BCM2711_DMA40_D_DREQ                RT_BIT(15) /* Enable DREQ for destination */
#define BCM2711_DMA40_S_WAIT(x)             ((x & 0xff) << 16) /* Add DMA read-wait cycles */
#define BCM2711_DMA40_D_WAIT(x)             ((x & 0xff) << 24) /* Add DMA write-wait cycles */

#define BCM2711_DMA40_BURST_LEN(x)          (((x) & 15) << 8)
#define BCM2711_DMA40_INC                   RT_BIT(12)
#define BCM2711_DMA40_SIZE_32               (0 << 13)
#define BCM2711_DMA40_SIZE_64               (1 << 13)
#define BCM2711_DMA40_SIZE_128              (2 << 13)
#define BCM2711_DMA40_SIZE_256              (3 << 13)
#define BCM2711_DMA40_IGNORE                RT_BIT(15)
#define BCM2711_DMA40_STRIDE(x)             ((x) << 16) /* For 2D mode */

#define BCM2835_DMA_MAX_DMA_CHAN_SUPPORTED  14
#define BCM2835_DMA_CHAN_NAME_SIZE          8
#define BCM2835_DMA_BULK_MASK               RT_BIT(0)
#define BCM2711_DMA_MEMCPY_CHAN             14

#define MAX_DMA_LEN                         SIZE_GB
#define MAX_LITE_DMA_LEN                    (64 * SIZE_KB - 4)

struct bcm2835_dma_control_block
{
    rt_uint32_t info;
    rt_uint32_t src;
    rt_uint32_t dst;
    rt_uint32_t length;
    rt_uint32_t stride;
    rt_uint32_t next;
    rt_uint32_t padding[2];
};

struct bcm2711_dma40_control_block
{
    rt_uint32_t ti;
    rt_uint32_t src;
    rt_uint32_t srci;
    rt_uint32_t dst;
    rt_uint32_t dsti;
    rt_uint32_t len;
    rt_uint32_t next_cb;
    rt_uint32_t rsvd;
};

struct bcm2835_dma_soc_data
{
    rt_uint32_t chan_40bit_mask;
    rt_uint64_t dma_mask;
};

struct bcm2835_chan
{
    struct rt_dma_chan parent;

    int irq;
    void *base;

    rt_size_t size;
    rt_uint32_t dreq;
    rt_bool_t enabled;

    void *control_block;
    rt_ubase_t control_block_dma;
};

struct bcm2835_dma
{
    struct rt_dma_controller parent;
    const struct bcm2835_dma_soc_data *data;

    void *base;
    rt_uint32_t num_chans;
    struct bcm2835_chan *chans;

    rt_size_t max_frame_length;

    rt_bool_t is_2712;
    rt_bool_t is_40bit;
};
#define raw_to_bcm2835_dma(raw)         rt_container_of(raw, struct bcm2835_dma, parent)
#define raw_to_bcm2835_dma_chan(raw)    rt_container_of(raw, struct bcm2835_chan, parent)

rt_inline rt_ubase_t to_40bit_cbaddr(rt_ubase_t addr)
{
    return addr >> 5;
}

rt_inline rt_uint32_t to_bcm2711_ti(rt_uint32_t info)
{
    return ((info & BCM2835_DMA_INT_EN) ? BCM2711_DMA40_INTEN : 0) |
            ((info & BCM2835_DMA_WAIT_RESP) ? BCM2711_DMA40_WAIT_RESP : 0) |
            ((info & BCM2835_DMA_S_DREQ) ?
                (BCM2711_DMA40_S_DREQ | BCM2711_DMA40_WAIT_RD_RESP) : 0) |
            ((info & BCM2835_DMA_D_DREQ) ? BCM2711_DMA40_D_DREQ : 0) |
            BCM2711_DMA40_PER_MAP((info >> 16) & 0x1f);
}

rt_inline rt_uint32_t to_bcm2711_srci(rt_uint32_t info)
{
    return ((info & BCM2835_DMA_S_INC) ? BCM2711_DMA40_INC : 0) |
            ((info & BCM2835_DMA_S_WIDTH) ? BCM2711_DMA40_SIZE_128 : 0) |
            BCM2711_DMA40_BURST_LEN(BCM2835_DMA_GET_BURST_LENGTH(info));
}

rt_inline rt_uint32_t to_bcm2711_dsti(rt_uint32_t info)
{
    return ((info & BCM2835_DMA_D_INC) ? BCM2711_DMA40_INC : 0) |
            ((info & BCM2835_DMA_D_WIDTH) ? BCM2711_DMA40_SIZE_128 : 0) |
            BCM2711_DMA40_BURST_LEN(BCM2835_DMA_GET_BURST_LENGTH(info));
}

rt_inline rt_size_t bcm2835_dma_frames_for_length(rt_size_t len, rt_size_t max_len)
{
    return RT_DIV_ROUND_UP(len, max_len);
}

static rt_err_t bcm2835_dma_fill_prep(struct bcm2835_chan *chan, enum rt_dma_transfer_direction dir,
        rt_bool_t cyclic, rt_uint32_t info, rt_uint32_t finalextrainfo, rt_size_t frames,
        rt_ubase_t src, rt_ubase_t dst, rt_size_t buf_len, rt_size_t period_len)
{
    struct bcm2835_dma *dma = raw_to_bcm2835_dma(chan->parent.ctrl);

    if (frames > 1)
    {
        /*
         * Should create dma buffer and fill the CB list if enable,
         * This demand is rare or even non-existent on RT-thread.
         */
        return -RT_ENOSYS;
    }
    info |= finalextrainfo;

    if (dma->is_40bit)
    {
        struct bcm2711_dma40_control_block *cb = chan->control_block;

        cb->ti = to_bcm2711_ti(info);
        cb->src = rt_lower_32_bits(src);
        cb->srci = rt_upper_32_bits(src) | to_bcm2711_srci(info);
        cb->dst = rt_lower_32_bits(dst);
        cb->dsti = rt_upper_32_bits(dst) | to_bcm2711_dsti(info);
        cb->len = buf_len;
        cb->next_cb = 0;
    }
    else
    {
        struct bcm2835_dma_control_block *cb = chan->control_block;

        cb->info = info;
        cb->src = src;
        cb->dst = dst;
        cb->length = buf_len;

        if (dma->is_2712)
        {
            cb->stride = (rt_upper_32_bits(dst) << 8) | rt_upper_32_bits(src);
        }
        else
        {
            cb->stride = 0;
        }

        cb->next = 0;
    }

    return RT_EOK;
}

static struct rt_dma_chan *bcm2835_dma_request_chan(struct rt_dma_controller *ctrl,
        struct rt_device *slave, void *fw_data)
{
    rt_size_t size;
    struct bcm2835_chan *chan = RT_NULL;
    struct bcm2835_dma *dma = raw_to_bcm2835_dma(ctrl);
    struct rt_ofw_cell_args *args = fw_data;

    for (int i = 0; i < dma->num_chans; ++i)
    {
        if (!dma->chans[i].enabled)
        {
            chan = &dma->chans[i];
            break;
        }
    }

    if (!chan)
    {
        return rt_err_ptr(-RT_EBUSY);
    }

    if (dma->is_40bit)
    {
        size = sizeof(struct bcm2711_dma40_control_block);
    }
    else
    {
        size = sizeof(struct bcm2835_dma_control_block);
    }

    chan->control_block = rt_dma_alloc_coherent(slave, size, &chan->control_block_dma);

    if (!chan->control_block)
    {
        return rt_err_ptr(-RT_ENOMEM);
    }

    chan->dreq = args ? args->args[0] : 0;
    chan->enabled = RT_TRUE;

    return &chan->parent;
}

static rt_err_t bcm2835_dma_release_chan(struct rt_dma_chan *chan)
{
    rt_size_t size;
    struct bcm2835_chan *bcm_chan = rt_container_of(chan, struct bcm2835_chan, parent);
    struct bcm2835_dma *dma = raw_to_bcm2835_dma(chan->ctrl);

    bcm_chan->enabled = RT_FALSE;

    if (dma->is_40bit)
    {
        size = sizeof(struct bcm2711_dma40_control_block);
    }
    else
    {
        size = sizeof(struct bcm2835_dma_control_block);
    }

    rt_dma_free_coherent(chan->slave, size,
            bcm_chan->control_block, bcm_chan->control_block_dma);

    return RT_EOK;
}

static rt_err_t bcm2835_dma_start(struct rt_dma_chan *chan)
{
    void *base;
    rt_ubase_t cb_dma;
    struct bcm2835_chan *bcm_chan = raw_to_bcm2835_dma_chan(chan);
    struct bcm2835_dma *dma = raw_to_bcm2835_dma(chan->ctrl);

    base = bcm_chan->base;
    cb_dma = bcm_chan->control_block_dma;

    if (dma->is_40bit)
    {
        HWREG32(base + BCM2711_DMA40_CB) = to_40bit_cbaddr(cb_dma);
        HWREG32(base + BCM2711_DMA40_CS) =
                BCM2711_DMA40_ACTIVE | BCM2711_DMA40_PROT | BCM2711_DMA40_CS_FLAGS(bcm_chan->dreq);
    }
    else
    {
        HWREG32(base + BCM2835_DMA_CS) = RT_BIT(31);
        HWREG32(base + BCM2835_DMA_ADDR) = dma->is_2712 ? to_40bit_cbaddr(cb_dma) : cb_dma;
        HWREG32(base + BCM2835_DMA_CS) = BCM2835_DMA_ACTIVE | BCM2835_DMA_CS_FLAGS(bcm_chan->dreq);
    }

    return RT_EOK;
}

static rt_err_t bcm2835_dma_stop(struct rt_dma_chan *chan)
{
    void *base;
    rt_uint32_t timeout = 100;
    struct bcm2835_chan *bcm_chan = raw_to_bcm2835_dma_chan(chan);
    struct bcm2835_dma *dma = raw_to_bcm2835_dma(chan->ctrl);

    base = bcm_chan->base;

    if (dma->is_40bit)
    {
        if (!HWREG32(base + BCM2711_DMA40_CB))
        {
            return RT_EOK;
        }

        /* Pause the current DMA */
        HWREG32(base + BCM2711_DMA40_CS) = HWREG32(base + BCM2711_DMA40_CS) & ~BCM2711_DMA40_ACTIVE;

        /* wait for outstanding transactions to complete */
        while ((HWREG32(base + BCM2711_DMA40_CS) & BCM2711_DMA40_TRANSACTIONS) && --timeout)
        {
            rt_hw_cpu_relax();
        }

        /* Peripheral might be stuck and fail to complete */
        if (!timeout)
        {
            LOG_E("Failed to complete pause on dma[%d] CS:%08x", bcm_chan - dma->chans,
                    HWREG32(base + BCM2711_DMA40_CS));
        }

        /* Set CS back to default state */
        HWREG32(base + BCM2711_DMA40_CS) = BCM2711_DMA40_PROT;

        /* Reset the DMA */
        HWREG32(base + BCM2711_DMA40_DEBUG) |= BCM2711_DMA40_DEBUG_RESET;
    }
    else
    {
        if (!HWREG32(base + BCM2835_DMA_ADDR))
        {
            return RT_EOK;
        }

        /* We need to clear the next DMA block pending */
        HWREG32(base + BCM2835_DMA_NEXTCB) = 0;

        /* Abort the DMA, which needs to be enabled to complete */
        HWREG32(base + BCM2835_DMA_CS) =
                HWREG32(base + BCM2835_DMA_CS) | BCM2835_DMA_ABORT | BCM2835_DMA_ACTIVE;

        /* Wait for DMA to be aborted */
        while ((HWREG32(base + BCM2835_DMA_CS) & BCM2835_DMA_ABORT) && --timeout)
        {
            rt_hw_cpu_relax();
        }

        /* Write 0 to the active bit - Pause the DMA */
        HWREG32(base + BCM2835_DMA_CS) =
                HWREG32(base + BCM2835_DMA_CS) & ~BCM2835_DMA_ACTIVE;

        if (!timeout && !(HWREG32(base + BCM2835_DMA_TI) &
           (BCM2835_DMA_S_DREQ | BCM2835_DMA_D_DREQ)))
        {
            LOG_E("Failed to complete pause on dma[%d] CS:%08x", bcm_chan - dma->chans,
                HWREG32(base + BCM2835_DMA_CS));
        }

        /* Set CS back to default state and reset the DMA */
        HWREG32(base + BCM2835_DMA_CS) = BCM2835_DMA_RESET;
    }

    return RT_EOK;
}

static rt_err_t bcm2835_dma_config(struct rt_dma_chan *chan,
        struct rt_dma_slave_config *conf)
{
    return RT_EOK;
}

static rt_err_t bcm2835_dma_prep_memcpy(struct rt_dma_chan *chan,
        rt_ubase_t dma_addr_src, rt_ubase_t dma_addr_dst, rt_size_t len)
{
    rt_size_t frames;
    rt_uint32_t info, extra;
    struct bcm2835_chan *bcm_chan = raw_to_bcm2835_dma_chan(chan);
    struct bcm2835_dma *dma = raw_to_bcm2835_dma(chan->ctrl);

    info = BCM2835_DMA_D_INC | BCM2835_DMA_S_INC |
            WAIT_RESP(bcm_chan->dreq) | WIDE_SOURCE(bcm_chan->dreq) |
            WIDE_DEST(bcm_chan->dreq) | BURST_LENGTH(bcm_chan->dreq);
    extra = BCM2835_DMA_INT_EN;
    frames = bcm2835_dma_frames_for_length(len, dma->max_frame_length);

    bcm_chan->size = len;

    return bcm2835_dma_fill_prep(bcm_chan, RT_DMA_MEM_TO_MEM, RT_FALSE,
            info, extra, frames, dma_addr_src, dma_addr_dst, len, 0);
}

static rt_err_t bcm2835_dma_prep_cyclic(struct rt_dma_chan *chan,
        rt_ubase_t dma_buf_addr, rt_size_t buf_len, rt_size_t period_len,
        enum rt_dma_transfer_direction dir)
{
    rt_size_t frames;
    rt_ubase_t src, dst;
    rt_uint32_t info, extra;
    struct bcm2835_chan *bcm_chan = raw_to_bcm2835_dma_chan(chan);
    struct bcm2835_dma *dma = raw_to_bcm2835_dma(chan->ctrl);

    info = WAIT_RESP(bcm_chan->dreq) | WIDE_SOURCE(bcm_chan->dreq) |
            WIDE_DEST(bcm_chan->dreq) | BURST_LENGTH(bcm_chan->dreq);
    extra = 0;

    if (bcm_chan->dreq)
    {
        info |= BCM2835_DMA_PER_MAP(bcm_chan->dreq);
    }

    if (dir == RT_DMA_DEV_TO_MEM)
    {
        if (chan->conf.src_addr_width != RT_DMA_SLAVE_BUSWIDTH_4_BYTES)
        {
            return -RT_EINVAL;
        }

        src = chan->conf.src_addr;
        dst = dma_buf_addr;
        info |= BCM2835_DMA_S_DREQ | BCM2835_DMA_D_INC;
    }
    else
    {
        if (chan->conf.dst_addr_width != RT_DMA_SLAVE_BUSWIDTH_4_BYTES)
        {
            return -RT_EINVAL;
        }

        dst = chan->conf.dst_addr;
        src = dma_buf_addr;
        info |= BCM2835_DMA_D_DREQ | BCM2835_DMA_S_INC;
    }

    frames = RT_DIV_ROUND_UP(buf_len, period_len) *
            bcm2835_dma_frames_for_length(period_len, dma->max_frame_length);

    bcm_chan->size = buf_len;

    return bcm2835_dma_fill_prep(bcm_chan, dir, RT_TRUE,
            info, extra, frames, src, dst, buf_len, period_len);
}

static rt_err_t bcm2835_dma_prep_single(struct rt_dma_chan *chan,
        rt_ubase_t dma_buf_addr, rt_size_t buf_len,
        enum rt_dma_transfer_direction dir)
{
    rt_size_t frames;
    rt_ubase_t src, dst;
    rt_uint32_t info, extra;
    struct bcm2835_chan *bcm_chan = raw_to_bcm2835_dma_chan(chan);
    struct bcm2835_dma *dma = raw_to_bcm2835_dma(chan->ctrl);

    info = WAIT_RESP(bcm_chan->dreq) | WIDE_SOURCE(bcm_chan->dreq) |
            WIDE_DEST(bcm_chan->dreq) | BURST_LENGTH(bcm_chan->dreq);
    extra = BCM2835_DMA_INT_EN;

    if (bcm_chan->dreq)
    {
        info |= BCM2835_DMA_PER_MAP(bcm_chan->dreq);
    }

    if (dir == RT_DMA_DEV_TO_MEM)
    {
        if (chan->conf.src_addr_width != RT_DMA_SLAVE_BUSWIDTH_4_BYTES)
        {
            return -RT_EINVAL;
        }

        dst = dma_buf_addr;
        src = chan->conf.src_addr;
        info |= BCM2835_DMA_S_DREQ | BCM2835_DMA_D_INC;
    }
    else
    {
        if (chan->conf.dst_addr_width != RT_DMA_SLAVE_BUSWIDTH_4_BYTES)
        {
            return -RT_EINVAL;
        }

        dst = chan->conf.dst_addr;
        src = dma_buf_addr;
        info |= BCM2835_DMA_D_DREQ | BCM2835_DMA_S_INC;
    }

    frames = bcm2835_dma_frames_for_length(buf_len, dma->max_frame_length);
    bcm_chan->size = buf_len;

    return bcm2835_dma_fill_prep(bcm_chan, dir, RT_FALSE,
            info, extra, frames, src, dst, buf_len, 0);
}

static const struct rt_dma_controller_ops bcm2835_dma_ops =
{
    .request_chan = bcm2835_dma_request_chan,
    .release_chan = bcm2835_dma_release_chan,
    .start = bcm2835_dma_start,
    .stop = bcm2835_dma_stop,
    .config = bcm2835_dma_config,
    .prep_memcpy = bcm2835_dma_prep_memcpy,
    .prep_cyclic = bcm2835_dma_prep_cyclic,
    .prep_single = bcm2835_dma_prep_single,
};

static void bcm2835_dma_isr(int irq, void *param)
{
    struct bcm2835_chan *chan = param;
    struct bcm2835_dma *dma = raw_to_bcm2835_dma(chan->parent.ctrl);

    /* Check for share IRQ */
    if (!(HWREG32(chan->base + BCM2835_DMA_CS) & BCM2835_DMA_INT))
    {
        return;
    }

    if (dma->is_40bit)
    {
        HWREG32(chan->base + BCM2711_DMA40_CS) =
            BCM2835_DMA_INT | BCM2711_DMA40_ACTIVE | BCM2711_DMA40_PROT |
            BCM2711_DMA40_CS_FLAGS(chan->dreq);
    }
    else
    {
        HWREG32(chan->base + BCM2835_DMA_CS) =
            BCM2835_DMA_INT | BCM2835_DMA_ACTIVE |
            BCM2835_DMA_CS_FLAGS(chan->dreq);
    }

    rt_dma_chan_done(&chan->parent, chan->size);
}

static rt_err_t bcm2835_dma_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint64_t addr, size;
    rt_uint32_t channel_mask = ~0U;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_dma *dma = rt_calloc(1, sizeof(*dma));

    if (!dma)
    {
        return -RT_ENOMEM;
    }
    dma->data = pdev->id->data;

    if (dma->data->dma_mask == RT_DMA_ADDR_MASK(40))
    {
        dma->is_2712 = RT_TRUE;
    }

    rt_ofw_prop_read_u32(dev->ofw_node, "brcm,dma-channel-mask", &channel_mask);
    dma->is_40bit = !!(dma->data->chan_40bit_mask & channel_mask);

    if ((err = rt_dm_dev_get_address(dev, 0, &addr, &size)))
    {
        goto _fail;
    }

    if (!(dma->base = rt_ioremap((void *)addr, size)))
    {
        err = -RT_EIO;
        goto _fail;
    }

    if (HWREG32(dma->base + BCM2835_DMA_DEBUG) & BCM2835_DMA_DEBUG_LITE)
    {
        dma->max_frame_length = MAX_LITE_DMA_LEN;
    }
    else
    {
        dma->max_frame_length = MAX_DMA_LEN;
    }

    dma->num_chans = size / BCM2835_DMA_CHAN_SIZE;

    dma->chans = rt_calloc(dma->num_chans, sizeof(dma->chans[0]));

    if (!dma->chans)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    for (int i = 0; i < dma->num_chans; ++i)
    {
        struct bcm2835_chan *chan = &dma->chans[i];

        chan->irq = rt_dm_dev_get_irq(dev, i);

        if (chan->irq < 0)
        {
            err = chan->irq;
            goto _fail;
        }
    }

    dma->parent.dev = dev;
    dma->parent.ops = &bcm2835_dma_ops;
    rt_dma_controller_add_direction(&dma->parent, RT_DMA_MEM_TO_MEM);
    rt_dma_controller_add_direction(&dma->parent, RT_DMA_MEM_TO_DEV);
    rt_dma_controller_add_direction(&dma->parent, RT_DMA_DEV_TO_MEM);
    rt_dma_controller_set_addr_mask(&dma->parent, dma->data->dma_mask);

    if ((err = rt_dma_controller_register(&dma->parent)))
    {
        goto _fail;
    }

    for (int i = 0; i < dma->num_chans; ++i)
    {
        char isr_name[RT_NAME_MAX];
        struct bcm2835_chan *chan = &dma->chans[i];

        chan->base = dma->base + i * BCM2835_DMA_CHAN_SIZE;

        rt_sprintf(isr_name, "dma-%u", i);

        rt_hw_interrupt_install(chan->irq, bcm2835_dma_isr, chan, isr_name);
        rt_hw_interrupt_umask(chan->irq);
    }

    dev->user_data = dma;

    return err;

_fail:
    if (dma->chans)
    {
        rt_free(dma->chans);
    }

    if (dma->base)
    {
        rt_iounmap(dma->base);
    }

    rt_free(dma);

    return err;
}

static rt_err_t bcm2835_dma_remove(struct rt_platform_device *pdev)
{
    struct bcm2835_dma *dma = pdev->parent.user_data;

    rt_dma_controller_unregister(&dma->parent);

    for (int i = 0; i < dma->num_chans; ++i)
    {
        struct bcm2835_chan *chan = &dma->chans[i];

        rt_hw_interrupt_mask(chan->irq);
        rt_pic_detach_irq(chan->irq, chan);
    }

    rt_free(dma->chans);
    rt_iounmap(dma->base);

    rt_free(dma);

    return RT_EOK;
}

static const struct bcm2835_dma_soc_data bcm2835_dma_data =
{
    .chan_40bit_mask = 0,
    .dma_mask = RT_DMA_ADDR_MASK(32),
};

static const struct bcm2835_dma_soc_data bcm2711_dma_data =
{
    .chan_40bit_mask = RT_BIT(11) | RT_BIT(12) | RT_BIT(13) | RT_BIT(14),
    .dma_mask = RT_DMA_ADDR_MASK(36),
};

static const struct bcm2835_dma_soc_data bcm2712_dma_data =
{
    .chan_40bit_mask = RT_BIT(6) | RT_BIT(7) | RT_BIT(8) | RT_BIT(9) | RT_BIT(10) | RT_BIT(11),
    .dma_mask = RT_DMA_ADDR_MASK(40),
};

static const struct rt_ofw_node_id bcm2835_dma_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-dma", .data = &bcm2835_dma_data },
    { .compatible = "brcm,bcm2711-dma", .data = &bcm2711_dma_data },
    { .compatible = "brcm,bcm2712-dma", .data = &bcm2712_dma_data },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_dma_driver =
{
    .name = "dma-bcm2835",
    .ids = bcm2835_dma_ofw_ids,

    .probe = bcm2835_dma_probe,
    .remove = bcm2835_dma_remove,
};

static int bcm2835_dma_drv_register(void)
{
    rt_platform_driver_register(&bcm2835_dma_driver);

    return 0;
}
INIT_SUBSYS_EXPORT(bcm2835_dma_drv_register);
