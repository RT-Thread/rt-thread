/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2020-10-26     bigmagic       first version
 */
#ifndef __DRV_HDMI_H__
#define __DRV_HDMI_H__

#define RGB(r, g, b) ((((r))<<16) | (((g))<<8) | ((b)))

struct rt_hdmi_fb_device
{
    struct rt_device parent;

    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t depth;
    rt_uint32_t pitch;
    rt_uint32_t pixel_format;

    rt_uint8_t *fb;
};
#endif/* __DRV_HDMI_H__ */
