/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-10-01     GuEe-GUI     first version
 */

#ifndef __PHYE_HDMI_H__
#define __PHYE_HDMI_H__

#include <rtthread.h>

struct rt_phye_configure_opts_hdmi
{
    rt_uint64_t pixel_clock;
    rt_uint64_t tmds_clock;
};

#endif /* __PHYE_HDMI_H__ */
