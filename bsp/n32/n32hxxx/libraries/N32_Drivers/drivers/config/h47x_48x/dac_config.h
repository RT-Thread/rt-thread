/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-08-28     FUNMSAN          first version
 */

#ifndef __DAC_CONFIG_H__
#define __DAC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(N32H473) || defined(N32H474)
#define N32H47X_48X_DAC1234_CLK_PRESCALER 100U
#else
#define N32H47X_48X_DAC1234_CLK_PRESCALER 120U
#endif

#define N32H47X_48X_DAC5678_CLK_PRESCALER 16U

#define N32H47X_48X_DAC_CONFIG(DAC_INSTANCE, DAC_MODULE, DAC_PERIPH, CLK_ENABLE, CLK_PRESCALER) \
    {                                                                                           \
        .DACx = DAC_INSTANCE,                                                                   \
        .DAC_Module = DAC_MODULE,                                                               \
        .periph_clk = DAC_PERIPH,                                                               \
        .EnablePeriphClk = CLK_ENABLE,                                                          \
        .DAC_clk_pres = CLK_PRESCALER,                                                          \
        .Init.DAC_Trigger = DAC_Trigger_Software,                                               \
        .Init.DAC_Trigger2 = DAC_Trigger2_Software,                                             \
        .Init.DAC_WaveGeneration = DAC_WaveGeneration_None,                                     \
        .Init.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0,                           \
        .Init.DAC_OutputBuffer = DISABLE,                                                       \
        .Init.DAC_TriggerEnable = ENABLE,                                                       \
        .Init.DAC_ConnectOnChipPeripheral = DISABLE,                                            \
        .Init.DAC_ConnectExternalPin = ENABLE,                                                  \
        .Init.DAC_DMADoubleDataMode = DISABLE,                                                  \
        .Init.DAC_SignedFormat = DISABLE,                                                       \
    }

#ifdef BSP_USING_DAC1
#ifndef DAC1_CONFIG
#define DAC1_CONFIG N32H47X_48X_DAC_CONFIG(DAC1, DAC12, RCC_APB1_PERIPH_DAC12, \
                                           RCC_EnableAPB1PeriphClk, N32H47X_48X_DAC1234_CLK_PRESCALER)
#endif /* DAC1_CONFIG */
#endif /* BSP_USING_DAC1 */

#ifdef BSP_USING_DAC2
#ifndef DAC2_CONFIG
#define DAC2_CONFIG N32H47X_48X_DAC_CONFIG(DAC2, DAC12, RCC_APB1_PERIPH_DAC12, \
                                           RCC_EnableAPB1PeriphClk, N32H47X_48X_DAC1234_CLK_PRESCALER)
#endif /* DAC2_CONFIG */
#endif /* BSP_USING_DAC2 */

#ifdef BSP_USING_DAC3
#ifndef DAC3_CONFIG
#define DAC3_CONFIG N32H47X_48X_DAC_CONFIG(DAC3, DAC34, RCC_APB1_PERIPH_DAC34, \
                                           RCC_EnableAPB1PeriphClk, N32H47X_48X_DAC1234_CLK_PRESCALER)
#endif /* DAC3_CONFIG */
#endif /* BSP_USING_DAC3 */

#ifdef BSP_USING_DAC4
#ifndef DAC4_CONFIG
#define DAC4_CONFIG N32H47X_48X_DAC_CONFIG(DAC4, DAC34, RCC_APB1_PERIPH_DAC34, \
                                           RCC_EnableAPB1PeriphClk, N32H47X_48X_DAC1234_CLK_PRESCALER)
#endif /* DAC4_CONFIG */
#endif /* BSP_USING_DAC4 */

#ifdef BSP_USING_DAC5
#ifndef DAC5_CONFIG
#define DAC5_CONFIG N32H47X_48X_DAC_CONFIG(DAC5, DAC56, RCC_AHB_PERIPHEN_DAC56, \
                                           RCC_EnableAHBPeriphClk, N32H47X_48X_DAC5678_CLK_PRESCALER)
#endif /* DAC5_CONFIG */
#endif /* BSP_USING_DAC5 */

#ifdef BSP_USING_DAC6
#ifndef DAC6_CONFIG
#define DAC6_CONFIG N32H47X_48X_DAC_CONFIG(DAC6, DAC56, RCC_AHB_PERIPHEN_DAC56, \
                                           RCC_EnableAHBPeriphClk, N32H47X_48X_DAC5678_CLK_PRESCALER)
#endif /* DAC6_CONFIG */
#endif /* BSP_USING_DAC6 */

#ifdef BSP_USING_DAC7
#ifndef DAC7_CONFIG
#define DAC7_CONFIG N32H47X_48X_DAC_CONFIG(DAC7, DAC78, RCC_AHB_PERIPHEN_DAC78, \
                                           RCC_EnableAHBPeriphClk, N32H47X_48X_DAC5678_CLK_PRESCALER)
#endif /* DAC7_CONFIG */
#endif /* BSP_USING_DAC7 */

#ifdef BSP_USING_DAC8
#ifndef DAC8_CONFIG
#define DAC8_CONFIG N32H47X_48X_DAC_CONFIG(DAC8, DAC78, RCC_AHB_PERIPHEN_DAC78, \
                                           RCC_EnableAHBPeriphClk, N32H47X_48X_DAC5678_CLK_PRESCALER)
#endif /* DAC8_CONFIG */
#endif /* BSP_USING_DAC8 */

#ifdef __cplusplus
}
#endif

#endif /* __DAC_CONFIG_H__ */
