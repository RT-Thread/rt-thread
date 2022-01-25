/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-12-07     Leo         first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>
#include <drivers/adc.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) || defined(BSP_USING_ADC3)

#ifndef ADC1_CONFIG
#define ADC1_CONFIG                 \
    {                              \
       .ADC_Handler = ADC1,        \
       .name        = "adc1",      \
    }
#endif /* ADC1_CONFIG */

#ifndef ADC2_CONFIG
#define ADC2_CONFIG                \
    {                              \
       .ADC_Handler = ADC2,        \
       .name        = "adc2",      \
    }
#endif /* ADC2_CONFIG */

#ifndef ADC3_CONFIG
#define ADC3_CONFIG                \
    {                              \
       .ADC_Handler = ADC3,        \
       .name        = "adc3",      \
    }
#endif /* ADC3_CONFIG */

#endif


#ifdef __cplusplus
}
#endif

#endif /* __ADC_CONFIG_H__ */
