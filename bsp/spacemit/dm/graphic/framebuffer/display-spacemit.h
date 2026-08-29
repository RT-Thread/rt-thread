/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __DISPLAY_SPACEMIT_H__
#define __DISPLAY_SPACEMIT_H__

#include <rtthread.h>
#include <rtdevice.h>

#define SPACEMIT_DISPLAY_F_PHSYNC    (1U << 0)
#define SPACEMIT_DISPLAY_F_PVSYNC    (1U << 1)

struct spacemit_display_timing
{
    rt_uint32_t hactive;
    rt_uint32_t vactive;
    rt_uint32_t hfront_porch;
    rt_uint32_t hback_porch;
    rt_uint32_t hsync_len;
    rt_uint32_t vfront_porch;
    rt_uint32_t vback_porch;
    rt_uint32_t vsync_len;
    rt_uint32_t refresh;
    rt_uint64_t pixelclock;
    rt_uint32_t flags;
};

struct spacemit_display_connector;

struct spacemit_display_connector_ops
{
    rt_err_t (*detect)(struct spacemit_display_connector *connector,
            rt_bool_t *connected);
    rt_err_t (*get_timing)(struct spacemit_display_connector *connector,
            struct spacemit_display_timing *timing);
    rt_err_t (*enable)(struct spacemit_display_connector *connector,
            const struct spacemit_display_timing *timing);
    rt_err_t (*disable)(struct spacemit_display_connector *connector);
};

struct spacemit_display_connector
{
    rt_list_t list;
    struct rt_ofw_node *ofw_node;
    const struct spacemit_display_connector_ops *ops;
    void *priv;
};

rt_err_t spacemit_display_connector_register(
        struct spacemit_display_connector *connector,
        struct rt_ofw_node *np,
        const struct spacemit_display_connector_ops *ops,
        void *priv);
void spacemit_display_connector_unregister(
        struct spacemit_display_connector *connector);
struct spacemit_display_connector *spacemit_display_connector_find(
        const char *compatible);

rt_err_t spacemit_hdmi_driver_register(void);
rt_err_t spacemit_fb_driver_register(void);

#endif /* __DISPLAY_SPACEMIT_H__ */
