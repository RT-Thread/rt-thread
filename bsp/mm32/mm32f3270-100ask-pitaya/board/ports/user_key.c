/*
 * Copyright (c) 2006-2022, 100ask Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author                Notes
 * 2022-06-06      Alen      Add key code for 100ask f103 mini
 */

#include <rtthread.h>
#include <drv_gpio.h>

#ifdef BSP_USING_USER_KEY
#define KEY         GET_PIN(A, 0)
static void KEY_IRQHandler(void *args)
{
    rt_kprintf("Key Status: ");
    if(rt_pin_read(KEY) == 0)
    {
        rt_kprintf("pressed.\r\n");
    }
    else
    {
        rt_kprintf("released.\r\n");
    }
}


static int rt_hw_user_key_init(void)
{
    rt_pin_mode(KEY, PIN_IRQ_MODE_RISING_FALLING);
    rt_pin_attach_irq(KEY, PIN_IRQ_MODE_RISING_FALLING, KEY_IRQHandler, RT_NULL);
    rt_pin_irq_enable(KEY, RT_TRUE);

    return RT_EOK;
}

INIT_COMPONENT_EXPORT(rt_hw_user_key_init);
#endif


