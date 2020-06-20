/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-03-01     Yangfs       the first version
 * 2015-03-27     Bernard      code cleanup.
 */

/**
 * @addtogroup NRF52832
 */
/*@{*/

#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

#include <drv_gpio.h>
#define DK_BOARD_LED_1  13

int main(void)
{
    int count = 1; 
	rt_pin_mode(DK_BOARD_LED_1, PIN_MODE_OUTPUT);
	
	while (count++)
	{	
		rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
		rt_thread_mdelay(500);
		
		rt_pin_write(DK_BOARD_LED_1, PIN_LOW);
		rt_thread_mdelay(500);					
	}
	return RT_EOK;
}

/*@}*/
