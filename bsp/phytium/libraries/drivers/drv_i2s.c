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

#define TX_RX_BUF_LEN            2048

static rt_uint8_t trans_buf[2][TX_RX_BUF_LEN] __attribute__((aligned(FDDMA_DDR_ADDR_ALIGNMENT))) = {0};

static FDdmaBdlDesc *bdl_desc_list_tx = NULL;
static FDdmaBdlDesc *bdl_desc_list_rx = NULL;

struct phytium_i2s_device
{
    const char *name;
    struct rt_audio_device audio;
    struct rt_audio_configure config;

    u32 i2s_ctrl_id;
    FI2s i2s_ctrl;
    FI2sConfig i2s_config;

    u32 ddma_ctrl_id;
    FDdma ddmac;
    FDdmaConfig ddmac_config;
    FDdmaChanConfig rx_config;
    FDdmaChanConfig tx_config;

    rt_uint8_t rx_channel; /* 接收通道为DDMA通道1 */
    rt_uint8_t tx_channel; /* 接收通道为DDMA通道1 */
};

static struct phytium_i2s_device i2s_dev0;

static void FDdmaSetupInterrupt(FDdma *const instance)
{
    FASSERT(instance);
    FDdmaConfig *config = &instance->config;

    rt_uint32_t cpu_id = rt_hw_cpu_id();
    rt_hw_interrupt_set_target_cpus(config->irq_num, cpu_id);
    rt_hw_interrupt_set_priority(config->irq_num, config->irq_priority);
    rt_hw_interrupt_install(config->irq_num, FDdmaIrqHandler, instance, NULL);
    rt_hw_interrupt_umask(config->irq_num);

    return;
}

static FError i2s_ddma_init(struct phytium_i2s_device *i2s_dev, u32 word_length, u32 samplerate)
{
    LOG_E("i2s_ddma_init");
    FError ret = FI2S_SUCCESS;
    /*Init i2s*/
    FIOPadSetI2sMux();
    i2s_dev->i2s_ctrl.data_config.word_length = word_length;
    i2s_dev->i2s_config = *FI2sLookupConfig(i2s_dev->i2s_ctrl_id);
    ret = FI2sCfgInitialize(&i2s_dev->i2s_ctrl, &i2s_dev->i2s_config);
    if (FI2S_SUCCESS != ret)
    {
        printf("Init the i2s failed.\r\n");
        return ret;
    }
    FI2sClkOutDiv(&i2s_dev->i2s_ctrl, samplerate);

    /*Init ddma*/
    i2s_dev->ddmac_config = *FDdmaLookupConfig(i2s_dev->ddma_ctrl_id);
    ret = FDdmaCfgInitialize(&i2s_dev->ddmac, &i2s_dev->ddmac_config);
    if (FI2S_SUCCESS != ret)
    {
        printf("DDMA config initialization failed.\r\n");
        return ret;
    }
    FDdmaSetupInterrupt(&i2s_dev->ddmac);

    return ret;
}

static FError FI2sDdmaDeviceRX(struct phytium_i2s_device *i2s_dev, uintptr src, fsize_t total_bytes, fsize_t per_buff_len)
{
    FError ret = FI2S_SUCCESS;
    fsize_t bdl_num = total_bytes / per_buff_len;

    rt_hw_cpu_dcache_clean(src, total_bytes);

    for (u32 chan = FDDMA_CHAN_0; chan < FDDMA_NUM_OF_CHAN; chan++)
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

    for (fsize_t loop = 0; loop < bdl_num; loop++)
    {
        bdl_desc_config[loop].current_desc_num = loop;
        bdl_desc_config[loop].src_addr = (uintptr)(src + per_buff_len * loop);
        bdl_desc_config[loop].trans_length = per_buff_len;
    }
    bdl_desc_config[bdl_num - 1].ioc = TRUE;

    for (fsize_t loop = 0; loop < bdl_num; loop++)
    {
        FDdmaBDLSetDesc(bdl_desc_list_rx, &bdl_desc_config[loop]);
    }

    i2s_dev->rx_config.slave_id = 0U;
    i2s_dev->rx_config.req_mode = FI2S_PCM_STREAM_CAPTURE;
    i2s_dev->rx_config.ddr_addr = src;
    i2s_dev->rx_config.dev_addr = i2s_dev->i2s_config.base_addr + FI2S_RXDMA;
    i2s_dev->rx_config.trans_len = total_bytes;
    i2s_dev->rx_config.timeout = 0xffff;
    i2s_dev->rx_config.first_desc_addr = (uintptr)bdl_desc_list_rx;
    i2s_dev->rx_config.valid_desc_num = bdl_num;

    ret = FDdmaChanBdlConfigure(&i2s_dev->ddmac, i2s_dev->rx_channel, &i2s_dev->rx_config);

    if (ret != FI2S_SUCCESS)
    {
        printf("DDMA BDL configure failer.\r\n");
        return ret;
    }
    rt_free(bdl_desc_config);

    return ret;
}

static FError FI2sDdmaDeviceTX(struct phytium_i2s_device *i2s_dev, uintptr src, fsize_t total_bytes, fsize_t per_buff_len)
{
    FError ret = FI2S_SUCCESS;
    fsize_t bdl_num = total_bytes / per_buff_len;

    rt_hw_cpu_dcache_clean(src, total_bytes);
    for (u32 chan = FDDMA_CHAN_0; chan < FDDMA_NUM_OF_CHAN; chan++)
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

    for (fsize_t loop = 0; loop < bdl_num; loop++)
    {
        bdl_desc_config[loop].current_desc_num = loop;
        bdl_desc_config[loop].src_addr = (uintptr)(src + per_buff_len * loop);
        bdl_desc_config[loop].trans_length = per_buff_len;
    }
    bdl_desc_config[bdl_num - 1].ioc = TRUE;

    for (fsize_t loop = 0; loop < bdl_num; loop++)
    {
        FDdmaBDLSetDesc(bdl_desc_list_tx, &bdl_desc_config[loop]);
    }

    i2s_dev->tx_config.slave_id = 0U;
    i2s_dev->tx_config.req_mode = FI2S_PCM_STREAM_PLAYBACK;
    i2s_dev->tx_config.ddr_addr = src;
    i2s_dev->tx_config.dev_addr = i2s_dev->i2s_config.base_addr + FI2S_TXDMA;
    i2s_dev->tx_config.trans_len = total_bytes;
    i2s_dev->tx_config.timeout = 0xffff;
    i2s_dev->tx_config.first_desc_addr = (uintptr)bdl_desc_list_tx;
    i2s_dev->tx_config.valid_desc_num = bdl_num;

    ret = FDdmaChanBdlConfigure(&i2s_dev->ddmac, i2s_dev->tx_channel, &i2s_dev->tx_config);

    if (ret != FI2S_SUCCESS)
    {
        printf("DDMA BDL configure failer.\r\n");
        return ret;
    }
    rt_free(bdl_desc_config);

    return ret;
}


void dma_rx_channel_transfer_callback(FDdmaChanIrq *irq, void *args)
{
    int i;
    rt_uint16_t *pcm = (rt_uint16_t *)trans_buf[1];

    rt_audio_rx_done(&i2s_dev0.audio, trans_buf[1], TX_RX_BUF_LEN);
    FI2sDdmaDeviceRX(&i2s_dev0, trans_buf[1], TX_RX_BUF_LEN, TX_RX_BUF_LEN);

}

void dma_tx_channel_transfer_callback(FDdmaChanIrq *irq, void *args)
{
    LOG_E("dma_tx_channel_transfer_callback");
    rt_audio_tx_complete(&i2s_dev0.audio);
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
            // caps->udata.value = i2s_dev->volume;
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
    if (caps->main_type == AUDIO_TYPE_OUTPUT)
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_SAMPLERATE:
            // i2s_set_sample_rate(caps->udata.value);
            break;
        case AUDIO_DSP_CHANNELS:
            // i2s_set_channels(caps->udata.value);
            break;
        case AUDIO_DSP_SAMPLEBITS:
            // i2s_set_sample_bits(caps->udata.value);
            break;
        }
    }
    else if (caps->main_type == AUDIO_TYPE_MIXER)
    {
        if (caps->sub_type == AUDIO_MIXER_VOLUME)
        {
            // codec_set_volume(caps->udata.value); /* 音量控制通过CODEC实现 */
        }
    }
    return RT_EOK;
}

static rt_err_t i2s_start(struct rt_audio_device *audio, int stream)
{
    LOG_E("i2s_start");
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;
    LOG_E("i2s_dev = %x", i2s_dev->i2s_ctrl.config.base_addr);
    i2s_dev->rx_channel = 1;
    i2s_dev->tx_channel = 0;
    FI2sTxRxEnable(&i2s_dev->i2s_ctrl, TRUE); /* 模块使能 */

    if (stream == AUDIO_STREAM_REPLAY)
    {
        

    }
    else if(stream == AUDIO_STREAM_RECORD)
    {
        rt_uint8_t *rx_buf = trans_buf[1];
        FI2sDdmaDeviceRX(i2s_dev, (uintptr)rx_buf, TX_RX_BUF_LEN, TX_RX_BUF_LEN);
        FDdmaRegisterChanEvtHandler(&i2s_dev->ddmac, i2s_dev->rx_channel, FDDMA_CHAN_EVT_REQ_DONE, dma_rx_channel_transfer_callback, i2s_dev);
        FDdmaChanActive(&i2s_dev->ddmac, i2s_dev->rx_channel);
        FDdmaStart(&i2s_dev->ddmac);
    }
    return RT_EOK;
}

static rt_err_t i2s_stop(struct rt_audio_device *audio, int stream)
{
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;

    return RT_EOK;
}

static rt_err_t i2s_init(struct rt_audio_device* audio)
{
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;
    i2s_ddma_init(i2s_dev, 16, 16000);

    return RT_EOK;
}

static rt_ssize_t i2s_ddma_transmit(struct rt_audio_device *audio, const void *writeBuf, void *readBuf, rt_size_t size)
{
    LOG_E("i2s_ddma_transmit");
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;
    if (writeBuf != RT_NULL)
    {
        rt_memcpy(trans_buf[0], writeBuf, size);
        /* Playback: 复制数据到当前 ping/pong 缓冲区并启动 DDMA */
        FI2sDdmaDeviceTX(&i2s_dev0, trans_buf[0], size, size);
        FDdmaRegisterChanEvtHandler(&i2s_dev->ddmac, i2s_dev->tx_channel, FDDMA_CHAN_EVT_REQ_DONE, dma_tx_channel_transfer_callback, i2s_dev);
        FDdmaChanActive(&i2s_dev->ddmac, i2s_dev->tx_channel);
        FDdmaStart(&i2s_dev->ddmac);
    }

    return size;
}

static struct rt_audio_ops i2s_ops =
{
    .getcaps     = i2s_getcaps,
    .configure   = i2s_configure,
    .init        = i2s_init,
    .start       = i2s_start,
    .stop        = i2s_stop,
    .transmit    = i2s_ddma_transmit,
    .buffer_info = NULL,
};

static int i2s_controller_init(struct phytium_i2s_device *i2s_dev)
{
    struct rt_audio_device *audio = &i2s_dev->audio;
    i2s_dev->audio.ops = &i2s_ops;
    int ret = rt_audio_register(audio, i2s_dev->name, RT_DEVICE_FLAG_RDWR, (void *)i2s_dev);
    RT_ASSERT(RT_EOK == ret);
    LOG_D("i2s_controller_init i2s bus reg success. \n");
    return ret;
}

int rt_hw_i2s_init(void)
{
    i2s_dev0.name = "I2S0";
    i2s_dev0.config.channels = 1;
    i2s_dev0.config.samplerate = RT_I2S_SAMPLERATE;
    i2s_dev0.config.samplebits = RT_I2S_SAMPLEBITS;
    i2s_dev0.ddma_ctrl_id = FDDMA2_I2S_ID;
    i2s_dev0.i2s_ctrl_id = FI2S0_ID;

    i2s_controller_init(&i2s_dev0);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_i2s_init);