/*
 * File      : board.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009 - 2011 RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-02-24     Bernard      first implementation
 */

#include <rthw.h>
#include <rtthread.h>

#include "board.h"
#include <mb9bf506r.h>
#include <core_cm3.h>

extern const uint32_t SystemFrequency;

/**
 * @addtogroup FM3
 */

/*@{*/

/**
 * This is the timer interrupt service routine.
 *
 */
void rt_hw_timer_handler(void)
{
	/* enter interrupt */
	rt_interrupt_enter();

	rt_tick_increase();

	/* leave interrupt */
	rt_interrupt_leave();
}

void led_init(void)
{
    /*Select CPIO function*/
    LED_PFR &= ~LED_MASK;
    /*Set Pin to turn off leds*/
    LED_PDOR |= LED_MASK;
    /*Make led pins outputs*/
    LED_DDR |= LED_MASK;
}

void rt_hw_led_on(int n)
{
    switch(n)
    {
        case LED1:
            LED_PDOR &= ~LED1;
        break;
        case LED2:
            LED_PDOR &= ~LED2;
        break;
        case LED3:
            LED_PDOR &= ~LED3;        
        break;
        default:
        break;
    }
}

void rt_hw_led_off(int n)
{
    switch(n)
    {
        case LED1:
            LED_PDOR |= LED1;
        break;
        case LED2:
            LED_PDOR |= LED2;
        break;
        case LED3:
            LED_PDOR |= LED3;        
        break;
        default:
        break;
    }
}

/**
* This function will initial FM3 Easy Kit board.
 */
void rt_hw_board_init()
{
    led_init();
    /* init systick */
    SysTick_Config(SystemFrequency/RT_TICK_PER_SECOND - 1);
}

/*@}*/
