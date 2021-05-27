/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-06-01     Ernest       the first version
 */
#ifndef __PIN_CONFIG_H__
#define __PIN_CONFIG_H__

// UART
#define WM_UART2_RX_PIN  1          // PB19 : UART2_RX  (W601)
#define WM_UART2_TX_PIN  2          // PB20 : UART2_TX  (W601)

#define WM_UART1_RX_PIN  31         // PB11 : UART1_RX  (W600)
#define WM_UART1_TX_PIN  32         // PB12 : UART1_TX  (W600)

// spi
#define WM_SPI_CK_PIN 53            // PB27 : SPI_SCK
#define WM_SPI_DI_PIN 55            // PB1  : SPI_MISO
#define WM_SPI_DO_PIN 56            // PB2  : SPI_MOSI

// i2c
#define WM_I2C_SCL_PIN 18
#define WM_I2C_DAT_PIN 19

// soft i2c
#define SOFT_I2C1_SCL_PIN 23         // PA0 : I2C1_SCL
#define SOFT_I2C1_SDA_PIN 24         // PA1 : I2C1_SDA
#define SOFT_I2C2_SCL_PIN 25         // PA2 : I2C2_SCL
#define SOFT_I2C2_SDA_PIN 24         // PA1 : I2C2_SDA

#endif /* __PIN_CONFIG_H__ */

