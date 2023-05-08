/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022/12/25     flyingcys    first version
 */

#ifndef __DRV_USART_H__
#define __DRV_USART_H__

#include <rtthread.h>
#include "rtdevice.h"
#include <rthw.h>

#include "bflb_uart.h"
#include "bflb_gpio.h"

// uart0
#ifdef UART0_TX_USING_GPIO0
#define UART0_GPIO_TX           GPIO_PIN_0
#elif defined(UART0_TX_USING_GPIO1)
#define UART0_GPIO_TX           GPIO_PIN_1
#elif defined(UART0_TX_USING_GPIO2)
#define UART0_GPIO_TX           GPIO_PIN_2
#elif defined(UART0_TX_USING_GPIO3)
#define UART0_GPIO_TX           GPIO_PIN_3
#elif defined(UART0_TX_USING_GPIO4)
#define UART0_GPIO_TX           GPIO_PIN_4
#elif defined(UART0_TX_USING_GPIO5)
#define UART0_GPIO_TX           GPIO_PIN_5
#elif defined(UART0_TX_USING_GPIO6)
#define UART0_GPIO_TX           GPIO_PIN_6
#elif defined(UART0_TX_USING_GPIO7)
#define UART0_GPIO_TX           GPIO_PIN_7
#elif defined(UART0_TX_USING_GPIO8)
#define UART0_GPIO_TX           GPIO_PIN_8
#elif defined(UART0_TX_USING_GPIO9)
#define UART0_GPIO_TX           GPIO_PIN_9
#elif defined(UART0_TX_USING_GPIO10)
#define UART0_GPIO_TX           GPIO_PIN_10
#elif defined(UART0_TX_USING_GPIO11)
#define UART0_GPIO_TX           GPIO_PIN_11
#elif defined(UART0_TX_USING_GPIO12)
#define UART0_GPIO_TX           GPIO_PIN_12
#elif defined(UART0_TX_USING_GPIO13)
#define UART0_GPIO_TX           GPIO_PIN_13
#elif defined(UART0_TX_USING_GPIO14)
#define UART0_GPIO_TX           GPIO_PIN_14
#elif defined(UART0_TX_USING_GPIO15)
#define UART0_GPIO_TX           GPIO_PIN_15
#elif defined(UART0_TX_USING_GPIO16)
#define UART0_GPIO_TX           GPIO_PIN_16
#elif defined(UART0_TX_USING_GPIO17)
#define UART0_GPIO_TX           GPIO_PIN_17
#elif defined(UART0_TX_USING_GPIO18)
#define UART0_GPIO_TX           GPIO_PIN_18
#elif defined(UART0_TX_USING_GPIO19)
#define UART0_GPIO_TX           GPIO_PIN_19
#elif defined(UART0_TX_USING_GPIO20)
#define UART0_GPIO_TX           GPIO_PIN_20
#elif defined(UART0_TX_USING_GPIO21)
#define UART0_GPIO_TX           GPIO_PIN_21
#elif defined(UART0_TX_USING_GPIO22)
#define UART0_GPIO_TX           GPIO_PIN_22
#elif defined(UART0_TX_USING_GPIO23)
#define UART0_GPIO_TX           GPIO_PIN_23
#elif defined(UART0_TX_USING_GPIO24)
#define UART0_GPIO_TX           GPIO_PIN_24
#elif defined(UART0_TX_USING_GPIO25)
#define UART0_GPIO_TX           GPIO_PIN_25
#elif defined(UART0_TX_USING_GPIO26)
#define UART0_GPIO_TX           GPIO_PIN_26
#elif defined(UART0_TX_USING_GPIO27)
#define UART0_GPIO_TX           GPIO_PIN_27
#elif defined(UART0_TX_USING_GPIO28)
#define UART0_GPIO_TX           GPIO_PIN_28
#elif defined(UART0_TX_USING_GPIO29)
#define UART0_GPIO_TX           GPIO_PIN_29
#elif defined(UART0_TX_USING_GPIO30)
#define UART0_GPIO_TX           GPIO_PIN_30
#elif defined(UART0_TX_USING_GPIO31)
#define UART0_GPIO_TX           GPIO_PIN_31
#elif defined(UART0_TX_USING_GPIO32)
#define UART0_GPIO_TX           GPIO_PIN_32
#elif defined(UART0_TX_USING_GPIO33)
#define UART0_GPIO_TX           GPIO_PIN_33
#elif defined(UART0_TX_USING_GPIO34)
#define UART0_GPIO_TX           GPIO_PIN_34
#elif defined(UART0_TX_USING_GPIO35)
#define UART0_GPIO_TX           GPIO_PIN_35
#elif defined(UART0_TX_USING_GPIO36)
#define UART0_GPIO_TX           GPIO_PIN_36
#elif defined(UART0_TX_USING_GPIO37)
#define UART0_GPIO_TX           GPIO_PIN_37
#elif defined(UART0_TX_USING_GPIO38)
#define UART0_GPIO_TX           GPIO_PIN_38
#elif defined(UART0_TX_USING_GPIO39)
#define UART0_GPIO_TX           GPIO_PIN_39
#elif defined(UART0_TX_USING_GPIO44)
#define UART0_GPIO_TX           GPIO_PIN_44
#elif defined(UART0_TX_USING_GPIO45)
#define UART0_GPIO_TX           GPIO_PIN_45
#endif

#ifdef UART0_RX_USING_GPIO0
#define UART0_GPIO_RX           GPIO_PIN_0
#elif defined(UART0_RX_USING_GPIO1)
#define UART0_GPIO_RX           GPIO_PIN_1
#elif defined(UART0_RX_USING_GPIO2)
#define UART0_GPIO_RX           GPIO_PIN_2
#elif defined(UART0_RX_USING_GPIO3)
#define UART0_GPIO_RX           GPIO_PIN_3
#elif defined(UART0_RX_USING_GPIO4)
#define UART0_GPIO_RX           GPIO_PIN_4
#elif defined(UART0_RX_USING_GPIO5)
#define UART0_GPIO_RX           GPIO_PIN_5
#elif defined(UART0_RX_USING_GPIO6)
#define UART0_GPIO_RX           GPIO_PIN_6
#elif defined(UART0_RX_USING_GPIO7)
#define UART0_GPIO_RX           GPIO_PIN_7
#elif defined(UART0_RX_USING_GPIO8)
#define UART0_GPIO_RX           GPIO_PIN_8
#elif defined(UART0_RX_USING_GPIO9)
#define UART0_GPIO_RX           GPIO_PIN_9
#elif defined(UART0_RX_USING_GPIO10)
#define UART0_GPIO_RX           GPIO_PIN_10
#elif defined(UART0_RX_USING_GPIO11)
#define UART0_GPIO_RX           GPIO_PIN_11
#elif defined(UART0_RX_USING_GPIO12)
#define UART0_GPIO_RX           GPIO_PIN_12
#elif defined(UART0_RX_USING_GPIO13)
#define UART0_GPIO_RX           GPIO_PIN_13
#elif defined(UART0_RX_USING_GPIO14)
#define UART0_GPIO_RX           GPIO_PIN_14
#elif defined(UART0_RX_USING_GPIO15)
#define UART0_GPIO_RX           GPIO_PIN_15
#elif defined(UART0_RX_USING_GPIO16)
#define UART0_GPIO_RX           GPIO_PIN_16
#elif defined(UART0_RX_USING_GPIO17)
#define UART0_GPIO_RX           GPIO_PIN_17
#elif defined(UART0_RX_USING_GPIO18)
#define UART0_GPIO_RX           GPIO_PIN_18
#elif defined(UART0_RX_USING_GPIO19)
#define UART0_GPIO_RX           GPIO_PIN_19
#elif defined(UART0_RX_USING_GPIO20)
#define UART0_GPIO_RX           GPIO_PIN_20
#elif defined(UART0_RX_USING_GPIO21)
#define UART0_GPIO_RX           GPIO_PIN_21
#elif defined(UART0_RX_USING_GPIO22)
#define UART0_GPIO_RX           GPIO_PIN_22
#elif defined(UART0_RX_USING_GPIO23)
#define UART0_GPIO_RX           GPIO_PIN_23
#elif defined(UART0_RX_USING_GPIO24)
#define UART0_GPIO_RX           GPIO_PIN_24
#elif defined(UART0_RX_USING_GPIO25)
#define UART0_GPIO_RX           GPIO_PIN_25
#elif defined(UART0_RX_USING_GPIO26)
#define UART0_GPIO_RX           GPIO_PIN_26
#elif defined(UART0_RX_USING_GPIO27)
#define UART0_GPIO_RX           GPIO_PIN_27
#elif defined(UART0_RX_USING_GPIO28)
#define UART0_GPIO_RX           GPIO_PIN_28
#elif defined(UART0_RX_USING_GPIO29)
#define UART0_GPIO_RX           GPIO_PIN_29
#elif defined(UART0_RX_USING_GPIO30)
#define UART0_GPIO_RX           GPIO_PIN_30
#elif defined(UART0_RX_USING_GPIO31)
#define UART0_GPIO_RX           GPIO_PIN_31
#elif defined(UART0_RX_USING_GPIO31)
#define UART0_GPIO_RX           GPIO_PIN_32
#elif defined(UART0_RX_USING_GPIO33)
#define UART0_GPIO_RX           GPIO_PIN_33
#elif defined(UART0_RX_USING_GPIO34)
#define UART0_GPIO_RX           GPIO_PIN_34
#elif defined(UART0_RX_USING_GPIO35)
#define UART0_GPIO_RX           GPIO_PIN_35
#elif defined(UART0_RX_USING_GPIO36)
#define UART0_GPIO_RX           GPIO_PIN_36
#elif defined(UART0_RX_USING_GPIO37)
#define UART0_GPIO_RX           GPIO_PIN_37
#elif defined(UART0_RX_USING_GPIO38)
#define UART0_GPIO_RX           GPIO_PIN_38
#elif defined(UART0_RX_USING_GPIO39)
#define UART0_GPIO_RX           GPIO_PIN_39
#elif defined(UART0_RX_USING_GPIO44)
#define UART0_GPIO_RX           GPIO_PIN_44
#elif defined(UART0_RX_USING_GPIO45)
#define UART0_GPIO_RX           GPIO_PIN_45
#endif

// uart1
#ifdef UART1_TX_USING_GPIO0
#define UART1_GPIO_TX           GPIO_PIN_0
#elif defined(UART1_TX_USING_GPIO1)
#define UART1_GPIO_TX           GPIO_PIN_1
#elif defined(UART1_TX_USING_GPIO2)
#define UART1_GPIO_TX           GPIO_PIN_2
#elif defined(UART1_TX_USING_GPIO3)
#define UART1_GPIO_TX           GPIO_PIN_3
#elif defined(UART1_TX_USING_GPIO4)
#define UART1_GPIO_TX           GPIO_PIN_4
#elif defined(UART1_TX_USING_GPIO5)
#define UART1_GPIO_TX           GPIO_PIN_5
#elif defined(UART1_TX_USING_GPIO6)
#define UART1_GPIO_TX           GPIO_PIN_6
#elif defined(UART1_TX_USING_GPIO7)
#define UART1_GPIO_TX           GPIO_PIN_7
#elif defined(UART1_TX_USING_GPIO8)
#define UART1_GPIO_TX           GPIO_PIN_8
#elif defined(UART1_TX_USING_GPIO9)
#define UART1_GPIO_TX           GPIO_PIN_9
#elif defined(UART1_TX_USING_GPIO10)
#define UART1_GPIO_TX           GPIO_PIN_10
#elif defined(UART1_TX_USING_GPIO11)
#define UART1_GPIO_TX           GPIO_PIN_11
#elif defined(UART1_TX_USING_GPIO12)
#define UART1_GPIO_TX           GPIO_PIN_12
#elif defined(UART1_TX_USING_GPIO13)
#define UART1_GPIO_TX           GPIO_PIN_13
#elif defined(UART1_TX_USING_GPIO14)
#define UART1_GPIO_TX           GPIO_PIN_14
#elif defined(UART1_TX_USING_GPIO15)
#define UART1_GPIO_TX           GPIO_PIN_15
#elif defined(UART1_TX_USING_GPIO16)
#define UART1_GPIO_TX           GPIO_PIN_16
#elif defined(UART1_TX_USING_GPIO17)
#define UART1_GPIO_TX           GPIO_PIN_17
#elif defined(UART1_TX_USING_GPIO18)
#define UART1_GPIO_TX           GPIO_PIN_18
#elif defined(UART1_TX_USING_GPIO19)
#define UART1_GPIO_TX           GPIO_PIN_19
#elif defined(UART1_TX_USING_GPIO20)
#define UART1_GPIO_TX           GPIO_PIN_20
#elif defined(UART1_TX_USING_GPIO21)
#define UART1_GPIO_TX           GPIO_PIN_21
#elif defined(UART1_TX_USING_GPIO22)
#define UART1_GPIO_TX           GPIO_PIN_22
#elif defined(UART1_TX_USING_GPIO23)
#define UART1_GPIO_TX           GPIO_PIN_23
#elif defined(UART1_TX_USING_GPIO24)
#define UART1_GPIO_TX           GPIO_PIN_24
#elif defined(UART1_TX_USING_GPIO25)
#define UART1_GPIO_TX           GPIO_PIN_25
#elif defined(UART1_TX_USING_GPIO26)
#define UART1_GPIO_TX           GPIO_PIN_26
#elif defined(UART1_TX_USING_GPIO27)
#define UART1_GPIO_TX           GPIO_PIN_27
#elif defined(UART1_TX_USING_GPIO28)
#define UART1_GPIO_TX           GPIO_PIN_28
#elif defined(UART1_TX_USING_GPIO29)
#define UART1_GPIO_TX           GPIO_PIN_29
#elif defined(UART1_TX_USING_GPIO30)
#define UART1_GPIO_TX           GPIO_PIN_30
#elif defined(UART1_TX_USING_GPIO31)
#define UART1_GPIO_TX           GPIO_PIN_31
#elif defined(UART1_TX_USING_GPIO32)
#define UART1_GPIO_TX           GPIO_PIN_32
#elif defined(UART1_TX_USING_GPIO33)
#define UART1_GPIO_TX           GPIO_PIN_33
#elif defined(UART1_TX_USING_GPIO34)
#define UART1_GPIO_TX           GPIO_PIN_34
#elif defined(UART1_TX_USING_GPIO35)
#define UART1_GPIO_TX           GPIO_PIN_35
#elif defined(UART1_TX_USING_GPIO36)
#define UART1_GPIO_TX           GPIO_PIN_36
#elif defined(UART1_TX_USING_GPIO37)
#define UART1_GPIO_TX           GPIO_PIN_37
#elif defined(UART1_TX_USING_GPIO38)
#define UART1_GPIO_TX           GPIO_PIN_38
#elif defined(UART1_TX_USING_GPIO39)
#define UART1_GPIO_TX           GPIO_PIN_39
#elif defined(UART1_TX_USING_GPIO44)
#define UART1_GPIO_TX           GPIO_PIN_44
#elif defined(UART1_TX_USING_GPIO45)
#define UART1_GPIO_TX           GPIO_PIN_45
#endif

#ifdef UART1_RX_USING_GPIO0
#define UART1_GPIO_RX           GPIO_PIN_0
#elif defined(UART1_RX_USING_GPIO1)
#define UART1_GPIO_RX           GPIO_PIN_1
#elif defined(UART1_RX_USING_GPIO2)
#define UART1_GPIO_RX           GPIO_PIN_2
#elif defined(UART1_RX_USING_GPIO3)
#define UART1_GPIO_RX           GPIO_PIN_3
#elif defined(UART1_RX_USING_GPIO4)
#define UART1_GPIO_RX           GPIO_PIN_4
#elif defined(UART1_RX_USING_GPIO5)
#define UART1_GPIO_RX           GPIO_PIN_5
#elif defined(UART1_RX_USING_GPIO6)
#define UART1_GPIO_RX           GPIO_PIN_6
#elif defined(UART1_RX_USING_GPIO7)
#define UART1_GPIO_RX           GPIO_PIN_7
#elif defined(UART1_RX_USING_GPIO8)
#define UART1_GPIO_RX           GPIO_PIN_8
#elif defined(UART1_RX_USING_GPIO9)
#define UART1_GPIO_RX           GPIO_PIN_9
#elif defined(UART1_RX_USING_GPIO10)
#define UART1_GPIO_RX           GPIO_PIN_10
#elif defined(UART1_RX_USING_GPIO11)
#define UART1_GPIO_RX           GPIO_PIN_11
#elif defined(UART1_RX_USING_GPIO12)
#define UART1_GPIO_RX           GPIO_PIN_12
#elif defined(UART1_RX_USING_GPIO13)
#define UART1_GPIO_RX           GPIO_PIN_13
#elif defined(UART1_RX_USING_GPIO14)
#define UART1_GPIO_RX           GPIO_PIN_14
#elif defined(UART1_RX_USING_GPIO15)
#define UART1_GPIO_RX           GPIO_PIN_15
#elif defined(UART1_RX_USING_GPIO16)
#define UART1_GPIO_RX           GPIO_PIN_16
#elif defined(UART1_RX_USING_GPIO17)
#define UART1_GPIO_RX           GPIO_PIN_17
#elif defined(UART1_RX_USING_GPIO18)
#define UART1_GPIO_RX           GPIO_PIN_18
#elif defined(UART1_RX_USING_GPIO19)
#define UART1_GPIO_RX           GPIO_PIN_19
#elif defined(UART1_RX_USING_GPIO20)
#define UART1_GPIO_RX           GPIO_PIN_20
#elif defined(UART1_RX_USING_GPIO21)
#define UART1_GPIO_RX           GPIO_PIN_21
#elif defined(UART1_RX_USING_GPIO22)
#define UART1_GPIO_RX           GPIO_PIN_22
#elif defined(UART1_RX_USING_GPIO23)
#define UART1_GPIO_RX           GPIO_PIN_23
#elif defined(UART1_RX_USING_GPIO24)
#define UART1_GPIO_RX           GPIO_PIN_24
#elif defined(UART1_RX_USING_GPIO25)
#define UART1_GPIO_RX           GPIO_PIN_25
#elif defined(UART1_RX_USING_GPIO26)
#define UART1_GPIO_RX           GPIO_PIN_26
#elif defined(UART1_RX_USING_GPIO27)
#define UART1_GPIO_RX           GPIO_PIN_27
#elif defined(UART1_RX_USING_GPIO28)
#define UART1_GPIO_RX           GPIO_PIN_28
#elif defined(UART1_RX_USING_GPIO29)
#define UART1_GPIO_RX           GPIO_PIN_29
#elif defined(UART1_RX_USING_GPIO30)
#define UART1_GPIO_RX           GPIO_PIN_30
#elif defined(UART1_RX_USING_GPIO31)
#define UART1_GPIO_RX           GPIO_PIN_31
#elif defined(UART1_RX_USING_GPIO31)
#define UART1_GPIO_RX           GPIO_PIN_32
#elif defined(UART1_RX_USING_GPIO33)
#define UART1_GPIO_RX           GPIO_PIN_33
#elif defined(UART1_RX_USING_GPIO34)
#define UART1_GPIO_RX           GPIO_PIN_34
#elif defined(UART1_RX_USING_GPIO35)
#define UART1_GPIO_RX           GPIO_PIN_35
#elif defined(UART1_RX_USING_GPIO36)
#define UART1_GPIO_RX           GPIO_PIN_36
#elif defined(UART1_RX_USING_GPIO37)
#define UART1_GPIO_RX           GPIO_PIN_37
#elif defined(UART1_RX_USING_GPIO38)
#define UART1_GPIO_RX           GPIO_PIN_38
#elif defined(UART1_RX_USING_GPIO39)
#define UART1_GPIO_RX           GPIO_PIN_39
#elif defined(UART1_RX_USING_GPIO44)
#define UART1_GPIO_RX           GPIO_PIN_44
#elif defined(UART1_RX_USING_GPIO45)
#define UART1_GPIO_RX           GPIO_PIN_45
#endif

// uart2
#ifdef UART2_TX_USING_GPIO0
#define UART2_GPIO_TX           GPIO_PIN_0
#elif defined(UART2_TX_USING_GPIO1)
#define UART2_GPIO_TX           GPIO_PIN_1
#elif defined(UART2_TX_USING_GPIO2)
#define UART2_GPIO_TX           GPIO_PIN_2
#elif defined(UART2_TX_USING_GPIO3)
#define UART2_GPIO_TX           GPIO_PIN_3
#elif defined(UART2_TX_USING_GPIO4)
#define UART2_GPIO_TX           GPIO_PIN_4
#elif defined(UART2_TX_USING_GPIO5)
#define UART2_GPIO_TX           GPIO_PIN_5
#elif defined(UART2_TX_USING_GPIO6)
#define UART2_GPIO_TX           GPIO_PIN_6
#elif defined(UART2_TX_USING_GPIO7)
#define UART2_GPIO_TX           GPIO_PIN_7
#elif defined(UART2_TX_USING_GPIO8)
#define UART2_GPIO_TX           GPIO_PIN_8
#elif defined(UART2_TX_USING_GPIO9)
#define UART2_GPIO_TX           GPIO_PIN_9
#elif defined(UART2_TX_USING_GPIO10)
#define UART2_GPIO_TX           GPIO_PIN_10
#elif defined(UART2_TX_USING_GPIO11)
#define UART2_GPIO_TX           GPIO_PIN_11
#elif defined(UART2_TX_USING_GPIO12)
#define UART2_GPIO_TX           GPIO_PIN_12
#elif defined(UART2_TX_USING_GPIO13)
#define UART2_GPIO_TX           GPIO_PIN_13
#elif defined(UART2_TX_USING_GPIO14)
#define UART2_GPIO_TX           GPIO_PIN_14
#elif defined(UART2_TX_USING_GPIO15)
#define UART2_GPIO_TX           GPIO_PIN_15
#elif defined(UART2_TX_USING_GPIO16)
#define UART2_GPIO_TX           GPIO_PIN_16
#elif defined(UART2_TX_USING_GPIO17)
#define UART2_GPIO_TX           GPIO_PIN_17
#elif defined(UART2_TX_USING_GPIO18)
#define UART2_GPIO_TX           GPIO_PIN_18
#elif defined(UART2_TX_USING_GPIO19)
#define UART2_GPIO_TX           GPIO_PIN_19
#elif defined(UART2_TX_USING_GPIO20)
#define UART2_GPIO_TX           GPIO_PIN_20
#elif defined(UART2_TX_USING_GPIO21)
#define UART2_GPIO_TX           GPIO_PIN_21
#elif defined(UART2_TX_USING_GPIO22)
#define UART2_GPIO_TX           GPIO_PIN_22
#elif defined(UART2_TX_USING_GPIO23)
#define UART2_GPIO_TX           GPIO_PIN_23
#elif defined(UART2_TX_USING_GPIO24)
#define UART2_GPIO_TX           GPIO_PIN_24
#elif defined(UART2_TX_USING_GPIO25)
#define UART2_GPIO_TX           GPIO_PIN_25
#elif defined(UART2_TX_USING_GPIO26)
#define UART2_GPIO_TX           GPIO_PIN_26
#elif defined(UART2_TX_USING_GPIO27)
#define UART2_GPIO_TX           GPIO_PIN_27
#elif defined(UART2_TX_USING_GPIO28)
#define UART2_GPIO_TX           GPIO_PIN_28
#elif defined(UART2_TX_USING_GPIO29)
#define UART2_GPIO_TX           GPIO_PIN_29
#elif defined(UART2_TX_USING_GPIO30)
#define UART2_GPIO_TX           GPIO_PIN_30
#elif defined(UART2_TX_USING_GPIO31)
#define UART2_GPIO_TX           GPIO_PIN_31
#elif defined(UART2_TX_USING_GPIO32)
#define UART2_GPIO_TX           GPIO_PIN_32
#elif defined(UART2_TX_USING_GPIO33)
#define UART2_GPIO_TX           GPIO_PIN_33
#elif defined(UART2_TX_USING_GPIO34)
#define UART2_GPIO_TX           GPIO_PIN_34
#elif defined(UART2_TX_USING_GPIO35)
#define UART2_GPIO_TX           GPIO_PIN_35
#elif defined(UART2_TX_USING_GPIO36)
#define UART2_GPIO_TX           GPIO_PIN_36
#elif defined(UART2_TX_USING_GPIO37)
#define UART2_GPIO_TX           GPIO_PIN_37
#elif defined(UART2_TX_USING_GPIO38)
#define UART2_GPIO_TX           GPIO_PIN_38
#elif defined(UART2_TX_USING_GPIO39)
#define UART2_GPIO_TX           GPIO_PIN_39
#elif defined(UART2_TX_USING_GPIO44)
#define UART2_GPIO_TX           GPIO_PIN_44
#elif defined(UART2_TX_USING_GPIO45)
#define UART2_GPIO_TX           GPIO_PIN_45
#endif

#ifdef UART2_RX_USING_GPIO0
#define UART2_GPIO_RX           GPIO_PIN_0
#elif defined(UART2_RX_USING_GPIO1)
#define UART2_GPIO_RX           GPIO_PIN_1
#elif defined(UART2_RX_USING_GPIO2)
#define UART2_GPIO_RX           GPIO_PIN_2
#elif defined(UART2_RX_USING_GPIO3)
#define UART2_GPIO_RX           GPIO_PIN_3
#elif defined(UART2_RX_USING_GPIO4)
#define UART2_GPIO_RX           GPIO_PIN_4
#elif defined(UART2_RX_USING_GPIO5)
#define UART2_GPIO_RX           GPIO_PIN_5
#elif defined(UART2_RX_USING_GPIO6)
#define UART2_GPIO_RX           GPIO_PIN_6
#elif defined(UART2_RX_USING_GPIO7)
#define UART2_GPIO_RX           GPIO_PIN_7
#elif defined(UART2_RX_USING_GPIO8)
#define UART2_GPIO_RX           GPIO_PIN_8
#elif defined(UART2_RX_USING_GPIO9)
#define UART2_GPIO_RX           GPIO_PIN_9
#elif defined(UART2_RX_USING_GPIO10)
#define UART2_GPIO_RX           GPIO_PIN_10
#elif defined(UART2_RX_USING_GPIO11)
#define UART2_GPIO_RX           GPIO_PIN_11
#elif defined(UART2_RX_USING_GPIO12)
#define UART2_GPIO_RX           GPIO_PIN_12
#elif defined(UART2_RX_USING_GPIO13)
#define UART2_GPIO_RX           GPIO_PIN_13
#elif defined(UART2_RX_USING_GPIO14)
#define UART2_GPIO_RX           GPIO_PIN_14
#elif defined(UART2_RX_USING_GPIO15)
#define UART2_GPIO_RX           GPIO_PIN_15
#elif defined(UART2_RX_USING_GPIO16)
#define UART2_GPIO_RX           GPIO_PIN_16
#elif defined(UART2_RX_USING_GPIO17)
#define UART2_GPIO_RX           GPIO_PIN_17
#elif defined(UART2_RX_USING_GPIO18)
#define UART2_GPIO_RX           GPIO_PIN_18
#elif defined(UART2_RX_USING_GPIO19)
#define UART2_GPIO_RX           GPIO_PIN_19
#elif defined(UART2_RX_USING_GPIO20)
#define UART2_GPIO_RX           GPIO_PIN_20
#elif defined(UART2_RX_USING_GPIO21)
#define UART2_GPIO_RX           GPIO_PIN_21
#elif defined(UART2_RX_USING_GPIO22)
#define UART2_GPIO_RX           GPIO_PIN_22
#elif defined(UART2_RX_USING_GPIO23)
#define UART2_GPIO_RX           GPIO_PIN_23
#elif defined(UART2_RX_USING_GPIO24)
#define UART2_GPIO_RX           GPIO_PIN_24
#elif defined(UART2_RX_USING_GPIO25)
#define UART2_GPIO_RX           GPIO_PIN_25
#elif defined(UART2_RX_USING_GPIO26)
#define UART2_GPIO_RX           GPIO_PIN_26
#elif defined(UART2_RX_USING_GPIO27)
#define UART2_GPIO_RX           GPIO_PIN_27
#elif defined(UART2_RX_USING_GPIO28)
#define UART2_GPIO_RX           GPIO_PIN_28
#elif defined(UART2_RX_USING_GPIO29)
#define UART2_GPIO_RX           GPIO_PIN_29
#elif defined(UART2_RX_USING_GPIO30)
#define UART2_GPIO_RX           GPIO_PIN_30
#elif defined(UART2_RX_USING_GPIO31)
#define UART2_GPIO_RX           GPIO_PIN_31
#elif defined(UART2_RX_USING_GPIO31)
#define UART2_GPIO_RX           GPIO_PIN_32
#elif defined(UART2_RX_USING_GPIO33)
#define UART2_GPIO_RX           GPIO_PIN_33
#elif defined(UART2_RX_USING_GPIO34)
#define UART2_GPIO_RX           GPIO_PIN_34
#elif defined(UART2_RX_USING_GPIO35)
#define UART2_GPIO_RX           GPIO_PIN_35
#elif defined(UART2_RX_USING_GPIO36)
#define UART2_GPIO_RX           GPIO_PIN_36
#elif defined(UART2_RX_USING_GPIO37)
#define UART2_GPIO_RX           GPIO_PIN_37
#elif defined(UART2_RX_USING_GPIO38)
#define UART2_GPIO_RX           GPIO_PIN_38
#elif defined(UART2_RX_USING_GPIO39)
#define UART2_GPIO_RX           GPIO_PIN_39
#elif defined(UART2_RX_USING_GPIO44)
#define UART2_GPIO_RX           GPIO_PIN_44
#elif defined(UART2_RX_USING_GPIO45)
#define UART2_GPIO_RX           GPIO_PIN_45
#endif

// uart3
#ifdef UART3_TX_USING_GPIO0
#define UART3_GPIO_TX           GPIO_PIN_0
#elif defined(UART3_TX_USING_GPIO4)
#define UART3_GPIO_TX           GPIO_PIN_4
#elif defined(UART3_TX_USING_GPIO8)
#define UART3_GPIO_TX           GPIO_PIN_8
#elif defined(UART3_TX_USING_GPIO12)
#define UART3_GPIO_TX           GPIO_PIN_12
#elif defined(UART3_TX_USING_GPIO16)
#define UART3_GPIO_TX           GPIO_PIN_16
#elif defined(UART3_TX_USING_GPIO18)
#define UART3_GPIO_TX           GPIO_PIN_18
#elif defined(UART3_TX_USING_GPIO20)
#define UART3_GPIO_TX           GPIO_PIN_20
#elif defined(UART3_TX_USING_GPIO24)
#define UART3_GPIO_TX           GPIO_PIN_24
#elif defined(UART3_TX_USING_GPIO28)
#define UART3_GPIO_TX           GPIO_PIN_28
#elif defined(UART3_TX_USING_GPIO32)
#define UART3_GPIO_TX           GPIO_PIN_32
#elif defined(UART3_TX_USING_GPIO36)
#define UART3_GPIO_TX           GPIO_PIN_36
#elif defined(UART3_TX_USING_GPIO40)
#define UART3_GPIO_TX           GPIO_PIN_40
#elif defined(UART3_TX_USING_GPIO44)
#define UART3_GPIO_TX           GPIO_PIN_44
#endif

#ifdef UART3_RX_USING_GPIO1
#define UART3_GPIO_RX           GPIO_PIN_1
#elif defined(UART3_RX_USING_GPIO5)
#define UART3_GPIO_RX           GPIO_PIN_5
#elif defined(UART3_RX_USING_GPIO9)
#define UART3_GPIO_RX           GPIO_PIN_9
#elif defined(UART3_RX_USING_GPIO13)
#define UART3_GPIO_RX           GPIO_PIN_13
#elif defined(UART3_RX_USING_GPIO17)
#define UART3_GPIO_RX           GPIO_PIN_17
#elif defined(UART3_RX_USING_GPIO21)
#define UART3_GPIO_RX           GPIO_PIN_21
#elif defined(UART3_RX_USING_GPIO25)
#define UART3_GPIO_RX           GPIO_PIN_25
#elif defined(UART3_RX_USING_GPIO29)
#define UART3_GPIO_RX           GPIO_PIN_29
#elif defined(UART3_RX_USING_GPIO33)
#define UART3_GPIO_RX           GPIO_PIN_33
#elif defined(UART3_RX_USING_GPIO37)
#define UART3_GPIO_RX           GPIO_PIN_37
#elif defined(UART3_RX_USING_GPIO41)
#define UART3_GPIO_RX           GPIO_PIN_41
#elif defined(UART3_RX_USING_GPIO45)
#define UART3_GPIO_RX           GPIO_PIN_45
#endif

int rt_hw_uart_init(void);

#endif  /* __DRV_USART_H__ */
