/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-10-07     qiyu         first version
 */

#ifndef DRIVERS_DRV_ADC_H_
#define DRIVERS_DRV_ADC_H_
#ifdef BSP_ADC_USING_12BIT
#define ADC_RESOLUTION ADC_RESOLUTION_12BIT
#else
#define ADC_RESOLUTION ADC_RESOLUTION_16BIT
#endif
#include "rtdevice.h"
#ifdef BSP_USING_ADC

struct c28x_adc
{
    struct rt_adc_device c28x_adc_device;
    volatile struct ADC_REGS *adc_regs;
    volatile struct ADC_RESULT_REGS *adc_results;
    const char *name;
};
#endif /* BSP_USING_ADC */

#endif /* DRIVERS_DRV_ADC_H_ */
