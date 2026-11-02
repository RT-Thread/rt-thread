/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-23     Chushicheng  first version
 */

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include <rtconfig.h>

#if defined BSP_USING_ADC

/* esp config class */
static struct esp_adc_config
{
    rt_uint8_t adc_id;
    const char *device_name;
};

int rt_hw_adc_init(void);

#endif /* BSP_USING_ADC */
#endif /* __DRV_ADC_H__ */
