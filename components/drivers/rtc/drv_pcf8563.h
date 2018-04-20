/*
 * File      : drv_pcf8563.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2017, RT-Thread Development Team
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
 * 2018-04-20     Acuity       the first version
 */

#ifndef _DRV_PCF8563_H_
#define _DRV_PCF8563_H_

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

//地址	
#define 		PCF8563_ARRD				0X51			//i2c slave address	

//寄存器
#define			REG_PCF8563_STATE1			0X00
#define			REG_PCF8563_STATE2			0X01
#define			REG_PCF8563_SEC				0X02
#define			REG_PCF8563_MIN				0X03
#define			REG_PCF8563_HOUR			0X04
#define			REG_PCF8563_DAY				0X05
#define			REG_PCF8563_WEEK			0X06
#define			REG_PCF8563_MON				0X07
#define			REG_PCF8563_YEAR			0X08
#define			REG_PCF8563_CLKOUT			0X0d


//屏蔽无效位
#define 		SHIELD_PCF8563_STATE1   (unsigned char)0xa8
#define 		SHIELD_PCF8563_STATE2   (unsigned char)0x1f
#define 		SHIELD_PCF8563_SEC      (unsigned char)0x7f
#define 		SHIELD_PCF8563_MIN      (unsigned char)0x7f
#define 		SHIELD_PCF8563_HOUR     (unsigned char)0x3f
#define 		SHIELD_PCF8563_DAY      (unsigned char)0x3f
#define 		SHIELD_PCF8563_WEEK     (unsigned char)0x07
#define 		SHIELD_PCF8563_MON      (unsigned char)0x1f
#define 		SHIELD_PCF8563_YEAR     (unsigned char)0xff

externa int rt_hw_pcf8563_init(void);

#endif 
