/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#ifndef __ROCKCHIP_HDMI_H__
#define __ROCKCHIP_HDMI_H__

#include <rtdevice.h>

#ifdef RT_GRAPHIC_CONNECTOR_HDMI
rt_err_t rk_hdmi_audio_configure(struct rt_ofw_node *np,
        rt_uint32_t samplerate, rt_uint8_t channels, rt_uint8_t samplebits);
rt_err_t rk_hdmi_audio_enable(struct rt_ofw_node *np, rt_bool_t enable);
#else
rt_inline rt_err_t rk_hdmi_audio_configure(struct rt_ofw_node *np,
        rt_uint32_t samplerate, rt_uint8_t channels, rt_uint8_t samplebits)
{
    RT_UNUSED(np);
    RT_UNUSED(samplerate);
    RT_UNUSED(channels);
    RT_UNUSED(samplebits);

    return -RT_ENOSYS;
}

rt_inline rt_err_t rk_hdmi_audio_enable(struct rt_ofw_node *np, rt_bool_t enable)
{
    RT_UNUSED(np);
    RT_UNUSED(enable);

    return -RT_ENOSYS;
}
#endif

#endif /* __ROCKCHIP_HDMI_H__ */
