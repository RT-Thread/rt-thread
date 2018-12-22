/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

#include <MK64F12.h>
#include "led.h"

const rt_uint32_t led_mask[] = {1 << 21, 1 << 22, 1 << 26};

void rt_hw_led_init(void)
{
    SIM->SCGC5 |= (1 << SIM_SCGC5_PORTB_SHIFT);
    SIM->SCGC5 |= (1 << SIM_SCGC5_PORTE_SHIFT);

    PORTB->PCR[21] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[21] |= PORT_PCR_MUX(1);   //PTB21 is GPIO pin

    PORTB->PCR[22] &= ~PORT_PCR_MUX_MASK;
    PORTB->PCR[22] |= PORT_PCR_MUX(1);  //PTB22 is GPIO pin

    PORTE->PCR[26] &= ~PORT_PCR_MUX_MASK;
    PORTE->PCR[26] |= PORT_PCR_MUX(1);  //PTE26 is GPIO pin

    /* Switch LEDs off and enable output*/
    PTB->PDDR |= GPIO_PDDR_PDD(led_mask[1] | led_mask[0]);
    PTE->PDDR |= GPIO_PDDR_PDD(led_mask[2]);

    rt_hw_led_off(LED_RED);
    rt_hw_led_off(LED_GREEN);
    rt_hw_led_off(LED_BLUE);
}

void rt_hw_led_uninit(void)
{
    PORTB->PCR[21] &= ~PORT_PCR_MUX_MASK;

    PORTB->PCR[22] &= ~PORT_PCR_MUX_MASK;

    PORTE->PCR[26] &= ~PORT_PCR_MUX_MASK;
}

void rt_hw_led_on(rt_uint32_t n)
{
    if (n != LED_GREEN)
    {
        PTB->PCOR |= led_mask[n];
    }
    else
    {
        PTE->PCOR |= led_mask[n];
    }
}

void rt_hw_led_off(rt_uint32_t n)
{
    if (n != LED_GREEN)
    {
        PTB->PSOR |= led_mask[n];
    }
    else
    {
        PTE->PSOR |= led_mask[n];
    }
}
