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

#ifndef SYSTEM_IP_CFG_DEFINES_H_
#define SYSTEM_IP_CFG_DEFINES_H_
/**
*   @file
*
*   @addtogroup System_Ip
*   @{
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Std_Types.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_VENDOR_ID                          43
#define CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_SW_MAJOR_VERSION                   5
#define CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_SW_MINOR_VERSION                   0
#define CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_SW_PATCH_VERSION                   0
#define CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION           4
#define CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION           7
#define CDD_PLATFORM_SYSTEM_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION        0

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


        #include "S32K344_MCM_CM7.h"
            #define MCM_ISCR_FIDCE_SHIFT          MCM_CM7_ISCR_FIDCE_SHIFT
    #define MCM_ISCR_FIXCE_SHIFT          MCM_CM7_ISCR_FIXCE_SHIFT
    #define MCM_ISCR_FUFCE_SHIFT          MCM_CM7_ISCR_FUFCE_SHIFT
    #define MCM_ISCR_FOFCE_SHIFT          MCM_CM7_ISCR_FOFCE_SHIFT
    #define MCM_ISCR_FDZCE_SHIFT          MCM_CM7_ISCR_FDZCE_SHIFT
    #define MCM_ISCR_FIOCE_SHIFT          MCM_CM7_ISCR_FIOCE_SHIFT
    #define MCM_ISCR_WABE_SHIFT           MCM_CM7_ISCR_WABE_SHIFT 
    #define MCM_CPCR_CM7_AHBSPRI_MASK     MCM_CM7_CPCR_CM7_AHBSPRI_MASK
    #define MCM_ISCR_WABS_MASK            MCM_CM7_ISCR_WABS_MASK
    
    #define IP_MCM IP_MCM_0_CM7
    #define FPU_INPUT_DENORMAL_IRQ_SUPPORTED
    #define FPU_INEXACT_IRQ_SUPPORTED
    #define FPU_UNDERFLOW_IRQ_SUPPORTED
    #define FPU_OVERFLOW_IRQ_SUPPORTED
    #define FPU_DIVIDE_BY_ZERO_IRQ_SUPPORTED
    #define FPU_INVALID_OPERATION_IRQ_SUPPORTED
    #define TCM_WRITE_ABORT_IRQ_SUPPORTED
    
    #define MCM_HAS_WABS_SUPPORTED
    
    #define MCM_HAS_PLATFORM_REVISION
    /* Arm Cortex M4 */
#define SYSTEM_IP_ARM_CORTEXM                   (STD_ON)
#define SYSTEM_FPU_CFG                           (1)
#if ((SYSTEM_IP_ARM_CORTEXM == STD_ON) && (SYSTEM_FPU_CFG == STD_ON))
/**
* @brief      Enumeration listing available core-related interrupt requests
*             defined per each platform.
* @implements System_Ip_IrqType_typedef
*/    
typedef enum
{
#ifdef FPU_INPUT_DENORMAL_IRQ_SUPPORTED
    /** @brief FPU Input Denormal Interrupt */
    FPU_INPUT_DENORMAL_IRQ         = MCM_ISCR_FIDCE_SHIFT,
#endif	
#ifdef FPU_INEXACT_IRQ_SUPPORTED
    /** @brief FPU Inexact Interrupt */
    FPU_INEXACT_IRQ                = MCM_ISCR_FIXCE_SHIFT,
#endif
#ifdef FPU_UNDERFLOW_IRQ_SUPPORTED
    /** @brief FPU Underflow Interrupt */
    FPU_UNDERFLOW_IRQ              = MCM_ISCR_FUFCE_SHIFT,
#endif
#ifdef FPU_OVERFLOW_IRQ_SUPPORTED
    /** @brief FPU Overflow Interrupt */
    FPU_OVERFLOW_IRQ               = MCM_ISCR_FOFCE_SHIFT,
#endif
#ifdef FPU_DIVIDE_BY_ZERO_IRQ_SUPPORTED
    /** @brief FPU Divide-by-Zero Interrupt */
    FPU_DIVIDE_BY_ZERO_IRQ         = MCM_ISCR_FDZCE_SHIFT,
#endif
#ifdef FPU_INVALID_OPERATION_IRQ_SUPPORTED
    /** @brief FPU Invalid Operation Interrupt */
    FPU_INVALID_OPERATION_IRQ      = MCM_ISCR_FIOCE_SHIFT,
#endif
#ifdef TCM_WRITE_ABORT_IRQ_SUPPORTED
    /** @brief TCM Write Abort Interrupt */
    TCM_WRITE_ABORT_IRQ            = MCM_ISCR_WABE_SHIFT,
#endif
#ifdef CACHE_WRITE_BUFFER_ERROR_SUPPORTED
    /** @brief Cache Write Buffer Error */
    CACHE_WRITE_BUFFER_ERROR       = MCM_ISCR_CWBEE_SHIFT
#endif
}System_Ip_IrqType;
#endif /* SYSTEM_IP_ARM_CORTEXM == STD_ON */
#endif /* SYSTEM_IP_CFG_DEFINES_H_ */

/** @} */

