/**************************************************************************//**
*
* @copyright (C) 2020 Nuvoton Technology Corp. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Change Logs:
* Date            Author           Notes
* 2020-12-12      Wayne Lin        First version
*
******************************************************************************/

#include <rtconfig.h>

#if defined(BSP_USING_I2S)

#include <rtdevice.h>
#include <drv_i2s.h>
#include "NuMicro.h"

/* Private define ---------------------------------------------------------------*/
#define DBG_ENABLE
#define DBG_LEVEL DBG_LOG
#define DBG_SECTION_NAME  "i2s"
#define DBG_COLOR
#include <rtdbg.h>

#define I2S_RSR_R_DMA_RIA_IRQ_Pos   (0)
#define I2S_RSR_R_DMA_RIA_IRQ_Msk   (1<<I2S_RSR_R_DMA_RIA_IRQ_Pos)
#define I2S_RSR_R_DMA_RIA_SN_Pos    (5)
#define I2S_RSR_R_DMA_RIA_SN_Msk    (7<<I2S_RSR_R_DMA_RIA_SN_Pos)

#define I2S_GLBCON_P_DMA_IRQ_Pos       (10)
#define I2S_GLBCON_P_DMA_IRQ_Msk       (1<<I2S_GLBCON_P_DMA_IRQ_Pos)
#define I2S_GLBCON_R_DMA_IRQ_Pos       (11)
#define I2S_GLBCON_R_DMA_IRQ_Msk       (1<<I2S_GLBCON_R_DMA_IRQ_Pos)

#define I2S_PSP_P_DMA_RIA_I_Pos        (0)
#define I2S_PSP_P_DMA_RIA_I_Msk        (1<<I2S_PSP_P_DMA_RIA_I_Pos)
#define I2S_PSP_DMA_DATA_ZERO_IRQ_Pos  (3)
#define I2S_PSP_DMA_DATA_ZERO_IRQ_Msk  (1<<I2S_PSP_DMA_DATA_ZERO_IRQ_Pos)
#define I2S_PSP_DMA_CNTER_IRQ_Pos      (4)
#define I2S_PSP_DMA_CNTER_IRQ_Msk      (1<<I2S_PSP_DMA_CNTER_IRQ_Pos)

#define I2S_RESET_PLAY_Pos        (5)
#define I2S_RESET_PLAY_Msk        (1<<I2S_RESET_PLAY_Pos)
#define I2S_RESET_RECORD_Pos      (6)
#define I2S_RESET_RECORD_Msk      (1<<I2S_RESET_RECORD_Pos)

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
    .irqn = IRQ_I2S,
    .rstidx = I2SRST,
    .clkidx = I2SCKEN,
};

static void nu_i2s_isr(int vector, void *param)
{
    nu_i2s_t psNuI2s = (nu_i2s_t)param;
    volatile uint32_t u32RegAudCtl = inpw(REG_I2S_CON);

    if (u32RegAudCtl & I2S_GLBCON_P_DMA_IRQ_Msk)
    {
        volatile uint32_t u32RegPlayStatus = inpw(REG_I2S_PSR);
        outpw(REG_I2S_CON, u32RegAudCtl | I2S_GLBCON_P_DMA_IRQ_Msk);  //Clear TX INT

        if (u32RegPlayStatus & I2S_PSP_DMA_CNTER_IRQ_Msk)
        {
            outpw(REG_I2S_PSR, I2S_PSP_DMA_CNTER_IRQ_Msk);
            rt_kprintf("\ndebug:DMA_COUNTER_IRQ occur\n");
        }

        if (u32RegPlayStatus & I2S_PSP_DMA_DATA_ZERO_IRQ_Msk)
        {
            outpw(REG_I2S_PSR, I2S_PSP_DMA_DATA_ZERO_IRQ_Msk);
            rt_kprintf("\ndebug:DMA_DATA_ZERO_IRQ occur\n");
        }

        if (u32RegPlayStatus & I2S_PSP_P_DMA_RIA_I_Msk)
        {
            /* Clear Playback status of DMA reach indicate address interrupt. */
            outpw(REG_I2S_PSR, I2S_PSP_P_DMA_RIA_I_Msk);
            rt_audio_tx_complete(&psNuI2s->audio);
        }
    }

    if (u32RegAudCtl & I2S_GLBCON_R_DMA_IRQ_Msk)
    {
        volatile uint32_t u32RegRecordStatus = inpw(REG_I2S_RSR);

        outpw(REG_I2S_CON, u32RegAudCtl | I2S_GLBCON_R_DMA_IRQ_Msk);  //Clear RX INT

        /* Record DMA Reach Indicative Address Interrupt Request Bit */
        /* 0 = Record DMA address does not reach the indicative address by R_DMA_IRQ_SEL */
        /* 1 = Record DMA address does reach the indicative address by R_DMA_IRQ_SEL */
        /* Note: This bit is readable, and can only be cleared by writing '1' to it. */
        if (u32RegRecordStatus & I2S_RSR_R_DMA_RIA_IRQ_Msk)
        {
            nu_i2s_dai_t psNuI2sDai = &psNuI2s->i2s_dais[NU_I2S_DAI_CAPTURE];

            /*
            Record DMA Reach Indicative Address Section Number Bit (Read Only)
            R_DMA_IRQ_SEL (I2S_GLBCON[15:14]) = 01, R_DMA_RIA_SN[2:0]= 1, 0.
            R_DMA_IRQ_SEL (I2S_GLBCON[15:14]) = 10, R_DMA_RIA_SN[2:0]= 1, 2, 3, 0.
            R_DMA_IRQ_SEL (I2S_GLBCON[15:14]) = 11, R_DMA_RIA_SN[2:0]= 1, 2, 3, 4, 5, 6, 7, 0.
            */
            uint8_t u8FifoBlockIdx = (u32RegRecordStatus & I2S_RSR_R_DMA_RIA_SN_Msk) >> I2S_RSR_R_DMA_RIA_SN_Pos;

            rt_uint8_t *pbuf = (uint8_t *)((uint32_t)&psNuI2sDai->fifo[u8FifoBlockIdx * NU_I2S_DMA_BUF_BLOCK_SIZE] | NONCACHEABLE);

            /* Clear Record status of DMA reach indicate address interrupt. */
            outpw(REG_I2S_RSR, I2S_RSR_R_DMA_RIA_IRQ_Msk);

            /* Report upper layer. */
            rt_audio_rx_done(&psNuI2s->audio, pbuf, NU_I2S_DMA_BUF_BLOCK_SIZE);
        }
    }

}

static rt_bool_t nu_i2s_capacity_check(struct rt_audio_configure *pconfig)
{
    switch (pconfig->samplebits)
    {
    case  8:
    case 16:
    case 24:
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

        /* Open I2S */
        if (i2sOpen() != 0)
            goto exit_nu_i2s_dai_setup;

        /* Select I2S function */
        i2sIoctl(I2S_SELECT_BLOCK, I2S_BLOCK_I2S, 0);

        /* Select Data width */
        i2sIoctl(I2S_SELECT_BIT, ((pconfig->samplebits / 8) - 1), 0);

        if (pconfig->channels > 1)
        {
            /* Set to stereo */
            i2sIoctl(I2S_SET_CHANNEL, I2S_PLAY, I2S_CHANNEL_P_I2S_TWO);
            i2sIoctl(I2S_SET_CHANNEL, I2S_REC, I2S_CHANNEL_R_I2S_TWO);
        }
        else
        {
            /* Set to mono */
            i2sIoctl(I2S_SET_CHANNEL, I2S_PLAY, I2S_CHANNEL_P_I2S_ONE);
            i2sIoctl(I2S_SET_CHANNEL, I2S_REC, I2S_CHANNEL_R_I2S_LEFT_PCM_SLOT0);
        }

        /* Set DMA interrupt selection to half of DMA buffer */
        switch (NU_I2S_DMA_BUF_BLOCK_NUMBER)
        {
        case 2:
            i2sIoctl(I2S_SET_PLAY_DMA_INT_SEL, I2S_DMA_INT_HALF, 0);
            i2sIoctl(I2S_SET_REC_DMA_INT_SEL, I2S_DMA_INT_HALF, 0);
            break;
        case 4:
            i2sIoctl(I2S_SET_PLAY_DMA_INT_SEL, I2S_DMA_INT_QUARTER, 0);
            i2sIoctl(I2S_SET_REC_DMA_INT_SEL, I2S_DMA_INT_QUARTER, 0);
            break;
        case 8:
            i2sIoctl(I2S_SET_PLAY_DMA_INT_SEL, I2S_DMA_INT_EIGHTH, 0);
            i2sIoctl(I2S_SET_REC_DMA_INT_SEL, I2S_DMA_INT_EIGHTH, 0);
            break;
        default:
            RT_ASSERT(0);
            break;
        }

        /* Set DMA buffer address */
        i2sIoctl(I2S_SET_DMA_ADDRESS, I2S_PLAY, (uint32_t)&psNuI2s->i2s_dais[NU_I2S_DAI_PLAYBACK].fifo[0]);
        i2sIoctl(I2S_SET_DMA_ADDRESS, I2S_REC, (uint32_t)&psNuI2s->i2s_dais[NU_I2S_DAI_CAPTURE].fifo[0]);

        /* Set DMA buffer length */
        i2sIoctl(I2S_SET_DMA_LENGTH, I2S_PLAY, NU_I2S_DMA_FIFO_SIZE);
        i2sIoctl(I2S_SET_DMA_LENGTH, I2S_REC, NU_I2S_DMA_FIFO_SIZE);

        /* Select I2S format */
        i2sIoctl(I2S_SET_I2S_FORMAT, I2S_FORMAT_I2S, 0);

        if (psNuI2s->AcodecOps->role == NU_ACODEC_ROLE_MASTER)
        {
            if (pconfig->samplerate % 11025)
            {
                // 12.288MHz ==> APLL=98.4MHz / 8 = 12.3MHz
                // APLL is 98.4MHz
                /*
                     FB_DV  = 0x28 ->  N=FB_DV+1 -> N=41
                     IN_DV  = 0    ->  M=IN_DV+1 -> M=1
                     OUT_DV = 4    ->  P=4+1     -> P=5
                     Fpllout = 12MHz * N / (M*P) -> Fpllout = 12MHz * 41 / (5*1) = 98.4 MHz
                */
                outpw(REG_CLK_APLLCON, 0xC0008028);

                // Select APLL as I2S source and divider is (7+1)
                outpw(REG_CLK_DIVCTL1, (inpw(REG_CLK_DIVCTL1) & ~0x001f0000) | (0x2 << 19) | (0x7 << 24));

                // Set sampleing rate, data width, channel
                i2sSetSampleRate(12300000, pconfig->samplerate, pconfig->samplebits, pconfig->channels);
            }
            else
            {
                // 11.2896MHz ==> APLL=90MHz / 8 = 11.25MHz
                // APLL is 90MHz
                /*
                     FB_DV  = 0x2D ->  N=FB_DV+1 -> N=45
                     IN_DV  = 0    ->  M=IN_DV+1 -> M=1
                     OUT_DV = 5    ->  P=5+1     -> P=6
                     Fpllout = 12MHz * N / (M*P) -> Fpllout = 12MHz * 45 / (6*1) = 90 MHz
                */
                outpw(REG_CLK_APLLCON, 0xC000A02D);

                // Select APLL as I2S source and divider is (7+1)
                outpw(REG_CLK_DIVCTL1, (inpw(REG_CLK_DIVCTL1) & ~0x001f0000) | (0x2 << 19) | (0x7 << 24));

                // Set sampleing rate, data width, channel
                i2sSetSampleRate(11250000, pconfig->samplerate, pconfig->samplebits, pconfig->channels);
            }
            // Set as master
            i2sIoctl(I2S_SET_MODE, I2S_MODE_MASTER, 0);
        }
        else
        {
            // Set as slave, source clock is XIN (12MHz)
            i2sIoctl(I2S_SET_MODE, I2S_MODE_SLAVE, 0);
        }

        LOG_I("Open I2S.");

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

    /* Enable IP engine clock */
    nu_sys_ipclk_enable(psNuI2s->clkidx);

    /* Reset IP engine */
    nu_sys_ip_reset(psNuI2s->rstidx);

    /* Enable interrupt */
    rt_hw_interrupt_umask(psNuI2s->irqn);

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
        i2sIoctl(I2S_SET_PLAY, I2S_START_PLAY, 0);

        LOG_I("Start replay.");
    }
    break;

    case AUDIO_STREAM_RECORD:
    {
        i2sIoctl(I2S_SET_RECORD, I2S_START_REC, 0);

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

        i2sIoctl(I2S_SET_PLAY, I2S_STOP_PLAY, 0);

        LOG_I("Stop replay.");
        break;

    case AUDIO_STREAM_RECORD:
        psNuI2sDai = &psNuI2s->i2s_dais[NU_I2S_DAI_CAPTURE];

        i2sIoctl(I2S_SET_RECORD, I2S_STOP_REC, 0);

        LOG_I("Stop record.");
        break;

    default:
        return -RT_EINVAL;
    }

    /* Close I2S if record and playback path. */
    if (!((inpw(REG_I2S_RESET)&I2S_RESET_PLAY_Msk) || (inpw(REG_I2S_RESET)&I2S_RESET_RECORD_Msk)))
    {
        i2sClose();
        LOG_I("Close I2S.");
    }

    /* Silence */
    rt_memset((void *)psNuI2sDai->fifo, 0, NU_I2S_DMA_FIFO_SIZE);

    return RT_EOK;
}

static void nu_i2s_buffer_info(struct rt_audio_device *audio, struct rt_audio_buf_info *info)
{
    nu_i2s_t psNuI2s;

    RT_ASSERT(audio != RT_NULL);
    RT_ASSERT(info != RT_NULL);

    psNuI2s = (nu_i2s_t)audio;

    /* Define it a NONCACHEABLE address. */
    info->buffer = (rt_uint8_t *)((uint32_t)psNuI2s->i2s_dais[NU_I2S_DAI_PLAYBACK].fifo | NONCACHEABLE) ;
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

int rt_hw_i2s_init(void)
{
    int i = 0;
    nu_i2s_dai_t psNuI2sDai;

    for (i = 0; i < NU_I2S_DAI_CNT; i++)
    {
        psNuI2sDai = &g_nu_i2s_dev.i2s_dais[i];

        /* Allocate playback and record FIFO buffer. */
        psNuI2sDai->fifo = (uint8_t *)rt_malloc_align(NU_I2S_DMA_FIFO_SIZE, 32);
        RT_ASSERT(psNuI2sDai->fifo != RT_NULL);

        rt_memset(psNuI2sDai->fifo, 0, NU_I2S_DMA_FIFO_SIZE);
    }

    /* Register ops of audio device */
    g_nu_i2s_dev.audio.ops  = &nu_i2s_audio_ops;

    /* Register device, RW: it is with replay and record functions. */
    rt_audio_register(&g_nu_i2s_dev.audio, g_nu_i2s_dev.name, RT_DEVICE_FLAG_RDWR, &g_nu_i2s_dev);

    /* Register I2S ISR */
    rt_hw_interrupt_install(g_nu_i2s_dev.irqn, nu_i2s_isr, &g_nu_i2s_dev, g_nu_i2s_dev.name);

    return RT_EOK;
}
INIT_DEVICE_EXPORT(rt_hw_i2s_init);
#endif //#if defined(BSP_USING_I2S)
