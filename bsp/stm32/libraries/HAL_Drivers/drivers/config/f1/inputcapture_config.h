/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-11-02     wdfk-prog         first version
 */
#ifndef __INPUTCAPTURE_CONFIG_H__
#define __INPUTCAPTURE_CONFIG_H__

#include "drv_inputcapture.h"

#ifdef BSP_USING_INPUT_CAPTURE_TIM1
/** @brief Board-selected TIM1 Input Capture configuration. */
#define INPUTCAPTURE_TIM1_CONFIG                                          \
    {                                                                     \
        .name = BSP_INPUT_CAPTURE_TIM1_NAME,                              \
        .instance = TIM1,                                                 \
        .channel = STM32_CAPTURE_CHANNEL(BSP_INPUT_CAPTURE_TIM1_CHANNEL), \
        .input_filter = BSP_INPUT_CAPTURE_TIM1_FILTER,                    \
        .counter_period = 0xFFFFU,                                        \
        .initial_edge_rising = BSP_INPUT_CAPTURE_TIM1_INITIAL_RISING,     \
        .hardware_both_edges = RT_FALSE,                                  \
    }
#endif /* BSP_USING_INPUT_CAPTURE_TIM1 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM2
/** @brief Board-selected TIM2 Input Capture configuration. */
#define INPUTCAPTURE_TIM2_CONFIG                                          \
    {                                                                     \
        .name = BSP_INPUT_CAPTURE_TIM2_NAME,                              \
        .instance = TIM2,                                                 \
        .channel = STM32_CAPTURE_CHANNEL(BSP_INPUT_CAPTURE_TIM2_CHANNEL), \
        .input_filter = BSP_INPUT_CAPTURE_TIM2_FILTER,                    \
        .counter_period = 0xFFFFU,                                        \
        .initial_edge_rising = BSP_INPUT_CAPTURE_TIM2_INITIAL_RISING,     \
        .hardware_both_edges = RT_FALSE,                                  \
    }
#endif /* BSP_USING_INPUT_CAPTURE_TIM2 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM3
/** @brief Board-selected TIM3 Input Capture configuration. */
#define INPUTCAPTURE_TIM3_CONFIG                                          \
    {                                                                     \
        .name = BSP_INPUT_CAPTURE_TIM3_NAME,                              \
        .instance = TIM3,                                                 \
        .channel = STM32_CAPTURE_CHANNEL(BSP_INPUT_CAPTURE_TIM3_CHANNEL), \
        .input_filter = BSP_INPUT_CAPTURE_TIM3_FILTER,                    \
        .counter_period = 0xFFFFU,                                        \
        .initial_edge_rising = BSP_INPUT_CAPTURE_TIM3_INITIAL_RISING,     \
        .hardware_both_edges = RT_FALSE,                                  \
    }
#endif /* BSP_USING_INPUT_CAPTURE_TIM3 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM4
/** @brief Board-selected TIM4 Input Capture configuration. */
#define INPUTCAPTURE_TIM4_CONFIG                                          \
    {                                                                     \
        .name = BSP_INPUT_CAPTURE_TIM4_NAME,                              \
        .instance = TIM4,                                                 \
        .channel = STM32_CAPTURE_CHANNEL(BSP_INPUT_CAPTURE_TIM4_CHANNEL), \
        .input_filter = BSP_INPUT_CAPTURE_TIM4_FILTER,                    \
        .counter_period = 0xFFFFU,                                        \
        .initial_edge_rising = BSP_INPUT_CAPTURE_TIM4_INITIAL_RISING,     \
        .hardware_both_edges = RT_FALSE,                                  \
    }
#endif /* BSP_USING_INPUT_CAPTURE_TIM4 */

#endif /* __INPUTCAPTURE_CONFIG_H__ */
