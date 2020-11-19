/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-11-06     SummerGift   first version
 * 2018-11-19     flybreak     add stm32f407-atk-explorer bsp
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>
#include <rtthread.h>
#include "drv_spi.h"
//#include "ban_config.h"


/*
  U8g2lib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.

  This is a frame buffer example.
*/

#ifdef __cplusplus
extern   "C"
{
#endif



int main(void)
{
    int count = 1;
	
		rt_kprintf("test!/s");
	
		rt_kprintf("hello_oled!/s");
	    /* ¿ªÆôOLEDµçÔ´ */
	char buf[]= "hello rt-thread!\r\n";
	
	rt_device_t dev =RT_NULL;
	
	dev =rt_device_find("vcom");
	
	if(dev)
		rt_device_open(dev,RT_DEVICE_FLAG_RDWR);
	else
		return -RT_ERROR;
			rt_kprintf("hello_oled_gui!\r\n");


//	u8g2_full_buffer_u8g2_logo();
    while (1)
    {

        rt_thread_mdelay(500);
			rt_device_write(dev,0,buf,rt_strlen(buf));
			
    }

    return RT_EOK;
}
#ifdef   __cplusplus
}
#endif
// End of main.cpp
