/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-3-15      GuEe-GUI     the first version
 */

#ifndef __RK3528_CODEC_H__
#define __RK3528_CODEC_H__

#include <rtdevice.h>

struct rk3528_codec;

#ifdef RT_AUDIO_ROCKCHIP_CODEC_RK3528
struct rk3528_codec *rk3528_codec_find(struct rt_ofw_node *np);
rt_err_t rk3528_codec_hw_params(struct rk3528_codec *codec,
        rt_uint32_t rate, rt_uint16_t bits,
        rt_uint32_t mclk_fs);
rt_err_t rk3528_codec_start(struct rk3528_codec *codec);
rt_err_t rk3528_codec_stop(struct rk3528_codec *codec);
rt_err_t rk3528_codec_set_volume(struct rk3528_codec *codec,
        rt_uint32_t volume);
rt_err_t rk3528_codec_mute(struct rk3528_codec *codec, rt_bool_t mute);
#else
rt_inline struct rk3528_codec *rk3528_codec_find(struct rt_ofw_node *np)
{
    return RT_NULL;
}
rt_inline rt_err_t rk3528_codec_hw_params(struct rk3528_codec *codec,
        rt_uint32_t rate, rt_uint16_t bits,
        rt_uint32_t mclk_fs)
{
    return -RT_ENOSYS;
}
rt_inline rt_err_t rk3528_codec_start(struct rk3528_codec *codec)
{
    return -RT_ENOSYS;
}
rt_inline rt_err_t rk3528_codec_stop(struct rk3528_codec *codec)
{
    return -RT_ENOSYS;
}
rt_inline rt_err_t rk3528_codec_set_volume(struct rk3528_codec *codec,
        rt_uint32_t volume)
{
    return -RT_ENOSYS;
}
rt_inline rt_err_t rk3528_codec_mute(struct rk3528_codec *codec, rt_bool_t mute)
{
    return -RT_ENOSYS;
}
#endif

#endif
