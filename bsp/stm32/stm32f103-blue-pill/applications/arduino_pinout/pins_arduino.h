/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-05     liYony       first version
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
#define D25  (25)
#define D26  (26)
#define D27  (27)
#define D28  (28)
#define A0   (29)
#define A1   (30)
#define A2   (31)
#define A3   (32)
#define A4   (33)
#define A5   (34)
#define A6   (35)

#define F_CPU  72000000L /* CPU: 72MHz */
#define LED_BUILTIN  D19 /* Default Built-in LED */

#define RTDUINO_DEFAULT_IIC_BUS_NAME            "i2c1"

#define RTDUINO_SERIAL2_DEVICE_NAME             "uart2"
#define RTDUINO_SERIAL3_DEVICE_NAME             "uart3"

#endif /* Pins_Arduino_h */
