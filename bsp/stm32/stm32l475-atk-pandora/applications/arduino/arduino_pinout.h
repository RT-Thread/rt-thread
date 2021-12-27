/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 */
#ifndef __UNO_PINOUT_H__
#define __UNO_PINOUT_H__

#define LED_BUILTIN  13 /* Built-in LED */

#define ARDUINO_PWM_HZ 500 /* Arduino UNO's PWM is around 500Hz */

#define ARDUINO_PINOUT_PIN_MAX  20 /* Arduino UNO has 20 pins in total*/
#define ARDUINO_PINOUT_ADC_MAX  6  /* Arduino UNO has 6 ADC pins */
#define ARDUINO_PINOUT_PWM_MAX  5  /* Arduino UNO has 5 PWM pins */

#define A0   (14)
#define A1   (15)
#define A2   (16)
#define A3   (17)
#define A4   (18)
#define A5   (19)

#endif /* __UNO_PINOUT_H__ */
