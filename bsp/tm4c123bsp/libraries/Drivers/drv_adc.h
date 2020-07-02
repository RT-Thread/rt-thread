/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-27     AHTYDHD      the first version
 */

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include<stdint.h>
#include<rtthread.h>
#include<rtdevice.h>
#include<rthw.h>

struct tm4c123_adc_config
{
    const char  *name;
    uint32_t    adcbase;
    uint32_t    channel;
    uint32_t    sequence;
    uint32_t    trigermode;
    uint32_t    sequencepriority;
};

#endif /*__DRV_ADC_H__*/

/************************** end of file ******************/