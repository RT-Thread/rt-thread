/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-19     Nations      first version
 */

#ifndef __DRV_DAC__
#define __DRV_DAC__

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <board.h>

#ifdef __cplusplus
extern "C" {
#endif

/* n32 config class */
struct n32_dac_config
{
    const char *name;
    rt_uint32_t dac_periph;
};

struct n32_dac
{
    struct rt_dac_device dac_device;
    struct n32_dac_config *config;
};

int rt_hw_dac_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __DRV_DAC__ */
