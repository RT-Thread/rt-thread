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

#ifndef FLEXIO_UART_IP_IRQ_H
#define FLEXIO_UART_IP_IRQ_H

/**
*   @file
*   @defgroup flexio_uart_ip Flexio UART IPL
*   @addtogroup  flexio_uart_ip Flexio UART IPL
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

#include "Flexio_Uart_Ip_Defines.h"
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_UART_IP_IRQ_VENDOR_ID                    43
#define FLEXIO_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION     4
#define FLEXIO_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION     7
#define FLEXIO_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION  0
#define FLEXIO_UART_IP_IRQ_SW_MAJOR_VERSION             5
#define FLEXIO_UART_IP_IRQ_SW_MINOR_VERSION             0
#define FLEXIO_UART_IP_IRQ_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Flexio_Uart_Ip_Defines.h */
#if (FLEXIO_UART_IP_IRQ_VENDOR_ID != FLEXIO_UART_IP_DEFINES_VENDOR_ID)
    #error "Flexio_Uart_Ip_Irq.h and Flexio_Uart_Ip_Defines.h have different vendor ids"
#endif
#if ((FLEXIO_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION    != FLEXIO_UART_IP_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION    != FLEXIO_UART_IP_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION != FLEXIO_UART_IP_DEFINES_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Uart_Ip_Irq.h and Flexio_Uart_Ip_Defines.h are different"
#endif
#if ((FLEXIO_UART_IP_IRQ_SW_MAJOR_VERSION != FLEXIO_UART_IP_DEFINES_SW_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_SW_MINOR_VERSION != FLEXIO_UART_IP_DEFINES_SW_MINOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_SW_PATCH_VERSION != FLEXIO_UART_IP_DEFINES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Uart_Ip_Irq.h and Flexio_Uart_Ip_Defines.h are different"
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
#ifdef FLEXIO_UART_IP_IS_USING
#if (FLEXIO_UART_IP_IS_USING == STD_ON)
#define UART_START_SEC_CODE
#include "Uart_MemMap.h"

/*FUNCTION**********************************************************************
 *
 * Function Name : Flexio_Uart_Ip_IrqHandler
 * Description   : Implementation of Flexio interrupt handler
 *
 ******************************************************************************/
void Flexio_Uart_Ip_IrqHandler(uint8 Channel, uint8 ShifterMaskFlag, uint8 ShifterErrorMaskFlag, uint8 TimerMaskFlag);

#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 0U)
void Flexio_0_Uart_Ip_DmaRxCompleteCallback(void);
void Flexio_0_Uart_Ip_DmaTxCompleteCallback(void);
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 1U)
void Flexio_1_Uart_Ip_DmaRxCompleteCallback(void);
void Flexio_1_Uart_Ip_DmaTxCompleteCallback(void);
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 2U)
void Flexio_2_Uart_Ip_DmaRxCompleteCallback(void);
void Flexio_2_Uart_Ip_DmaTxCompleteCallback(void);
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 3U)
void Flexio_3_Uart_Ip_DmaRxCompleteCallback(void);
void Flexio_3_Uart_Ip_DmaTxCompleteCallback(void);
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 4U)
void Flexio_4_Uart_Ip_DmaRxCompleteCallback(void);
void Flexio_4_Uart_Ip_DmaTxCompleteCallback(void);
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 5U)
void Flexio_5_Uart_Ip_DmaRxCompleteCallback(void);
void Flexio_5_Uart_Ip_DmaTxCompleteCallback(void);
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 6U)
void Flexio_6_Uart_Ip_DmaRxCompleteCallback(void);
void Flexio_6_Uart_Ip_DmaTxCompleteCallback(void);
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 7U)
void Flexio_7_Uart_Ip_DmaRxCompleteCallback(void);
void Flexio_7_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif /*(FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)*/


#define UART_STOP_SEC_CODE
#include "Uart_MemMap.h"

#endif /* (FLEXIO_UART_IP_IS_USING == STD_ON) */
#endif /* #ifdef FLEXIO_UART_IP_IS_USING */

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* FLEXIO_UART_IP_IRQ_H */
