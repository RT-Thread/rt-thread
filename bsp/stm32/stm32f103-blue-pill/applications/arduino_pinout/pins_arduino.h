/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-09-20     liYony       first version
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
#define D24       (24)
#define D25       (25)
#define D26       (26)
#define A0        (27)
#define A1        (28)
#define A2        (29)
#define A3        (30)
#define A4        (31)
#define A5        (32)
#define A6        (33)

#define RTDUINO_PIN_MAX_LIMIT A6 /* pin number max limit check */

#define F_CPU          72000000L  /* CPU:72MHz */

#define LED_BUILTIN     D8  /* Default Built-in LED */

/* i2c1 : PB9-SDA PB8-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c1"

/* spi2 : PB13-SCK  PB14-MISO  PB15-MOSI */
#define SS      D7  /* Chip select pin of default spi */
#define RTDUINO_DEFAULT_SPI_BUS_NAME      "spi2"

/* Serial2 : PA2-TX  PA3-RX */
#define RTDUINO_SERIAL2_DEVICE_NAME      "uart2"

/* Serial3 : PB10-TX  PB11-RX */
#define RTDUINO_SERIAL3_DEVICE_NAME      "uart3"

#endif /* Pins_Arduino_h */
