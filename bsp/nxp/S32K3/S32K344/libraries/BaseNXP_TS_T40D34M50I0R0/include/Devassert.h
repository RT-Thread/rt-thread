/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 5.0.0
* Build Version : S32K3_RTD_5_0_0_D2408_ASR_REL_4_7_REV_0000_20241002
*
* Copyright 2020 - 2024 NXP
*
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be 
*   used strictly in accordance with the applicable license terms.  By expressly 
*   accepting such terms or by downloading, installing, activating and/or otherwise 
*   using the software, you are agreeing that you have read, and that you agree to 
*   comply with and are bound by, such license terms.  If you do not agree to be 
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef DEVASSERT_H
#define DEVASSERT_H

#include "Platform_Types.h"
#include "Mcal.h"

/*
    Drivers can use a mechanism to validate data coming from upper software layers (application code) by performing
    a number of checks on input parameters' range or other invariants that can be statically checked (not dependent on
    runtime conditions). A failed validation is indicative of a software bug in application code, therefore it is important
    to use this mechanism during development.
*/

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define DEVASSERT_VENDOR_ID                    43
#define DEVASSERT_AR_RELEASE_MAJOR_VERSION     4
#define DEVASSERT_AR_RELEASE_MINOR_VERSION     7
#define DEVASSERT_AR_RELEASE_REVISION_VERSION  0
#define DEVASSERT_SW_MAJOR_VERSION             5
#define DEVASSERT_SW_MINOR_VERSION             0
#define DEVASSERT_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Devassert.h and Platform_Types.h are of the same version */
    #if ((DEVASSERT_AR_RELEASE_MAJOR_VERSION != PLATFORM_AR_RELEASE_MAJOR_VERSION) || \
         (DEVASSERT_AR_RELEASE_MINOR_VERSION != PLATFORM_AR_RELEASE_MINOR_VERSION)     \
        )
        #error "AUTOSAR Version Numbers of Devassert.h and Platform_Types.h are different"
    #endif
    /* Check if the files Devassert.h and Mcal.h are of the same version */
    #if ((DEVASSERT_AR_RELEASE_MAJOR_VERSION != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (DEVASSERT_AR_RELEASE_MINOR_VERSION != MCAL_AR_RELEASE_MINOR_VERSION)     \
        )
        #error "AUTOSAR Version Numbers of Devassert.h and Mcal.h are different"
    #endif
#endif

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/
#ifdef CCOV_ENABLE
    #define DevAssert(x)
#else


 #if ((MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64) || \
     (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH32) || \
     (MCAL_PLATFORM_ARM == MCAL_ARM_RARCH))
    #define BREAKPOINT_INSTR        "HLT #0"
#elif (MCAL_PLATFORM_ARM == MCAL_ARM_MARCH)
    #define BREAKPOINT_INSTR        "BKPT #0"
#else
    #error "Unsupported architecture!"
#endif

/* Implement default assert macro */
static inline void DevAssert(volatile boolean x)
{
    if(x) { } else { for(;;) {ASM_KEYWORD(BREAKPOINT_INSTR);} }
}
#endif

 #endif /* DEVASSERT_H */

/*******************************************************************************
 * EOF
 ******************************************************************************/
