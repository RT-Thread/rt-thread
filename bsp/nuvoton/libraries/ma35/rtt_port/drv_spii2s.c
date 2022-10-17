/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-5-29       Wayne            First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_SPII2S)

#include <rtdevice.h>
#include <drv_pdma.h>
#include <drv_i2s.h>

/* Private define ---------------------------------------------------------------*/
#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "spii2s"
#define DBG_COLOR
#include <rtdbg.h>

enum
{
    SPII2S_START = -1,
#if defined(BSP_USING_SPII2S0)
    SPII2S0_IDX,
#endif
#if defined(BSP_USING_SPII2S1)
    SPII2S1_IDX,
#endif
#if defined(BSP_USING_SPII2S2)
    SPII2S2_IDX,
#endif
#if defined(BSP_USING_SPII2S3)
    SPII2S3_IDX,
#endif
    SPII2S_CNT
};

/* Private functions ------------------------------------------------------------*/
static rt_err_t nu_spii2s_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps);
static rt_err_t nu_spii2s_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps);
static rt_err_t nu_spii2s_init(struct rt_audio_device *audio);
static rt_err_t nu_spii2s_start(struct rt_audio_device *audio, int stream);
static rt_err_t nu_spii2s_stop(struct rt_audio_device *audio, int stream);
static void nu_spii2s_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info);
/* Public functions -------------------------------------------------------------*/
rt_err_t nu_spii2s_acodec_register(struct rt_audio_device *audio, nu_acodec_ops_t);

/* Private variables ------------------------------------------------------------*/
static struct nu_i2s g_nu_spii2s_arr [] =
{
#if defined(BSP_USING_SPII2S0)
    {
        .name = "spii2s0",
        .i2s_base  = (I2S_T *)SPI0, //Avoid warning
        .i2s_rst   = SPI0_RST,
        .i2s_dais = {
            [NU_I2S_DAI_PLAYBACK] = {
                .pdma_perp = PDMA_SPI0_TX,
            },
            [NU_I2S_DAI_CAPTURE] = {
                .pdma_perp = PDMA_SPI0_RX,
            }
        }
    },
#endif
#if defined(BSP_USING_SPII2S1)
    {
        .name = "spii2s1",
        .i2s_base  = (I2S_T *)SPI1, //Avoid warning
        .i2s_rst   = SPI1_RST,
        .i2s_dais = {
            [NU_I2S_DAI_PLAYBACK] = {
                .pdma_perp = PDMA_SPI1_TX,
            },
            [NU_I2S_DAI_CAPTURE] = {
                .pdma_perp = PDMA_SPI1_RX,
            }
        }
    },
#endif
#if defined(BSP_USING_SPII2S2)
    {
        .name = "spii2s2",
        .i2s_base  = (I2S_T *)SPI2, //Avoid warning
        .i2s_rst   = SPI2_RST,
        .i2s_dais = {
            [NU_I2S_DAI_PLAYBACK] = {
                .pdma_perp = PDMA_SPI2_TX,
            },
            [NU_I2S_DAI_CAPTURE] = {
                .pdma_perp = PDMA_SPI2_RX,
            }
        }
    },
#endif
#if defined(BSP_USING_SPII2S3)
    {
        .name = "spii2s3",
        .i2s_base  = (I2S_T *)SPI3, //Avoid warning
        .i2s_rst   = SPI3_RST,
        .i2s_dais = {
            [NU_I2S_DAI_PLAYBACK] = {
                .pdma_perp = PDMA_SPI3_TX,
            },
            [NU_I2S_DAI_CAPTURE] = {
                .pdma_perp = PDMA_SPI3_RX,
            }
        }
    },
#endif
};

static void nu_pdma_spii2s_rx_cb(void *pvUserData, uint32_t u32EventFilter)
{
    nu_i2s_t psNuSPII2s = (nu_i2s_t)pvUserData;
    nu_i2s_dai_t psNuSPII2sDai;

    RT_ASSERT(psNuSPII2s != RT_NULL);
    psNuSPII2sDai = &psNuSPII2s->i2s_dais[NU_I2S_DAI_CAPTURE];

    if (u32EventFilter & NU_PDMA_EVENT_TRANSFER_DONE)
    {
        // Report a buffer ready.
        rt_uint8_t *pbuf_old = &psNuSPII2sDai->fifo[psNuSPII2sDai->fifo_block_idx * NU_I2S_DMA_BUF_BLOCK_SIZE] ;
        psNuSPII2sDai->fifo_block_idx = (psNuSPII2sDai->fifo_block_idx + 1) % NU_I2S_DMA_BUF_BLOCK_NUMBER;

        /* Report upper layer. */
        rt_audio_rx_done(&psNuSPII2s->audio, pbuf_old, NU_I2S_DMA_BUF_BLOCK_SIZE);
    }
}

static void nu_pdma_spii2s_tx_cb(void *pvUserData, uint32_t u32EventFilter)
{
    nu_i2s_t psNuSPII2s = (nu_i2s_t)pvUserData;
    nu_i2s_dai_t psNuSPII2sDai;

    RT_ASSERT(psNuSPII2s != RT_NULL);
    psNuSPII2sDai = &psNuSPII2s->i2s_dais[NU_I2S_DAI_PLAYBACK];

    if (u32EventFilter & NU_PDMA_EVENT_TRANSFER_DONE)
    {
        rt_audio_tx_complete(&psNuSPII2s->audio);
        psNuSPII2sDai->fifo_block_idx = (psNuSPII2sDai->fifo_block_idx + 1) % NU_I2S_DMA_BUF_BLOCK_NUMBER;
    }
}

static rt_err_t nu_spii2s_pdma_sc_config(nu_i2s_t psNuSPII2s, E_NU_I2S_DAI dai)
{
    rt_err_t result = RT_EOK;
    SPI_T *spii2s_base;
    nu_i2s_dai_t psNuSPII2sDai;
    int i;
    uint32_t u32Src, u32Dst;
    nu_pdma_cb_handler_t pfm_pdma_cb;
    struct nu_pdma_chn_cb sChnCB;

    RT_ASSERT(psNuSPII2s != RT_NULL);

    /* Get base address of spii2s register */
    spii2s_base = (SPI_T *)psNuSPII2s->i2s_base;
    psNuSPII2sDai = &psNuSPII2s->i2s_dais[dai];

    switch ((int)dai)
    {
    case NU_I2S_DAI_PLAYBACK:
        pfm_pdma_cb = nu_pdma_spii2s_tx_cb;
        u32Src = (uint32_t)&psNuSPII2sDai->fifo[0];
        u32Dst = (uint32_t)&spii2s_base->TX;
        break;

    case NU_I2S_DAI_CAPTURE:
        pfm_pdma_cb = nu_pdma_spii2s_rx_cb;
        u32Src = (uint32_t)&spii2s_base->RX;
        u32Dst = (uint32_t)&psNuSPII2sDai->fifo[0];
        break;

    default:
        return -RT_EINVAL;
    }
    /* Register ISR callback function */
    sChnCB.m_eCBType = eCBType_Event;
    sChnCB.m_pfnCBHandler = pfm_pdma_cb;
    sChnCB.m_pvUserData = (void *)psNuSPII2s;

    nu_pdma_filtering_set(psNuSPII2sDai->pdma_chanid, NU_PDMA_EVENT_TRANSFER_DONE);
    result = nu_pdma_callback_register(psNuSPII2sDai->pdma_chanid, &sChnCB);
    RT_ASSERT(result == RT_EOK);

    for (i = 0; i < NU_I2S_DMA_BUF_BLOCK_NUMBER; i++)
    {
        /* Setup dma descriptor entry */
        result = nu_pdma_desc_setup(psNuSPII2sDai->pdma_chanid,    // Channel ID
                                    psNuSPII2sDai->pdma_descs[i], // this descriptor
                                    32, // 32-bits
                                    (dai == NU_I2S_DAI_PLAYBACK) ? u32Src + (i * NU_I2S_DMA_BUF_BLOCK_SIZE) : u32Src, //Memory or RXFIFO
                                    (dai == NU_I2S_DAI_PLAYBACK) ? u32Dst : u32Dst + (i * NU_I2S_DMA_BUF_BLOCK_SIZE), //TXFIFO or Memory
                                    (int32_t)NU_I2S_DMA_BUF_BLOCK_SIZE / 4,   // Transfer count
                                    psNuSPII2sDai->pdma_descs[(i + 1) % NU_I2S_DMA_BUF_BLOCK_NUMBER], // Next descriptor
                                    0);  // Interrupt assert when every SG-table done.
        RT_ASSERT(result == RT_EOK);
    }

    /* Assign head descriptor */
    result = nu_pdma_sg_transfer(psNuSPII2sDai->pdma_chanid, psNuSPII2sDai->pdma_descs[0], 0);
    RT_ASSERT(result == RT_EOK);

    return result;
}

static rt_bool_t nu_spii2s_capacity_check(struct rt_audio_configure *pconfig)
{
    switch (pconfig->samplebits)
    {
    case  8:
    case 16:
    /* case 24: PDMA constrain */
    case 32:
        break;
    default:
        goto exit_nu_spii2s_capacity_check;
    }

    switch (pconfig->channels)
    {
    case 1:
    case 2:
        break;
    default:
        goto exit_nu_spii2s_capacity_check;
    }

    return RT_TRUE;

exit_nu_spii2s_capacity_check:

    return RT_FALSE;
}

static rt_err_t nu_spii2s_dai_setup(nu_i2s_t psNuSPII2s, struct rt_audio_configure *pconfig)
{
    rt_err_t result = RT_EOK;
    nu_acodec_ops_t pNuACodecOps;
    SPI_T *spii2s_base = (SPI_T *)psNuSPII2s->i2s_base;

    RT_ASSERT(psNuSPII2s->AcodecOps != RT_NULL);
    pNuACodecOps = psNuSPII2s->AcodecOps;

    /* Open SPII2S */
    if (nu_spii2s_capacity_check(pconfig) == RT_TRUE)
    {
        /* Reset audio codec */
        if (pNuACodecOps->nu_acodec_reset)
            result = pNuACodecOps->nu_acodec_reset();

        if (result != RT_EOK)
            goto exit_nu_spii2s_dai_setup;

        /* Setup audio codec */
        if (pNuACodecOps->nu_acodec_init)
            result = pNuACodecOps->nu_acodec_init();

        if (!pNuACodecOps->nu_acodec_init || result != RT_EOK)
            goto exit_nu_spii2s_dai_setup;

        /* Setup acodec samplerate/samplebit/channel */
        if (pNuACodecOps->nu_acodec_dsp_control)
            result = pNuACodecOps->nu_acodec_dsp_control(pconfig);

        if (!pNuACodecOps->nu_acodec_dsp_control || result != RT_EOK)
            goto exit_nu_spii2s_dai_setup;

        SPII2S_Open(spii2s_base,
                    (psNuSPII2s->AcodecOps->role == NU_ACODEC_ROLE_MASTER) ? SPII2S_MODE_SLAVE : SPII2S_MODE_MASTER,
                    pconfig->samplerate,
                    (((pconfig->samplebits / 8) - 1) << SPI_I2SCTL_WDWIDTH_Pos),
                    (pconfig->channels == 1) ? SPII2S_MONO : SPII2S_STEREO,
                    SPII2S_FORMAT_I2S);
        LOG_I("Open SPII2S.");

        /* Set MCLK and enable MCLK */
        /* The target MCLK is related to audio codec setting. */
        SPII2S_EnableMCLK(spii2s_base, 12000000);

        /* Set un-mute */
        if (pNuACodecOps->nu_acodec_mixer_control)
            pNuACodecOps->nu_acodec_mixer_control(AUDIO_MIXER_MUTE, RT_FALSE);
    }
    else
        result = -RT_EINVAL;

exit_nu_spii2s_dai_setup:

    return result;
}

static rt_err_t nu_spii2s_getcaps(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    nu_i2s_t psNuSPII2s = (nu_i2s_t)audio;
    nu_acodec_ops_t pNuACodecOps;

    RT_ASSERT(audio != RT_NULL);
    RT_ASSERT(caps != RT_NULL);
    RT_ASSERT(psNuSPII2s->AcodecOps != RT_NULL);

    pNuACodecOps = psNuSPII2s->AcodecOps;

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
            caps->udata.config.channels = psNuSPII2s->config.channels;
            caps->udata.config.samplebits = psNuSPII2s->config.samplebits;
            caps->udata.config.samplerate = psNuSPII2s->config.samplerate;
            break;
        case AUDIO_DSP_SAMPLERATE:
            caps->udata.config.samplerate = psNuSPII2s->config.samplerate;
            break;
        case AUDIO_DSP_CHANNELS:
            caps->udata.config.channels = psNuSPII2s->config.channels;
            break;
        case AUDIO_DSP_SAMPLEBITS:
            caps->udata.config.samplebits = psNuSPII2s->config.samplebits;
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

static rt_err_t nu_spii2s_configure(struct rt_audio_device *audio, struct rt_audio_caps *caps)
{
    rt_err_t result = RT_EOK;
    nu_i2s_t psNuSPII2s = (nu_i2s_t)audio;
    nu_acodec_ops_t pNuACodecOps;
    int stream = -1;

    RT_ASSERT(audio != RT_NULL);
    RT_ASSERT(caps != RT_NULL);
    RT_ASSERT(psNuSPII2s->AcodecOps != RT_NULL);

    pNuACodecOps = psNuSPII2s->AcodecOps;

    switch (caps->main_type)
    {
    case AUDIO_TYPE_MIXER:
        if (psNuSPII2s->AcodecOps->nu_acodec_mixer_control)
            psNuSPII2s->AcodecOps->nu_acodec_mixer_control(caps->sub_type, caps->udata.value);
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
            if (rt_memcmp(&psNuSPII2s->config, &caps->udata.config, sizeof(struct rt_audio_configure)) != 0)
            {
                rt_memcpy(&psNuSPII2s->config, &caps->udata.config, sizeof(struct rt_audio_configure));
                bNeedReset = RT_TRUE;
            }
            break;
        case AUDIO_DSP_SAMPLEBITS:
            if (psNuSPII2s->config.samplerate != caps->udata.config.samplebits)
            {
                psNuSPII2s->config.samplerate = caps->udata.config.samplebits;
                bNeedReset = RT_TRUE;
            }
            break;
        case AUDIO_DSP_CHANNELS:
            if (psNuSPII2s->config.channels != caps->udata.config.channels)
            {
                pNuACodecOps->config.channels = caps->udata.config.channels;
                bNeedReset = RT_TRUE;
            }
            break;
        case AUDIO_DSP_SAMPLERATE:
            if (psNuSPII2s->config.samplerate != caps->udata.config.samplerate)
            {
                psNuSPII2s->config.samplerate = caps->udata.config.samplerate;
                bNeedReset = RT_TRUE;
            }
            break;
        default:
            result = -RT_ERROR;
            break;
        } // switch (caps->sub_type)

        if (bNeedReset)
        {
            return nu_spii2s_start(audio, stream);
        }
    }
    break;

    default:
        result = -RT_ERROR;
        break;
    } // switch (caps->main_type)

    return result;
}

static rt_err_t nu_spii2s_init(struct rt_audio_device *audio)
{
    rt_err_t result = RT_EOK;
    nu_i2s_t psNuSPII2s = (nu_i2s_t)audio;

    RT_ASSERT(audio != RT_NULL);

    /* Reset this module */
    SYS_ResetModule(psNuSPII2s->i2s_rst);

    return -(result);
}

static rt_err_t nu_spii2s_start(struct rt_audio_device *audio, int stream)
{
    nu_i2s_t psNuSPII2s = (nu_i2s_t)audio;
    SPI_T *spii2s_base;

    RT_ASSERT(audio != RT_NULL);

    spii2s_base = (SPI_T *)psNuSPII2s->i2s_base;

    /* Restart all: SPII2S and codec. */
    nu_spii2s_stop(audio, stream);
    if (nu_spii2s_dai_setup(psNuSPII2s, &psNuSPII2s->config) != RT_EOK)
        return -RT_ERROR;

    switch (stream)
    {
    case AUDIO_STREAM_REPLAY:
    {
        nu_spii2s_pdma_sc_config(psNuSPII2s, NU_I2S_DAI_PLAYBACK);

        /* Start TX DMA */
        SPII2S_ENABLE_TXDMA(spii2s_base);

        /* Enable I2S Tx function */
        SPII2S_ENABLE_TX(spii2s_base);

        LOG_I("Start replay.");
    }
    break;

    case AUDIO_STREAM_RECORD:
    {
        nu_spii2s_pdma_sc_config(psNuSPII2s, NU_I2S_DAI_CAPTURE);

        /* Start RX DMA */
        SPII2S_ENABLE_RXDMA(spii2s_base);

        /* Enable I2S Rx function */
        SPII2S_ENABLE_RX(spii2s_base);

        LOG_I("Start record.");
    }
    break;
    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static rt_err_t nu_spii2s_stop(struct rt_audio_device *audio, int stream)
{
    nu_i2s_t psNuSPII2s = (nu_i2s_t)audio;
    nu_i2s_dai_t psNuSPII2sDai = RT_NULL;
    SPI_T *spii2s_base;

    RT_ASSERT(audio != RT_NULL);

    spii2s_base = (SPI_T *)psNuSPII2s->i2s_base;

    switch (stream)
    {
    case AUDIO_STREAM_REPLAY:
        psNuSPII2sDai = &psNuSPII2s->i2s_dais[NU_I2S_DAI_PLAYBACK];

        // Disable TX
        SPII2S_DISABLE_TXDMA(spii2s_base);
        SPII2S_DISABLE_TX(spii2s_base);

        LOG_I("Stop replay.");
        break;

    case AUDIO_STREAM_RECORD:
        psNuSPII2sDai = &psNuSPII2s->i2s_dais[NU_I2S_DAI_CAPTURE];

        // Disable RX
        SPII2S_DISABLE_RXDMA(spii2s_base);
        SPII2S_DISABLE_RX(spii2s_base);

        LOG_I("Stop record.");
        break;

    default:
        return -RT_EINVAL;
    }

    /* Stop DMA transfer. */
    nu_pdma_channel_terminate(psNuSPII2sDai->pdma_chanid);

    /* Close SPII2S */
    if (!(spii2s_base->I2SCTL & (SPI_I2SCTL_TXEN_Msk | SPI_I2SCTL_RXEN_Msk)))
    {
        SPII2S_DisableMCLK(spii2s_base);
        SPII2S_Close(spii2s_base);
        LOG_I("Close SPII2S.");
    }

    /* Silence */
    rt_memset((void *)psNuSPII2sDai->fifo, 0, NU_I2S_DMA_FIFO_SIZE);
    psNuSPII2sDai->fifo_block_idx = 0;

    return RT_EOK;
}

static void nu_spii2s_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    nu_i2s_t psNuSPII2s = (nu_i2s_t)audio;

    RT_ASSERT(audio != RT_NULL);
    RT_ASSERT(info != RT_NULL);

    info->buffer = (rt_uint8_t *)psNuSPII2s->i2s_dais[NU_I2S_DAI_PLAYBACK].fifo ;
    info->total_size = NU_I2S_DMA_FIFO_SIZE;
    info->block_size = NU_I2S_DMA_BUF_BLOCK_SIZE;
    info->block_count = NU_I2S_DMA_BUF_BLOCK_NUMBER;

    return;
}

static struct rt_audio_ops nu_spii2s_audio_ops =
{
    .getcaps     = nu_spii2s_getcaps,
    .configure   = nu_spii2s_configure,

    .init        = nu_spii2s_init,
    .start       = nu_spii2s_start,
    .stop        = nu_spii2s_stop,
    .transmit    = RT_NULL,
    .buffer_info = nu_spii2s_buffer_info
};

static rt_err_t nu_hw_spii2s_pdma_allocate(nu_i2s_dai_t psNuSPII2sDai)
{
    /* Allocate I2S nu_dma channel */
    if ((psNuSPII2sDai->pdma_chanid = nu_pdma_channel_allocate(psNuSPII2sDai->pdma_perp)) < 0)
    {
        goto nu_hw_spii2s_pdma_allocate;
    }

    return RT_EOK;

nu_hw_spii2s_pdma_allocate:

    return -(RT_ERROR);
}

int rt_hw_spii2s_init(void)
{
    int j = 0;
    nu_i2s_dai_t psNuSPII2sDai;

    for (j = (SPII2S_START + 1); j < SPII2S_CNT; j++)
    {
        int i = 0;
        for (i = 0; i < NU_I2S_DAI_CNT; i++)
        {
            uint8_t *pu8ptr = rt_malloc(NU_I2S_DMA_FIFO_SIZE);
            psNuSPII2sDai = &g_nu_spii2s_arr[j].i2s_dais[i];
            psNuSPII2sDai->fifo = pu8ptr;
            rt_memset(pu8ptr, 0, NU_I2S_DMA_FIFO_SIZE);
            RT_ASSERT(psNuSPII2sDai->fifo != RT_NULL);

            psNuSPII2sDai->pdma_chanid = -1;
            psNuSPII2sDai->fifo_block_idx = 0;
            RT_ASSERT(nu_hw_spii2s_pdma_allocate(psNuSPII2sDai) == RT_EOK);
            RT_ASSERT(nu_pdma_sgtbls_allocate(&psNuSPII2sDai->pdma_descs[0], NU_I2S_DMA_BUF_BLOCK_NUMBER) == RT_EOK);
        }

        /* Register ops of audio device */
        g_nu_spii2s_arr[j].audio.ops  = &nu_spii2s_audio_ops;

        /* Register device, RW: it is with replay and record functions. */
        rt_audio_register(&g_nu_spii2s_arr[j].audio, g_nu_spii2s_arr[j].name, RT_DEVICE_FLAG_RDWR, &g_nu_spii2s_arr[j]);
    }

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_spii2s_init);
#endif //#if defined(BSP_USING_SPII2S)
