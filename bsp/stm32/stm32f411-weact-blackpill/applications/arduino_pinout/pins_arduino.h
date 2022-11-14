/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-14     ChuShicheng  first version
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
#define D20       (20)
#define D21       (21)
#define D22       (22)
#define D23       (23)
#define A0        (24)
#define A1        (25)
#define A2        (26)
#define A3        (27)
#define A4        (28)
#define A5        (29)
#define A6        (30)
#define A7        (31)

#define F_CPU          60000000L  /* CPU:60MHz */

#define LED_BUILTIN     D0  /* Default Built-in LED */

/* spi1 : xxx-SCK  xxx-MISO  xxx-MOSI */
#define SS      D14  /* Chip select pin of default spi */
#define RTDUINO_DEFAULT_SPI_BUS_NAME      "spi1"

#endif /* Pins_Arduino_h */
