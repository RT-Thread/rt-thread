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
#include "Flexio_Uart_Ip.h"
#include "Flexio_Uart_Ip_Irq.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLEXIO_UART_IP_IRQ_VENDOR_ID_C                      43
#define FLEXIO_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define FLEXIO_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION_C       7
#define FLEXIO_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define FLEXIO_UART_IP_IRQ_SW_MAJOR_VERSION_C               5
#define FLEXIO_UART_IP_IRQ_SW_MINOR_VERSION_C               0
#define FLEXIO_UART_IP_IRQ_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Flexio_Uart_Ip.h */
#if (FLEXIO_UART_IP_IRQ_VENDOR_ID_C != FLEXIO_UART_IP_VENDOR_ID)
    #error "Flexio_Uart_Ip_Irq.c and Flexio_Uart_Ip.h have different vendor ids"
#endif
#if ((FLEXIO_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_UART_IP_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_UART_IP_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != FLEXIO_UART_IP_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Uart_Ip_Irq.c and Flexio_Uart_Ip.h are different"
#endif
#if ((FLEXIO_UART_IP_IRQ_SW_MAJOR_VERSION_C != FLEXIO_UART_IP_SW_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_SW_MINOR_VERSION_C != FLEXIO_UART_IP_SW_MINOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_SW_PATCH_VERSION_C != FLEXIO_UART_IP_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Uart_Ip_Irq.c and Flexio_Uart_Ip.h are different"
#endif
/* Checks against Flexio_Uart_Ip_Irq.h */
#if (FLEXIO_UART_IP_IRQ_VENDOR_ID_C != FLEXIO_UART_IP_IRQ_VENDOR_ID)
    #error "Flexio_Uart_Ip_Irq.c and Flexio_Uart_Ip_Irq.h have different vendor ids"
#endif
#if ((FLEXIO_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != FLEXIO_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != FLEXIO_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != FLEXIO_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION) \
    )
     #error "AUTOSAR Version Numbers of Flexio_Uart_Ip_Irq.c and Flexio_Uart_Ip_Irq.h are different"
#endif
#if ((FLEXIO_UART_IP_IRQ_SW_MAJOR_VERSION_C != FLEXIO_UART_IP_IRQ_SW_MAJOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_SW_MINOR_VERSION_C != FLEXIO_UART_IP_IRQ_SW_MINOR_VERSION) || \
     (FLEXIO_UART_IP_IRQ_SW_PATCH_VERSION_C != FLEXIO_UART_IP_IRQ_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Flexio_Uart_Ip_Irq.c and Flexio_Uart_Ip_Irq.h are different"
#endif
/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef FLEXIO_UART_IP_IS_USING
#if (FLEXIO_UART_IP_IS_USING == STD_ON)
#define UART_START_SEC_CODE
#include "Uart_MemMap.h"


#if (FLEXIO_UART_IP_HAS_DMA_ENABLED == STD_ON)
#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 0U)
/* Implementation of Flexio0 Rx callback function for Dma interrupt. */
void Flexio_0_Uart_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteReceiveUsingDma(0);
}
/* Implementation of Flexio0 Tx callback function for Dma interrupt. */
void Flexio_0_Uart_Ip_DmaTxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteSendUsingDma(0);
}
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 1U)
/* Implementation of Flexio1 Rx callback function for Dma interrupt. */
void Flexio_1_Uart_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteReceiveUsingDma(1);
}
/* Implementation of Flexio1 Tx callback function for Dma interrupt. */
void Flexio_1_Uart_Ip_DmaTxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteSendUsingDma(1);
}
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 2U)
/* Implementation of Flexio2 Rx callback function for Dma interrupt. */
void Flexio_2_Uart_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteReceiveUsingDma(2);
}
/* Implementation of Flexio2 Tx callback function for Dma interrupt. */
void Flexio_2_Uart_Ip_DmaTxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteSendUsingDma(2);
}
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 3U)
/* Implementation of Flexio3 Rx callback function for Dma interrupt. */
void Flexio_3_Uart_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteReceiveUsingDma(3);
}
/* Implementation of Flexio3 Tx callback function for Dma interrupt. */
void Flexio_3_Uart_Ip_DmaTxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteSendUsingDma(3);
}
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 4U)
/* Implementation of Flexio4 Rx callback function for Dma interrupt. */
void Flexio_4_Uart_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteReceiveUsingDma(4);
}
/* Implementation of Flexio4 Tx callback function for Dma interrupt. */
void Flexio_4_Uart_Ip_DmaTxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteSendUsingDma(4);
}
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 5U)
/* Implementation of Flexio5 Rx callback function for Dma interrupt. */
void Flexio_5_Uart_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteReceiveUsingDma(5);
}
/* Implementation of Flexio5 Tx callback function for Dma interrupt. */
void Flexio_5_Uart_Ip_DmaTxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteSendUsingDma(5);
}
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 6U)
/* Implementation of Flexio6 Rx callback function for Dma interrupt. */
void Flexio_6_Uart_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteReceiveUsingDma(6);
}
/* Implementation of Flexio6 Tx callback function for Dma interrupt. */
void Flexio_6_Uart_Ip_DmaTxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteSendUsingDma(6);
}
#endif

#if (FLEXIO_UART_IP_NUMBER_OF_SHIFTER_AND_TIMER > 7U)
/* Implementation of Flexio7 Rx callback function for Dma interrupt. */
void Flexio_7_Uart_Ip_DmaRxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteReceiveUsingDma(7);
}
/* Implementation of Flexio7 Tx callback function for Dma interrupt. */
void Flexio_7_Uart_Ip_DmaTxCompleteCallback(void)
{
    Flexio_Uart_Ip_CompleteSendUsingDma(7);
}
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
