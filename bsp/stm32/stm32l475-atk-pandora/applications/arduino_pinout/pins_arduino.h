/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
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
#define A0   (26)
#define A1   (27)
#define A2   (28)
#define A3   (29)
#define DAC0 (30)

#define LED_BUILTIN  D22 /* Default Built-in LED */

/*
 * i2c1 - PC7-SDA PC6-SCL(User I2C)
 * i2c3 - ICM20608, AP3216C (On Board)
 * i2c4 - AHT10 (On Board)
 */
#define RTDUINO_DEFAULT_IIC_BUS_NAME            "i2c4"
#define RTDUINO_DEFAULT_SPI_BUS_NAME            "spi2"
#define RTDUINO_DEFAULT_HWTIMER_DEVICE_NAME     "timer7"
#define RTDUINO_SERIAL2_DEVICE_NAME             "uart2"

#endif /* Pins_Arduino_h */
