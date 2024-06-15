/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-20     default      first version
 */

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

/* pins alias. Must keep in sequence */
#define D0        (0)
#define D1        (1)
#define D2        (2)
#define D3        (3)
#define D4        (4)
#define D5        (5)
#define D6        (6)
#define D7        (7)
#define D8        (8)
#define D9        (9)
#define D10       (10)
#define D11       (11)
#define D12       (12)
#define D13       (13)
#define A0        (14)
#define A1        (15)

#define RTDUINO_PIN_MAX_LIMIT A1 /* pin number max limit check */

#define F_CPU          168000000L  /* CPU:168MHz */

#define LED_BUILTIN     D0  /* Default Built-in LED */

/* i2c1 : PF0-SDA PF1-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c1"

#endif /* Pins_Arduino_h */
