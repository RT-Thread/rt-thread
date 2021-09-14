/*
 * Copyright (C) 2021, lizhengyang
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author          Notes
 * 2021-09-02      lizhengyang     first version
 */
#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include <rtconfig.h>
#include "hc32_ddl.h"

/***********  Port configure *********/
#if defined(BSP_USING_UART1)
    #define USART1_RX_PORT                  (PortD)
    #define USART1_RX_PIN                   (Pin00)

    #define USART1_TX_PORT                  (PortD)
    #define USART1_TX_PIN                   (Pin01)
#endif

#if defined(BSP_USING_UART2)
    #define USART2_RX_PORT                  (PortC)
    #define USART2_RX_PIN                   (Pin11)

    #define USART2_TX_PORT                  (PortC)
    #define USART2_TX_PIN                   (Pin12)
#endif

#if defined(BSP_USING_UART3)
    #define USART3_RX_PORT                  (PortB)
    #define USART3_RX_PIN                   (Pin08)

    #define USART3_TX_PORT                  (PortB)
    #define USART3_TX_PIN                   (Pin09)
#endif

#if defined(BSP_USING_UART4)
    #define USART4_RX_PORT                  (PortC)
    #define USART4_RX_PIN                   (Pin07)

    #define USART4_TX_PORT                  (PortC)
    #define USART4_TX_PIN                   (Pin06)
#endif

/***********  USART configure *********/
#if defined(BSP_USING_UART1)
    #define USART1_RXERR_INT_IRQn           (Int001_IRQn)
    #define USART1_RXERR_INT_PRIO           (DDL_IRQ_PRIORITY_DEFAULT)

    #define USART1_RX_INT_IRQn              (Int002_IRQn)
    #define USART1_RX_INT_PRIO              (DDL_IRQ_PRIORITY_00)
#endif

#if defined(BSP_USING_UART2)
    #define USART2_RXERR_INT_IRQn           (Int003_IRQn)
    #define USART2_RXERR_INT_PRIO           (DDL_IRQ_PRIORITY_DEFAULT)

    #define USART2_RX_INT_IRQn              (Int004_IRQn)
    #define USART2_RX_INT_PRIO              (DDL_IRQ_PRIORITY_00)
#endif

#if defined(BSP_USING_UART3)
    #define USART3_RXERR_INT_IRQn           (Int005_IRQn)
    #define USART3_RXERR_INT_PRIO           (DDL_IRQ_PRIORITY_DEFAULT)

    #define USART3_RX_INT_IRQn              (Int006_IRQn)
    #define USART3_RX_INT_PRIO              (DDL_IRQ_PRIORITY_00)
#endif

#if defined(BSP_USING_UART4)
    #define USART4_RXERR_INT_IRQn           (Int007_IRQn)
    #define USART4_RXERR_INT_PRIO           (DDL_IRQ_PRIORITY_DEFAULT)

    #define USART4_RX_INT_IRQn              (Int008_IRQn)
    #define USART4_RX_INT_PRIO              (DDL_IRQ_PRIORITY_00)
#endif



/***********  Pin configure *********/
#if defined(RT_USING_PIN)

    #define EXINT0_INT_IRQn                 (Int016_IRQn)
    #define EXINT0_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT1_INT_IRQn                 (Int017_IRQn)
    #define EXINT1_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT2_INT_IRQn                 (Int018_IRQn)
    #define EXINT2_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT3_INT_IRQn                 (Int019_IRQn)
    #define EXINT3_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT4_INT_IRQn                 (Int020_IRQn)
    #define EXINT4_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT5_INT_IRQn                 (Int021_IRQn)
    #define EXINT5_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT6_INT_IRQn                 (Int022_IRQn)
    #define EXINT6_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT7_INT_IRQn                 (Int023_IRQn)
    #define EXINT7_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT8_INT_IRQn                 (Int024_IRQn)
    #define EXINT8_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT9_INT_IRQn                 (Int025_IRQn)
    #define EXINT9_INT_PRIO                 (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT10_INT_IRQn                (Int026_IRQn)
    #define EXINT10_INT_PRIO                (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT11_INT_IRQn                (Int027_IRQn)
    #define EXINT11_INT_PRIO                (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT12_INT_IRQn                (Int028_IRQn)
    #define EXINT12_INT_PRIO                (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT13_INT_IRQn                (Int029_IRQn)
    #define EXINT13_INT_PRIO                (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT14_INT_IRQn                (Int030_IRQn)
    #define EXINT14_INT_PRIO                (DDL_IRQ_PRIORITY_DEFAULT)

    #define EXINT15_INT_IRQn                (Int031_IRQn)
    #define EXINT15_INT_PRIO                (DDL_IRQ_PRIORITY_DEFAULT)

#endif

#endif
