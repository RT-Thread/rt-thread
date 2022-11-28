/*
* Copyright (c) 2019-2025 Allwinner Technology Co., Ltd. ALL rights reserved.
*
* Allwinner is a trademark of Allwinner Technology Co.,Ltd., registered in
* the the people's Republic of China and other countries.
* All Allwinner Technology Co.,Ltd. trademarks are used with permission.
*
* DISCLAIMER
* THIRD PARTY LICENCES MAY BE REQUIRED TO IMPLEMENT THE SOLUTION/PRODUCT.
* IF YOU NEED TO INTEGRATE THIRD PARTY’S TECHNOLOGY (SONY, DTS, DOLBY, AVS OR MPEGLA, ETC.)
* IN ALLWINNERS’SDK OR PRODUCTS, YOU SHALL BE SOLELY RESPONSIBLE TO OBTAIN
* ALL APPROPRIATELY REQUIRED THIRD PARTY LICENCES.
* ALLWINNER SHALL HAVE NO WARRANTY, INDEMNITY OR OTHER OBLIGATIONS WITH RESPECT TO MATTERS
* COVERED UNDER ANY REQUIRED THIRD PARTY LICENSE.
* YOU ARE SOLELY RESPONSIBLE FOR YOUR USAGE OF THIRD PARTY’S TECHNOLOGY.
*
*
* THIS SOFTWARE IS PROVIDED BY ALLWINNER"AS IS" AND TO THE MAXIMUM EXTENT
* PERMITTED BY LAW, ALLWINNER EXPRESSLY DISCLAIMS ALL WARRANTIES OF ANY KIND,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING WITHOUT LIMITATION REGARDING
* THE TITLE, NON-INFRINGEMENT, ACCURACY, CONDITION, COMPLETENESS, PERFORMANCE
* OR MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
* IN NO EVENT SHALL ALLWINNER BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
* NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS, OR BUSINESS INTERRUPTION)
* HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
* STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
* ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef __SOUND_PCM_H
#define __SOUND_PCM_H
#include <unistd.h>
#define SND_SOC_DAIFMT_I2S              1 /* I2S mode */
#define SND_SOC_DAIFMT_RIGHT_J          2 /* Right Justified mode */
#define SND_SOC_DAIFMT_LEFT_J           3 /* Left Justified mode */
#define SND_SOC_DAIFMT_DSP_A            4 /* L data MSB after FRM LRC */
#define SND_SOC_DAIFMT_DSP_B            5 /* L data MSB during FRM LRC */
#define SND_SOC_DAIFMT_AC97             6 /* AC97 */
#define SND_SOC_DAIFMT_PDM              7 /* Pulse density modulation */

/* left and right justified also known as MSB and LSB respectively */
#define SND_SOC_DAIFMT_MSB              SND_SOC_DAIFMT_LEFT_J
#define SND_SOC_DAIFMT_LSB              SND_SOC_DAIFMT_RIGHT_J

#define SND_SOC_DAIFMT_SIG_SHIFT        8
#define SND_SOC_DAIFMT_MASTER_SHIFT     12

#define SND_SOC_DAIFMT_NB_NF            (1 << 8) /* normal bit clock + frame */
#define SND_SOC_DAIFMT_NB_IF            (2 << 8) /* normal BCLK + inv FRM */
#define SND_SOC_DAIFMT_IB_NF            (3 << 8) /* invert BCLK + nor FRM */
#define SND_SOC_DAIFMT_IB_IF            (4 << 8) /* invert BCLK + FRM */

#define SND_SOC_DAIFMT_CBM_CFM          (1 << 12) /* codec clk & FRM master */
#define SND_SOC_DAIFMT_CBS_CFM          (2 << 12) /* codec clk slave & FRM master */
#define SND_SOC_DAIFMT_CBM_CFS          (3 << 12) /* codec clk master & frame slave */
#define SND_SOC_DAIFMT_CBS_CFS          (4 << 12) /* codec clk & FRM slave */

#define SND_SOC_DAIFMT_FORMAT_MASK      0x000f
#define SND_SOC_DAIFMT_CLOCK_MASK       0x00f0
#define SND_SOC_DAIFMT_INV_MASK         0x0f00
#define SND_SOC_DAIFMT_MASTER_MASK      0xf000

#define SNDRV_PCM_IOCTL1_RESET          0
/* 1 is absent slot. */
#define SNDRV_PCM_IOCTL1_CHANNEL_INFO   2
#define SNDRV_PCM_IOCTL1_GSTATE         3
#define SNDRV_PCM_IOCTL1_FIFO_SIZE      4

#define SNDRV_PCM_TRIGGER_STOP          0
#define SNDRV_PCM_TRIGGER_START         1
#define SNDRV_PCM_TRIGGER_PAUSE_PUSH    3
#define SNDRV_PCM_TRIGGER_PAUSE_RELEASE 4
#define SNDRV_PCM_TRIGGER_SUSPEND       5
#define SNDRV_PCM_TRIGGER_RESUME        6
#define SNDRV_PCM_TRIGGER_DRAIN         7


#define SNDRV_PCM_RATE_5512             (1<<0)          /* 5512Hz */
#define SNDRV_PCM_RATE_8000             (1<<1)          /* 8000Hz */
#define SNDRV_PCM_RATE_11025            (1<<2)          /* 11025Hz */
#define SNDRV_PCM_RATE_16000            (1<<3)          /* 16000Hz */
#define SNDRV_PCM_RATE_22050            (1<<4)          /* 22050Hz */
#define SNDRV_PCM_RATE_32000            (1<<5)          /* 32000Hz */
#define SNDRV_PCM_RATE_44100            (1<<6)          /* 44100Hz */
#define SNDRV_PCM_RATE_48000            (1<<7)          /* 48000Hz */
#define SNDRV_PCM_RATE_64000            (1<<8)          /* 64000Hz */
#define SNDRV_PCM_RATE_88200            (1<<9)          /* 88200Hz */
#define SNDRV_PCM_RATE_96000            (1<<10)         /* 96000Hz */
#define SNDRV_PCM_RATE_176400           (1<<11)         /* 176400Hz */
#define SNDRV_PCM_RATE_192000           (1<<12)         /* 192000Hz */

#define SNDRV_PCM_RATE_CONTINUOUS       (1<<30)         /* continuous range */
#define SNDRV_PCM_RATE_KNOT             (1<<31)         /* supports more non-continuos rates */

#define SNDRV_PCM_RATE_8000_44100       (SNDRV_PCM_RATE_8000|SNDRV_PCM_RATE_11025|\
                                         SNDRV_PCM_RATE_16000|SNDRV_PCM_RATE_22050|\
                                         SNDRV_PCM_RATE_32000|SNDRV_PCM_RATE_44100)
#define SNDRV_PCM_RATE_8000_48000       (SNDRV_PCM_RATE_8000_44100|SNDRV_PCM_RATE_48000)
#define SNDRV_PCM_RATE_8000_96000       (SNDRV_PCM_RATE_8000_48000|SNDRV_PCM_RATE_64000|\
                                         SNDRV_PCM_RATE_88200|SNDRV_PCM_RATE_96000)
#define SNDRV_PCM_RATE_8000_192000      (SNDRV_PCM_RATE_8000_96000|SNDRV_PCM_RATE_176400|\
                                         SNDRV_PCM_RATE_192000)

#define SNDRV_PCM_FORMAT_S8 ((snd_pcm_format_t) 0)
#define SNDRV_PCM_FORMAT_U8 ((snd_pcm_format_t) 1)
#define SNDRV_PCM_FORMAT_S16_LE ((snd_pcm_format_t) 2)
#define SNDRV_PCM_FORMAT_S16_BE ((snd_pcm_format_t) 3)
#define SNDRV_PCM_FORMAT_U16_LE ((snd_pcm_format_t) 4)
#define SNDRV_PCM_FORMAT_U16_BE ((snd_pcm_format_t) 5)
#define SNDRV_PCM_FORMAT_S24_LE ((snd_pcm_format_t) 6)
#define SNDRV_PCM_FORMAT_S24_BE ((snd_pcm_format_t) 7)
#define SNDRV_PCM_FORMAT_U24_LE ((snd_pcm_format_t) 8)
#define SNDRV_PCM_FORMAT_U24_BE ((snd_pcm_format_t) 9)
#define SNDRV_PCM_FORMAT_S32_LE ((snd_pcm_format_t) 10)
#define SNDRV_PCM_FORMAT_S32_BE ((snd_pcm_format_t) 11)
#define SNDRV_PCM_FORMAT_U32_LE ((snd_pcm_format_t) 12)
#define SNDRV_PCM_FORMAT_U32_BE ((snd_pcm_format_t) 13)

#define _SNDRV_PCM_FMTBIT(fmt)          (1ULL << (int)SND_PCM_FORMAT_##fmt)
#define SNDRV_PCM_FMTBIT_S8             _SNDRV_PCM_FMTBIT(S8)
#define SNDRV_PCM_FMTBIT_U8             _SNDRV_PCM_FMTBIT(U8)
#define SNDRV_PCM_FMTBIT_S16_LE         _SNDRV_PCM_FMTBIT(S16_LE)
#define SNDRV_PCM_FMTBIT_S16_BE         _SNDRV_PCM_FMTBIT(S16_BE)
#define SNDRV_PCM_FMTBIT_U16_LE         _SNDRV_PCM_FMTBIT(U16_LE)
#define SNDRV_PCM_FMTBIT_U16_BE         _SNDRV_PCM_FMTBIT(U16_BE)
#define SNDRV_PCM_FMTBIT_S24_LE         _SNDRV_PCM_FMTBIT(S24_LE)
#define SNDRV_PCM_FMTBIT_S24_BE         _SNDRV_PCM_FMTBIT(S24_BE)
#define SNDRV_PCM_FMTBIT_U24_LE         _SNDRV_PCM_FMTBIT(U24_LE)
#define SNDRV_PCM_FMTBIT_U24_BE         _SNDRV_PCM_FMTBIT(U24_BE)
#define SNDRV_PCM_FMTBIT_S32_LE         _SNDRV_PCM_FMTBIT(S32_LE)
#define SNDRV_PCM_FMTBIT_S32_BE         _SNDRV_PCM_FMTBIT(S32_BE)
#define SNDRV_PCM_FMTBIT_U32_LE         _SNDRV_PCM_FMTBIT(U32_LE)
#define SNDRV_PCM_FMTBIT_U32_BE         _SNDRV_PCM_FMTBIT(U32_BE)


#ifdef SNDRV_LITTLE_ENDIAN
#define SNDRV_PCM_FMTBIT_S16            SNDRV_PCM_FMTBIT_S16_LE
#define SNDRV_PCM_FMTBIT_U16            SNDRV_PCM_FMTBIT_U16_LE
#define SNDRV_PCM_FMTBIT_S24            SNDRV_PCM_FMTBIT_S24_LE
#define SNDRV_PCM_FMTBIT_U24            SNDRV_PCM_FMTBIT_U24_LE
#define SNDRV_PCM_FMTBIT_S32            SNDRV_PCM_FMTBIT_S32_LE
#define SNDRV_PCM_FMTBIT_U32            SNDRV_PCM_FMTBIT_U32_LE
#define SNDRV_PCM_FMTBIT_FLOAT          SNDRV_PCM_FMTBIT_FLOAT_LE
#define SNDRV_PCM_FMTBIT_FLOAT64        SNDRV_PCM_FMTBIT_FLOAT64_LE
#define SNDRV_PCM_FMTBIT_IEC958_SUBFRAME SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_LE
#endif
#ifdef SNDRV_BIG_ENDIAN
#define SNDRV_PCM_FMTBIT_S16            SNDRV_PCM_FMTBIT_S16_BE
#define SNDRV_PCM_FMTBIT_U16            SNDRV_PCM_FMTBIT_U16_BE
#define SNDRV_PCM_FMTBIT_S24            SNDRV_PCM_FMTBIT_S24_BE
#define SNDRV_PCM_FMTBIT_U24            SNDRV_PCM_FMTBIT_U24_BE
#define SNDRV_PCM_FMTBIT_S32            SNDRV_PCM_FMTBIT_S32_BE
#define SNDRV_PCM_FMTBIT_U32            SNDRV_PCM_FMTBIT_U32_BE
#define SNDRV_PCM_FMTBIT_FLOAT          SNDRV_PCM_FMTBIT_FLOAT_BE
#define SNDRV_PCM_FMTBIT_FLOAT64        SNDRV_PCM_FMTBIT_FLOAT64_BE
#define SNDRV_PCM_FMTBIT_IEC958_SUBFRAME SNDRV_PCM_FMTBIT_IEC958_SUBFRAME_BE
#endif

static inline snd_pcm_sframes_t bytes_to_frames(struct snd_pcm_runtime *runtime, ssize_t size)
{
    return size * 8 / runtime->frame_bits;
}

static inline ssize_t frames_to_bytes(struct snd_pcm_runtime *runtime, snd_pcm_sframes_t size)
{
    return size * runtime->frame_bits / 8;
}

static inline size_t snd_pcm_lib_buffer_bytes(struct snd_pcm_substream *substream)
{
    struct snd_pcm_runtime *runtime = substream->runtime;
    return frames_to_bytes(runtime, runtime->buffer_size);
}

static inline size_t snd_pcm_lib_period_bytes(struct snd_pcm_substream *substream)
{
    struct snd_pcm_runtime *runtime = substream->runtime;
    return frames_to_bytes(runtime, runtime->period_size);
}

/* Get the available(readable) space for capture */
static inline snd_pcm_uframes_t snd_pcm_capture_avail(struct snd_pcm_runtime *runtime)
{
    snd_pcm_sframes_t avail = runtime->status->hw_ptr - runtime->control->appl_ptr;
    if (avail < 0)
        avail += runtime->boundary;
    return avail;
}

/* Get the available(writeable) space for playback */
static inline snd_pcm_uframes_t snd_pcm_playback_avail(struct snd_pcm_runtime *runtime)
{
    snd_pcm_sframes_t avail = runtime->status->hw_ptr + runtime->buffer_size - runtime->control->appl_ptr;

    if (avail < 0)
        avail += runtime->boundary;
    else if ((snd_pcm_uframes_t) avail >= runtime->boundary)
        avail -= runtime->boundary;

    return avail;
}

/* Get the queued space(has been written) for playback */
static inline snd_pcm_sframes_t snd_pcm_playback_hw_avail(struct snd_pcm_runtime *runtime)
{
    return runtime->buffer_size - snd_pcm_playback_avail(runtime);
}

/* Get the free space for capture */
static inline snd_pcm_sframes_t snd_pcm_capture_hw_avail(struct snd_pcm_runtime *runtime)
{
    return runtime->buffer_size - snd_pcm_capture_avail(runtime);
}

static inline int snd_pcm_playback_data(struct snd_pcm_substream *substream)
{
    struct snd_pcm_runtime *runtime = substream->runtime;

    if (runtime->stop_threshold >= runtime->boundary)
        return 1;

    return snd_pcm_playback_avail(runtime) < runtime->buffer_size;
}

static inline int snd_pcm_playback_empty(struct snd_pcm_substream *substream)
{
    struct snd_pcm_runtime *runtime = substream->runtime;
    return snd_pcm_playback_avail(runtime) >= runtime->buffer_size;
}

#endif /* __SOUND_PCM_H */
