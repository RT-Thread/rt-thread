/*
 * Copyright (c) 2022-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG              "i2s"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#ifdef BSP_USING_I2S
#include "hpm_i2s_drv.h"
#include "board.h"
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
#include "hpm_dmav2_drv.h"
#else
#include "hpm_dma_drv.h"
#endif
#include "hpm_dmamux_drv.h"
#include "hpm_l1c_drv.h"
#include "hpm_clock_drv.h"
#include "hpm_dma_mgr.h"

#include "drv_i2s.h"
#include "drivers/dev_audio.h"

static rt_ssize_t hpm_i2s_transmit(struct rt_audio_device* audio, const void* writeBuf, void* readBuf, rt_size_t size);

/**
 * I2S state
 */
typedef enum {
    hpm_i2s_state_stop,
    hpm_i2s_state_read,
    hpm_i2s_state_write,
} hpm_i2s_state_t;

struct hpm_i2s
{
    struct rt_audio_device audio;
    struct rt_audio_configure audio_config;
    dma_resource_t rx_dma_resource;
    dma_resource_t tx_dma_resource;
    char *dev_name;
    I2S_Type *base;
    clock_name_t clk_name;
    i2s_transfer_config_t transfer;
    uint8_t rx_dma_req;
    uint8_t tx_dma_req;
    rt_uint8_t* tx_buff;
    rt_uint8_t* rx_buff;
    hpm_i2s_state_t i2s_state;
};

#if defined(BSP_USING_I2S0)
ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t i2s0_tx_buff[I2S_FIFO_SIZE];
ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t i2s0_rx_buff[I2S_FIFO_SIZE];
#endif
#if defined(BSP_USING_I2S1)
ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t i2s1_tx_buff[I2S_FIFO_SIZE];
ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t i2s1_rx_buff[I2S_FIFO_SIZE];
#endif
#if defined(BSP_USING_I2S2)
ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t i2s2_tx_buff[I2S_FIFO_SIZE];
ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t i2s2_rx_buff[I2S_FIFO_SIZE];
#endif
#if defined(BSP_USING_I2S3)
ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t i2s3_tx_buff[I2S_FIFO_SIZE];
ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t i2s3_rx_buff[I2S_FIFO_SIZE];
#endif

static struct hpm_i2s hpm_i2s_set[] =
{
#if defined(BSP_USING_I2S0) && defined(HPM_I2S0)
    {
        .dev_name = "i2s0",
        .base = HPM_I2S0,
        .clk_name =  clock_i2s0,
        .rx_dma_req = HPM_DMA_SRC_I2S0_RX,
        .tx_dma_req = HPM_DMA_SRC_I2S0_TX,
        .tx_buff = i2s0_tx_buff,
        .rx_buff = i2s0_rx_buff,
    },
#endif
#if defined(BSP_USING_I2S1) && defined(HPM_I2S1)
    {
        .dev_name = "i2s1",
        .base = HPM_I2S1;
        .clk_name =  clock_i2s1,
        .rx_dma_req = HPM_DMA_SRC_I2S1_RX,
        .tx_dma_req = HPM_DMA_SRC_I2S1_TX,
        .tx_buff = i2s1_tx_buff,
        .rx_buff = i2s1_rx_buff,
    },
#endif
#if defined(BSP_USING_I2S2) && defined(HPM_I2S2)
    {
        .dev_name = "i2s2",
        .base = HPM_I2S2,
        .clk_name =  clock_i2s2,
        .rx_dma_req = HPM_DMA_SRC_I2S2_RX,
        .tx_dma_req = HPM_DMA_SRC_I2S2_TX,
        .tx_buff = i2s2_tx_buff,
        .rx_buff = i2s2_rx_buff,
    },
#endif
#if defined(BSP_USING_I2S3) && defined(HPM_I2S3)
    {
        .dev_name = "i2s3",
        .base = HPM_I2S3,
        .clk_name =  clock_i2s3,
        .rx_dma_req = HPM_DMA_SRC_I2S3_RX,
        .tx_dma_req = HPM_DMA_SRC_I2S3_TX,
        .tx_buff = i2s3_tx_buff,
        .rx_buff = i2s3_rx_buff,
    },
#endif
};

/* I2S TX DMA callback function: trigger next transfer */
void i2s_tx_dma_tc_callback(DMA_Type *ptr, uint32_t channel, void *user_data)
{
    struct hpm_i2s* hpm_audio = (struct hpm_i2s*) user_data;
    rt_audio_tx_complete(&hpm_audio->audio);
}

/* I2S RX DMA callback function: write data into record->pipe and trigger next transfer */
void i2s_rx_dma_tc_callback(DMA_Type *ptr, uint32_t channel, void *user_data)
{
    struct hpm_i2s* hpm_audio = (struct hpm_i2s*) user_data;
    rt_audio_rx_done(&hpm_audio->audio, hpm_audio->rx_buff, I2S_FIFO_SIZE);
    hpm_i2s_transmit(&hpm_audio->audio, NULL, hpm_audio->rx_buff, I2S_FIFO_SIZE);
}


static rt_err_t hpm_i2s_init(struct rt_audio_device* audio)
{
    RT_ASSERT(audio != RT_NULL);
    rt_uint32_t mclk_hz;
    i2s_config_t i2s_config;
    i2s_transfer_config_t transfer;

    struct hpm_i2s* hpm_audio = (struct hpm_i2s*)audio->parent.user_data;

    init_i2s_pins(hpm_audio->base);
    board_init_i2s_clock(hpm_audio->base);

    /* enable dma request */
    i2s_enable_rx_dma_request(hpm_audio->base);
    i2s_enable_tx_dma_request(hpm_audio->base);

    i2s_get_default_config(hpm_audio->base, &i2s_config);
    i2s_config.enable_mclk_out = true;
    i2s_init(hpm_audio->base, &i2s_config);

    mclk_hz = clock_get_frequency(hpm_audio->clk_name);
    i2s_get_default_transfer_config(&transfer);
    /* init I2S parameter */
    transfer.sample_rate = 48000U;
    transfer.protocol = I2S_PROTOCOL_LEFT_JUSTIFIED;
    transfer.channel_slot_mask = I2S_CHANNEL_SLOT_MASK(0); /* one channel */
    transfer.audio_depth = i2s_audio_depth_16_bits;
    transfer.master_mode = true;
    hpm_audio->transfer = transfer;
    /* record i2s parameter to audio_config */
    hpm_audio->audio_config.samplerate = 48000U;
    hpm_audio->audio_config.samplebits = 16;
    hpm_audio->audio_config.channels = 1;
    if (status_success != i2s_config_transfer(hpm_audio->base, mclk_hz, &transfer))
    {
        LOG_E("dao_i2s configure transfer failed\n");
        return -RT_ERROR;
    }

    hpm_audio->i2s_state = hpm_i2s_state_stop;

    return RT_EOK;
}

static rt_err_t hpm_i2s_getcaps(struct rt_audio_device* audio, struct rt_audio_caps* caps)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(audio != RT_NULL);
    struct hpm_i2s* hpm_audio = (struct hpm_i2s*)audio->parent.user_data;

    switch(caps->main_type)
    {
        case AUDIO_TYPE_INPUT:
        {
            switch(caps->sub_type)
            {
                case AUDIO_DSP_PARAM:
                {
                    caps->udata.config.channels     = hpm_audio->audio_config.channels;
                    caps->udata.config.samplebits   = hpm_audio->audio_config.samplebits;
                    caps->udata.config.samplerate   = hpm_audio->audio_config.samplerate;
                    break;
                }

                case AUDIO_DSP_SAMPLERATE:
                {
                    caps->udata.config.samplerate   = hpm_audio->audio_config.samplerate;
                    break;
                }

                case AUDIO_DSP_CHANNELS:
                {
                    caps->udata.config.channels     = hpm_audio->audio_config.channels;
                    break;
                }

                case AUDIO_DSP_SAMPLEBITS:
                {
                    caps->udata.config.samplebits   = hpm_audio->audio_config.samplebits;
                    break;
                }

                case AUDIO_PARM_I2S_DATA_LINE:
                {
                    caps->udata.value               = hpm_audio->transfer.data_line;
                    break;
                }

                default:
                {
                    result = -RT_ERROR;
                    break;
                }
            }
            break;
        }
        case AUDIO_TYPE_OUTPUT:
        {
            switch(caps->sub_type)
            {
                case AUDIO_DSP_PARAM:
                {
                    caps->udata.config.samplerate   = hpm_audio->audio_config.samplerate;
                    caps->udata.config.channels     = hpm_audio->audio_config.channels;
                    caps->udata.config.samplebits   = hpm_audio->audio_config.samplebits;
                    break;
                }

                case AUDIO_DSP_SAMPLERATE:
                {
                    caps->udata.config.samplerate   = hpm_audio->audio_config.samplerate;
                    break;
                }

                case AUDIO_DSP_CHANNELS:
                {
                    caps->udata.config.channels     = hpm_audio->audio_config.channels;
                    break;
                }

                case AUDIO_DSP_SAMPLEBITS:
                {
                    caps->udata.config.samplebits   = hpm_audio->audio_config.samplebits;
                    break;
                }

                case AUDIO_PARM_I2S_DATA_LINE:
                {
                    caps->udata.value               = hpm_audio->transfer.data_line;
                    break;
                }

                default:
                {
                    result = -RT_ERROR;
                    break;
                }
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

static rt_err_t hpm_i2s_configure(struct rt_audio_device* audio, struct rt_audio_caps* caps)
{
    rt_err_t result = RT_EOK;
    RT_ASSERT(audio != RT_NULL);
    struct hpm_i2s* hpm_audio = (struct hpm_i2s*)audio->parent.user_data;

    switch(caps->main_type)
    {
        case AUDIO_TYPE_OUTPUT:
        {
            switch(caps->sub_type)
            {
            case AUDIO_DSP_PARAM:
            {
                hpm_audio->audio_config.samplerate = caps->udata.config.samplerate;
                hpm_audio->audio_config.samplebits = caps->udata.config.samplebits;
                hpm_audio->audio_config.channels = caps->udata.config.channels;
                break;
            }

            case AUDIO_DSP_SAMPLERATE:
            {
                hpm_audio->audio_config.samplerate = caps->udata.config.samplerate;
                break;
            }

            case AUDIO_DSP_CHANNELS:
            {
                hpm_audio->audio_config.channels = caps->udata.config.channels;
                break;
            }

            case AUDIO_DSP_SAMPLEBITS:
            {
                hpm_audio->audio_config.samplebits = caps->udata.config.samplebits;
                break;
            }

            case AUDIO_PARM_I2S_DATA_LINE:
            {
                hpm_audio->transfer.data_line      = caps->udata.value;
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
                hpm_audio->audio_config.samplerate = caps->udata.config.samplerate;
                hpm_audio->audio_config.channels   = caps->udata.config.channels;
                hpm_audio->audio_config.samplebits = caps->udata.config.samplebits;
                break;
            }

            case AUDIO_DSP_SAMPLERATE:
            {
                hpm_audio->audio_config.samplerate = caps->udata.config.samplerate;
                break;
            }
            case AUDIO_DSP_CHANNELS:
            {
                hpm_audio->audio_config.channels = caps->udata.config.channels;
                break;
            }

            case AUDIO_DSP_SAMPLEBITS:
            {
                hpm_audio->audio_config.samplebits = caps->udata.config.samplebits;
                break;
            }

            case AUDIO_PARM_I2S_DATA_LINE:
            {
                hpm_audio->transfer.data_line      = caps->udata.value;
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

    /* configure I2S transfer */
    if (hpm_audio->audio_config.channels == i2s_mono_left) {
        hpm_audio->transfer.channel_slot_mask = I2S_CHANNEL_SLOT_MASK(0);
    } else if (hpm_audio->audio_config.channels == i2s_mono_right) {
        hpm_audio->transfer.channel_slot_mask = I2S_CHANNEL_SLOT_MASK(1);
    } else if(hpm_audio->audio_config.channels == 2) {
        hpm_audio->transfer.channel_slot_mask = I2S_CHANNEL_SLOT_MASK(0) | I2S_CHANNEL_SLOT_MASK(1);
    } else {
        LOG_E("I2S not support channels number %d.\n", hpm_audio->audio_config.channels);
        return -RT_ERROR;
    }

    hpm_audio->transfer.sample_rate = hpm_audio->audio_config.samplerate;

    /* i2s dma only support sample bit: 16 and 32 bits */
    assert(hpm_audio->audio_config.samplebits == 16 || hpm_audio->audio_config.samplebits == 32);
    hpm_audio->transfer.audio_depth = hpm_audio->audio_config.samplebits;

    /* Stop I2S transfer if the I2S needs to be re-configured */
    bool is_enabled = i2s_is_enabled(hpm_audio->base);
    if (is_enabled)
    {
        if (hpm_audio->i2s_state == hpm_i2s_state_read)
        {
            dma_abort_channel(hpm_audio->rx_dma_resource.base, hpm_audio->rx_dma_resource.channel);
        }
        if (hpm_audio->i2s_state == hpm_i2s_state_write)
        {
            dma_abort_channel(hpm_audio->tx_dma_resource.base, hpm_audio->tx_dma_resource.channel);
        }
    }
    if (status_success != i2s_config_transfer(hpm_audio->base, clock_get_frequency(hpm_audio->clk_name), &hpm_audio->transfer))
    {
        LOG_E("%s configure transfer failed.\n", hpm_audio->dev_name);
        return -RT_ERROR;
    }
    /* Restore I2S to previous state */
    if (is_enabled)
    {
        i2s_enable(hpm_audio->base);
    }

    return result;
}

static rt_err_t hpm_i2s_start(struct rt_audio_device* audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    struct hpm_i2s* hpm_audio = (struct hpm_i2s*)audio->parent.user_data;

    /*  request DMA resource for audio data transfer */
    if (stream == AUDIO_STREAM_REPLAY) {
        i2s_disable(hpm_audio->base);
        i2s_disable_tx_dma_request(hpm_audio->base);
        dma_resource_t *dma_resource = &hpm_audio->tx_dma_resource;
        if (dma_mgr_request_resource(dma_resource) == status_success) {
            uint8_t dmamux_ch;
            dma_mgr_install_chn_tc_callback(dma_resource, i2s_tx_dma_tc_callback, hpm_audio);
            dma_mgr_enable_dma_irq_with_priority(dma_resource, 1);
            dmamux_ch = DMA_SOC_CHN_TO_DMAMUX_CHN(dma_resource->base, dma_resource->channel);
            dmamux_config(HPM_DMAMUX, dmamux_ch, hpm_audio->tx_dma_req, true);
        } else {
            LOG_E("no dma resource available for I2S TX transfer.\n");
            return -RT_ERROR;
        }
        i2s_reset_tx(hpm_audio->base); /* disable and reset tx */
        /* fill 2 dummy data, it is suitable for 1/2 channel of audio */
        if (i2s_fill_tx_dummy_data(hpm_audio->base, hpm_audio->transfer.data_line , 2) != status_success) {
            return -RT_ERROR;
        }
        rt_audio_tx_complete(audio);
        i2s_enable(hpm_audio->base);
        i2s_enable_tx_dma_request(hpm_audio->base);
    } else if (stream == AUDIO_STREAM_RECORD) {
        i2s_disable(hpm_audio->base);
        i2s_disable_rx_dma_request(hpm_audio->base);
        dma_resource_t *dma_resource = &hpm_audio->rx_dma_resource;
        if (dma_mgr_request_resource(dma_resource) == status_success) {
            uint8_t dmamux_ch;
            dma_mgr_install_chn_tc_callback(dma_resource, i2s_rx_dma_tc_callback, hpm_audio);
            dma_mgr_enable_dma_irq_with_priority(dma_resource, 1);
            dmamux_ch = DMA_SOC_CHN_TO_DMAMUX_CHN(dma_resource->base, dma_resource->channel);
            dmamux_config(HPM_DMAMUX, dmamux_ch, hpm_audio->rx_dma_req, true);
        } else {
            LOG_E("no dma resource available for I2S RX transfer.\n");
            return -RT_ERROR;
        }
        i2s_reset_rx(hpm_audio->base); /* disable and reset rx */
        if (I2S_FIFO_SIZE != hpm_i2s_transmit(&hpm_audio->audio, NULL, hpm_audio->rx_buff, I2S_FIFO_SIZE)) {
            return -RT_ERROR;
        }
        i2s_enable(hpm_audio->base);
        i2s_enable_rx_dma_request(hpm_audio->base);
    } else {
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t hpm_i2s_stop(struct rt_audio_device* audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);
    struct hpm_i2s* hpm_audio = (struct hpm_i2s*)audio->parent.user_data;

    i2s_disable(hpm_audio->base);

    if (stream == AUDIO_STREAM_REPLAY) {
        dma_resource_t *dma_resource = &hpm_audio->tx_dma_resource;
        dma_abort_channel(dma_resource->base, dma_resource->channel);
        dma_mgr_release_resource(dma_resource);
    } else if (stream == AUDIO_STREAM_RECORD)
    {
        dma_resource_t *dma_resource = &hpm_audio->rx_dma_resource;
        dma_abort_channel(dma_resource->base, dma_resource->channel);
        dma_mgr_release_resource(dma_resource);
    } else {
        return -RT_ERROR;
    }

    hpm_audio->i2s_state = hpm_i2s_state_stop;

    return RT_EOK;
}

static rt_ssize_t hpm_i2s_transmit(struct rt_audio_device* audio, const void* writeBuf, void* readBuf, rt_size_t size)
{
    RT_ASSERT(audio != RT_NULL);
    struct hpm_i2s* hpm_audio = (struct hpm_i2s*)audio->parent.user_data;

    /* i2s dma only support sample bit: 16 and 32 bits */
    uint8_t data_width;
    uint8_t data_shift_byte;
    if (hpm_audio->transfer.audio_depth == i2s_audio_depth_16_bits) {
        data_width = DMA_TRANSFER_WIDTH_HALF_WORD;
        data_shift_byte = 2U ; /* put 16bit data on high bit of register */
    } else {
        data_width = DMA_TRANSFER_WIDTH_WORD;
        data_shift_byte = 0U;
    }

    if(writeBuf != RT_NULL)
    {
        dma_resource_t *dma_resource = &hpm_audio->tx_dma_resource;
        dma_channel_config_t ch_config = {0};
        dma_default_channel_config(dma_resource->base, &ch_config);
        ch_config.src_addr = core_local_mem_to_sys_address(HPM_CORE0, (uint32_t)writeBuf);
        ch_config.dst_addr = (uint32_t)&hpm_audio->base->TXD[hpm_audio->transfer.data_line] + data_shift_byte;
        ch_config.src_width = data_width;
        ch_config.dst_width = data_width;
        ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
        ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        ch_config.size_in_byte = size;
        ch_config.dst_mode = DMA_HANDSHAKE_MODE_HANDSHAKE;
        ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;

        if (l1c_dc_is_enabled()) {
            /* cache writeback for sent buff */
            l1c_dc_writeback((uint32_t)writeBuf, size);
        }

        hpm_audio->i2s_state = hpm_i2s_state_write;
        if (status_success != dma_setup_channel(dma_resource->base, dma_resource->channel, &ch_config, true)) {
            LOG_E("dma setup channel failed\n");
            return -RT_ERROR;
        }
    } else if (readBuf != RT_NULL){
        dma_resource_t *dma_resource = &hpm_audio->rx_dma_resource;
        dma_channel_config_t ch_config = {0};
        dma_default_channel_config(dma_resource->base, &ch_config);
        ch_config.src_addr = (uint32_t)&hpm_audio->base->RXD[hpm_audio->transfer.data_line] + data_shift_byte;
        ch_config.dst_addr = core_local_mem_to_sys_address(HPM_CORE0, (uint32_t)readBuf);
        ch_config.src_width = data_width;
        ch_config.dst_width = data_width;
        ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
        ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
        ch_config.size_in_byte = size;
        ch_config.src_mode = DMA_HANDSHAKE_MODE_HANDSHAKE;
        ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;

        hpm_audio->i2s_state = hpm_i2s_state_read;
        if (status_success != dma_setup_channel(dma_resource->base, dma_resource->channel, &ch_config, true)) {
            LOG_E("dma setup channel failed\n");
            return -RT_ERROR;
        }

        if (l1c_dc_is_enabled()) {
            /* cache invalidate for receive buff */
            l1c_dc_invalidate((uint32_t)readBuf, size);
        }
    }

    return size;
}

static void hpm_i2s_buffer_info(struct rt_audio_device* audio, struct rt_audio_buf_info* info)
{
    RT_ASSERT(audio != RT_NULL);
    struct hpm_i2s* hpm_audio = (struct hpm_i2s*)audio->parent.user_data;
    /**
     *               AUD_FIFO
     * +----------------+----------------+
     * |     block1     |     block2     |
     * +----------------+----------------+
     *  \  block_size  /
     */
    info->buffer      = hpm_audio->tx_buff;
    info->total_size  = I2S_FIFO_SIZE;
    info->block_size  = I2S_FIFO_SIZE / 2;
    info->block_count = 2;
}


static struct rt_audio_ops hpm_i2s_ops =
{
    .getcaps     = hpm_i2s_getcaps,
    .configure   = hpm_i2s_configure,
    .init        = hpm_i2s_init,
    .start       = hpm_i2s_start,
    .stop        = hpm_i2s_stop,
    .transmit    = hpm_i2s_transmit,
    .buffer_info = hpm_i2s_buffer_info,
};

int rt_hw_i2s_init(void)
{
    rt_err_t ret = RT_EOK;

    for (uint32_t i = 0; i < sizeof(hpm_i2s_set) / sizeof(hpm_i2s_set[0]); i++) {
        hpm_i2s_set[i].audio.ops = &hpm_i2s_ops;

        ret = rt_audio_register(&hpm_i2s_set[i].audio, hpm_i2s_set[i].dev_name, RT_DEVICE_FLAG_RDWR, &hpm_i2s_set[i]);

        if (ret != RT_EOK)
        {
            LOG_E("rt audio %s register failed, status=%d\n", hpm_i2s_set[i].dev_name, ret);
        }

    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2s_init);


#endif /* BSP_USING_I2S */
