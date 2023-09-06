/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-04     Rbb666       first version
 */

#ifndef __TMR_CONFIG_H__
#define __TMR_CONFIG_H__

#include <rtthread.h>
#include <drivers/hwtimer.h>
#include <drv_config.h>
#include <hal_data.h>

#ifdef __cplusplus
extern "C"
{
#endif

struct ra_hwtimer
{
    rt_hwtimer_t                    tmr_device;
    gpt_instance_ctrl_t             *g_ctrl;
    timer_instance_t const *const   g_timer;
    timer_cfg_t const *const        g_cfg;
    char                            *name;
};

#ifdef __cplusplus
}
#endif

#endif /* __TMR_CONFIG_H__ */
