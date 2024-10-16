/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
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
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/
/**
*   @file       Clock_Ip_Irq.c
*   @version    5.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Ip Driver
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
#include "Clock_Ip_Private.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CLOCK_IP_IRQ_VENDOR_ID_C                      43
#define CLOCK_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define CLOCK_IP_IRQ_AR_RELEASE_MINOR_VERSION_C       7
#define CLOCK_IP_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define CLOCK_IP_IRQ_SW_MAJOR_VERSION_C               5
#define CLOCK_IP_IRQ_SW_MINOR_VERSION_C               0
#define CLOCK_IP_IRQ_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Clock_Ip_Irq.c file and Clock_Ip_Private.h file are of the same vendor */
#if (CLOCK_IP_IRQ_VENDOR_ID_C != CLOCK_IP_PRIVATE_VENDOR_ID)
    #error "Clock_Ip_Irq.c and Clock_Ip_Private.h have different vendor ids"
#endif

/* Check if Clock_Ip_Irq.c file and Clock_Ip_Private.h file are of the same Autosar version */
#if ((CLOCK_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MAJOR_VERSION) || \
     (CLOCK_IP_IRQ_AR_RELEASE_MINOR_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_MINOR_VERSION) || \
     (CLOCK_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != CLOCK_IP_PRIVATE_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Clock_Ip_Irq.c and Clock_Ip_Private.h are different"
#endif

/* Check if Clock_Ip_Irq.c file and Clock_Ip_Private.h file are of the same Software version */
#if ((CLOCK_IP_IRQ_SW_MAJOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MAJOR_VERSION) || \
     (CLOCK_IP_IRQ_SW_MINOR_VERSION_C != CLOCK_IP_PRIVATE_SW_MINOR_VERSION) || \
     (CLOCK_IP_IRQ_SW_PATCH_VERSION_C != CLOCK_IP_PRIVATE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Clock_Ip_Irq.c and Clock_Ip_Private.h are different"
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
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                    GLOBAL FUNCTION PROTOTYPES
==================================================================================================*/
#ifdef CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"
#if CLOCK_IP_CMU_INSTANCES_ARRAY_SIZE > 0U

ISR(Mcu_Cmu_ClockFail_IRQHandler);

#endif
#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"
#endif





/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"
#ifdef CLOCK_IP_CMU_FC_FCE_REF_CNT_LFREF_HFREF
#if CLOCK_IP_CMU_INSTANCES_ARRAY_SIZE > 0U

/**
* @brief        This function clear the CMU interrupt flag from CMU module.
* @details      Called by RGM ISR routine when a user notification for CMU FCCU events is configured
*
* @return       void
*
*/
ISR(Mcu_Cmu_ClockFail_IRQHandler)
{
    Clock_Ip_CMU_ClockFailInt();
    EXIT_INTERRUPT();
}
#endif
#endif





#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
