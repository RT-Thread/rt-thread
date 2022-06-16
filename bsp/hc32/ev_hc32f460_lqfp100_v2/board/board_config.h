/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 * 2022-06-16     lianghongquan     use macro definition config adc pin.
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
    #define USART2_RX_PIN                   (GPIO_PIN_03)

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

/***********  CAN configure *********/
#if defined(BSP_USING_CAN1)
    #define CAN1_TX_PORT                     (GPIO_PORT_B)
    #define CAN1_TX_PIN                      (GPIO_PIN_07)
    #define CAN1_TX_PIN_FUNC                 (GPIO_FUNC_50)

    #define CAN1_RX_PORT                     (GPIO_PORT_B)
    #define CAN1_RX_PIN                      (GPIO_PIN_06)
    #define CAN1_RX_PIN_FUNC                 (GPIO_FUNC_51)

    #define CAN_STB_PORT                     (GPIO_PORT_D)
    #define CAN_STB_PIN                      (GPIO_PIN_15)
#endif

/***********  ADC configure *********/
#if defined(BSP_USING_ADC1) || defined(BSP_USING_ADC2)
    #define ADC1_IN0_PORT                   (GPIO_PORT_A)
    #define ADC1_IN0_PIN                    (GPIO_PIN_00)

    #define ADC1_IN1_PORT                   (GPIO_PORT_A)
    #define ADC1_IN1_PIN                    (GPIO_PIN_01)

    #define ADC1_IN2_PORT                   (GPIO_PORT_A)
    #define ADC1_IN2_PIN                    (GPIO_PIN_02)

    #define ADC1_IN3_PORT                   (GPIO_PORT_A)
    #define ADC1_IN3_PIN                    (GPIO_PIN_03)

    #define ADC12_IN4_PORT                  (GPIO_PORT_A)
    #define ADC12_IN4_PIN                   (GPIO_PIN_04)

    #define ADC12_IN5_PORT                  (GPIO_PORT_A)
    #define ADC12_IN5_PIN                   (GPIO_PIN_05)

    #define ADC12_IN6_PORT                  (GPIO_PORT_A)
    #define ADC12_IN6_PIN                   (GPIO_PIN_06)

    #define ADC12_IN7_PORT                  (GPIO_PORT_A)
    #define ADC12_IN7_PIN                   (GPIO_PIN_07)

    #define ADC12_IN8_PORT                  (GPIO_PORT_B)
    #define ADC12_IN8_PIN                   (GPIO_PIN_00)

    #define ADC12_IN9_PORT                  (GPIO_PORT_B)
    #define ADC12_IN9_PIN                   (GPIO_PIN_01)

    #define ADC12_IN10_PORT                 (GPIO_PORT_C)
    #define ADC12_IN10_PIN                  (GPIO_PIN_00)

    #define ADC12_IN11_PORT                 (GPIO_PORT_C)
    #define ADC12_IN11_PIN                  (GPIO_PIN_01)

    #define ADC1_IN12_PORT                  (GPIO_PORT_C)
    #define ADC1_IN12_PIN                   (GPIO_PIN_02)

    #define ADC1_IN13_PORT                  (GPIO_PORT_C)
    #define ADC1_IN13_PIN                   (GPIO_PIN_03)

    #define ADC1_IN14_PORT                  (GPIO_PORT_C)
    #define ADC1_IN14_PIN                   (GPIO_PIN_04)

    #define ADC1_IN15_PORT                  (GPIO_PORT_C)
    #define ADC1_IN15_PIN                   (GPIO_PIN_05)
#endif

#endif
