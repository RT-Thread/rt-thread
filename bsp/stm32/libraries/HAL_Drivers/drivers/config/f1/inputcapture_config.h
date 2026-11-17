/*
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2026-11-01     wdfk-prog         first version
 * 2026-11-10     wdfk-prog         describe individual capture channels and exclusive PWM Input
 */
#ifndef __INPUTCAPTURE_CONFIG_H__
#define __INPUTCAPTURE_CONFIG_H__

/* The configurations below describe board hardware, not Kconfig user choices.
 * Edit pin-related capture polarity, filter, ARR and name for this board here.
 * Every logical device on the same physical TIM shares PSC, ARR and CNT.
 * PWM_INPUT uses the direct input channel plus its indirect paired channel.
 * DUAL_EDGE pairs the same input without slave reset or interval batching.
 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM1
/** @brief TIM1 CH1 independent input-capture configuration. */
#define INPUTCAPTURE_TIM1_CH1_CONFIG     \
    {                                    \
        .name = "ic1",                   \
        .instance = TIM1,                \
        .channel = TIM_CHANNEL_1,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM1 CH2 independent input-capture configuration. */
#define INPUTCAPTURE_TIM1_CH2_CONFIG     \
    {                                    \
        .name = "ic1_2",                 \
        .instance = TIM1,                \
        .channel = TIM_CHANNEL_2,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM1 CH3 independent input-capture configuration. */
#define INPUTCAPTURE_TIM1_CH3_CONFIG     \
    {                                    \
        .name = "ic1_3",                 \
        .instance = TIM1,                \
        .channel = TIM_CHANNEL_3,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM1 CH4 independent input-capture configuration. */
#define INPUTCAPTURE_TIM1_CH4_CONFIG     \
    {                                    \
        .name = "ic1_4",                 \
        .instance = TIM1,                \
        .channel = TIM_CHANNEL_4,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM1 exclusive PWM Input configuration (CH1+CH2 pair). */
#define INPUTCAPTURE_TIM1_PWM_CONFIG                   \
    {                                                  \
        .name = "ic1",                                 \
        .instance = TIM1,                              \
        .channel = TIM_CHANNEL_1,                      \
        .input_filter = 0U,                            \
        .counter_period = 0xFFFFU,                     \
        .initial_edge_rising = RT_TRUE,                \
        .hardware_both_edges = RT_FALSE,               \
        .pwm_input = BSP_INPUT_CAPTURE_TIM1_PWM_INPUT, \
    }
/** @brief TIM1 exclusive dual-edge capture (CH1/CH2 on one TI input). */
#define INPUTCAPTURE_TIM1_DUAL_CONFIG    \
    {                                    \
        .name = "ic1",                   \
        .instance = TIM1,                \
        .channel = TIM_CHANNEL_1,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
        .dual_edge = RT_TRUE,            \
        .dual_partner_filter = 0U,       \
    }

#endif /* BSP_USING_INPUT_CAPTURE_TIM1 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM2
/** @brief TIM2 CH1 independent input-capture configuration. */
#define INPUTCAPTURE_TIM2_CH1_CONFIG     \
    {                                    \
        .name = "ic2",                   \
        .instance = TIM2,                \
        .channel = TIM_CHANNEL_1,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM2 CH2 independent input-capture configuration. */
#define INPUTCAPTURE_TIM2_CH2_CONFIG     \
    {                                    \
        .name = "ic2_2",                 \
        .instance = TIM2,                \
        .channel = TIM_CHANNEL_2,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM2 CH3 independent input-capture configuration. */
#define INPUTCAPTURE_TIM2_CH3_CONFIG     \
    {                                    \
        .name = "ic2_3",                 \
        .instance = TIM2,                \
        .channel = TIM_CHANNEL_3,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM2 CH4 independent input-capture configuration. */
#define INPUTCAPTURE_TIM2_CH4_CONFIG     \
    {                                    \
        .name = "ic2_4",                 \
        .instance = TIM2,                \
        .channel = TIM_CHANNEL_4,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM2 exclusive PWM Input configuration (CH1+CH2 pair). */
#define INPUTCAPTURE_TIM2_PWM_CONFIG                   \
    {                                                  \
        .name = "ic2",                                 \
        .instance = TIM2,                              \
        .channel = TIM_CHANNEL_1,                      \
        .input_filter = 0U,                            \
        .counter_period = 0xFFFFU,                     \
        .initial_edge_rising = RT_TRUE,                \
        .hardware_both_edges = RT_FALSE,               \
        .pwm_input = BSP_INPUT_CAPTURE_TIM2_PWM_INPUT, \
    }
/** @brief TIM2 exclusive dual-edge capture (CH1/CH2 on one TI input). */
#define INPUTCAPTURE_TIM2_DUAL_CONFIG    \
    {                                    \
        .name = "ic2",                   \
        .instance = TIM2,                \
        .channel = TIM_CHANNEL_1,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
        .dual_edge = RT_TRUE,            \
        .dual_partner_filter = 0U,       \
    }

#endif /* BSP_USING_INPUT_CAPTURE_TIM2 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM3
/** @brief TIM3 CH1 independent input-capture configuration. */
#define INPUTCAPTURE_TIM3_CH1_CONFIG     \
    {                                    \
        .name = "ic3_1",                 \
        .instance = TIM3,                \
        .channel = TIM_CHANNEL_1,        \
        .input_filter = 9U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_FALSE, \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM3 CH2 independent input-capture configuration. */
#define INPUTCAPTURE_TIM3_CH2_CONFIG     \
    {                                    \
        .name = "ic0",                   \
        .instance = TIM3,                \
        .channel = TIM_CHANNEL_2,        \
        .input_filter = 9U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_FALSE, \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM3 CH3 independent input-capture configuration. */
#define INPUTCAPTURE_TIM3_CH3_CONFIG     \
    {                                    \
        .name = "ic3_3",                 \
        .instance = TIM3,                \
        .channel = TIM_CHANNEL_3,        \
        .input_filter = 9U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_FALSE, \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM3 CH4 independent input-capture configuration. */
#define INPUTCAPTURE_TIM3_CH4_CONFIG     \
    {                                    \
        .name = "ic3_4",                 \
        .instance = TIM3,                \
        .channel = TIM_CHANNEL_4,        \
        .input_filter = 9U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_FALSE, \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM3 exclusive PWM Input configuration (CH1+CH2 pair). */
#define INPUTCAPTURE_TIM3_PWM_CONFIG                   \
    {                                                  \
        .name = "ic0",                                 \
        .instance = TIM3,                              \
        .channel = TIM_CHANNEL_2,                      \
        .input_filter = 9U,                            \
        .counter_period = 0xFFFFU,                     \
        .initial_edge_rising = RT_FALSE,               \
        .hardware_both_edges = RT_FALSE,               \
        .pwm_input = BSP_INPUT_CAPTURE_TIM3_PWM_INPUT, \
    }
/** @brief TIM3 exclusive dual-edge capture (CH1/CH2 on one TI input). */
#define INPUTCAPTURE_TIM3_DUAL_CONFIG    \
    {                                    \
        .name = "ic0",                   \
        .instance = TIM3,                \
        .channel = TIM_CHANNEL_2,        \
        .input_filter = 9U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
        .dual_edge = RT_TRUE,            \
        .dual_partner_filter = 0U,       \
    }

#endif /* BSP_USING_INPUT_CAPTURE_TIM3 */

#ifdef BSP_USING_INPUT_CAPTURE_TIM4
/** @brief TIM4 CH1 independent input-capture configuration. */
#define INPUTCAPTURE_TIM4_CH1_CONFIG     \
    {                                    \
        .name = "ic4",                   \
        .instance = TIM4,                \
        .channel = TIM_CHANNEL_1,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM4 CH2 independent input-capture configuration. */
#define INPUTCAPTURE_TIM4_CH2_CONFIG     \
    {                                    \
        .name = "ic4_2",                 \
        .instance = TIM4,                \
        .channel = TIM_CHANNEL_2,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM4 CH3 independent input-capture configuration. */
#define INPUTCAPTURE_TIM4_CH3_CONFIG     \
    {                                    \
        .name = "ic4_3",                 \
        .instance = TIM4,                \
        .channel = TIM_CHANNEL_3,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM4 CH4 independent input-capture configuration. */
#define INPUTCAPTURE_TIM4_CH4_CONFIG     \
    {                                    \
        .name = "ic4_4",                 \
        .instance = TIM4,                \
        .channel = TIM_CHANNEL_4,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
    }

/** @brief TIM4 exclusive PWM Input configuration (CH1+CH2 pair). */
#define INPUTCAPTURE_TIM4_PWM_CONFIG                   \
    {                                                  \
        .name = "ic4",                                 \
        .instance = TIM4,                              \
        .channel = TIM_CHANNEL_1,                      \
        .input_filter = 0U,                            \
        .counter_period = 0xFFFFU,                     \
        .initial_edge_rising = RT_TRUE,                \
        .hardware_both_edges = RT_FALSE,               \
        .pwm_input = BSP_INPUT_CAPTURE_TIM4_PWM_INPUT, \
    }
/** @brief TIM4 exclusive dual-edge capture (CH1/CH2 on one TI input). */
#define INPUTCAPTURE_TIM4_DUAL_CONFIG    \
    {                                    \
        .name = "ic4",                   \
        .instance = TIM4,                \
        .channel = TIM_CHANNEL_1,        \
        .input_filter = 0U,              \
        .counter_period = 0xFFFFU,       \
        .initial_edge_rising = RT_TRUE,  \
        .hardware_both_edges = RT_FALSE, \
        .pwm_input = RT_FALSE,           \
        .dual_edge = RT_TRUE,            \
        .dual_partner_filter = 0U,       \
    }

#endif /* BSP_USING_INPUT_CAPTURE_TIM4 */

#endif /* __INPUTCAPTURE_CONFIG_H__ */
