/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-12-10     Meco Man     first version
 * 2022-09-18     Meco Man     sort pinout out
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

#define F_CPU          80000000L  /* CPU:80MHz */

#define LED_BUILTIN     D22  /* Default Built-in LED */

/*
 * High accuracy timing is provided by hardware timer 7.
 * ALL of the Cortex-M CPU don't need to provide extra hardware timer.
 * RTduino will automatically use Cortex-M internal timer to provide the
 * high accuracy timing.
 * This is just an example to show how to use hardware timer to provide
 * high accuracy timing for RTduino.
 */
#define RTDUINO_DEFAULT_HWTIMER_DEVICE_NAME      "timer7"

/* Serial2 - PA2-TX  PA3-RX */
#define RTDUINO_SERIAL2_DEVICE_NAME     "uart2"

/* I2C */
#if defined(BSP_USING_ARDUINO_AHT10)
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c4" /* i2c4 - AHT10 (On Board) */
#elif defined(BSP_USING_ARDUINO_AP3216) || defined(BSP_USING_ARDUINO_ICM20608)
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c3" /* i2c3 - ICM20608, AP3216C (On Board) */
#else
#define RTDUINO_DEFAULT_IIC_BUS_NAME    "i2c1" /* i2c1 - PC7-SDA PC6-SCL (User I2C) */
#endif /* BSP_USING_ARDUINO_AHT10 */

/* SPI */
#if defined(BSP_USING_ARDUINO_ST7789)
/*
 * SPI LCD ST7789 (spi3)
 * LCD-SPI-SDA  PB5
 * LCD-SPI-SCK  PB3
 * LCD-SPI-CS   PD7
 * LCD-POWER    PB7
 * LCD-RESET    PB6
 * LCD-WR/DC    PB4
 */
#define SS      D36  /* LCD-SPI-CS PD7 */
#define RTDUINO_DEFAULT_SPI_BUS_NAME      "spi3" /* LCD SPI Bus */
#else
/* spi2 - PB13-SCK  PB14-MISO  PB15-MOSI */
#define SS      D28  /* Chip select pin of default spi */
#define RTDUINO_DEFAULT_SPI_BUS_NAME      "spi2"
#endif /* BSP_USING_ARDUINO_ST7789 */

#endif /* Pins_Arduino_h */
