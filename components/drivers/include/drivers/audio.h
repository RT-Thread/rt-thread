/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-05-09     Urey      first version
 */

#ifndef __AUDIO_H__
#define __AUDIO_H__

/* AUDIO command */
#define _AUDIO_CTL(a) (0x10 + a)

#define AUDIO_CTL_GETCAPS                   _AUDIO_CTL(1)
#define AUDIO_CTL_CONFIGURE                 _AUDIO_CTL(2)
#define AUDIO_CTL_SHUTDOWN                  _AUDIO_CTL(3)
#define AUDIO_CTL_START                     _AUDIO_CTL(4)
#define AUDIO_CTL_STOP                      _AUDIO_CTL(5)
#define AUDIO_CTL_PAUSE                     _AUDIO_CTL(6)
#define AUDIO_CTL_RESUME                    _AUDIO_CTL(7)
#define AUDIO_CTL_GETBUFFERINFO             _AUDIO_CTL(8)
#define AUDIO_CTL_ALLOCBUFFER               _AUDIO_CTL(9)
#define AUDIO_CTL_FREEBUFFER                _AUDIO_CTL(10)
#define AUDIO_CTL_HWRESET                   _AUDIO_CTL(11)


/* Audio Device Types */
#define AUDIO_TYPE_QUERY                    0x00
#define AUDIO_TYPE_INPUT                    0x01
#define AUDIO_TYPE_OUTPUT                   0x02
#define AUDIO_TYPE_MIXER                    0x04
#define AUDIO_TYPE_SELECTOR                 0x08
#define AUDIO_TYPE_EFFECT                   0x10

/* Audio Format Types */
#define AUDIO_FMT_PCM_U8                    0x0001
#define AUDIO_FMT_PCM_S8                    0x0002

#define AUDIO_FMT_PCM_U16_LE                0x0010
#define AUDIO_FMT_PCM_S16_BE                0x0020
#define AUDIO_FMT_PCM_S16_LE                0x0040
#define AUDIO_FMT_PCM_U16_BE                0x0080
#define AUDIO_FMT_PCM_U24_LE                0x0100
#define AUDIO_FMT_PCM_S24_BE                0x0200
#define AUDIO_FMT_PCM_S24_LE                0x0400
#define AUDIO_FMT_PCM_U24_BE                0x0800
#define AUDIO_FMT_PCM_U32_LE                0x1000
#define AUDIO_FMT_PCM_S32_BE                0x2000
#define AUDIO_FMT_PCM_S32_LE                0x4000
#define AUDIO_FMT_PCM_U32_BE                0x8000

/* Supported Sampling Rates */
#define AUDIO_SAMP_RATE_8K                  0x0001
#define AUDIO_SAMP_RATE_11K                 0x0002
#define AUDIO_SAMP_RATE_16K                 0x0004
#define AUDIO_SAMP_RATE_22K                 0x0008
#define AUDIO_SAMP_RATE_32K                 0x0010
#define AUDIO_SAMP_RATE_44K                 0x0020
#define AUDIO_SAMP_RATE_48K                 0x0040
#define AUDIO_SAMP_RATE_96K                 0x0080
#define AUDIO_SAMP_RATE_128K                0x0100
#define AUDIO_SAMP_RATE_160K                0x0200
#define AUDIO_SAMP_RATE_172K                0x0400
#define AUDIO_SAMP_RATE_192K                0x0800

/* Supported Bit Rates */
#define AUDIO_BIT_RATE_22K                  0x01
#define AUDIO_BIT_RATE_44K                  0x02
#define AUDIO_BIT_RATE_48K                  0x04
#define AUDIO_BIT_RATE_96K                  0x08
#define AUDIO_BIT_RATE_128K                 0x10
#define AUDIO_BIT_RATE_160K                 0x20
#define AUDIO_BIT_RATE_172K                 0x40
#define AUDIO_BIT_RATE_192K                 0x80



/* Support Dsp(input/output) Units controls */
#define AUDIO_DSP_PARAM                     0           /* get/set all params */
#define AUDIO_DSP_SAMPLERATE                1                       /*  采样频率                    */
#define AUDIO_DSP_FMT                       2
#define AUDIO_DSP_CHANNELS                  3

/* Supported Mixer Units controls */
#define AUDIO_MIXER_QUERY                   0x0000
#define AUDIO_MIXER_MUTE                    0x0001
#define AUDIO_MIXER_VOLUME                  0x0002
#define AUDIO_MIXER_BASS                    0x0004
#define AUDIO_MIXER_MID                     0x0008
#define AUDIO_MIXER_TREBLE                  0x0010
#define AUDIO_MIXER_EQUALIZER               0x0020
#define AUDIO_MIXER_LINE                    0x0040
#define AUDIO_MIXER_DIGITAL                 0x0080
#define AUDIO_MIXER_MIC                     0x0100

#define AUDIO_MIXER_EXTEND                  0x8000    //extend mixer command

#define CFG_AUDIO_REPLAY_QUEUE_COUNT        4
#define CFG_AUDIO_RECORD_PIPE_SIZE          (8 * 1024)
#define AUDIO_DEVICE_MP_CNT                 (4)
#define AUDIO_DEVICE_DECODE_MP_BLOCK_SZ     (4352 * 4)
#define AUDIO_DEVICE_DECODE_MP_SZ           ((AUDIO_DEVICE_DECODE_MP_BLOCK_SZ*2 + 4)*AUDIO_DEVICE_MP_CNT)


enum
{
    AUDIO_STREAM_REPLAY = 0,
    AUDIO_STREAM_RECORD,
    AUDIO_STREAM_LAST = AUDIO_STREAM_RECORD,
};

/* the preferred number and size of audio pipeline buffer for the audio device */
struct rt_audio_buf_info
{
  rt_uint32_t buffer_size;          /* Preferred qty of buffers */
  rt_uint32_t buffer_count;           /* Preferred size of the buffers */
};
struct rt_audio_buf_desc
{
  rt_uint8_t *data_ptr;
  rt_size_t data_size;
};

struct rt_audio_frame
{
    const void *data_ptr;
    rt_size_t   data_size;
};

struct rt_audio_device;
struct rt_audio_caps;
struct rt_audio_configure;
struct rt_audio_ops
{
    rt_err_t  (*getcaps)        (struct rt_audio_device *audio,struct rt_audio_caps *caps);
    rt_err_t  (*configure)      (struct rt_audio_device *audio,struct rt_audio_caps *caps);

    rt_err_t    (*init)         (struct rt_audio_device *audio);
    rt_err_t    (*shutdown)     (struct rt_audio_device *audio);
    rt_err_t    (*start)        (struct rt_audio_device *audio,int stream);
    rt_err_t    (*stop)         (struct rt_audio_device *audio,int stream);
    rt_err_t    (*suspend)      (struct rt_audio_device *audio,int stream);
    rt_err_t    (*resume)       (struct rt_audio_device *audio,int stream);

    rt_err_t    (*control)      (struct rt_audio_device *audio, int cmd, void *arg);
    rt_size_t   (*transmit)     (struct rt_audio_device *audio, const void *writeBuf,void *readBuf, rt_size_t size);

    //get page size of codec or private buffer's info
    void    (*buffer_info)      (struct rt_audio_device *audio,struct rt_audio_buf_info *info );
};


struct rt_audio_configure
{
    rt_uint32_t channels;

    rt_uint32_t samplefmt;
    rt_uint32_t samplerate;
    rt_uint32_t samplefmts;
};

struct rt_audio_caps
{
  int main_type;
  int sub_type;

  union
  {
    rt_uint32_t mask;
    int     value;
    struct rt_audio_configure config;
  }udata;
};

struct rt_audio_replay
{
    rt_bool_t activated;
    struct rt_data_queue queue;
};

struct rt_audio_record
{
    rt_bool_t activated;
};

struct rt_audio_device
{
    struct rt_device            parent;
    struct rt_audio_ops        *ops;

    struct rt_mempool           mp;

    struct rt_audio_replay     *replay;
    struct rt_audio_record     *record;
};

rt_err_t    rt_audio_register       (struct rt_audio_device *audio, const char *name, rt_uint32_t flag, void *data);
void        rt_audio_tx_complete    (struct rt_audio_device *audio,rt_uint8_t *pbuf);
void        rt_audio_rx_done        (struct rt_audio_device *audio,rt_uint8_t *pbuf,rt_size_t len);
rt_uint32_t rt_audio_format_to_bits (rt_uint32_t format);


/* Device Control Commands */
#define CODEC_CMD_RESET             0
#define CODEC_CMD_SET_VOLUME        1
#define CODEC_CMD_GET_VOLUME        2
#define CODEC_CMD_SAMPLERATE        3
#define CODEC_CMD_EQ                4
#define CODEC_CMD_3D                5

#define CODEC_VOLUME_MAX            (63)

#endif /* __AUDIO_H__ */
