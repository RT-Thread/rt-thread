/*
 * File      : drv_slcdc_ili9341.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2008 - 2016, RT-Thread Development Team
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
 * 2016-08-12     fujie        The first version
 */

#include <string.h>

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include "board.h"
#include "drv_gpio.h"
#include "drv_slcdc.h"
#include "drv_clock.h"

#if defined(RT_USING_ILI9341)

rt_uint32_t _ili9341_cmd_table[]=
{
        0x2c2c2c2c,
};


const struct slcd_data_table _ili9341_data_table[] =
{
	{SMART_CONFIG_CMD,  0x11},
	{SMART_CONFIG_UDELAY, 1200},

	{SMART_CONFIG_CMD,  0xCF},	//Power control B 功耗控制B 【3参数】
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0xAA},
	{SMART_CONFIG_DATA, 0XB0},

	{SMART_CONFIG_CMD,  0xED},	//Power on sequence control 电源时序控制B 【4参数】
	{SMART_CONFIG_DATA, 0x64},
	{SMART_CONFIG_DATA, 0x03},
	{SMART_CONFIG_DATA, 0X12},
	{SMART_CONFIG_DATA, 0X81},

	{SMART_CONFIG_CMD,  0xE8},	//Driver timing control A
	{SMART_CONFIG_DATA, 0x85},
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0x78},

	{SMART_CONFIG_CMD,  0xCB},	//Power control A
	{SMART_CONFIG_DATA, 0x39},
	{SMART_CONFIG_DATA, 0x2C},
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0x34},
	{SMART_CONFIG_DATA, 0x02},

	{SMART_CONFIG_CMD,  0xF7},	//Pump ratio control
	{SMART_CONFIG_DATA, 0x20},

	{SMART_CONFIG_CMD,  0xEA},	// Driver timing control B
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0x00},

	{SMART_CONFIG_CMD,  0xb6},	//Display Function Control
	{SMART_CONFIG_DATA, 0x0a},
	{SMART_CONFIG_DATA, 0xa2},

	{SMART_CONFIG_CMD,  0xC0},	//Power control
	{SMART_CONFIG_DATA, 0x26},	//VRH[5:0]

	{SMART_CONFIG_CMD,  0xC1},	//Power control
	{SMART_CONFIG_DATA, 0x11},	//SAP[2:0];BT[3:0]

	{SMART_CONFIG_CMD,  0xC5},	//VCM control
	{SMART_CONFIG_DATA, 0x31},	//对比度调节 0x31
	{SMART_CONFIG_DATA, 0x3C},

	{SMART_CONFIG_CMD,  0xC7},	//VCM control2
	{SMART_CONFIG_DATA, 0xd3},

	{SMART_CONFIG_CMD,  0x36},	// Memory Access Control
	{SMART_CONFIG_DATA, 0x68},	// ●定义帧存储器的读写扫描方向   //[竖屏]0x48	0x88	[横屏]0x28 0xE8  0x68 //0x08

	{SMART_CONFIG_CMD,  0x3A},	//COLMOD: Pixel Format Set
	{SMART_CONFIG_DATA, 0x55},

	{SMART_CONFIG_CMD,  0xB1},	//VCM control
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0x14},

	{SMART_CONFIG_CMD,  0xF2},	   // 3Gamma Function Disable
	{SMART_CONFIG_DATA, 0x00},

	{SMART_CONFIG_CMD,  0x26},	   //Gamma curve selected
	{SMART_CONFIG_DATA, 0x01},

	{SMART_CONFIG_CMD,  0xE0},	   //Set Gamma
	{SMART_CONFIG_DATA, 0x0F},
	{SMART_CONFIG_DATA, 0x1d},
	{SMART_CONFIG_DATA, 0x1a},
	{SMART_CONFIG_DATA, 0x09},
	{SMART_CONFIG_DATA, 0x0f},
	{SMART_CONFIG_DATA, 0x09},
	{SMART_CONFIG_DATA, 0x46},
	{SMART_CONFIG_DATA, 0x88},
	{SMART_CONFIG_DATA, 0x39},
	{SMART_CONFIG_DATA, 0x05},
	{SMART_CONFIG_DATA, 0x0f},
	{SMART_CONFIG_DATA, 0x03},
	{SMART_CONFIG_DATA, 0x07},
	{SMART_CONFIG_DATA, 0x05},
	{SMART_CONFIG_DATA, 0x00},

	{SMART_CONFIG_CMD,  0XE1},	   //Set Gamma
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0x22},
	{SMART_CONFIG_DATA, 0x25},
	{SMART_CONFIG_DATA, 0x06},
	{SMART_CONFIG_DATA, 0x10},
	{SMART_CONFIG_DATA, 0x06},
	{SMART_CONFIG_DATA, 0x39},
	{SMART_CONFIG_DATA, 0x22},
	{SMART_CONFIG_DATA, 0x4a},
	{SMART_CONFIG_DATA, 0x0a},
	{SMART_CONFIG_DATA, 0x10},
	{SMART_CONFIG_DATA, 0x0C},
	{SMART_CONFIG_DATA, 0x38},
	{SMART_CONFIG_DATA, 0x3a},
	{SMART_CONFIG_DATA, 0x0F},

	{SMART_CONFIG_UDELAY, 5},
	{SMART_CONFIG_CMD,  0x11},	   //Exit Sleep
	{SMART_CONFIG_UDELAY, 12},
	{SMART_CONFIG_CMD,  0x29},	   //Display

	// Write the display data into GRAM here
	{SMART_CONFIG_CMD,  0x2A},
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0xEF},

	{SMART_CONFIG_CMD,  0x2B},
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0x00},
	{SMART_CONFIG_DATA, 0x01},
	{SMART_CONFIG_DATA, 0x3F},

//	 {SMART_CONFIG_CMD,  0x2C}, //GRAM start writing

	/* set window */
    {SMART_CONFIG_CMD,  0x2a},
    {SMART_CONFIG_DATA, 0>>8},
    {SMART_CONFIG_DATA, 0&0xFF},
    {SMART_CONFIG_DATA, 320>>8},
    {SMART_CONFIG_DATA, 320&0xFF},

    {SMART_CONFIG_CMD,  0x2b},
    {SMART_CONFIG_DATA, 0>>8},
    {SMART_CONFIG_DATA, 0&0xFF},
    {SMART_CONFIG_DATA, 240>>8},
    {SMART_CONFIG_DATA, 240&0xFF},

    {SMART_CONFIG_CMD,  0X2C}, //GRAM start writing
};

const struct slcd_configure _ili9341_config = 
{
    .reg_write_twice   = 0,
    .rsply_cmd_high    = 0,
    .csply_active_high = 0,
    /* write graphic ram command, in word, for example 8-bit bus, write_gram_cmd=C3C2C1C0. */
    .newcfg_fmt_conv   = 1,

    .width      = 320,
    .height     = 240,

    .bpp        = 16,
    .bus_width  = 8,

	.data_table_num     = sizeof(_ili9341_data_table)/sizeof(_ili9341_data_table[0]),
	.data_table         = &_ili9341_data_table[0],

    .cmd_table          = &_ili9341_cmd_table[0],
    .cmd_table_num      = sizeof(_ili9341_cmd_table)/sizeof(_ili9341_cmd_table[0]),
};

void ili9341_bl_set(rt_bool_t isPwrON)
{
    if(isPwrON)
        gpio_set_value(GPIO_PORT_B, GPIO_Pin_10, 1);
    else
        gpio_set_value(GPIO_PORT_B, GPIO_Pin_10, 0);
}


int ili9341_init(void)
{
	/* enable backlight */
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_12, GPIO_OUTPUT0); //LCD Light

    /* Reset LCD Driver */
    gpio_set_func(GPIO_PORT_B, GPIO_Pin_10, GPIO_OUTPUT0);
    rt_thread_delay(20);
    gpio_set_value(GPIO_PORT_B, GPIO_Pin_10, 1);
    rt_thread_delay(20);
    rt_hw_slcd_init((struct slcd_configure *)&_ili9341_config);
//	rt_hw_lcd_set_bl_func(ili9341_bl_set);
    return 0;
}

#include <finsh.h>
int bl(int argc, char** argv)
{
	int enable = 0;

	if (argc != 2) return 0;

	enable = atoi(argv[1]);

    if (enable)
    {
        rt_kprintf("turn on blight\n");
        gpio_set_value(GPIO_PORT_B, GPIO_Pin_12, 1);
    }
    else
    {
        rt_kprintf("turn off blight\n");
        gpio_set_value(GPIO_PORT_B, GPIO_Pin_12, 0);
    }

	return 0;
}
MSH_CMD_EXPORT(bl, black light);

#endif  //RT_USING_ILI9341

