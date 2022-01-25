/*
 * Copyright (c) 2020-2021, Bluetrum Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-02-01     greedyhao         first version
 */

#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef BSP_USING_ADC0
#ifndef ADC0_CONFIG
#define ADC0_CONFIG                                     \
    {                                                   \
       .adc_dat_handle      = (hal_sfr_t)&SADCDAT0,     \
       .name                = "adc0",                   \
    }
#endif /* ADC0_CONFIG */
#endif /* BSP_USING_ADC0 */

#ifdef __cplusplus
}
#endif

#endif
