/*
 * File      : drv_adc.h
 * This file is part of GK710X BSP for RT-Thread distribution.
 *
 * Copyright (c) 2017 GOKE Microelectronics Co., Ltd.
 * All rights reserved
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Visit http://www.goke.com to get contact with Goke.
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef ADC_H_
#define ADC_H_

#include <rtdef.h>
#ifdef RT_USING_ADC

/****************************************************************************
 * #define section
 *	add constant #define here if any
 ***************************************************************************/
#define MAX_CHANNEL_NO (2)
#define ADC_INIT_ALREADY (0x33)

#define ADC_CMD_READ_RAW_DATA (0x22)
#define ADC_CMD_DISABLE (0x44)

/****************************************************************************
 * ADT section
 *	add Abstract Data Type definition here
 ***************************************************************************/

struct wrap_adc_obj
{
    rt_uint32_t id;
    rt_uint32_t init_flag;
    rt_uint32_t active_channel_no;
    rt_uint32_t handle;
    rt_uint16_t channel_data[MAX_CHANNEL_NO];

    // bind to the rtdev..
    rt_device_t rt_dev;
};

typedef struct
{
    rt_uint32_t channel;
    rt_uint32_t adc_data;
} ADC_INFO;

/****************************************************************************
 *  extern variable declaration section
 ***************************************************************************/

/****************************************************************************
 *  section
 *	add function prototype here if any
 ***************************************************************************/
void rt_hw_adc_init(void);
#endif
#endif /* ADC_H_ */
