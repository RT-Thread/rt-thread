/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-05-09     Urey         first version
 * 2019-07-09     Zero-Free    improve device ops interface and data flows
 *
 */

#ifndef __DEV_AUDIO_H__
#define __DEV_AUDIO_H__

#include "dev_audio_pipe.h"

/**
 * @defgroup group_Audio Audio
 *
 * @ingroup group_Drivers RT-Thread Drivers
 *
 * @brief Audio driver API.
 */

/**
 * @addtogroup group_Audio
 * @{
 */

/**
 * @defgroup audio_control AUDIO_CTL
 *
 * @brief Control audio device.
 */

/**
 * @addtogroup audio_control
 * @{
 */

/**
 * @brief Generate audio command code with @a a
 *
 * @param[in] a offset of command.
 *
 * @return audio device control command code.
 */
#define _AUDIO_CTL(a) (RT_DEVICE_CTRL_BASE(Sound) + a)

#define AUDIO_CTL_GETCAPS                   _AUDIO_CTL(1) /**< Get audio device capabilities */
#define AUDIO_CTL_CONFIGURE                 _AUDIO_CTL(2) /**< Get audio device configuration */
#define AUDIO_CTL_START                     _AUDIO_CTL(3) /**< Start audio device  */
#define AUDIO_CTL_STOP                      _AUDIO_CTL(4) /**< Stop audio device */
#define AUDIO_CTL_GETBUFFERINFO             _AUDIO_CTL(5) /**< Get audio device buffer information */

/** @} */ /* End of audio_control*/

/**
 * @defgroup audio_type AUDIO_TYPE
 *
 * @brief Audio Device Types
 */

/**
 * @addtogroup audio_type
 * @{
 */
#define AUDIO_TYPE_QUERY                    0x00 /**< Query audio device type */
#define AUDIO_TYPE_INPUT                    0x01 /**< Set audio device type to input type */
#define AUDIO_TYPE_OUTPUT                   0x02 /**< Set audio device type to output type */
#define AUDIO_TYPE_MIXER                    0x04 /**< Set audio device type to mixer type */
/** @} */ /* End of audio_type*/

/**
 * @defgroup audio_samp_rates AUDIO_SAMP_RATES
 *
 * @brief Supported audio sample rates for the audio device.
 */

/**
 * @addtogroup audio_samp_rates
 * @{
 */
#define AUDIO_SAMP_RATE_8K                  0x0001 /**< Set audio device sample rate to 8K */
#define AUDIO_SAMP_RATE_11K                 0x0002 /**< Set audio device sample rate to 11K */
#define AUDIO_SAMP_RATE_16K                 0x0004 /**< Set audio device sample rate to 16K */
#define AUDIO_SAMP_RATE_22K                 0x0008 /**< Set audio device sample rate to 22K */
#define AUDIO_SAMP_RATE_32K                 0x0010 /**< Set audio device sample rate to 32K */
#define AUDIO_SAMP_RATE_44K                 0x0020 /**< Set audio device sample rate to 44K */
#define AUDIO_SAMP_RATE_48K                 0x0040 /**< Set audio device sample rate to 48K */
#define AUDIO_SAMP_RATE_96K                 0x0080 /**< Set audio device sample rate to 96K */
#define AUDIO_SAMP_RATE_128K                0x0100 /**< Set audio device sample rate to 128K */
#define AUDIO_SAMP_RATE_160K                0x0200 /**< Set audio device sample rate to 160K */
#define AUDIO_SAMP_RATE_172K                0x0400 /**< Set audio device sample rate to 172K */
#define AUDIO_SAMP_RATE_192K                0x0800 /**< Set audio device sample rate to 192K */
/** @} */ /* End of audio_samp_rates*/

/**
 * @defgroup audio_bit_rates AUDIO_BIT_RATES
 *
 * @brief Supported bit rates for the audio device.
 */

/**
 * @addtogroup audio_bit_rates
 * @{
 */
#define AUDIO_BIT_RATE_22K                  0x01 /**< Set audio device bit rates to 22K */
#define AUDIO_BIT_RATE_44K                  0x02 /**< Set audio device bit rates to 44K */
#define AUDIO_BIT_RATE_48K                  0x04 /**< Set audio device bit rates to 48K */
#define AUDIO_BIT_RATE_96K                  0x08 /**< Set audio device bit rates to 96K */
#define AUDIO_BIT_RATE_128K                 0x10 /**< Set audio device bit rates to 128K */
#define AUDIO_BIT_RATE_160K                 0x20 /**< Set audio device bit rates to 160K */
#define AUDIO_BIT_RATE_172K                 0x40 /**< Set audio device bit rates to 172K */
#define AUDIO_BIT_RATE_192K                 0x80 /**< Set audio device bit rates to 192K */
/** @} */ /* End of audio_bit_rates*/


/**
 * @defgroup audio_dsp AUDIO_DSP
 *
 * @brief Support Dsp(input/output) Units controls
 */

/**
 * @addtogroup audio_dsp
 * @{
 */
#define AUDIO_DSP_PARAM                     0 /**< get/set all params */
#define AUDIO_DSP_SAMPLERATE                1 /**< samplerate */
#define AUDIO_DSP_CHANNELS                  2 /**< channels */
#define AUDIO_DSP_SAMPLEBITS                3 /**< sample bits width */
/** @} */ /* End of audio_dsp*/

/**
 * @defgroup audio_mixer AUDIO_MIXER
 *
 * @brief Supported Mixer Units controls
 */

/**
 * @addtogroup audio_mixer
 * @{
 */
#define AUDIO_MIXER_QUERY                   0x0000 /**< Query mixer capabilities */
#define AUDIO_MIXER_MUTE                    0x0001 /**< Mute audio device */
#define AUDIO_MIXER_VOLUME                  0x0002 /**< Set mixer volume */
#define AUDIO_MIXER_BASS                    0x0004 /**< Set the low-frequency section of the mixer */
#define AUDIO_MIXER_MID                     0x0008 /**< Set the mid-frequency section of the mixer*/
#define AUDIO_MIXER_TREBLE                  0x0010 /**< Set the high-frequency section of the mixer */
#define AUDIO_MIXER_EQUALIZER               0x0020 /**< Set equalizer option */
#define AUDIO_MIXER_LINE                    0x0040 /**< Set line control option */
#define AUDIO_MIXER_DIGITAL                 0x0080 /**< Set digital source */
#define AUDIO_MIXER_MIC                     0x0100 /**< Set microphone option */
#define AUDIO_MIXER_VITURAL                 0x0200 /**< Set virtual audio option */
#define AUDIO_MIXER_EXTEND                  0x8000 /**< Extend mixer command */
/** @} */ /* End of audio_mixer*/

#define AUDIO_VOLUME_MAX                    (100)
#define AUDIO_VOLUME_MIN                    (0)

#define CFG_AUDIO_REPLAY_QUEUE_COUNT        4

/**
 * @brief Audio stream control command
 */
enum
{
    AUDIO_STREAM_REPLAY = 0,
    AUDIO_STREAM_RECORD,
    AUDIO_STREAM_LAST = AUDIO_STREAM_RECORD,
};

/**
 * @brief Audio buffer info
 *
 * The preferred number and size of audio pipeline buffer for the audio device, it
 * will be used in rt_audio_replay struct.
 *
 */
struct rt_audio_buf_info
{
    rt_uint8_t *buffer;
    rt_uint16_t block_size;
    rt_uint16_t block_count;
    rt_uint32_t total_size;
};

struct rt_audio_device;
struct rt_audio_caps;
struct rt_audio_configure;
struct rt_audio_ops
{
    rt_err_t (*getcaps)(struct rt_audio_device *audio, struct rt_audio_caps *caps);
    rt_err_t (*configure)(struct rt_audio_device *audio, struct rt_audio_caps *caps);
    rt_err_t (*init)(struct rt_audio_device *audio);
    rt_err_t (*start)(struct rt_audio_device *audio, int stream);
    rt_err_t (*stop)(struct rt_audio_device *audio, int stream);
    rt_ssize_t (*transmit)(struct rt_audio_device *audio, const void *writeBuf, void *readBuf, rt_size_t size);
    /* get page size of codec or private buffer's info */
    void (*buffer_info)(struct rt_audio_device *audio, struct rt_audio_buf_info *info);
};

/**
 * @brief Audio configuration
 *
 * The preferred number and size of audio pipeline buffer for the audio device, it
 * will be used in rt_audio_caps struct.
 *
 */
struct rt_audio_configure
{
    rt_uint32_t samplerate;
    rt_uint16_t channels;
    rt_uint16_t samplebits;
};

/**
 * @brief Audio capabilities
 */
struct rt_audio_caps
{
    int main_type;
    int sub_type;

    union
    {
        rt_uint32_t mask;
        int     value;
        struct rt_audio_configure config;
    } udata;
};

/**
 * @brief Audio replay
 */
struct rt_audio_replay
{
    struct rt_mempool *mp;
    struct rt_data_queue queue;
    struct rt_mutex lock;
    struct rt_completion cmp;
    struct rt_audio_buf_info buf_info;
    rt_uint8_t *write_data;
    rt_uint16_t write_index;
    rt_uint16_t read_index;
    rt_uint32_t pos;
    rt_uint8_t event;
    rt_bool_t activated;
};

/**
 * @brief Audio record, the audio device pipe container of ringbuffer
 */
struct rt_audio_record
{
    struct rt_audio_pipe pipe;
    rt_bool_t activated;
};

/**
 * @brief Audio device
 */
struct rt_audio_device
{
    struct rt_device           parent;
    struct rt_audio_ops        *ops;
    struct rt_audio_replay     *replay;
    struct rt_audio_record     *record;
};

rt_err_t    rt_audio_register(struct rt_audio_device *audio, const char *name, rt_uint32_t flag, void *data);
void        rt_audio_tx_complete(struct rt_audio_device *audio);
void        rt_audio_rx_done(struct rt_audio_device *audio, rt_uint8_t *pbuf, rt_size_t len);

/**
 * @defgroup audio_codec_cmd CODEC_CMD
 *
 * @brief Device Control Commands
 */

/**
 * @addtogroup audio_codec_cmd
 * @{
 */
#define CODEC_CMD_RESET             0 /**< Reset audio device by codec */
#define CODEC_CMD_SET_VOLUME        1 /**< Set volume by codec */
#define CODEC_CMD_GET_VOLUME        2 /**< Get volume by codec */
#define CODEC_CMD_SAMPLERATE        3 /**< Set sample rate by codec */
#define CODEC_CMD_EQ                4 /**< Set equalizer by codec */
#define CODEC_CMD_3D                5 /**< Set 3D effect by codec */

#define CODEC_VOLUME_MAX            (63)
/** @} */ /* End of audio_codec_cmd*/

/** @} group_Audio */

#endif /* __DEV_AUDIO_H__ */