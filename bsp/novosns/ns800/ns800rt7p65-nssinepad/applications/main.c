/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author           Notes
 * 2026-05-06     Jiawei.Deng      first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <board.h>

/* defined the LED1 pin: GPIO_68 = PC4 */
#define LED1_PIN    PIN_NUM(GPIO_68)
#define LED2_PIN    PIN_NUM(GPIO_69)
#define KEY1_PIN    PIN_NUM(GPIO_41)

void keydown(void *args)
{
    rt_kprintf("KEY1 Press Down!\n");
    rt_pin_write(LED2_PIN, !rt_pin_read(LED2_PIN));
}


int main(void)
{
		rt_base_t level;
		level = rt_hw_interrupt_disable();
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
		rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
	
	  /* 按键1引脚为输入模式 */
    rt_pin_mode(KEY1_PIN, PIN_MODE_INPUT_PULLUP);
    /* 绑定中断，下降沿模式，回调函数名为keydown */
    if(rt_pin_attach_irq(KEY1_PIN, PIN_IRQ_MODE_FALLING, keydown, RT_NULL)	==	RT_EOK)
		{
			rt_kprintf("bangding chenggong!\n");
		}
    /* 使能中断 */
    if(rt_pin_irq_enable(KEY1_PIN, PIN_IRQ_ENABLE)==	RT_EOK)
		{
			rt_kprintf("shineng chenggong!\n");
		}
  
    rt_hw_interrupt_enable(level);
    while (1)
    {
/*        rt_kprintf("\r\n led1_thread_entry running! \r\n"); */
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_mdelay(1000);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_mdelay(1000);

    }
}

