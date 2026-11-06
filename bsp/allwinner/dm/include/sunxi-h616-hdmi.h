/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef __SUNXI_H616_HDMI_H__
#define __SUNXI_H616_HDMI_H__

#include <rtdef.h>

rt_err_t sunxi_h616_hdmi_audio_configure(rt_uint32_t samplerate,
                                         rt_uint32_t channels, rt_uint32_t samplebits);
void sunxi_h616_hdmi_audio_enable(rt_bool_t enable);

#endif
