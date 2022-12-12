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
    #define USART1_RX_PORT                  (GPIO_PORT_H)
    #define USART1_RX_PIN                   (GPIO_PIN_13)

    #define USART1_TX_PORT                  (GPIO_PORT_H)
    #define USART1_TX_PIN                   (GPIO_PIN_15)
#endif

#if defined(BSP_USING_UART6)
    #define USART6_RX_PORT                  (GPIO_PORT_H)
    #define USART6_RX_PIN                   (GPIO_PIN_06)

    #define USART6_TX_PORT                  (GPIO_PORT_E)
    #define USART6_TX_PIN                   (GPIO_PIN_06)
#endif

/***********  ADC configure *********/
#if defined(BSP_USING_ADC1)
    #define ADC1_CH_PORT                     (GPIO_PORT_C)
    #define ADC1_CH_PIN                      (GPIO_PIN_00)
#endif

#if defined(BSP_USING_ADC2)
    #define ADC2_CH_PORT                     (GPIO_PORT_C)
    #define ADC2_CH_PIN                      (GPIO_PIN_01)
#endif

#if defined(BSP_USING_ADC3)
    #define ADC3_CH_PORT                     (GPIO_PORT_C)
    #define ADC3_CH_PIN                      (GPIO_PIN_02)
#endif

/***********  CAN configure *********/
#if defined(BSP_USING_CAN1)
    #define CAN1_TX_PORT                     (GPIO_PORT_D)
    #define CAN1_TX_PIN                      (GPIO_PIN_05)
    #define CAN1_TX_PIN_FUNC                 (GPIO_FUNC_60)

    #define CAN1_RX_PORT                     (GPIO_PORT_D)
    #define CAN1_RX_PIN                      (GPIO_PIN_04)
    #define CAN1_RX_PIN_FUNC                 (GPIO_FUNC_61)
#endif

#if defined(BSP_USING_CAN2)
    #define CAN2_TX_PORT                     (GPIO_PORT_D)
    #define CAN2_TX_PIN                      (GPIO_PIN_07)
    #define CAN2_TX_PIN_FUNC                 (GPIO_FUNC_62)

    #define CAN2_RX_PORT                     (GPIO_PORT_D)
    #define CAN2_RX_PIN                      (GPIO_PIN_06)
    #define CAN2_RX_PIN_FUNC                 (GPIO_FUNC_63)
#endif

#endif
