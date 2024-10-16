/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : FLEXIO
*   Dependencies         : 
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 5.0.0
*   Build Version        : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
*   Copyright 2020 - 2024 NXP
*
*   NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef LPUART_UART_IP_IRQ_H
#define LPUART_UART_IP_IRQ_H

/**
*   @file
*   @defgroup lpuart_uart_ip Lpuart UART IPL
*   @addtogroup  lpuart_uart_ip Lpuart UART IPL
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Lpuart_Uart_Ip_Cfg.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LPUART_UART_IP_IRQ_VENDOR_ID                    43
#define LPUART_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION     4
#define LPUART_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION     7
#define LPUART_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION  0
#define LPUART_UART_IP_IRQ_SW_MAJOR_VERSION             5
#define LPUART_UART_IP_IRQ_SW_MINOR_VERSION             0
#define LPUART_UART_IP_IRQ_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Lpuart_Uart_Ip_Cfg.h */
#if (LPUART_UART_IP_CFG_VENDOR_ID != LPUART_UART_IP_IRQ_VENDOR_ID)
    #error "Lpuart_Uart_Ip_Irq.h and Lpuart_Uart_Ip_Cfg.h have different vendor ids"
#endif
#if ((LPUART_UART_IP_CFG_AR_RELEASE_MAJOR_VERSION    != LPUART_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (LPUART_UART_IP_CFG_AR_RELEASE_MINOR_VERSION    != LPUART_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (LPUART_UART_IP_CFG_AR_RELEASE_REVISION_VERSION != LPUART_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Lpuart_Uart_Ip_Irq.h and Lpuart_Uart_Ip_Cfg.h are different"
#endif
#if ((LPUART_UART_IP_CFG_SW_MAJOR_VERSION != LPUART_UART_IP_IRQ_SW_MAJOR_VERSION) || \
     (LPUART_UART_IP_CFG_SW_MINOR_VERSION != LPUART_UART_IP_IRQ_SW_MINOR_VERSION) || \
     (LPUART_UART_IP_CFG_SW_PATCH_VERSION != LPUART_UART_IP_IRQ_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lpuart_Uart_Ip_Irq.h and Lpuart_Uart_Ip_Cfg.h are different"
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/

#define UART_START_SEC_CODE
#include "Uart_MemMap.h"

#if (LPUART_INSTANCE_COUNT > 0U)
#ifdef LPUART_UART_IP_INSTANCE_USING_0
/* Implementation of Lpuart0 handler named in startup code. */
ISR(LPUART_UART_IP_0_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 1U)
#ifdef LPUART_UART_IP_INSTANCE_USING_1
/* Implementation of Lpuart1 handler named in startup code. */
ISR(LPUART_UART_IP_1_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 2U)
#ifdef LPUART_UART_IP_INSTANCE_USING_2
/* Implementation of Lpuart2 handler named in startup code. */
ISR(LPUART_UART_IP_2_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 3U)
#ifdef LPUART_UART_IP_INSTANCE_USING_3
/* Implementation of Lpuart3 handler named in startup code. */
ISR(LPUART_UART_IP_3_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 4U)
#ifdef LPUART_UART_IP_INSTANCE_USING_4
/* Implementation of Lpuart4 handler named in startup code. */
ISR(LPUART_UART_IP_4_IRQHandler);
#endif
#ifdef LPUART_UART_IP_INSTANCE_USING_MSC
/* Implementation of Lpuart_Msc handler named in startup code. */
ISR(LPUART_UART_IP_MSC_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 5U)
#ifdef LPUART_UART_IP_INSTANCE_USING_5
/* Implementation of Lpuart5 handler named in startup code. */
ISR(LPUART_UART_IP_5_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 6U)
#ifdef LPUART_UART_IP_INSTANCE_USING_6
/* Implementation of Lpuart6 handler named in startup code. */
ISR(LPUART_UART_IP_6_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 7U)
#ifdef LPUART_UART_IP_INSTANCE_USING_7
/* Implementation of Lpuart7 handler named in startup code. */
ISR(LPUART_UART_IP_7_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 8U)
#ifdef LPUART_UART_IP_INSTANCE_USING_8
/* Implementation of Lpuart8 handler named in startup code. */
ISR(LPUART_UART_IP_8_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 9U)
#ifdef LPUART_UART_IP_INSTANCE_USING_9
/* Implementation of Lpuart9 handler named in startup code. */
ISR(LPUART_UART_IP_9_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 10U)
#ifdef LPUART_UART_IP_INSTANCE_USING_10
/* Implementation of Lpuart10 handler named in startup code. */
ISR(LPUART_UART_IP_10_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 11U)
#ifdef LPUART_UART_IP_INSTANCE_USING_11
/* Implementation of Lpuart11 handler named in startup code. */
ISR(LPUART_UART_IP_11_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 12U)
#ifdef LPUART_UART_IP_INSTANCE_USING_12
/* Implementation of Lpuart12 handler named in startup code. */
ISR(LPUART_UART_IP_12_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 13U)
#ifdef LPUART_UART_IP_INSTANCE_USING_13
/* Implementation of Lpuart13 handler named in startup code. */
ISR(LPUART_UART_IP_13_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 14U)
#ifdef LPUART_UART_IP_INSTANCE_USING_14
/* Implementation of Lpuart14 handler named in startup code. */
ISR(LPUART_UART_IP_14_IRQHandler);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 15U)
#ifdef LPUART_UART_IP_INSTANCE_USING_15
/* Implementation of Lpuart15 handler named in startup code. */
ISR(LPUART_UART_IP_15_IRQHandler);
#endif
#endif


#if (LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)
#if (LPUART_INSTANCE_COUNT > 0U)
#ifdef LPUART_UART_IP_INSTANCE_USING_0
void Lpuart_0_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_0_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 1U)
#ifdef LPUART_UART_IP_INSTANCE_USING_1
void Lpuart_1_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_1_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 2U)
#ifdef LPUART_UART_IP_INSTANCE_USING_2
void Lpuart_2_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_2_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 3U)
#ifdef LPUART_UART_IP_INSTANCE_USING_3
void Lpuart_3_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_3_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 4U)
#ifdef LPUART_UART_IP_INSTANCE_USING_4
void Lpuart_4_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_4_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#ifdef LPUART_UART_IP_INSTANCE_USING_MSC
/* Implementation of Lpuart_Msc handler named in startup code. */
void Lpuart_MSC_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_MSC_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 5U)
#ifdef LPUART_UART_IP_INSTANCE_USING_5
void Lpuart_5_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_5_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 6U)
#ifdef LPUART_UART_IP_INSTANCE_USING_6
void Lpuart_6_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_6_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 7U)
#ifdef LPUART_UART_IP_INSTANCE_USING_7
void Lpuart_7_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_7_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 8U)
#ifdef LPUART_UART_IP_INSTANCE_USING_8
void Lpuart_8_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_8_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 9U)
#ifdef LPUART_UART_IP_INSTANCE_USING_9
void Lpuart_9_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_9_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 10U)
#ifdef LPUART_UART_IP_INSTANCE_USING_10
void Lpuart_10_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_10_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 11U)
#ifdef LPUART_UART_IP_INSTANCE_USING_11
void Lpuart_11_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_11_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 12U)
#ifdef LPUART_UART_IP_INSTANCE_USING_12
void Lpuart_12_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_12_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 13U)
#ifdef LPUART_UART_IP_INSTANCE_USING_13
void Lpuart_13_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_13_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 14U)
#ifdef LPUART_UART_IP_INSTANCE_USING_14
void Lpuart_14_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_14_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif

#if (LPUART_INSTANCE_COUNT > 15U)
#ifdef LPUART_UART_IP_INSTANCE_USING_15
void Lpuart_15_Uart_Ip_DmaRxCompleteCallback(void);
void Lpuart_15_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif
#endif /*(LPUART_UART_IP_HAS_DMA_ENABLED == STD_ON)*/

#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* LPUART_UART_IP_IRQ_H */
