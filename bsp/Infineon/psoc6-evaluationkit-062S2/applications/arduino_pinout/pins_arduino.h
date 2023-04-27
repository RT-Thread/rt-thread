/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-04-17     Rbb666       first version
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

#define F_CPU          150000000L  /* CPU:150MHz */

/* i2c4 : P81-SDA P80-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c4"

/* spi0 : P04-SCK  P03-MISO  P02-MOSI */
#define SS      D5  /* Chip select pin of default spi */
#define RTDUINO_DEFAULT_SPI_BUS_NAME      "spi0"

/* Serial2 : P1,1-TX  P1,0-RX */
#define RTDUINO_SERIAL2_DEVICE_NAME      "uart5"

#endif /* Pins_Arduino_h */
