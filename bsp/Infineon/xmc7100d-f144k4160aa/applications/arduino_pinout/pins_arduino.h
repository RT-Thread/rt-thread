/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2025-10-16     Hydevcode         first version
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

#define RTDUINO_PIN_MAX_LIMIT D7 /* pin number max limit check */

#define F_CPU 350000000L /* CPU:350MHz */

// #define LED_BUILTIN D0 /* Default Built-in LED */

/* i2c2 : P00.00-SDA P00.01-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME "i2c2"

#define SS D2 /* Chip select pin of default spi */
#define RTDUINO_DEFAULT_SPI_BUS_NAME "spi0"

#endif /* Pins_Arduino_h */