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

    #define CAN1_STB_FUNC_ENABLE
    #define CAN_STB_PORT                     (GPIO_PORT_D)
    #define CAN_STB_PIN                      (GPIO_PIN_15)
#endif

/***********  ADC configure *********/
#if defined(BSP_USING_ADC1)
    #define ADC1_CH10_PORT                     (GPIO_PORT_C)
    #define ADC1_CH10_PIN                      (GPIO_PIN_00)

    #define ADC1_CH12_PORT                     (GPIO_PORT_C)
    #define ADC1_CH12_PIN                      (GPIO_PIN_02)

    #define ADC1_CH13_PORT                     (GPIO_PORT_C)
    #define ADC1_CH13_PIN                      (GPIO_PIN_03)
#endif

#if defined(BSP_USING_ADC2)
    //ADC2 has 7 channels CH0-CH7. ADC12_IN4-ADC12_IN11 means ADC2 CH0-CH7
    #define ADC2_CH7_PORT                     (GPIO_PORT_C)
    #define ADC2_CH7_PIN                      (GPIO_PIN_01)
#endif

#endif
