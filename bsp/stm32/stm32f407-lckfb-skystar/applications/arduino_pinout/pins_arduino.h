/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-04-07     Li ZhenHong    first version
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
#define D27       (27)
#define D28       (28)
#define D29       (29)
#define D30       (30)
#define D31       (31)
#define D32       (32)
#define D33       (33)
#define D34       (34)
#define D35       (35)
#define D36       (36)
#define D37       (37)
#define D38       (38)
#define D39       (39)
#define A0        (40)
#define A1        (41)
#define A2        (42)
#define A3        (43)
#define DAC0      (44)

#define RTDUINO_PIN_MAX_LIMIT DAC0 /* pin number max limit check */

#define F_CPU 168000000L /* CPU:168MHz */

#define LED_BUILTIN D33 /* Default Built-in LED */

/* i2c4 : PD.7-SDA PG.7-SCL */
#define RTDUINO_DEFAULT_IIC_BUS_NAME "i2c4"

#define SS D32 /* Chip select pin of default spi */
/* sspi1 : PG.5-SCK  PG.3-MISO  PG.1-MOSI */
#define RTDUINO_DEFAULT_SPI_BUS_NAME "sspi1"

/* Serial2(uart2) : PA.2-TX  PA.3-RX */
#define RTDUINO_SERIAL2_DEVICE_NAME "uart2"

#endif /* Pins_Arduino_h */
