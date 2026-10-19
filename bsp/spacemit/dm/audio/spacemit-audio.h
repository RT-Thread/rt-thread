/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SPACEMIT_AUDIO_H__
#define __SPACEMIT_AUDIO_H__

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

struct spacemit_i2s;
struct spacemit_hdmi_audio;
struct es8326_codec;

struct spacemit_audio_config
{
    rt_uint32_t samplerate;
    rt_uint16_t channels;
    rt_uint16_t samplebits;
    rt_uint32_t mclk_fs;
};

struct spacemit_pcm
{
    struct rt_device *dev;
    struct rt_ofw_node *np;
    struct rt_dma_chan *tx;
    struct rt_dma_chan *rx;

    rt_bool_t is_hdmi;
    void *hdmi_buffer;
    rt_ubase_t hdmi_dma;
    rt_size_t hdmi_size;

    rt_list_t list;
};

struct spacemit_pcm *spacemit_pcm_find(struct rt_ofw_node *np);

struct spacemit_i2s *spacemit_i2s_find(struct rt_ofw_node *np);
rt_err_t spacemit_i2s_configure(struct spacemit_i2s *i2s,
        const struct spacemit_audio_config *config);
rt_err_t spacemit_i2s_start(struct spacemit_i2s *i2s);
rt_err_t spacemit_i2s_stop(struct spacemit_i2s *i2s);
rt_ubase_t spacemit_i2s_fifo_phys(struct spacemit_i2s *i2s);

struct spacemit_hdmi_audio *spacemit_hdmi_audio_find(struct rt_ofw_node *np);
rt_err_t spacemit_hdmi_audio_start(struct spacemit_hdmi_audio *hdmi);
rt_err_t spacemit_hdmi_audio_stop(struct spacemit_hdmi_audio *hdmi);
rt_ubase_t spacemit_hdmi_audio_fifo_phys(struct spacemit_hdmi_audio *hdmi);
rt_bool_t spacemit_hdmi_audio_connected(struct spacemit_hdmi_audio *hdmi);

struct es8326_codec *es8326_codec_find(struct rt_ofw_node *np);
rt_err_t es8326_codec_hw_params(struct es8326_codec *codec,
        const struct spacemit_audio_config *config);
rt_err_t es8326_codec_start(struct es8326_codec *codec, int stream);
rt_err_t es8326_codec_stop(struct es8326_codec *codec, int stream);
rt_err_t es8326_codec_set_volume(struct es8326_codec *codec, int volume);
rt_err_t es8326_codec_set_mute(struct es8326_codec *codec, rt_bool_t mute);

#endif /* __SPACEMIT_AUDIO_H__ */
