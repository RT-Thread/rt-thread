/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG              "dao"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#ifdef BSP_USING_DAO
#include "drivers/dev_audio.h"
#include "hpm_i2s_drv.h"
#include "hpm_dao_drv.h"
#include "board.h"
#include "drv_dao.h"
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
#include "hpm_dmav2_drv.h"
#else
#include "hpm_dma_drv.h"
#endif
#include "hpm_dmamux_drv.h"
#include "hpm_l1c_drv.h"
#include "hpm_clock_drv.h"
#include "hpm_dma_mgr.h"

/* DAO connect to I2S1 TX*/
#define DAO_DMA_REQ          HPM_DMA_SRC_I2S1_TX
#define DAO_I2S_DATA_LINE    0

struct hpm_dao
{
    struct rt_audio_device audio;
    struct rt_audio_configure play_config;
    rt_uint8_t* tx_fifo;
};

struct hpm_dao hpm_dao_dev = { 0 };
static dma_resource_t dma_resource = { 0 };

void dao_dma_tc_callback(DMA_Type *ptr, uint32_t channel, void *user_data)
{
    rt_audio_tx_complete(&hpm_dao_dev.audio);
}

static rt_err_t hpm_dao_getcaps(struct rt_audio_device* audio, struct rt_audio_caps* caps)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(audio != RT_NULL);
    struct hpm_dao* hpm_audio = (struct hpm_dao*)audio->parent.user_data;

    switch(caps->main_type)
    {
        case AUDIO_TYPE_OUTPUT:
        {
            switch(caps->sub_type)
            {
            case AUDIO_DSP_PARAM:
                caps->udata.config.samplerate   = hpm_audio->play_config.samplerate;
                caps->udata.config.channels     = hpm_audio->play_config.channels;
                caps->udata.config.samplebits   = hpm_audio->play_config.samplebits;
                break;

            case AUDIO_DSP_SAMPLERATE:
                caps->udata.config.samplerate   = hpm_audio->play_config.samplerate;
                break;

            case AUDIO_DSP_CHANNELS:
                caps->udata.config.channels     = hpm_audio->play_config.channels;
                break;

            case AUDIO_DSP_SAMPLEBITS:
                caps->udata.config.samplebits   = hpm_audio->play_config.samplebits;
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

static bool i2s_is_enabled(I2S_Type *ptr)
{
    return ((ptr->CTRL & I2S_CTRL_I2S_EN_MASK) != 0);
}

static rt_err_t hpm_dao_set_samplerate(uint32_t samplerate)
{
    uint32_t mclk_hz;
    i2s_transfer_config_t transfer;

    mclk_hz = clock_get_frequency(clock_i2s1);
    i2s_get_default_transfer_config_for_dao(&transfer);
    transfer.sample_rate = samplerate;
    bool is_enabled = i2s_is_enabled(DAO_I2S);
    if (is_enabled) {
        dma_abort_channel(dma_resource.base, dma_resource.channel);
    }
    if (status_success != i2s_config_tx(DAO_I2S, mclk_hz, &transfer))
    {
        LOG_E("dao_i2s configure transfer failed\n");
        return -RT_ERROR;
    }
    if (is_enabled)
    {
        i2s_enable(DAO_I2S);
    }

    return RT_EOK;
}

static rt_err_t hpm_dao_configure(struct rt_audio_device* audio, struct rt_audio_caps* caps)
{

    rt_err_t result = RT_EOK;
    RT_ASSERT(audio != RT_NULL);

    struct hpm_dao* hpm_audio = (struct hpm_dao*)audio->parent.user_data;

    switch(caps->main_type)
    {
        case AUDIO_TYPE_OUTPUT:
        {
            switch(caps->sub_type)
            {
                case AUDIO_DSP_SAMPLERATE:
                {
                    hpm_audio->play_config.samplerate = caps->udata.config.samplerate;
                    hpm_dao_set_samplerate(caps->udata.config.samplerate);
                    break;
                }

                default:
                    result = -RT_ERROR;
                    break;
            }
        }

        default:
            result = -RT_ERROR;
            break;
    }
    return result;
}

static rt_err_t hpm_dao_init(struct rt_audio_device* audio)
{
    RT_ASSERT(audio != RT_NULL);
    rt_uint32_t mclk_hz;
    i2s_config_t i2s_config;
    i2s_transfer_config_t transfer;
    dao_config_t dao_config;

    init_dao_pins();
    board_init_dao_clock();

    i2s_get_default_config(DAO_I2S, &i2s_config);
    i2s_init(DAO_I2S, &i2s_config);
    i2s_enable_tx_dma_request(DAO_I2S);

    mclk_hz = clock_get_frequency(clock_i2s1);
    i2s_get_default_transfer_config_for_dao(&transfer);
    if (status_success != i2s_config_tx(DAO_I2S, mclk_hz, &transfer))
    {
        LOG_E("dao_i2s configure transfer failed\n");
        return -RT_ERROR;
    }

    /* init audio configure */
    hpm_dao_dev.play_config.channels = 2U; /* fix to 2 channels*/
    hpm_dao_dev.play_config.samplebits = 32U; /* fix to 32 sample bits */
    hpm_dao_dev.play_config.samplerate = 48000U; /* default 48KHz sample rate */

    dao_get_default_config(HPM_DAO, &dao_config);
    dao_config.enable_mono_output = true;
    if (status_success != dao_init(HPM_DAO, &dao_config)) {
        LOG_E("dao init failed\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t hpm_dao_start(struct rt_audio_device* audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    i2s_disable(DAO_I2S);
    i2s_disable_tx_dma_request(DAO_I2S);
    dao_stop(HPM_DAO);
    dao_software_reset(HPM_DAO);

    if (dma_mgr_request_resource(&dma_resource) == status_success) {
        uint8_t dmamux_ch;
        dma_mgr_install_chn_tc_callback(&dma_resource, dao_dma_tc_callback, NULL);
        dma_mgr_enable_dma_irq_with_priority(&dma_resource, 1);
        dmamux_ch = DMA_SOC_CHN_TO_DMAMUX_CHN(dma_resource.base, dma_resource.channel);
        dmamux_config(HPM_DMAMUX, dmamux_ch, DAO_DMA_REQ, true);
    } else {
        LOG_E("no dma resource available for DAO transfer.\n");
        return -RT_ERROR;
    }

    /* fill 2 dummy data, it is suitable for 1/2 channel of audio */
    i2s_reset_tx(DAO_I2S);
    if (i2s_fill_tx_dummy_data(DAO_I2S, DAO_I2S_DATA_LINE, 2) != status_success) {
        return -RT_ERROR;
    }
    rt_audio_tx_complete(audio);
    i2s_enable(DAO_I2S);
    i2s_enable_tx_dma_request(DAO_I2S);
    dao_start(HPM_DAO);

    return RT_EOK;
}

static rt_err_t hpm_dao_stop(struct rt_audio_device* audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    dao_stop(HPM_DAO);
    i2s_stop(DAO_I2S);

    dma_abort_channel(dma_resource.base, dma_resource.channel);
    dma_mgr_release_resource(&dma_resource);

    return RT_EOK;
}

static rt_ssize_t hpm_dao_transmit(struct rt_audio_device* audio, const void* writeBuf, void* readBuf, rt_size_t size)
{
    RT_ASSERT(audio != RT_NULL);

    dma_channel_config_t ch_config = {0};
    dma_default_channel_config(dma_resource.base, &ch_config);
    ch_config.src_addr = core_local_mem_to_sys_address(HPM_CORE0, (uint32_t)writeBuf);
    ch_config.dst_addr = (uint32_t)&DAO_I2S->TXD[DAO_I2S_DATA_LINE];
    ch_config.src_width = DMA_TRANSFER_WIDTH_WORD;
    ch_config.dst_width = DMA_TRANSFER_WIDTH_WORD;
    ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
    ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
    ch_config.size_in_byte = size;
    ch_config.dst_mode = DMA_HANDSHAKE_MODE_HANDSHAKE;
    ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;

    if (l1c_dc_is_enabled()) {
        /* cache writeback for sent buff */
        l1c_dc_writeback((uint32_t)writeBuf, size);
    }

    if (status_success != dma_setup_channel(dma_resource.base, dma_resource.channel, &ch_config, true)) {
        return 0;
    }

    return size;
}

static void hpm_dao_buffer_info(struct rt_audio_device* audio, struct rt_audio_buf_info* info)
{
    RT_ASSERT(audio != RT_NULL);
    /**
     *               AUD_FIFO
     * +----------------+----------------+
     * |     block1     |     block2     |
     * +----------------+----------------+
     *  \  block_size  /
     */
    info->buffer      = hpm_dao_dev.tx_fifo;
    info->total_size  = DAO_FIFO_SIZE;
    info->block_size  = DAO_FIFO_SIZE / 2;
    info->block_count = 2;
}

static struct rt_audio_ops hpm_dao_ops =
{
    .getcaps     = hpm_dao_getcaps,
    .configure   = hpm_dao_configure,
    .init        = hpm_dao_init,
    .start       = hpm_dao_start,
    .stop        = hpm_dao_stop,
    .transmit    = hpm_dao_transmit,
    .buffer_info = hpm_dao_buffer_info,
};

ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t dao_tx_fifo[DAO_FIFO_SIZE];

int rt_hw_dao_init(void)
{
    hpm_dao_dev.tx_fifo = dao_tx_fifo;

    hpm_dao_dev.audio.ops = &hpm_dao_ops;

    LOG_I("audio dao registered.\n");
    LOG_I("!!!Note: dao depends on i2s1, they share clock.\n");
    rt_audio_register(&hpm_dao_dev.audio, "dao", RT_DEVICE_FLAG_WRONLY, &hpm_dao_dev);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_dao_init);


#endif /* BSP_USING_DAO */
