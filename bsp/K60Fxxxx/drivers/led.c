/*
 * File      : led.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2009, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-11     reynolds     port to TWR-K60F120M
 */

#include <MK60F12.H>
#include "led.h"

const rt_uint32_t led_mask[] = { 1 << 11, 1 << 28, 1 << 29, 1 << 10 };

void rt_hw_led_init(void)
{
    SIM->SCGC5    |= (1UL <<  9);         //Enable Port A Clock
    PORTA->PCR[10] = (1UL <<  8);         //PTA10 is GPIO pin  
    PORTA->PCR[11] = (1UL <<  8);         //PTA11 is GPIO pin  
    PORTA->PCR[28] = (1UL <<  8);         //PTA28 is GPIO pin  
    PORTA->PCR[29] = (1UL <<  8);         //PTA29 is GPIO pin  

    /* Switch LEDs off and enable output*/
    PTA->PDOR = (led_mask[3] | led_mask[2] | led_mask[1] | led_mask[0]);
    PTA->PDDR = (led_mask[3] | led_mask[2] | led_mask[1] | led_mask[0]);
}

void rt_hw_led_uninit(void)
{
    PORTA->PCR[10] = 0;                   //PTA10 is at reset state
    PORTA->PCR[11] = 0;                   //PTA11 is at reset state
    PORTA->PCR[28] = 0;                   //PTA28 is at reset state
    PORTA->PCR[29] = 0;                   //PTA29 is at reset state
}

void rt_hw_led_on(rt_uint32_t n)
{
    if (n < LED_MAX)
    {
        PTA->PCOR = led_mask[n];
    }
}


void rt_hw_led_off(rt_uint32_t n)
{
    if (n < LED_MAX) {
        PTA->PSOR = led_mask[n];
    }
}
