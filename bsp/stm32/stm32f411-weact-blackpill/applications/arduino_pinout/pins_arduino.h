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
#define A8        (32)
#define A9        (33)

#define RTDUINO_PIN_MAX_LIMIT A9 /* pin number max limit check */

#define F_CPU          60000000L  /* CPU:60MHz */

#define LED_BUILTIN     D0  /* Default Built-in LED */

/* spi1 : SPI1-SCK  SPI1-MISO  SPI1-MOSI */
#define SS      D14  /* Chip select pin of default spi */
#define RTDUINO_DEFAULT_SPI_BUS_NAME      "spi1"

/* i2c1 : PB2-SDA PB10-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c1"

/* Serial2 - PA2-TX  PA3-RX */
#define RTDUINO_SERIAL2_DEVICE_NAME      "uart2"

#endif /* Pins_Arduino_h */
