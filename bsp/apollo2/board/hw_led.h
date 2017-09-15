/*
 * File      : hw_led.h
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2017, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-14     Haley        the first version
 */
 
#ifndef __HW_LED_H
#define __HW_LED_H

#include <rtthread.h>
	
/**
 * @brief LED polarity macros
 *
 */
#define AM_LED_POL_POLARITY_M       0x1
#define AM_LED_ON_HIGH              0x1
#define AM_LED_ON_LOW               0x0

/**
 * @brief LED direct drive indicator macro
 *	Or this in with the polarity value to use the GPIO DATA register instead of
 *	the GPIO DATA ENABLE register to directly drive an LED buffer.
 */
#define AM_LED_POL_DIRECT_DRIVE_M   0x2


/**
 * @brief Structure for keeping track of LEDs
 *
 */
typedef struct
{
    rt_uint32_t GPIONumber;
    rt_uint32_t Polarity;
}
rt_hw_led_t;

/**
 * @brief External function definitions
 *
 */
void rt_hw_led_init(rt_uint32_t LEDNum);
void rt_hw_led_array_init(rt_uint32_t NumLEDs);
void rt_hw_led_array_disable(rt_uint32_t NumLEDs);
void rt_hw_led_on(rt_uint32_t LEDNum);
void rt_hw_led_off(rt_uint32_t LEDNum);
void rt_hw_led_toggle(rt_uint32_t LEDNum);
int rt_hw_led_get(rt_uint32_t LEDNum);
void rt_hw_led_array_out(rt_uint32_t NumLEDs, rt_uint32_t Value);

#endif // __HW_LED_H
