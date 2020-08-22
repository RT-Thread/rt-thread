/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-2-7        Wayne Lin        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_I2S)

#include <rtdevice.h>
#include <drv_pdma.h>
#include <drv_i2s.h>

/* Private define ---------------------------------------------------------------*/
#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "i2s"
#define DBG_COLOR
#include <rtdbg.h>

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_i2s_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps);
static rt_err_t nu_i2s_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps);
static rt_err_t nu_i2s_init(struct rt_audio_device *audio);
static rt_err_t nu_i2s_start(struct rt_audio_device *audio, int stream);
static rt_err_t nu_i2s_stop(struct rt_audio_device *audio, int stream);
static void nu_i2s_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info);
/* Public functions -------------------------------------------------------------*/
rt_err_t nu_i2s_acodec_register(nu_acodec_ops_t);

/* Private variables ------------------------------------------------------------*/
static struct nu_i2s g_nu_i2s_dev =
{
    .name = "sound0",
    .i2s_base  = I2S0,
    .i2s_rst   = I2S0_RST,
    .i2s_dais = {
        [NU_I2S_DAI_PLAYBACK] = {
            .pdma_perp = PDMA_I2S0_TX,
        },
        [NU_I2S_DAI_CAPTURE] = {
            .pdma_perp = PDMA_I2S0_RX,
        }
    }
};

static void nu_pdma_i2s_rx_cb(void *pvUserData, uint32_t u32EventFilter)
{
    nu_i2s_t psNuI2s = (nu_i2s_t)pvUserData;
    nu_i2s_dai_t psNuI2sDai;

    RT_ASSERT(psNuI2s != RT_NULL);
    psNuI2sDai = &psNuI2s->i2s_dais[NU_I2S_DAI_CAPTURE];

    if (u32EventFilter & NU_PDMA_EVENT_TRANSFER_DONE)
    {
        // Report a buffer ready.
        rt_uint8_t *pbuf_old = &psNuI2sDai->fifo[psNuI2sDai->fifo_block_idx * NU_I2S_DMA_BUF_BLOCK_SIZE] ;
        psNuI2sDai->fifo_block_idx = (psNuI2sDai->fifo_block_idx + 1) % NU_I2S_DMA_BUF_BLOCK_NUMBER;

        /* Report upper layer. */
        rt_audio_rx_done(&psNuI2s->audio, pbuf_old, NU_I2S_DMA_BUF_BLOCK_SIZE);
    }
}

static void nu_pdma_i2s_tx_cb(void *pvUserData, uint32_t u32EventFilter)
{
    nu_i2s_t psNuI2s = (nu_i2s_t)pvUserData;
    nu_i2s_dai_t psNuI2sDai;

    RT_ASSERT(psNuI2s != RT_NULL);
    psNuI2sDai = &psNuI2s->i2s_dais[NU_I2S_DAI_PLAYBACK];

    if (u32EventFilter & NU_PDMA_EVENT_TRANSFER_DONE)
    {
        rt_audio_tx_complete(&psNuI2s->audio);
        psNuI2sDai->fifo_block_idx = (psNuI2sDai->fifo_block_idx + 1) % NU_I2S_DMA_BUF_BLOCK_NUMBER;
    }
}

static rt_err_t nu_i2s_pdma_sc_config(nu_i2s_t psNuI2s, E_NU_I2S_DAI dai)
{
    rt_err_t result = RT_EOK;
    I2S_T *i2s_base;
    nu_i2s_dai_t psNuI2sDai;
    int i;
    uint32_t u32Src, u32Dst;
    nu_pdma_cb_handler_t pfm_pdma_cb;

    RT_ASSERT(psNuI2s != RT_NULL);

    /* Get base address of i2s register */
    i2s_base = psNuI2s->i2s_base;
    psNuI2sDai = &psNuI2s->i2s_dais[dai];

    switch ((int)dai)
    {
    case NU_I2S_DAI_PLAYBACK:
        pfm_pdma_cb = nu_pdma_i2s_tx_cb;
        u32Src = (uint32_t)&psNuI2sDai->fifo[0];
        u32Dst = (uint32_t)&i2s_base->TXFIFO;
        break;

    case NU_I2S_DAI_CAPTURE:
        pfm_pdma_cb = nu_pdma_i2s_rx_cb;
        u32Src = (uint32_t)&i2s_base->RXFIFO;
        u32Dst = (uint32_t)&psNuI2sDai->fifo[0];
        break;

    default:
        return -RT_EINVAL;
    }

    result = nu_pdma_callback_register(psNuI2sDai->pdma_chanid,
                                       pfm_pdma_cb,
                                       (void *)psNuI2s,
                                       NU_PDMA_EVENT_TRANSFER_DONE);
    RT_ASSERT(result == RT_EOK);

    for (i = 0; i < NU_I2S_DMA_BUF_BLOCK_NUMBER; i++)
    {
        /* Setup dma descriptor entry */
        result = nu_pdma_desc_setup(psNuI2sDai->pdma_chanid,    // Channel ID
                                    psNuI2sDai->pdma_descs[i], // this descriptor
                                    32, // 32-bits
                                    (dai == NU_I2S_DAI_PLAYBACK) ? u32Src + (i * NU_I2S_DMA_BUF_BLOCK_SIZE) : u32Src, //Memory or RXFIFO
                                    (dai == NU_I2S_DAI_PLAYBACK) ? u32Dst : u32Dst + (i * NU_I2S_DMA_BUF_BLOCK_SIZE), //TXFIFO or Memory
                                    (int32_t)NU_I2S_DMA_BUF_BLOCK_SIZE / 4,   // Transfer count
                                    psNuI2sDai->pdma_descs[(i + 1) % NU_I2S_DMA_BUF_BLOCK_NUMBER]); // Next descriptor
        RT_ASSERT(result == RT_EOK);
    }

    /* Assign head descriptor */
    result = nu_pdma_sg_transfer(psNuI2sDai->pdma_chanid, psNuI2sDai->pdma_descs[0], 0);
    RT_ASSERT(result == RT_EOK);

    return result;
}

static rt_bool_t nu_i2s_capacity_check(struct rt_audio_configure *pconfig)
{
    switch (pconfig->samplebits)
    {
    case  8:
    case 16:
    /* case 24: PDMA constrain */
    case 32:
        break;
    default:
        goto exit_nu_i2s_capacity_check;
    }

    switch (pconfig->channels)
    {
    case 1:
    case 2:
        break;
    default:
        goto exit_nu_i2s_capacity_check;
    }

    return RT_TRUE;

exit_nu_i2s_capacity_check:

    return RT_FALSE;
}

static rt_err_t nu_i2s_dai_setup(nu_i2s_t psNuI2s, struct rt_audio_configure *pconfig)
{
    rt_err_t result = RT_EOK;
    nu_acodec_ops_t pNuACodecOps = RT_NULL;
    RT_ASSERT(psNuI2s->AcodecOps != RT_NULL);
    pNuACodecOps = psNuI2s->AcodecOps;
    rt_uint32_t real_samplerate;

    /* Open I2S */
    if (nu_i2s_capacity_check(pconfig) == RT_TRUE)
    {
        /* Reset audio codec */
        if (pNuACodecOps->nu_acodec_reset)
            result = pNuACodecOps->nu_acodec_reset();

        if (result != RT_EOK)
            goto exit_nu_i2s_dai_setup;

        /* Setup audio codec */
        if (pNuACodecOps->nu_acodec_init)
            result = pNuACodecOps->nu_acodec_init();

        if (!pNuACodecOps->nu_acodec_init || result != RT_EOK)
            goto exit_nu_i2s_dai_setup;

        /* Setup acodec samplerate/samplebit/channel */
        if (pNuACodecOps->nu_acodec_dsp_control)
            result = pNuACodecOps->nu_acodec_dsp_control(pconfig);

        if (!pNuACodecOps->nu_acodec_dsp_control || result != RT_EOK)
            goto exit_nu_i2s_dai_setup;

        real_samplerate = I2S_Open(psNuI2s->i2s_base,
                                   (psNuI2s->AcodecOps->role == NU_ACODEC_ROLE_MASTER) ? I2S_MODE_SLAVE : I2S_MODE_MASTER,
                                   pconfig->samplerate,
                                   (((pconfig->samplebits / 8) - 1) << I2S_CTL0_DATWIDTH_Pos),
                                   (pconfig->channels == 1) ? I2S_ENABLE_MONO : I2S_DISABLE_MONO,
                                   I2S_FORMAT_I2S);
        LOG_I("Open I2S.");

        /* Open I2S0 interface and set to slave mode, stereo channel, I2S format */
        if (pconfig->samplerate != real_samplerate)
        {
            LOG_W("Real sample rate: %d Hz != preferred sample rate: %d Hz\n", real_samplerate, pconfig->samplerate);
        }

        /* Set MCLK and enable MCLK */
        I2S_EnableMCLK(psNuI2s->i2s_base, __HXT);

        /* Set unmute */
        if (pNuACodecOps->nu_acodec_mixer_control)
            pNuACodecOps->nu_acodec_mixer_control(AUDIO_MIXER_MUTE, RT_FALSE);
    }
    else
        result = -RT_EINVAL;

exit_nu_i2s_dai_setup:

    return result;
}

static rt_err_t nu_i2s_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    nu_i2s_t psNuI2s;
    nu_acodec_ops_t pNuACodecOps = RT_NULL;

    RT_ASSERT(audio != RT_NULL);
    RT_ASSERT(caps != RT_NULL);

    psNuI2s = (nu_i2s_t)audio;

    RT_ASSERT(psNuI2s->AcodecOps != RT_NULL);

    pNuACodecOps = psNuI2s->AcodecOps;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_QUERY:
        switch (caps->sub_type)
        {
        case AUDIO_TYPE_QUERY:
            caps->udata.mask = AUDIO_TYPE_INPUT | AUDIO_TYPE_OUTPUT | AUDIO_TYPE_MIXER;
            break;
        default:
            result = -RT_ERROR;
            break;
        } // switch (caps->sub_type)
        break;

    case AUDIO_TYPE_MIXER:

        if (pNuACodecOps->nu_acodec_mixer_query)
        {
            switch (caps->sub_type)
            {
            case AUDIO_MIXER_QUERY:
                return pNuACodecOps->nu_acodec_mixer_query(AUDIO_MIXER_QUERY, &caps->udata.mask);

            default:
                return pNuACodecOps->nu_acodec_mixer_query(caps->sub_type, (rt_uint32_t *)&caps->udata.value);
            } // switch (caps->sub_type)

        } // if (pNuACodecOps->nu_acodec_mixer_query)

        result = -RT_ERROR;
        break;

    case AUDIO_TYPE_INPUT:
    case AUDIO_TYPE_OUTPUT:

        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            caps->udata.config.channels = psNuI2s->config.channels;
            caps->udata.config.samplebits = psNuI2s->config.samplebits;
            caps->udata.config.samplerate = psNuI2s->config.samplerate;
            break;
        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = psNuI2s->config.samplerate;
            break;
        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = psNuI2s->config.channels;
            break;
        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = psNuI2s->config.samplebits;
            break;
        default:
            result = -RT_ERROR;
            break;
        } // switch (caps->sub_type)
        break;

    default:
        result = -RT_ERROR;
        break;

    } // switch (caps->main_type)

    return result;
}

static rt_err_t nu_i2s_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    nu_i2s_t psNuI2s;
    nu_acodec_ops_t pNuACodecOps = RT_NULL;
    int stream = -1;

    RT_ASSERT(audio != RT_NULL);
    RT_ASSERT(caps != RT_NULL);

    psNuI2s = (nu_i2s_t)audio;

    RT_ASSERT(psNuI2s->AcodecOps != RT_NULL);
    pNuACodecOps = psNuI2s->AcodecOps;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
        if (psNuI2s->AcodecOps->nu_acodec_mixer_control)
            psNuI2s->AcodecOps->nu_acodec_mixer_control(caps->sub_type, caps->udata.value);
        break;


    case AUDIO_TYPE_INPUT:
        stream = AUDIO_STREAM_RECORD;
    case AUDIO_TYPE_OUTPUT:
    {
        rt_bool_t bNeedReset = RT_FALSE;

        if (stream < 0)
            stream = AUDIO_STREAM_REPLAY;

        switch (caps->sub_type)
        {
        case AUDIO_DSP_PARAM:
            if (rt_memcmp(&psNuI2s->config, &caps->udata.config, sizeof(struct rt_audio_configure)) != 0)
            {
                rt_memcpy(&psNuI2s->config, &caps->udata.config, sizeof(struct rt_audio_configure));
                bNeedReset = RT_TRUE;
            }
            break;
        case AUDIO_DSP_SAMPLEBITS:
            if (psNuI2s->config.samplerate != caps->udata.config.samplebits)
            {
                psNuI2s->config.samplerate = caps->udata.config.samplebits;
                bNeedReset = RT_TRUE;
            }
            break;
        case AUDIO_DSP_CHANNELS:
            if (psNuI2s->config.channels != caps->udata.config.channels)
            {
                pNuACodecOps->config.channels = caps->udata.config.channels;
                bNeedReset = RT_TRUE;
            }
            break;
        case AUDIO_DSP_SAMPLERATE:
            if (psNuI2s->config.samplerate != caps->udata.config.samplerate)
            {
                psNuI2s->config.samplerate = caps->udata.config.samplerate;
                bNeedReset = RT_TRUE;
            }
            break;
        default:
            result = -RT_ERROR;
            break;
        } // switch (caps->sub_type)

        if (bNeedReset)
        {
            return nu_i2s_start(audio, stream);
        }
    }
    break;
    default:
        result = -RT_ERROR;
        break;
    } // switch (caps->main_type)

    return result;
}

static rt_err_t nu_i2s_init(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;
    nu_i2s_t psNuI2s;

    RT_ASSERT(audio != RT_NULL);

    psNuI2s = (nu_i2s_t)audio;

    /* Reset this module */
    SYS_ResetModule(psNuI2s->i2s_rst);

    return -(result);
}

static rt_err_t nu_i2s_start(struct rt_audio_device *audio, int stream)
{
    nu_i2s_t psNuI2s;

    RT_ASSERT(audio != RT_NULL);

    psNuI2s = (nu_i2s_t)audio;

    /* Restart all: I2S and codec. */
    nu_i2s_stop(audio, stream);
    if (nu_i2s_dai_setup(psNuI2s, &psNuI2s->config) != RT_EOK)
        return -RT_ERROR;

    switch (stream)
    {
    case AUDIO_STREAM_REPLAY:
    {
        nu_i2s_pdma_sc_config(psNuI2s, NU_I2S_DAI_PLAYBACK);

        /* Start TX DMA */
        I2S_ENABLE_TXDMA(psNuI2s->i2s_base);

        /* Enable I2S Tx function */
        I2S_ENABLE_TX(psNuI2s->i2s_base);

        LOG_I("Start replay.");
    }
    break;

    case AUDIO_STREAM_RECORD:
    {
        nu_i2s_pdma_sc_config(psNuI2s, NU_I2S_DAI_CAPTURE);

        /* Start RX DMA */
        I2S_ENABLE_RXDMA(psNuI2s->i2s_base);

        /* Enable I2S Rx function */
        I2S_ENABLE_RX(psNuI2s->i2s_base);

        LOG_I("Start record.");
    }
    break;

    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t nu_i2s_stop(struct rt_audio_device *audio, int stream)
{
    nu_i2s_t psNuI2s;
    nu_i2s_dai_t psNuI2sDai = RT_NULL;

    RT_ASSERT(audio != RT_NULL);

    psNuI2s = (nu_i2s_t)audio;

    switch (stream)
    {
    case AUDIO_STREAM_REPLAY:
        psNuI2sDai = &psNuI2s->i2s_dais[NU_I2S_DAI_PLAYBACK];

        // Disable TX
        I2S_DISABLE_TXDMA(psNuI2s->i2s_base);
        I2S_DISABLE_TX(psNuI2s->i2s_base);

        LOG_I("Stop replay.");
        break;

    case AUDIO_STREAM_RECORD:
        psNuI2sDai = &psNuI2s->i2s_dais[NU_I2S_DAI_CAPTURE];

        // Disable RX
        I2S_DISABLE_RXDMA(psNuI2s->i2s_base);
        I2S_DISABLE_RX(psNuI2s->i2s_base);

        LOG_I("Stop record.");
        break;

    default:
        return -RT_EINVAL;
    }

    /* Stop DMA transfer. */
    nu_pdma_channel_terminate(psNuI2sDai->pdma_chanid);

    /* Close I2S */
    if (!(psNuI2s->i2s_base->CTL0 & (I2S_CTL0_TXEN_Msk | I2S_CTL0_RXEN_Msk)))
    {
        I2S_DisableMCLK(psNuI2s->i2s_base);
        I2S_Close(psNuI2s->i2s_base);
        LOG_I("Close I2S.");
    }

    /* Silence */
    rt_memset((void *)psNuI2sDai->fifo, 0, NU_I2S_DMA_FIFO_SIZE);
    psNuI2sDai->fifo_block_idx = 0;

    return RT_EOK;
}

static void nu_i2s_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    nu_i2s_t psNuI2s;

    RT_ASSERT(audio != RT_NULL);
    RT_ASSERT(info != RT_NULL);

    psNuI2s = (nu_i2s_t)audio;

    info->buffer = (rt_uint8_t *)psNuI2s->i2s_dais[NU_I2S_DAI_PLAYBACK].fifo ;
    info->total_size = NU_I2S_DMA_FIFO_SIZE;
    info->block_size = NU_I2S_DMA_BUF_BLOCK_SIZE;
    info->block_count = NU_I2S_DMA_BUF_BLOCK_NUMBER;

    return;
}

static struct rt_audio_ops nu_i2s_audio_ops =
{
    .getcaps     = nu_i2s_getcaps,
    .configure   = nu_i2s_configure,

    .init        = nu_i2s_init,
    .start       = nu_i2s_start,
    .stop        = nu_i2s_stop,
    .transmit    = RT_NULL,
    .buffer_info = nu_i2s_buffer_info
};

static rt_err_t nu_hw_i2s_pdma_allocate(nu_i2s_dai_t psNuI2sDai)
{
    /* Allocate I2S nu_dma channel */
    if ((psNuI2sDai->pdma_chanid = nu_pdma_channel_allocate(psNuI2sDai->pdma_perp)) < 0)
    {
        goto nu_hw_i2s_pdma_allocate;
    }

    return RT_EOK;

nu_hw_i2s_pdma_allocate:

    return -(RT_ERROR);
}

int rt_hw_i2s_init(void)
{
    int i = 0;
    nu_i2s_dai_t psNuI2sDai;

    for (i = 0; i < NU_I2S_DAI_CNT; i++)
    {
        uint8_t *pu8ptr = rt_malloc(NU_I2S_DMA_FIFO_SIZE);
        psNuI2sDai = &g_nu_i2s_dev.i2s_dais[i];
        psNuI2sDai->fifo = pu8ptr;
        rt_memset(pu8ptr, 0, NU_I2S_DMA_FIFO_SIZE);
        RT_ASSERT(psNuI2sDai->fifo != RT_NULL);

        psNuI2sDai->pdma_chanid = -1;
        psNuI2sDai->fifo_block_idx = 0;
        RT_ASSERT(nu_hw_i2s_pdma_allocate(psNuI2sDai) == RT_EOK);

        RT_ASSERT(nu_pdma_sgtbls_allocate(&psNuI2sDai->pdma_descs[0], NU_I2S_DMA_BUF_BLOCK_NUMBER) == RT_EOK);
    }

    /* Register ops of audio device */
    g_nu_i2s_dev.audio.ops  = &nu_i2s_audio_ops;

    /* Register device, RW: it is with replay and record functions. */
    rt_audio_register(&g_nu_i2s_dev.audio, g_nu_i2s_dev.name, RT_DEVICE_FLAG_RDWR, &g_nu_i2s_dev);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2s_init);
#endif //#if defined(BSP_USING_I2S)
