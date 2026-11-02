/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-24     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "audio.bcm2835-i2s"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* I2S registers */
#define BCM2835_I2S_CS_A_REG            0x00
#define BCM2835_I2S_FIFO_A_REG          0x04
#define BCM2835_I2S_MODE_A_REG          0x08
#define BCM2835_I2S_RXC_A_REG           0x0c
#define BCM2835_I2S_TXC_A_REG           0x10
#define BCM2835_I2S_DREQ_A_REG          0x14
#define BCM2835_I2S_INTEN_A_REG         0x18
#define BCM2835_I2S_INTSTC_A_REG        0x1c
#define BCM2835_I2S_GRAY_REG            0x20

/* I2S register settings */
#define BCM2835_I2S_STBY                RT_BIT(25)
#define BCM2835_I2S_SYNC                RT_BIT(24)
#define BCM2835_I2S_RXSEX               RT_BIT(23)
#define BCM2835_I2S_RXF                 RT_BIT(22)
#define BCM2835_I2S_TXE                 RT_BIT(21)
#define BCM2835_I2S_RXD                 RT_BIT(20)
#define BCM2835_I2S_TXD                 RT_BIT(19)
#define BCM2835_I2S_RXR                 RT_BIT(18)
#define BCM2835_I2S_TXW                 RT_BIT(17)
#define BCM2835_I2S_CS_RXERR            RT_BIT(16)
#define BCM2835_I2S_CS_TXERR            RT_BIT(15)
#define BCM2835_I2S_RXSYNC              RT_BIT(14)
#define BCM2835_I2S_TXSYNC              RT_BIT(13)
#define BCM2835_I2S_DMAEN               RT_BIT(9)
#define BCM2835_I2S_RXTHR(v)            ((v) << 7)
#define BCM2835_I2S_TXTHR(v)            ((v) << 5)
#define BCM2835_I2S_RXCLR               RT_BIT(4)
#define BCM2835_I2S_TXCLR               RT_BIT(3)
#define BCM2835_I2S_TXON                RT_BIT(2)
#define BCM2835_I2S_RXON                RT_BIT(1)
#define BCM2835_I2S_EN                  (1)

#define BCM2835_I2S_CLKDIS              RT_BIT(28)
#define BCM2835_I2S_PDMN                RT_BIT(27)
#define BCM2835_I2S_PDME                RT_BIT(26)
#define BCM2835_I2S_FRXP                RT_BIT(25)
#define BCM2835_I2S_FTXP                RT_BIT(24)
#define BCM2835_I2S_CLKM                RT_BIT(23)
#define BCM2835_I2S_CLKI                RT_BIT(22)
#define BCM2835_I2S_FSM                 RT_BIT(21)
#define BCM2835_I2S_FSI                 RT_BIT(20)
#define BCM2835_I2S_FLEN(v)             ((v) << 10)
#define BCM2835_I2S_FSLEN(v)            (v)

#define BCM2835_I2S_CHWEX               RT_BIT(15)
#define BCM2835_I2S_CHEN                RT_BIT(14)
#define BCM2835_I2S_CHPOS(v)            ((v) << 4)
#define BCM2835_I2S_CHWID(v)            (v)
#define BCM2835_I2S_CH1(v)              ((v) << 16)
#define BCM2835_I2S_CH2(v)              (v)
#define BCM2835_I2S_CH1_POS(v)          BCM2835_I2S_CH1(BCM2835_I2S_CHPOS(v))
#define BCM2835_I2S_CH2_POS(v)          BCM2835_I2S_CH2(BCM2835_I2S_CHPOS(v))

#define BCM2835_I2S_TX_PANIC(v)         ((v) << 24)
#define BCM2835_I2S_RX_PANIC(v)         ((v) << 16)
#define BCM2835_I2S_TX(v)               ((v) << 8)
#define BCM2835_I2S_RX(v)               (v)

#define BCM2835_I2S_INT_RXERR           RT_BIT(3)
#define BCM2835_I2S_INT_TXERR           RT_BIT(2)
#define BCM2835_I2S_INT_RXR             RT_BIT(1)
#define BCM2835_I2S_INT_TXW             RT_BIT(0)

#define BCM2835_I2S_MAX_FRAME_LENGTH    1024        /* Frame length register is 10 bit, maximum length 1024 */
#define BCM2835_I2S_MAX_FIFO_LENGTH     (64 * 32)   /* 64 * 32 bit TX/RX FIFO */

struct bcm2835_i2s
{
    struct rt_audio_device parent;
    struct rt_audio_configure audio_config;
    struct rt_device *dev;

    void *regs;
    struct rt_clk *clk;
    rt_bool_t clk_prepared;
    rt_bool_t hifi_hat;

    void *playback_buf;
    void *capture_buf;
    rt_ubase_t playback_dma;
    rt_ubase_t capture_dma;

    rt_ubase_t fifo_dma;
    struct rt_dma_chan *dma_rx;
    struct rt_dma_chan *dma_tx;
};

#define raw_to_bcm2835_i2s(raw) rt_container_of(raw, struct bcm2835_i2s, parent)

static void bcm2835_i2s_start_clock(struct bcm2835_i2s *i2s)
{
    if (i2s->clk_prepared)
    {
        return;
    }

    rt_clk_prepare_enable(i2s->clk);
    i2s->clk_prepared = RT_TRUE;
}

static void bcm2835_i2s_stop_clock(struct bcm2835_i2s *i2s)
{
    if (i2s->clk_prepared)
    {
        rt_clk_disable_unprepare(i2s->clk);
    }

    i2s->clk_prepared = RT_FALSE;
}

static void bcm2835_i2s_clear_fifos(struct bcm2835_i2s *i2s, rt_bool_t tx, rt_bool_t rx)
{
    int timeout = 1000;
    rt_bool_t clk_was_prepared;
    rt_uint32_t syncval, csreg, i2s_active_state, off, clr;

    off = (tx ? BCM2835_I2S_TXON : 0) | (rx ? BCM2835_I2S_RXON : 0);
    clr = (tx ? BCM2835_I2S_TXCLR : 0) | (rx ? BCM2835_I2S_RXCLR : 0);

    /* Backup the current state */
    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    i2s_active_state = csreg & (BCM2835_I2S_RXON | BCM2835_I2S_TXON);

    /* Start clock if not running */
    if (!(clk_was_prepared = i2s->clk_prepared))
    {
        bcm2835_i2s_start_clock(i2s);
    }

    /* Stop I2S module */
    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~off;
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg;

    /* Clear the FIFOs, Requires at least 2 PCM clock cycles to take effect */
    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~clr;
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg | clr;

    /* Wait for 2 PCM clock cycles */

    /* Toggle the SYNC flag. After 2 PCM clock cycles it can be read back */
    syncval = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) & BCM2835_I2S_SYNC;
    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~BCM2835_I2S_SYNC;
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg | ~syncval;

    /* Wait for the SYNC flag changing it's state */
    while (--timeout)
    {
        if ((HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) & BCM2835_I2S_SYNC) != syncval)
        {
            break;
        }
    }

    if (!timeout)
    {
        LOG_E("%s: sync error", rt_dm_dev_get_name(&i2s->parent.parent));
    }

    /* Stop clock if it was not running before */
    if (!clk_was_prepared)
    {
        bcm2835_i2s_stop_clock(i2s);
    }

    /* Restore I2S state */
    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~(BCM2835_I2S_RXON | BCM2835_I2S_TXON);
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg | i2s_active_state;
}

static rt_err_t bcm2835_i2s_audio_getcaps(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    struct bcm2835_i2s *i2s = raw_to_bcm2835_i2s(audio);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY:
        i2s->hifi_hat = caps->udata.value > 0;

        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    case AUDIO_TYPE_OUTPUT:
    case AUDIO_TYPE_INPUT:
        switch(caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.channels = i2s->audio_config.channels;
            caps->udata.config.samplebits = i2s->audio_config.samplebits;
            caps->udata.config.samplerate = i2s->audio_config.samplerate;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = i2s->audio_config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = i2s->audio_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = i2s->audio_config.samplebits;
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    default:
        return -RT_ENOSYS;
    }

    return RT_EOK;
}

static rt_err_t bcm2835_i2s_audio_configure(struct rt_audio_device *audio,
        struct rt_audio_caps *caps)
{
    rt_uint32_t csreg, value, frame_length;
    struct rt_audio_configure audio_config;
    struct bcm2835_i2s *i2s = raw_to_bcm2835_i2s(audio);

    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);

    if (csreg & (BCM2835_I2S_TXON | BCM2835_I2S_RXON))
    {
        return -RT_EBUSY;
    }

    rt_memcpy(&audio_config, &i2s->audio_config, sizeof(audio_config));

    switch (caps->main_type)
    {
    case AUDIO_TYPE_OUTPUT:
    case AUDIO_TYPE_INPUT:
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            audio_config.channels = caps->udata.config.channels;
            audio_config.samplebits = caps->udata.config.samplebits;
            audio_config.samplerate = caps->udata.config.samplerate;
            break;

        case AUDIO_DSP_SAMPLERATE:
            audio_config.samplerate = caps->udata.config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            audio_config.channels = caps->udata.config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            audio_config.samplebits = caps->udata.config.samplebits;
            break;

        default:
            return -RT_ENOSYS;
        }
        break;

    default:
        return -RT_ENOSYS;
    }

    if (audio_config.channels > 2)
    {
        return -RT_EINVAL;
    }

    if (audio_config.samplerate < 8000 || audio_config.samplerate > 384000)
    {
        return -RT_EINVAL;
    }

    if (audio_config.samplebits != 16 &&
        audio_config.samplebits != 24 &&
        audio_config.samplebits != 32)
    {
        return -RT_EINVAL;
    }

    rt_memcpy(&i2s->audio_config, &audio_config, sizeof(audio_config));

    if (i2s->hifi_hat)
    {
        /* Clock setting */
        bcm2835_i2s_stop_clock(i2s);

        rt_clk_set_rate(i2s->clk, audio_config.samplerate);

        bcm2835_i2s_start_clock(i2s);
    }

    /* Setup the frame format */
    value = BCM2835_I2S_CHEN;

    if (audio_config.samplebits >= 24)
    {
        value |= BCM2835_I2S_CHWEX;
    }

    value |= BCM2835_I2S_CHWID((audio_config.samplebits - 8) & 0xf);
    /* CH2 format is the same as for CH1 */
    value = BCM2835_I2S_CH1(value) | BCM2835_I2S_CH2(value);

    HWREG32(i2s->regs + BCM2835_I2S_RXC_A_REG) = value |
        BCM2835_I2S_CH1_POS(1) | BCM2835_I2S_CH2_POS(33);
    HWREG32(i2s->regs + BCM2835_I2S_TXC_A_REG) = value |
        BCM2835_I2S_CH1_POS(1) | BCM2835_I2S_CH2_POS(33);

    /* Setup the I2S mode */
    value = 0;
    frame_length = audio_config.channels * audio_config.samplebits;

    if (audio_config.samplebits <= 16)
    {
        /* Use frame packed mode (2 channels per 32 bit word) */
        value |= BCM2835_I2S_FTXP | BCM2835_I2S_FRXP;
    }

    value |= BCM2835_I2S_FLEN(frame_length - 1);
    value |= BCM2835_I2S_FSLEN(frame_length / 2);

    if (!i2s->hifi_hat)
    {
        value |= BCM2835_I2S_CLKM | BCM2835_I2S_CLKI | BCM2835_I2S_FSM;
    }

    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = value;

    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~(BCM2835_I2S_RXTHR(1) | BCM2835_I2S_TXTHR(1) | BCM2835_I2S_DMAEN);
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg | 0xffffffff;

    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~(BCM2835_I2S_TX_PANIC(0x10) | BCM2835_I2S_RX_PANIC(0x30) |
            BCM2835_I2S_TX(0x30) | BCM2835_I2S_RX(0x20));
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg | 0xffffffff;

    bcm2835_i2s_clear_fifos(i2s, RT_TRUE, RT_TRUE);

    return RT_EOK;
}

static rt_err_t bcm2835_i2s_audio_init(struct rt_audio_device *audio)
{
    rt_uint32_t csreg;
    struct bcm2835_i2s *i2s = raw_to_bcm2835_i2s(audio);

    i2s->audio_config.samplerate = 8000;    /* 8000 ~ 384000 */
    i2s->audio_config.samplebits = 16;      /* 16/24/32 */
    i2s->audio_config.channels = 2;

    bcm2835_i2s_stop_clock(i2s);

    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~BCM2835_I2S_EN;
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg | BCM2835_I2S_EN;

    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~BCM2835_I2S_STBY;
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg | BCM2835_I2S_STBY;

    return RT_EOK;
}

static rt_err_t bcm2835_i2s_audio_start(struct rt_audio_device *audio, int stream)
{
    rt_uint32_t csreg, mask;
    struct bcm2835_i2s *i2s = raw_to_bcm2835_i2s(audio);

    bcm2835_i2s_start_clock(i2s);

    if (stream == AUDIO_STREAM_RECORD)
    {
        mask = BCM2835_I2S_RXON;
    }
    else if (stream == AUDIO_STREAM_REPLAY)
    {
        mask = BCM2835_I2S_TXON;
    }
    else
    {
        return -RT_EINVAL;
    }

    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~mask;
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg | mask;

    return RT_EOK;
}

static rt_err_t bcm2835_i2s_audio_stop(struct rt_audio_device *audio, int stream)
{
    rt_uint32_t csreg, mask;
    struct bcm2835_i2s *i2s = raw_to_bcm2835_i2s(audio);

    if (stream == AUDIO_STREAM_RECORD)
    {
        mask = BCM2835_I2S_RXON;
    }
    else if (stream == AUDIO_STREAM_REPLAY)
    {
        mask = BCM2835_I2S_TXON;
    }
    else
    {
        return -RT_EINVAL;
    }

    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~mask;
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg;

    bcm2835_i2s_stop_clock(i2s);

    return RT_EOK;
}

static rt_ssize_t bcm2835_i2s_audio_transmit(struct rt_audio_device *audio,
        const void *write_buf, void *read_buf, rt_size_t size)
{
    rt_err_t err;
    struct rt_dma_chan *chan;
    struct rt_dma_slave_config config;
    struct rt_dma_slave_transfer transfer;
    struct bcm2835_i2s *i2s = raw_to_bcm2835_i2s(audio);

    rt_memset(&config, 0, sizeof(config));

    if (write_buf)
    {
        config.dst_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
        config.dst_maxburst = 2;

        config.direction = RT_DMA_MEM_TO_DEV;
        config.src_addr = (write_buf - i2s->playback_buf) + i2s->playback_dma;
        config.dst_addr = i2s->fifo_dma;

        chan = i2s->dma_tx;
    }
    else if (read_buf)
    {
        config.src_addr_width = RT_DMA_SLAVE_BUSWIDTH_4_BYTES;
        config.src_maxburst = 2;

        config.direction = RT_DMA_DEV_TO_MEM;
        config.src_addr = i2s->fifo_dma;
        config.dst_addr = i2s->capture_dma;

        chan = i2s->dma_rx;
    }
    else
    {
        return -RT_EINVAL;
    }

    if ((err = rt_dma_chan_config(chan, &config)))
    {
        LOG_E("Config DMA error = %s", rt_strerror(err));
        return err;
    }

    rt_memset(&transfer, 0, sizeof(transfer));
    transfer.buffer_len = size;
    transfer.src_addr = config.src_addr;
    transfer.dst_addr = config.dst_addr;
    transfer.period_len = BCM2835_I2S_MAX_FRAME_LENGTH;

    if (chan == i2s->dma_rx)
    {
        transfer.buffer = read_buf;
    }

    if ((err = rt_dma_prep_cyclic(chan, &transfer)))
    {
        LOG_E("Prepare DMA error = %s", rt_strerror(err));
        return err;
    }

    if ((err = rt_dma_chan_start(chan)))
    {
        LOG_E("Start DMA error = %s", rt_strerror(err));
        return err;
    }

    return size;
}

static void bcm2835_i2s_audio_buffer_info(struct rt_audio_device *audio,
        struct rt_audio_buf_info *info)
{
    struct bcm2835_i2s *i2s = raw_to_bcm2835_i2s(audio);

    info->buffer      = i2s->playback_buf;
    info->total_size  = BCM2835_I2S_MAX_FIFO_LENGTH;
    info->block_size  = BCM2835_I2S_MAX_FRAME_LENGTH;
    info->block_count = BCM2835_I2S_MAX_FIFO_LENGTH / BCM2835_I2S_MAX_FRAME_LENGTH;
}

const static struct rt_audio_ops bcm2835_i2s_audio_ops =
{
    .getcaps = bcm2835_i2s_audio_getcaps,
    .configure = bcm2835_i2s_audio_configure,
    .init = bcm2835_i2s_audio_init,
    .start = bcm2835_i2s_audio_start,
    .stop = bcm2835_i2s_audio_stop,
    .transmit = bcm2835_i2s_audio_transmit,
    .buffer_info = bcm2835_i2s_audio_buffer_info,
};

static void bcm2835_i2s_dma_rx_done(struct rt_dma_chan *chan, rt_size_t size)
{
    void *buffer;
    struct bcm2835_i2s *i2s = chan->priv;

    buffer = chan->transfer.buffer;
    chan->transfer.buffer += size;

    rt_memcpy(buffer, i2s->capture_buf, size);
    rt_audio_rx_done(&i2s->parent, buffer, size);
}

static void bcm2835_i2s_dma_tx_done(struct rt_dma_chan *chan, rt_size_t size)
{
    struct bcm2835_i2s *i2s = chan->priv;

    rt_audio_tx_complete(&i2s->parent);
}

static void bcm2835_i2s_free(struct bcm2835_i2s *i2s)
{
    if (!rt_is_err_or_null(i2s->dma_rx))
    {
        rt_dma_chan_release(i2s->dma_rx);
    }

    if (!rt_is_err_or_null(i2s->dma_tx))
    {
        rt_dma_chan_release(i2s->dma_tx);
    }

    if (i2s->playback_buf)
    {
        rt_dma_free_coherent(i2s->dev, BCM2835_I2S_MAX_FIFO_LENGTH,
                i2s->playback_buf, i2s->playback_dma);
    }

    if (i2s->capture_buf)
    {
        rt_dma_free_coherent(i2s->dev, BCM2835_I2S_MAX_FIFO_LENGTH,
                i2s->capture_buf, i2s->capture_dma);
    }

    if (!rt_is_err_or_null(i2s->clk))
    {
        rt_clk_put(i2s->clk);
    }

    if (i2s->regs)
    {
        rt_iounmap(i2s->regs);
    }

    rt_free(i2s);
}

static rt_err_t bcm2835_i2s_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *dev_name;
    struct rt_device *dev = &pdev->parent;
    struct bcm2835_i2s *i2s = rt_calloc(1, sizeof(*i2s));

    if (!i2s)
    {
        return -RT_ENOMEM;
    }

    i2s->dev = dev;
    i2s->regs = rt_dm_dev_iomap(dev, 0);

    if (!i2s->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    i2s->playback_buf = rt_dma_alloc_coherent(dev,
            BCM2835_I2S_MAX_FIFO_LENGTH, &i2s->playback_dma);

    if (!i2s->playback_buf)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    i2s->capture_buf = rt_dma_alloc_coherent(dev,
            BCM2835_I2S_MAX_FIFO_LENGTH, &i2s->capture_dma);

    if (!i2s->capture_buf)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    i2s->clk = rt_clk_get_by_index(dev, 0);

    if (rt_is_err(i2s->clk))
    {
        err = rt_ptr_err(i2s->clk);
        goto _fail;
    }

    i2s->dma_rx = rt_dma_chan_request(dev, "rx");

    if (rt_is_err(i2s->dma_rx))
    {
        err = rt_ptr_err(i2s->clk);
        goto _fail;
    }

    i2s->dma_tx = rt_dma_chan_request(dev, "tx");

    if (rt_is_err(i2s->dma_tx))
    {
        err = rt_ptr_err(i2s->clk);
        goto _fail;
    }

    i2s->dma_rx->callback = bcm2835_i2s_dma_rx_done;
    i2s->dma_tx->callback = bcm2835_i2s_dma_tx_done;

    i2s->dma_rx->priv = i2s;
    i2s->dma_tx->priv = i2s;

    i2s->fifo_dma = (rt_ubase_t)rt_kmem_v2p(i2s->regs) + BCM2835_I2S_FIFO_A_REG;

    rt_dm_dev_set_name_auto(&i2s->parent.parent, "sound");
    dev_name = rt_dm_dev_get_name(&i2s->parent.parent);

    i2s->parent.ops = (struct rt_audio_ops *)&bcm2835_i2s_audio_ops;
    if ((err = rt_audio_register(&i2s->parent, dev_name, RT_DEVICE_FLAG_RDWR, i2s)))
    {
        goto _fail;
    }

    dev->user_data = i2s;

    return RT_EOK;

_fail:
    bcm2835_i2s_free(i2s);

    return err;
}

static rt_err_t bcm2835_i2s_remove(struct rt_platform_device *pdev)
{
    rt_uint32_t csreg;
    struct bcm2835_i2s *i2s = pdev->parent.user_data;

    csreg = HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG);
    csreg &= ~BCM2835_I2S_EN;
    HWREG32(i2s->regs + BCM2835_I2S_CS_A_REG) = csreg;

    bcm2835_i2s_stop_clock(i2s);

    rt_device_unregister(&i2s->parent.parent);

    bcm2835_i2s_free(i2s);

    return RT_EOK;
}

static const struct rt_ofw_node_id bcm2835_i2s_ofw_ids[] =
{
    { .compatible = "brcm,bcm2835-i2s" },
    { /* sentinel */ }
};

static struct rt_platform_driver bcm2835_i2s_driver =
{
    .name = "bcm2835-i2s",
    .ids = bcm2835_i2s_ofw_ids,

    .probe = bcm2835_i2s_probe,
    .remove = bcm2835_i2s_remove,
};
RT_PLATFORM_DRIVER_EXPORT(bcm2835_i2s_driver);
