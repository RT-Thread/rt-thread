/*
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-09-05     DongBowen    first version
 */

#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include <rtconfig.h>
#include "hc32l196_ddl.h"
#include "hc32l196_gpio.h"
#include "hc32l196_uart.h"
#include "hc32l196_sysctrl.h"

/***********  Port configure *********/
#if defined(BSP_USING_UART0)
    #define UART0_RX_PORT                   GpioPortA
    #define UART0_RX_PIN                    GpioPin10
    #define UART0_RX_AF                     GpioAf1

    #define UART0_TX_PORT                   GpioPortA
    #define UART0_TX_PIN                    GpioPin9
    #define UART0_TX_AF                     GpioAf1
#endif

#if defined(BSP_USING_UART1)
    #define UART1_RX_PORT                   GpioPortA
    #define UART1_RX_PIN                    GpioPin3
    #define UART1_RX_AF                     GpioAf1

    #define UART1_TX_PORT                   GpioPortA
    #define UART1_TX_PIN                    GpioPin2
    #define UART1_TX_AF                     GpioAf1
#endif

#endif
