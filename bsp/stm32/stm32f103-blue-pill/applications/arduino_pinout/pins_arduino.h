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
#define A0   (14)
#define A1   (15)
#define A2   (16)
#define A3   (17)
#define A4   (18)
#define A5   (19)
#define A6   (20)

#define F_CPU  72000000L /* CPU: 72MHz */
#define LED_BUILTIN  D8 /* Default Built-in LED */

/*
 * i2c1 - PB9-SDA PB8-SCL
 */
#define RTDUINO_DEFAULT_IIC_BUS_NAME            "i2c1"

/*
 * uart2 - PA2-TX  PA3-RX
 * uart3 - PB10-TX PB11-RX
 */
#define RTDUINO_SERIAL2_DEVICE_NAME             "uart2"
#define RTDUINO_SERIAL3_DEVICE_NAME             "uart3"

#endif /* Pins_Arduino_h */
