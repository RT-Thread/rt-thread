/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-16     linshire     add some operation function
 * 2021-09-09     WCH          the first version
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
