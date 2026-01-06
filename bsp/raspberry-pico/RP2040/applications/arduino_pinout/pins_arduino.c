/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-25     ShichengChu  first version
 */

#include <Arduino.h>
#include <board.h>
#include "pins_arduino.h"
#include <pico/stdlib.h>
#include <hardware/spi.h>
#include <hardware/gpio.h>
#include <pico/binary_info.h>

#define DBG_TAG    "RTduino.pins_arduino"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

/*
 * {Arduino Pin, RT-Thread Pin [, Device Name, Channel]}
 * [] means optional
 * Digital pins must NOT give the device name and channel.
 * Analog pins MUST give the device name and channel(ADC, PWM or DAC).
 * Arduino Pin must keep in sequence.
 */
const pin_map_t pin_map_table[]=
{
    {D0, 0, "uart0"},                                  /* Serial-TX */
    {D1, 1, "uart0"},                                  /* Serial-RX */
    {D2, 2},
    {D3, 3},
    {D4, 4, "i2c0"},                                   /* I2C-SDA (Wire) */
    {D5, 5, "i2c0"},                                   /* I2C-SCL (Wire) */
    {D6, 6},
    {D7, 7},
    {D8, 8, "uart1"},                                  /* Serial2-TX */
    {D9, 9, "uart1"},                                  /* Serial2-RX */
    {D10, 10, "pwm5", 0},                              /* PWM */
    {D11, 11, "pwm5", 1},                              /* PWM */
    {D12, 12, "pwm6", 0},                              /* PWM */
    {D13, 13, "pwm6", 1},                              /* PWM */
    {D14, 14, "pwm7", 0},                              /* PWM */
    {D15, 15, "pwm7", 1},                              /* PWM */
    {D16, 16, "pwm0", 0},                              /* PWM */
    {D17, 17, "pwm0", 1},                              /* PWM */
    {D18, 18, "pwm1", 0},                              /* PWM */
    {D19, 19, "pwm1", 1},                              /* PWM */
    {D20, 20, "pwm2", 0},                              /* PWM */
    {D21, 21, "pwm2", 1},                              /* PWM */
    {D22, 22, "pwm3", 0},                              /* PWM */
    {D23, 23, "pwm3", 1},                              /* PWM */
    {D24, 24, "pwm4", 0},                              /* PWM */
    {D25, 25, "pwm4", 1},                              /* LED_BUILTIN */
    {A0, 26, "adc0", 0},                               /* ADC */
    {A1, 27, "adc1", 1},                               /* ADC */
    {A2, 28, "adc2", 2},                               /* ADC */
};

#ifdef RTDUINO_USING_SPI
void switchToSPI(const char *bus_name)
{
    if(!rt_strcmp(bus_name, "spi0"))
    {
        /**SPI0 GPIO Configuration
        18u     ------> SPI0_SCK
        16u     ------> SPI0_MISO
        19u     ------> SPI0_MOSI
        17u     ------> SPI0_CS
        */
        gpio_set_function(BSP_SPI0_SCK_PIN, GPIO_FUNC_SPI);
        gpio_set_function(BSP_SPI0_MISO_PIN, GPIO_FUNC_SPI);
        gpio_set_function(BSP_SPI0_MOSI_PIN, GPIO_FUNC_SPI);
        gpio_init(BSP_SPI0_CS_PIN);
        // Make the SPI pins available to picotool
        bi_decl(bi_3pins_with_func(BSP_SPI0_MISO_PIN, BSP_SPI0_MOSI_PIN, BSP_SPI0_SCK_PIN, GPIO_FUNC_SPI));
        // Make the CS pin available to picotool
        bi_decl(bi_1pin_with_name(BSP_SPI0_CS_PIN, "SPI CS"));

        LOG_I("D16, D17, D18 and D19 will switch from PWM to SPI");
    }
}
#endif /* RTDUINO_USING_SPI */
