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
            USER_LED_PDOR &= ~USER_LED1;
        break;
        case 2:
            USER_LED_PDOR &= ~USER_LED2;
        break;
        case 3:
            USER_LED_PDOR &= ~USER_LED3;
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
            USER_LED_PDOR |= USER_LED1;
        break;
        case 2:
            USER_LED_PDOR |= USER_LED2;
        break;
        case 3:
            USER_LED_PDOR |= USER_LED3;
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
            if (USER_LED_PDOR&USER_LED1)
                USER_LED_PDOR &= ~USER_LED1;
            else
                USER_LED_PDOR |= USER_LED1;
        break;
        case 2:
            if (USER_LED_PDOR&USER_LED2)
                USER_LED_PDOR &= ~USER_LED2;
            else
                USER_LED_PDOR |= USER_LED2;
        break;
        case 3:
            if (USER_LED_PDOR&USER_LED3)
                USER_LED_PDOR &= ~USER_LED3;
            else
                USER_LED_PDOR |= USER_LED3;
        break;
        default:
        break;
    }
}

void led_init(void)
{
    /*Select CPIO function*/
    USER_LED_PFR &= ~USER_LED_MASK;
    /* disable analog input */
    FM3_GPIO->ADE &= ~USER_LED_MASK;
    /*Set CPIO Pull-Up function*/
    USER_LED_PCR |= USER_LED_MASK;
    /*Make led pins outputs*/
    USER_LED_DDR |= USER_LED_MASK;
    USER_LED_PDOR |= USER_LED_MASK;
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
    led_init();

    led1_thread = rt_thread_create("led1", led1_thread_entry, RT_NULL, 384, 29, 5);
    if (led1_thread != RT_NULL)
        rt_thread_startup(led1_thread);

    led2_thread = rt_thread_create("led2", led2_thread_entry, RT_NULL, 384, 30, 5);
    if (led2_thread != RT_NULL)
        rt_thread_startup(led2_thread);
}


