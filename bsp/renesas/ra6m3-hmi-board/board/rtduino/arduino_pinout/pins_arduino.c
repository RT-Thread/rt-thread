/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2023-10-28     Wangyuqiang    first version
 */

#include <Arduino.h>
#include "pins_arduino.h"

#include <rtthread.h>
#include "hal_data.h"
#include <rtdevice.h>

/*
 * {Arduino Pin, RT-Thread Pin [, Device Name, Channel]}
 * [] means optional
 * Digital pins must NOT give the device name and channel.
 * Analog pins MUST give the device name and channel(ADC, PWM or DAC).
 * Arduino Pin must keep in sequence.
 */
const pin_map_t pin_map_table[]=
{
    {D0, BSP_IO_PORT_02_PIN_06, "uart4"},                        /* Serial4-RX */
    {D1, BSP_IO_PORT_02_PIN_05, "uart4"},                        /* Serial4-TX */
    {D2, BSP_IO_PORT_00_PIN_08},
    {D3, BSP_IO_PORT_05_PIN_06},
    {D4, BSP_IO_PORT_06_PIN_03},
    {D5, BSP_IO_PORT_06_PIN_04, "pwm8", 0},
    {D6, BSP_IO_PORT_06_PIN_05, "pwm8", 0},
    {D7, BSP_IO_PORT_02_PIN_08},
    {D8, BSP_IO_PORT_02_PIN_07},
    {D9, BSP_IO_PORT_00_PIN_09},
    {D10, BSP_IO_PORT_07_PIN_12, "pwm2", 0},                     /* PWM */
    {D11, BSP_IO_PORT_05_PIN_12, "pwm0", 0},                     /* PWM */
    {D12, BSP_IO_PORT_05_PIN_11},
    {D13, BSP_IO_PORT_02_PIN_04},
    {D14, BSP_IO_PORT_02_PIN_03, "i2c0"},                        /* I2C-SDA (Soft Wire) */
    {D15, BSP_IO_PORT_02_PIN_02, "i2c0"},                        /* I2C-SCL (Soft Wire) */
    {A0, BSP_IO_PORT_00_PIN_00, "adc0", 0},                      /* ADC */
    {A1, BSP_IO_PORT_00_PIN_01, "adc0", 1},                      /* ADC */
    {A2, BSP_IO_PORT_00_PIN_02, "adc0", 2},                      /* ADC */
    {A3, BSP_IO_PORT_00_PIN_03, "adc0", 7},                      /* ADC */
    {A4, BSP_IO_PORT_05_PIN_08, "adc0", 20},                     /* ADC */
    {A5, BSP_IO_PORT_00_PIN_14, "adc0", 5}                       /* ADC */
};
