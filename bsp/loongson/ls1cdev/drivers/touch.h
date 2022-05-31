/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-30    Sundm75       first version
 */
 #ifndef __TOUCH_H__
#define __TOUCH_H__

#define RT_TOUCH_NORMAL             0
#define RT_TOUCH_CALIBRATION_DATA   1
#define RT_TOUCH_CALIBRATION        2

//#define SAVE_CALIBRATION


rt_uint16_t touch_read_x(void);
rt_uint16_t touch_read_y(void);
void touch_config(void);


rt_err_t rtgui_touch_hw_init(const char * spi_device_name);

#endif


