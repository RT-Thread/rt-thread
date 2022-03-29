/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-03     lgnq
 */

#include <rtthread.h>
#include <rthw.h>

#include "mb9bf506r.h"
#include "led.h"

void rt_hw_led_on(rt_uint8_t num)
{
    RT_ASSERT(num < LEDS_MAX_NUMBER);

    switch (num)
    {
        case 1:
            LED_PDOR &= ~LED1;
        break;
        case 2:
            LED_PDOR &= ~LED2;
        break;
        case 3:
            LED_PDOR &= ~LED3;
        break;
        default:
        break;
    }
}

void rt_hw_led_off(rt_uint8_t num)
{
    RT_ASSERT(num < LEDS_MAX_NUMBER);

    switch (num)
    {
        case 1:
            LED_PDOR |= LED1;
        break;
        case 2:
            LED_PDOR |= LED2;
        break;
        case 3:
            LED_PDOR |= LED3;
        break;
        default:
        break;
    }
}

void rt_hw_led_toggle(rt_uint8_t num)
{
    RT_ASSERT(num < LEDS_MAX_NUMBER);

    switch (num)
    {
        case 1:
            if (LED_PDOR&LED1)
                LED_PDOR &= ~LED1;
            else
                LED_PDOR |= LED1;
        break;
        case 2:
            if (LED_PDOR&LED2)
                LED_PDOR &= ~LED2;
            else
                LED_PDOR |= LED2;
        break;
        case 3:
            if (LED_PDOR&LED3)
                LED_PDOR &= ~LED3;
            else
                LED_PDOR |= LED3;
        break;
        default:
        break;
    }
}

static rt_err_t led_io_init(void)
{
    /*Select CPIO function*/
    LED_PFR &= ~LED_MASK;
    /*Set Pin to turn off leds*/
    LED_PDOR |= LED_MASK;
    /*Make led pins outputs*/
    LED_DDR |= LED_MASK;

    //LED3 is controled by PWM
    FM3_GPIO->PFR3 = 0x1000;
    FM3_GPIO->EPFR04 = 0x00080000;
    FM3_BT2_PWM->TMCR = 0x0018;
    FM3_BT2_PWM->TMCR2 = 0x01;          /* cks=0b1000 count clk 1/512 */
    FM3_BT2_PWM->STC = 0x00;
    FM3_BT2_PWM->PCSR  = 0x61A;         /* Down count = 1562 */
    FM3_BT2_PWM->PDUT  = 0x0;           /* Duty count = 16/1562=10% */

    FM3_BT2_PWM->TMCR |= 0x03;          /* start base timer(softwere TRG) */
    return RT_EOK;
}

void pwm_update(rt_uint16_t value)
{
    FM3_BT2_PWM->PDUT  = value;
}

static void led1_thread_entry(void *parameter)
{
    while (1)
    {
        rt_hw_led_toggle(1);
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

static void led2_thread_entry(void *parameter)
{
    while (1)
    {
        rt_hw_led_toggle(2);
        rt_thread_delay(RT_TICK_PER_SECOND/2);
    }
}

static rt_thread_t led1_thread;
static rt_thread_t led2_thread;
void rt_hw_led_init(void)
{
    led_io_init();

    led1_thread = rt_thread_create("led1", led1_thread_entry, RT_NULL, 384, 29, 5);
    if (led1_thread != RT_NULL)
        rt_thread_startup(led1_thread);

    led2_thread = rt_thread_create("led2", led2_thread_entry, RT_NULL, 384, 30, 5);
    if (led2_thread != RT_NULL)
        rt_thread_startup(led2_thread);
}


