/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-08-18     guohp1128    the first version
 */

#ifndef __DRV_ADC_H__
#define __DRV_ADC_H__

#include <board.h>
#include "rtdevice.h"
#include <hal/nrf_saadc.h>
#include <drivers/include/nrfx_saadc.h>

#define ADC_NAME "adc"

/*
    previous definition in application

    set single-ended mode or differential mode.
    selection ADC input pin, and config the number of Channel.

    mode: 0 single-ended mode,1 differential mode
    pin_p: 0-7
    pin_n: 0-7,if single-ended mode, pin_n invalid
    channel_num: 0-7
 */
typedef struct
{
    nrf_saadc_mode_t    mode;           ///< SAADC mode. Single-ended or differential.
    uint8_t             pin_p;          ///< Input positive pin selection.
    uint8_t             pin_n;          ///< Input negative pin selection.
    uint8_t             channel_num;    ///< Channel number.
} drv_nrfx_saadc_channel_t;

typedef struct
{
    nrfx_saadc_channel_t    channels[8];
    uint8_t                 channel_count;
    nrf_saadc_value_t       result_buffer[8];
    uint8_t                 done;
} drv_nrfx_saadc_result_t;

#endif /* __DRV_ADC_H__ */
