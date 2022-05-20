/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-27     AisinoCip    add board.h to this bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtthread.h>
#include "ACM32Fxx_HAL.h"

/*-------------------------- UART CONFIG BEGIN --------------------------*/

/** After configuring corresponding UART or UART DMA, you can use it.
  *
  * STEP 1, define macro define related to the serial port opening based on the serial port number
  *                 such as     #define BSP_USING_UATR1
  *
  * STEP 2, according to the corresponding pin of serial port, modify the related serial port information
  *                 such as     #define UART1_TX_PORT            GPIOX   ->   GPIOA
  *                             #define UART1_RX_PORT            GPIOX   ->   GPIOA
  *                             #define UART1_TX_PIN        GPIO_PIN_X   ->   GPIO_PIN_9
  *                             #define UART1_RX_PIN        GPIO_PIN_X   ->   GPIO_PIN_10
  *
  * STEP 3, if you want using SERIAL DMA, you must open it in the RT-Thread Settings.
  *                 RT-Thread Setting -> Components -> Device Drivers -> Serial Device Drivers -> Enable Serial DMA Mode
  *
  * STEP 4, according to serial port number to define serial port tx/rx DMA function in the board.h file
  *                 such as     #define BSP_UART1_RX_USING_DMA
  *
  */

#if defined(BSP_USING_UART1)
    #define UART1_TX_PORT           GPIOA
    #define UART1_RX_PORT           GPIOA
    #define UART1_TX_PIN            GPIO_PIN_9
    #define UART1_RX_PIN            GPIO_PIN_10

    #if defined(BSP_UART1_RX_USING_DMA)
        #define UART1_RX_DMA_INSTANCE   DMA_Channel0
        #define UART1_RX_DMA_RCC        BIT12
        #define UART1_RX_DMA_IRQ        DMA_IRQn
        #define UART1_RX_DMA_CHANNEL    0
        #define UART1_RX_DMA_REQUEST    REQ6_UART1_RECV
    #endif /* BSP_UART1_RX_USING_DMA */

    #if defined(BSP_UART1_TX_USING_DMA)
        #define UART1_TX_DMA_INSTANCE   DMA_Channel1
        #define UART1_TX_DMA_RCC        BIT12
        #define UART1_TX_DMA_IRQ        DMA_IRQn
        #define UART1_TX_DMA_CHANNEL    1
        #define UART1_TX_DMA_REQUEST    REQ5_UART1_SEND
    #endif /* BSP_UART1_TX_USING_DMA */

#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
    #define UART2_TX_PORT           GPIOA
    #define UART2_RX_PORT           GPIOA
    #define UART2_TX_PIN            GPIO_PIN_2
    #define UART2_RX_PIN            GPIO_PIN_3

    #if defined(BSP_UART2_RX_USING_DMA)
        #define UART2_RX_DMA_INSTANCE   DMA_Channel0
        #define UART2_RX_DMA_RCC        BIT12
        #define UART2_RX_DMA_IRQ        DMA_IRQn
        #define UART2_RX_DMA_CHANNEL    0
        #define UART2_RX_DMA_REQUEST    REQ8_UART2_RECV
    #endif /* BSP_UART2_RX_USING_DMA */

    #if defined(BSP_UART2_TX_USING_DMA)
        #define UART2_TX_DMA_INSTANCE   DMA_Channel1
        #define UART2_TX_DMA_RCC        BIT12
        #define UART2_TX_DMA_IRQ        DMA_IRQn
        #define UART2_TX_DMA_CHANNEL    1
        #define UART2_TX_DMA_REQUEST    REQ7_UART2_SEND
    #endif /* BSP_UART2_TX_USING_DMA */
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
    #define UART3_TX_PORT           GPIOB
    #define UART3_RX_PORT           GPIOB
    #define UART3_TX_PIN            GPIO_PIN_10
    #define UART3_RX_PIN            GPIO_PIN_11

    #if defined(BSP_UART3_RX_USING_DMA)
        #define UART3_RX_DMA_INSTANCE   DMA_Channel0
        #define UART3_RX_DMA_RCC        BIT12
        #define UART3_RX_DMA_IRQ        DMA_IRQn
        #define UART3_RX_DMA_CHANNEL    2
        #define UART3_RX_DMA_REQUEST    REQ29_UART3_RECV
    #endif /* BSP_UART3_RX_USING_DMA */

    #if defined(BSP_UART3_TX_USING_DMA)
        #define UART3_TX_DMA_INSTANCE   DMA_Channel1
        #define UART3_TX_DMA_RCC        BIT12
        #define UART3_TX_DMA_IRQ        DMA_IRQn
        #define UART3_TX_DMA_CHANNEL    3
        #define UART3_TX_DMA_REQUEST    REQ27_UART3_SEND
    #endif /* BSP_UART3_TX_USING_DMA */
#endif /* BSP_USING_UART3 */
/*-------------------------- UART CONFIG END --------------------------*/

/*-------------------------- SPI CONFIG BEGIN --------------------------*/
#if defined(BSP_USING_SPI1)
    #define SPI1_CS_PORT            GPIOA
    #define SPI1_CS_PIN             GPIO_PIN_2
    #define SPI1_CS_ALTERNATE       GPIO_FUNCTION_3
    #define SPI1_SCK_PORT           GPIOA
    #define SPI1_SCK_PIN            GPIO_PIN_1
    #define SPI1_SCK_ALTERNATE      GPIO_FUNCTION_1
    #define SPI1_MISO_PORT          GPIOB
    #define SPI1_MISO_PIN           GPIO_PIN_0
    #define SPI1_MISO_ALTERNATE     GPIO_FUNCTION_5
    #define SPI1_MOSI_PORT          GPIOB
    #define SPI1_MOSI_PIN           GPIO_PIN_1
    #define SPI1_MOSI_ALTERNATE     GPIO_FUNCTION_5
    #define SPI1_WP_PORT            GPIOA
    #define SPI1_WP_PIN             GPIO_PIN_7
    #define SPI1_WP_ALTERNATE       GPIO_FUNCTION_4
    #define SPI1_HOLD_PORT          GPIOA
    #define SPI1_HOLD_PIN           GPIO_PIN_6
    #define SPI1_HOLD_ALTERNATE     GPIO_FUNCTION_4

    #if defined(BSP_SPI1_RX_USING_DMA)
        #define SPI1_RX_DMA_INSTANCE   DMA_Channel0
        #define SPI1_RX_DMA_RCC        BIT12
        #define SPI1_RX_DMA_IRQ        DMA_IRQn
        #define SPI1_RX_DMA_CHANNEL    0
        #define SPI1_RX_DMA_REQUEST    REQ2_SPI1_RECV
    #endif /* BSP_SPI1_RX_USING_DMA */

    #if defined(BSP_SPI1_TX_USING_DMA)
        #define SPI1_TX_DMA_INSTANCE   DMA_Channel1
        #define SPI1_TX_DMA_RCC        BIT12
        #define SPI1_TX_DMA_IRQ        DMA_IRQn
        #define SPI1_TX_DMA_CHANNEL    1
        #define SPI1_TX_DMA_REQUEST    REQ1_SPI1_SEND
    #endif /* BSP_SPI1_TX_USING_DMA */
#endif /* BSP_USING_SPI1 */

#if defined(BSP_USING_SPI2)
    #define SPI2_CS_PORT            GPIOB
    #define SPI2_CS_PIN             GPIO_PIN_12
    #define SPI2_CS_ALTERNATE       GPIO_FUNCTION_4
    #define SPI2_SCK_PORT           GPIOB
    #define SPI2_SCK_PIN            GPIO_PIN_13
    #define SPI2_SCK_ALTERNATE      GPIO_FUNCTION_4
    #define SPI2_MISO_PORT          GPIOB
    #define SPI2_MISO_PIN           GPIO_PIN_14
    #define SPI2_MISO_ALTERNATE     GPIO_FUNCTION_4
    #define SPI2_MOSI_PORT          GPIOB
    #define SPI2_MOSI_PIN           GPIO_PIN_15
    #define SPI2_MOSI_ALTERNATE     GPIO_FUNCTION_4
    #define SPI2_WP_PORT            GPIOC
    #define SPI2_WP_PIN             GPIO_PIN_7
    #define SPI2_WP_ALTERNATE       GPIO_FUNCTION_2
    #define SPI2_HOLD_PORT          GPIOC
    #define SPI2_HOLD_PIN           GPIO_PIN_6
    #define SPI2_HOLD_ALTERNATE     GPIO_FUNCTION_2

    #if defined(BSP_SPI2_RX_USING_DMA)
        #define SPI2_RX_DMA_INSTANCE   DMA_Channel2
        #define SPI2_RX_DMA_RCC        BIT12
        #define SPI2_RX_DMA_IRQ        DMA_IRQn
        #define SPI2_RX_DMA_CHANNEL    2
        #define SPI2_RX_DMA_REQUEST    REQ4_SPI2_RECV
    #endif /* BSP_SPI2_RX_USING_DMA */

    #if defined(BSP_SPI2_TX_USING_DMA)
        #define SPI2_TX_DMA_INSTANCE   DMA_Channel3
        #define SPI2_TX_DMA_RCC        BIT12
        #define SPI2_TX_DMA_IRQ        DMA_IRQn
        #define SPI2_TX_DMA_CHANNEL    3
        #define SPI2_TX_DMA_REQUEST    REQ3_SPI2_SEND
    #endif /* BSP_SPI2_TX_USING_DMA */
#endif /* BSP_USING_SPI2 */
/*-------------------------- SPI CONFIG END --------------------------*/

/*-------------------------- I2C CONFIG BEGIN --------------------------*/
#if defined(BSP_USING_I2C1)
    #define I2C1_SCL_PORT               GPIOB
    #define I2C1_SCL_PIN                GPIO_PIN_6
    #define I2C1_SCL_ALTERNATE          GPIO_FUNCTION_6
    #define I2C1_SDA_PORT               GPIOB
    #define I2C1_SDA_PIN                GPIO_PIN_7
    #define I2C1_SDA_ALTERNATE          GPIO_FUNCTION_6

    #if defined(BSP_I2C1_RX_USING_DMA)
        #define I2C1_RX_DMA_INSTANCE   DMA_Channel0
        #define I2C1_RX_DMA_RCC        BIT12
        #define I2C1_RX_DMA_IRQ        DMA_IRQn
        #define I2C1_RX_DMA_CHANNEL    0
        #define I2C1_RX_DMA_REQUEST    REQ10_I2C1_RECV
    #endif /* BSP_I2C1_RX_USING_DMA */

    #if defined(BSP_I2C1_TX_USING_DMA)
        #define I2C1_TX_DMA_INSTANCE   DMA_Channel1
        #define I2C1_TX_DMA_RCC        BIT12
        #define I2C1_TX_DMA_IRQ        DMA_IRQn
        #define I2C1_TX_DMA_CHANNEL    1
        #define I2C1_TX_DMA_REQUEST    REQ9_I2C1_SEND
    #endif /* BSP_I2C1_TX_USING_DMA */
#endif /* BSP_USING_I2C1 */

#if defined(BSP_USING_I2C2)
    #define I2C2_SCL_PORT               GPIOB
    #define I2C2_SCL_PIN                GPIO_PIN_10
    #define I2C2_SCL_ALTERNATE          GPIO_FUNCTION_6
    #define I2C2_SDA_PORT               GPIOB
    #define I2C2_SDA_PIN                GPIO_PIN_11
    #define I2C2_SDA_ALTERNATE          GPIO_FUNCTION_6

    #if defined(BSP_I2C2_RX_USING_DMA)
        #define I2C2_RX_DMA_INSTANCE   DMA_Channel0
        #define I2C2_RX_DMA_RCC        BIT12
        #define I2C2_RX_DMA_IRQ        DMA_IRQn
        #define I2C2_RX_DMA_CHANNEL    0
        #define I2C2_RX_DMA_REQUEST    REQ10_I2C1_RECV
    #endif /* BSP_I2C2_RX_USING_DMA */

    #if defined(BSP_I2C2_TX_USING_DMA)
        #define I2C2_TX_DMA_INSTANCE   DMA_Channel1
        #define I2C2_TX_DMA_RCC        BIT12
        #define I2C2_TX_DMA_IRQ        DMA_IRQn
        #define I2C2_TX_DMA_CHANNEL    1
        #define I2C2_TX_DMA_REQUEST    REQ9_I2C1_SEND
    #endif /* BSP_I2C2_TX_USING_DMA */
#endif /* BSP_USING_I2C2 */
/*-------------------------- I2C CONFIG END --------------------------*/

void rt_hw_board_init(void);
#if defined(RT_USING_SPI)
    rt_err_t rt_hw_spi_device_attach(const char *bus_name, const char *device_name, enum_GPIOx_t cs_gpiox, uint16_t cs_gpio_pin);
#endif

#endif /* __BOARD_H__ */

