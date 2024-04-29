/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-02-20     CDT          first version
 */

#ifndef __IRQ_CONFIG_H__
#define __IRQ_CONFIG_H__

#include <rtthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BSP_EXTINT0_IRQ_NUM             EXTINT_PORT_EIRQ0_IRQn
#define BSP_EXTINT0_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT1_IRQ_NUM             EXTINT_PORT_EIRQ1_IRQn
#define BSP_EXTINT1_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT2_IRQ_NUM             EXTINT_PORT_EIRQ2_IRQn
#define BSP_EXTINT2_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT3_IRQ_NUM             EXTINT_PORT_EIRQ3_IRQn
#define BSP_EXTINT3_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT4_IRQ_NUM             EXTINT_PORT_EIRQ4_IRQn
#define BSP_EXTINT4_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT5_IRQ_NUM             EXTINT_PORT_EIRQ5_IRQn
#define BSP_EXTINT5_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT6_IRQ_NUM             EXTINT_PORT_EIRQ6_IRQn
#define BSP_EXTINT6_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT7_IRQ_NUM             EXTINT_PORT_EIRQ7_IRQn
#define BSP_EXTINT7_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT8_IRQ_NUM             EXTINT_PORT_EIRQ8_IRQn
#define BSP_EXTINT8_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT9_IRQ_NUM             EXTINT_PORT_EIRQ9_IRQn
#define BSP_EXTINT9_IRQ_PRIO            DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT10_IRQ_NUM            EXTINT_PORT_EIRQ10_IRQn
#define BSP_EXTINT10_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT11_IRQ_NUM            EXTINT_PORT_EIRQ11_IRQn
#define BSP_EXTINT11_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT12_IRQ_NUM            EXTINT_PORT_EIRQ12_IRQn
#define BSP_EXTINT12_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT13_IRQ_NUM            EXTINT_PORT_EIRQ13_IRQn
#define BSP_EXTINT13_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT14_IRQ_NUM            EXTINT_PORT_EIRQ14_IRQn
#define BSP_EXTINT14_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#define BSP_EXTINT15_IRQ_NUM            EXTINT_PORT_EIRQ15_IRQn
#define BSP_EXTINT15_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

/* DMA1 ch0 */
#define BSP_DMA1_CH0_IRQ_NUM            INT000_IRQn
#define BSP_DMA1_CH0_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch1 */
#define BSP_DMA1_CH1_IRQ_NUM            INT001_IRQn
#define BSP_DMA1_CH1_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch2 */
#define BSP_DMA1_CH2_IRQ_NUM            INT002_IRQn
#define BSP_DMA1_CH2_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch3 */
#define BSP_DMA1_CH3_IRQ_NUM            INT003_IRQn
#define BSP_DMA1_CH3_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch4 */
#define BSP_DMA1_CH4_IRQ_NUM            INT004_IRQn
#define BSP_DMA1_CH4_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA1 ch5 */
#define BSP_DMA1_CH5_IRQ_NUM            INT005_IRQn
#define BSP_DMA1_CH5_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

/* DMA2 ch0 */
#define BSP_DMA2_CH0_IRQ_NUM            INT006_IRQn
#define BSP_DMA2_CH0_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch1 */
#define BSP_DMA2_CH1_IRQ_NUM            INT007_IRQn
#define BSP_DMA2_CH1_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch2 */
#define BSP_DMA2_CH2_IRQ_NUM            INT008_IRQn
#define BSP_DMA2_CH2_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch3 */
#define BSP_DMA2_CH3_IRQ_NUM            INT009_IRQn
#define BSP_DMA2_CH3_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch4 */
#define BSP_DMA2_CH4_IRQ_NUM            INT010_IRQn
#define BSP_DMA2_CH4_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
/* DMA2 ch5 */
#define BSP_DMA2_CH5_IRQ_NUM            INT011_IRQn
#define BSP_DMA2_CH5_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT

#if defined(BSP_USING_UART1)
#define BSP_UART1_IRQ_NUM               USART1_IRQn
#define BSP_UART1_IRQ_PRIO              DDL_IRQ_PRIO_DEFAULT

#if (defined(RT_USING_SERIAL_V1) && defined(BSP_UART1_TX_USING_DMA)) || \
    defined(RT_USING_SERIAL_V2)
#define BSP_UART1_TX_CPLT_IRQ_NUM       USART1_TCI_IRQn
#define BSP_UART1_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif
#endif /* BSP_USING_UART1 */

#if defined(BSP_USING_UART2)
#define BSP_UART2_IRQ_NUM               USART2_IRQn
#define BSP_UART2_IRQ_PRIO              DDL_IRQ_PRIO_DEFAULT

#if (defined(RT_USING_SERIAL_V1) && defined(BSP_UART2_TX_USING_DMA)) || \
    defined(RT_USING_SERIAL_V2)
#define BSP_UART2_TX_CPLT_IRQ_NUM       USART2_TCI_IRQn
#define BSP_UART2_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif
#endif /* BSP_USING_UART2 */

#if defined(BSP_USING_UART3)
#define BSP_UART3_IRQ_NUM               USART3_IRQn
#define BSP_UART3_IRQ_PRIO              DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_UART3 */

#if defined(BSP_USING_UART4)
#define BSP_UART4_IRQ_NUM               USART4_IRQn
#define BSP_UART4_IRQ_PRIO              DDL_IRQ_PRIO_DEFAULT

#if (defined(RT_USING_SERIAL_V1) && defined(BSP_UART4_TX_USING_DMA)) || \
    defined(RT_USING_SERIAL_V2)
#define BSP_UART4_TX_CPLT_IRQ_NUM       USART4_TCI_IRQn
#define BSP_UART4_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif
#endif /* BSP_USING_UART4 */

#if defined(BSP_USING_UART5)
#define BSP_UART5_IRQ_NUM               USART5_IRQn
#define BSP_UART5_IRQ_PRIO              DDL_IRQ_PRIO_DEFAULT

#if (defined(RT_USING_SERIAL_V1) && defined(BSP_UART5_TX_USING_DMA)) || \
    defined(RT_USING_SERIAL_V2)
#define BSP_UART5_TX_CPLT_IRQ_NUM       USART5_TCI_IRQn
#define BSP_UART5_TX_CPLT_IRQ_PRIO      DDL_IRQ_PRIO_DEFAULT
#endif
#endif /* BSP_USING_UART5 */

#if defined(BSP_USING_UART6)
#define BSP_UART6_IRQ_NUM               USART6_IRQn
#define BSP_UART6_IRQ_PRIO              DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_UART6 */

#if defined(BSP_USING_SPI1)
#define BSP_SPI1_ERR_IRQ_NUM            SPI1_IRQn
#define BSP_SPI1_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(BSP_USING_SPI2)
#define BSP_SPI2_ERR_IRQ_NUM            SPI2_IRQn
#define BSP_SPI2_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(BSP_USING_SPI3)
#define BSP_SPI3_ERR_IRQ_NUM            SPI3_IRQn
#define BSP_SPI3_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif

#if defined(BSP_USING_SPI4)
#define BSP_SPI4_ERR_IRQ_NUM            SPI4_IRQn
#define BSP_SPI4_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif

#if defined (BSP_USING_QSPI)
#define BSP_QSPI_ERR_IRQ_NUM            QSPI_IRQn
#define BSP_QSPI_ERR_IRQ_PRIO           DDL_IRQ_PRIO_DEFAULT
#endif /* BSP_USING_QSPI */

#if defined(BSP_USING_TMRA_1)
#define BSP_USING_TMRA_1_IRQ_NUM        TMRA_1_OVF_UDF_IRQn
#define BSP_USING_TMRA_1_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_1 */

#if defined(BSP_USING_TMRA_2)
#define BSP_USING_TMRA_2_IRQ_NUM        TMRA_2_OVF_UDF_IRQn
#define BSP_USING_TMRA_2_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_2 */

#if defined(BSP_USING_TMRA_3)
#define BSP_USING_TMRA_3_IRQ_NUM        TMRA_3_OVF_UDF_IRQn
#define BSP_USING_TMRA_3_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_3 */

#if defined(BSP_USING_TMRA_4)
#define BSP_USING_TMRA_4_IRQ_NUM        TMRA_4_OVF_UDF_IRQn
#define BSP_USING_TMRA_4_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_4 */

#if defined(BSP_USING_TMRA_5)
#define BSP_USING_TMRA_5_IRQ_NUM        TMRA_5_OVF_UDF_IRQn
#define BSP_USING_TMRA_5_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_5 */

#if defined(BSP_USING_TMRA_6)
#define BSP_USING_TMRA_6_IRQ_NUM        TMRA_6_OVF_UDF_IRQn
#define BSP_USING_TMRA_6_IRQ_PRIO       DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_TMRA_6 */

#if defined(BSP_USING_CAN1)
#define BSP_CAN1_IRQ_NUM                MCAN1_INT0_IRQn
#define BSP_CAN1_IRQ_PRIO               DDL_IRQ_PRIO_DEFAULT
#endif/* BSP_USING_CAN1 */

#if defined(RT_USING_ALARM)
#define BSP_RTC_ALARM_IRQ_NUM           RTC_IRQn
#define BSP_RTC_ALARM_IRQ_PRIO          DDL_IRQ_PRIO_DEFAULT
#endif/* RT_USING_ALARM */

#ifdef __cplusplus
}
#endif

#endif /* __IRQ_CONFIG_H__ */
