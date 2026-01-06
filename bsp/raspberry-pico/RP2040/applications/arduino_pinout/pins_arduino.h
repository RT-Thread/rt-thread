/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-01-25     ShichengChu  first version
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
#define A0        (26)
#define A1        (27)
#define A2        (28)

#define RTDUINO_PIN_MAX_LIMIT A2 /* pin number max limit check */

#define F_CPU          133000000L  /* CPU:133MHz */

#define LED_BUILTIN     D25  /* Default Built-in LED */

/* Serial2 : P-TX  P-RX */
#define RTDUINO_SERIAL2_DEVICE_NAME      "uart1"

#define SS          D17
#define RTDUINO_DEFAULT_SPI_BUS_NAME     "spi0"

/* i2c0 : D4-SDA D5-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c0"

#endif /* Pins_Arduino_h */
