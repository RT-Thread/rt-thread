/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
