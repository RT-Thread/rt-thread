/*
 * Copyright (C) 2022, xiaoxiaolisunny
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author             Notes
 * 2022-05-10     xiaoxiaolisunny    first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>
#include <drv_adc.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_ADC1
#ifndef ADC1_CONFIG
#define ADC1_CONFIG                                                             \
    {                                                                           \
       .name                            = "adc1",                               \
       .resolution                      = AdcResolution_12Bit,                 \
       .data_align                      = AdcDataAlign_Right,                  \
       .auto_clear                      = AdcClren_Disable,                    \
       .eoc_poll_time_max               = 100,                                  \
       .hard_trig_enable                = RT_FALSE,                             \
       .internal_trig0_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig0_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig0_sel              = EVT_MAX,                          \
       .internal_trig1_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig1_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig1_sel              = EVT_MAX,                          \
       .continue_conv_mode_enable       = RT_FALSE,                             \
       .data_reg_auto_clear             = RT_TRUE,                              \
    }
#endif /* ADC1_CONFIG */
#endif /* BSP_USING_ADC1 */

#ifdef BSP_USING_ADC2
#ifndef ADC2_CONFIG
#define ADC2_CONFIG                                                             \
    {                                                                           \
       .name                            = "adc2",                               \
       .resolution                      = AdcResolution_12Bit,                 \
       .data_align                      = AdcDataAlign_Right,                  \
       .auto_clear                      = AdcClren_Disable,                    \
       .eoc_poll_time_max               = 100,                                  \
       .hard_trig_enable                = RT_FALSE,                             \
       .internal_trig0_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig0_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig0_sel              = EVT_MAX,                          \
       .internal_trig1_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig1_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig1_sel              = EVT_MAX,                          \
       .continue_conv_mode_enable       = RT_FALSE,                             \
       .data_reg_auto_clear             = RT_TRUE,                              \
    }
#endif /* ADC2_CONFIG */
#endif /* BSP_USING_ADC2 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_CONFIG_H__ */
