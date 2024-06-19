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

#define _HTCFG_SPI1_SCK_GPIOX                    C
#define _HTCFG_SPI1_SCK_GPION                    5

#define _HTCFG_SPI1_MISO_GPIOX                   C
#define _HTCFG_SPI1_MISO_GPION                   9

#define _HTCFG_SPI1_MOSI_GPIOX                   C
#define _HTCFG_SPI1_MOSI_GPION                   8

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
#ifdef BSP_USING_I2C_HW
#ifdef BSP_USING_I2C0_HW

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
#ifdef BSP_USING_I2C1_HW

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

/* ADC gpio */
#ifdef BSP_USING_ADC
#ifdef BSP_USING_ADC0

#define HTCFG_ADC0_IPN                           ADC0

#define _HTCFG_ADC0CH0_GPIOX                     A
#define _HTCFG_ADC0CH0_AFION                     0

#define _HTCFG_ADC0CH1_GPIOX                     A
#define _HTCFG_ADC0CH1_AFION                     1

#define _HTCFG_ADC0CH2_GPIOX                     A
#define _HTCFG_ADC0CH2_AFION                     2

#define _HTCFG_ADC0CH3_GPIOX                     A
#define _HTCFG_ADC0CH3_AFION                     3

#define _HTCFG_ADC0CH4_GPIOX                     A
#define _HTCFG_ADC0CH4_AFION                     4

#define _HTCFG_ADC0CH5_GPIOX                     A
#define _HTCFG_ADC0CH5_AFION                     5

#define _HTCFG_ADC0CH6_GPIOX                     A
#define _HTCFG_ADC0CH6_AFION                     6

#define _HTCFG_ADC0CH7_GPIOX                     A
#define _HTCFG_ADC0CH7_AFION                     7

#define _HTCFG_ADC0CH8_GPIOX                     C
#define _HTCFG_ADC0CH8_AFION                     4

#define _HTCFG_ADC0CH9_GPIOX                     C
#define _HTCFG_ADC0CH9_AFION                     5

#define _HTCFG_ADC0CH10_GPIOX                    C
#define _HTCFG_ADC0CH10_AFION                    8

#define _HTCFG_ADC0CH11_GPIOX                    C
#define _HTCFG_ADC0CH11_AFION                    9

#define _HTCFG_ADC0CH12_GPIOX                    C
#define _HTCFG_ADC0CH12_AFION                    1

#define _HTCFG_ADC0CH13_GPIOX                    C
#define _HTCFG_ADC0CH13_AFION                    1

#define _HTCFG_ADC0CH14_GPIOX                    C
#define _HTCFG_ADC0CH14_AFION                    1

#define _HTCFG_ADC0CH15_GPIOX                    C
#define _HTCFG_ADC0CH15_AFION                    1

#define HTCFG_ADC0CH0_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH0_GPIOX)
#define HTCFG_ADC0CH1_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH1_GPIOX)
#define HTCFG_ADC0CH2_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH2_GPIOX)
#define HTCFG_ADC0CH3_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH3_GPIOX)
#define HTCFG_ADC0CH4_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH4_GPIOX)
#define HTCFG_ADC0CH5_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH5_GPIOX)
#define HTCFG_ADC0CH6_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH6_GPIOX)
#define HTCFG_ADC0CH7_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH7_GPIOX)
#define HTCFG_ADC0CH8_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH8_GPIOX)
#define HTCFG_ADC0CH9_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC0CH9_GPIOX)
#define HTCFG_ADC0CH10_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_ADC0CH10_GPIOX)
#define HTCFG_ADC0CH11_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_ADC0CH11_GPIOX)
#define HTCFG_ADC0CH12_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_ADC0CH12_GPIOX)
#define HTCFG_ADC0CH13_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_ADC0CH13_GPIOX)
#define HTCFG_ADC0CH14_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_ADC0CH14_GPIOX)
#define HTCFG_ADC0CH15_GPIO_ID                   STRCAT2(GPIO_P,         _HTCFG_ADC0CH15_GPIOX)

#define HTCFG_ADC0CH0_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH0_AFION)
#define HTCFG_ADC0CH1_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH1_AFION)
#define HTCFG_ADC0CH2_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH2_AFION)
#define HTCFG_ADC0CH3_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH3_AFION)
#define HTCFG_ADC0CH4_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH4_AFION)
#define HTCFG_ADC0CH5_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH5_AFION)
#define HTCFG_ADC0CH6_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH6_AFION)
#define HTCFG_ADC0CH7_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH7_AFION)
#define HTCFG_ADC0CH8_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH8_AFION)
#define HTCFG_ADC0CH9_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH9_AFION)
#define HTCFG_ADC0CH10_AFIO_PIN                  STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH10_AFION)
#define HTCFG_ADC0CH11_AFIO_PIN                  STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH11_AFION)
#define HTCFG_ADC0CH12_AFIO_PIN                  STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH12_AFION)
#define HTCFG_ADC0CH13_AFIO_PIN                  STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH13_AFION)
#define HTCFG_ADC0CH14_AFIO_PIN                  STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH14_AFION)
#define HTCFG_ADC0CH15_AFIO_PIN                  STRCAT2(AFIO_PIN_,      _HTCFG_ADC0CH15_AFION)

#endif
#ifdef BSP_USING_ADC1

#define HTCFG_ADC1_IPN                           ADC1

#define _HTCFG_ADC1CH0_GPIOX                     B
#define _HTCFG_ADC1CH0_AFION                     8

#define _HTCFG_ADC1CH1_GPIOX                     A
#define _HTCFG_ADC1CH1_AFION                     0

#define _HTCFG_ADC1CH2_GPIOX                     A
#define _HTCFG_ADC1CH2_AFION                     1

#define _HTCFG_ADC1CH3_GPIOX                     A
#define _HTCFG_ADC1CH3_AFION                     2

#define _HTCFG_ADC1CH4_GPIOX                     A
#define _HTCFG_ADC1CH4_AFION                     3

#define _HTCFG_ADC1CH5_GPIOX                     A
#define _HTCFG_ADC1CH5_AFION                     4

#define _HTCFG_ADC1CH6_GPIOX                     A
#define _HTCFG_ADC1CH6_AFION                     5

#define _HTCFG_ADC1CH7_GPIOX                     A
#define _HTCFG_ADC1CH7_AFION                     6

#define HTCFG_ADC1CH0_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC1CH0_GPIOX)
#define HTCFG_ADC1CH1_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC1CH1_GPIOX)
#define HTCFG_ADC1CH2_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC1CH2_GPIOX)
#define HTCFG_ADC1CH3_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC1CH3_GPIOX)
#define HTCFG_ADC1CH4_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC1CH4_GPIOX)
#define HTCFG_ADC1CH5_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC1CH5_GPIOX)
#define HTCFG_ADC1CH6_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC1CH6_GPIOX)
#define HTCFG_ADC1CH7_GPIO_ID                    STRCAT2(GPIO_P,         _HTCFG_ADC1CH7_GPIOX)

#define HTCFG_ADC1CH0_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC1CH0_AFION)
#define HTCFG_ADC1CH1_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC1CH1_AFION)
#define HTCFG_ADC1CH2_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC1CH2_AFION)
#define HTCFG_ADC1CH3_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC1CH3_AFION)
#define HTCFG_ADC1CH4_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC1CH4_AFION)
#define HTCFG_ADC1CH5_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC1CH5_AFION)
#define HTCFG_ADC1CH6_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC1CH6_AFION)
#define HTCFG_ADC1CH7_AFIO_PIN                   STRCAT2(AFIO_PIN_,      _HTCFG_ADC1CH7_AFION)

#endif
#endif


void ht32_usart_gpio_init(void *instance);
void ht32_spi_gpio_init(void *instance);
void ht32_hardware_i2c_gpio_init(void *instance);
void ht32_adc_gpio_init(void *instance,int8_t channel);

#ifdef __cplusplus
}
#endif

#endif /* __HT32_MSP_H__ */
