/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-08-28     FUNMSAN          first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define N32H49X_ADC_CONFIG(ADC_INSTANCE, ADC_PERIPH)          \
    {                                                         \
        .ADCx = ADC_INSTANCE,                                 \
        .AHB_periph = ADC_PERIPH,                             \
        .EnablePeriphClk = RCC_EnableAHB1PeriphClk,           \
        .ADC_ClkMode = ADC_CTRL3_CKMOD_AHB,                   \
        .RCC_ADCPrescaler = RCC_ADCHCLK_DIV16,                \
        .ADC1M_ClkSource = RCC_ADC1MCLK_SRC_HSI,              \
        .ADC1M_ClkPrescaler = RCC_ADC1MCLK_DIV8,              \
        .Rank = 1U,                                           \
        .ADC_SampleTime = ADC_SAMP_TIME_CYCLES_239_5,         \
        .Init.WorkMode = ADC_WORKMODE_INDEPENDENT,            \
        .Init.MultiChEn = DISABLE,                            \
        .Init.ContinueConvEn = DISABLE,                       \
        .Init.ExtTrigSelect = ADC_EXT_TRIG_REG_CONV_SOFTWARE, \
        .Init.DatAlign = ADC_DAT_ALIGN_R,                     \
        .Init.ChsNumber = 1U,                                 \
        .Init.Resolution = ADC_DATA_RES_12BIT,                \
    }

#ifdef BSP_USING_ADC1
#ifndef ADC1_CONFIG
#define ADC1_CONFIG N32H49X_ADC_CONFIG(ADC1, RCC_AHB_PERIPHEN_ADC1)
#endif /* ADC1_CONFIG */
#endif /* BSP_USING_ADC1 */

#ifdef BSP_USING_ADC2
#ifndef ADC2_CONFIG
#define ADC2_CONFIG N32H49X_ADC_CONFIG(ADC2, RCC_AHB_PERIPHEN_ADC2)
#endif /* ADC2_CONFIG */
#endif /* BSP_USING_ADC2 */

#ifdef BSP_USING_ADC3
#ifndef ADC3_CONFIG
#define ADC3_CONFIG N32H49X_ADC_CONFIG(ADC3, RCC_AHB_PERIPHEN_ADC3)
#endif /* ADC3_CONFIG */
#endif /* BSP_USING_ADC3 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_CONFIG_H__ */
