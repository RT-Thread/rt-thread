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

/**
*   @file Osif_Software_Semaphore.c
*
*   @addtogroup  osif_drv
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
#include "Osif_Software_Semaphore.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define OSIF_SOFTWARE_SEMAPHORE_VENDOR_ID_C                       43
#define OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MAJOR_VERSION_C        4
#define OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MINOR_VERSION_C        7
#define OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_REVISION_VERSION_C     0
#define OSIF_SOFTWARE_SEMAPHORE_SW_MAJOR_VERSION_C                5
#define OSIF_SOFTWARE_SEMAPHORE_SW_MINOR_VERSION_C                0
#define OSIF_SOFTWARE_SEMAPHORE_SW_PATCH_VERSION_C                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Osif_Software_Semaphore.h */
#if (OSIF_SOFTWARE_SEMAPHORE_VENDOR_ID_C != OSIF_SOFTWARE_SEMAPHORE_VENDOR_ID_H)
    #error "Osif_Software_Semaphore.c and Osif_Software_Semaphore.h have different vendor ids"
#endif
#if ((OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MAJOR_VERSION_C    != OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MAJOR_VERSION_H) || \
     (OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MINOR_VERSION_C    != OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_MINOR_VERSION_H) || \
     (OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_REVISION_VERSION_C != OSIF_SOFTWARE_SEMAPHORE_AR_RELEASE_REVISION_VERSION_H))
    #error "AUTOSAR Version Numbers of Osif_Software_Semaphore.c and Osif_Software_Semaphore.h are different"
#endif
#if ((OSIF_SOFTWARE_SEMAPHORE_SW_MAJOR_VERSION_C != OSIF_SOFTWARE_SEMAPHORE_SW_MAJOR_VERSION_H) || \
     (OSIF_SOFTWARE_SEMAPHORE_SW_MINOR_VERSION_C != OSIF_SOFTWARE_SEMAPHORE_SW_MINOR_VERSION_H) || \
     (OSIF_SOFTWARE_SEMAPHORE_SW_PATCH_VERSION_C != OSIF_SOFTWARE_SEMAPHORE_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Osif_Software_Semaphore.c and Osif_Software_Semaphore.h are different"
#endif

/*==================================================================================================
 *                                      GLOBAL VARIABLES
==================================================================================================*/

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
#define BASENXP_START_SEC_CODE
#include "BaseNXP_MemMap.h"

/* lock semaphore */
boolean Osif_Software_Semaphore_Lock(const uint32 *Semaphore, uint32 Lockval)
{
    uint32 result = 0U;
/*LDRA_NOANALYSIS*/
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    ASM_KEYWORD (" LDREX %0, [%1] \n\t"
                 " CMP %0, #0 \n\t"
                 " IT EQ\n\t"
                 " STREXEQ %0, %2, [%1]"
                 : "=&r" (result) 
                 : "r" (Semaphore), "r" (Lockval));
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
/*LDRA_ANALYSIS*/
    return (result == 0U);
}

/* unlock semaphore */
boolean Osif_Software_Semaphore_Unlock(const uint32 *Semaphore, uint32 Lockval)
{
    uint32 result = 0U;
    uint32 UnlockValue = OSIF_SOFTWARE_SEMAPHORE_UNLOCKED_VALUE;
/*LDRA_NOANALYSIS*/
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    ASM_KEYWORD (" LDREX %0, [%2] \n\t"
                 " CMP %0, %3 \n\t"
                 " IT EQ\n\t"
                 " STREXEQ %0, %1, [%2]"
                 : "=&r" (result)
                 : "r" (UnlockValue), "r" (Semaphore), "r" (Lockval));
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
/*LDRA_ANALYSIS*/
    return (result == 0U);
}
#define BASENXP_STOP_SEC_CODE
#include "BaseNXP_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
