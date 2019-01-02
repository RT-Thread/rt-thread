/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_codec.h"
#include "fsl_wm8960.h"

#include <fsl_sai.h>
#include <fsl_sai_edma.h>
#include <fsl_lpi2c.h>
#include <fsl_dmamux.h>

#define DEMO_CODEC_WM8960
#define DEMO_SAI SAI1
#define DEMO_SAI_IRQ SAI1_IRQn
#define SAI_TxIRQHandler SAI1_IRQHandler

/* Select Audio/Video PLL (786.48 MHz) as sai1 clock source */
#define DEMO_SAI1_CLOCK_SOURCE_SELECT (2U)
/* Clock pre divider for sai1 clock source */
#define DEMO_SAI1_CLOCK_SOURCE_PRE_DIVIDER (1U)
/* Clock divider for sai1 clock source */
#define DEMO_SAI1_CLOCK_SOURCE_DIVIDER (63U)
/* Get frequency of sai1 clock */
#define DEMO_SAI_CLK_FREQ (CLOCK_GetFreq(kCLOCK_AudioPllClk) / (DEMO_SAI1_CLOCK_SOURCE_DIVIDER + 1U) / (DEMO_SAI1_CLOCK_SOURCE_PRE_DIVIDER + 1U))

/* I2C instance and clock */
#define DEMO_I2C LPI2C1

/* Select USB1 PLL (480 MHz) as master lpi2c clock source */
#define DEMO_LPI2C_CLOCK_SOURCE_SELECT (0U)
/* Clock divider for master lpi2c clock source */
#define DEMO_LPI2C_CLOCK_SOURCE_DIVIDER (5U)
/* Get frequency of lpi2c clock */
#define DEMO_I2C_CLK_FREQ ((CLOCK_GetFreq(kCLOCK_Usb1PllClk) / 8) / (DEMO_LPI2C_CLOCK_SOURCE_DIVIDER + 1U))

/* DMA */
#define DMAMUX0 DMAMUX
#define EXAMPLE_DMA DMA0
#define EXAMPLE_CHANNEL (0U)
#define EXAMPLE_SAI_TX_SOURCE kDmaRequestMuxSai1Tx

struct imxcodec
{
    I2S_Type *sai;
    sai_edma_handle_t txHandle;
    wm8960_handle_t codecHandle;
    edma_handle_t dmaHandle;
    lpi2c_master_handle_t i2cHandle;
    sai_transfer_format_t format;
};

static void _InitPins(void)
{
    CLOCK_EnableClock(kCLOCK_Iomuxc);

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL, 1);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA, 1);

    IOMUXC_SetPinConfig( IOMUXC_GPIO_AD_B1_00_LPI2C1_SCL,  0xD8B0u);
    IOMUXC_SetPinConfig(  IOMUXC_GPIO_AD_B1_01_LPI2C1_SDA, 0xD8B0u);

    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_09_SAI1_MCLK, 1U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_13_SAI1_TX_DATA00, 1U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_14_SAI1_TX_BCLK, 1U);
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B1_15_SAI1_TX_SYNC, 1U);

    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_09_SAI1_MCLK, 0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_13_SAI1_TX_DATA00,  0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_14_SAI1_TX_BCLK, 0x10B0u);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B1_15_SAI1_TX_SYNC, 0x10B0u);
}

static void BOARD_EnableSaiMclkOutput(bool enable)
{
    if (enable)
    {
        IOMUXC_GPR->GPR1 |= IOMUXC_GPR_GPR1_SAI1_MCLK_DIR_MASK;
    }
    else
    {
        IOMUXC_GPR->GPR1 &= (~IOMUXC_GPR_GPR1_SAI1_MCLK_DIR_MASK);
    }
}

static void saidma_callback(I2S_Type *base, sai_edma_handle_t *handle, status_t status, void *userData)
{
    int ind = 0;
    rt_uint8_t *saddr;

    ind = handle->queueDriver;
    saddr = (rt_uint8_t*)handle->saiQueue[ind].data;
    rt_audio_tx_complete(userData, saddr);
}

/*********************************************************************************************************
**   Audio device
*********************************************************************************************************/

static rt_err_t icodec_getcaps(struct rt_audio_device *audio,struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct imxcodec *icodec = (struct imxcodec *)audio->parent.user_data;

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
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            if (audio->replay == NULL)
            {
                result = -RT_ERROR;
                break;
            }
            caps->udata.config.channels     = 1;
            caps->udata.config.samplefmt    = 1;
            caps->udata.config.samplerate   = 1;
            caps->udata.config.samplefmts   = 1;
            break;
        default:
            result = -RT_ERROR;
            break;
        }
        break;
    case AUDIO_TYPE_MIXER: /* report the Mixer Units */
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_QUERY:
            caps->udata.mask = AUDIO_MIXER_VOLUME | AUDIO_MIXER_DIGITAL | AUDIO_MIXER_LINE;
            break;
        case AUDIO_MIXER_VOLUME:
            caps->udata.value = WM8960_GetVolume(&icodec->codecHandle, kWM8960_ModuleDAC);
            break;
        case AUDIO_MIXER_DIGITAL:

            break;
        case AUDIO_MIXER_LINE:

            break;
        default:
            result = -RT_ERROR;
            break;
        }
        break;
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}

static rt_err_t icodec_configure(struct rt_audio_device *audio,struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct imxcodec *icodec = (struct imxcodec *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_VOLUME:
        {
            WM8960_SetVolume(&icodec->codecHandle, kWM8960_ModuleDAC,
                             caps->udata.value);
        }
        break;
        default:
        {
            result = -RT_ERROR;
        }
        break;
        }
    }
    break;
    case AUDIO_TYPE_OUTPUT:
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
        {

        } break;
        case AUDIO_DSP_SAMPLERATE:
        {
            int rate = caps->udata.value;

            icodec->format.sampleRate_Hz = rate;
            SAI_TxSetFormat(icodec->sai, &icodec->format, icodec->format.masterClockHz, icodec->format.masterClockHz);
        }
        break;
        default:
        {
            result = -RT_ERROR;
        }
        break;
        }
    }
    break;
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}

static rt_err_t icodec_init(struct rt_audio_device *audio)
{
    sai_config_t config;
    uint32_t mclkSourceClockHz = 0U;
    edma_config_t dmaConfig = {0};
    lpi2c_master_config_t i2cConfig = {0};
    uint32_t i2cSourceClock;
    clock_audio_pll_config_t audioPllConfig = {32, 1, 77, 100};
    struct imxcodec *icodec = audio->parent.user_data;
    sai_transfer_format_t *format;

    icodec->sai = DEMO_SAI;
    format = &icodec->format;

    _InitPins();
    CLOCK_InitAudioPll(&audioPllConfig);

    /*Clock setting for LPI2C*/
    CLOCK_SetMux(kCLOCK_Lpi2cMux, DEMO_LPI2C_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Lpi2cDiv, DEMO_LPI2C_CLOCK_SOURCE_DIVIDER);

    /*Clock setting for SAI1*/
    CLOCK_SetMux(kCLOCK_Sai1Mux, DEMO_SAI1_CLOCK_SOURCE_SELECT);
    CLOCK_SetDiv(kCLOCK_Sai1PreDiv, DEMO_SAI1_CLOCK_SOURCE_PRE_DIVIDER);
    CLOCK_SetDiv(kCLOCK_Sai1Div, DEMO_SAI1_CLOCK_SOURCE_DIVIDER);

    /*Enable MCLK clock*/
    BOARD_EnableSaiMclkOutput(true);

    /* Create EDMA handle */
    EDMA_GetDefaultConfig(&dmaConfig);
    EDMA_Init(EXAMPLE_DMA, &dmaConfig);
    EDMA_CreateHandle(&icodec->dmaHandle, EXAMPLE_DMA, EXAMPLE_CHANNEL);

    DMAMUX_Init(DMAMUX0);
    DMAMUX_SetSource(DMAMUX0, EXAMPLE_CHANNEL, EXAMPLE_SAI_TX_SOURCE);
    DMAMUX_EnableChannel(DMAMUX0, EXAMPLE_CHANNEL);

    /* Init SAI module */
    SAI_TxGetDefaultConfig(&config);
    config.protocol = kSAI_BusLeftJustified;
    SAI_TxInit(DEMO_SAI, &config);

    /* Configure the audio format */
    format->bitWidth = kSAI_WordWidth16bits;
    format->channel = 0U;
    format->sampleRate_Hz = kSAI_SampleRate48KHz;
    format->masterClockHz = DEMO_SAI_CLK_FREQ;
    format->protocol = config.protocol;
    format->stereo = kSAI_Stereo;
    format->isFrameSyncCompact = 0;
    format->watermark = FSL_FEATURE_SAI_FIFO_COUNT / 2U;

    /* Configure Sgtl5000 I2C */
    icodec->codecHandle.base = DEMO_I2C;
    icodec->codecHandle.i2cHandle = &icodec->i2cHandle;
    i2cSourceClock = DEMO_I2C_CLK_FREQ;

    LPI2C_MasterGetDefaultConfig(&i2cConfig);
    LPI2C_MasterInit(DEMO_I2C, &i2cConfig, i2cSourceClock);
    LPI2C_MasterTransferCreateHandle(DEMO_I2C, &icodec->i2cHandle, NULL, NULL);

    WM8960_Init(&icodec->codecHandle, NULL);
    WM8960_ConfigDataFormat(&icodec->codecHandle, format->masterClockHz, format->sampleRate_Hz, format->bitWidth);

    SAI_TransferTxCreateHandleEDMA(icodec->sai, &icodec->txHandle, saidma_callback, audio, &icodec->dmaHandle);

    mclkSourceClockHz = DEMO_SAI_CLK_FREQ;
    SAI_TransferTxSetFormatEDMA(icodec->sai, &icodec->txHandle, format, mclkSourceClockHz, format->masterClockHz);

    return RT_EOK;
}

static rt_err_t icodec_shutdown(struct rt_audio_device *audio)
{
    return RT_EOK;
}

rt_err_t icodec_start(struct rt_audio_device *audio,int stream)
{
    return RT_EOK;
}

rt_err_t icodec_stop(struct rt_audio_device *audio,int stream)
{
    return RT_EOK;
}

static rt_err_t icodec_suspend(struct rt_audio_device *audio,int stream)
{
    return RT_EOK;
}

static rt_err_t    icodec_resume(struct rt_audio_device *audio,int stream)
{
    return RT_EOK;
}

static rt_err_t icodec_control (struct rt_audio_device *audio, int cmd, void *args)
{
    rt_err_t result = RT_EOK;

    switch (cmd)
    {
    case AUDIO_CTL_HWRESET:

        break;
    default:
        result = -RT_ERROR;
        break;
    }

    return result;
}

static rt_size_t icodec_transmit(struct rt_audio_device *audio, const void *writeBuf, void *readBuf, rt_size_t size)
{
    struct imxcodec *icodec = (struct imxcodec *)audio->parent.user_data;

    if(writeBuf != RT_NULL)
    {
        sai_transfer_t xfer;

        xfer.data = (uint8_t *)writeBuf;
        xfer.dataSize = size;
		if (size%32 == 0)
            icodec->txHandle.count = 16;
		else
            icodec->txHandle.count = 1;

        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void*)writeBuf, size);
        if (SAI_TransferSendEDMA(icodec->sai, &icodec->txHandle, &xfer) != kStatus_Success)
            return 0;

        return size;
    }

    return 0;
}

static struct imxcodec          _g_imxcodec;
static struct rt_audio_device   _g_audio_device;
const struct rt_audio_ops       _g_audio_ops =
{
    .getcaps    = icodec_getcaps,
    .configure  = icodec_configure,

    .init       = icodec_init,
    .shutdown   = icodec_shutdown,
    .start      = icodec_start,
    .stop       = icodec_stop,
    .suspend    = icodec_suspend,
    .resume     = icodec_resume,
    .control    = icodec_control,

    .transmit   = icodec_transmit,
};

int rt_hw_codec_init(void)
{
    int result;
    struct rt_audio_device *audio   = &_g_audio_device;

    audio->ops = (struct rt_audio_ops*)&_g_audio_ops;
    _g_imxcodec.sai = DEMO_SAI;
    result = rt_audio_register(audio,"sound0", RT_DEVICE_FLAG_WRONLY, &_g_imxcodec);

    return result;
}
INIT_DEVICE_EXPORT(rt_hw_codec_init);
