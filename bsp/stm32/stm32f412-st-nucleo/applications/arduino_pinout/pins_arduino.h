/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-21     Meco Man     first version
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
#define D18       (18)
#define D19       (19)
#define A0        (20)
#define A1        (21)
#define A2        (22)
#define A3        (23)
#define A4        (24)
#define A5        (25)
#define A6        (26)
#define A7        (27)

#define RTDUINO_PIN_MAX_LIMIT A7 /* pin number max limit check */

#define F_CPU          96000000L  /* CPU:96MHz */

#define LED_BUILTIN     D17  /* Default Built-in LED */

/* i2c1 : PB9-SDA PB8-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c1"

#define SS          D10
#define RTDUINO_DEFAULT_SPI_BUS_NAME    "spi1"

#define RTDUINO_TONE_HWTIMER_DEVICE_NAME "timer6"

#endif /* Pins_Arduino_h */
