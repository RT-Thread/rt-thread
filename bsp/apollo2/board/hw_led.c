/*
 * File      : hw_led.c
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

#include <rtthread.h>
#include "am_mcu_apollo.h"
#include "hw_led.h"

#define AM_GPIO_LED0                46
#define AM_GPIO_LED1                47
#define AM_GPIO_LED2                48
#define AM_GPIO_LED3                49

#define AM_NUM_LEDS             4

rt_hw_led_t am_psLEDs[AM_NUM_LEDS] =
{
    {AM_GPIO_LED0, AM_LED_ON_LOW | AM_LED_POL_DIRECT_DRIVE_M},
    {AM_GPIO_LED1, AM_LED_ON_LOW | AM_LED_POL_DIRECT_DRIVE_M},
    {AM_GPIO_LED2, AM_LED_ON_LOW | AM_LED_POL_DIRECT_DRIVE_M},
    {AM_GPIO_LED3, AM_LED_ON_LOW | AM_LED_POL_DIRECT_DRIVE_M},
};

/**
 * @brief Configures the necessary pins for an array of LEDs
 *
 * @param LEDNum is the LED number.
 *
 * This function configures a GPIO to drive an LED in a low-power way.
 *
 * @return None.
 */
void rt_hw_led_init(rt_uint32_t LEDNum)
{
		rt_hw_led_t *psLED = am_psLEDs + LEDNum;
	
    /* Handle Direct Drive Versus 3-State (with pull-up or no buffer) */
    if ( AM_LED_POL_DIRECT_DRIVE_M & psLED->Polarity )
    {
        /* Configure the pin as a push-pull GPIO output */
        am_hal_gpio_pin_config(psLED->GPIONumber, AM_HAL_GPIO_OUTPUT);

        /* Enable the output driver, and set the output value to the LEDs "ON" state */
        am_hal_gpio_out_enable_bit_set(psLED->GPIONumber);
        am_hal_gpio_out_bit_replace(psLED->GPIONumber,
                                    psLED->Polarity &
                                    AM_LED_POL_DIRECT_DRIVE_M);
    }
    else
    {
        /* Configure the pin as a tri-state GPIO */
        am_hal_gpio_pin_config(psLED->GPIONumber, AM_HAL_GPIO_3STATE);

        /* Disable the output driver, and set the output value to the LEDs "ON" state */
        am_hal_gpio_out_enable_bit_clear(psLED->GPIONumber);
        am_hal_gpio_out_bit_replace(psLED->GPIONumber,
                                    psLED->Polarity &
                                    AM_LED_POL_DIRECT_DRIVE_M );
    }
}

/**
 * @brief Configures the necessary pins for an array of LEDs
 *
 * @param NumLEDs is the total number of LEDs in the array.
 *
 * This function configures the GPIOs for an array of LEDs.
 *
 * @return None.
 */
void rt_hw_led_array_init(rt_uint32_t NumLEDs)
{
    /* Loop through the list of LEDs, configuring each one individually */
    for ( int i = 0; i < NumLEDs; i++ )
    {
        rt_hw_led_init(i);
    }
}

/**
 * @brief Disables an array of LEDs
 *
 * @param NumLEDs is the total number of LEDs in the array.
 *
 * This function disables the GPIOs for an array of LEDs.
 *
 * @return None.
 */
void rt_hw_led_array_disable(rt_uint32_t NumLEDs)
{
		rt_hw_led_t *psLEDs = am_psLEDs;
	
    /* Loop through the list of LEDs, configuring each one individually */
    for ( int i = 0; i < NumLEDs; i++ )
    {
        am_hal_gpio_pin_config((psLEDs + i)->GPIONumber, AM_HAL_GPIO_DISABLE);
    }
}

/**
 * @brief Turns on the requested LED.
 *
 * @param LEDNum is the LED number for the light to turn on.
 *
 * This function turns on a single LED.
 *
 * @return None.
 */
void rt_hw_led_on(rt_uint32_t LEDNum)
{
		rt_hw_led_t *psLEDs = am_psLEDs;
	
    /* Handle Direct Drive Versus 3-State (with pull-up or no buffer) */
    if ( AM_LED_POL_DIRECT_DRIVE_M & psLEDs[LEDNum].Polarity )
    {
        /* Set the output to the correct state for the LED */
        am_hal_gpio_out_bit_replace(psLEDs[LEDNum].GPIONumber,
                                    psLEDs[LEDNum].Polarity &
                                    AM_LED_POL_POLARITY_M );
    }
    else
    {
        /* Turn on the output driver for the LED */
        am_hal_gpio_out_enable_bit_set(psLEDs[LEDNum].GPIONumber);
    }
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
void rt_hw_led_off(rt_uint32_t LEDNum)
{
		rt_hw_led_t *psLEDs = am_psLEDs;

    /* Handle Direct Drive Versus 3-State (with pull-up or no buffer) */
    if ( AM_LED_POL_DIRECT_DRIVE_M & psLEDs[LEDNum].Polarity )
    {
        /* Set the output to the correct state for the LED */
        am_hal_gpio_out_bit_replace(psLEDs[LEDNum].GPIONumber,
                                    !(psLEDs[LEDNum].Polarity &
                                      AM_LED_POL_POLARITY_M) );
    }
    else
    {
        /* Turn off the output driver for the LED */
        am_hal_gpio_out_enable_bit_clear(psLEDs[LEDNum].GPIONumber);
    }
}

/**
 * @brief Toggles the requested LED.
 *
 * @param LEDNum is the LED number for the light to toggle.
 *
 * This function toggles a single LED.
 *
 * @return None.
 */
void rt_hw_led_toggle(rt_uint32_t LEDNum)
{
		rt_hw_led_t *psLEDs = am_psLEDs;

    /* Handle Direct Drive Versus 3-State (with pull-up or no buffer) */
    if ( AM_LED_POL_DIRECT_DRIVE_M & psLEDs[LEDNum].Polarity )
    {
        am_hal_gpio_out_bit_toggle(psLEDs[LEDNum].GPIONumber);
    }
    else
    {
        /* Check to see if the LED pin is enabled */
        if ( am_hal_gpio_out_enable_bit_get(psLEDs[LEDNum].GPIONumber) )
        {
            /* If it was enabled, turn if off */
            am_hal_gpio_out_enable_bit_clear(psLEDs[LEDNum].GPIONumber);
        }
        else
        {
            /* If it was not enabled, turn if on */
            am_hal_gpio_out_enable_bit_set(psLEDs[LEDNum].GPIONumber);
        }
    }
}

/**
 * @brief Gets the state of the requested LED.
 *
 * @param LEDNum is the LED to check.
 *
 * This function checks the state of a single LED.
 *
 * @return 1(true) if the LED is on.
 */
int rt_hw_led_get(rt_uint32_t LEDNum)
{
		rt_hw_led_t *psLEDs = am_psLEDs;

    /* Handle Direct Drive Versus 3-State (with pull-up or no buffer) */
    if ( AM_LED_POL_DIRECT_DRIVE_M & psLEDs[LEDNum].Polarity )
    {
        /* Mask to the GPIO bit position for this GPIO number */
        uint64_t ui64Mask = 0x01l << psLEDs[LEDNum].GPIONumber;

        /* Extract the state of this bit and return it */
        return !!(am_hal_gpio_input_read() & ui64Mask);
    }
    else
    {
        return am_hal_gpio_out_enable_bit_get(
                    psLEDs[LEDNum].GPIONumber);
    }
}

/**
 * @brief Display a binary value using LEDs.
 *
 * @param NumLEDs is the number of LEDs in the array.
 * @param Value is the value to display on the LEDs.
 *
 * This function displays a value in binary across an array of LEDs.
 *
 * @return None.
 */
void rt_hw_led_array_out(rt_uint32_t NumLEDs, rt_uint32_t Value)
{
    for ( int i = 0; i < NumLEDs; i++ )
    {
        if ( Value & (1 << i) )
        {
            rt_hw_led_on(i);
        }
        else
        {
            rt_hw_led_off(i);
        }
    }
}

#ifdef RT_USING_FINSH
#include <finsh.h>
static rt_uint8_t led_inited = 0;
void led(rt_uint32_t led, rt_uint32_t value)
{
    /* init led configuration if it's not inited. */
    if (!led_inited)
    {
//        rt_hw_led_init(0);
//				rt_hw_led_init(1);
        led_inited = 1;
    }

    if ( led == 0 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            rt_hw_led_off(0);
            break;
        case 1:
            rt_hw_led_on(0);
            break;
        default:
            break;
        }
    }

    if ( led == 1 )
    {
        /* set led status */
        switch (value)
        {
        case 0:
            rt_hw_led_off(1);
            break;
        case 1:
            rt_hw_led_on(1);
            break;
        default:
            break;
        }
    }
}
FINSH_FUNCTION_EXPORT(led, set led[0 - 1] on[1] or off[0].)
#endif

/*@}*/
