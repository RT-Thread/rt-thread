/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-02-22     airm2m       first version
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

#endif
