/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 * Copyright (c) 2022, xiaoxiaolisunny
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author                   Notes
 * 2022-06-07     xiaoxiaolisunny          first version
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
       .resolution                      = ADC_RESOLUTION_12BIT,                 \
       .data_align                      = ADC_DATAALIGN_RIGHT,                  \
       .eoc_poll_time_max               = 100,                                  \
       .hard_trig_enable                = RT_FALSE,                             \
       .hard_trig_src                   = ADC_HARDTRIG_ADTRG_PIN,               \
       .internal_trig0_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig0_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig0_sel              = EVT_SRC_MAX,                          \
       .internal_trig1_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig1_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig1_sel              = EVT_SRC_MAX,                          \
       .continue_conv_mode_enable       = RT_FALSE,                             \
       .data_reg_auto_clear             = RT_TRUE,                              \
    }
#endif /* ADC1_INIT_PARAMS */
#endif /* BSP_USING_ADC1 */

#ifdef BSP_USING_ADC2
#ifndef ADC2_INIT_PARAMS
#define ADC2_INIT_PARAMS                                                        \
    {                                                                           \
       .name                            = "adc2",                               \
       .resolution                      = ADC_RESOLUTION_12BIT,                 \
       .data_align                      = ADC_DATAALIGN_RIGHT,                  \
       .eoc_poll_time_max               = 100,                                  \
       .hard_trig_enable                = RT_FALSE,                             \
       .hard_trig_src                   = ADC_HARDTRIG_ADTRG_PIN,               \
       .internal_trig0_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig0_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig0_sel              = EVT_SRC_MAX,                          \
       .internal_trig1_comtrg0_enable   = RT_FALSE,                             \
       .internal_trig1_comtrg1_enable   = RT_FALSE,                             \
       .internal_trig1_sel              = EVT_SRC_MAX,                          \
       .continue_conv_mode_enable       = RT_FALSE,                             \
       .data_reg_auto_clear             = RT_TRUE,                              \
    }
#endif /* ADC2_INIT_PARAMS */
#endif /* BSP_USING_ADC2 */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_CONFIG_H__ */
