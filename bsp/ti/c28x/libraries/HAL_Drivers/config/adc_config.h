/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-07     qiyu         first version
 */

#ifndef DRIVERS_CONFIG_ADC_CONFIG_H_
#define DRIVERS_CONFIG_ADC_CONFIG_H_
#include "F28x_Project.h"     // Device Headerfile and Examples Include File
#include "F2837xD_adc.h"
#include "rtthread.h"
#include "drv_config.h"
#define BSP_USING_ADC1
#ifdef __cplusplus
extern "C" {
#endif
#ifdef BSP_USING_ADC1
    #ifndef ADC1_CONFIG
    #define ADC1_CONFIG                             \
    {                                           \
        .name = "adc1",                         \
        .adc_regs   = &AdcaRegs,                \
        .adc_results = &AdcaResultRegs,          \
    }
    #endif
#endif
#ifdef BSP_USING_ADC2
    #ifndef ADC2_CONFIG
    #define ADC2_CONFIG                             \
    {                                           \
        .name = "adc2",                         \
        .adc_regs   = &AdcbRegs,                \
        .adc_results = &AdcbResultRegs          \
    }
    #endif
#endif
#ifdef BSP_USING_ADC3
    #ifndef ADC3_CONFIG
    #define ADC3_CONFIG                             \
    {                                           \
        .name = "adc3",                         \
        .adc_regs   = &AdccRegs,                \
        .adc_results = &AdccResultRegs          \
    }
    #endif
#endif
#ifdef __cplusplus
}
#endif
#endif /* DRIVERS_CONFIG_ADC_CONFIG_H_ */
