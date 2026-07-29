/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-06-09     li.mengmeng      first version
 */

#ifndef __DAC_CONFIG_H__
#define __DAC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_DAC1
#ifndef DAC1_CONFIG
#define DAC1_CONFIG                                                          \
    {                                                                        \
        .DACx                                  = DAC1,                       \
        .DAC_Module                            = DAC12,                      \
        .periph_clk                            = RCC_APB1_PERIPHEN_M7_DAC12, \
        .EnablePeriphClk                       = RCC_EnableAPB1PeriphClk2,   \
        .DAC_clk_pres                          = 150,                        \
        .Init.DAC_Trigger                      = DAC_Trigger_Software,       \
        .Init.DAC_Trigger2                     = DAC_Trigger2_Software,      \
        .Init.DAC_WaveGeneration               = DAC_WaveGeneration_None,    \
        .Init.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0,        \
        .Init.DAC_OutputBuffer                 = DISABLE,                    \
        .Init.DAC_TriggerEnable                = ENABLE,                     \
        .Init.DAC_ConnectOnChipPeripheral      = DISABLE,                    \
        .Init.DAC_ConnectExternalPin           = ENABLE,                     \
        .Init.DAC_DMADoubleDataMode            = DISABLE,                    \
        .Init.DAC_SignedFormat                 = DISABLE,                    \
    }
#endif /* DAC1_CONFIG */
#endif /* BSP_USING_DAC1 */

#ifdef BSP_USING_DAC2
#ifndef DAC2_CONFIG
#define DAC2_CONFIG                                                          \
    {                                                                        \
        .DACx                                  = DAC2,                       \
        .DAC_Module                            = DAC12,                      \
        .periph_clk                            = RCC_APB1_PERIPHEN_M7_DAC12, \
        .EnablePeriphClk                       = RCC_EnableAPB1PeriphClk2,   \
        .DAC_clk_pres                          = 150,                        \
        .Init.DAC_Trigger                      = DAC_Trigger_Software,       \
        .Init.DAC_Trigger2                     = DAC_Trigger2_Software,      \
        .Init.DAC_WaveGeneration               = DAC_WaveGeneration_None,    \
        .Init.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0,        \
        .Init.DAC_OutputBuffer                 = DISABLE,                    \
        .Init.DAC_TriggerEnable                = ENABLE,                     \
        .Init.DAC_ConnectOnChipPeripheral      = DISABLE,                    \
        .Init.DAC_ConnectExternalPin           = ENABLE,                     \
        .Init.DAC_DMADoubleDataMode            = DISABLE,                    \
        .Init.DAC_SignedFormat                 = DISABLE,                    \
    }
#endif /* DAC2_CONFIG */
#endif /* BSP_USING_DAC2 */

#ifdef __cplusplus
}
#endif

#endif /* __DAC_CONFIG_H__ */
