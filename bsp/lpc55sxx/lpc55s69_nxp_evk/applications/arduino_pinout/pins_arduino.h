/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-22     ChuShicheng  first version
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
#define D14       (14)
#define D15       (15)
#define D16       (16)
#define D17       (17)
#define A0        (18)
#define A1        (19)
#define A2        (20)
#define A3        (21)

#define F_CPU          150000000L  /* CPU:150MHz */

#define LED_BUILTIN     D6  /* Default Built-in LED */

/* i2c1 : P-SDA P-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c1"

#endif /* Pins_Arduino_h */
