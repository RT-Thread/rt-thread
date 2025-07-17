/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 ch0 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_TX_DMA_INSTANCE           CM_DMA
#define UART1_TX_DMA_CHANNEL            DMA_CH0
#define UART1_TX_DMA_CLOCK              (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define UART1_TX_DMA_TRIG_SELECT        AOS_DMA_0
#define UART1_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH0
#define UART1_TX_DMA_IRQn               BSP_DMA1_CH0_IRQ_NUM
#define UART1_TX_DMA_INT_PRIO           BSP_DMA1_CH0_IRQ_PRIO
#define UART1_TX_DMA_INT_SRC            INT_SRC_DMA_TC0

#elif defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_TX_DMA_INSTANCE            CM_DMA
#define SPI1_TX_DMA_CHANNEL             DMA_CH0
#define SPI1_TX_DMA_CLOCK               (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define SPI1_TX_DMA_TRIG_SELECT         AOS_DMA_0
#define SPI1_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH0
#define SPI1_TX_DMA_IRQn                BSP_DMA1_CH0_IRQ_NUM
#define SPI1_TX_DMA_INT_PRIO            BSP_DMA1_CH0_IRQ_PRIO
#define SPI1_TX_DMA_INT_SRC             INT_SRC_DMA_TC0
#endif

/* DMA1 ch1 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_RX_DMA_INSTANCE           CM_DMA
#define UART1_RX_DMA_CHANNEL            DMA_CH1
#define UART1_RX_DMA_CLOCK              (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define UART1_RX_DMA_TRIG_SELECT        AOS_DMA_1
#define UART1_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH1
#define UART1_RX_DMA_IRQn               BSP_DMA1_CH1_IRQ_NUM
#define UART1_RX_DMA_INT_PRIO           BSP_DMA1_CH1_IRQ_PRIO
#define UART1_RX_DMA_INT_SRC            INT_SRC_DMA_TC1

#elif defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_RX_DMA_INSTANCE            CM_DMA
#define SPI1_RX_DMA_CHANNEL             DMA_CH1
#define SPI1_RX_DMA_CLOCK               (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define SPI1_RX_DMA_TRIG_SELECT         AOS_DMA_1
#define SPI1_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH1
#define SPI1_RX_DMA_IRQn                BSP_DMA1_CH1_IRQ_NUM
#define SPI1_RX_DMA_INT_PRIO            BSP_DMA1_CH1_IRQ_PRIO
#define SPI1_RX_DMA_INT_SRC             INT_SRC_DMA_TC1
#endif

/* DMA1 ch2 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_INSTANCE)
#define UART2_TX_DMA_INSTANCE           CM_DMA
#define UART2_TX_DMA_CHANNEL            DMA_CH2
#define UART2_TX_DMA_CLOCK              (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define UART2_TX_DMA_TRIG_SELECT        AOS_DMA_2
#define UART2_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH2
#define UART2_TX_DMA_IRQn               BSP_DMA1_CH2_IRQ_NUM
#define UART2_TX_DMA_INT_PRIO           BSP_DMA1_CH2_IRQ_PRIO
#define UART2_TX_DMA_INT_SRC            INT_SRC_DMA_TC2

#elif defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_INSTANCE)
#define I2C1_TX_DMA_INSTANCE            CM_DMA
#define I2C1_TX_DMA_CHANNEL             DMA_CH2
#define I2C1_TX_DMA_CLOCK               (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define I2C1_TX_DMA_TRIG_SELECT         AOS_DMA_2
#define I2C1_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH2
#define I2C1_TX_DMA_IRQn                BSP_DMA1_CH2_IRQ_NUM
#define I2C1_TX_DMA_INT_PRIO            BSP_DMA1_CH2_IRQ_PRIO
#define I2C1_TX_DMA_INT_SRC             INT_SRC_DMA_TC2
#endif

/* DMA1 ch3 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_RX_DMA_INSTANCE           CM_DMA
#define UART2_RX_DMA_CHANNEL            DMA_CH3
#define UART2_RX_DMA_CLOCK              (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define UART2_RX_DMA_TRIG_SELECT        AOS_DMA_3
#define UART2_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH3
#define UART2_RX_DMA_IRQn               BSP_DMA1_CH3_IRQ_NUM
#define UART2_RX_DMA_INT_PRIO           BSP_DMA1_CH3_IRQ_PRIO
#define UART2_RX_DMA_INT_SRC            INT_SRC_DMA_TC3

#elif defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_INSTANCE)
#define I2C1_RX_DMA_INSTANCE            CM_DMA
#define I2C1_RX_DMA_CHANNEL             DMA_CH3
#define I2C1_RX_DMA_CLOCK               (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define I2C1_RX_DMA_TRIG_SELECT         AOS_DMA_3
#define I2C1_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH3
#define I2C1_RX_DMA_IRQn                BSP_DMA1_CH3_IRQ_NUM
#define I2C1_RX_DMA_INT_PRIO            BSP_DMA1_CH3_IRQ_PRIO
#define I2C1_RX_DMA_INT_SRC             INT_SRC_DMA_TC3
#endif

/* DMA1 ch4 */
#if defined(BSP_UART3_TX_USING_DMA) && !defined(UART3_TX_DMA_INSTANCE)
#define UART3_TX_DMA_INSTANCE           CM_DMA
#define UART3_TX_DMA_CHANNEL            DMA_CH4
#define UART3_TX_DMA_CLOCK              (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define UART3_TX_DMA_TRIG_SELECT        AOS_DMA_4
#define UART3_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH4
#define UART3_TX_DMA_IRQn               BSP_DMA1_CH4_IRQ_NUM
#define UART3_TX_DMA_INT_PRIO           BSP_DMA1_CH4_IRQ_PRIO
#define UART3_TX_DMA_INT_SRC            INT_SRC_DMA_TC4

#elif defined(BSP_ADC1_USING_DMA) && !defined(ADC1_EOCA_DMA_INSTANCE)
#define ADC1_EOCA_DMA_INSTANCE          CM_DMA
#define ADC1_EOCA_DMA_CHANNEL           DMA_CH4
#define ADC1_EOCA_DMA_CLOCK             (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define ADC1_EOCA_DMA_TRIG_SELECT       AOS_DMA_4
#define ADC1_EOCA_DMA_TRANS_FLAG        DMA_FLAG_TC_CH4
#define ADC1_EOCA_DMA_IRQn              BSP_DMA1_CH4_IRQ_NUM
#define ADC1_EOCA_DMA_INT_PRIO          BSP_DMA1_CH4_IRQ_PRIO
#define ADC1_EOCA_DMA_INT_SRC           INT_SRC_DMA_TC4
#endif

/* DMA1 ch5 */
#if defined(BSP_UART3_RX_USING_DMA) && !defined(UART3_RX_DMA_INSTANCE)
#define UART3_RX_DMA_INSTANCE           CM_DMA
#define UART3_RX_DMA_CHANNEL            DMA_CH5
#define UART3_RX_DMA_CLOCK              (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define UART3_RX_DMA_TRIG_SELECT        AOS_DMA_5
#define UART3_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH5
#define UART3_RX_DMA_IRQn               BSP_DMA1_CH5_IRQ_NUM
#define UART3_RX_DMA_INT_PRIO           BSP_DMA1_CH5_IRQ_PRIO
#define UART3_RX_DMA_INT_SRC            INT_SRC_DMA_TC5

#elif defined(BSP_ADC2_USING_DMA) && !defined(ADC2_EOCA_DMA_INSTANCE)
#define ADC2_EOCA_DMA_INSTANCE          CM_DMA
#define ADC2_EOCA_DMA_CHANNEL           DMA_CH5
#define ADC2_EOCA_DMA_CLOCK             (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define ADC2_EOCA_DMA_TRIG_SELECT       AOS_DMA_5
#define ADC2_EOCA_DMA_TRANS_FLAG        DMA_FLAG_TC_CH5
#define ADC2_EOCA_DMA_IRQn              BSP_DMA1_CH5_IRQ_NUM
#define ADC2_EOCA_DMA_INT_PRIO          BSP_DMA1_CH5_IRQ_PRIO
#define ADC2_EOCA_DMA_INT_SRC           INT_SRC_DMA_TC5
#endif

/* DMA1 ch6 */
#if defined(BSP_UART4_TX_USING_DMA) && !defined(UART4_TX_DMA_INSTANCE)
#define UART4_TX_DMA_INSTANCE           CM_DMA
#define UART4_TX_DMA_CHANNEL            DMA_CH6
#define UART4_TX_DMA_CLOCK              (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define UART4_TX_DMA_TRIG_SELECT        AOS_DMA_6
#define UART4_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH6
#define UART4_TX_DMA_IRQn               BSP_DMA1_CH6_IRQ_NUM
#define UART4_TX_DMA_INT_PRIO           BSP_DMA1_CH6_IRQ_PRIO
#define UART4_TX_DMA_INT_SRC            INT_SRC_DMA_TC6

#elif defined(BSP_ADC3_USING_DMA) && !defined(ADC3_EOCA_DMA_INSTANCE)
#define ADC3_EOCA_DMA_INSTANCE          CM_DMA
#define ADC3_EOCA_DMA_CHANNEL           DMA_CH6
#define ADC3_EOCA_DMA_CLOCK             (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define ADC3_EOCA_DMA_TRIG_SELECT       AOS_DMA_6
#define ADC3_EOCA_DMA_TRANS_FLAG        DMA_FLAG_TC_CH6
#define ADC3_EOCA_DMA_IRQn              BSP_DMA1_CH6_IRQ_NUM
#define ADC3_EOCA_DMA_INT_PRIO          BSP_DMA1_CH6_IRQ_PRIO
#define ADC3_EOCA_DMA_INT_SRC           INT_SRC_DMA_TC6
#endif

/* DMA1 ch7 */
#if defined(BSP_UART4_RX_USING_DMA) && !defined(UART4_RX_DMA_INSTANCE)
#define UART4_RX_DMA_INSTANCE           CM_DMA
#define UART4_RX_DMA_CHANNEL            DMA_CH7
#define UART4_RX_DMA_CLOCK              (PWC_FCG0_DMA | PWC_FCG0_AOS)
#define UART4_RX_DMA_TRIG_SELECT        AOS_DMA_7
#define UART4_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH7
#define UART4_RX_DMA_IRQn               BSP_DMA1_CH7_IRQ_NUM
#define UART4_RX_DMA_INT_PRIO           BSP_DMA1_CH7_IRQ_PRIO
#define UART4_RX_DMA_INT_SRC            INT_SRC_DMA_TC7
#endif

#ifdef __cplusplus
}
#endif

#endif /* __DMA_CONFIG_H__ */
