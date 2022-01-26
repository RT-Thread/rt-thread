/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-03-03     lgnq
 */

#ifndef __LED_H__
#define __LED_H__

#include "mb9bf506r.h"

#define LEDS_MAX_NUMBER         4

/* LED */
#define USER_LED1      (1UL<<0x9)
#define USER_LED2      (1UL<<0xa)
#define USER_LED3      (1UL<<0xb)

#define USER_LED_MASK       (USER_LED1 | USER_LED2 | USER_LED3)
#define USER_LED_PFR            FM3_GPIO->PFR1
#define USER_LED_PCR            FM3_GPIO->PCR1
#define USER_LED_PDOR           FM3_GPIO->PDOR1
#define USER_LED_DDR            FM3_GPIO->DDR1

#define RT_DEVICE_CTRL_LED_ON           0
#define RT_DEVICE_CTRL_LED_OFF          1
#define RT_DEVICE_CTRL_LED_TOGGLE       2

void rt_hw_led_init(void);
void rt_hw_led_on(rt_uint8_t num);
void rt_hw_led_off(rt_uint8_t num);
void rt_hw_led_toggle(rt_uint8_t num);
void pwm_update(rt_uint16_t value);

#endif
