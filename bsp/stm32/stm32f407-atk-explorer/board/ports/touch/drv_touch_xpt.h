/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-6-27      solar        first version
 */

#ifndef __DRV_XPT2046_H__
#define __DRV_XPT2046_H__

#include <rtthread.h>
#include <rtdevice.h>
#include "touch.h"

#ifdef BSP_USING_TOUCH_RES

/* Related parameters of screen calibration, if the calibration is not performed 
 * after power on, please manually set the following macro definitions */
#define BSP_XPT2046_MIN_RAW_X   100
#define BSP_XPT2046_MIN_RAW_Y   100
#define BSP_XPT2046_MAX_RAW_X   100
#define BSP_XPT2046_MAX_RAW_Y   100
#define BSP_XPT2046_RANGE_X     320
#define BSP_XPT2046_RANGE_Y     480

/* cmd for Calibrate touch */
#define RT_TOUCH_CALIBRATION (RT_DEVICE_CTRL_BASE(Touch) + 20)

struct rt_xpt2046
{
    struct rt_touch_device parent;
    struct rt_spi_device *spi; 
    rt_uint16_t min_raw_x;
    rt_uint16_t min_raw_y;
    rt_uint16_t max_raw_x;
    rt_uint16_t max_raw_y;
};
typedef struct rt_xpt2046 *rt_xpt2046_t;

struct calibrate_args
{
    char *lcd_name;
    char *touch_name;
};

#endif /* BSP_USING_TOUCH_RES */

#endif /* __DRV_XPT2046_H__ */
