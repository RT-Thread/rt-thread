/*
 * Copyright (C) 2021, lizhengyang
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2021-09-02      lizhengyang     first version
 */
#include "board.h"
#include <rtthread.h>
#include <rtdevice.h>


/* defined the LED1 pin: PE0 */
#define LED1_PIN                 GET_PIN(E,0)
/* defined the LED2 pin: PE0 */
#define LED2_PIN                 GET_PIN(E,1)
/* defined the KEY pin: PE13 */
#define KEY_PIN                 GET_PIN(E,13)

#define DELAY_MS                (RT_TICK_PER_SECOND)    /* 1s */

void LED2_Toggle(void *args)
{
    static uint8_t i;
    if (i % 2 == 1)
    {
        rt_pin_write(LED2_PIN, PIN_HIGH);
    }
    else
    {
        rt_pin_write(LED2_PIN, PIN_LOW);
    }
    i++;
}

int32_t main(void)
{
    /* set LED1_PIN  output*/
    rt_pin_mode(LED1_PIN, PIN_MODE_OUTPUT);
    /* set LED2_PIN  output*/
    rt_pin_mode(LED2_PIN, PIN_MODE_OUTPUT);
    /*set KEY_PIN intput pullup*/
    rt_pin_mode(KEY_PIN, PIN_MODE_INPUT_PULLUP);
    /*attach KEY_PIN irq*/
    rt_pin_attach_irq(KEY_PIN, PIN_IRQ_MODE_FALLING, LED2_Toggle, RT_NULL);
    /*enable KEY_PIN irq*/
    rt_pin_irq_enable(KEY_PIN, PIN_IRQ_ENABLE);


    rt_pin_write(LED1_PIN, PIN_HIGH);
    while (1)
    {
        rt_pin_write(LED1_PIN, PIN_HIGH);
        rt_thread_delay(DELAY_MS);
        rt_pin_write(LED1_PIN, PIN_LOW);
        rt_thread_delay(DELAY_MS);
    }
}

