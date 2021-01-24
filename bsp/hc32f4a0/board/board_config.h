/*
 * Copyright (C) 2020, Huada Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-10-30     CDT          first version
 */


#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

#include <rtconfig.h>
#include "hc32_ddl.h"

/***********  Port configure *********/
#if defined(BSP_USING_UART1)
#define USART1_RX_PORT                  (GPIO_PORT_H)
#define USART1_RX_PIN                   (GPIO_PIN_13)

#define USART1_TX_PORT                  (GPIO_PORT_H)
#define USART1_TX_PIN                   (GPIO_PIN_15)
#endif

#if defined(BSP_USING_SPI1)
#define SPI1_NSS_PORT                   (GPIO_PORT_C)
#define SPI1_NSS_PIN                    (GPIO_PIN_07)
#define SPI1_NSS_GPIO_FUNC              (GPIO_FUNC_0_GPO)

#define SPI1_SCK_PORT                   (GPIO_PORT_C)
#define SPI1_SCK_PIN                    (GPIO_PIN_06)
#define SPI1_SCK_GPIO_FUNC              (GPIO_FUNC_40_SPI1_SCK)

#define SPI1_MOSI_PORT                  (GPIO_PORT_B)
#define SPI1_MOSI_PIN                   (GPIO_PIN_13)
#define SPI1_MOSI_GPIO_FUNC             (GPIO_FUNC_41_SPI1_MOSI)

#define SPI1_MISO_PORT                  (GPIO_PORT_B)
#define SPI1_MISO_PIN                   (GPIO_PIN_12)
#define SPI1_MISO_GPIO_FUNC             (GPIO_FUNC_42_SPI1_MISO)
#endif

#if defined(BSP_USING_PWM1)

#if defined(BSP_USING_PWM1_CH1)
#define PWM1_CH1_PORT                   (GPIO_PORT_A)
#define PWM1_CH1_PIN                    (GPIO_PIN_08)
#define PWM1_CH1_FUNC                   (GPIO_FUNC_4_TIMA1_PWM1)
#endif

#if defined(BSP_USING_PWM1_CH2)
#define PWM1_CH2_PORT                   (GPIO_PORT_A)
#define PWM1_CH2_PIN                    (GPIO_PIN_09)
#define PWM1_CH2_FUNC                   (GPIO_FUNC_4_TIMA1_PWM2)
#endif

#endif

#if defined(BSP_USING_PULSE_ENCODER9)
#define PULSE_ENCODER9_CLKA_PORT        (GPIO_PORT_G)
#define PULSE_ENCODER9_CLKA_PIN         (GPIO_PIN_04)
#define PULSE_ENCODER9_CLKA_FUNC        (GPIO_FUNC_4_TIMA9_PWM1)

#define PULSE_ENCODER9_CLKB_PORT        (GPIO_PORT_G)
#define PULSE_ENCODER9_CLKB_PIN         (GPIO_PIN_05)
#define PULSE_ENCODER9_CLKB_FUNC        (GPIO_FUNC_4_TIMA9_PWM2)
#endif

/***********  USART configure *********/
#if defined(BSP_USING_UART1)

#define USART1_RXERR_INT_IRQn           (Int001_IRQn)
#define USART1_RXERR_INT_PRIO           (DDL_IRQ_PRIORITY_DEFAULT)

#define USART1_RX_INT_IRQn              (Int002_IRQn)
#define USART1_RX_INT_PRIO              (DDL_IRQ_PRIORITY_00)

#define USART1_TX_INT_IRQn              (Int003_IRQn)
#define USART1_TX_INT_PRIO              (DDL_IRQ_PRIORITY_DEFAULT)

#if defined(RT_SERIAL_USING_DMA)
#if defined(BSP_UART1_RX_USING_DMA)
#define USART1_RXTO_TMR0_UNIT           (M4_TMR0_1)
#define USART1_RXTO_TMR0_CH             (TMR0_CH_A)
#define USART1_RXTO_INT_IRQn            (Int004_IRQn)
#define USART1_RXTO_INT_PRIO            (DDL_IRQ_PRIORITY_01)

#define USART1_RX_DMA_UNIT              (M4_DMA1)
#define USART1_RX_DMA_CH                (DMA_CH0)
#define USART1_RX_DMA_INT_IRQn          (Int005_IRQn)
#define USART1_RX_DMA_INT_SRC           (INT_DMA1_TC0)
#define USART1_RX_DMA_INT_PRIO          (DDL_IRQ_PRIORITY_01)
#endif

#if defined(BSP_UART1_TX_USING_DMA)
#define USART1_TX_DMA_UNIT              (M4_DMA2)
#define USART1_TX_DMA_CH                (DMA_CH0)

#define USART1_TC_INT_IRQn              (Int006_IRQn)
#define USART1_TC_INT_PRIO              (DDL_IRQ_PRIORITY_DEFAULT)
#endif
#endif

#endif

/***********  Timer configure *********/
#if defined(BSP_USING_TIMER5)
#define TIMER5_CNT_INT_IRQn             (Int092_IRQn)
#define TIMER5_CNT_INT_PRIO             (DDL_IRQ_PRIORITY_DEFAULT)
#endif

#if defined(BSP_USING_TIMER6)
#define TIMER6_CNT_INT_IRQn             (Int093_IRQn)
#define TIMER6_CNT_INT_PRIO             (DDL_IRQ_PRIORITY_DEFAULT)
#endif

/******  Pulse Encoder configure ******/
#if defined(BSP_USING_PULSE_ENCODER9)
#define PULSE_ENCODER9_OVF_INT_IRQn     (Int098_IRQn)
#define PULSE_ENCODER9_OVF_INT_PRIO     (DDL_IRQ_PRIORITY_DEFAULT)

#define PULSE_ENCODER9_UNF_INT_IRQn     (Int099_IRQn)
#define PULSE_ENCODER9_UNF_INT_PRIO     (DDL_IRQ_PRIORITY_DEFAULT)
#endif

/***********  SPI configure *********/
#if defined(BSP_SPI1_TX_USING_DMA)
#define SPI1_TX_DMA_INSTANCE            (M4_DMA1)
#define SPI1_TX_DMA_CHANNEL             (DMA_CH1)
#define SPI1_TX_DMA_IRQn                (Int010_IRQn)
#define SPI1_TX_DMA_INT_SRC             (INT_DMA1_TC1)
#define SPI1_TX_DMA_INT_PRIO            (DDL_IRQ_PRIORITY_DEFAULT)
#endif

#if defined(BSP_SPI1_RX_USING_DMA)
#define SPI1_RX_DMA_INSTANCE            (M4_DMA1)
#define SPI1_RX_DMA_CHANNEL             (DMA_CH2)
#define SPI1_RX_DMA_IRQn                (Int011_IRQn)
#define SPI1_RX_DMA_INT_SRC             (INT_DMA1_TC2)
#define SPI1_RX_DMA_INT_PRIO            (DDL_IRQ_PRIORITY_DEFAULT)
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
