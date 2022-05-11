/*
 * Copyright (C) 2022, Xiaohua Semiconductor Co., Ltd.
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

#ifdef __cplusplus
extern "C" {
#endif

/* DMA1 ch0 */
#if defined(BSP_SPI1_RX_USING_DMA) && !defined(SPI1_RX_DMA_INSTANCE)
#define SPI1_RX_DMA_INSTANCE            CM_DMA1
#define SPI1_RX_DMA_CHANNEL             DMA_CH0
#define SPI1_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI1_RX_DMA_TRIG_SELECT         AOS_DMA1_0
#define SPI1_RX_DMA_IRQn                INT038_IRQn
#define SPI1_RX_DMA_INT_PRIO            DDL_IRQ_PRIO_DEFAULT
#define SPI1_RX_DMA_INT_SRC             INT_SRC_DMA1_TC0
#endif

/* DMA1 ch1 */
#if defined(BSP_SPI1_TX_USING_DMA) && !defined(SPI1_TX_DMA_INSTANCE)
#define SPI1_TX_DMA_INSTANCE            CM_DMA1
#define SPI1_TX_DMA_CHANNEL             DMA_CH1
#define SPI1_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI1_TX_DMA_TRIG_SELECT         AOS_DMA1_1
#define SPI1_TX_DMA_IRQn                INT039_IRQn
#define SPI1_TX_DMA_INT_PRIO            DDL_IRQ_PRIO_DEFAULT
#define SPI1_TX_DMA_INT_SRC             INT_SRC_DMA1_TC1
#endif

/* DMA1 ch2 */
#if defined(BSP_SPI2_RX_USING_DMA) && !defined(SPI2_RX_DMA_INSTANCE)
#define SPI2_RX_DMA_INSTANCE            CM_DMA1
#define SPI2_RX_DMA_CHANNEL             DMA_CH2
#define SPI2_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI2_RX_DMA_TRIG_SELECT         AOS_DMA1_2
#define SPI2_RX_DMA_IRQn                INT040_IRQn
#define SPI2_RX_DMA_INT_PRIO            DDL_IRQ_PRIO_DEFAULT
#define SPI2_RX_DMA_INT_SRC             INT_SRC_DMA1_TC2
#endif

/* DMA1 ch3 */
#if defined(BSP_SPI2_TX_USING_DMA) && !defined(SPI2_TX_DMA_INSTANCE)
#define SPI2_TX_DMA_INSTANCE            CM_DMA1
#define SPI2_TX_DMA_CHANNEL             DMA_CH3
#define SPI2_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI2_TX_DMA_TRIG_SELECT         AOS_DMA1_3
#define SPI2_TX_DMA_IRQn                INT041_IRQn
#define SPI2_TX_DMA_INT_PRIO            DDL_IRQ_PRIO_DEFAULT
#define SPI2_TX_DMA_INT_SRC             INT_SRC_DMA1_TC3
#endif

/* DMA1 ch4 */
#if defined(BSP_SPI3_RX_USING_DMA) && !defined(SPI3_RX_DMA_INSTANCE)
#define SPI3_RX_DMA_INSTANCE            CM_DMA1
#define SPI3_RX_DMA_CHANNEL             DMA_CH4
#define SPI3_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI3_RX_DMA_TRIG_SELECT         AOS_DMA1_4
#define SPI3_RX_DMA_IRQn                INT042_IRQn
#define SPI3_RX_DMA_INT_PRIO            DDL_IRQ_PRIO_DEFAULT
#define SPI3_RX_DMA_INT_SRC             INT_SRC_DMA1_TC4
#endif

/* DMA1 ch5 */
#if defined(BSP_SPI3_TX_USING_DMA) && !defined(SPI3_TX_DMA_INSTANCE)
#define SPI3_TX_DMA_INSTANCE            CM_DMA1
#define SPI3_TX_DMA_CHANNEL             DMA_CH5
#define SPI3_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI3_TX_DMA_TRIG_SELECT         AOS_DMA1_5
#define SPI3_TX_DMA_IRQn                INT043_IRQn
#define SPI3_TX_DMA_INT_PRIO            DDL_IRQ_PRIO_DEFAULT
#define SPI3_TX_DMA_INT_SRC             INT_SRC_DMA1_TC5
#endif

/* DMA1 ch6 */
#if defined(BSP_SPI4_RX_USING_DMA) && !defined(SPI4_RX_DMA_INSTANCE)
#define SPI4_RX_DMA_INSTANCE            CM_DMA1
#define SPI4_RX_DMA_CHANNEL             DMA_CH6
#define SPI4_RX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI4_RX_DMA_TRIG_SELECT         AOS_DMA1_6
#define SPI4_RX_DMA_IRQn                INT018_IRQn
#define SPI4_RX_DMA_INT_PRIO            DDL_IRQ_PRIO_DEFAULT
#define SPI4_RX_DMA_INT_SRC             INT_SRC_DMA1_TC6
#endif

/* DMA1 ch7 */
#if defined(BSP_SPI4_TX_USING_DMA) && !defined(SPI4_TX_DMA_INSTANCE)
#define SPI4_TX_DMA_INSTANCE            CM_DMA1
#define SPI4_TX_DMA_CHANNEL             DMA_CH7
#define SPI4_TX_DMA_CLOCK               (PWC_FCG0_DMA1 | PWC_FCG0_AOS)
#define SPI4_TX_DMA_TRIG_SELECT         AOS_DMA1_7
#define SPI4_TX_DMA_IRQn                INT019_IRQn
#define SPI4_TX_DMA_INT_PRIO            DDL_IRQ_PRIO_DEFAULT
#define SPI4_TX_DMA_INT_SRC             INT_SRC_DMA1_TC7
#endif

/* DMA2 ch0 */
#if defined(BSP_UART1_RX_USING_DMA) && !defined(UART1_RX_DMA_INSTANCE)
#define UART1_RX_DMA_INSTANCE           CM_DMA2
#define UART1_RX_DMA_CHANNEL            DMA_CH0
#define UART1_RX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART1_RX_DMA_TRIG_SELECT        AOS_DMA2_0
#define UART1_RX_DMA_IRQn               INT044_IRQn
#define UART1_RX_DMA_INT_PRIO           DDL_IRQ_PRIO_DEFAULT
#define UART1_RX_DMA_INT_SRC            INT_SRC_DMA2_TC0
#endif

/* DMA2 ch1 */
#if defined(BSP_UART1_TX_USING_DMA) && !defined(UART1_TX_DMA_INSTANCE)
#define UART1_TX_DMA_INSTANCE           CM_DMA2
#define UART1_TX_DMA_CHANNEL            DMA_CH1
#define UART1_TX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART1_TX_DMA_TRIG_SELECT        AOS_DMA2_1
#define UART1_TX_DMA_IRQn               INT045_IRQn
#define UART1_TX_DMA_INT_PRIO           DDL_IRQ_PRIO_DEFAULT
#define UART1_TX_DMA_INT_SRC            INT_SRC_DMA2_TC1
#endif

/* DMA2 ch2 */
#if defined(BSP_UART2_RX_USING_DMA) && !defined(UART2_RX_DMA_INSTANCE)
#define UART2_RX_DMA_INSTANCE           CM_DMA2
#define UART2_RX_DMA_CHANNEL            DMA_CH2
#define UART2_RX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART2_RX_DMA_TRIG_SELECT        AOS_DMA2_2
#define UART2_RX_DMA_IRQn               INT046_IRQn
#define UART2_RX_DMA_INT_PRIO           DDL_IRQ_PRIO_DEFAULT
#define UART2_RX_DMA_INT_SRC            INT_SRC_DMA2_TC2
#endif

/* DMA2 ch3 */
#if defined(BSP_UART2_TX_USING_DMA) && !defined(UART2_TX_DMA_INSTANCE)
#define UART2_TX_DMA_INSTANCE           CM_DMA2
#define UART2_TX_DMA_CHANNEL            DMA_CH3
#define UART2_TX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART2_TX_DMA_TRIG_SELECT        AOS_DMA2_3
#define UART2_TX_DMA_IRQn               INT047_IRQn
#define UART2_TX_DMA_INT_PRIO           DDL_IRQ_PRIO_DEFAULT
#define UART2_TX_DMA_INT_SRC            INT_SRC_DMA2_TC3
#endif

/* DMA2 ch4 */
#if defined(BSP_UART6_RX_USING_DMA) && !defined(UART6_RX_DMA_INSTANCE)
#define UART6_RX_DMA_INSTANCE           CM_DMA2
#define UART6_RX_DMA_CHANNEL            DMA_CH4
#define UART6_RX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART6_RX_DMA_TRIG_SELECT        AOS_DMA2_4
#define UART6_RX_DMA_IRQn               INT048_IRQn
#define UART6_RX_DMA_INT_PRIO           DDL_IRQ_PRIO_DEFAULT
#define UART6_RX_DMA_INT_SRC            INT_SRC_DMA2_TC4
#endif

/* DMA2 ch5 */
#if defined(BSP_UART6_TX_USING_DMA) && !defined(UART6_TX_DMA_INSTANCE)
#define UART6_TX_DMA_INSTANCE           CM_DMA2
#define UART6_TX_DMA_CHANNEL            DMA_CH5
#define UART6_TX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART6_TX_DMA_TRIG_SELECT        AOS_DMA2_5
#define UART6_TX_DMA_IRQn               INT049_IRQn
#define UART6_TX_DMA_INT_PRIO           DDL_IRQ_PRIO_DEFAULT
#define UART6_TX_DMA_INT_SRC            INT_SRC_DMA2_TC5
#endif

/* DMA2 ch6 */
#if defined(BSP_UART7_RX_USING_DMA) && !defined(UART7_RX_DMA_INSTANCE)
#define UART7_RX_DMA_INSTANCE           CM_DMA2
#define UART7_RX_DMA_CHANNEL            DMA_CH6
#define UART7_RX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART7_RX_DMA_TRIG_SELECT        AOS_DMA2_6
#define UART7_RX_DMA_IRQn               INT020_IRQn
#define UART7_RX_DMA_INT_PRIO           DDL_IRQ_PRIO_DEFAULT
#define UART7_RX_DMA_INT_SRC            INT_SRC_DMA2_TC6
#endif

/* DMA2 ch7 */
#if defined(BSP_UART7_TX_USING_DMA) && !defined(UART7_TX_DMA_INSTANCE)
#define UART7_TX_DMA_INSTANCE           CM_DMA2
#define UART7_TX_DMA_CHANNEL            DMA_CH7
#define UART7_TX_DMA_CLOCK              (PWC_FCG0_DMA2 | PWC_FCG0_AOS)
#define UART7_TX_DMA_TRIG_SELECT        AOS_DMA2_7
#define UART7_TX_DMA_IRQn               INT021_IRQn
#define UART7_TX_DMA_INT_PRIO           DDL_IRQ_PRIO_DEFAULT
#define UART7_TX_DMA_INT_SRC            INT_SRC_DMA2_TC7
#endif


#ifdef __cplusplus
}
#endif


#endif /* __DMA_CONFIG_H__ */
