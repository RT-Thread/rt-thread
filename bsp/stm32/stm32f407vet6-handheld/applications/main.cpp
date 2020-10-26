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

#include "board_config.h"

#ifdef __cplusplus
extern   "C"
{
#endif

int main(void)
{
    int count = 1;
	rt_kprintf("hello_oled!/s");
	/* turn on the OLED 13.5V Power */
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
