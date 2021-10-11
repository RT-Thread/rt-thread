/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-09-22     AisinoCip    add board.h to this bsp
 */

#ifndef __BOARD_H__
#define __BOARD_H__

#include <rtconfig.h>
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
        #define UART3_RX_DMA_INSTANCE   DMA_Channel2
        #define UART3_RX_DMA_RCC        BIT12
        #define UART3_RX_DMA_IRQ        DMA_IRQn
        #define UART3_RX_DMA_CHANNEL    2
        #define UART3_RX_DMA_REQUEST    REQ29_UART3_RECV
    #endif /* BSP_UART3_RX_USING_DMA */

    #if defined(BSP_UART3_TX_USING_DMA)
        #define UART3_TX_DMA_INSTANCE   DMA_Channel3
        #define UART3_TX_DMA_RCC        BIT12
        #define UART3_TX_DMA_IRQ        DMA_IRQn
        #define UART3_TX_DMA_CHANNEL    3
        #define UART3_TX_DMA_REQUEST    REQ27_UART3_SEND
    #endif /* BSP_UART3_TX_USING_DMA */
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
    #define UART4_TX_PORT           GPIOC
    #define UART4_RX_PORT           GPIOC
    #define UART4_TX_PIN            GPIO_PIN_10
    #define UART4_RX_PIN            GPIO_PIN_11

    #if defined(BSP_UART4_RX_USING_DMA)
        #define UART4_RX_DMA_INSTANCE   DMA_Channel4
        #define UART4_RX_DMA_RCC        BIT12
        #define UART4_RX_DMA_IRQ        DMA_IRQn
        #define UART4_RX_DMA_CHANNEL    4
        #define UART4_RX_DMA_REQUEST    REQ46_UART4_RECV
    #endif /* BSP_UART4_RX_USING_DMA */

    #if defined(BSP_UART4_TX_USING_DMA)
        #define UART4_TX_DMA_INSTANCE   DMA_Channel5
        #define UART4_TX_DMA_RCC        BIT12
        #define UART4_TX_DMA_IRQ        DMA_IRQn
        #define UART4_TX_DMA_CHANNEL    5
        #define UART4_TX_DMA_REQUEST    REQ45_UART4_SEND
    #endif /* BSP_UART4_TX_USING_DMA */
#endif /* BSP_USING_UART4 */
/*-------------------------- UART CONFIG END --------------------------*/

/* board configuration */

void rt_hw_board_init(void);

#endif /* __BOARD_H__ */

