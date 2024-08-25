/*
 * Copyright (c) 2022 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG              "pdm"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#ifdef BSP_USING_PDM
#include "board.h"
#include "drivers/dev_audio.h"
#include "hpm_i2s_drv.h"
#include "hpm_pdm_drv.h"
#include "drv_pdm.h"
#ifdef HPMSOC_HAS_HPMSDK_DMAV2
#include "hpm_dmav2_drv.h"
#else
#include "hpm_dma_drv.h"
#endif
#include "hpm_dmamux_drv.h"
#include "hpm_l1c_drv.h"
#include "hpm_dma_mgr.h"


/* PDM connect to I2S0 RX */
#define PDM_DMA_REQ          HPM_DMA_SRC_I2S0_RX
#define PDM_I2S_DATA_LINE    0

struct hpm_pdm
{
    struct rt_audio_device audio;
    struct rt_audio_configure record_config;
    rt_uint8_t* rx_fifo;
};

struct hpm_pdm hpm_pdm_dev = { 0 };
static dma_resource_t dma_resource = { 0 };
static rt_err_t hpm_pdm_dma_transmit();


void pdm_dma_tc_callback(DMA_Type *ptr, uint32_t channel, void *user_data)
{
    rt_audio_rx_done(&hpm_pdm_dev.audio, hpm_pdm_dev.rx_fifo, PDM_FIFO_SIZE);
    hpm_pdm_dma_transmit();
}

static rt_err_t hpm_pdm_getcaps(struct rt_audio_device* audio, struct rt_audio_caps* caps)
{
    rt_err_t result = RT_EOK;

    RT_ASSERT(audio != RT_NULL);
    struct hpm_pdm* hpm_audio = (struct hpm_pdm*)audio->parent.user_data;

    switch(caps->main_type)
    {
        case AUDIO_TYPE_INPUT:
        {
            switch(caps->sub_type)
            {
            case AUDIO_DSP_PARAM:
                caps->udata.config.samplerate   = hpm_audio->record_config.samplerate;
                caps->udata.config.channels     = hpm_audio->record_config.channels;
                caps->udata.config.samplebits   = hpm_audio->record_config.samplebits;
                break;

            case AUDIO_DSP_SAMPLERATE:
                caps->udata.config.samplerate   = hpm_audio->record_config.samplerate;
                break;

            case AUDIO_DSP_CHANNELS:
                caps->udata.config.channels     = hpm_audio->record_config.channels;
                break;

            case AUDIO_DSP_SAMPLEBITS:
                caps->udata.config.samplebits   = hpm_audio->record_config.samplebits;
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

static rt_err_t hpm_pdm_set_channels(uint32_t channel)
{
    uint32_t mclk_hz;
    i2s_transfer_config_t transfer;

    mclk_hz = clock_get_frequency(clock_i2s0);
    i2s_get_default_transfer_config_for_pdm(&transfer);
    transfer.data_line = PDM_I2S_DATA_LINE;
    if (channel == 1) {
        transfer.channel_slot_mask = BOARD_PDM_SINGLE_CHANNEL_MASK;
    } else if(channel == 2) {
        transfer.channel_slot_mask = BOARD_PDM_DUAL_CHANNEL_MASK;
    } else {
        LOG_E("PDM not support channels number %d.\n", channel);
        return -RT_ERROR;
    }

    bool is_enabled = i2s_is_enabled(PDM_I2S);
    if (is_enabled) {
        dma_abort_channel(dma_resource.base, dma_resource.channel);
    }
    if (status_success != i2s_config_rx(PDM_I2S, mclk_hz, &transfer))
    {
        LOG_E("pdm_i2s configure transfer failed\n");
        return -RT_ERROR;
    }
    if (is_enabled)
    {
        i2s_enable(PDM_I2S);
    }

    return RT_EOK;
}

static rt_err_t hpm_pdm_configure(struct rt_audio_device* audio, struct rt_audio_caps* caps)
{

    rt_err_t result = RT_EOK;
    RT_ASSERT(audio != RT_NULL);

    struct hpm_pdm* hpm_audio = (struct hpm_pdm*)audio->parent.user_data;

    switch(caps->main_type)
    {
        case AUDIO_TYPE_INPUT:
        {
            switch(caps->sub_type)
            {
                case AUDIO_DSP_CHANNELS:
                {
                    hpm_audio->record_config.channels = caps->udata.config.channels;
                    hpm_pdm_set_channels(caps->udata.config.channels);
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


static rt_err_t hpm_pdm_init(struct rt_audio_device* audio)
{
    RT_ASSERT(audio != RT_NULL);

    i2s_config_t i2s_config;
    i2s_transfer_config_t transfer;
    pdm_config_t pdm_config;

    init_pdm_pins();
    board_init_pdm_clock();

    i2s_get_default_config(PDM_I2S, &i2s_config);
    i2s_enable_rx_dma_request(PDM_I2S);
    i2s_init(PDM_I2S, &i2s_config);

    i2s_get_default_transfer_config_for_pdm(&transfer);
    transfer.data_line = PDM_I2S_DATA_LINE;
    transfer.channel_slot_mask = BOARD_PDM_SINGLE_CHANNEL_MASK;
    if (status_success != i2s_config_rx(PDM_I2S, clock_get_frequency(clock_i2s0), &transfer))
    {
        LOG_E("pdm_i2s configure receive failed\n");
        return -RT_ERROR;
    }

    /* init audio configure */
    hpm_pdm_dev.record_config.channels = 1U;
    hpm_pdm_dev.record_config.samplebits = 32U; /* the actual significant bit is 24 bits, and the low bit is 0  */
    hpm_pdm_dev.record_config.samplerate = PDM_SOC_SAMPLE_RATE_IN_HZ; /* fix 16KHz */

    pdm_get_default_config(HPM_PDM, &pdm_config);
    if (status_success != pdm_init(HPM_PDM, &pdm_config)) {
        LOG_E("pdm init failed\n");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t hpm_pdm_start(struct rt_audio_device* audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);
    struct hpm_pdm* hpm_audio = (struct hpm_pdm*)audio->parent.user_data;

    if (stream == AUDIO_STREAM_RECORD)
    {
        i2s_disable(PDM_I2S);
        i2s_disable_rx_dma_request(PDM_I2S);
        pdm_stop(HPM_PDM);
        pdm_software_reset(HPM_PDM);

        if (dma_mgr_request_resource(&dma_resource) == status_success) {
            uint8_t dmamux_ch;
            dma_mgr_install_chn_tc_callback(&dma_resource, pdm_dma_tc_callback, NULL);
            dma_mgr_enable_dma_irq_with_priority(&dma_resource, 1);
            dmamux_ch = DMA_SOC_CHN_TO_DMAMUX_CHN(dma_resource.base, dma_resource.channel);
            dmamux_config(HPM_DMAMUX, dmamux_ch, PDM_DMA_REQ, true);
        } else {
            LOG_E("no dma resource available for PDM transfer.\n");
            return -RT_ERROR;
        }

        i2s_reset_rx(PDM_I2S);
        if (RT_EOK != hpm_pdm_dma_transmit()) {
            return -RT_ERROR;
        }

        pdm_start(HPM_PDM);
        i2s_enable_rx_dma_request(PDM_I2S);
        i2s_start(PDM_I2S);
    }

    return RT_EOK;
}

static rt_err_t hpm_pdm_stop(struct rt_audio_device* audio, int stream)
{
    RT_ASSERT(audio != RT_NULL);

    if (stream == AUDIO_STREAM_RECORD) {
        pdm_stop(HPM_PDM);
        i2s_stop(PDM_I2S);

        dma_abort_channel(dma_resource.base, dma_resource.channel);
        dma_mgr_release_resource(&dma_resource);
    }

    return RT_EOK;
}

static rt_err_t hpm_pdm_dma_transmit()
{
    dma_channel_config_t ch_config = {0};
    dma_default_channel_config(dma_resource.base, &ch_config);
    ch_config.src_addr = (uint32_t)&PDM_I2S->RXD[PDM_I2S_DATA_LINE];
    ch_config.dst_addr = core_local_mem_to_sys_address(HPM_CORE0, (uint32_t)hpm_pdm_dev.rx_fifo);
    ch_config.src_width = DMA_TRANSFER_WIDTH_WORD;
    ch_config.dst_width = DMA_TRANSFER_WIDTH_WORD;
    ch_config.src_addr_ctrl = DMA_ADDRESS_CONTROL_FIXED;
    ch_config.dst_addr_ctrl = DMA_ADDRESS_CONTROL_INCREMENT;
    ch_config.size_in_byte = PDM_FIFO_SIZE;
    ch_config.src_mode = DMA_HANDSHAKE_MODE_HANDSHAKE;
    ch_config.src_burst_size = DMA_NUM_TRANSFER_PER_BURST_1T;

    if (status_success != dma_setup_channel(dma_resource.base, dma_resource.channel, &ch_config, true)) {
        LOG_E("dma setup channel failed\n");
        return -RT_ERROR;
    }

    if (l1c_dc_is_enabled()) {
        /* cache invalidate for receive buff */
        l1c_dc_invalidate((uint32_t)hpm_pdm_dev.rx_fifo, PDM_FIFO_SIZE);
    }

    return RT_EOK;
}


static struct rt_audio_ops hpm_pdm_ops =
{
    .getcaps     = hpm_pdm_getcaps,
    .configure   = hpm_pdm_configure,
    .init        = hpm_pdm_init,
    .start       = hpm_pdm_start,
    .stop        = hpm_pdm_stop,
    .transmit    = NULL,
    .buffer_info = NULL,
};

ATTR_ALIGN(HPM_L1C_CACHELINE_SIZE) uint8_t pdm_rx_fifo[PDM_FIFO_SIZE];

int rt_hw_pdm_init(void)
{
    hpm_pdm_dev.rx_fifo = pdm_rx_fifo;

    hpm_pdm_dev.audio.ops = &hpm_pdm_ops;

    LOG_I("audio pdm registered.\n");
    LOG_I("!!!Note: pdm depends on i2s0, they share clock.\n");
    rt_audio_register(&hpm_pdm_dev.audio, "pdm", RT_DEVICE_FLAG_RDONLY, &hpm_pdm_dev);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_pdm_init);

#endif /* BSP_USING_PDM */
