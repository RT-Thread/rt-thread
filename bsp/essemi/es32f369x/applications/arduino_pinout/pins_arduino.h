/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-07-07     shiwa        Adapt ES32F369x
 */

#ifndef Pins_Arduino_h
#define Pins_Arduino_h

/* pins alias. Must keep in sequence */
#define D0   (0)
#define D1   (1)
#define D2   (2)
#define D3   (3)
#define D4   (4)
#define D5   (5)
#define D6   (6)
#define D7   (7)

#define D8   (8)
#define D9   (9)
#define D10  (10)
#define D11  (11)
#define D12  (12)
#define D13  (13)
#define D14  (14)
#define D15  (15)
#define D16  (16)
#define D17  (17)
#define D18  (18)
#define D19  (19)
#define D20  (20)
#define D21  (21)
#define D22  (22)
#define D23  (23)
#define D24  (24)

#define A0   (25)
#define A1   (26)
#define A2   (27)
#define A3   (28)
#define A4   (29)
#define A5   (30)

#define RTDUINO_PIN_MAX_LIMIT A5 /* pin number max limit check */

#define F_CPU  96000000L /* CPU: 96MHz */

#define RTDUINO_DEFAULT_IIC_BUS_NAME            "i2c0"

#define SS D10
#define RTDUINO_DEFAULT_SPI_BUS_NAME            "spi0"

#define LED_BUILTIN D16

#endif /* Pins_Arduino_h */
