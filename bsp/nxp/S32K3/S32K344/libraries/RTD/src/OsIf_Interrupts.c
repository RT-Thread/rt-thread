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
* Copyright 2020 - 2024 NXP.
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
*   @file
*
*   @addtogroup osif_drv
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
#include "OsIf.h"
#include "OsIf_Interrupts.h"

#if defined(USING_OS_ZEPHYR)
#include <zephyr/kernel.h>
#endif

#if defined(USING_OS_FREERTOS)
#include "OsIf_Cfg_TypesDef.h"
#include "FreeRTOS.h"
#include "task.h"
#endif

#if (defined(USING_OS_ZEPHYR) || defined(USING_OS_FREERTOS))
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define OSIF_INTERRUPTS_VENDOR_ID_C                    43
#define OSIF_INTERRUPTS_AR_RELEASE_MAJOR_VERSION_C     4
#define OSIF_INTERRUPTS_AR_RELEASE_MINOR_VERSION_C     7
#define OSIF_INTERRUPTS_AR_RELEASE_REVISION_VERSION_C  0
#define OSIF_INTERRUPTS_SW_MAJOR_VERSION_C             5
#define OSIF_INTERRUPTS_SW_MINOR_VERSION_C             0
#define OSIF_INTERRUPTS_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if OsIf_Interrupts.c file and OsIf.h file are of the same vendor */
#if (OSIF_INTERRUPTS_VENDOR_ID_C != OSIF_VENDOR_ID)
    #error "OsIf_Interrupts.c and OsIf.h have different vendor ids"
#endif
/* Check if OsIf_Interrupts.c file and OsIf.h file are of the same Autosar version */
#if ((OSIF_INTERRUPTS_AR_RELEASE_MAJOR_VERSION_C    != OSIF_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_INTERRUPTS_AR_RELEASE_MINOR_VERSION_C    != OSIF_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_INTERRUPTS_AR_RELEASE_REVISION_VERSION_C != OSIF_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Interrupts.c and OsIf.h are different"
#endif
/* Check if OsIf_Interrupts.c file and OsIf.h file are of the same Software version */
#if ((OSIF_INTERRUPTS_SW_MAJOR_VERSION_C != OSIF_SW_MAJOR_VERSION) || \
     (OSIF_INTERRUPTS_SW_MINOR_VERSION_C != OSIF_SW_MINOR_VERSION) || \
     (OSIF_INTERRUPTS_SW_PATCH_VERSION_C != OSIF_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Interrupts.c and OsIf.h are different"
#endif

/* Check if OsIf_Interrupts.c file and OsIf_Interrupts.h file are of the same vendor */
#if (OSIF_INTERRUPTS_VENDOR_ID_C != OSIF_INTERRUPTS_VENDOR_ID)
    #error "OsIf_Interrupts.c and OsIf_Interrupts.h have different vendor ids"
#endif
/* Check if OsIf_Interrupts.c file and OsIf_Interrupts.h file are of the same Autosar version */
#if ((OSIF_INTERRUPTS_AR_RELEASE_MAJOR_VERSION_C    != OSIF_INTERRUPTS_AR_RELEASE_MAJOR_VERSION) || \
     (OSIF_INTERRUPTS_AR_RELEASE_MINOR_VERSION_C    != OSIF_INTERRUPTS_AR_RELEASE_MINOR_VERSION) || \
     (OSIF_INTERRUPTS_AR_RELEASE_REVISION_VERSION_C != OSIF_INTERRUPTS_AR_RELEASE_REVISION_VERSION))
    #error "AUTOSAR Version Numbers of OsIf_Interrupts.c and OsIf_Interrupts.h are different"
#endif
/* Check if OsIf_Interrupts.c file and OsIf_Interrupts.h file are of the same Software version */
#if ((OSIF_INTERRUPTS_SW_MAJOR_VERSION_C != OSIF_INTERRUPTS_SW_MAJOR_VERSION) || \
     (OSIF_INTERRUPTS_SW_MINOR_VERSION_C != OSIF_INTERRUPTS_SW_MINOR_VERSION) || \
     (OSIF_INTERRUPTS_SW_PATCH_VERSION_C != OSIF_INTERRUPTS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of OsIf_Interrupts.c and OsIf_Interrupts.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/
#if defined(USING_OS_ZEPHYR)
#if (STD_ON == OSIF_ENABLE_MULTICORE_SUPPORT)
    #define OsIfCoreID()        (OsIf_GetCoreID())
#else
    #define OsIfCoreID()        (0U)
#endif /* STD_ON == OSIF_ENABLE_MULTICORE_SUPPORT */
#endif /* defined(USING_OS_ZEPHYR)*/
/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/
#if defined(USING_OS_ZEPHYR)
#define BASENXP_START_SEC_VAR_CLEARED_32
#include "BaseNXP_MemMap.h"

static uint32 OsIf_au32OldIrqMask[OSIF_MAX_COREIDX_SUPPORTED];
static uint32 OsIf_au32SuspendLevel[OSIF_MAX_COREIDX_SUPPORTED];

#define BASENXP_STOP_SEC_VAR_CLEARED_32
#include "BaseNXP_MemMap.h"

#elif defined(USING_OS_FREERTOS)
#define BASENXP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "BaseNXP_MemMap.h"

volatile UBaseType_t OsIf_InterruptNestingLevel;
volatile UBaseType_t OsIf_SavedInterruptStatus;

#define BASENXP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "BaseNXP_MemMap.h"

#endif /* defined(USING_OS_FREERTOS) */
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

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_Interrupts_SuspendAllInterrupts.
 * Description   : Suspend all interrupts.
 * 
 *END**************************************************************************/
#if defined(USING_OS_ZEPHYR)
void OsIf_Interrupts_SuspendAllInterrupts(void)
{
    uint32 CoreId = OsIfCoreID();

    if (OsIf_au32SuspendLevel[CoreId]++ == 0U)
    {
        OsIf_au32OldIrqMask[CoreId] = arch_irq_lock();
    }
}
#elif defined(USING_OS_FREERTOS)
void OsIf_Interrupts_SuspendAllInterrupts(void)
{
    if (xPortIsInsideInterrupt())
    {
        UBaseType_t CurrentInterruptStatus = taskENTER_CRITICAL_FROM_ISR();

        if (0 == OsIf_InterruptNestingLevel)
        {
            OsIf_SavedInterruptStatus = CurrentInterruptStatus; /* only value from nesting level 0 is needed for restoration */
        }
        OsIf_InterruptNestingLevel++;
    }
    else
    {
        taskENTER_CRITICAL(); /* supports nesting already */
    }
}
#endif /* defined(USING_OS_FREERTOS) */

/*FUNCTION**********************************************************************
 *
 * Function Name : OsIf_Interrupts_ResumeAllInterrupts.
 * Description   : Resume all interrupts.
 * 
 *END**************************************************************************/
#if defined(USING_OS_ZEPHYR)
void OsIf_Interrupts_ResumeAllInterrupts(void)
{
    uint32 CoreId = OsIfCoreID();

    if (--OsIf_au32SuspendLevel[CoreId] == 0U)
    {
       arch_irq_unlock(OsIf_au32OldIrqMask[CoreId]);
    }
}
#elif defined(USING_OS_FREERTOS)
void OsIf_Interrupts_ResumeAllInterrupts(void)
{
    if (xPortIsInsideInterrupt())
    {
        if(0 < OsIf_InterruptNestingLevel)
        { 
            OsIf_InterruptNestingLevel--;
            if( 0 == OsIf_InterruptNestingLevel)
            {
                taskEXIT_CRITICAL_FROM_ISR(OsIf_SavedInterruptStatus);
            }
        }
        else
        {
            #if (STD_ON == OSIF_DEV_ERROR_DETECT)
            (void)Det_ReportError(OSIF_MODULE_ID, OSIF_DRIVER_INSTANCE, OSIF_SID_RESUMEALLINT, OSIF_E_INV_CALL);
            #endif
        }
    }
    else
    {
        taskEXIT_CRITICAL();  /* supports nesting already */
    }
}
#endif /* defined(USING_OS_FREERTOS) */

#define BASENXP_STOP_SEC_CODE
#include "BaseNXP_MemMap.h"

#endif /* defined(USING_OS_ZEPHYR) || defined(USING_OS_FREERTOS) */

#ifdef __cplusplus
}
#endif

/** @} */
