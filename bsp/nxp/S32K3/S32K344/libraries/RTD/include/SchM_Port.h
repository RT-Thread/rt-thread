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
*   @file    SchM_Port.h
*   @version 5.0.0
*
*   @brief   AUTOSAR Rte - module interface
*   @details This file contains the functions prototypes and data types of the AUTOSAR Rte.
*            This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup RTE_MODULE
*   @{
*/

#ifndef SCHM_PORT_H
#define SCHM_PORT_H

#ifdef __cplusplus
extern "C" {
#endif
/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SCHM_PORT_AR_RELEASE_MAJOR_VERSION     4
#define SCHM_PORT_AR_RELEASE_MINOR_VERSION     7
#define SCHM_PORT_AR_RELEASE_REVISION_VERSION  0
#define SCHM_PORT_SW_MAJOR_VERSION             5
#define SCHM_PORT_SW_MINOR_VERSION             0
#define SCHM_PORT_SW_PATCH_VERSION             0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define NUMBER_OF_CORES         (uint8)(4U)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"

#ifdef MCAL_TESTING_ENVIRONMENT
/** 
@brief   This function checks that all entered exclusive areas were also exited. 
@details This function checks that all entered exclusive areas were also exited. The check
         is done by verifying that all reentry_guard_* static variables are back to the
         zero value.
    
@param[in]     void       No input parameters
@return        void       This function does not return a value. Test asserts are used instead. 

@pre  None
@post None

@remarks Covers 
@remarks Implements 
*/
void SchM_Check_port(void);
#endif /*MCAL_TESTING_ENVIRONMENT*/

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_00(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_00(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_01(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_01(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_02(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_02(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_03(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_03(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_04(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_04(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_05(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_05(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_06(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_06(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_07(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_07(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_08(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_08(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_09(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_09(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_10(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_10(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_11(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_11(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_12(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_12(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_13(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_13(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_14(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_14(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_15(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_15(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_16(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_16(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_17(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_17(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_18(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_18(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_19(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_19(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_20(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_20(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_21(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_21(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_22(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_22(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_23(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_23(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_24(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_24(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_25(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_25(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_26(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_26(void);

extern void SchM_Enter_Port_PORT_EXCLUSIVE_AREA_27(void);
extern void SchM_Exit_Port_PORT_EXCLUSIVE_AREA_27(void);




#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* SCHM_PORT_H */
