/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-19     ChuShicheng  first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_ADC1
#ifndef ADC1_CONFIG
#define ADC1_CONFIG                                                     \
    {                                                                   \
        .Instance                      = ADC1,                          \
        .Init.ClockPrescaler           = ADC_CLOCK_ASYNC_DIV2,          \
        .Init.Resolution               = ADC_RESOLUTION_12B,            \
        .Init.DataAlign                = ADC_DATAALIGN_RIGHT,           \
        .Init.ScanConvMode             = ADC_SCAN_DISABLE,              \
        .Init.EOCSelection             = ADC_EOC_SINGLE_CONV,           \
        .Init.LowPowerAutoWait         = DISABLE,                       \
        .Init.ContinuousConvMode       = DISABLE,                       \
        .Init.NbrOfConversion          = 1,                             \
        .Init.DiscontinuousConvMode    = DISABLE,                       \
        .Init.ExternalTrigConv         = ADC_SOFTWARE_START,            \
        .Init.ExternalTrigConvEdge     = ADC_EXTERNALTRIGCONVEDGE_NONE, \
        .Init.DMAContinuousRequests    = DISABLE,                       \
        .Init.SamplingMode             = ADC_SAMPLING_MODE_NORMAL,      \
        .Init.Overrun                  = ADC_OVR_DATA_PRESERVED,        \
        .Init.OversamplingMode         = DISABLE,                       \
    }
#endif /* ADC1_CONFIG */
#endif /* BSP_USING_ADC1 */

#ifdef BSP_USING_ADC2
#ifndef ADC2_CONFIG
#define ADC2_CONFIG                                                     \
    {                                                                   \
        .Instance                      = ADC2,                          \
        .Init.ClockPrescaler           = ADC_CLOCK_ASYNC_DIV2,          \
        .Init.Resolution               = ADC_RESOLUTION_12B,            \
        .Init.DataAlign                = ADC_DATAALIGN_RIGHT,           \
        .Init.ScanConvMode             = ADC_SCAN_DISABLE,              \
        .Init.EOCSelection             = ADC_EOC_SINGLE_CONV,           \
        .Init.LowPowerAutoWait         = DISABLE,                       \
        .Init.ContinuousConvMode       = DISABLE,                       \
        .Init.NbrOfConversion          = 1,                             \
        .Init.DiscontinuousConvMode    = DISABLE,                       \
        .Init.ExternalTrigConv         = ADC_SOFTWARE_START,            \
        .Init.ExternalTrigConvEdge     = ADC_EXTERNALTRIGCONVEDGE_NONE, \
        .Init.DMAContinuousRequests    = DISABLE,                       \
        .Init.SamplingMode             = ADC_SAMPLING_MODE_NORMAL,      \
        .Init.Overrun                  = ADC_OVR_DATA_PRESERVED,        \
        .Init.OversamplingMode         = DISABLE,                       \
    }
#endif /* ADC2_CONFIG */
#endif /* BSP_USING_ADC2 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_CONFIG_H__ */
