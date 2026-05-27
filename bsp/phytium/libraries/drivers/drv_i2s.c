/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Email: opensource_embedded@phytium.com.cn
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-01-21     zhangyan     first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>

#include <drv_i2s.h>
#include "fi2s.h"
#include "fi2s_hw.h"
#include "fddma.h"
#include "fddma_hw.h"
#include "fddma_bdl.h"
#include "interrupt.h"

#define DBG_TAG              "drv.i2s"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#define PER_BUFFER_SIZE          16384
#define TX_RX_BUF_LEN            16384

static struct phytium_i2s_device i2s_dev0;
static const u32 ddma_ctrl_id = FDDMA2_I2S_ID;
static const u32 i2s_ctrl_id = FI2S0_ID;
static u32 trans_buf[2][TX_RX_BUF_LEN] __attribute__((aligned(FDDMA_DDR_ADDR_ALIGNMENT))) = {0};
static FDdmaBdlDesc *bdl_desc_list_tx = NULL;
static FDdmaBdlDesc *bdl_desc_list_rx = NULL;

struct phytium_i2s_device
{
    const char *name;
    struct rt_audio_device audio;
    struct rt_audio_configure config;

    FI2s i2s_ctrl;
    FI2sConfig i2s_config;
    FDdma ddmac;
    FDdmaConfig ddmac_config;

    rt_uint8_t *rx_fifo;
    rt_uint8_t *tx_fifo;
    FDdmaChanConfig rx_config;
    FDdmaChanConfig tx_config;
    rt_uint8_t rx_channel; /* 接收通道为DDMA通道1 */
    rt_uint8_t tx_channel; /* 接收通道为DDMA通道1 */
    rt_uint8_t volume;
};

static void FDdmaSetupInterrupt(FDdma *const instance)
{
    FASSERT(instance);
    FDdmaConfig *config = &instance->config;

    rt_uint32_t cpu_id = rt_hw_cpu_id();
    rt_hw_interrupt_set_target_cpus(config->irq_num, cpu_id);
    rt_hw_interrupt_set_priority(config->irq_num, config->irq_priority);
    /* register intr callback */
    rt_hw_interrupt_install(config->irq_num,
                            FDdmaIrqHandler,
                            instance,
                            NULL);

    /* enable ddma0 irq */
    rt_hw_interrupt_umask(config->irq_num);

    return;
}

static FError FI2sCodecInit(u32 word_length)
{
    FError ret = FT_SUCCESS;

    return ret;
}

static FError FI2sRxInit(struct phytium_i2s_device *i2s_dev, u32 word_length)
{
    LOG_E("FI2sRxInit");
    FError ret = FI2S_SUCCESS;
    FIOPadSetI2sMux();
    i2s_dev->i2s_ctrl.data_config.word_length = word_length;
    i2s_dev->i2s_config = *FI2sLookupConfig(i2s_ctrl_id);

    ret = FI2sCfgInitialize(&i2s_dev->i2s_ctrl, &i2s_dev->i2s_config);
    if (FI2S_SUCCESS != ret)
    {
        printf("Init the i2s failed.\r\n");
        return ret;
    }

    FI2sClkOutDiv(&i2s_dev->i2s_ctrl, i2s_dev->config.samplerate);
    FI2sTxRxEnable(&i2s_dev->i2s_ctrl, TRUE); /* 模块使能 */
    return ret;
}

static FError FI2sRxDdmaInit(struct phytium_i2s_device *i2s_dev)
{
    FError ret = FI2S_SUCCESS;

    i2s_dev->ddmac_config = *FDdmaLookupConfig(ddma_ctrl_id);

    ret = FDdmaCfgInitialize(&i2s_dev->ddmac, &i2s_dev->ddmac_config);
    if (FI2S_SUCCESS != ret)
    {
        printf("DDMA config initialization failed.\r\n");
        return ret;
    }

    return ret;
}

static FError FI2sDdmaDeviceRX(struct phytium_i2s_device *i2s_dev, u32 work_mode, const void *src, fsize_t total_bytes, fsize_t per_buff_len)
{
    FError ret = FI2S_SUCCESS;
    fsize_t bdl_num = total_bytes / per_buff_len;

    rt_hw_cpu_dcache_invalidate((uintptr)src, total_bytes);

    for (u32 chan = FDDMA_CHAN_0; chan < FDDMA_NUM_OF_CHAN; chan++) /* 清除中断 */
    {
        FDdmaClearChanIrq(i2s_dev->ddmac_config.base_addr, chan, i2s_dev->ddmac_config.caps);
    }

    if (bdl_desc_list_rx == NULL)
    {
        bdl_desc_list_rx = rt_malloc_align(bdl_num * sizeof(FDdmaBdlDesc), FDDMA_BDL_ADDR_ALIGNMENT);
    }
    rt_memset(bdl_desc_list_rx, 0, bdl_num * sizeof(FDdmaBdlDesc));

    FDdmaBdlDescConfig *bdl_desc_config = rt_calloc(1, bdl_num * sizeof(FDdmaBdlDescConfig));
    if ((NULL == bdl_desc_config))
    {
        printf("FDdmaBdlDescConfig allocate failed.\r\n");
        return FDDMA_ERR_IS_USED;
    }
    /* set BDL descriptors */
    for (fsize_t loop = 0; loop < bdl_num; loop++)
    {
        bdl_desc_config[loop].current_desc_num = loop;
        bdl_desc_config[loop].src_addr = (uintptr)(src + per_buff_len * loop);
        bdl_desc_config[loop].trans_length = per_buff_len;
    }
       bdl_desc_config[bdl_num -1].ioc = TRUE;
    /* set BDL descriptor list with descriptor configs */
    for (fsize_t loop = 0; loop <  bdl_num; loop++)
    {
        FDdmaBDLSetDesc(bdl_desc_list_rx, &bdl_desc_config[loop]);
    }

    i2s_dev->rx_config.slave_id = 0U,
    i2s_dev->rx_config.req_mode = FI2S_PCM_STREAM_CAPTURE;
    i2s_dev->rx_config.ddr_addr = (uintptr)src;
    i2s_dev->rx_config.dev_addr = i2s_dev->i2s_config.base_addr + FI2S_RXDMA ;
    i2s_dev->rx_config.trans_len = total_bytes;
    i2s_dev->rx_config.timeout = 0xffff,
    i2s_dev->rx_config.first_desc_addr = (uintptr)bdl_desc_list_rx;
    i2s_dev->rx_config.valid_desc_num = bdl_num;

    ret = FDdmaChanBdlConfigure(&i2s_dev->ddmac, i2s_dev->rx_channel, &i2s_dev->rx_config);

    if (ret !=  FI2S_SUCCESS)
    {
        printf("DDMA BDL configure failer.\r\n");
        return ret;
    }
    rt_free(bdl_desc_config);

    return ret;
}

static FError FI2sDdmaDeviceTX(struct phytium_i2s_device *i2s_dev, u32 work_mode, const void *src, fsize_t total_bytes, fsize_t per_buff_len)
{
    FError ret = FI2S_SUCCESS;
    fsize_t bdl_num = total_bytes / per_buff_len;

    rt_hw_cpu_dcache_clean((uintptr)src, total_bytes);

    for (u32 chan = FDDMA_CHAN_0; chan < FDDMA_NUM_OF_CHAN; chan++) /* 清除中断 */
    {
        FDdmaClearChanIrq(i2s_dev->ddmac_config.base_addr, chan, i2s_dev->ddmac_config.caps);
    }

    if (bdl_desc_list_tx == NULL)
    {
        bdl_desc_list_tx = rt_malloc_align(bdl_num * sizeof(FDdmaBdlDesc), FDDMA_BDL_ADDR_ALIGNMENT);
    }
    rt_memset(bdl_desc_list_tx, 0, bdl_num * sizeof(FDdmaBdlDesc));

    FDdmaBdlDescConfig *bdl_desc_config = rt_calloc(1, bdl_num * sizeof(FDdmaBdlDescConfig));
    if ((NULL == bdl_desc_config))
    {
        printf("FDdmaBdlDescConfig allocate failed.\r\n");
        return FDDMA_ERR_IS_USED;
    }
    /* set BDL descriptors */
    for (fsize_t loop = 0; loop < bdl_num; loop++)
    {
        bdl_desc_config[loop].current_desc_num = loop;
        bdl_desc_config[loop].src_addr = (uintptr)(src + per_buff_len * loop);
        bdl_desc_config[loop].trans_length = per_buff_len;
    }
       bdl_desc_config[bdl_num -1].ioc = TRUE;
    /* set BDL descriptor list with descriptor configs */
    for (fsize_t loop = 0; loop <  bdl_num; loop++)
    {
        FDdmaBDLSetDesc(bdl_desc_list_tx, &bdl_desc_config[loop]);
    }

    i2s_dev->tx_config.slave_id = 0U,
    i2s_dev->tx_config.req_mode = FI2S_PCM_STREAM_PLAYBACK;
    i2s_dev->tx_config.ddr_addr = (uintptr)src;
    i2s_dev->tx_config.dev_addr = i2s_dev->i2s_config.base_addr + FI2S_TXDMA ;
    i2s_dev->tx_config.trans_len = total_bytes;
    i2s_dev->tx_config.timeout = 0xffff,
    i2s_dev->tx_config.first_desc_addr = (uintptr)bdl_desc_list_tx;
    i2s_dev->tx_config.valid_desc_num = bdl_num;

    ret = FDdmaChanBdlConfigure(&i2s_dev->ddmac, i2s_dev->tx_channel, &i2s_dev->tx_config);

    if (ret !=  FI2S_SUCCESS)
    {
        printf("DDMA BDL configure failer.\r\n");
        return ret;
    }
    rt_free(bdl_desc_config);

    return ret;
}

void dma_rx_channel_transfer_callback(void *args)
{
    LOG_E("dma_rx_channel_transfer_callback");
#if defined(RT_USING_I2S0)
    rt_audio_rx_done(&i2s_dev0.audio, i2s_dev0.rx_fifo, TX_RX_BUF_LEN);
#endif
}

void dma_tx_channel_transfer_callback(void *args)
{
    LOG_E("dma_tx_channel_transfer_callback");
#if defined(RT_USING_I2S0)
    rt_audio_tx_complete(&i2s_dev0.audio);
#endif
}

static rt_err_t i2s_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    LOG_E("i2s_getcaps");
    rt_err_t result = RT_EOK;
    struct phytium_i2s_device *i2s_dev;

    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY: /* qurey the types of hw_codec device */
    {
        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_INPUT | AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
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
            caps->udata.config.samplerate   = i2s_dev->config.samplerate;
            caps->udata.config.channels     = i2s_dev->config.channels;
            caps->udata.config.samplebits   = i2s_dev->config.samplebits;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = i2s_dev->config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = i2s_dev->config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits   = i2s_dev->config.samplebits;
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
            caps->udata.value = i2s_dev->volume;
            break;

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    case AUDIO_TYPE_INPUT:
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
        {
            struct rt_audio_configure config = caps->udata.config;

            i2s_dev->config.channels   = config.channels;
            i2s_dev->config.samplebits = config.samplebits;
            i2s_dev->config.samplerate = config.samplerate;

            break;
        }

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

static rt_err_t i2s_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    LOG_E("i2s_configure");
    rt_err_t result = RT_EOK;
    struct phytium_i2s_device *i2s_dev;
    struct rt_audio_replay *replay;

    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_VOLUME:
        {
            break;
        }

        case AUDIO_MIXER_EXTEND:

        break;

        default:
            result = -RT_ERROR;
            break;
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

            i2s_dev->config.channels   = config.channels;
            i2s_dev->config.samplebits = config.samplebits;
            i2s_dev->config.samplerate = config.samplerate;

            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            break;
        }

        case AUDIO_DSP_CHANNELS:
        {
            break;
        }

        case AUDIO_DSP_SAMPLEBITS:
        {
            /* not support */
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }

        break;
    }

    default:
        break;
    }

    return result;
}

static rt_err_t i2s_init(struct rt_audio_device *audio)
{
    LOG_E("i2s_init");
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;
    FError ret = FT_SUCCESS;
    u32 word_length = i2s_dev->config.samplebits; /* 16-bits word length */

    FI2sCodecInit(word_length);
    if (FT_SUCCESS != ret)
    {
        printf("Init the escodec failed.\r\n");
        return ret;
    }
    ret = FI2sRxDdmaInit(i2s_dev);
    if (FT_SUCCESS != ret)
    {
        printf("Init DDMA-2 failed.\r\n");
        return ret;
    }
    ret = FI2sRxInit(i2s_dev, word_length);
    if (FI2S_SUCCESS != ret)
    {
        printf("Init the I2S failed.\r\n");
        return ret;
    }
    i2s_dev->rx_channel = 1;
    i2s_dev->tx_channel = 0;
    FDdmaSetupInterrupt(&i2s_dev->ddmac);
    FDdmaRegisterChanEvtHandler(&i2s_dev->ddmac, i2s_dev->rx_channel, FDDMA_CHAN_EVT_REQ_DONE, dma_rx_channel_transfer_callback, (void *)i2s_dev);
    FDdmaRegisterChanEvtHandler(&i2s_dev->ddmac, i2s_dev->tx_channel, FDDMA_CHAN_EVT_REQ_DONE, dma_tx_channel_transfer_callback, (void *)i2s_dev);

    return ret;
}

static rt_err_t i2s_start(struct rt_audio_device *audio, int stream)
{
    LOG_E("i2s_start");
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;

    if (stream == AUDIO_STREAM_REPLAY)
    {
        LOG_E("stream == AUDIO_STREAM_REPLAY");
        FI2sDdmaDeviceTX(i2s_dev, FI2S_PCM_STREAM_PLAYBACK, i2s_dev->tx_fifo, TX_RX_BUF_LEN, PER_BUFFER_SIZE);
        FDdmaChanActive(&i2s_dev->ddmac, i2s_dev->tx_channel);
    }
    else if(stream == AUDIO_STREAM_RECORD)
    {
        LOG_E("stream == AUDIO_STREAM_RECORD");
        FI2sDdmaDeviceRX(i2s_dev, FI2S_PCM_STREAM_CAPTURE, i2s_dev->rx_fifo, TX_RX_BUF_LEN, PER_BUFFER_SIZE);
        FDdmaChanActive(&i2s_dev->ddmac, i2s_dev->rx_channel);
    }

    FDdmaStart(&i2s_dev->ddmac);

    return RT_EOK;
}

static rt_err_t i2s_stop(struct rt_audio_device *audio, int stream)
{
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;

    return RT_EOK;
}

static struct rt_audio_ops i2s_ops =
{
    .getcaps     = i2s_getcaps,
    .configure   = i2s_configure,
    .init        = i2s_init,
    .start       = i2s_start,
    .stop        = i2s_stop,
    .transmit    = NULL,
    .buffer_info = NULL,
};

static int i2s_controller_init(struct phytium_i2s_device *i2s_dev)
{
    struct rt_audio_device *audio = &i2s_dev->audio;

    i2s_dev->rx_fifo = trans_buf[0];
    if (i2s_dev->rx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    i2s_dev->tx_fifo = trans_buf[1];
    if (i2s_dev->tx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    i2s_dev->audio.ops = &i2s_ops;
    int ret = rt_audio_register(audio, i2s_dev->name, RT_DEVICE_FLAG_RDONLY, (void *)i2s_dev);
    RT_ASSERT(RT_EOK == ret);
    LOG_D("i2s_controller_init i2s bus reg success. \n");
    return ret;
}

int rt_hw_i2s_init(void)
{

#if defined(RT_USING_I2S0)
    i2s_dev0.name = "I2S0";
    i2s_dev0.i2s_ctrl.config.instance_id = FI2S0_ID;
    i2s_dev0.config.channels = 1;
    i2s_dev0.config.samplerate = RT_I2S_SAMPLERATE;
    i2s_dev0.config.samplebits = RT_I2S_SAMPLEBITS;

    i2s_controller_init(&i2s_dev0);
#endif

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_i2s_init);