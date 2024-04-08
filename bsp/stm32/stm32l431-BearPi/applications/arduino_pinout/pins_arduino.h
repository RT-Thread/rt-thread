/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-01     liYony       first version
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
#define A0        (13)
#define A1        (14)
#define A2        (15)
#define DAC0      (16)

#define RTDUINO_PIN_MAX_LIMIT DAC0 /* pin number max limit check */

#define F_CPU          80000000L  /* CPU:80MHz */

/* i2c1 : PB7-SDA PB6-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c1"

/* spi1 : PA1-SCK  PA6-MISO  PA12-MOSI */
#define SS      D1  /* Chip select pin of default spi */
#define RTDUINO_DEFAULT_SPI_BUS_NAME      "spi1"

/* Serial : PC4-TX  PC5-RX */
#define RTDUINO_SERIAL2_DEVICE_NAME      "uart3"

#endif /* Pins_Arduino_h */
