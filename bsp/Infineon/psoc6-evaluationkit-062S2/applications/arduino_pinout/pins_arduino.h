/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-08-16     LZerro         first version
 */

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

/* pins alias. Must keep in sequence */
#define D00        (0)
#define D01        (1)
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

#define RTDUINO_PIN_MAX_LIMIT D15 /* pin number max limit check */

#define F_CPU 150000000L /* CPU:150MHz */

// #define LED_BUILTIN D0 /* Default Built-in LED */

/* i2c0 : P08.01-SDA P08.00-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME "i2c4"

/* spi0 : P0.04-SCK  P00.03-MISO  P00.02-MOSI */
#define SS D10 /* Chip select pin of default spi */
#define RTDUINO_DEFAULT_SPI_BUS_NAME "spi0"

#endif /* Pins_Arduino_h */
