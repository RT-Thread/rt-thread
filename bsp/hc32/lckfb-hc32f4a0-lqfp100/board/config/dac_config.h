/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-05-12     CDT          first version
 */

#ifndef __DAC_CONFIG_H__
#define __DAC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_DAC1
#ifndef DAC1_INIT_PARAMS
#define DAC1_INIT_PARAMS                                                    \
    {                                                                       \
       .name                      = "dac1",                                 \
    }
#endif /* DAC1_INIT_PARAMS */
#endif /* BSP_USING_DAC1 */

#ifdef BSP_USING_DAC2
#ifndef DAC2_INIT_PARAMS
#define DAC2_INIT_PARAMS                                                    \
    {                                                                       \
       .name                      = "dac2",                                 \
    }
#endif /* DAC2_INIT_PARAMS */
#endif /* BSP_USING_DAC2 */

#ifdef __cplusplus
}
#endif

#endif /* __DAC_CONFIG_H__ */
