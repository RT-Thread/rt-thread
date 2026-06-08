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
#include "fio_mux.h"
#include "cache.h"
#define DBG_TAG              "drv.i2s"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_SMART
    #include "ioremap.h"
#endif

#define TX_RX_BUF_LEN        RT_AUDIO_REPLAY_MP_BLOCK_SIZE
static rt_uint8_t trans_buf[2][TX_RX_BUF_LEN  * 4] __attribute__((aligned(FDDMA_DDR_ADDR_ALIGNMENT))) = {0};
static FDdmaBdlDesc *bdl_desc_list_tx = NULL;
static FDdmaBdlDesc *bdl_desc_list_rx = NULL;
static rt_sem_t tx_done_sem = RT_NULL;
static rt_thread_t audio_tx_thread = RT_NULL;
static rt_thread_t audio_wdg_thread = RT_NULL;
static volatile rt_bool_t audio_running = RT_FALSE;

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
    FError ret = FI2S_SUCCESS;
    /*Init i2s*/
    FIOPadSetI2sMux();
    if (i2s_dev->i2s_ctrl.is_ready != FT_COMPONENT_IS_READY)
    {
        i2s_dev->i2s_ctrl.data_config.word_length = word_length;
        i2s_dev->i2s_config = *FI2sLookupConfig(i2s_dev->i2s_ctrl_id);
#ifdef RT_USING_SMART
        i2s_dev->i2s_config.base_addr = (uintptr)rt_ioremap((void *)i2s_dev->i2s_config.base_addr, 0xd00);
#endif
        ret = FI2sCfgInitialize(&i2s_dev->i2s_ctrl, &i2s_dev->i2s_config);
        if (FI2S_SUCCESS != ret)
        {
            printf("Init the i2s failed.\r\n");
            return ret;
        }
        FI2sClkOutDiv(&i2s_dev->i2s_ctrl, samplerate);
    }
    if (i2s_dev->ddmac.is_ready != FT_COMPONENT_IS_READY)
    {
        /*Init ddma*/
        i2s_dev->ddmac_config = *FDdmaLookupConfig(i2s_dev->ddma_ctrl_id);
#ifdef RT_USING_SMART
        i2s_dev->ddmac_config.base_addr = (uintptr)rt_ioremap((void *)i2s_dev->ddmac_config.base_addr, 0x1000);
#endif
        ret = FDdmaCfgInitialize(&i2s_dev->ddmac, &i2s_dev->ddmac_config);

        if (FI2S_SUCCESS != ret)
        {
            printf("DDMA config initialization failed.\r\n");
            return ret;
        }
        FDdmaSetupInterrupt(&i2s_dev->ddmac);
    }
    return ret;
}

static FError FI2sDdmaDeviceRX(struct phytium_i2s_device *i2s_dev, uintptr src, fsize_t total_bytes, fsize_t per_buff_len)
{
    FError ret = FI2S_SUCCESS;
    fsize_t bdl_num = total_bytes / per_buff_len;

    rt_hw_cpu_dcache_invalidate((void *)src, total_bytes);
#ifdef RT_USING_SMART
    src = (uintptr)rt_kmem_v2p((void *)src);
#endif
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
#ifdef RT_USING_SMART
    i2s_dev->rx_config.dev_addr = (uintptr)rt_kmem_v2p((void *)i2s_dev->i2s_config.base_addr) + FI2S_RXDMA;
#else
    i2s_dev->rx_config.dev_addr = i2s_dev->i2s_config.base_addr + FI2S_RXDMA;
#endif
    i2s_dev->rx_config.trans_len = total_bytes;
    i2s_dev->rx_config.timeout = 0xffff;
#ifdef RT_USING_SMART
    i2s_dev->rx_config.first_desc_paddr = (uintptr)rt_kmem_v2p(bdl_desc_list_rx);
#else
    i2s_dev->rx_config.first_desc_paddr = (uintptr)bdl_desc_list_rx;
#endif
    i2s_dev->rx_config.first_desc_vaddr = (uintptr)bdl_desc_list_rx;
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

    rt_hw_cpu_dcache_invalidate((void *)src, total_bytes);

#ifdef RT_USING_SMART
    src = (uintptr)rt_kmem_v2p((void *)src);
#endif
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

#ifdef RT_USING_SMART
    i2s_dev->tx_config.dev_addr = (uintptr)rt_kmem_v2p((void *)i2s_dev->i2s_config.base_addr) + FI2S_TXDMA;
#else
    i2s_dev->tx_config.dev_addr = i2s_dev->i2s_config.base_addr + FI2S_TXDMA;
#endif

    i2s_dev->tx_config.trans_len = total_bytes;
    i2s_dev->tx_config.timeout = 0xffff;

#ifdef RT_USING_SMART
    i2s_dev->tx_config.first_desc_paddr = (uintptr)rt_kmem_v2p(bdl_desc_list_tx);
#else
    i2s_dev->tx_config.first_desc_paddr = (uintptr)bdl_desc_list_tx;
#endif
    i2s_dev->tx_config.first_desc_vaddr = (uintptr)bdl_desc_list_tx;
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
    struct phytium_i2s_device *i2s_dev = (struct phytium_i2s_device *)args;
    rt_audio_rx_done(&i2s_dev->audio,
                     trans_buf[i2s_dev->rx_channel],
                     TX_RX_BUF_LEN);

    FI2sDdmaDeviceRX(i2s_dev,
                     (uintptr)trans_buf[i2s_dev->rx_channel],
                     TX_RX_BUF_LEN,
                     TX_RX_BUF_LEN);
}

void dma_tx_channel_transfer_callback(FDdmaChanIrq *irq, void *args)
{
    rt_sem_release(tx_done_sem);
}

static rt_err_t i2s_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
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
            caps->udata.config.samplerate   = i2s_dev->config.samplerate;
            caps->udata.config.channels     = i2s_dev->config.channels;
            caps->udata.config.samplebits   = i2s_dev->config.samplebits;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = caps->udata.config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = caps->udata.config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits   = caps->udata.config.samplebits;
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

static void i2s_set_word_length(struct phytium_i2s_device *dev, rt_uint32_t bits)
{
    switch (bits)
    {
    case 16:
        dev->i2s_ctrl.data_config.word_length =
            FI2S_PCM_STREAM_WORD_LENGTH_16;
        break;

    case 24:
        dev->i2s_ctrl.data_config.word_length =
            FI2S_PCM_STREAM_WORD_LENGTH_24;
        break;

    case 32:
        dev->i2s_ctrl.data_config.word_length =
            FI2S_PCM_STREAM_WORD_LENGTH_32;
        break;

    default:
        dev->i2s_ctrl.data_config.word_length =
            FI2S_PCM_STREAM_WORD_LENGTH_16;
        break;
    }
}

static rt_err_t i2s_configure(struct rt_audio_device *audio,
                               struct rt_audio_caps *caps)
{
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;
    if (caps->main_type == AUDIO_TYPE_OUTPUT)
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            i2s_dev->config.samplerate = caps->udata.config.samplerate;
            i2s_dev->config.samplebits = caps->udata.config.samplebits;
            i2s_dev->config.channels = caps->udata.config.channels;
            i2s_set_word_length(i2s_dev, caps->udata.config.samplebits);
            break;
        case AUDIO_DSP_SAMPLERATE:
            i2s_dev->config.samplerate = caps->udata.config.samplerate;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            i2s_dev->config.samplebits = caps->udata.config.samplebits;
            i2s_set_word_length(i2s_dev, caps->udata.config.samplebits);

            break;

        case AUDIO_DSP_CHANNELS:
            /* TODO */
            break;

        default:
            break;
        }
        FI2sClkOutDiv(&i2s_dev->i2s_ctrl, i2s_dev->config.samplerate);

    }
    else if (caps->main_type == AUDIO_TYPE_MIXER)
    {
        if (caps->sub_type == AUDIO_MIXER_VOLUME)
        {
            /* TODO */
        }
    }

    return RT_EOK;
}

static rt_err_t i2s_start(struct rt_audio_device *audio, int stream)
{
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;
    i2s_ddma_init(i2s_dev, FI2S_PCM_STREAM_WORD_LENGTH_16, FI2S_SAMPLE_RATE_CD);
    i2s_dev->rx_channel = 1;
    i2s_dev->tx_channel = 0;
    FI2sTxRxEnable(&i2s_dev->i2s_ctrl, TRUE); /* 模块使能 */
    audio_running = RT_TRUE;

    if (stream == AUDIO_STREAM_REPLAY)
    {
        FDdmaRegisterChanEvtHandler(&i2s_dev->ddmac, i2s_dev->tx_channel, FDDMA_CHAN_EVT_REQ_DONE, dma_tx_channel_transfer_callback, i2s_dev);

    }
    else if(stream == AUDIO_STREAM_RECORD)
    {
        rt_uint8_t *rx_buf = trans_buf[i2s_dev->rx_channel];
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
    audio_running = RT_FALSE;
    if (i2s_dev->i2s_ctrl.is_ready == FT_COMPONENT_IS_READY)
    {
        FI2sStopWork(&i2s_dev->i2s_ctrl);
        FI2sDeInitialize(&i2s_dev->i2s_ctrl);
    }
    if (i2s_dev->ddmac.is_ready == FT_COMPONENT_IS_READY)
    {
        FDdmaStop(&i2s_dev->ddmac);
        FDdmaDisableChanIrq(i2s_dev->ddmac.config.base_addr, i2s_dev->rx_channel, i2s_dev->ddmac.config.caps);
        FDdmaDisableChanIrq(i2s_dev->ddmac.config.base_addr, i2s_dev->tx_channel, i2s_dev->ddmac.config.caps);
        FDdmaDeInitialize(&i2s_dev->ddmac);
    }

    if (bdl_desc_list_tx)
    {
        rt_free(bdl_desc_list_tx);
        bdl_desc_list_tx = NULL;
    }
    if (bdl_desc_list_rx)
    {
        rt_free(bdl_desc_list_rx);
        bdl_desc_list_rx = NULL;
    }

    rt_data_queue_reset(&audio->replay->queue);
    return RT_EOK;
}

static rt_err_t i2s_init(struct rt_audio_device* audio)
{
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;
    i2s_ddma_init(i2s_dev, FI2S_PCM_STREAM_WORD_LENGTH_16, FI2S_SAMPLE_RATE_CD);

    return RT_EOK;
}

static void audio_tx_thread_entry(void *parameter)
{
    struct rt_audio_device *audio = parameter;
    struct phytium_i2s_device *i2s_dev;
    RT_ASSERT(audio != RT_NULL);
    i2s_dev = (struct phytium_i2s_device *)audio->parent.user_data;
    while (1)
    {
        if (!audio_running)
        {
            rt_thread_mdelay(20);
            continue;
        }
        rt_uint8_t *data = RT_NULL;
        rt_size_t size = 0;
        if (rt_data_queue_pop(&audio->replay->queue, (const void **)&data, &size, 100) == RT_EOK)
        {
            rt_memcpy(trans_buf[i2s_dev->tx_channel], data, size);
            FI2sDdmaDeviceTX(i2s_dev, (uintptr)trans_buf[i2s_dev->tx_channel], size, size);
            FDdmaChanActive(&i2s_dev->ddmac, i2s_dev->tx_channel);
            FDdmaStart(&i2s_dev->ddmac);
            rt_sem_take(tx_done_sem, 100);
            rt_mp_free(data);
        }
    }
}

static void audio_wdg_thread_entry(void *p)
{
    struct rt_audio_device *audio = p;
    while (1)
    {
        if (!audio_running)
        {
            rt_thread_mdelay(20);
            continue;
        }
        rt_thread_mdelay(10);
        if (audio->replay->event & 0x02)
        {
            rt_completion_done(&audio->replay->cmp);
        }
    }
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
    i2s_dev->audio.ops = &i2s_ops;
    if (audio_tx_thread == RT_NULL)
    {
        audio_tx_thread = rt_thread_create("audio_tx",
                                     audio_tx_thread_entry,
                                     audio,          // parameter
                                     4096,           // stack size
                                     20,             // priority
                                     10);            // tick
        if (audio_tx_thread)
            rt_thread_startup(audio_tx_thread);
    }
    if (audio_wdg_thread == RT_NULL)
    {
        audio_wdg_thread = rt_thread_create(
                                "audio_wdg",
                                audio_wdg_thread_entry,
                                audio,
                                2048,
                                15,
                                10);
        if (audio_wdg_thread)
            rt_thread_startup(audio_wdg_thread);
    }
    tx_done_sem = rt_sem_create("tx_done", 0, RT_IPC_FLAG_FIFO);

    int ret = rt_audio_register(audio, i2s_dev->name, RT_DEVICE_FLAG_RDWR, (void *)i2s_dev);
    RT_ASSERT(RT_EOK == ret);
    LOG_D("i2s_controller_init i2s bus reg success. \n");
    return ret;
}

#if defined(RT_USING_I2S0)
    static struct phytium_i2s_device i2s_dev0;
#endif

int rt_hw_i2s_init(void)
{

#if defined(RT_USING_I2S0)
    i2s_dev0.name = "I2S0";
    i2s_dev0.config.channels = 1;
    i2s_dev0.config.samplerate = FI2S_SAMPLE_RATE_CD;
    i2s_dev0.config.samplebits = FI2S_PCM_STREAM_WORD_LENGTH_16;
    i2s_dev0.ddma_ctrl_id = FDDMA2_I2S_ID;
    i2s_dev0.i2s_ctrl_id = FI2S0_ID;

    i2s_controller_init(&i2s_dev0);
#endif

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_i2s_init);