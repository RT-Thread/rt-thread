/*
 * File      : touch.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
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
 * Change Logs:
 * Date           Author       Notes
 * 2017-12-30    Sundm75       first version
 */
 #ifndef __TOUCH_H__
#define __TOUCH_H__

#define RT_TOUCH_NORMAL		        0
#define RT_TOUCH_CALIBRATION_DATA	1
#define RT_TOUCH_CALIBRATION 		2

//#define SAVE_CALIBRATION

     
rt_uint16_t touch_read_x(void);
rt_uint16_t touch_read_y(void);
void touch_config(void);
																 

rt_err_t rtgui_touch_hw_init(const char * spi_device_name);
		  
#endif


