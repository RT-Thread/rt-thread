/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author    Notes
 * 2025-05-28     RTT       the first version
 */
#ifndef __ADC_CONFIG_H__
#define __ADC_CONFIG_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "drv_common.h"
#include "cyhal.h"
#include "cybsp.h"

#ifdef __cplusplus
extern "C"
{
#endif

#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2)

cyhal_adc_t adc_obj;
cyhal_adc_channel_t adc_chan_obj;

const cyhal_adc_config_t adc_config = {
        .continuous_scanning = false,   // Continuous Scanning is disabled
        .average_count = 1,             // Average count disabled
        .vref = CYHAL_ADC_REF_VDDA,     // VREF for Single ended channel set to VDDA
        .vneg = CYHAL_ADC_VNEG_VSSA,    // VNEG for Single ended channel set to VSSA
        .resolution = 12u,              // 12-bit resolution
        .ext_vref = NC,                 // No connection
        .bypass_pin = NC                // No connection
};

struct ifx_adc
{
    struct rt_adc_device ifx_adc_device;
    cyhal_adc_channel_t *adc_ch;
    char *name;
};

const cyhal_gpio_t adc_gpio[6] = {P10_0, P10_1, P10_2, P10_3, P10_4, P10_5};

#ifndef ADC1_CONFIG
#define ADC1_CONFIG                 \
    {                               \
        .adc_ch = &adc_chan_obj,    \
        .name = "adc1",             \
    }
#endif

#endif /* defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2) */

#ifdef __cplusplus
}
#endif

#endif /* __ADC_CONFIG_H__ */
