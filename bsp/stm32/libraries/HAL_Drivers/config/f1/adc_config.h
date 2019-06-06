/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-07     zylx         first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>

<<<<<<< HEAD
=======
#ifdef __cplusplus
extern "C" {
#endif

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#ifdef BSP_USING_ADC1
#ifndef ADC1_CONFIG
#define ADC1_CONFIG                                                \
    {                                                              \
       .Instance                   = ADC1,                         \
       .Init.DataAlign             = ADC_DATAALIGN_RIGHT,          \
       .Init.ScanConvMode          = ADC_SCAN_DISABLE,             \
       .Init.ContinuousConvMode    = DISABLE,                      \
       .Init.NbrOfConversion       = 1,                            \
       .Init.DiscontinuousConvMode = DISABLE,                      \
       .Init.NbrOfDiscConversion   = 1,                            \
       .Init.ExternalTrigConv      = ADC_SOFTWARE_START,           \
    }  
#endif /* ADC1_CONFIG */
#endif /* BSP_USING_ADC1 */

#ifdef BSP_USING_ADC2
#ifndef ADC2_CONFIG
#define ADC2_CONFIG                                                \
    {                                                              \
       .Instance                   = ADC2,                         \
       .Init.DataAlign             = ADC_DATAALIGN_RIGHT,          \
       .Init.ScanConvMode          = ADC_SCAN_DISABLE,             \
       .Init.ContinuousConvMode    = DISABLE,                      \
       .Init.NbrOfConversion       = 1,                            \
       .Init.DiscontinuousConvMode = DISABLE,                      \
       .Init.NbrOfDiscConversion   = 1,                            \
       .Init.ExternalTrigConv      = ADC_SOFTWARE_START,           \
    }  
#endif /* ADC2_CONFIG */
#endif /* BSP_USING_ADC2 */

#ifdef BSP_USING_ADC3
#ifndef ADC3_CONFIG
#define ADC3_CONFIG                                                \
    {                                                              \
       .Instance                   = ADC3,                         \
       .Init.DataAlign             = ADC_DATAALIGN_RIGHT,          \
       .Init.ScanConvMode          = ADC_SCAN_DISABLE,             \
       .Init.ContinuousConvMode    = DISABLE,                      \
       .Init.NbrOfConversion       = 1,                            \
       .Init.DiscontinuousConvMode = DISABLE,                      \
       .Init.NbrOfDiscConversion   = 1,                            \
       .Init.ExternalTrigConv      = ADC_SOFTWARE_START,           \
    }  
#endif /* ADC3_CONFIG */
#endif /* BSP_USING_ADC3 */

<<<<<<< HEAD
=======
#ifdef __cplusplus
}
#endif

>>>>>>> 49e424905b5922b07aa7166ec7a0eeb90adf58a8
#endif /* __ADC_CONFIG_H__ */
