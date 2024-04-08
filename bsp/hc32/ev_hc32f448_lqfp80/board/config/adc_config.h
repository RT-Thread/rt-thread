/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_ADC1
#ifndef ADC1_INIT_PARAMS
#define ADC1_INIT_PARAMS                                                        \
    {                                                                           \
       .name                            = "adc1",                               \
       .vref                            = 3300,                                 \
       .resolution                      = ADC_RESOLUTION_12BIT,                 \
       .data_align                      = ADC_DATAALIGN_RIGHT,                  \
       .eoc_poll_time_max               = 100,                                  \
       .hard_trig_enable                = RT_FALSE,                             \
       .hard_trig_src                   = ADC_HARDTRIG_EVT0,                    \
       .internal_trig0_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig0_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig0_sel              = EVT_SRC_TMR0_1_CMP_A,                 \
       .internal_trig1_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig1_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig1_sel              = EVT_SRC_MAX,                          \
       .continue_conv_mode_enable       = RT_FALSE,                             \
       .data_reg_auto_clear             = RT_TRUE,                              \
    }
#endif /* ADC1_INIT_PARAMS */

#if defined (BSP_ADC1_USING_DMA)
#ifndef ADC1_EOCA_DMA_CONFIG
#define ADC1_EOCA_DMA_CONFIG                                                    \
    {                                                                           \
        .Instance                       = ADC1_EOCA_DMA_INSTANCE,               \
        .channel                        = ADC1_EOCA_DMA_CHANNEL,                \
        .clock                          = ADC1_EOCA_DMA_CLOCK,                  \
        .trigger_select                 = ADC1_EOCA_DMA_TRIG_SELECT,            \
        .trigger_event                  = EVT_SRC_ADC1_EOCA,                    \
        .flag                           = ADC1_EOCA_DMA_TRANS_FLAG,             \
        .irq_config                     =                                       \
        {                                                                       \
            .irq_num                    = ADC1_EOCA_DMA_IRQn,                   \
            .irq_prio                   = ADC1_EOCA_DMA_INT_PRIO,               \
            .int_src                    = ADC1_EOCA_DMA_INT_SRC,                \
        },                                                                      \
    }
#endif /* ADC1_EOCA_DMA_CONFIG */
#endif /* BSP_ADC1_USING_DMA */
#endif /* BSP_USING_ADC1 */

#ifdef BSP_USING_ADC2
#ifndef ADC2_INIT_PARAMS
#define ADC2_INIT_PARAMS                                                        \
    {                                                                           \
       .name                            = "adc2",                               \
       .vref                            = 3300,                                 \
       .resolution                      = ADC_RESOLUTION_12BIT,                 \
       .data_align                      = ADC_DATAALIGN_RIGHT,                  \
       .eoc_poll_time_max               = 100,                                  \
       .hard_trig_enable                = RT_FALSE,                             \
       .hard_trig_src                   = ADC_HARDTRIG_EVT0,                    \
       .internal_trig0_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig0_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig0_sel              = EVT_SRC_TMR0_1_CMP_A,                 \
       .internal_trig1_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig1_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig1_sel              = EVT_SRC_MAX,                          \
       .continue_conv_mode_enable       = RT_FALSE,                             \
       .data_reg_auto_clear             = RT_TRUE,                              \
    }
#endif /* ADC2_INIT_PARAMS */

#if defined (BSP_ADC2_USING_DMA)
#ifndef ADC2_EOCA_DMA_CONFIG
#define ADC2_EOCA_DMA_CONFIG                                                    \
    {                                                                           \
        .Instance                       = ADC2_EOCA_DMA_INSTANCE,               \
        .channel                        = ADC2_EOCA_DMA_CHANNEL,                \
        .clock                          = ADC2_EOCA_DMA_CLOCK,                  \
        .trigger_select                 = ADC2_EOCA_DMA_TRIG_SELECT,            \
        .trigger_event                  = EVT_SRC_ADC2_EOCA,                    \
        .flag                           = ADC2_EOCA_DMA_TRANS_FLAG,             \
        .irq_config                     =                                       \
        {                                                                       \
            .irq_num                    = ADC2_EOCA_DMA_IRQn,                   \
            .irq_prio                   = ADC2_EOCA_DMA_INT_PRIO,               \
            .int_src                    = ADC2_EOCA_DMA_INT_SRC,                \
        },                                                                      \
    }
#endif /* ADC2_EOCA_DMA_CONFIG */
#endif /* BSP_ADC2_USING_DMA */
#endif /* BSP_USING_ADC2 */

#ifdef BSP_USING_ADC3
#ifndef ADC3_INIT_PARAMS
#define ADC3_INIT_PARAMS                                                        \
    {                                                                           \
       .name                            = "adc3",                               \
       .vref                            = 3300,                                 \
       .resolution                      = ADC_RESOLUTION_12BIT,                 \
       .data_align                      = ADC_DATAALIGN_RIGHT,                  \
       .eoc_poll_time_max               = 100,                                  \
       .hard_trig_enable                = RT_FALSE,                             \
       .hard_trig_src                   = ADC_HARDTRIG_EVT0,                    \
       .internal_trig0_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig0_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig0_sel              = EVT_SRC_TMR0_1_CMP_A,                 \
       .internal_trig1_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig1_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig1_sel              = EVT_SRC_MAX,                          \
       .continue_conv_mode_enable       = RT_FALSE,                             \
       .data_reg_auto_clear             = RT_TRUE,                              \
    }
#endif /* ADC3_INIT_PARAMS */

#if defined (BSP_ADC3_USING_DMA)
#ifndef ADC3_EOCA_DMA_CONFIG
#define ADC3_EOCA_DMA_CONFIG                                                    \
    {                                                                           \
        .Instance                       = ADC3_EOCA_DMA_INSTANCE,               \
        .channel                        = ADC3_EOCA_DMA_CHANNEL,                \
        .clock                          = ADC3_EOCA_DMA_CLOCK,                  \
        .trigger_select                 = ADC3_EOCA_DMA_TRIG_SELECT,            \
        .trigger_event                  = EVT_SRC_ADC3_EOCA,                    \
        .flag                           = ADC3_EOCA_DMA_TRANS_FLAG,             \
        .irq_config                     =                                       \
        {                                                                       \
            .irq_num                    = ADC3_EOCA_DMA_IRQn,                   \
            .irq_prio                   = ADC3_EOCA_DMA_INT_PRIO,               \
            .int_src                    = ADC3_EOCA_DMA_INT_SRC,                \
        },                                                                      \
    }
#endif /* ADC3_EOCA_DMA_CONFIG */
#endif /* BSP_ADC3_USING_DMA */
#endif /* BSP_USING_ADC3 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_CONFIG_H__ */
