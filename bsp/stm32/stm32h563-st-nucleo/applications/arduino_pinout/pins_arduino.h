/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-13     songw4232    first version
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
#define A0        (16)
#define A1        (17)
#define A2        (18)
#define A3        (19)
#define A4        (20)
#define A5        (21)

#define F_CPU          160000000L  /* CPU:160MHz */

/* i2c1 : PB9-SDA PB8-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c1"

/* spi1 : PA5-SCK  PA6-MISO  PA7-MOSI */
#define RTDUINO_DEFAULT_SPI_BUS_NAME      "spi1"

#endif /* Pins_Arduino_h */
