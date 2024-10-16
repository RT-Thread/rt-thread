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
*   @file       Power_Ip_PMC_Irq.c
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
#include "Power_Ip_PMC.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define POWER_IP_PMC_IRQ_VENDOR_ID_C                      43
#define POWER_IP_PMC_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define POWER_IP_PMC_IRQ_AR_RELEASE_MINOR_VERSION_C       7
#define POWER_IP_PMC_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define POWER_IP_PMC_IRQ_SW_MAJOR_VERSION_C               5
#define POWER_IP_PMC_IRQ_SW_MINOR_VERSION_C               0
#define POWER_IP_PMC_IRQ_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if Power_Ip_PMC_Irq.c file and Power_Ip_Cfg.h file are of the same vendor */
#if (POWER_IP_PMC_IRQ_VENDOR_ID_C != POWER_IP_CFG_VENDOR_ID)
    #error "Power_Ip_PMC_Irq.c and Power_Ip_Cfg.h have different vendor ids"
#endif

/* Check if Power_Ip_PMC_Irq.c file and Power_Ip_Cfg.h file are of the same Autosar version */
#if ((POWER_IP_PMC_IRQ_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PMC_IRQ_AR_RELEASE_MINOR_VERSION_C != POWER_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PMC_IRQ_AR_RELEASE_REVISION_VERSION_C != POWER_IP_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_PMC_Irq.c and Power_Ip_Cfg.h are different"
#endif

/* Check if Power_Ip_PMC_Irq.c file and Power_Ip_Cfg.h file are of the same Software version */
#if ((POWER_IP_PMC_IRQ_SW_MAJOR_VERSION_C != POWER_IP_CFG_SW_MAJOR_VERSION) || \
     (POWER_IP_PMC_IRQ_SW_MINOR_VERSION_C != POWER_IP_CFG_SW_MINOR_VERSION) || \
     (POWER_IP_PMC_IRQ_SW_PATCH_VERSION_C != POWER_IP_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_PMC_Irq.c and Power_Ip_Cfg.h are different"
#endif

/* Check if Power_Ip_PMC_Irq.c file and Power_Ip_PMC.h file are of the same vendor */
#if (POWER_IP_PMC_IRQ_VENDOR_ID_C != POWER_IP_PMC_VENDOR_ID)
    #error "Power_Ip_PMC_Irq.c and Power_Ip_PMC.h have different vendor ids"
#endif

/* Check if Power_Ip_PMC_Irq.c file and Power_Ip_PMC.h file are of the same Autosar version */
#if ((POWER_IP_PMC_IRQ_AR_RELEASE_MAJOR_VERSION_C != POWER_IP_PMC_AR_RELEASE_MAJOR_VERSION) || \
     (POWER_IP_PMC_IRQ_AR_RELEASE_MINOR_VERSION_C != POWER_IP_PMC_AR_RELEASE_MINOR_VERSION) || \
     (POWER_IP_PMC_IRQ_AR_RELEASE_REVISION_VERSION_C != POWER_IP_PMC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Power_Ip_PMC_Irq.c and Power_Ip_PMC.h are different"
#endif

/* Check if Power_Ip_PMC_Irq.c file and Power_Ip_PMC.h file are of the same Software version */
#if ((POWER_IP_PMC_IRQ_SW_MAJOR_VERSION_C != POWER_IP_PMC_SW_MAJOR_VERSION) || \
     (POWER_IP_PMC_IRQ_SW_MINOR_VERSION_C != POWER_IP_PMC_SW_MINOR_VERSION) || \
     (POWER_IP_PMC_IRQ_SW_PATCH_VERSION_C != POWER_IP_PMC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Power_Ip_PMC_Irq.c and Power_Ip_PMC.h are different"
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
#define MCU_START_SEC_CODE
#include "Mcu_MemMap.h"

#ifdef POWER_IP_VOLTAGE_ERROR_ISR_USED
#if (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON)

ISR(PMC_VoltageError_IRQHandler);
#endif /* (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON) */
#endif /* POWER_IP_VOLTAGE_ERROR_ISR_USED */

#if (defined(POWER_IP_PMCAECONFIG_API) && (STD_ON == POWER_IP_PMCAECONFIG_API))
ISR(Power_Ip_PMC_AE_VoltageDetectHvdOnVddintVdd15_ISR);
ISR(Power_Ip_PMC_AE_VoltageDetectHvdOnVdd_ISR);
ISR(Power_Ip_PMC_AE_VoltageDetectLvdOnVddc_ISR);
ISR(Power_Ip_PMC_AE_VoltageDetectLvdOnVls_ISR);
#endif
/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef POWER_IP_VOLTAGE_ERROR_ISR_USED
#if (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON)
/**
* @brief            This function handles the voltage error detection.
*
*/
ISR(PMC_VoltageError_IRQHandler)
{
    Power_Ip_PMC_VoltageErrorIsr();
    EXIT_INTERRUPT();
}
#endif /* (POWER_IP_VOLTAGE_ERROR_ISR_USED == STD_ON) */
#endif /* POWER_IP_VOLTAGE_ERROR_ISR_USED */

#if (defined(POWER_IP_PMCAECONFIG_API) && (STD_ON == POWER_IP_PMCAECONFIG_API))
/**
* @brief       This function represents the ISR handler for PMC_AE related events.
* @details     This interrupt is triggered if one of the enabled PMC_AE's detect an out of range clock.
*
*
* @isr
*
*/
ISR(Power_Ip_PMC_AE_VoltageDetectHvdOnVddintVdd15_ISR)
{
    Power_Ip_PMC_AE_VoltageDetectHvdOnVddintVdd15Isr();
    EXIT_INTERRUPT();
}

ISR(Power_Ip_PMC_AE_VoltageDetectHvdOnVdd_ISR)
{
    Power_Ip_PMC_AE_VoltageDetectHvdOnVddIsr();
    EXIT_INTERRUPT();
}

ISR(Power_Ip_PMC_AE_VoltageDetectLvdOnVddc_ISR)
{
    Power_Ip_PMC_AE_VoltageDetectLvdOnVddcIsr();
    EXIT_INTERRUPT();
}

ISR(Power_Ip_PMC_AE_VoltageDetectLvdOnVls_ISR)
{
    Power_Ip_PMC_AE_VoltageDetectLvdOnVlsIsr();
    EXIT_INTERRUPT();
}
#endif

#define MCU_STOP_SEC_CODE
#include "Mcu_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

