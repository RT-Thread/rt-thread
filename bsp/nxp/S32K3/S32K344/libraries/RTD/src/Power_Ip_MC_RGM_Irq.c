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
*   @file       Power_Ip_MC_RGM_Irq.c
*   @version    5.0.0
*
*   @brief
*   @brief   POWER driver implementations.
*   @details POWER driver implementations.
*
*   @addtogroup POWER_DRIVER Power Ip Driver
*   @{
*/


#ifdef __cplusplus
extern "C"{
#endif



/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Power_Ip_Cfg.h"
#include "Power_Ip_MC_RGM.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_MC_RGM_IRQ_VENDOR_ID_C                      43
#define POWER_IP_MC_RGM_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_MC_RGM_IRQ_AR_RELEASE_MINOR_VERSION_C       7
#define POWER_IP_MC_RGM_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_MC_RGM_IRQ_SW_MAJOR_VERSION_C               5
#define POWER_IP_MC_RGM_IRQ_SW_MINOR_VERSION_C               0
#define POWER_IP_MC_RGM_IRQ_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_MC_RGM_Irq.c file and Power_Ip_Cfg.h file are of the same vendor */
#if (POWER_IP_MC_RGM_IRQ_VENDOR_ID_C != POWER_IP_CFG_VENDOR_ID)
    #error "Power_Ip_MC_RGM_Irq.c and Power_Ip_Cfg.h have different vendor ids"
#endif

/* Check if Power_Ip_MC_RGM_Irq.c file and Power_Ip_Cfg.h file are of the same Autosar version */
#if ((POWER_IP_MC_RGM_IRQ_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_IRQ_AR_RELEASE_MINOR_VERSION_C != POWER_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_IRQ_AR_RELEASE_REVISION_VERSION_C != POWER_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_MC_RGM_Irq.c and Power_Ip_Cfg.h are different"
#endif

/* Check if Power_Ip_MC_RGM_Irq.c file and Power_Ip_Cfg.h file are of the same Software version */
#if ((POWER_IP_MC_RGM_IRQ_SW_MAJOR_VERSION_C != POWER_IP_CFG_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_IRQ_SW_MINOR_VERSION_C != POWER_IP_CFG_SW_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_IRQ_SW_PATCH_VERSION_C != POWER_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_MC_RGM_Irq.c and Power_Ip_Cfg.h are different"
#endif

/* Check if Power_Ip_MC_RGM_Irq.c file and Power_Ip_MC_RGM.h file are of the same vendor */
#if (POWER_IP_MC_RGM_IRQ_VENDOR_ID_C != POWER_IP_MC_RGM_VENDOR_ID)
    #error "Power_Ip_MC_RGM_Irq.c and Power_Ip_MC_RGM.h have different vendor ids"
#endif

/* Check if Power_Ip_MC_RGM_Irq.c file and Power_Ip_MC_RGM.h file are of the same Autosar version */
#if ((POWER_IP_MC_RGM_IRQ_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_MC_RGM_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_IRQ_AR_RELEASE_MINOR_VERSION_C != POWER_IP_MC_RGM_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_IRQ_AR_RELEASE_REVISION_VERSION_C != POWER_IP_MC_RGM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_MC_RGM_Irq.c and Power_Ip_MC_RGM.h are different"
#endif

/* Check if Power_Ip_MC_RGM_Irq.c file and Power_Ip_MC_RGM.h file are of the same Software version */
#if ((POWER_IP_MC_RGM_IRQ_SW_MAJOR_VERSION_C != POWER_IP_MC_RGM_SW_MAJOR_VERSION) || \
     (POWER_IP_MC_RGM_IRQ_SW_MINOR_VERSION_C != POWER_IP_MC_RGM_SW_MINOR_VERSION) || \
     (POWER_IP_MC_RGM_IRQ_SW_PATCH_VERSION_C != POWER_IP_MC_RGM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_MC_RGM_Irq.c and Power_Ip_MC_RGM.h are different"
#endif
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef POWER_IP_RESET_ALTERNATE_ISR_USED
#if (POWER_IP_RESET_ALTERNATE_ISR_USED == STD_ON)

/* This function handles both the 'Functional' and 'Destructive' Reset Alternate Event Interrupts. */
ISR(MC_RGM_ResetAlt_IRQHandler)
{
    Power_Ip_MC_RGM_ResetAltInt();
    EXIT_INTERRUPT();
}

#endif
#endif /* POWER_IP_RESET_ALTERNATE_ISR_USED */

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

