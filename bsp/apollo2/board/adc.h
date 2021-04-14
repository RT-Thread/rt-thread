/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-18     Haley        the first version
 */

#ifndef __ADC_H_
#define __ADC_H_

#include <rtthread.h>

/**
 * @brief External function definitions
 *
 */
int rt_hw_adc_init(void);
rt_uint8_t am_adc_data_get(rt_uint8_t channel, rt_int16_t *buff, rt_uint16_t size);
void am_adc_start(rt_uint8_t channel);
void am_adc_stop(rt_uint8_t channel);

#endif // __ADC_H_
