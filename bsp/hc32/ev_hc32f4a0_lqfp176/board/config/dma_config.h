/*
 * Copyright (C) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-04-28     CDT          first version
 */

#ifndef __DMA_CONFIG_H__
#define __DMA_CONFIG_H__

#include <rtthread.h>
#include "irq_config.h"

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 ch0 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_RX_DMA_INSTANCE            CM_DMA1
#define SPI1_RX_DMA_CHANNEL             DMA_CH0
#define SPI1_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI1_RX_DMA_TRIG_SELECT         AOS_DMA1_0
#define SPI1_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH0
#define SPI1_RX_DMA_IRQn                BSP_DMA1_CH0_IRQ_NUM
#define SPI1_RX_DMA_INT_PRIO            BSP_DMA1_CH0_IRQ_PRIO
#define SPI1_RX_DMA_INT_SRC             INT_SRC_DMA1_TC0
#elif defined(BSP_USING_SDIO1) && !defined(SDIO1_RX_DMA_INSTANCE)
#define SDIO1_RX_DMA_INSTANCE           CM_DMA1
#define SDIO1_RX_DMA_CHANNEL            DMA_CH0
#define SDIO1_RX_DMA_CLOCK              (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SDIO1_RX_DMA_TRIG_SELECT        AOS_DMA1_0
#define SDIO1_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH0
#define SDIO1_RX_DMA_IRQn               BSP_DMA1_CH0_IRQ_NUM
#define SDIO1_RX_DMA_INT_PRIO           BSP_DMA1_CH0_IRQ_PRIO
#define SDIO1_RX_DMA_INT_SRC            INT_SRC_DMA1_TC0
#elif defined(BSP_I2C1_TX_USING_DMA) && !defined(I2C1_TX_DMA_INSTANCE)
#define I2C1_TX_DMA_INSTANCE            CM_DMA1
#define I2C1_TX_DMA_CHANNEL             DMA_CH0
#define I2C1_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define I2C1_TX_DMA_TRIG_SELECT         AOS_DMA1_0
#define I2C1_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH0
#define I2C1_TX_DMA_IRQn                BSP_DMA1_CH0_IRQ_NUM
#define I2C1_TX_DMA_INT_PRIO            BSP_DMA1_CH0_IRQ_PRIO
#define I2C1_TX_DMA_INT_SRC             INT_SRC_DMA1_TC0
#endif

/* DMA1 ch1 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_TX_DMA_INSTANCE            CM_DMA1
#define SPI1_TX_DMA_CHANNEL             DMA_CH1
#define SPI1_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI1_TX_DMA_TRIG_SELECT         AOS_DMA1_1
#define SPI1_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH1
#define SPI1_TX_DMA_IRQn                BSP_DMA1_CH1_IRQ_NUM
#define SPI1_TX_DMA_INT_PRIO            BSP_DMA1_CH1_IRQ_PRIO
#define SPI1_TX_DMA_INT_SRC             INT_SRC_DMA1_TC1
#elif defined(BSP_USING_SDIO1) && !defined(SDIO1_TX_DMA_INSTANCE)
#define SDIO1_TX_DMA_INSTANCE           CM_DMA1
#define SDIO1_TX_DMA_CHANNEL            DMA_CH1
#define SDIO1_TX_DMA_CLOCK              (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SDIO1_TX_DMA_TRIG_SELECT        AOS_DMA1_1
#define SDIO1_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH1
#define SDIO1_TX_DMA_IRQn               BSP_DMA1_CH1_IRQ_NUM
#define SDIO1_TX_DMA_INT_PRIO           BSP_DMA1_CH1_IRQ_PRIO
#define SDIO1_TX_DMA_INT_SRC            INT_SRC_DMA1_TC1
#elif defined(BSP_I2C1_RX_USING_DMA) && !defined(I2C1_RX_DMA_INSTANCE)
#define I2C1_RX_DMA_INSTANCE            CM_DMA1
#define I2C1_RX_DMA_CHANNEL             DMA_CH1
#define I2C1_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define I2C1_RX_DMA_TRIG_SELECT         AOS_DMA1_1
#define I2C1_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH1
#define I2C1_RX_DMA_IRQn                BSP_DMA1_CH1_IRQ_NUM
#define I2C1_RX_DMA_INT_PRIO            BSP_DMA1_CH1_IRQ_PRIO
#define I2C1_RX_DMA_INT_SRC             INT_SRC_DMA1_TC1
#endif

/* DMA1 ch2 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_RX_DMA_INSTANCE            CM_DMA1
#define SPI2_RX_DMA_CHANNEL             DMA_CH2
#define SPI2_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI2_RX_DMA_TRIG_SELECT         AOS_DMA1_2
#define SPI2_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH2
#define SPI2_RX_DMA_IRQn                BSP_DMA1_CH2_IRQ_NUM
#define SPI2_RX_DMA_INT_PRIO            BSP_DMA1_CH2_IRQ_PRIO
#define SPI2_RX_DMA_INT_SRC             INT_SRC_DMA1_TC2
#elif defined(BSP_USING_SDIO2) && !defined(SDIO2_RX_DMA_INSTANCE)
#define SDIO2_RX_DMA_INSTANCE           CM_DMA1
#define SDIO2_RX_DMA_CHANNEL            DMA_CH2
#define SDIO2_RX_DMA_CLOCK              (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SDIO2_RX_DMA_TRIG_SELECT        AOS_DMA1_2
#define SDIO2_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH2
#define SDIO2_RX_DMA_IRQn               BSP_DMA1_CH2_IRQ_NUM
#define SDIO2_RX_DMA_INT_PRIO           BSP_DMA1_CH2_IRQ_PRIO
#define SDIO2_RX_DMA_INT_SRC            INT_SRC_DMA1_TC2
#elif defined(BSP_I2C2_TX_USING_DMA) && !defined(I2C2_TX_DMA_INSTANCE)
#define I2C2_TX_DMA_INSTANCE            CM_DMA1
#define I2C2_TX_DMA_CHANNEL             DMA_CH2
#define I2C2_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define I2C2_TX_DMA_TRIG_SELECT         AOS_DMA1_2
#define I2C2_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH2
#define I2C2_TX_DMA_IRQn                BSP_DMA1_CH2_IRQ_NUM
#define I2C2_TX_DMA_INT_PRIO            BSP_DMA1_CH2_IRQ_PRIO
#define I2C2_TX_DMA_INT_SRC             INT_SRC_DMA1_TC2
#endif

/* DMA1 ch3 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_TX_DMA_INSTANCE            CM_DMA1
#define SPI2_TX_DMA_CHANNEL             DMA_CH3
#define SPI2_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI2_TX_DMA_TRIG_SELECT         AOS_DMA1_3
#define SPI2_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH3
#define SPI2_TX_DMA_IRQn                BSP_DMA1_CH3_IRQ_NUM
#define SPI2_TX_DMA_INT_PRIO            BSP_DMA1_CH3_IRQ_PRIO
#define SPI2_TX_DMA_INT_SRC             INT_SRC_DMA1_TC3
#elif defined(BSP_USING_SDIO2) && !defined(SDIO2_TX_DMA_INSTANCE)
#define SDIO2_TX_DMA_INSTANCE           CM_DMA1
#define SDIO2_TX_DMA_CHANNEL            DMA_CH3
#define SDIO2_TX_DMA_CLOCK              (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SDIO2_TX_DMA_TRIG_SELECT        AOS_DMA1_3
#define SDIO2_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH3
#define SDIO2_TX_DMA_IRQn               BSP_DMA1_CH3_IRQ_NUM
#define SDIO2_TX_DMA_INT_PRIO           BSP_DMA1_CH3_IRQ_PRIO
#define SDIO2_TX_DMA_INT_SRC            INT_SRC_DMA1_TC3
#elif defined(BSP_USING_QSPI) && !defined(QSPI_DMA_INSTANCE)
#define QSPI_DMA_INSTANCE               CM_DMA1
#define QSPI_DMA_CHANNEL                DMA_CH3
#define QSPI_DMA_CLOCK                  (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define QSPI_DMA_TRIG_SELECT            AOS_DMA1_3
#define QSPI_DMA_TRANS_FLAG             DMA_FLAG_TC_CH3
#define QSPI_DMA_IRQn                   BSP_DMA1_CH3_IRQ_NUM
#define QSPI_DMA_INT_PRIO               BSP_DMA1_CH3_IRQ_PRIO
#define QSPI_DMA_INT_SRC                INT_SRC_DMA1_TC3
#elif defined(BSP_I2C2_RX_USING_DMA) && !defined(I2C2_RX_DMA_INSTANCE)
#define I2C2_RX_DMA_INSTANCE            CM_DMA1
#define I2C2_RX_DMA_CHANNEL             DMA_CH3
#define I2C2_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define I2C2_RX_DMA_TRIG_SELECT         AOS_DMA1_3
#define I2C2_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH3
#define I2C2_RX_DMA_IRQn                BSP_DMA1_CH3_IRQ_NUM
#define I2C2_RX_DMA_INT_PRIO            BSP_DMA1_CH3_IRQ_PRIO
#define I2C2_RX_DMA_INT_SRC             INT_SRC_DMA1_TC3
#endif

/* DMA1 ch4 */
#if defined(BSP_SPI3_RX_USING_DMA) && !defined(SPI3_RX_DMA_INSTANCE)
#define SPI3_RX_DMA_INSTANCE            CM_DMA1
#define SPI3_RX_DMA_CHANNEL             DMA_CH4
#define SPI3_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI3_RX_DMA_TRIG_SELECT         AOS_DMA1_4
#define SPI3_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH4
#define SPI3_RX_DMA_IRQn                BSP_DMA1_CH4_IRQ_NUM
#define SPI3_RX_DMA_INT_PRIO            BSP_DMA1_CH4_IRQ_PRIO
#define SPI3_RX_DMA_INT_SRC             INT_SRC_DMA1_TC4
#elif defined(BSP_I2C3_TX_USING_DMA) && !defined(I2C3_TX_DMA_INSTANCE)
#define I2C3_TX_DMA_INSTANCE            CM_DMA1
#define I2C3_TX_DMA_CHANNEL             DMA_CH4
#define I2C3_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define I2C3_TX_DMA_TRIG_SELECT         AOS_DMA1_4
#define I2C3_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH4
#define I2C3_TX_DMA_IRQn                BSP_DMA1_CH4_IRQ_NUM
#define I2C3_TX_DMA_INT_PRIO            BSP_DMA1_CH4_IRQ_PRIO
#define I2C3_TX_DMA_INT_SRC             INT_SRC_DMA1_TC4
#endif

/* DMA1 ch5 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_INSTANCE)
#define SPI3_TX_DMA_INSTANCE            CM_DMA1
#define SPI3_TX_DMA_CHANNEL             DMA_CH5
#define SPI3_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI3_TX_DMA_TRIG_SELECT         AOS_DMA1_5
#define SPI3_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH5
#define SPI3_TX_DMA_IRQn                BSP_DMA1_CH5_IRQ_NUM
#define SPI3_TX_DMA_INT_PRIO            BSP_DMA1_CH5_IRQ_PRIO
#define SPI3_TX_DMA_INT_SRC             INT_SRC_DMA1_TC5
#elif defined(BSP_I2C3_RX_USING_DMA) && !defined(I2C3_RX_DMA_INSTANCE)
#define I2C3_RX_DMA_INSTANCE            CM_DMA1
#define I2C3_RX_DMA_CHANNEL             DMA_CH5
#define I2C3_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define I2C3_RX_DMA_TRIG_SELECT         AOS_DMA1_5
#define I2C3_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH5
#define I2C3_RX_DMA_IRQn                BSP_DMA1_CH5_IRQ_NUM
#define I2C3_RX_DMA_INT_PRIO            BSP_DMA1_CH5_IRQ_PRIO
#define I2C3_RX_DMA_INT_SRC             INT_SRC_DMA1_TC5
#endif

/* DMA1 ch6 */
#if defined(BSP_SPI4_RX_USING_DMA) && !defined(SPI4_RX_DMA_INSTANCE)
#define SPI4_RX_DMA_INSTANCE            CM_DMA1
#define SPI4_RX_DMA_CHANNEL             DMA_CH6
#define SPI4_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI4_RX_DMA_TRIG_SELECT         AOS_DMA1_6
#define SPI4_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH6
#define SPI4_RX_DMA_IRQn                BSP_DMA1_CH6_IRQ_NUM
#define SPI4_RX_DMA_INT_PRIO            BSP_DMA1_CH6_IRQ_PRIO
#define SPI4_RX_DMA_INT_SRC             INT_SRC_DMA1_TC6
#elif defined(BSP_I2C4_TX_USING_DMA) && !defined(I2C4_TX_DMA_INSTANCE)
#define I2C4_TX_DMA_INSTANCE            CM_DMA1
#define I2C4_TX_DMA_CHANNEL             DMA_CH6
#define I2C4_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define I2C4_TX_DMA_TRIG_SELECT         AOS_DMA1_6
#define I2C4_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH6
#define I2C4_TX_DMA_IRQn                BSP_DMA1_CH6_IRQ_NUM
#define I2C4_TX_DMA_INT_PRIO            BSP_DMA1_CH6_IRQ_PRIO
#define I2C4_TX_DMA_INT_SRC             INT_SRC_DMA1_TC6
#endif

/* DMA1 ch7 */
#if defined(BSP_SPI4_TX_USING_DMA) && !defined(SPI4_TX_DMA_INSTANCE)
#define SPI4_TX_DMA_INSTANCE            CM_DMA1
#define SPI4_TX_DMA_CHANNEL             DMA_CH7
#define SPI4_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI4_TX_DMA_TRIG_SELECT         AOS_DMA1_7
#define SPI4_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH7
#define SPI4_TX_DMA_IRQn                BSP_DMA1_CH7_IRQ_NUM
#define SPI4_TX_DMA_INT_PRIO            BSP_DMA1_CH7_IRQ_PRIO
#define SPI4_TX_DMA_INT_SRC             INT_SRC_DMA1_TC7
#elif defined(BSP_I2C4_RX_USING_DMA) && !defined(I2C4_RX_DMA_INSTANCE)
#define I2C4_RX_DMA_INSTANCE            CM_DMA1
#define I2C4_RX_DMA_CHANNEL             DMA_CH7
#define I2C4_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define I2C4_RX_DMA_TRIG_SELECT         AOS_DMA1_7
#define I2C4_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH7
#define I2C4_RX_DMA_IRQn                BSP_DMA1_CH7_IRQ_NUM
#define I2C4_RX_DMA_INT_PRIO            BSP_DMA1_CH7_IRQ_PRIO
#define I2C4_RX_DMA_INT_SRC             INT_SRC_DMA1_TC7
#endif

/* DMA2 ch0 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_RX_DMA_INSTANCE           CM_DMA2
#define UART1_RX_DMA_CHANNEL            DMA_CH0
#define UART1_RX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART1_RX_DMA_TRIG_SELECT        AOS_DMA2_0
#define UART1_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH0
#define UART1_RX_DMA_IRQn               BSP_DMA2_CH0_IRQ_NUM
#define UART1_RX_DMA_INT_PRIO           BSP_DMA2_CH0_IRQ_PRIO
#define UART1_RX_DMA_INT_SRC            INT_SRC_DMA2_TC0
#elif defined(BSP_I2C5_TX_USING_DMA) && !defined(I2C5_TX_DMA_INSTANCE)
#define I2C5_TX_DMA_INSTANCE            CM_DMA2
#define I2C5_TX_DMA_CHANNEL             DMA_CH0
#define I2C5_TX_DMA_CLOCK               (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define I2C5_TX_DMA_TRIG_SELECT         AOS_DMA2_0
#define I2C5_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH0
#define I2C5_TX_DMA_IRQn                BSP_DMA2_CH0_IRQ_NUM
#define I2C5_TX_DMA_INT_PRIO            BSP_DMA2_CH0_IRQ_PRIO
#define I2C5_TX_DMA_INT_SRC             INT_SRC_DMA2_TC0
#endif

/* DMA2 ch1 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_TX_DMA_INSTANCE           CM_DMA2
#define UART1_TX_DMA_CHANNEL            DMA_CH1
#define UART1_TX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART1_TX_DMA_TRIG_SELECT        AOS_DMA2_1
#define UART1_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH1
#define UART1_TX_DMA_IRQn               BSP_DMA2_CH1_IRQ_NUM
#define UART1_TX_DMA_INT_PRIO           BSP_DMA2_CH1_IRQ_PRIO
#define UART1_TX_DMA_INT_SRC            INT_SRC_DMA2_TC1
#elif defined(BSP_I2C5_RX_USING_DMA) && !defined(I2C5_RX_DMA_INSTANCE)
#define I2C5_RX_DMA_INSTANCE            CM_DMA2
#define I2C5_RX_DMA_CHANNEL             DMA_CH1
#define I2C5_RX_DMA_CLOCK               (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define I2C5_RX_DMA_TRIG_SELECT         AOS_DMA2_1
#define I2C5_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH1
#define I2C5_RX_DMA_IRQn                BSP_DMA2_CH1_IRQ_NUM
#define I2C5_RX_DMA_INT_PRIO            BSP_DMA2_CH1_IRQ_PRIO
#define I2C5_RX_DMA_INT_SRC             INT_SRC_DMA2_TC1
#endif

/* DMA2 ch2 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_RX_DMA_INSTANCE           CM_DMA2
#define UART2_RX_DMA_CHANNEL            DMA_CH2
#define UART2_RX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART2_RX_DMA_TRIG_SELECT        AOS_DMA2_2
#define UART2_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH2
#define UART2_RX_DMA_IRQn               BSP_DMA2_CH2_IRQ_NUM
#define UART2_RX_DMA_INT_PRIO           BSP_DMA2_CH2_IRQ_PRIO
#define UART2_RX_DMA_INT_SRC            INT_SRC_DMA2_TC2
#elif defined(BSP_I2C6_TX_USING_DMA) && !defined(I2C6_TX_DMA_INSTANCE)
#define I2C6_TX_DMA_INSTANCE            CM_DMA2
#define I2C6_TX_DMA_CHANNEL             DMA_CH2
#define I2C6_TX_DMA_CLOCK               (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define I2C6_TX_DMA_TRIG_SELECT         AOS_DMA2_2
#define I2C6_TX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH2
#define I2C6_TX_DMA_IRQn                BSP_DMA2_CH2_IRQ_NUM
#define I2C6_TX_DMA_INT_PRIO            BSP_DMA2_CH2_IRQ_PRIO
#define I2C6_TX_DMA_INT_SRC             INT_SRC_DMA2_TC2
#endif

/* DMA2 ch3 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_INSTANCE)
#define UART2_TX_DMA_INSTANCE           CM_DMA2
#define UART2_TX_DMA_CHANNEL            DMA_CH3
#define UART2_TX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART2_TX_DMA_TRIG_SELECT        AOS_DMA2_3
#define UART2_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH3
#define UART2_TX_DMA_IRQn               BSP_DMA2_CH3_IRQ_NUM
#define UART2_TX_DMA_INT_PRIO           BSP_DMA2_CH3_IRQ_PRIO
#define UART2_TX_DMA_INT_SRC            INT_SRC_DMA2_TC3
#elif defined(BSP_I2C6_RX_USING_DMA) && !defined(I2C6_RX_DMA_INSTANCE)
#define I2C6_RX_DMA_INSTANCE            CM_DMA2
#define I2C6_RX_DMA_CHANNEL             DMA_CH3
#define I2C6_RX_DMA_CLOCK               (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define I2C6_RX_DMA_TRIG_SELECT         AOS_DMA2_3
#define I2C6_RX_DMA_TRANS_FLAG          DMA_FLAG_TC_CH3
#define I2C6_RX_DMA_IRQn                BSP_DMA2_CH3_IRQ_NUM
#define I2C6_RX_DMA_INT_PRIO            BSP_DMA2_CH3_IRQ_PRIO
#define I2C6_RX_DMA_INT_SRC             INT_SRC_DMA2_TC3
#endif

/* DMA2 ch4 */
#if defined(BSP_UART6_RX_USING_DMA) && !defined(UART6_RX_DMA_INSTANCE)
#define UART6_RX_DMA_INSTANCE           CM_DMA2
#define UART6_RX_DMA_CHANNEL            DMA_CH4
#define UART6_RX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART6_RX_DMA_TRIG_SELECT        AOS_DMA2_4
#define UART6_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH4
#define UART6_RX_DMA_IRQn               BSP_DMA2_CH4_IRQ_NUM
#define UART6_RX_DMA_INT_PRIO           BSP_DMA2_CH4_IRQ_PRIO
#define UART6_RX_DMA_INT_SRC            INT_SRC_DMA2_TC4
#endif

/* DMA2 ch5 */
#if defined(BSP_UART6_TX_USING_DMA) && !defined(UART6_TX_DMA_INSTANCE)
#define UART6_TX_DMA_INSTANCE           CM_DMA2
#define UART6_TX_DMA_CHANNEL            DMA_CH5
#define UART6_TX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART6_TX_DMA_TRIG_SELECT        AOS_DMA2_5
#define UART6_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH5
#define UART6_TX_DMA_IRQn               BSP_DMA2_CH5_IRQ_NUM
#define UART6_TX_DMA_INT_PRIO           BSP_DMA2_CH5_IRQ_PRIO
#define UART6_TX_DMA_INT_SRC            INT_SRC_DMA2_TC5
#endif

/* DMA2 ch6 */
#if defined(BSP_UART7_RX_USING_DMA) && !defined(UART7_RX_DMA_INSTANCE)
#define UART7_RX_DMA_INSTANCE           CM_DMA2
#define UART7_RX_DMA_CHANNEL            DMA_CH6
#define UART7_RX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART7_RX_DMA_TRIG_SELECT        AOS_DMA2_6
#define UART7_RX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH6
#define UART7_RX_DMA_IRQn               BSP_DMA2_CH6_IRQ_NUM
#define UART7_RX_DMA_INT_PRIO           BSP_DMA2_CH6_IRQ_PRIO
#define UART7_RX_DMA_INT_SRC            INT_SRC_DMA2_TC6
#endif

/* DMA2 ch7 */
#if defined(BSP_UART7_TX_USING_DMA) && !defined(UART7_TX_DMA_INSTANCE)
#define UART7_TX_DMA_INSTANCE           CM_DMA2
#define UART7_TX_DMA_CHANNEL            DMA_CH7
#define UART7_TX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART7_TX_DMA_TRIG_SELECT        AOS_DMA2_7
#define UART7_TX_DMA_TRANS_FLAG         DMA_FLAG_TC_CH7
#define UART7_TX_DMA_IRQn               BSP_DMA2_CH7_IRQ_NUM
#define UART7_TX_DMA_INT_PRIO           BSP_DMA2_CH7_IRQ_PRIO
#define UART7_TX_DMA_INT_SRC            INT_SRC_DMA2_TC7
#endif


#ifdef __cplusplus
}
#endif


#endif /* __DMA_CONFIG_H__ */
