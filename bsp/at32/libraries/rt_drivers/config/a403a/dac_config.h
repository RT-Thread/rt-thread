/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-12     shelton      first version
 */

#ifndef __DAC_CONFIG_H__
#define __DAC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_DAC1)
#define DAC1_CONFIG                                                 \
    {                                                               \
        .name = "dac1",                                             \
        .dac_x = DAC,                                               \
    }
#endif /* BSP_USING_DAC1 */

#ifdef __cplusplus
}
#endif

#endif
