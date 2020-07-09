/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-28     Ernest         the first version
 */

#include "board.h"
#include "drv_mic.h"
#include "drv_wm8978.h"
#include "drv_sound.h"

#define DBG_TAG              "drv.mic"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#define CODEC_I2C_NAME ("i2c1")
#define RX_DMA_FIFO_SIZE (2048)

extern struct drv_sai _sai_a;
static struct drv_sai _sai_b = {0};

struct stm32_mic
{
    struct rt_i2c_bus_device *i2c_bus;
    struct rt_audio_device audio;
    struct rt_audio_configure config;
    rt_uint8_t *rx_fifo;
    rt_bool_t startup;
};
static struct stm32_mic _stm32_audio_record = {0};

static  rt_err_t SAIB_samplerate_set(rt_uint32_t freq)
{
    __HAL_SAI_DISABLE(&_sai_b.hsai);
    _sai_b.hsai.Init.AudioFrequency = freq;
    HAL_SAI_Init(&_sai_b.hsai);
    __HAL_SAI_ENABLE(&_sai_b.hsai);

    return RT_EOK;
}

void SAIB_channels_set(rt_uint16_t channels)
{
    if (channels == 2)
    {
        _sai_b.hsai.Init.MonoStereoMode = SAI_STEREOMODE;
    }
    else
    {
        _sai_b.hsai.Init.MonoStereoMode = SAI_MONOMODE;
    }
    __HAL_SAI_DISABLE(&_sai_b.hsai);
    HAL_SAI_Init(&_sai_b.hsai);
    __HAL_SAI_ENABLE(&_sai_b.hsai);
}

void SAIB_samplebits_set(rt_uint16_t samplebits)
{
    switch (samplebits)
    {
    case 16:
        _sai_b.hsai.Init.DataSize = SAI_DATASIZE_16;
        break;
    case 24:
        _sai_b.hsai.Init.DataSize = SAI_DATASIZE_24;
        break;
    case 32:
        _sai_b.hsai.Init.DataSize = SAI_DATASIZE_32;
        break;
    default:
        _sai_b.hsai.Init.DataSize = SAI_DATASIZE_16;
        break;
    }
    __HAL_SAI_DISABLE(&_sai_b.hsai);
    HAL_SAI_Init(&_sai_b.hsai);
    __HAL_SAI_ENABLE(&_sai_b.hsai);
}

void SAIB_config_set(struct rt_audio_configure config)
{
    SAIB_channels_set(config.channels);
    SAIB_samplerate_set(config.samplerate);
    SAIB_samplebits_set(config.samplebits);
}
		
static void SAIB_config_init()
{
    _sai_b.hsai.Instance = SAI1_Block_B;
    _sai_b.hsai.Init.AudioMode = SAI_MODESLAVE_RX;
    _sai_b.hsai.Init.Synchro = SAI_SYNCHRONOUS;
    _sai_b.hsai.Init.OutputDrive = SAI_OUTPUTDRIVE_ENABLE;
    _sai_b.hsai.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
    _sai_b.hsai.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_1QF;
    _sai_b.hsai.Init.ClockSource = SAI_CLKSOURCE_PLLI2S;
    _sai_b.hsai.Init.MonoStereoMode = SAI_STEREOMODE;
    _sai_b.hsai.Init.Protocol = SAI_FREE_PROTOCOL;
    _sai_b.hsai.Init.DataSize = SAI_DATASIZE_16;
    _sai_b.hsai.Init.FirstBit = SAI_FIRSTBIT_MSB;
    _sai_b.hsai.Init.ClockStrobing = SAI_CLOCKSTROBING_RISINGEDGE;

    /* frame */
    _sai_b.hsai.FrameInit.FrameLength = 64;
    _sai_b.hsai.FrameInit.ActiveFrameLength = 32;
    _sai_b.hsai.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
    _sai_b.hsai.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
    _sai_b.hsai.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT;

    /* slot */
    _sai_b.hsai.SlotInit.FirstBitOffset = 0;
    _sai_b.hsai.SlotInit.SlotSize = SAI_SLOTSIZE_32B;
    _sai_b.hsai.SlotInit.SlotNumber = 2;
    _sai_b.hsai.SlotInit.SlotActive = SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1;

    HAL_SAI_Init(&_sai_b.hsai);
    __HAL_SAI_ENABLE(&_sai_b.hsai);
}

static void SAIB_tx_dma(void)
{
    __HAL_RCC_DMA2_CLK_ENABLE();
    __HAL_LINKDMA(&_sai_b.hsai, hdmarx, _sai_b.hdma);
    _sai_b.hdma.Instance = DMA2_Stream5;
    _sai_b.hdma.Init.Channel = DMA_CHANNEL_0;
    _sai_b.hdma.Init.Direction = DMA_PERIPH_TO_MEMORY;
    _sai_b.hdma.Init.PeriphInc = DMA_PINC_DISABLE;
    _sai_b.hdma.Init.MemInc = DMA_MINC_ENABLE;
    _sai_b.hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    _sai_b.hdma.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
    _sai_b.hdma.Init.Mode = DMA_CIRCULAR;
    _sai_b.hdma.Init.Priority = DMA_PRIORITY_MEDIUM;
    _sai_b.hdma.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
    _sai_b.hdma.Init.MemBurst = DMA_MBURST_SINGLE;
    _sai_b.hdma.Init.PeriphBurst = DMA_PBURST_SINGLE;
    HAL_DMA_DeInit(&_sai_b.hdma);
    HAL_DMA_Init(&_sai_b.hdma);

    __HAL_DMA_DISABLE(&_sai_b.hdma);

    __HAL_DMA_CLEAR_FLAG(&_sai_b.hdma, DMA_FLAG_TCIF1_5);
    __HAL_DMA_ENABLE_IT(&_sai_b.hdma, DMA_IT_TC);

    HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, 5, 1);
    HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);
}

static rt_err_t sai_record_init()
{
    SAIA_config_init();
    SAIB_config_init();

    /* set record samplerate */
    SAIA_config_set(_stm32_audio_record.config);
    SAIB_config_set(_stm32_audio_record.config);
    SAIA_tx_dma();
    SAIB_tx_dma();

    return RT_EOK;
}

void DMA2_Stream5_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(_sai_b.hsai.hdmarx);
    rt_interrupt_leave();
}

void HAL_SAI_RxCpltCallback(SAI_HandleTypeDef *hsai)
{
    rt_audio_rx_done(&(_stm32_audio_record.audio), &_stm32_audio_record.rx_fifo[0], RX_DMA_FIFO_SIZE / 2);
}

void HAL_SAI_RxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{

    rt_audio_rx_done(&(_stm32_audio_record.audio), &_stm32_audio_record.rx_fifo[RX_DMA_FIFO_SIZE / 2], RX_DMA_FIFO_SIZE / 2);
}

static rt_err_t stm32_mic_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;

    LOG_D("%s:main_type: %d, sub_type: %d", __FUNCTION__, caps->main_type, caps->sub_type);

    switch (caps->main_type)
    {
    /* Provide capabilities of INTPUT unit */
    case AUDIO_TYPE_INPUT:
    {
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.channels     = _stm32_audio_record.config.channels;
            caps->udata.config.samplebits   = _stm32_audio_record.config.samplebits;
            caps->udata.config.samplerate   = _stm32_audio_record.config.samplerate;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = _stm32_audio_record.config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = _stm32_audio_record.config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits   = _stm32_audio_record.config.samplebits;
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

static void start_record_mode(void)
{
    rt_uint8_t temp[4] = {0};

    HAL_SAI_DMAStop(&_sai_b.hsai);
    HAL_SAI_Transmit(&_sai_a.hsai, temp, 4, 0);
    HAL_SAI_Receive_DMA(&_sai_b.hsai, _stm32_audio_record.rx_fifo, RX_DMA_FIFO_SIZE / 2);
}

static rt_err_t  stm32_mic_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;

    LOG_D("%s:main_type: %d, sub_type: %d", __FUNCTION__, caps->main_type, caps->sub_type);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_INPUT:
    {
        switch (caps->sub_type)
        {

        case AUDIO_DSP_PARAM:
        {
            _stm32_audio_record.config.samplerate = caps->udata.config.samplerate;
            _stm32_audio_record.config.channels   = caps->udata.config.channels;
            _stm32_audio_record.config.samplebits = caps->udata.config.samplebits;

            HAL_SAI_DMAStop(&_sai_b.hsai);
            SAIA_config_set(caps->udata.config);
            SAIB_config_set(caps->udata.config);
            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            _stm32_audio_record.config.samplerate = caps->udata.config.samplerate;
            SAIA_samplerate_set(caps->udata.config.samplerate);
            break;
        }
        case AUDIO_DSP_CHANNELS:
        {
            _stm32_audio_record.config.channels = caps->udata.config.channels;
            SAIA_channels_set(caps->udata.config.channels);
            SAIB_channels_set(caps->udata.config.channels);
            break;
        }

        case AUDIO_DSP_SAMPLEBITS:
        {
            _stm32_audio_record.config.samplebits = caps->udata.config.samplebits;
            SAIA_samplebits_set(caps->udata.config.samplebits);
            break;
        }

        default:
            result = -RT_ERROR;
            break;
        }
        /* After set config, MCLK will stop */
        start_record_mode();
        break;
    }

    default:
        break;
    }

    return result;
}

static rt_err_t stm32_mic_init(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;

    /* initialize wm8978 */
    _stm32_audio_record.i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(CODEC_I2C_NAME);
    if (_stm32_audio_record.i2c_bus != RT_NULL)
    {
        LOG_D("Find device i2c1 success");
    }
    else
    {
        LOG_E("Find device i2c1 error");
        return -RT_ERROR;
    }

    result = wm8978_init(_stm32_audio_record.i2c_bus);
    if (result != RT_EOK)
    {
        LOG_E("initialize wm8978 failed");
        return result;
    }

    sai_record_init();

    return RT_EOK;
}

static rt_err_t stm32_mic_start(struct rt_audio_device *audio, int stream)
{
    rt_err_t result = RT_EOK;

    if (stream == AUDIO_STREAM_RECORD)
    {
        /* set mic start */
        wm8978_record_start(_stm32_audio_record.i2c_bus);
        /* start transfer data */
        start_record_mode();
    }

    return result;
}

static rt_err_t stm32_mic_stop(struct rt_audio_device *audio, int stream)
{
    if (stream == AUDIO_STREAM_RECORD)
    {
        HAL_SAI_DMAStop(&_sai_b.hsai);
        HAL_SAI_DMAStop(&_sai_a.hsai);
        wm8978_mic_enabled(_stm32_audio_record.i2c_bus, 0);
    }

    return RT_EOK;
}

static struct rt_audio_ops _mic_audio_ops =
{
    .getcaps     = stm32_mic_getcaps,
    .configure   = stm32_mic_configure,
    .init        = stm32_mic_init,
    .start       = stm32_mic_start,
    .stop        = stm32_mic_stop,
    .transmit    = RT_NULL,
    .buffer_info = RT_NULL,
};

int rt_hw_mic_init(void)
{
    struct rt_audio_device *audio = &_stm32_audio_record.audio;
    /* mic default */
    _stm32_audio_record.rx_fifo = rt_calloc(1, RX_DMA_FIFO_SIZE);
    if (_stm32_audio_record.rx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }

    _stm32_audio_record.config.channels = 1;
    _stm32_audio_record.config.samplerate = 16000;
    _stm32_audio_record.config.samplebits = 16;

    /* register mic device */
    audio->ops = &_mic_audio_ops;
    rt_audio_register(audio, "mic0", RT_DEVICE_FLAG_RDONLY, &_stm32_audio_record);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_mic_init);
