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
*   @file           CompilerDefinition.h
*   @version 5.0.0
*
*   @brief   AUTOSAR BaseNXP - SWS Compiler abstraction
*   @details The file Compiler.h provides macros for the encapsulation of definitions and
*            declarations.
*            This file contains sample code only. It is not part of the production code deliverables
*
*   @addtogroup BASENXP_COMPONENT
*   @{
*/

#ifndef COMPILERDEFINITION_H
#define COMPILERDEFINITION_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @brief  Parameters that shall be published within the compiler abstraction header file and also in
          the module's description file.
@{
*/
#define COMPILERDEFINITION_VENDOR_ID                      43
#define COMPILERDEFINITION_AR_RELEASE_MAJOR_VERSION       4
#define COMPILERDEFINITION_AR_RELEASE_MINOR_VERSION       7
#define COMPILERDEFINITION_AR_RELEASE_REVISION_VERSION    0
#define COMPILERDEFINITION_SW_MAJOR_VERSION               5
#define COMPILERDEFINITION_SW_MINOR_VERSION               0
#define COMPILERDEFINITION_SW_PATCH_VERSION               0
/**@}*/
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

#ifdef __ghs__
    /**
    * @brief Symbol required to be defined when GreenHills compiler is used.
    */
    #define _GREENHILLS_C_S32K3XX_
#endif
#ifdef __DCC__
    /**
    * @brief Symbol required to be defined when Diab compiler is used.
    */
    #define _DIABDATA_C_S32K3XX_
#endif
#ifdef __MWERKS__
    /**
    * @brief Symbol required to be defined when Codewarrior compiler is used.
    */
    #define _CODEWARRIOR_C_S32K3XX_
#endif
#if (defined(__GNUC__) && !defined(__DCC__))
         /**
        * @brief Symbol required to be defined when GCC ARM compiler is used.
        */
        #define _GCC_C_S32K3XX_
 #endif      
#ifdef __CC_ARM 
        /**
        * @brief Symbol required to be defined when DS5 ARM compiler is used.
        */
        #define _ARM_DS5_C_S32K3XX_     
#endif
#ifdef __ICCARM__ 
        /**
        * @brief Symbol required to be defined when IAR compiler is used.
        */
        #define _IAR_C_S32K3XX_     
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef COMPILERDEFINITION_H */

/** @} */
