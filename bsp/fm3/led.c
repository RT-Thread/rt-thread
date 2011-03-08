/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2011, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
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
    
    switch(num)
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

    switch(num)
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
    
    switch(num)
    {
        case 1:
            if(LED_PDOR&LED1)
                LED_PDOR &= ~LED1;
            else
                LED_PDOR |= LED1;
        break;
        case 2:
            if(LED_PDOR&LED2)
                LED_PDOR &= ~LED2;
            else
                LED_PDOR |= LED2;
        break;
        case 3:
            if(LED_PDOR&LED3)
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

    return RT_EOK;
}

static void led1_thread_entry(void *parameter)
{
    while(1)
    {
        rt_hw_led_toggle(1);
        rt_thread_delay(10);
    }
}

static void led2_thread_entry(void *parameter)
{
    while(1)
    {
        rt_hw_led_toggle(2);
        rt_thread_delay(20);
    }
}

static rt_thread_t led1_thread;
static rt_thread_t led2_thread;
void rt_hw_led_init(void)
{
    led_io_init();
    
    led1_thread = rt_thread_create("led1", led1_thread_entry, RT_NULL, 384, 31, 5);
    if(led1_thread != RT_NULL) 
        rt_thread_startup(led1_thread);
    
    led2_thread = rt_thread_create("led2", led2_thread_entry, RT_NULL, 384, 30, 5);
    if(led2_thread != RT_NULL) 
        rt_thread_startup(led2_thread);
}


