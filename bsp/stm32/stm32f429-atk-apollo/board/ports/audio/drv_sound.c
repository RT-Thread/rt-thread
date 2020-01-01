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
#include "drv_wm8978.h"
#include "drv_sound.h"

#define DBG_TAG              "drv.sound"
#define DBG_LVL              DBG_INFO
#include <rtdbg.h>

#define	CODEC_I2C_NAME  ("i2c1")

#define TX_DMA_FIFO_SIZE (2048)

struct drv_sai _sai_a = {0};

struct stm32_audio
{
    struct rt_i2c_bus_device *i2c_bus;
    struct rt_audio_device audio;
    struct rt_audio_configure replay_config;
    int replay_volume;
    rt_uint8_t *tx_fifo;
    rt_bool_t startup;
};
struct stm32_audio _stm32_audio_play = {0};

/* sample_rate, PLLI2SN(50.7), PLLI2SQ, PLLI2SDivQ, MCKDIV */
const rt_uint32_t SAI_PSC_TBL[][5] =
{
    {AUDIO_FREQUENCY_048K, 206, 7, 0, 12},
    {AUDIO_FREQUENCY_044K, 257, 2, 18, 2},
    {AUDIO_FREQUENCY_032K, 206, 7, 0, 6},
    {AUDIO_FREQUENCY_022K, 257, 2, 18, 1},
    {AUDIO_FREQUENCY_016K, 206, 7, 0, 3},
    {AUDIO_FREQUENCY_011K, 257, 2, 18, 0},
    {AUDIO_FREQUENCY_008K, 206, 7, 0, 2},
};

void SAIA_samplerate_set(rt_uint32_t freq)
{
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    int i;
    
    /* check frequence */
    for (i = 0; i < (sizeof(SAI_PSC_TBL) / sizeof(SAI_PSC_TBL[0])); i++)
    {
        if ((freq) == SAI_PSC_TBL[i][0])break;
    }
    if (i == (sizeof(SAI_PSC_TBL) / sizeof(SAI_PSC_TBL[0])))
    {
        LOG_E("Can not support this frequence: %d.", freq);
        return;
    }
    
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SAI_PLLI2S;
    PeriphClkInitStruct.PLLI2S.PLLI2SN = SAI_PSC_TBL[i][1];
    PeriphClkInitStruct.PLLI2S.PLLI2SQ = SAI_PSC_TBL[i][2];
    PeriphClkInitStruct.PLLI2SDivQ = SAI_PSC_TBL[i][3] + 1;
    
    HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    __HAL_RCC_SAI_BLOCKACLKSOURCE_CONFIG(RCC_SAIACLKSOURCE_PLLI2S);

    __HAL_SAI_DISABLE(&_sai_a.hsai);
    _sai_a.hsai.Init.AudioFrequency = freq;
    HAL_SAI_Init(&_sai_a.hsai);
    __HAL_SAI_ENABLE(&_sai_a.hsai);
}

void SAIA_channels_set(rt_uint16_t channels)
{
    if (channels == 2)
    {
        _sai_a.hsai.Init.MonoStereoMode = SAI_STEREOMODE;
    }
    else
    {
        _sai_a.hsai.Init.MonoStereoMode = SAI_MONOMODE;
    }
    __HAL_SAI_DISABLE(&_sai_a.hsai);
    HAL_SAI_Init(&_sai_a.hsai);
    __HAL_SAI_ENABLE(&_sai_a.hsai);
}

void SAIA_samplebits_set(rt_uint16_t samplebits)
{
    switch (samplebits)
    {
    case 16:
        _sai_a.hsai.Init.DataSize = SAI_DATASIZE_16;
        break;
    case 24:
        _sai_a.hsai.Init.DataSize = SAI_DATASIZE_24;
        break;
    case 32:
        _sai_a.hsai.Init.DataSize = SAI_DATASIZE_32;
        break;
    default:
        _sai_a.hsai.Init.DataSize = SAI_DATASIZE_16;
        break;
    }
    __HAL_SAI_DISABLE(&_sai_a.hsai);
    HAL_SAI_Init(&_sai_a.hsai);
    __HAL_SAI_ENABLE(&_sai_a.hsai);
}

void SAIA_config_set(struct rt_audio_configure config)
{
    SAIA_channels_set(config.channels);
    SAIA_samplerate_set(config.samplerate);
    SAIA_samplebits_set(config.samplebits);
}

/* initial sai A */
rt_err_t SAIA_config_init(void)
{
    _sai_a.hsai.Instance = SAI1_Block_A;
    _sai_a.hsai.Init.AudioMode = SAI_MODEMASTER_TX;
    _sai_a.hsai.Init.Synchro = SAI_ASYNCHRONOUS;
    _sai_a.hsai.Init.OutputDrive = SAI_OUTPUTDRIVE_ENABLE;
    _sai_a.hsai.Init.NoDivider = SAI_MASTERDIVIDER_ENABLE;
    _sai_a.hsai.Init.FIFOThreshold = SAI_FIFOTHRESHOLD_1QF;
    _sai_a.hsai.Init.ClockSource = SAI_CLKSOURCE_PLLI2S;

    _sai_a.hsai.Init.Protocol = SAI_FREE_PROTOCOL;
    _sai_a.hsai.Init.DataSize = SAI_DATASIZE_16;
    _sai_a.hsai.Init.FirstBit = SAI_FIRSTBIT_MSB;
    _sai_a.hsai.Init.ClockStrobing = SAI_CLOCKSTROBING_RISINGEDGE;

    //frame
    _sai_a.hsai.FrameInit.FrameLength = 64;
    _sai_a.hsai.FrameInit.ActiveFrameLength = 32;
    _sai_a.hsai.FrameInit.FSDefinition = SAI_FS_CHANNEL_IDENTIFICATION;
    _sai_a.hsai.FrameInit.FSPolarity = SAI_FS_ACTIVE_LOW;
    _sai_a.hsai.FrameInit.FSOffset = SAI_FS_BEFOREFIRSTBIT;

    //slot
    _sai_a.hsai.SlotInit.FirstBitOffset = 0;
    _sai_a.hsai.SlotInit.SlotSize = SAI_SLOTSIZE_32B;
    _sai_a.hsai.SlotInit.SlotNumber = 2;
    _sai_a.hsai.SlotInit.SlotActive = SAI_SLOTACTIVE_0 | SAI_SLOTACTIVE_1;

    HAL_SAI_Init(&_sai_a.hsai);
    __HAL_SAI_ENABLE(&_sai_a.hsai);

    return RT_EOK;
}

rt_err_t SAIA_tx_dma(void)
{
    __HAL_RCC_DMA2_CLK_ENABLE();
    __HAL_LINKDMA(&_sai_a.hsai, hdmatx, _sai_a.hdma);

    _sai_a.hdma.Instance                 = DMA2_Stream3;
    _sai_a.hdma.Init.Channel             = DMA_CHANNEL_0;
    _sai_a.hdma.Init.Direction           = DMA_MEMORY_TO_PERIPH;
    _sai_a.hdma.Init.PeriphInc           = DMA_PINC_DISABLE;
    _sai_a.hdma.Init.MemInc              = DMA_MINC_ENABLE;

    _sai_a.hdma.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
    _sai_a.hdma.Init.MemDataAlignment    = DMA_MDATAALIGN_HALFWORD;

    _sai_a.hdma.Init.Mode                = DMA_CIRCULAR;
    _sai_a.hdma.Init.Priority            = DMA_PRIORITY_HIGH;
    _sai_a.hdma.Init.FIFOMode            = DMA_FIFOMODE_DISABLE;
    _sai_a.hdma.Init.FIFOThreshold       = DMA_FIFO_THRESHOLD_FULL;
    _sai_a.hdma.Init.MemBurst            = DMA_MBURST_SINGLE;
    _sai_a.hdma.Init.PeriphBurst         = DMA_PBURST_SINGLE;

    HAL_DMA_DeInit(&_sai_a.hdma);
    HAL_DMA_Init(&_sai_a.hdma);

    __HAL_DMA_DISABLE(&_sai_a.hdma);

    __HAL_DMA_ENABLE_IT(&_sai_a.hdma, DMA_IT_TC);
    __HAL_DMA_CLEAR_FLAG(&_sai_a.hdma, DMA_FLAG_TCIF3_7);
    /* set nvic */
    HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);
    return RT_EOK;
}

void DMA2_Stream3_IRQHandler(void)
{
    rt_interrupt_enter();
    HAL_DMA_IRQHandler(_sai_a.hsai.hdmatx);
    rt_interrupt_leave();
}

void HAL_SAI_TxHalfCpltCallback(SAI_HandleTypeDef *hsai)
{
    rt_audio_tx_complete(&_stm32_audio_play.audio);
}

void HAL_SAI_TxCpltCallback(SAI_HandleTypeDef *hsai)
{
    rt_audio_tx_complete(&_stm32_audio_play.audio);
}

rt_err_t sai_a_init()
{
    /* set sai_a DMA */
    SAIA_tx_dma();
    SAIA_config_init();

    return RT_EOK;
}

static rt_err_t stm32_player_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct stm32_audio *st_audio = (struct stm32_audio *)audio->parent.user_data;

    LOG_D("%s:main_type: %d, sub_type: %d", __FUNCTION__, caps->main_type, caps->sub_type);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY: /* query the types of hw_codec device */
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
            caps->udata.config.channels     = st_audio->replay_config.channels;
            caps->udata.config.samplebits   = st_audio->replay_config.samplebits;
            caps->udata.config.samplerate   = st_audio->replay_config.samplerate;
            break;

        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate   = st_audio->replay_config.samplerate;
            break;

        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels     = st_audio->replay_config.channels;
            break;

        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits     = st_audio->replay_config.samplebits;
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
            caps->udata.mask = AUDIO_MIXER_VOLUME | AUDIO_MIXER_LINE;
            break;

        case AUDIO_MIXER_VOLUME:
            caps->udata.value = st_audio->replay_volume;
            break;

        case AUDIO_MIXER_LINE:
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

static rt_err_t  stm32_player_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    struct stm32_audio *st_audio = (struct stm32_audio *)audio->parent.user_data;

    LOG_D("%s:main_type: %d, sub_type: %d", __FUNCTION__, caps->main_type, caps->sub_type);

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
    {
        switch (caps->sub_type)
        {
        case AUDIO_MIXER_MUTE:
        {
            /* set mute mode */
            wm8978_mute_enabled(_stm32_audio_play.i2c_bus, RT_FALSE);
            break;
        }

        case AUDIO_MIXER_VOLUME:
        {
            int volume = caps->udata.value;

            st_audio->replay_volume = volume;
            /* set mixer volume */
            wm8978_set_volume(_stm32_audio_play.i2c_bus, volume);

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
        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
        {
            struct rt_audio_configure config = caps->udata.config;

            st_audio->replay_config.samplerate = config.samplerate;
            st_audio->replay_config.samplebits = config.samplebits;
            st_audio->replay_config.channels = config.channels;

            SAIA_config_set(config);
            break;
        }

        case AUDIO_DSP_SAMPLERATE:
        {
            st_audio->replay_config.samplerate = caps->udata.config.samplerate;
            SAIA_samplerate_set(caps->udata.config.samplerate);
            break;
        }

        case AUDIO_DSP_CHANNELS:
        {
            st_audio->replay_config.channels = caps->udata.config.channels;
            SAIA_channels_set(caps->udata.config.channels);
            break;
        }

        case AUDIO_DSP_SAMPLEBITS:
        {
            st_audio->replay_config.samplebits = caps->udata.config.samplebits;
            SAIA_samplebits_set(caps->udata.config.samplebits);
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

static rt_err_t stm32_player_init(struct rt_audio_device *audio)
{
    /* initialize wm8978 */
    _stm32_audio_play.i2c_bus = (struct rt_i2c_bus_device *)rt_device_find(CODEC_I2C_NAME);

    sai_a_init();
    wm8978_init(_stm32_audio_play.i2c_bus);
    return RT_EOK;
}

static rt_err_t stm32_player_start(struct rt_audio_device *audio, int stream)
{
    if (stream == AUDIO_STREAM_REPLAY)
    {
        HAL_SAI_Transmit_DMA(&_sai_a.hsai, _stm32_audio_play.tx_fifo, TX_DMA_FIFO_SIZE / 2);
        wm8978_player_start(_stm32_audio_play.i2c_bus);
    }

    return RT_EOK;
}

static rt_err_t stm32_player_stop(struct rt_audio_device *audio, int stream)
{
    if (stream == AUDIO_STREAM_REPLAY)
    {
        HAL_SAI_DMAStop(&_sai_a.hsai);
    }

    return RT_EOK;
}

static void stm32_player_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    /**
     *               TX_FIFO
     * +----------------+----------------+
     * |     block1     |     block2     |
     * +----------------+----------------+
     *  \  block_size  /
     */
    info->buffer = _stm32_audio_play.tx_fifo;
    info->total_size = TX_DMA_FIFO_SIZE;
    info->block_size = TX_DMA_FIFO_SIZE / 2;
    info->block_count = 2;
}
static struct rt_audio_ops _p_audio_ops =
{
    .getcaps     = stm32_player_getcaps,
    .configure   = stm32_player_configure,
    .init        = stm32_player_init,
    .start       = stm32_player_start,
    .stop        = stm32_player_stop,
    .transmit    = RT_NULL,
    .buffer_info = stm32_player_buffer_info,
};

int rt_hw_sound_init(void)
{
    rt_uint8_t *tx_fifo;

    /* player */
    tx_fifo = rt_malloc(TX_DMA_FIFO_SIZE);
    if (tx_fifo == RT_NULL)
    {
        return -RT_ENOMEM;
    }
    rt_memset(tx_fifo, 0, TX_DMA_FIFO_SIZE);
    _stm32_audio_play.tx_fifo = tx_fifo;

    /* register sound device */
    _stm32_audio_play.audio.ops = &_p_audio_ops;
    rt_audio_register(&_stm32_audio_play.audio, "sound0", RT_DEVICE_FLAG_WRONLY, &_stm32_audio_play);

    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_sound_init);
