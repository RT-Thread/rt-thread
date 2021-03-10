/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-16     thread-liu   first version
 */

#ifndef __DAC_CONFIG_H__
#define __DAC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_DAC1
#ifndef DAC1_CONFIG
#define DAC1_CONFIG                                                    \
    {                                                                  \
       .Instance                      = DAC1,                          \
    }
#endif /* DAC1_CONFIG */
#endif /* BSP_USING_DAC1 */

#ifdef __cplusplus
}
#endif

#endif /* __DAC_CONFIG_H__ */
