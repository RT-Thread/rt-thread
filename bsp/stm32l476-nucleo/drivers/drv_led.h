/*
 * File      : drv_led.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2012, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author        Notes
 * 2012-10-07     yiyue.fang    modified from LED driver code for Energy Micro 
 *                              EFM32_G8xx_STK starter kit
 */

#ifndef __DRV_LED_H__
#define __DRV_LED_H__

#ifdef __cplusplus
extern "C" {
#endif

void led_init(void);
void led_set(int led);
int  led_get(int led);
void led_clear(int led);
void led_toggle(int led);
void led_value(int value);
void led_deinit(void);

#ifdef __cplusplus
}
#endif

#endif
