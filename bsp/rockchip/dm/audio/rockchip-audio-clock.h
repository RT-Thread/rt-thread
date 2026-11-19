/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-3-15      GuEe-GUI     the first version
 */

#ifndef __ROCKCHIP_AUDIO_CLOCK_H__
#define __ROCKCHIP_AUDIO_CLOCK_H__

#include <rtdevice.h>

rt_err_t rockchip_audio_set_mclk(struct rt_clk *mclk, rt_ubase_t rate);

#endif /* __ROCKCHIP_AUDIO_CLOCK_H__ */
