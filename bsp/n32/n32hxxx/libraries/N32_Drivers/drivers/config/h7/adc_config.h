/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-01-24     ox-horse         first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_ADC1
#ifndef ADC1_CONFIG
#define ADC1_CONFIG                                                                              \
    {                                                                                            \
        .ADCx                  = ADC1,                                                           \
        .AHB_periph            = (RCC_AHB1_PERIPHEN_M7_ADC1SYS | RCC_AHB1_PERIPHEN_M7_ADC1BUS),  \
        .EnablePeriphClk       = RCC_EnableAHB1PeriphClk1,                                       \
        .ADC_ClkMode           = ADC_CTRL3_CKMOD_AHB,                                            \
        .Pll_CLK_source        = RCC_ADCPLLCLK_SRC_PLL1B,                                        \
        .RCC_ADCPrescaler      = RCC_AHB1DIV2_ADC1SYSDIV_DIV15,                                  \
        .Init.WorkMode         = ADC_WORKMODE_INDEPENDENT,                                       \
        .Init.MultiChEn        = DISABLE,                                                        \
        .Init.ContinueConvEn   = DISABLE,                                                        \
        .Init.ExtTrigSelect    = ADC_EXT_TRIG_REG_CONV_SOFTWARE,                                 \
        .Init.DataTransferMode = ADC_REG_DR_TRANSFER,                                            \
        .Init.DatAlign         = ADC_DAT_ALIGN_R,                                                \
        .Init.ChsNumber        = 1U,                                                             \
        .Init.Resolution       = ADC_DATA_RES_12BIT,                                             \
        .Rank                  = 1U,                                                             \
        .ADC_SampleTime        = ADC_SAMP_TIME_CYCLES_24,                                        \
    }
#endif /* ADC1_CONFIG */
#endif /* BSP_USING_ADC1 */

#ifdef BSP_USING_ADC2
#ifndef ADC2_CONFIG
#define ADC2_CONFIG                                                                              \
    {                                                                                            \
        .ADCx                  = ADC2,                                                           \
        .AHB_periph            = (RCC_AHB1_PERIPHEN_M7_ADC2SYS | RCC_AHB1_PERIPHEN_M7_ADC2BUS),  \
        .EnablePeriphClk       = RCC_EnableAHB1PeriphClk4,                                       \
        .ADC_ClkMode           = ADC_CTRL3_CKMOD_AHB,                                            \
        .Pll_CLK_source        = RCC_ADCPLLCLK_SRC_PLL1B,                                        \
        .RCC_ADCPrescaler      = RCC_AHB1DIV2_ADC1SYSDIV_DIV15,                                  \
        .Init.WorkMode         = ADC_WORKMODE_INDEPENDENT,                                       \
        .Init.MultiChEn        = DISABLE,                                                        \
        .Init.ContinueConvEn   = DISABLE,                                                        \
        .Init.ExtTrigSelect    = ADC_EXT_TRIG_REG_CONV_SOFTWARE,                                 \
        .Init.DataTransferMode = ADC_REG_DR_TRANSFER,                                            \
        .Init.DatAlign         = ADC_DAT_ALIGN_R,                                                \
        .Init.ChsNumber        = 1U,                                                             \
        .Init.Resolution       = ADC_DATA_RES_12BIT,                                             \
        .Rank                  = 1U,                                                             \
        .ADC_SampleTime        = ADC_SAMP_TIME_CYCLES_24,                                        \
    }
#endif /* ADC2_CONFIG */
#endif /* BSP_USING_ADC2 */

#ifdef BSP_USING_ADC3
#ifndef ADC3_CONFIG
#define ADC3_CONFIG                                                                              \
    {                                                                                            \
        .ADCx                  = ADC3,                                                           \
        .AHB_periph            = (RCC_AHB1_PERIPHEN_M7_ADC3SYS | RCC_AHB1_PERIPHEN_M7_ADC3BUS),  \
        .EnablePeriphClk       = RCC_EnableAHB1PeriphClk4,                                       \
        .ADC_ClkMode           = ADC_CTRL3_CKMOD_AHB,                                            \
        .Pll_CLK_source        = RCC_ADCPLLCLK_SRC_PLL1B,                                        \
        .RCC_ADCPrescaler      = RCC_AHB1DIV2_ADC1SYSDIV_DIV15,                                  \
        .Init.WorkMode         = ADC_WORKMODE_INDEPENDENT,                                       \
        .Init.MultiChEn        = DISABLE,                                                        \
        .Init.ContinueConvEn   = DISABLE,                                                        \
        .Init.ExtTrigSelect    = ADC_EXT_TRIG_REG_CONV_SOFTWARE,                                 \
        .Init.DataTransferMode = ADC_REG_DR_TRANSFER,                                            \
        .Init.DatAlign         = ADC_DAT_ALIGN_R,                                                \
        .Init.ChsNumber        = 1U,                                                             \
        .Init.Resolution       = ADC_DATA_RES_12BIT,                                             \
        .Rank                  = 1U,                                                             \
        .ADC_SampleTime        = ADC_SAMP_TIME_CYCLES_24,                                        \
    }
#endif /* ADC3_CONFIG */
#endif /* BSP_USING_ADC3 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_CONFIG_H__ */
