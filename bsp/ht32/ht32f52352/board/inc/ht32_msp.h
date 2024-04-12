/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-04-08     QT-one       first version
 */

#ifndef __HT32_MSP_H__
#define __HT32_MSP_H__

#include <rtthread.h>
#include "ht32.h"

#ifdef __cplusplus
extern "C" {
#endif

/* UART gpio */
#ifdef BSP_USING_UART
#ifdef BSP_USING_USART0
#define HTCFG_USART0_IPN                          USART0

#define _HTCFG_USART0_TX_GPIOX                    A
#define _HTCFG_USART0_TX_GPION                    2
#define _HTCFG_USART0_RX_GPIOX                    A
#define _HTCFG_USART0_RX_GPION                    3

#define HTCFG_USART0_TX_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_USART0_TX_GPIOX)
#define HTCFG_USART0_TX_GPIO_CLK                  STRCAT2(P,              _HTCFG_USART0_TX_GPIOX)
#define HTCFG_USART0_TX_GPIO_PORT                 STRCAT2(HT_GPIO,        _HTCFG_USART0_TX_GPIOX)
#define HTCFG_USART0_TX_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_USART0_TX_GPION)

#define HTCFG_USART0_RX_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_USART0_RX_GPIOX)
#define HTCFG_USART0_RX_GPIO_CLK                  STRCAT2(P,              _HTCFG_USART0_RX_GPIOX)
#define HTCFG_USART0_RX_GPIO_PORT                 STRCAT2(HT_GPIO,        _HTCFG_USART0_RX_GPIOX)
#define HTCFG_USART0_RX_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_USART0_RX_GPION)

#endif
#ifdef BSP_USING_USART1

#define HTCFG_USART1_IPN                          USART1

#define _HTCFG_USART1_TX_GPIOX                    A
#define _HTCFG_USART1_TX_GPION                    4
#define _HTCFG_USART1_RX_GPIOX                    A
#define _HTCFG_USART1_RX_GPION                    5

#define HTCFG_USART1_TX_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_USART1_TX_GPIOX)
#define HTCFG_USART1_TX_GPIO_CLK                  STRCAT2(P,              _HTCFG_USART1_TX_GPIOX)
#define HTCFG_USART1_TX_GPIO_PORT                 STRCAT2(HT_GPIO,        _HTCFG_USART1_TX_GPIOX)
#define HTCFG_USART1_TX_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_USART1_TX_GPION)

#define HTCFG_USART1_RX_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_USART1_RX_GPIOX)
#define HTCFG_USART1_RX_GPIO_CLK                  STRCAT2(P,              _HTCFG_USART1_RX_GPIOX)
#define HTCFG_USART1_RX_GPIO_PORT                 STRCAT2(HT_GPIO,        _HTCFG_USART1_RX_GPIOX)
#define HTCFG_USART1_RX_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_USART1_RX_GPION)

#endif
#ifdef BSP_USING_UART0

#define HTCFG_UART0_IPN                          UART0

#define _HTCFG_UART0_TX_GPIOX                    B
#define _HTCFG_UART0_TX_GPION                    2
#define _HTCFG_UART0_RX_GPIOX                    B
#define _HTCFG_UART0_RX_GPION                    3

#define HTCFG_UART0_TX_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_UART0_TX_GPIOX)
#define HTCFG_UART0_TX_GPIO_CLK                  STRCAT2(P,              _HTCFG_UART0_TX_GPIOX)
#define HTCFG_UART0_TX_GPIO_PORT                 STRCAT2(HT_GPIO,        _HTCFG_UART0_TX_GPIOX)
#define HTCFG_UART0_TX_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_UART0_TX_GPION)

#define HTCFG_UART0_RX_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_UART0_RX_GPIOX)
#define HTCFG_UART0_RX_GPIO_CLK                  STRCAT2(P,              _HTCFG_UART0_RX_GPIOX)
#define HTCFG_UART0_RX_GPIO_PORT                 STRCAT2(HT_GPIO,        _HTCFG_UART0_RX_GPIOX)
#define HTCFG_UART0_RX_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_UART0_RX_GPION)

#endif
#ifdef BSP_USING_UART1

#define HTCFG_UART1_IPN                          UART1

#define _HTCFG_UART1_TX_GPIOX                    B
#define _HTCFG_UART1_TX_GPION                    4
#define _HTCFG_UART1_RX_GPIOX                    B
#define _HTCFG_UART1_RX_GPION                    5

#define HTCFG_UART1_TX_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_UART1_TX_GPIOX)
#define HTCFG_UART1_TX_GPIO_CLK                  STRCAT2(P,              _HTCFG_UART1_TX_GPIOX)
#define HTCFG_UART1_TX_GPIO_PORT                 STRCAT2(HT_GPIO,        _HTCFG_UART1_TX_GPIOX)
#define HTCFG_UART1_TX_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_UART1_TX_GPION)

#define HTCFG_UART1_RX_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_UART1_RX_GPIOX)
#define HTCFG_UART1_RX_GPIO_CLK                  STRCAT2(P,              _HTCFG_UART1_RX_GPIOX)
#define HTCFG_UART1_RX_GPIO_PORT                 STRCAT2(HT_GPIO,        _HTCFG_UART1_RX_GPIOX)
#define HTCFG_UART1_RX_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_UART1_RX_GPION)

#endif
#endif

/* SPI gpio */
#ifdef BSP_USING_SPI
#ifdef BSP_USING_SPI0

#define HTCFG_SPI0_IPN                           SPI0

#define _HTCFG_SPI0_SCK_GPIOX                    C
#define _HTCFG_SPI0_SCK_GPION                    0

#define _HTCFG_SPI0_MISO_GPIOX                   A
#define _HTCFG_SPI0_MISO_GPION                   11

#define _HTCFG_SPI0_MOSI_GPIOX                   A
#define _HTCFG_SPI0_MOSI_GPION                   9

#define HTCFG_SPI0_SCK_GPIO_CLK                  STRCAT2(P,              _HTCFG_SPI0_SCK_GPIOX)
#define HTCFG_SPI0_SCK_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_SPI0_SCK_GPIOX)
#define HTCFG_SPI0_SCK_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_SPI0_SCK_GPION)

#define HTCFG_SPI0_MISO_GPIO_CLK                 STRCAT2(P,              _HTCFG_SPI0_MISO_GPIOX)
#define HTCFG_SPI0_MISO_GPIO_ID                  STRCAT2(GPIO_P,         _HTCFG_SPI0_MISO_GPIOX)
#define HTCFG_SPI0_MISO_GPIO_PIN                 STRCAT2(GPIO_PIN_,      _HTCFG_SPI0_MISO_GPION)

#define HTCFG_SPI0_MOSI_GPIO_CLK                 STRCAT2(P,              _HTCFG_SPI0_MOSI_GPIOX)
#define HTCFG_SPI0_MOSI_GPIO_ID                  STRCAT2(GPIO_P,         _HTCFG_SPI0_MOSI_GPIOX)
#define HTCFG_SPI0_MOSI_GPIO_PIN                 STRCAT2(GPIO_PIN_,      _HTCFG_SPI0_MOSI_GPION)

#endif
#ifdef BSP_USING_SPI1

#define HTCFG_SPI1_IPN                           SPI1

#define _HTCFG_SPI1_SCK_GPIOX                    A
#define _HTCFG_SPI1_SCK_GPION                    15

#define _HTCFG_SPI1_MISO_GPIOX                   B
#define _HTCFG_SPI1_MISO_GPION                   1

#define _HTCFG_SPI1_MOSI_GPIOX                   B
#define _HTCFG_SPI1_MOSI_GPION                   0

#define HTCFG_SPI1_SCK_GPIO_CLK                  STRCAT2(P,              _HTCFG_SPI1_SCK_GPIOX)
#define HTCFG_SPI1_SCK_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_SPI1_SCK_GPIOX)
#define HTCFG_SPI1_SCK_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_SPI1_SCK_GPION)

#define HTCFG_SPI1_MISO_GPIO_CLK                 STRCAT2(P,              _HTCFG_SPI1_MISO_GPIOX)
#define HTCFG_SPI1_MISO_GPIO_ID                  STRCAT2(GPIO_P,         _HTCFG_SPI1_MISO_GPIOX)
#define HTCFG_SPI1_MISO_GPIO_PIN                 STRCAT2(GPIO_PIN_,      _HTCFG_SPI1_MISO_GPION)

#define HTCFG_SPI1_MOSI_GPIO_CLK                 STRCAT2(P,              _HTCFG_SPI1_MOSI_GPIOX)
#define HTCFG_SPI1_MOSI_GPIO_ID                  STRCAT2(GPIO_P,         _HTCFG_SPI1_MOSI_GPIOX)
#define HTCFG_SPI1_MOSI_GPIO_PIN                 STRCAT2(GPIO_PIN_,      _HTCFG_SPI1_MOSI_GPION)

#endif
#endif

/* I2C gpio */
#ifdef BSP_USING_I2C
#ifdef BSP_USING_I2C0

#define HTCFG_I2C0_IPN                           I2C0

#define _HTCFG_I2C0_SCL_GPIOX                    C
#define _HTCFG_I2C0_SCL_GPION                    12

#define _HTCFG_I2C0_SDA_GPIOX                    C
#define _HTCFG_I2C0_SDA_GPION                    13

#define HTCFG_I2C0_SCL_GPIO_CLK                  STRCAT2(P,              _HTCFG_I2C0_SCL_GPIOX)
#define HTCFG_I2C0_SCL_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_I2C0_SCL_GPIOX)
#define HTCFG_I2C0_SCL_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_I2C0_SCL_GPION)

#define HTCFG_I2C0_SDA_GPIO_CLK                  STRCAT2(P,              _HTCFG_I2C0_SDA_GPIOX)
#define HTCFG_I2C0_SDA_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_I2C0_SDA_GPIOX)
#define HTCFG_I2C0_SDA_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_I2C0_SDA_GPION)

#endif
#ifdef BSP_USING_I2C1

#define HTCFG_I2C1_IPN                           I2C1

#define _HTCFG_I2C1_SCL_GPIOX                    A
#define _HTCFG_I2C1_SCL_GPION                    0

#define _HTCFG_I2C1_SDA_GPIOX                    A
#define _HTCFG_I2C1_SDA_GPION                    1

#define HTCFG_I2C1_SCL_GPIO_CLK                  STRCAT2(P,              _HTCFG_I2C1_SCL_GPIOX)
#define HTCFG_I2C1_SCL_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_I2C1_SCL_GPIOX)
#define HTCFG_I2C1_SCL_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_I2C1_SCL_GPION)

#define HTCFG_I2C1_SDA_GPIO_CLK                  STRCAT2(P,              _HTCFG_I2C1_SDA_GPIOX)
#define HTCFG_I2C1_SDA_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_I2C1_SDA_GPIOX)
#define HTCFG_I2C1_SDA_GPIO_PIN                  STRCAT2(GPIO_PIN_,      _HTCFG_I2C1_SDA_GPION)

#endif
#endif

void ht32_usart_gpio_init(void *instance);
void ht32_spi_gpio_init(void *instance);
void ht32_i2c_gpio_init(void *instance);

#ifdef __cplusplus
}
#endif

#endif /* __HT32_MSP_H__ */
