/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-14     Haley        the first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include "board.h"

#define AM_GPIO_LED0                46
#define AM_GPIO_LED1                47
#define AM_GPIO_LED2                48
#define AM_GPIO_LED3                49

/**
 * @brief Turns on the requested LED.
 *
 * @param LEDNum is the LED number for the light to turn on.
 *
 * This function turns on a single LED.
 *
 * @return None.
 */
void rt_hw_led_on(rt_uint8_t LEDNum)
{
#ifdef RT_USING_PIN
    if(LEDNum == 0)
        rt_pin_write(AM_GPIO_LED0, PIN_LOW);

    else if(LEDNum == 1)
        rt_pin_write(AM_GPIO_LED1, PIN_LOW);

    else if(LEDNum == 2)
        rt_pin_write(AM_GPIO_LED2, PIN_LOW);

    else if(LEDNum == 3)
        rt_pin_write(AM_GPIO_LED3, PIN_LOW);
#endif
}

/**
 * @brief Turns off the requested LED.
 *
 * @param LEDNum is the LED number for the light to turn off.
 *
 * This function turns off a single LED.
 *
 * @return None.
 */
void rt_hw_led_off(rt_uint8_t LEDNum)
{
#ifdef RT_USING_PIN
    if(LEDNum == 0)
        rt_pin_write(AM_GPIO_LED0, PIN_HIGH);

    else if(LEDNum == 1)
        rt_pin_write(AM_GPIO_LED1, PIN_HIGH);

    else if(LEDNum == 2)
        rt_pin_write(AM_GPIO_LED2, PIN_HIGH);

    else if(LEDNum == 3)
        rt_pin_write(AM_GPIO_LED3, PIN_HIGH);
#endif
}

/**
 * @brief Configures the necessary pins for an array of LEDs
 *
 * @param None.
 *
 * This function configures a GPIO to drive an LED in a low-power way.
 *
 * @return None.
 */
int rt_hw_led_init(void)
{
#ifdef RT_USING_PIN
#if defined(RT_USING_LED0)
    /* config led */
    rt_pin_mode(AM_GPIO_LED0, PIN_MODE_OUTPUT);

    /* turns off the led */
    rt_hw_led_off(0);
#endif /* RT_USING_LED0 */

#if defined(RT_USING_LED1)
    /* config led */
    rt_pin_mode(AM_GPIO_LED1, PIN_MODE_OUTPUT);

    /* turns off the led */
    rt_hw_led_off(1);
#endif /* RT_USING_LED1 */

#if defined(RT_USING_LED2)
    /* config led */
    rt_pin_mode(AM_GPIO_LED2, PIN_MODE_OUTPUT);

    /* turns off the led */
    rt_hw_led_off(2);
#endif /* RT_USING_LED0 */

#if defined(RT_USING_LED3)
    /* config led */
    rt_pin_mode(AM_GPIO_LED3, PIN_MODE_OUTPUT);

    /* turns off the led */
    rt_hw_led_off(3);
#endif /* RT_USING_LED1 */
#endif

    rt_kprintf("led_init!\n");

    return 0;
}
#ifdef RT_USING_COMPONENTS_INIT
INIT_DEVICE_EXPORT(rt_hw_led_init);
#endif

#ifdef RT_USING_FINSH
#include <finsh.h>

void led(rt_uint32_t led, rt_uint32_t state)
{
    /* set led status */
    switch (state)
    {
    case 0:
        rt_hw_led_off(led);
        break;
    case 1:
        rt_hw_led_on(led);
        break;
    default:
        break;
    }
}
FINSH_FUNCTION_EXPORT(led, turn led (0 - 3) on (1) or off (0).)
#endif

/*@}*/
