/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 */
#ifndef Pins_Arduino_h
#define Pins_Arduino_h

/* pins alias. Must keep in sequence */
#define D0   (0)
#define D1   (1)
#define D2   (2)
#define D3   (3)
#define D4   (4)
#define D5   (5)
#define D6   (6)
#define D7   (7)
#define D8   (8)
#define D9   (9)
#define D10  (10)
#define D11  (11)
#define D12  (12)
#define D13  (13)
#define D14  (14)
#define D15  (15)
#define A0   (16)
#define A1   (17)
#define A2   (18)
#define A3   (19)
#define A4   (20)
#define A5   (21)

#define LED_BUILTIN  D13 /* Built-in LED */

#define ARDUINO_PWM_HZ 500 /* Arduino UNO's PWM is around 500Hz */

#define ARDUINO_DEFAULT_IIC_BUS_NAME "i2c4"

#endif /* Pins_Arduino_h */
