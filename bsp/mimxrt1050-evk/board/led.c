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
 *
 */

#include "fsl_common.h"
#include "fsl_iomuxc.h"
#include "led.h"

const rt_uint32_t led_mask[] = {1u << 9};

void rt_hw_led_init(void)
{
    /* Enable Clock Gate */
    CLOCK_EnableClock(kCLOCK_Gpio1);

    /* Configure Pinmux to GPIO mode */
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO_AD_B0_09_GPIO1_IO09, 0xF1);

    /* Set GPIO Direction */
    GPIO1->GDIR |= (1U << 9); // output mode

    /* Switch LEDs off and enable output*/
    GPIO1->DR &= (uint32_t)~(1U << 9);

    rt_hw_led_off(LED_GREEN);
}

void rt_hw_led_uninit(void)
{
    IOMUXC_SetPinMux(IOMUXC_GPIO_AD_B0_09_JTAG_TDI, 0);
}

void rt_hw_led_on(rt_uint32_t n)
{
    GPIO1->DR |= led_mask[n];
}

void rt_hw_led_off(rt_uint32_t n)
{
    GPIO1->DR &= (uint32_t)~led_mask[n];
}
