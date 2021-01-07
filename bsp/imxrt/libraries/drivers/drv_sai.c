/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-4-30     misonyo     the first version.
 */
 
#include <rtthread.h>
#include <rthw.h>
#include <rtdef.h>

#ifdef BSP_USING_AUDIO
#define LOG_TAG              "drv.sai"
#include <drv_log.h>

#include <rtdevice.h>
#include "drivers/audio.h"
#include "bsp_wm8960.h"
#include "drv_i2c.h"
#include "drv_sai.h"


#define RX_DMA_FIFO_SIZE (2048)
volatile rt_uint16_t rx_busy = 0;
volatile rt_uint16_t tx_busy = 0;

struct drv_sai sai_tx = {0};
struct drv_sai sai_rx = {0};
wm8960_config_t wm8960Config = {
    .route     = kWM8960_RoutePlaybackandRecord,
    .rightInputSource = kWM8960_InputDifferentialMicInput2,
    .playSource       = kWM8960_PlaySourceDAC,
    .slaveAddress     = WM8960_I2C_ADDR,
    .bus              = kWM8960_BusI2S,
    .format = {.mclk_HZ = 6144000U, .sampleRate = kWM8960_AudioSampleRate16KHz, .bitWidth = kWM8960_AudioBitWidth16bit},
    .master_slave = false,
};
const clock_audio_pll_config_t audioPllConfig =
{
    .loopDivider = 32,  /* PLL loop divider. Valid range for DIV_SELECT divider value: 27~54. */
    .postDivider = 1,   /* Divider after the PLL, should only be 1, 2, 4, 8, 16. */
    .numerator   = 77,  /* 30 bit numerator of fractional loop divider. */
    .denominator = 100, /* 30 bit denominator of fractional loop divider */
};
sai_transfer_format_t format;
sai_config_t config;
sai_transfer_t xfer;
struct imxrt_sai
{
    struct rt_audio_device audio;
    struct rt_audio_configure play_config;
    rt_uint16_t volume;
    rt_uint8_t* tx_fifo;
    struct rt_i2c_bus_device* i2c_bus;
    rt_uint8_t* rx_fifo;
};

struct imxrt_sai imxrt_payer_dev = { 0 };
static void sai_config(void)
{
#ifdef BSP_AUDIO_USING_DMA
    static struct saidma_tx_config sai_txdma = { .channel = 0U, .request = kDmaRequestMuxSai1Tx };
    sai_tx.dma_tx = &sai_txdma;
    sai_tx.dma_flag |= RT_DEVICE_FLAG_DMA_TX;
#if defined (BSP_USING_AUDIO_RECORD)
    static struct saidma_rx_config sai_rxdma = { .channel = 1U, .request = kDmaRequestMuxSai1Rx };
    sai_rx.dma_rx = &sai_rxdma;
#endif
#endif
}
static void sai_TxDmaCallback(I2S_Type* base, sai_edma_handle_t* handle, rt_int32_t status, void* userData)
{
    tx_busy = 1;
    rt_audio_tx_complete(&imxrt_payer_dev.audio);
}
#if defined (BSP_USING_AUDIO_RECORD)
static void sai_RxDmaCallback(I2S_Type* base, sai_edma_handle_t* handle, rt_int32_t status, void* userData)
{
    rx_busy = 1;
    rt_audio_rx_done(&imxrt_payer_dev.audio, &imxrt_payer_dev.rx_fifo[0], RX_DMA_FIFO_SIZE / 2);
}
#endif
void BOARD_EnableSaiMclkOutput(rt_bool_t enable)
{
    if(enable)
    {
        IOMUXC_GPR->GPR1 |= IOMUXC_GPR_GPR1_SAI1_MCLK_DIR_MASK;
    }
    else
    {
        IOMUXC_GPR->GPR1 &= (~IOMUXC_GPR_GPR1_SAI1_MCLK_DIR_MASK);
    }
}
void sai_format(void)
{
    SAI_TransferTxCreateHandleEDMA(sai_tx.base, &sai_tx.dma_tx->txHandle, sai_TxDmaCallback, NULL, &sai_tx.dma_tx->edma);
    SAI_TransferTxSetFormatEDMA(sai_tx.base, &sai_tx.dma_tx->txHandle, &format, DEMO_SAI_CLK_FREQ, DEMO_SAI_CLK_FREQ);
#if defined (BSP_USING_AUDIO_RECORD)
    SAI_TransferRxCreateHandleEDMA(sai_rx.base, &sai_rx.dma_rx->rxHandle, sai_RxDmaCallback, NULL, &sai_rx.dma_rx->edma);
    SAI_TransferRxSetFormatEDMA(sai_rx.base, &sai_rx.dma_rx->rxHandle, &format, DEMO_SAI_CLK_FREQ, DEMO_SAI_CLK_FREQ);
#endif
}

void sai_init(void)
{
    CLOCK_InitAudioPll(&audioPllConfig);
    CLOCK_SetMux(kCLOCK_Sai1Mux, DEMO_SAI1_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Sai1PreDiv, DEMO_SAI1_CLOCK_SOURCE_PRE_DIVIDER);
    CLOCK_SetDiv(kCLOCK_Sai1Div, DEMO_SAI1_CLOCK_SOURCE_DIVIDER);
    BOARD_EnableSaiMclkOutput(RT_TRUE);

    EDMA_CreateHandle(&sai_tx.dma_tx->edma, DMA0, sai_tx.dma_tx->channel);
    DMAMUX_SetSource(DMAMUX, sai_tx.dma_tx->channel, (rt_uint8_t)sai_tx.dma_tx->request);
    DMAMUX_EnableChannel(DMAMUX, sai_tx.dma_tx->channel);
    SAI_TxGetDefaultConfig(&config);
    SAI_TxInit(sai_tx.base, &config);
#if defined (BSP_USING_AUDIO_RECORD)
    EDMA_CreateHandle(&sai_rx.dma_rx->edma, DMA0, sai_rx.dma_rx->channel);
    DMAMUX_SetSource(DMAMUX, sai_rx.dma_rx->channel, (rt_uint8_t)sai_rx.dma_rx->request);
    DMAMUX_EnableChannel(DMAMUX, sai_rx.dma_rx->channel);
    SAI_RxGetDefaultConfig(&config);
    SAI_RxInit(sai_rx.base, &config);
#endif
    format.bitWidth = kSAI_WordWidth16bits;
    format.channel = 0U;
    format.sampleRate_Hz = kSAI_SampleRate16KHz;
    format.masterClockHz = DEMO_SAI_CLK_FREQ;
    format.protocol = config.protocol;
    format.stereo = kSAI_Stereo;
    format.isFrameSyncCompact = true;
    format.watermark = FSL_FEATURE_SAI_FIFO_COUNT / 2U;
    SAI_TransferTxCreateHandleEDMA(sai_tx.base, &sai_tx.dma_tx->txHandle, sai_TxDmaCallback, NULL, &sai_tx.dma_tx->edma);
    SAI_TransferTxSetFormatEDMA(sai_tx.base, &sai_tx.dma_tx->txHandle, &format, DEMO_SAI_CLK_FREQ, DEMO_SAI_CLK_FREQ);
#if defined (BSP_USING_AUDIO_RECORD)
    SAI_TransferRxCreateHandleEDMA(sai_rx.base, &sai_rx.dma_rx->rxHandle, sai_RxDmaCallback, NULL, &sai_rx.dma_rx->edma);
    SAI_TransferRxSetFormatEDMA(sai_rx.base, &sai_rx.dma_rx->rxHandle, &format, DEMO_SAI_CLK_FREQ, DEMO_SAI_CLK_FREQ);
#endif
}

void SAI_samplerate_set(rt_uint32_t freq)
{
    switch(freq)
    {
    case 48000:
        format.sampleRate_Hz = kSAI_SampleRate48KHz;
        break;
    case 44100:
        format.sampleRate_Hz = kSAI_SampleRate44100Hz;
        break;
    case 32000:
        format.sampleRate_Hz = kSAI_SampleRate32KHz;
        break;
    case 24000:
        format.sampleRate_Hz = kSAI_SampleRate24KHz;
        break;
    case 22050:
        format.sampleRate_Hz = kSAI_SampleRate22050Hz;
        break;
    case 16000:
        format.sampleRate_Hz = kSAI_SampleRate16KHz;
        break;
    case 12000:
        format.sampleRate_Hz = kSAI_SampleRate12KHz;
        break;
    case 11025:
        format.sampleRate_Hz = kSAI_SampleRate11025Hz;
        break;
    case 8000:
        format.sampleRate_Hz = kSAI_SampleRate8KHz;
        break;
    default:
        format.sampleRate_Hz = kSAI_SampleRate16KHz;
        break;
    }

}

void SAI_channels_set(rt_uint16_t channels)
{
    switch(channels)
    {
    case 2:
        format.stereo = kSAI_Stereo;
        break;
    case 1:
        format.stereo = kSAI_MonoRight;
        break;
    case 0:
        format.stereo = kSAI_MonoLeft;
        break;
    default:
        format.stereo = kSAI_Stereo;
        break;
    }
}

void SAI_samplebits_set(rt_uint16_t samplebits)
{

    switch(samplebits)
    {
    case 16:
        format.bitWidth = kSAI_WordWidth16bits;
        break;
    case 24:
        format.bitWidth = kSAI_WordWidth24bits;
        break;
    case 32:
        format.bitWidth = kSAI_WordWidth32bits;
        break;
    default:
        format.bitWidth = kSAI_WordWidth16bits;
        break;
    }
}


static rt_err_t imxrt_payer_getcaps(struct rt_audio_device* audio, struct rt_audio_caps* caps)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(audio != RT_NULL);
    struct imxrt_sai* imxrt_audio = (struct imxrt_sai*)audio->parent.user_data;

    switch(caps->main_type)
    {
    case AUDIO_TYPE_QUERY: /* qurey the types of hw_codec device */
    {
        switch(caps->sub_type)
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
    case AUDIO_TYPE_INPUT:
    {
        switch(caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.channels     = imxrt_audio->play_config.channels;
            caps->udata.config.samplebits   = imxrt_audio->play_config.samplebits;
            caps->udata.config.samplerate   = imxrt_audio->play_config.samplerate;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = imxrt_audio->play_config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = imxrt_audio->play_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits   = imxrt_audio->play_config.samplebits;
            break;
        default:
            result = -RT_ERROR;
            break;
        }
        break;
    }
    case AUDIO_TYPE_OUTPUT: /* Provide capabilities of OUTPUT unit */
    {
        switch(caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.samplerate   = imxrt_audio->play_config.samplerate;
            caps->udata.config.channels     = imxrt_audio->play_config.channels;
            caps->udata.config.samplebits   = imxrt_audio->play_config.samplebits;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = imxrt_audio->play_config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = imxrt_audio->play_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits   = imxrt_audio->play_config.samplebits;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_MIXER: /* report the Mixer Units */
    {
        switch(caps->sub_type)
        {
        case AUDIO_MIXER_QUERY:
            caps->udata.mask = AUDIO_MIXER_VOLUME;
            break;

        case AUDIO_MIXER_VOLUME:
            caps->udata.value =  WM8960_GetVolume(imxrt_payer_dev.i2c_bus,kWM8960_ModuleDAC);
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

static rt_err_t imxrt_payer_configure(struct rt_audio_device* audio, struct rt_audio_caps* caps)
{

    rt_err_t result = RT_EOK;
    RT_ASSERT(audio != RT_NULL);
    struct imxrt_sai* imxrt_audio = (struct imxrt_sai*)audio->parent.user_data;

    switch(caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
    {
        switch(caps->sub_type)
        {
        case AUDIO_MIXER_MUTE:
        {
            /* set mute mode */
            WM8960_SetMute(imxrt_payer_dev.i2c_bus, kWM8960_ModuleDAC, RT_FALSE);
            break;
        }

        case AUDIO_MIXER_VOLUME:
        {
            int volume = caps->udata.value;

            imxrt_audio->volume = volume;
            /* set mixer volume */
            WM8960_SetVolume(imxrt_payer_dev.i2c_bus, kWM8960_ModuleDAC, volume);


            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_OUTPUT:
    {
        switch(caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
        {
            struct rt_audio_configure config = caps->udata.config;

            imxrt_audio->play_config.samplerate = config.samplerate;
            imxrt_audio->play_config.samplebits = config.samplebits;
            imxrt_audio->play_config.channels = config.channels;

            SAI_channels_set(config.channels);
            SAI_samplerate_set(config.samplerate);
            SAI_samplebits_set(config.samplebits);
            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            imxrt_audio->play_config.samplerate = caps->udata.config.samplerate;
            SAI_samplerate_set(caps->udata.config.samplerate);
            break;
        }

        case AUDIO_DSP_CHANNELS:
        {
            imxrt_audio->play_config.channels = caps->udata.config.channels;
            SAI_channels_set(caps->udata.config.channels);
            break;
        }

        case AUDIO_DSP_SAMPLEBITS:
        {
            imxrt_audio->play_config.samplebits = caps->udata.config.samplebits;
            SAI_samplebits_set(caps->udata.config.samplebits);
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }
        break;
    }
    case AUDIO_TYPE_INPUT:
    {
        switch(caps->sub_type)
        {

        case AUDIO_DSP_PARAM:
        {
            imxrt_audio->play_config.samplerate = caps->udata.config.samplerate;
            imxrt_audio->play_config.channels   = caps->udata.config.channels;
            imxrt_audio->play_config.samplebits = caps->udata.config.samplebits;

            SAI_TransferTerminateReceiveEDMA(sai_rx.base, &sai_rx.dma_rx->rxHandle);
            SAI_samplerate_set(caps->udata.config.samplerate);
            SAI_channels_set(caps->udata.config.channels);
            SAI_samplebits_set(caps->udata.config.samplebits);
            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            imxrt_audio->play_config.samplerate = caps->udata.config.samplerate;
            SAI_samplerate_set(caps->udata.config.samplerate);
            break;
        }
        case AUDIO_DSP_CHANNELS:
        {
            imxrt_audio->play_config.channels = caps->udata.config.channels;
            SAI_channels_set(caps->udata.config.channels);
            break;
        }

        case AUDIO_DSP_SAMPLEBITS:
        {
            imxrt_audio->play_config.samplebits = caps->udata.config.samplebits;
            SAI_samplebits_set(caps->udata.config.samplebits);
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }
        /* After set config, MCLK will stop */
        SAI_TxSoftwareReset(sai_tx.base, kSAI_ResetTypeSoftware);
        SAI_RxSoftwareReset(sai_rx.base, kSAI_ResetTypeSoftware);
        xfer.data = imxrt_payer_dev.tx_fifo; // +i * (AUD_FIFO_SIZE / 4);
        xfer.dataSize = AUD_BLOCK_SIZE;
        SAI_TransferSendEDMA(sai_tx.base, &sai_tx.dma_tx->txHandle, &xfer);
        SAI_TransferReceiveEDMA(sai_rx.base, &sai_rx.dma_rx->rxHandle, &xfer);
        break;
    }

    default:
        break;
    }
    return result;

}
static rt_err_t imxrt_payer_init(struct rt_audio_device* audio)
{
    RT_ASSERT(audio != RT_NULL);
    imxrt_payer_dev.i2c_bus = (struct rt_i2c_bus_device*)rt_device_find(CODEC_I2C_NAME);
    sai_init();
    return RT_EOK;
}
static rt_err_t imxrt_payer_start(struct rt_audio_device* audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    sai_format();
    WM8960_init(imxrt_payer_dev.i2c_bus, &wm8960Config);

    xfer.data = imxrt_payer_dev.rx_fifo;
    xfer.dataSize = AUD_BLOCK_SIZE;
#if defined (BSP_USING_AUDIO_RECORD)
    SAI_TransferReceiveEDMA(sai_rx.base, &sai_rx.dma_rx->rxHandle, &xfer);
#endif
    SAI_TransferSendEDMA(sai_tx.base, &sai_tx.dma_tx->txHandle, &xfer);
    return RT_EOK;
}

static rt_err_t imxrt_payer_stop(struct rt_audio_device* audio, int stream)
{

    RT_ASSERT(audio != RT_NULL);
    SAI_TransferTerminateSendEDMA(sai_tx.base, &sai_tx.dma_tx->txHandle);
    SAI_TransferTerminateReceiveEDMA(sai_rx.base, &sai_rx.dma_rx->rxHandle);
    WM8960_Deinit(imxrt_payer_dev.i2c_bus);

    return RT_EOK;

}
static rt_size_t imxrt_payer_transmit(struct rt_audio_device* audio, const void* writeBuf, void* readBuf, rt_size_t size)
{
    RT_ASSERT(audio != RT_NULL);
#if defined (BSP_USING_AUDIO_RECORD)
    xfer.data = imxrt_payer_dev.rx_fifo;
    xfer.dataSize = RX_DMA_FIFO_SIZE;
    SAI_TransferReceiveEDMA(sai_rx.base, &sai_rx.dma_rx->rxHandle, &xfer);
    SAI_TransferSendEDMA(sai_tx.base, &sai_tx.dma_tx->txHandle, &xfer);
#else
    xfer.data = (rt_uint8_t*)writeBuf;
    xfer.dataSize = size;
    SAI_TransferSendEDMA(sai_tx.base, &sai_tx.dma_tx->txHandle, &xfer);
#endif

    return size;
}

static void imxrt_payer_buffer_info(struct rt_audio_device* audio, struct rt_audio_buf_info* info)
{
    RT_ASSERT(audio != RT_NULL);
    /**
     *               AUD_FIFO
     * +----------------+----------------+
     * |     block1     |     block2     |
     * +----------------+----------------+
     *  \  block_size  /
     */
    info->buffer      = imxrt_payer_dev.tx_fifo;
    info->total_size  = AUD_DMA_FIFO_SIZE;
    info->block_size  = AUD_DMA_FIFO_SIZE / 2;
    info->block_count = 2;
}

static struct rt_audio_ops imxrt_payer_ops =
{
    .getcaps     = imxrt_payer_getcaps,
    .configure   = imxrt_payer_configure,
    .init        = imxrt_payer_init,
    .start       = imxrt_payer_start,
    .stop        = imxrt_payer_stop,
    .transmit    = imxrt_payer_transmit,
    .buffer_info = imxrt_payer_buffer_info,
};

int rt_hw_sound_init(void)
{
    rt_uint8_t* tx_fifo = RT_NULL;
    rt_uint8_t* rx_fifo = RT_NULL;

    sai_tx.base = SAI1;
    sai_rx.base = SAI1;
    sai_tx.irqn = SAI1_IRQn;
    sai_config();

    tx_fifo = rt_calloc(1, AUD_DMA_FIFO_SIZE);
    rx_fifo = rt_calloc(1, AUD_DMA_FIFO_SIZE);
    if(tx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    rt_memset(tx_fifo, 0, AUD_DMA_FIFO_SIZE);
    imxrt_payer_dev.tx_fifo = tx_fifo;
    rt_memset(rx_fifo, 0, AUD_DMA_FIFO_SIZE);
    imxrt_payer_dev.rx_fifo = rx_fifo;

    imxrt_payer_dev.audio.ops = &imxrt_payer_ops;
    rt_audio_register(&imxrt_payer_dev.audio, "mic", RT_DEVICE_FLAG_RDWR, &imxrt_payer_dev);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_sound_init);

#endif /* BSP_USING_AUDIO*/
