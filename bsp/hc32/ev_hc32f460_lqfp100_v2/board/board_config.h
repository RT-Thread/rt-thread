/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */


#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include <rtconfig.h>
#include "hc32_ll.h"
#include "drv_config.h"


/************************ USART port **********************/
#if defined(BSP_USING_UART1)
    #define USART1_RX_PORT                  (GPIO_PORT_C)
    #define USART1_RX_PIN                   (GPIO_PIN_04)

    #define USART1_TX_PORT                  (GPIO_PORT_A)
    #define USART1_TX_PIN                   (GPIO_PIN_07)
#endif

#if defined(BSP_USING_UART2)
    #define USART2_RX_PORT                  (GPIO_PORT_A)
    #define USART2_RX_PIN                   (GPIO_PIN_04)

    #define USART2_TX_PORT                  (GPIO_PORT_A)
    #define USART2_TX_PIN                   (GPIO_PIN_02)
#endif

#if defined(BSP_USING_UART3)
    #define USART3_RX_PORT                  (GPIO_PORT_C)
    #define USART3_RX_PIN                   (GPIO_PIN_13)

    #define USART3_TX_PORT                  (GPIO_PORT_H)
    #define USART3_TX_PIN                   (GPIO_PIN_02)
#endif

#if defined(BSP_USING_UART4)
    #define USART4_RX_PORT                  (GPIO_PORT_B)
    #define USART4_RX_PIN                   (GPIO_PIN_09)

    #define USART4_TX_PORT                  (GPIO_PORT_E)
    #define USART4_TX_PIN                   (GPIO_PIN_06)
#endif

#endif
