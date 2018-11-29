/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-07-29     Arda.Fu      first implementation
 */
#include <rtthread.h>

#include <rtdevice.h>

#include "board.h"
#include "LPC54114_cm4.h"

int led(void);

int main(void)
{
    /* user app entry */
    
    return 0;
}


#define LED_PIN  30   //ld4
#define KEY_PIN  40  //PB2
#define KEY_PIN1  41  //PB3
#define KEY_PIN2  42  //PB4
#define KEY_PIN3  43  //PB5

static void thread1_entry(void *parameter)
{
    rt_pin_mode(LED_PIN, PIN_MODE_OUTPUT);
     while (1)
    {
        rt_kprintf("led on \n");
        rt_pin_write(LED_PIN, 0);
        rt_thread_delay(1000);
        
        rt_kprintf("led off \n");
        rt_pin_write(LED_PIN, 1);
        rt_thread_delay(1000);
    }
}

static void thread2_entry(void *parameter)
{
    
    int val;
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLUP);

     while (1)
    {        
        val = rt_pin_read(KEY_PIN);
        rt_kprintf("read key pin_val = %d\n", val);
        rt_thread_delay(1000);
    }
}

static void callback(void *parameter)
{        
    rt_kprintf("irq callback is ok \n");
}

static void callbacktestdetach(void *parameter)
{      
    rt_uint32_t value;
    value = (rt_uint32_t)parameter;   
    
    rt_kprintf("irq callback is ok 111111, para = %d\n" , value);
    
    //rt_pin_irq_enable(KEY_PIN1, 0);
    rt_pin_detach_irq(KEY_PIN1);
}

static void thread3_entry(void *parameter)
{
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_PIN, PIN_IRQ_MODE_FALLING, callback, RT_NULL);
    rt_pin_irq_enable(KEY_PIN, 1);
}

static void thread31_entry(void *parameter)
{
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_PIN, PIN_IRQ_MODE_FALLING, callback, RT_NULL);
    rt_pin_irq_enable(KEY_PIN, 1);
    
    rt_pin_mode(KEY_PIN1, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_PIN1, PIN_IRQ_MODE_FALLING, callbacktestdetach, (void*)1);
    rt_pin_irq_enable(KEY_PIN1, 1);
    
        rt_pin_mode(KEY_PIN2, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_PIN2, PIN_IRQ_MODE_FALLING, callback, RT_NULL);
    rt_pin_irq_enable(KEY_PIN2, 1);
    
        rt_pin_mode(KEY_PIN3, PIN_MODE_INPUT_PULLUP);
    rt_pin_attach_irq(KEY_PIN3, PIN_IRQ_MODE_FALLING, callback, RT_NULL);
    rt_pin_irq_enable(KEY_PIN3, 1);
}

int led(void)
{
    rt_thread_t tid1;
    
    tid1 = rt_thread_create("t1",
                            thread2_entry,
                            RT_NULL,
                            512,
                            25,
                            20);
    
    if(tid1 != RT_NULL)
        rt_thread_startup(tid1);

    return 0;
}
MSH_CMD_EXPORT(led, led sample);
//INIT_APP_EXPORT(led);







