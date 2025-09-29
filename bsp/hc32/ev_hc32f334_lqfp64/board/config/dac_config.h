/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
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
        .name                      = "dac1",                                \
        .vref                      = 3300,                                  \
        .dac_adp_enable            = RT_FALSE,                              \
        .dac_adp_sel               = DAC_ADP_SEL_ALL,                       \
        .ch1_output_enable         = RT_TRUE,                               \
        .ch2_output_enable         = RT_TRUE,                               \
        .ch1_amp_enable            = RT_TRUE,                               \
        .ch2_amp_enable            = RT_TRUE,                               \
    }
#endif /* DAC1_INIT_PARAMS */
#endif /* BSP_USING_DAC1 */

#ifdef BSP_USING_DAC2
#ifndef DAC2_INIT_PARAMS
#define DAC2_INIT_PARAMS                                                    \
    {                                                                       \
        .name                      = "dac2",                                \
        .vref                      = 3300,                                  \
        .dac_adp_enable            = RT_FALSE,                              \
        .dac_adp_sel               = DAC_ADP_SEL_ALL,                       \
        .ch1_output_enable         = RT_TRUE,                               \
        .ch1_amp_enable            = RT_TRUE,                               \
    }
#endif /* DAC2_INIT_PARAMS */
#endif /* BSP_USING_DAC2 */

#ifdef __cplusplus
}
#endif

#endif /* __DAC_CONFIG_H__ */
