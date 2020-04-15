/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-11-17     LiWeiHao     First implementation
 */

#include "drv_mic.h"
#include "fsl_common.h"
#include "fsl_iocon.h"
#include "fsl_dmic.h"
#include "fsl_dma.h"
#include "fsl_dmic_dma.h"

struct mic_device
{
    dma_handle_t dma_handle;
    dmic_dma_handle_t dmic_dma_handle;
    struct rt_audio_device audio;
    struct rt_audio_configure config;
    rt_uint8_t *rx_fifo;
};

#define DMAREQ_DMIC0 16U
#define DMAREQ_DMIC1 17U
#define DMAREQ_CHANNEL DMAREQ_DMIC0
#define DMIC_CHANNEL kDMIC_Channel0
#define DMIC_CHANNEL_ENABLE DMIC_CHANEN_EN_CH0(1)
#define FIFO_DEPTH 15U

#define RX_DMA_FIFO_SIZE (2048)

struct mic_device mic_dev;

void dmic_dma_transfer_callback(DMIC_Type *base,
                                dmic_dma_handle_t *handle,
                                status_t status,
                                void *userData)
{
    struct mic_device *mic_dev = (struct mic_device *)userData;
    rt_audio_rx_done(&mic_dev->audio, &mic_dev->rx_fifo[0], RX_DMA_FIFO_SIZE);
    dmic_transfer_t dmic_transfer;
    dmic_transfer.data = (uint16_t *)&mic_dev->rx_fifo[0];
    dmic_transfer.dataSize = RX_DMA_FIFO_SIZE / 2;
    DMIC_TransferReceiveDMA(DMIC0, &mic_dev->dmic_dma_handle, &dmic_transfer, kDMIC_Channel0);
}

rt_err_t mic_device_init(struct rt_audio_device *audio)
{
    dmic_channel_config_t dmic_channel_cfg;

    CLOCK_EnableClock(kCLOCK_Iocon);
    CLOCK_EnableClock(kCLOCK_InputMux);
    CLOCK_EnableClock(kCLOCK_Gpio0);

    IOCON_PinMuxSet(IOCON, 1, 16, IOCON_FUNC1 | IOCON_DIGITAL_EN);
    IOCON_PinMuxSet(IOCON, 1, 15, IOCON_FUNC1 | IOCON_DIGITAL_EN);

    CLOCK_AttachClk(kFRO12M_to_DMIC);
    CLOCK_SetClkDiv(kCLOCK_DivDmicClk, 14, false);

    dmic_channel_cfg.divhfclk = kDMIC_PdmDiv1;
    dmic_channel_cfg.osr = 25U;
    dmic_channel_cfg.gainshft = 2U;
    dmic_channel_cfg.preac2coef = kDMIC_CompValueZero;
    dmic_channel_cfg.preac4coef = kDMIC_CompValueZero;
    dmic_channel_cfg.dc_cut_level = kDMIC_DcCut155;
    dmic_channel_cfg.post_dc_gain_reduce = 1;
    dmic_channel_cfg.saturate16bit = 1U;
    dmic_channel_cfg.sample_rate = kDMIC_PhyFullSpeed;
    DMIC_Init(DMIC0);

    DMIC_ConfigIO(DMIC0, kDMIC_PdmDual);
    DMIC_Use2fs(DMIC0, true);
    DMIC_SetOperationMode(DMIC0, kDMIC_OperationModeDma);
    DMIC_ConfigChannel(DMIC0, DMIC_CHANNEL, kDMIC_Left, &dmic_channel_cfg);

    DMIC_FifoChannel(DMIC0, DMIC_CHANNEL, FIFO_DEPTH, true, true);

    DMIC_EnableChannnel(DMIC0, DMIC_CHANNEL_ENABLE);

    DMA_EnableChannel(DMA0, DMAREQ_CHANNEL);

    /* Request dma channels from DMA manager. */
    DMA_CreateHandle(&mic_dev.dma_handle, DMA0, DMAREQ_CHANNEL);

    /* Create DMIC DMA handle. */
    DMIC_TransferCreateHandleDMA(DMIC0,
                                 &mic_dev.dmic_dma_handle,
                                 dmic_dma_transfer_callback,
                                 (void *)&mic_dev,
                                 &mic_dev.dma_handle);
    return RT_EOK;
}

rt_err_t mic_device_start(struct rt_audio_device *audio, int stream)
{
    struct mic_device *mic_dev = (struct mic_device *)audio->parent.user_data;
    if (stream == AUDIO_STREAM_RECORD)
    {
        dmic_transfer_t dmic_transfer;
        dmic_transfer.data = (uint16_t *)&mic_dev->rx_fifo[0];
        dmic_transfer.dataSize = RX_DMA_FIFO_SIZE / 2;
        DMIC_TransferReceiveDMA(DMIC0, &mic_dev->dmic_dma_handle, &dmic_transfer, kDMIC_Channel0);
    }
    return RT_EOK;
}

rt_err_t mic_device_stop(struct rt_audio_device *audio, int stream)
{
    struct mic_device *mic_dev = (struct mic_device *)audio->parent.user_data;
    if (stream == AUDIO_STREAM_RECORD)
    {
        DMIC_TransferAbortReceiveDMA(DMIC0, &mic_dev->dmic_dma_handle);
    }
    return RT_EOK;
}

rt_err_t mic_device_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    return RT_EOK;
}

rt_err_t mic_device_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    return RT_EOK;
}

static struct rt_audio_ops _mic_audio_ops =
{
    .getcaps     = mic_device_getcaps,
    .configure   = mic_device_configure,
    .init        = mic_device_init,
    .start       = mic_device_start,
    .stop        = mic_device_stop,
    .transmit    = RT_NULL,
    .buffer_info = RT_NULL,
};

int rt_hw_mic_init(void)
{
    struct rt_audio_device *audio = &mic_dev.audio;
    /* mic default */
    mic_dev.rx_fifo = rt_calloc(1, RX_DMA_FIFO_SIZE);
    if (mic_dev.rx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    mic_dev.config.channels = 1;
    mic_dev.config.samplerate = 16000;
    mic_dev.config.samplebits = 16;

    /* register mic device */
    audio->ops = &_mic_audio_ops;
    rt_audio_register(audio, "mic0", RT_DEVICE_FLAG_RDONLY, (void *)&mic_dev);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_mic_init);