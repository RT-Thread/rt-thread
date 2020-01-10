/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-17     LiWeiHao     First implementation
 */

#include "drv_sound.h"
#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_dma.h"
#include "fsl_i2s.h"
#include "fsl_i2s_dma.h"
#include "fsl_wm8904.h"
#include "fsl_i2c.h"

#define TX_FIFO_SIZE (4096)

#define I2S_TX I2S1
#define I2S_RX I2S0

#define I2S_DMA_TX 15
#define I2S_DMA_RX 12

#ifndef CODEC_I2C_NAME
    #define CODEC_I2C_NAME "i2c4"
#endif

struct sound_device
{
    wm8904_handle_t wm8904_handle;
    dma_handle_t tx_dma_handle;
    i2s_dma_handle_t tx_i2s_dma_handle;
    struct rt_audio_device audio;
    struct rt_audio_configure replay_config;
    rt_uint8_t volume;
    rt_uint8_t *tx_fifo;
};

const pll_setup_t pll_setup =
{
    .syspllctrl = SYSCON_SYSPLLCTRL_BANDSEL_MASK | SYSCON_SYSPLLCTRL_SELP(0x1FU) | SYSCON_SYSPLLCTRL_SELI(0x8U),
    .syspllndec = SYSCON_SYSPLLNDEC_NDEC(0x2DU),
    .syspllpdec = SYSCON_SYSPLLPDEC_PDEC(0x42U),
    .syspllssctrl = {SYSCON_SYSPLLSSCTRL0_MDEC(0x34D3U) | SYSCON_SYSPLLSSCTRL0_SEL_EXT_MASK, 0x00000000U},
    .pllRate = 24576000U, /* 16 bits * 2 channels * 44.1 kHz * 16 */
    .flags = PLL_SETUPFLAG_WAITLOCK
};

static struct sound_device snd_dev;

void i2s_tx_transfer_callback(I2S_Type *base,
                              i2s_dma_handle_t *handle,
                              status_t completionStatus,
                              void *userData)
{
    struct sound_device *snd_dev = (struct sound_device *)userData;
    rt_audio_tx_complete(&snd_dev->audio);
}

static rt_err_t lpc_audio_init(struct rt_audio_device *audio)
{
    i2s_config_t tx_i2s_config;
    wm8904_config_t wm8904_config;

    CLOCK_EnableClock(kCLOCK_Iocon);
    CLOCK_EnableClock(kCLOCK_InputMux);
    CLOCK_EnableClock(kCLOCK_Gpio0);
    CLOCK_EnableClock(kCLOCK_Gpio1);

    CLOCK_AttachClk(kFRO12M_to_SYS_PLL);
    CLOCK_AttachClk(kSYS_PLL_to_FLEXCOMM7);

    RESET_PeripheralReset(kFC7_RST_SHIFT_RSTn);

    CLOCK_SetPLLFreq(&pll_setup);
    CLOCK_AttachClk(kSYS_PLL_to_MCLK);
    SYSCON->MCLKDIV = SYSCON_MCLKDIV_DIV(0U);

    // Flexcomm 7 I2S Tx
    IOCON_PinMuxSet(IOCON, 1, 12, IOCON_FUNC4 | IOCON_DIGITAL_EN); /* Flexcomm 7 / SCK */
    IOCON_PinMuxSet(IOCON, 1, 13, IOCON_FUNC4 | IOCON_DIGITAL_EN);  /* Flexcomm 7 / SDA */
    IOCON_PinMuxSet(IOCON, 1, 14, IOCON_FUNC4 | IOCON_DIGITAL_EN);  /* Flexcomm 7 / WS */

    /* MCLK output for I2S */
    IOCON_PinMuxSet(IOCON, 1, 17, IOCON_FUNC4 | IOCON_MODE_INACT | IOCON_DIGITAL_EN);
    SYSCON->MCLKIO = 1U;

    WM8904_GetDefaultConfig(&wm8904_config);
    snd_dev.wm8904_handle.i2c = (struct rt_i2c_bus_device *)rt_device_find(CODEC_I2C_NAME);
    if (WM8904_Init(&snd_dev.wm8904_handle, &wm8904_config) != kStatus_Success)
    {
        rt_kprintf("wm8904 init failed\n");
        return -RT_ERROR;
    }

    WM8904_SetMute(&snd_dev.wm8904_handle, RT_TRUE, RT_TRUE);

    I2S_TxGetDefaultConfig(&tx_i2s_config);
    tx_i2s_config.divider = CLOCK_GetPllOutFreq() / 48000U / 16 / 2;
    I2S_TxInit(I2S_TX, &tx_i2s_config);

    DMA_Init(DMA0);

    DMA_EnableChannel(DMA0, I2S_DMA_TX);
    DMA_SetChannelPriority(DMA0, I2S_DMA_TX, kDMA_ChannelPriority3);
    DMA_CreateHandle(&snd_dev.tx_dma_handle, DMA0, I2S_DMA_TX);

    I2S_TxTransferCreateHandleDMA(I2S_TX,
                                  &snd_dev.tx_i2s_dma_handle,
                                  &snd_dev.tx_dma_handle,
                                  i2s_tx_transfer_callback,
                                  (void *)&snd_dev);

    return RT_EOK;
}

static rt_err_t lpc_audio_start(struct rt_audio_device *audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    if (stream == AUDIO_STREAM_REPLAY)
    {
        struct rt_audio_caps caps;
        caps.main_type = AUDIO_TYPE_MIXER;
        caps.sub_type = AUDIO_MIXER_VOLUME;
        audio->ops->getcaps(audio, &caps);
        audio->ops->configure(audio, &caps);
        rt_audio_tx_complete(audio);
    }
    return RT_EOK;
}

static rt_err_t lpc_audio_stop(struct rt_audio_device *audio, int stream)
{
    if (stream == AUDIO_STREAM_REPLAY)
    {
        WM8904_SetMute(&snd_dev.wm8904_handle, RT_TRUE, RT_TRUE);
        I2S_TransferAbortDMA(I2S_TX, &snd_dev.tx_i2s_dma_handle);
    }
    return RT_EOK;
}

static rt_err_t lpc_audio_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct sound_device *snd_dev;

    RT_ASSERT(audio != RT_NULL);
    snd_dev = (struct sound_device *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY: /* qurey the types of hw_codec device */
    {
        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_OUTPUT: /* Provide capabilities of OUTPUT unit */
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.samplerate   = snd_dev->replay_config.samplerate;
            caps->udata.config.channels     = snd_dev->replay_config.channels;
            caps->udata.config.samplebits   = snd_dev->replay_config.samplebits;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = snd_dev->replay_config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = snd_dev->replay_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits   = snd_dev->replay_config.samplebits;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_MIXER: /* report the Mixer Units */
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_QUERY:
            caps->udata.mask = AUDIO_MIXER_VOLUME;
            break;

        case AUDIO_MIXER_VOLUME:
            caps->udata.value = snd_dev->volume;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}

static rt_err_t lpc_audio_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct sound_device *snd_dev = audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_MUTE:
        {
            WM8904_SetMute(&snd_dev->wm8904_handle, RT_TRUE, RT_TRUE);
            snd_dev->volume = 0;
            break;
        }

        case AUDIO_MIXER_VOLUME:
        {
            int volume = caps->udata.value / 2;
            WM8904_SetMute(&snd_dev->wm8904_handle, RT_FALSE, RT_FALSE);
            WM8904_SetVolume(&snd_dev->wm8904_handle, volume, volume);
            snd_dev->volume = volume;
            break;
        }
        }

        break;
    }
    case AUDIO_TYPE_OUTPUT:
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
        {
            struct rt_audio_configure config = caps->udata.config;
            i2s_config_t tx_i2s_config;
            snd_dev->replay_config.channels = config.channels;
            snd_dev->replay_config.samplebits = config.samplebits;
            snd_dev->replay_config.samplerate = config.samplerate;
            I2S_TxGetDefaultConfig(&tx_i2s_config);
            tx_i2s_config.divider = CLOCK_GetPllOutFreq() / config.samplerate / 16 / 2;
            I2S_TxInit(I2S_TX, &tx_i2s_config);
            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            struct rt_audio_configure config = caps->udata.config;
            i2s_config_t tx_i2s_config;
            snd_dev->replay_config.samplerate = config.samplerate;
            I2S_TxGetDefaultConfig(&tx_i2s_config);
            tx_i2s_config.divider = CLOCK_GetPllOutFreq() / config.samplerate / 16 / 2;
            I2S_TxInit(I2S_TX, &tx_i2s_config);
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }
        break;
    }
    }

    return result;
}

static rt_size_t lpc_audio_transmit(struct rt_audio_device *audio, const void *writeBuf, void *readBuf, rt_size_t size)
{
    RT_ASSERT(audio != RT_NULL);
    i2s_transfer_t transfer;
    transfer.data = (uint8_t *)writeBuf;
    transfer.dataSize = size;
    I2S_TxTransferSendDMA(I2S_TX, &snd_dev.tx_i2s_dma_handle, transfer);

    return RT_EOK;
}

static void lpc_audio_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    RT_ASSERT(audio != RT_NULL);
    /**
     *               TX_FIFO
     * +----------------+----------------+
     * |     block1     |     block2     |
     * +----------------+----------------+
     *  \  block_size  /
     */
    info->buffer      = snd_dev.tx_fifo;
    info->total_size  = TX_FIFO_SIZE;
    info->block_size  = TX_FIFO_SIZE / 2;
    info->block_count = 2;
}

static struct rt_audio_ops audio_ops =
{
    .getcaps = lpc_audio_getcaps,
    .configure = lpc_audio_configure,
    .init = lpc_audio_init,
    .start = lpc_audio_start,
    .stop = lpc_audio_stop,
    .transmit = lpc_audio_transmit,
    .buffer_info = lpc_audio_buffer_info,
};

int rt_hw_sound_init(void)
{
    rt_uint8_t *tx_fifo = RT_NULL;

    tx_fifo = rt_malloc(TX_FIFO_SIZE);
    if (tx_fifo == NULL)
    {
        return -RT_ENOMEM;
    }
    snd_dev.tx_fifo = tx_fifo;

    /* init default configuration */
    {
        snd_dev.replay_config.samplerate = 44100;
        snd_dev.replay_config.channels   = 2;
        snd_dev.replay_config.samplebits = 16;
        snd_dev.volume                   = 30;
    }

    snd_dev.audio.ops = &audio_ops;
    rt_audio_register(&snd_dev.audio, "sound0", RT_DEVICE_FLAG_WRONLY, &snd_dev);
    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_sound_init);