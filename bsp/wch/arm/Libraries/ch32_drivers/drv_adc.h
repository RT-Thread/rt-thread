/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-06-29     zhan          first version
 */

#ifndef DRV_ADC_H__
#define DRV_ADC_H__

typedef struct
{
    ADC_TypeDef                   *Instance;
    ADC_InitTypeDef                Init;
}ADC_HandleTypeDef;

typedef struct
{
    uint32_t     Channel;
    uint32_t     Rank;
    uint32_t     SamplingTime;
    uint32_t     Offset;
}ADC_ChannelConfTypeDef;

int rt_hw_adc_init(void); 

#endif
