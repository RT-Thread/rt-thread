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
#define DK_BOARD_LED_2  14
#define DK_BOARD_LED_3  15
#define DK_BOARD_LED_4  16

#define DK_BOARD_BUTTON_1  11
#define DK_BOARD_BUTTON_2  12
#define DK_BOARD_BUTTON_3  24
#define DK_BOARD_BUTTON_4  25

void button_1_callback(void *args)
{
	static int flag1 = 0;
	if(flag1 == 0)
	{
		flag1 = 1;
		rt_pin_write(DK_BOARD_LED_1, PIN_LOW);
	}
	else
	{
		flag1 = 0;
		rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
	}
}
void button_2_callback(void *args)
{
	static int flag2 = 0;
	if(flag2 == 0)
	{
		flag2 = 1;
		rt_pin_write(DK_BOARD_LED_2, PIN_LOW);
	}
	else
	{
		flag2 = 0;
		rt_pin_write(DK_BOARD_LED_2, PIN_HIGH);
	}
}
void button_3_callback(void *args)
{
	static int flag3 = 0;
	if(flag3 == 0)
	{
		flag3 = 1;
		rt_pin_write(DK_BOARD_LED_3, PIN_LOW);
	}
	else
	{
		flag3 = 0;
		rt_pin_write(DK_BOARD_LED_3, PIN_HIGH);
	}
}
void button_4_callback(void *args)
{
	static int flag4 = 0;
	if(flag4 == 0)
	{
		flag4 = 1;
		rt_pin_write(DK_BOARD_LED_4, PIN_LOW);
	}
	else
	{
		flag4 = 0;
		rt_pin_write(DK_BOARD_LED_4, PIN_HIGH);
	}
}
int main(void)
{
	 
	rt_pin_mode(DK_BOARD_LED_1, PIN_MODE_OUTPUT);
	rt_pin_mode(DK_BOARD_LED_2, PIN_MODE_OUTPUT);
	rt_pin_mode(DK_BOARD_LED_3, PIN_MODE_OUTPUT);
	rt_pin_mode(DK_BOARD_LED_4, PIN_MODE_OUTPUT);

	rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
	rt_pin_write(DK_BOARD_LED_2, PIN_HIGH);
	rt_pin_write(DK_BOARD_LED_3, PIN_HIGH);
	rt_pin_write(DK_BOARD_LED_4, PIN_HIGH);
	
//	rt_pin_mode(DK_BOARD_BUTTON_1, PIN_MODE_INPUT_PULLUP);
//	rt_pin_mode(DK_BOARD_BUTTON_2, PIN_MODE_INPUT_PULLUP);
//	rt_pin_mode(DK_BOARD_BUTTON_3, PIN_MODE_INPUT_PULLUP);
//	rt_pin_mode(DK_BOARD_BUTTON_4, PIN_MODE_INPUT_PULLUP);
	
//    /*试验IO输入输出*/	
//    while (1)
//    {	
//      
//			rt_pin_write(DK_BOARD_LED_3, PIN_HIGH);
//			if(rt_pin_read(DK_BOARD_BUTTON_1))		
//			{	
//				rt_pin_write(DK_BOARD_LED_1, PIN_LOW);
//				rt_thread_mdelay(500);
//			}
//			
//			
//			rt_pin_write(DK_BOARD_LED_1, PIN_HIGH);
//			if(rt_pin_read(DK_BOARD_BUTTON_2))
//			{
//				rt_pin_write(DK_BOARD_LED_2, PIN_LOW);
//				rt_thread_mdelay(500);
//			}
//			
//			
//			rt_pin_write(DK_BOARD_LED_2, PIN_HIGH);
//			if(rt_pin_read(DK_BOARD_BUTTON_4))	
//			{	
//				rt_pin_write(DK_BOARD_LED_4, PIN_LOW);
//				rt_thread_mdelay(500);
//			}
//			

//			rt_pin_write(DK_BOARD_LED_4, PIN_HIGH);
//			if(rt_pin_read(DK_BOARD_BUTTON_3))
//			{				
//				rt_pin_write(DK_BOARD_LED_3, PIN_LOW);
//				rt_thread_mdelay(500);
//			}				
//    }


	/*试验IO中断*/
	rt_err_t err_code;
	
	err_code =  rt_pin_attach_irq(DK_BOARD_BUTTON_1, PIN_IRQ_MODE_FALLING,
                             button_1_callback, (void*) true); //true 为高精度 IN_EVENT,false 为低精度 PORT_EVENT
	rt_pin_irq_enable(DK_BOARD_BUTTON_1, PIN_IRQ_ENABLE);
	
	err_code =  rt_pin_attach_irq(DK_BOARD_BUTTON_2, PIN_IRQ_MODE_FALLING,
                             button_2_callback, (void*) true); //true 为高精度 IN_EVENT,false 为低精度 PORT_EVENT
	rt_pin_irq_enable(DK_BOARD_BUTTON_2, PIN_IRQ_ENABLE);
	
	
	err_code =  rt_pin_attach_irq(DK_BOARD_BUTTON_3, PIN_IRQ_MODE_FALLING,
                             button_3_callback, (void*) true); //true 为高精度 IN_EVENT,false 为低精度 PORT_EVENT
	rt_pin_irq_enable(DK_BOARD_BUTTON_3, PIN_IRQ_ENABLE);
	
	err_code =  rt_pin_attach_irq(DK_BOARD_BUTTON_4, PIN_IRQ_MODE_FALLING,
                             button_4_callback, (void*) false); //true 为高精度 IN_EVENT,false 为低精度 PORT_EVENT
	rt_pin_irq_enable(DK_BOARD_BUTTON_4, PIN_IRQ_ENABLE);
	
	while (1)
	{
		;
	}

  return RT_EOK;
}


/*@}*/
