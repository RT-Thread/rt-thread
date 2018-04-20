/*
 * File      : drv_pcf8563.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
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
#include <board.h>

#include <rtdevice.h>
#include <time.h>
#include "drv_pcf8563.h"

#ifdef RT_USING_PCF8563		

struct pcf8563_device
{
    struct rt_device rtc_parent;
    struct rt_i2c_bus_device *i2c_device;
};
static struct pcf8563_device pcf8563_dev;

//BCD To Byte
static unsigned char bcd_to_hex(unsigned char data)
{
    unsigned char temp;

    temp = ((data>>4)*10 + (data&0x0f));
    return temp;
}

//Byte To BCD
static unsigned char hex_to_bcd(unsigned char data)
{
    unsigned char temp;

    temp = (((data/10)<<4) + (data%10));
    return temp;
}

//read register
rt_uint8_t pcf8563_read_reg(rt_uint8_t reg,rt_uint8_t *data,rt_uint8_t data_size)
{
    struct rt_i2c_msg msg[2];
		
    msg[0].addr  = PCF8563_ARRD;
    msg[0].flags = RT_I2C_WR;
    msg[0].len   = 1;
    msg[0].buf   = &reg;
    msg[1].addr  = PCF8563_ARRD;
    msg[1].flags = RT_I2C_RD;
    msg[1].len   = data_size;
    msg[1].buf   = data;

    rt_i2c_transfer(pcf8563_dev.i2c_device, msg, 2);


    return RT_EOK;
}

//write register
rt_uint8_t pcf8563_write_reg(rt_uint8_t reg, rt_uint8_t *data,rt_uint8_t data_size)
{
    struct rt_i2c_msg msg[2];

    msg[0].addr   	= PCF8563_ARRD;
    msg[0].flags		= RT_I2C_WR;
    msg[0].len   		= 1;
    msg[0].buf   		= &reg;
    msg[1].addr  		= PCF8563_ARRD;
    msg[1].flags		= RT_I2C_WR | RT_I2C_NO_START;
    msg[1].len   		= data_size;
    msg[1].buf   		= data;
    rt_i2c_transfer(pcf8563_dev.i2c_device, msg, 2);

    return RT_EOK;
}

static rt_err_t rt_pcf8563_open(rt_device_t dev, rt_uint16_t flag)
{
    if (dev->rx_indicate != RT_NULL)
    {
        /* Open Interrupt */
    }

    return RT_EOK;
}

static rt_size_t rt_pcf8563_read(rt_device_t dev, rt_off_t pos, void *buffer, rt_size_t size)
{
    return RT_EOK;
}


static rt_err_t rt_pcf8563_control(rt_device_t dev, rt_uint8_t cmd, void *args)
{
    time_t 			*time;
    struct tm 	time_temp;	
    rt_uint8_t 	buff[7];
	
    RT_ASSERT(dev != RT_NULL);
    rt_memset(&time_temp, 0, sizeof(struct tm));

    switch (cmd)
    {
        case RT_DEVICE_CTRL_RTC_GET_TIME:
        time = (time_t *)args;
        pcf8563_read_reg(REG_PCF8563_SEC,buff,7);

        time_temp.tm_year  = bcd_to_hex(buff[6]&SHIELD_PCF8563_YEAR) + 2000 - 1900;
        time_temp.tm_mon   = bcd_to_hex(buff[5]&SHIELD_PCF8563_MON) - 1;
        time_temp.tm_mday  = bcd_to_hex(buff[3]&SHIELD_PCF8563_DAY);
        time_temp.tm_hour  = bcd_to_hex(buff[2]&SHIELD_PCF8563_HOUR);
        time_temp.tm_min   = bcd_to_hex(buff[1]&SHIELD_PCF8563_MIN);
        time_temp.tm_sec   = bcd_to_hex(buff[0]&SHIELD_PCF8563_SEC);

        *time = mktime(&time_temp);
        break;

        case RT_DEVICE_CTRL_RTC_SET_TIME:
        {
            struct tm *time_new;
					
            time = (time_t *)args;
            time_new = localtime(time);
            buff[6] = hex_to_bcd(time_new->tm_year + 1900 - 2000);
            buff[5] = hex_to_bcd(time_new->tm_mon + 1);
            buff[3] = hex_to_bcd(time_new->tm_mday);
            buff[4] = hex_to_bcd(time_new->tm_wday+1);
            buff[2] = hex_to_bcd(time_new->tm_hour);
            buff[1] = hex_to_bcd(time_new->tm_min);
            buff[0] = hex_to_bcd(time_new->tm_sec);
            pcf8563_write_reg(REG_PCF8563_SEC,buff,7);

        }
        break;
        default:
        break;
		}
    return RT_EOK;
}
		
//pcf8563 device int 
int rt_hw_pcf8563_init(void)
{		
    struct rt_i2c_bus_device *i2c_device;
    uint8_t data;
	
    i2c_device = rt_i2c_bus_device_find("i2c1");
    if (i2c_device == RT_NULL)
    {
		#ifdef RT_USE_FINSH_DEBUG
        //rt_kprintf("i2c bus device %s not found!\r\n", "i2c1");
		#endif
        return 1;
    }				 	
    pcf8563_dev.i2c_device = i2c_device;
    /* register rtc device */
    pcf8563_dev.rtc_parent.type   		= RT_Device_Class_RTC;
    pcf8563_dev.rtc_parent.init    		= RT_NULL;
    pcf8563_dev.rtc_parent.open    		= rt_pcf8563_open;
    pcf8563_dev.rtc_parent.close   		= RT_NULL;
    pcf8563_dev.rtc_parent.read   		= rt_pcf8563_read;
    pcf8563_dev.rtc_parent.write  	 	= RT_NULL;
    pcf8563_dev.rtc_parent.control 		= rt_pcf8563_control;
    pcf8563_dev.rtc_parent.user_data 	= RT_NULL;			/* no private */
    rt_device_register(&pcf8563_dev.rtc_parent, "rtc", RT_DEVICE_FLAG_RDWR);
		
    //init pcf8563
    data = 0x7f;	//close clock out
    pcf8563_write_reg(REG_PCF8563_CLKOUT,&data,1);

    return 0;
}
INIT_DEVICE_EXPORT(rt_hw_pcf8563_init);
#endif

