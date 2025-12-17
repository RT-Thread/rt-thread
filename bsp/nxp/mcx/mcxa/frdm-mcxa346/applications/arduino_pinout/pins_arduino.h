/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-12-08     westcity-yolo  first version
 *
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
#define D18       (14)
#define D19       (15)

#define A0        (16)
#define A1        (17)
#define A2        (18)
#define A3        (19)
#define A4        (20)
#define A5        (21)
#define A6        (22)
#define A7        (23)

#define RTDUINO_PIN_MAX_LIMIT A7 /* pin number max limit check */

#define F_CPU          180000000L  /* CPU:180MHz */

/* i2c2 : P(,1_8-SDA P(,1_9-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c2"

/* Serial2 : P(,2_2-TX  P(,2_3-RX */
#define RTDUINO_SERIAL2_DEVICE_NAME      "uart2"

/* spi1 : P(,3_8-SDO P(,3_9-SDI  P(,3_10-SCK P(,3_11-SS */

#define RTDUINO_DEFAULT_SPI_BUS_NAME    "spi1"

#endif /* Pins_Arduino_h */